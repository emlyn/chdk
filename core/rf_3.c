/*
 * RF3 - RangeFinder3.  Calibrated distance computations for the Powershot A620
 *
 * rf_3.c - The standalone RF3 code.
 * Copyright 2007 by Richard Lemieux
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation. You should have received
 * a copy of the license along with this program.
 */

#ifdef TEST_RF3
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#else
#include "math.h"
#include "platform.h"
#endif

/*
2007-05-23  Richard Lemieux.  A620 calibrated distance numbers.

  * This code was tested on the Powershot A620 only.

  * The following functions will together add the display of
    distance related numbers in the OSD/misc window.  This is
    designed to work well in 'manual focus' mode.

  * The new display items are,

      c  Close end of the depth-of-field range.
      d  Focus distance.
      f  Far end of the depth-of-field range.
      H  Hyperfocal distance.
      s  Optimal distance between stereo shots.

    There are two differences with the existing DOF calculator.

      1.  The programs here use calibrated distance numbers as opposed
          to the number returned by Canon.
      2.  It is not necessary to half-press the shutter to see the data
          when in Manual of Av mode.

  * Installation instructions.

    1.  * Open 'grand/core/gui_osd.c' with a program editor.

        * Paste the content of this file just before  function
          'gui_osd_draw_values()' or insert a line such as

          #include "this_file.c"

        * Add the following line at the end of function 'gui_osd_draw_values()'
          and while there, comment out the portions of code that print 'D'.

              gui_osd_draw_rf3();

    2.  Do 'make fir' as usual.

  * Testing the program.

    Compiling this program as follows will return a test program that you
    can run to see typical output.

    cc -DTEST_RF3 -o rf3test rf_3.c -lm
    rf3test


  Summary of distance computations for the Powershot A620

  &2. xH = Av*coc                             [D1D2D_f_coc:13]
  &3. D1 - d0 = f + (1 - xH/f)*f^2/(x + xH)   [xD:8, D1D2D_f_coc:16]
  &4. D - d0  = f + f^2/x                     [xD:8]
  &5. D2 - d0 = f + (1 + xH/f)*f^2/(x - xH)   [xD:8, D1D2D_f_coc:17]
  &6. H  = f + f^2/xH                         [H:11]
  &7. d  = (1/30) * 7.15 * f/(2*xH)           [optimal_stereo_d:20]
  &8.
  &9.  si  = -a1/a0                           [rf2_a620_calibration_specs.html/approach_2:{20,28}]
  &10. fa1 = f^2 / a1                         [rf2_a620_calibration_specs.html/approach_2:26]
  &11. a1  = f^2/fa1                          [10]
  &12. a0  = -a1/si                           [9]
  &13. x   = -a1/si + a1/s                    [1,12]
  &14. x   = (f^2/fa1)*(1/s - 1/si)           [11,13]
*/


static  float f_a[] = {7.300,8.460,9.565,10.835,12.565,14.926,17.342,21.709,29.200};
static  float si[]  = {1350, 1590, 1984, 3614, 4248, 8104, 10341, 11903, 21930}; // 2007-04-27
static  float fa1[] = {0.96458, 0.92003, 0.95259, 1.03059, 0.95736, 0.95754, 0.99251, 0.95281, 0.96006}; // 2007-04-27
static  float d0[]  = {-61.747, -61.747, -61.747, -86.446, -61.747, -61.747, -61.747, -61.747, -61.747}; // 2007-04-27
static char osd_buf[64];

void print_d(float d, float H5, char *t) {
  unsigned int ad = d >= 0.0 ? d : -d;
  unsigned int ad_;
  char *t_;
  short inf;

  if (d >= 0) {
    ad = d;
    t_ = &t[0];
    inf = (d > H5);
  }
  else {
    ad = -d;
    t[0]='-';
    t_ = &t[1];
    inf = ((-d) > H5);
  }

  if (inf) {
    t_[0]='I'; t_[1]='n'; t_[2]='f'; t_[3]=0;
  }
  else if (ad < 140) sprintf(t_,"%d.%.1dcm%s",ad/10,ad%10,""); //   8.4cm, 13.9cm
  else if (ad < 1000) {                                        // 15cm, 99cm
    ad_ = ad + 5;
    if (ad_ < 1000)
      sprintf(t_,"%dcm%s",ad_/10,"");
    else
      sprintf(t_,"1.0m%s","");
      }
  else if (ad < 1400) {                                        // 1.06m, 1.39m
    ad_ = (ad+5)/10;
    if (ad_ < 1000)
      sprintf(t_,"%d.%.2dm%s",ad_/100,ad_%100,"");
    else
      sprintf(t_,"1.4m%s","");
  }
  else if (ad < 10000) {                                       // 1.4m, 9.9m
    ad_ = (ad+50)/100;
    if (ad_ < 100)
      sprintf(t_,"%d.%.1dm%s",ad_/10,ad_%10,"");
    else
      sprintf(t_,"10m%s","");
  }
  else if (ad < 1000000) {                                     // 10m, 999m
    ad_ = ad/100 + 5;
    if (ad_ < 10000)
      sprintf(t_,"%dm%s",ad_/10,"");
    else
      sprintf(t_,"1.0km%s","");
  }
  else  sprintf(t_,"X%s","");
}

void canon_av2s(unsigned short z,           // z = lens_get_zoom_point()
                unsigned short s,           // s = lens_get_focus_pos()
                unsigned short gcav,        // gcav = GetCurrentAvValue()
                unsigned short coc10,       // coc10 = 10 * circle of confusion (microns): typically 6.
                char *tsd, unsigned short tsd_CMAX, // Optimal distance between stereo shots
                char *tc, unsigned short tc_CMAX,   // Close distance  of depth of field range
                char *td, unsigned short td_CMAX,   // Focus distance
                char *tf, unsigned short tf_CMAX,   // Far distance  of depth of field range
                char *tH, unsigned short tH_CMAX    // Hyperfocal distance
                ) {
  float  f  = f_a[z];
  float  Av = pow(2.,(double)((float)gcav/(2.0f*96.0f)));
  float  x  = (f*f/fa1[z])*(1.0f/s - 1.0f/si[z]);
  float  Ar = 0.915E-3f*Av;                   // (mm) [README/diffraction]
  float  coc = coc10/10000.0f;                // (mm) [rf3_a620_specs.html]
  float  ecoc = (Ar > coc ? Ar : coc);        // effective pixel width
  //float  ew  = 7.15f/ecoc;                    // (pixels) Effective image width
  float  xH = Av*ecoc;
  float  H  = f + f*f/xH;
  float  D1 = d0[z] + f + (1.0f - xH/f)*f*f/(x + xH);
  float  D  = d0[z] + f + f*f/x;
  float  D2 = d0[z] + f + (1.0f + xH/f)*f*f/(x - xH);
  float  H5 = 5.0f*H;                                     //  Threshold distance for declaring Infinity.
  float  sd = (1.0f/30.0f) * 7.15f * f/(2.0f*xH);         //  [rf3_a620_specs.html/optimal_stereo_d:21]
  float  sd1  = (1.0f/30.0f) * 7.15f*D1*(D - f)/(f*D);    //  [sd for D2 >= Inf, D1 < Inf]
  // D = H & D1 = H/2 & d = (1/30) * (7.15/f) * (H - f)/2     [rf3_a620_specs.html/optimal_stereo_d:22]
  print_d(D1,H5,tc);
  print_d(D,H5,td);
  print_d(D2,H5,tf);
  print_d(H,H5,tH);
  print_d(((D < 0 ? -D : D) <= H ? sd : sd1),H5,tsd);      //  Use 'sd1`' at distances larger than H
}


#ifdef TEST_RF3

int main() {
  char           tdH[8];
  char           tc[8];
  char           td[8];
  char           tf[8];
  char           tH[8];
  unsigned short i_z;
  unsigned short i_s;
  unsigned short s_t[] = {60,246,309,427,613,760,850,1000,1200,1300,1500,1700,\
                          2200,2800,3300,4000,5000,6000,8000,9000};
  unsigned short s_C = (unsigned short)(sizeof(s_t)/sizeof(unsigned short));

  {
    unsigned short s;
    int            j;

    for (i_z=0; i_z<=8; i_z++) 
      for (j=60; j<=65535; j = j*1.1) {
        s = j;
        canon_av2s(i_z,     // z = lens_get_zoom_point()
                   s,       // s = lens_get_focus_pos()
                   384,     // gcav = GetCurrentAvValue()
                   60,      // coc10 = 10 * circle of confusion (microns): typically 6.
                   tdH, 8, tc, 8, td, 8, tf, 8, tH, 8);
        printf("i_z %u, s %u, %s, dc %s, d %s, df %s, H %s\n",
               i_z,    s,   tdH,    tc,   td,    tf,   tH);
      }
  }

  return 0;
}
#else
void gui_osd_draw_rf3() {
  
  
  static char sd[10],dc[10],d[10],df[10],H[10];

  { unsigned short avv = 0;
    if (mode_get()&(MODE_M | MODE_AV))
         get_property_case(39, (void *)&avv, sizeof(avv));
    else get_property_case(68, (void *)&avv, sizeof(avv));

    canon_av2s((unsigned short)lens_get_zoom_point(),
               (unsigned short)lens_get_focus_pos(),
               (unsigned short)avv,
               (unsigned short)(10*3), // circle of confusion is 3 microns
               sd, 8,
               dc, 8,
               d, 8,
               df, 8,
               H, 8);

    //sprintf(osd_buf, "m %u A %u ", knob, avv, ""); }
    sprintf(osd_buf,"s%7u", (unsigned short)lens_get_focus_pos());
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*6,
                osd_buf,conf.osd_color);
    sprintf(osd_buf,"f%7s",df);
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*7,
                osd_buf,conf.osd_color);
    sprintf(osd_buf,"d%7s",d);
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*8,
                osd_buf, conf.osd_color);
    sprintf(osd_buf,"c%7s",dc);
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*9,
                osd_buf, conf.osd_color);
    sprintf(osd_buf,"s%7s",sd);
    draw_string(conf.values_pos.x, conf.values_pos.y+FONT_HEIGHT*10,
                osd_buf, conf.osd_color); }
}
#endif

/*
  A620
  PropertyCase 39
  in Av mode.
  |-----+------|
  |  Av | PC39 |
  |-----+------|
  | 2.8 |  288 |
  | 3.2 |  320 |
  | 3.5 |  352 |
  |   4 |  384 |
  | 4.5 |  416 |
  |   5 |  448 |
  | 5.6 |  480 |
  | 6.3 |  512 |
  | 7.1 |  544 |
  |   8 |  576 |
  |-----+------|
*/
