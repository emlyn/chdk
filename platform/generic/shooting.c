#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "math.h"
#include "stdlib.h"
#include "conf.h"

#define USE_FILE_COUNTER_FOR_EXP_COUNTING

#define SS_SIZE (sizeof(shutter_speeds_table)/sizeof(shutter_speeds_table[0]))
#define SSID_MIN (shutter_speeds_table[0].id)
#define SSID_MAX (shutter_speeds_table[SS_SIZE-1].id)

#define AS_SIZE (sizeof(aperture_sizes_table)/sizeof(aperture_sizes_table[0]))
#define ASID_MIN (aperture_sizes_table[0].id)
#define ASID_MAX (aperture_sizes_table[AS_SIZE-1].id)

#define AV96_MIN (aperture_sizes_table[0].prop_id)
#define AV96_MAX (aperture_sizes_table[AS_SIZE-1].prop_id)

#define ISO_SIZE (sizeof(iso_table)/sizeof(iso_table[0]))
#define ISO_MIN (iso_table[0].id)
#define ISO_MAX (iso_table[ISO_SIZE-1].id)
#define ISO_MIN_VALUE (iso_table[1-iso_table[0].id].prop_id)

/*define PROPCASE_CONT_MODE_SHOOT_COUNT 		218*/
static short iso_market_base=0;
//static short iso_base=0;
static short sv96_base=0;
static short svm96_base=0;
static short sv96_base_tmp=0;
//static short override_iso=0;
static const double sqrt2=1.4142135623731;//square root from 2 
static const double log_2=0.6931471805599;//natural logarithm of 2
static const double k=12.5;//K is the reflected-light meter calibration constant 
static const short koef[] = {0, 1,10,100,1000};
static const float shutter_koef[] = {0, 0.00001, 0.0001,0.001,0.01,0.1,1,10,100,1000};
static const char * expo_shift[] = { "Off", "1/3Ev","2/3Ev", "1Ev", "1 1/3Ev", "1 2/3Ev", "2Ev", "2 1/3Ev", "2 2/3Ev", "3Ev", "3 1/3Ev", "3 2/3Ev", "4Ev"};
const char* tv_override[]={
#ifdef CAM_EXT_TV_RANGE
    // add very long time exposures as approximately powers of 2, adding 15 exposures
    "2048","1625","1290","1024","812","645","512","406","322","256","203","161","128","101","80",
#endif
    "64","50.8", "40.3", "32", "25.4","20","16", "12.7", "10","8", "6.3","5","4","3.2", "2.5","2", "1.6", "1.3", "1", "0.8", "0.6", "0.5", "0.4", "0.3", "1/4", "1/5", "1/6", "1/8", "1/10", "1/13", "1/15", "1/20", "1/25", "1/30", "1/40", "1/50", "1/60", "1/80", "1/100", "1/125", "1/160", "1/200", "1/250", "1/320", "1/400", "1/500", "1/640","1/800", "1/1000", "1/1250", "1/1600","1/2000","1/2500","1/3200","1/4000", "1/5000", "1/6400", "1/8000", "1/10000", "1/12500", "1/16000", "1/20000", "1/25000", "1/32000", "1/40000", "1/50000", "1/64000","1/80000", "1/100k"};
const int tv_override_amount = sizeof(tv_override)/sizeof(tv_override[0]);

// offset index into tv_override to translate into 1/3 stops in APEX
#if CAM_EXT_TV_RANGE
const int tv_override_zero_shift = 18+15;
#else
const int tv_override_zero_shift = 18;
#endif
static const char * expo_type[] = { "+/-", "-","+"};

static PHOTO_PARAM photo_param_put_off;

static EXPO_BRACKETING_VALUES bracketing;

//***********************
/*

static char debug_str[60];

void debug_char(char * deb_str)
{
 short debug_str_length=strlen(debug_str);
 if	(debug_str_length>50) strcpy(debug_str, "");
 sprintf(debug_str+debug_str_length, "%s", deb_str);
}

void debug_init()
{
 strcpy(debug_str, "");
}


void debug_int(int deb_str)
{
 short debug_str_length=strlen(debug_str);
 if	(debug_str_length>50) strcpy(debug_str, "");
 sprintf(debug_str+debug_str_length, "%d", deb_str);
}


void debug(char * deb_str, int deb_int)
{
 short debug_str_length=strlen(debug_str);
 if	(debug_str_length>50) strcpy(debug_str, "");
 sprintf(debug_str+debug_str_length, "%s", deb_str);
 sprintf(debug_str+strlen(debug_str), "%d", deb_int);
}

char * get_debug()
{
 return debug_str;
}
*/
//***********************

int shooting_get_user_tv_id()
{
#if CAM_HAS_USER_TV_MODES 
    short tvv;
    long i;
    _GetPropertyCase(PROPCASE_USER_TV, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].prop_id == tvv)
	    return shutter_speeds_table[i].id;
    }
#endif        
    return 0;
}

short shooting_get_is_mode()
{
    short ism = 0;
    _GetPropertyCase(PROPCASE_IS_MODE, &ism, sizeof(ism));
    return ism;
}


const ShutterSpeed *shooting_get_tv_line()
{
    short tvv;
    long i;
    _GetPropertyCase(PROPCASE_USER_TV, &tvv, sizeof(tvv));
    for (i=0;i<SS_SIZE;i++){
	   if (shutter_speeds_table[i].prop_id == tvv)
	    return &shutter_speeds_table[i];
    }
    return 0;
}

void shooting_set_user_tv_by_id(int v)
{
#if CAM_HAS_USER_TV_MODES
if ((mode_get()&MODE_MASK) != MODE_PLAY){
    long i;
//    if ((v<SSID_MIN) || (v>SSID_MAX))
//	return;
 for (i=0;i<SS_SIZE;i++){
	if (shutter_speeds_table[i].id == v){
	    short vv = shutter_speeds_table[i].prop_id;
	    _SetPropertyCase(PROPCASE_USER_TV, &vv, sizeof(vv));
	    //_SetPropertyCase(PROPCASE_TV, &vv, sizeof(vv));
	    return;
	 }
 }
}
#endif 
}
void shooting_set_prop(int id, int v)
{
   short vv = v;
   _SetPropertyCase(id, &vv, sizeof(vv));
   return;
}

int shooting_get_prop(int id)
{
    short vv;
    _GetPropertyCase(id, &vv, sizeof(vv));
    return vv;
}

short shooting_get_canon_iso_mode()
{
    short isom;
    _GetPropertyCase(PROPCASE_ISO_MODE, &isom, sizeof(isom));
     return isom;
}


int shooting_get_iso_mode()
{
    short isov;
    long i;
    _GetPropertyCase(PROPCASE_ISO_MODE, &isov, sizeof(isov));
    for (i=0;i<ISO_SIZE;i++){
			if (iso_table[i].prop_id == isov)
	   		 return iso_table[i].id;
    }
    return 0;
}

void shooting_set_user_tv_by_id_rel(int v)
{
#if CAM_HAS_USER_TV_MODES
if ((mode_get()&MODE_MASK) != MODE_PLAY){
    int cv = shooting_get_user_tv_id();
    shooting_set_user_tv_by_id(cv+v);
}
#endif    
}

int shooting_get_user_av_id()
{
#if CAM_HAS_IRIS_DIAPHRAGM
    short avv;
    long i;
    _GetPropertyCase(PROPCASE_USER_AV, &avv, sizeof(avv));
    for (i=0;i<AS_SIZE;i++){
			if (aperture_sizes_table[i].prop_id == avv)
	   		 return aperture_sizes_table[i].id;
    }
#endif    
    return 0;
}

short shooting_get_real_aperture() {
//#if !CAM_HAS_IRIS_DIAPHRAGM
//    return shooting_get_min_real_aperture();
//#else
//I hope that GetCurrentAvValue is correct for ixus70_sd1000 ixus700_sd500 now
    return shooting_get_aperture_from_av96(_GetCurrentAvValue());
//#endif
}

short shooting_get_aperture_from_av96(short av96) {
	if (av96) return (short)((pow(sqrt2, ((double)av96)/96.0))*100.0);
	else return -1;
}

short shooting_get_min_real_aperture() {
	 short av96;
	_GetPropertyCase(PROPCASE_MIN_AV, &av96, sizeof(av96));
	if (av96) return shooting_get_aperture_from_av96(av96);
	else return shooting_get_real_aperture();
}

short shooting_get_iso_from_sv96(short sv96)
{
    return (short)(pow(2, (((double) sv96+168.0)/96.0)));
}

short shooting_get_iso_real()
{
    short sv;
    _GetPropertyCase(PROPCASE_SV, &sv, sizeof(sv));
    if (sv == 0) { 
     return 0;
    }
    return shooting_get_iso_from_sv96(sv);
}

short shooting_get_svm96()
{
    short  sv;
     _GetPropertyCase(PROPCASE_SV_MARKET, &sv, sizeof(sv));
     return sv;
}

short shooting_get_sv96()
{
    short  sv;
     _GetPropertyCase(PROPCASE_SV, &sv, sizeof(sv));
     return sv;
}

short shooting_get_base_sv96()
{
   short dsv,sv;
   if (shooting_get_canon_iso_mode()<50) { 	
       _GetPropertyCase(PROPCASE_DELTA_SV, &dsv, sizeof(dsv));
       _GetPropertyCase(PROPCASE_SV, &sv, sizeof(sv));
       sv96_base=(sv-dsv);
   }
   return sv96_base;
}

short shooting_get_sv96_from_iso(short iso)
{
  if  (iso>0) 
    return (short)(log(pow(2.0,(-7.0/4.0))*(double)(iso))*96.0/(log_2));
  return 0;  
}

short shooting_get_svm96_from_iso(short iso)
{
   if  (iso>0) return (short)(log((double)(iso)*32.0/100.0)*96.0/(log_2));
   return 0;   
}  

short shooting_get_iso_market_from_svm96(short svm96)
{
	if (svm96>0 )
		return (short)((double)pow(2, (((double)svm96)/96.0))*100.0/32.0);
	return 0;	
}

short shooting_get_iso_market_base()
{
//if ((iso_market_base==0) && (shooting_get_iso_mode() <= 0)) {
//	 iso_market_base=(short)shooting_get_iso_market_from_svm96(shooting_get_svm96());
// }
 //return iso_market_base;
  if (iso_market_base==0) {
      if (ISO_MIN_VALUE==50) iso_market_base=50;
      else iso_market_base=100;
     }
  return iso_market_base; 	
}

short shooting_get_svm96_base()
{
	if (svm96_base==0) svm96_base=shooting_get_svm96_from_iso(shooting_get_iso_market_base());
	return svm96_base;
}

short shooting_get_iso_base()
{
	sv96_base=shooting_get_base_sv96();
	if (sv96_base!=0) return shooting_get_iso_from_sv96(sv96_base);
	else return 0;
}

// AUTOISO:EXIF
short shooting_get_iso_market()
{
    //double koef;
    short iso_mode=shooting_get_canon_iso_mode();
    if ((iso_mode < 50) || (conf.iso_override_koef && conf.iso_override_value) || (conf.iso_bracket_koef && conf.iso_bracket_value)) 
     {
      short iso_b=shooting_get_iso_base();
      if (iso_b) return (short)((shooting_get_iso_market_base()*shooting_get_iso_real())/iso_b);
     }
    return iso_mode;
}

void shooting_set_sv96(short sv96, short is_now){
  short dsv96=0, iso_mode=shooting_get_canon_iso_mode(); 	
if ((mode_get()&MODE_MASK) != MODE_PLAY){
  if (is_now)  {
    if (iso_mode<50) dsv96 =sv96-shooting_get_base_sv96();
    else if (sv96_base) dsv96=sv96-sv96_base;
	else if (sv96_base_tmp) dsv96=sv96-sv96_base_tmp;  
	else
	 { 
	 sv96_base_tmp= (short)((shooting_get_svm96_base()*shooting_get_sv96())/shooting_get_svm96());   
	 dsv96=sv96-sv96_base_tmp;
	 }	 
    while ((shooting_is_flash_ready()!=1) || (focus_busy));
    short svm96_base =shooting_get_svm96_base();
    if (iso_mode>=50) shooting_set_iso_mode(0);
    _SetPropertyCase(PROPCASE_SV_MARKET, &svm96_base, sizeof(svm96_base));
    _SetPropertyCase(PROPCASE_SV, &sv96, sizeof(sv96));
    _SetPropertyCase(PROPCASE_DELTA_SV, &dsv96, sizeof(dsv96));
  }
  else   photo_param_put_off.sv96=sv96;
}
}

/*void shooting_set_iso_real_delta_from_base(int diso)
{
 return;
 int iso=(int)((short)shooting_get_iso_base()+diso);
 
 if (iso>0) {
    shooting_set_sv96((short)(shooting_get_sv96_from_iso(iso)));
  }
}*/

void shooting_set_iso_real(short iso, short is_now)
{
if ((mode_get()&MODE_MASK) != MODE_PLAY){
	if (iso>0) shooting_set_sv96(shooting_get_sv96_from_iso(iso), is_now);
}
}

short shooting_get_bv96()
{
    short bv = 0;
    _GetPropertyCase(PROPCASE_BV, &bv, sizeof(bv));
    return bv;
}

short shooting_get_canon_overexposure_value()
{
    short bv = 0;
    _GetPropertyCase(PROPCASE_OVEREXPOSURE, &bv, sizeof(bv));
    return bv;
}


short shooting_get_flash_mode()
{
    short fm = 0;
    _GetPropertyCase(PROPCASE_FLASH_MODE, &fm, sizeof(fm));
    return fm;
}

int shooting_get_luminance()// http://en.wikipedia.org/wiki/APEX_system
{
    short bv = shooting_get_bv96();
    int b=(int)(100*k*pow(2.0,((double)(bv-168)/96.0)));
    return b;
}

/*void shooting_set_iso_market(int isom)
{
	if (isom>0) {
   shooting_set_sv96(shooting_get_sv96_from_iso((int)(((double)isom*(double)shooting_get_iso_base())/(double)shooting_get_iso_market_base())));
  }
}*/

int shooting_get_exif_subject_dist()
{
    int sd = 0;
    _GetPropertyCase(PROPCASE_SUBJECT_DIST1, &sd, sizeof(sd));
    return sd;
}

int shooting_get_lens_to_focal_plane_width()
{
	return (int)(lens_get_focus_pos()-lens_get_focus_pos_from_lens());
}

int shooting_get_hyperfocal_distance_()
{
  int av=shooting_get_real_aperture();
  int fl=get_focal_length(lens_get_zoom_point());	
  if ((av>0) && (fl>0)) return (fl*fl)/(10*circle_of_confusion*av);
  else return (-1);
}

int shooting_get_hyperfocal_distance()
{
 int h=shooting_get_hyperfocal_distance_();
 if ((h>0) && (conf.dof_dist_from_lens)) 
   return (h-shooting_get_lens_to_focal_plane_width());
 else return h;
}

int shooting_get_hyperfocal_distance_f(int av, int fl)
{
  if ((av>0) && (fl>0) && (circle_of_confusion>0)) return (fl*fl)/(10*circle_of_confusion*av);
  else return (-1);
}

int shooting_get_canon_subject_distance()
{
	if (conf.dof_use_exif_subj_dist) return shooting_get_exif_subject_dist();
	else return lens_get_focus_pos();
}

int shooting_get_subject_distance_()
{
   if (!conf.dof_subj_dist_as_near_limit) return shooting_get_canon_subject_distance();
   else {
    	int h, v, m;
   		int fl=get_focal_length(lens_get_zoom_point()); 
    	int near=shooting_get_canon_subject_distance();	
        int v1=(fl*fl);
      	int av_min=shooting_get_min_real_aperture();
        int c_of_c=circle_of_confusion*10;
        if ((av_min!=0) && (c_of_c!=0) && (v1)) {
		    h=v1/(c_of_c*av_min);
    	    if ((near>0) && (near<MAX_DIST)) {
    		  v=(h-near);
    		  m=h*near;
    		  if ((v>0) && (m>0)) return m/v;  
       	     }
        }
       	return (-1);
    }
}

int shooting_get_subject_distance()
{
 int h=shooting_get_subject_distance_();
 if ((h>0) && (conf.dof_dist_from_lens)) 
   return (h-shooting_get_lens_to_focal_plane_width());
 else return h;
}

int shooting_get_near_limit_of_acceptable_sharpness_()
{
	int s=shooting_get_canon_subject_distance();	
	if (conf.dof_subj_dist_as_near_limit) return s;
    else {
      int h = shooting_get_hyperfocal_distance_();	
      int m = h*s;
      int v = h+s;
      if ((m>0) && (v>0)) return (m/v);
      else return (-1);
    }
}

int shooting_get_near_limit_of_acceptable_sharpness()
{
 int h=shooting_get_near_limit_of_acceptable_sharpness_();
 if ((h>0) && (conf.dof_dist_from_lens)) 
   return (h-shooting_get_lens_to_focal_plane_width());
 else return h;
}

int shooting_get_near_limit_f(int s, int a, int fl)
{
      int h = shooting_get_hyperfocal_distance_f(a, fl);	
      int m = h*s;
      int v = h+s;
      if ((m>0) && (v>0)) return (m/v);
      else return (-1);
}

int shooting_get_far_limit_of_acceptable_sharpness_()
{
	int s=shooting_get_subject_distance_(), h=shooting_get_hyperfocal_distance_();	
    int v = h-s;
    int m = h*s;
    if ((m>0) && (v>0)) return (m/v);
    else return (-1);
}

int shooting_get_far_limit_of_acceptable_sharpness()
{
 int h=shooting_get_far_limit_of_acceptable_sharpness_();
 if ((h>0) && (conf.dof_dist_from_lens)) 
   return (h-shooting_get_lens_to_focal_plane_width());
 else return h;
}

int shooting_get_depth_of_field()
{
  int far=shooting_get_far_limit_of_acceptable_sharpness_(), near=shooting_get_near_limit_of_acceptable_sharpness_();
  if ((far>0) && (near>0)) return far-near;
  else return (-1);
}

short shooting_get_tv96_from_shutter_speed(float t)
{
  if (t>0) return (short) (96.0*log(1.0/t)/log_2);  
  else return (-10000);
}

float shooting_get_shutter_speed_from_tv96(short tv)
{
  return  pow(2,(float)((-1)*tv)/96.0 );  
}

short shooting_get_tv96()
{
    short tv96;
    _GetPropertyCase(PROPCASE_TV, &tv96, sizeof(tv96));
    return tv96;
}

short shooting_get_user_tv96()
{
#if CAM_HAS_USER_TV_MODES
    short tv;
    _GetPropertyCase(PROPCASE_USER_TV, &tv, sizeof(tv));
    return tv;
#else       
    return 0;
#endif    
}

void shooting_set_user_tv96(short v)
{
#if CAM_HAS_USER_TV_MODES
if ((mode_get()&MODE_MASK) != MODE_PLAY){
long i;
//    if ((v<SSID_MIN) || (v>SSID_MAX))
//	return;
 for (i=0;i<SS_SIZE;i++){
  	if (shutter_speeds_table[i].prop_id == v){
  		_SetPropertyCase(PROPCASE_USER_TV, &v, sizeof(v));
  		//_SetPropertyCase(PROPCASE_TV, &v, sizeof(v));
	    return;
	  }
  }
}
#endif  
}

void shooting_set_tv96(short v, short is_now)
{
 long i;
//    if ((v<SSID_MIN) || (v>SSID_MAX))
//	return;
if ((mode_get()&MODE_MASK) != MODE_PLAY){
 for (i=0;i<SS_SIZE;i++){
  	if (shutter_speeds_table[i].prop_id == v){
       shooting_set_tv96_direct(v, is_now);
       return;
     }
  }
}
}

void shooting_set_tv96_direct(short v, short is_now)
{
if ((mode_get()&MODE_MASK) != MODE_PLAY){
   	if(is_now) {
	   _SetPropertyCase(PROPCASE_TV, &v, sizeof(v));
   	}
   	else photo_param_put_off.tv96=v; 
}
}


void shooting_set_shutter_speed(float t, short is_now)
{
	if (t>0) shooting_set_tv96_direct((short) 96.0*log(1/t)/log_2, is_now);  
}

void shooting_set_shutter_speed_ubasic(int t, short is_now)
{
if ((mode_get()&MODE_MASK) != MODE_PLAY){
	if (t>0) shooting_set_tv96_direct((short) (96.0*log(100000.0/(double)t)/log_2), is_now);  
}
}

short shooting_get_av96()
{
    short av;
    _GetPropertyCase(PROPCASE_AV, &av, sizeof(av));
    return av;
}

short shooting_get_aperture_sizes_table_size()
{
    return AS_SIZE;
}


short shooting_get_aperture_sizes_table_prop_id(short i)
{
    return aperture_sizes_table[i].prop_id;
}

short shooting_get_max_aperture_sizes_table_prop_id()
{
    return AV96_MAX;
}



short shooting_get_av_prop_id()
{
    short av;
    _GetPropertyCase(PROPCASE_AV, &av, sizeof(av));
    return av;
}



short shooting_get_user_av96()
{
#if CAM_HAS_IRIS_DIAPHRAGM
    short av;
    _GetPropertyCase(PROPCASE_USER_AV, &av, sizeof(av));
    return av;
#else     
    return 0;
#endif
}


void shooting_set_av96(short v, short is_now)
{
#if CAM_HAS_IRIS_DIAPHRAGM	
if ((mode_get()&MODE_MASK) != MODE_PLAY){
 long i;
//    if ((v<ASID_MIN) || (v>ASID_MAX))
//	return;
 for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == v){
	   shooting_set_av96_direct(v, is_now);
	   return;
	}
  }
}
#endif  
}

void shooting_set_nd_filter_state(short v, short is_now)
{
#if CAM_HAS_ND_FILTER
if ((mode_get()&MODE_MASK) != MODE_PLAY){
	if (is_now) {
	 if (v==1) _PutInNdFilter();
	 else if (v==2) _PutOutNdFilter();
	}
	else photo_param_put_off.nd_filter=v;
}
#endif	
}



void shooting_set_av96_direct(short v, short is_now)
{  
#if CAM_HAS_IRIS_DIAPHRAGM
if ((mode_get()&MODE_MASK) != MODE_PLAY){
 if(is_now) {
   _SetPropertyCase(PROPCASE_AV, &v, sizeof(v));
 }
 else photo_param_put_off.av96=v;
}
#endif
}


void shooting_set_user_av96(short v)
{
#if CAM_HAS_IRIS_DIAPHRAGM
    long i;
if ((mode_get()&MODE_MASK) != MODE_PLAY){
//    if ((v<ASID_MIN) || (v>ASID_MAX))
//	return;

 for (i=0;i<AS_SIZE;i++){
	if (aperture_sizes_table[i].prop_id == v){
		  _SetPropertyCase(PROPCASE_USER_AV, &v, sizeof(v));
		  //_SetPropertyCase(PROPCASE_AV, &v, sizeof(v));
	    return;
	}
 }
}
#endif		   
}

short shooting_get_drive_mode()
{
    short m;
// reyalp - this is related to http://chdk.setepontos.com/index.php/topic,3994.405.html
// TODO
#if defined (CAMERA_sx200is)
   short n;
   // unlike other cameras, sx200 does set PROPCASE_DRIVE_MODE when in custom timer mode
   // SX 200 IS 0,1,2,3,4=Off, 2 Second, Custom, Face Detection
   _GetPropertyCase(PROPCASE_TIMER_MODE, &n, sizeof(n));
   // note we return this only in custom mode.
   // Other cameras would return 3 if any timer mode is set (?) even if it doesn't do multiple exposures
   // note that face detect does multiple exposure
   if(n==3){
      return n;
   }
#endif

    _GetPropertyCase(PROPCASE_DRIVE_MODE, &m, sizeof(m));
    return m;
}

short shooting_can_focus()
{
#if !CAM_CAN_SD_OVER_NOT_IN_MF && CAM_CAN_SD_OVERRIDE
 int m=mode_get()&MODE_SHOOTING_MASK;
 int mode_video=((m==MODE_VIDEO_STD) || 
			    (m==MODE_VIDEO_SPEED) ||  
			    (m==MODE_VIDEO_COMPACT) ||
			    (m==MODE_VIDEO_MY_COLORS) || 
			    (m==MODE_VIDEO_TIME_LAPSE) ||
			    (m==MODE_VIDEO_COLOR_ACCENT));
  return (shooting_get_focus_mode() || mode_video);
#elif !CAM_CAN_SD_OVERRIDE
 int m=mode_get()&MODE_SHOOTING_MASK;
 int mode_video=((m==MODE_VIDEO_STD) || 
			    (m==MODE_VIDEO_SPEED) ||  
			    (m==MODE_VIDEO_COMPACT) ||
			    (m==MODE_VIDEO_MY_COLORS) || 
    	        (m==MODE_VIDEO_TIME_LAPSE) ||
			    (m==MODE_VIDEO_COLOR_ACCENT));
  return mode_video;
#elif defined (CAMERA_ixus800_sd700)                				   
 int m=mode_get()&MODE_SHOOTING_MASK;
  return (shooting_get_zoom()<8) && (m!=MODE_AUTO) && (m!=MODE_SCN_WATER);
#else 
  return 1;  
#endif 			  
}

short shooting_get_common_focus_mode()
{
#if !CAM_HAS_MANUAL_FOCUS && CAM_CAN_SD_OVERRIDE
  return shooting_get_subject_distance_override_koef();
#elif !CAM_CAN_SD_OVERRIDE
  return 0;
#else 
  return shooting_get_focus_mode();
#endif 			  
}

short shooting_get_focus_mode()
{
  short m;
  _GetPropertyCase(PROPCASE_FOCUS_MODE, &m, sizeof(m));
  return m;
}


/*
short shooting_get_continuous_mode_shoot_count()
{
    short c;
    _GetPropertyCase(PROPCASE_CONT_MODE_SHOOT_COUNT, &c, sizeof(c));
    return c;
}
*/


void shooting_set_user_av_by_id(int v)
{
#if CAM_HAS_IRIS_DIAPHRAGM
long i;
if ((mode_get()&MODE_MASK) != MODE_PLAY){
//    if ((v<ASID_MIN) || (v>ASID_MAX))
//	return;
  for (i=0;i<AS_SIZE;i++){
		if (aperture_sizes_table[i].id == v){
	    short vv = aperture_sizes_table[i].prop_id;
	    _SetPropertyCase(PROPCASE_USER_AV, &vv, sizeof(vv));
	    //_SetPropertyCase(PROPCASE_AV, &vv, sizeof(vv));
	    return;
		}
  }
}
#endif	      
}

void shooting_set_user_av_by_id_rel(int v)
{
#if CAM_HAS_IRIS_DIAPHRAGM
if ((mode_get()&MODE_MASK) != MODE_PLAY){
    int cv = shooting_get_user_av_id();
    shooting_set_user_av_by_id(cv+v);
}
#endif    
}


int shooting_get_day_seconds()
{
    unsigned long t;
    struct tm *ttm;
    t = time(NULL);
    ttm = localtime(&t);
    return ttm->tm_hour * 3600 + ttm->tm_min * 60 + ttm->tm_sec;
}

int shooting_get_tick_count()
{
    return (int)get_tick_count();
}

void shooting_set_iso_mode(int v)
{
 long i;
 for (i=0;i<ISO_SIZE;i++){
	if (iso_table[i].id == v){
	    short vv = iso_table[i].prop_id;
	    _SetPropertyCase(PROPCASE_ISO_MODE, &vv, sizeof(vv));
	    return;
	}
  }
}

int shooting_in_progress()
{
    int t = 0;
    _GetPropertyCase(PROPCASE_SHOOTING, &t, sizeof(&t));
    return t != 0;
}

int shooting_is_flash()
{
 int t = 0;	
 _GetPropertyCase(PROPCASE_IS_FLASH_READY, &t,sizeof(&t));
 return t;
}

int shooting_is_flash_ready()
{
   int t = 0;
/* well, I'm not sure what's exactly is happening here
 * but it works for a610-100e
 */
   // _GetPropertyCase(204, &t, 4);
   // if (t == 3){
   _GetPropertyCase(PROPCASE_FLASH_MODE, &t, sizeof(&t));
   if ((t != 2) && (shooting_in_progress()))
     if (shooting_is_flash()) return _IsStrobeChargeCompleted();
   return 1;
}

long get_file_counter()
{
#ifndef PARAM_FILE_COUNTER
#	error Please define PARAM_FILE_COUNTER in platform`s shooting.c!
#endif
    long v = 0;
    get_parameter_data(PARAM_FILE_COUNTER, &v, 4);
    return v;
}

long get_exposure_counter()
{
#if defined(USE_FILE_COUNTER_FOR_EXP_COUNTING) || !defined(PARAM_EXPOSURE_COUNTER)
    long v = 0;
    get_parameter_data(PARAM_FILE_COUNTER, &v, 4);
    v = ((v>>4)&0x3FFF);
    return v;
#else
    long v = 0;
    get_parameter_data(PARAM_EXPOSURE_COUNTER, &v, 4);
    return v;
#endif
}

short shooting_get_ev_correction1()
{
    short evc1 = 0;
    _GetPropertyCase(PROPCASE_EV_CORRECTION_1, &evc1, sizeof(evc1));
    return evc1;
}

#if CAM_QUALITY_OVERRIDE
void shooting_set_image_quality(int imq)
{
  if (imq != 3){
    _SetPropertyCase(PROPCASE_QUALITY, &imq, sizeof(imq));
  }
}
#endif

int shooting_get_zoom() {
    return lens_get_zoom_point();
}

void shooting_set_zoom(int v) {
    int dist;
if ((mode_get()&MODE_MASK) != MODE_PLAY)
	{
    dist = shooting_get_focus();
    lens_set_zoom_point(v);
    shooting_set_focus(dist, SET_NOW);
  }
}

void shooting_set_zoom_rel(int v) {
    int cv = shooting_get_zoom();
if ((mode_get()&MODE_MASK) != MODE_PLAY){
    shooting_set_zoom(cv+v);
}
}

void shooting_set_zoom_speed(int v) {
if ((mode_get()&MODE_MASK) != MODE_PLAY){
    lens_set_zoom_speed(v);
}
}

int shooting_get_focus() {
	return shooting_get_subject_distance();
}

void shooting_set_focus(int v, short is_now) {
	int s=v;
if ((mode_get()&MODE_MASK) != MODE_PLAY){
	if ((is_now) && shooting_can_focus()) {
	  if (conf.dof_dist_from_lens) s+=shooting_get_lens_to_focal_plane_width();
	  if ((!conf.dof_subj_dist_as_near_limit) && (s>0)) lens_set_focus_pos((s<MAX_DIST)?s:MAX_DIST); 
	  else {
        int near=shooting_get_near_limit_f(s,shooting_get_min_real_aperture(),get_focal_length(lens_get_zoom_point()));
        if (near>0) lens_set_focus_pos((near<MAX_DIST)?near:MAX_DIST); 
	  }
	}
	else photo_param_put_off.subj_dist=v;
}
}

void shooting_set_autoiso(int iso_mode) {
	short max_iso;
	switch (iso_mode) {
		case -1: // ISO HI
			max_iso = conf.autoiso_max_iso_hi*10;
			break;
		case 0: // ISO AUTO
			max_iso = conf.autoiso_max_iso_auto*10;
			break;
		default:
			return;
	}
	int m=mode_get()&MODE_SHOOTING_MASK;
	if (m==MODE_M || m==MODE_TV || m==MODE_STITCH) return; //Only operate outside of M and Tv
	static const short shutter[]={0, 8, 15, 30, 60, 125, 250, 500, 1000};
	float current_shutter = shooting_get_shutter_speed_from_tv96(shooting_get_tv96());
	
	short current_iso=shooting_get_iso_real();
		
	short min_shutter = shutter[conf.autoiso_shutter];
	if (min_shutter == 0)
		{
			short IS_factor = (shooting_get_is_mode()<=1)?conf.autoiso_is_factor:1;
			min_shutter = get_focal_length(lens_get_zoom_point())*conf.autoiso_user_factor / (IS_factor*1000);
	    	//min_shutter is NOT 1/Xs but optimized for the calculation.
		}

	short target_iso = current_iso * min_shutter * current_shutter;
	short min_iso = conf.autoiso_min_iso*10;
	
	if (target_iso > max_iso)
		{ target_iso = max_iso; }
	else if (target_iso < min_iso)
		{ target_iso = min_iso; }
	
	float target_shutter = current_shutter *  current_iso / target_iso;
	
	shooting_set_shutter_speed(target_shutter, SET_NOW);
	
    shooting_set_iso_real(target_iso, SET_NOW);
	
}

void shooting_video_bitrate_change(int v){
 int m[]={1,2,3,4,5,6,7,8,10,12};  // m[v]/4 = bitrate*1x
 if (v>=(sizeof(m)/sizeof(m[0]))) v=(sizeof(m)/sizeof(m[0]))-1;
#if CAM_CHDK_HAS_EXT_VIDEO_MENU
 change_video_tables(m[v],4);
#endif
}

float shooting_get_shutter_speed_override_value()
{
  return (float)conf.tv_override_value*shutter_koef[conf.tv_override_koef];  
}

const char * shooting_get_tv_bracket_value()
{
  return expo_shift[conf.tv_bracket_value];
}

const char * shooting_get_tv_override_value()
{
  return tv_override[conf.tv_override_value];
}


const char * shooting_get_bracket_type()
{
  return expo_type[conf.bracket_type];  
}


short shooting_get_iso_override_value()
{
  return conf.iso_override_value*koef[conf.iso_override_koef];  
}

short shooting_get_iso_bracket_value()
{
  return conf.iso_bracket_value*koef[conf.iso_bracket_koef];  
}



short shooting_get_av96_override_value()
{
  if (conf.av_override_value<=AS_SIZE)	return (short) aperture_sizes_table[conf.av_override_value-1].prop_id;
  else return (short) (AV96_MAX+32*(conf.av_override_value-AS_SIZE));
}

const char * shooting_get_av_bracket_value()
{
  return expo_shift[conf.av_bracket_value];  
}


int shooting_get_subject_distance_override_value()
{
  return conf.subj_dist_override_value;
}

int shooting_get_subject_distance_bracket_value()
{
  return conf.subj_dist_bracket_value*koef[conf.subj_dist_bracket_koef];
}

int shooting_get_subject_distance_override_koef()
{
  static const short koef[] = {0, 1,10,100,1000};
  return koef[(conf.subj_dist_override_koef)];

}

void shooting_tv_bracketing(){
  short value, is_odd;
  int m=mode_get()&MODE_SHOOTING_MASK;
  if (bracketing.shoot_counter==0) { // first shoot
    bracketing.shoot_counter=1;
    // if Tv override is enabled... (this was adapted from function shooting_expo_param_override() )
    if ( ((conf.tv_enum_type) || (conf.tv_override_value)) && (conf.tv_override_koef) && !(conf.override_disable==1) ) { 
      // ...use Tv override value as seed for bracketing:
      if (conf.tv_enum_type) 
        bracketing.tv96 = 32*(conf.tv_override_value-tv_override_zero_shift);
      else 
        bracketing.tv96 = shooting_get_tv96_from_shutter_speed(shooting_get_shutter_speed_override_value());
    }
    // Tv override is disabled, use camera's opinion of Tv for bracketing seed value.
    else {
      #if defined (CAMERA_tx1) // M mode is actually automatic on the tx1.
      bracketing.tv96=shooting_get_tv96();
      #else
      if (!(m==MODE_M || m==MODE_TV)) bracketing.tv96=shooting_get_tv96(); 
      else bracketing.tv96=shooting_get_user_tv96();
      #endif
    }
    bracketing.tv96_step=32*conf.tv_bracket_value;
  }
  // other shoots
   bracketing.shoot_counter++;   
   is_odd=(bracketing.shoot_counter&1);
   if ((!is_odd) || (conf.bracket_type>0)) bracketing.dtv96+=bracketing.tv96_step;
   if (((!is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==1))  value=bracketing.tv96-bracketing.dtv96;
   else value=bracketing.tv96+bracketing.dtv96;
   shooting_set_tv96_direct(value, SET_NOW);
}

void shooting_av_bracketing(){
 short value, is_odd;
 int m=mode_get()&MODE_SHOOTING_MASK;
 if (bracketing.shoot_counter==0) { // first shoot
    bracketing.shoot_counter=1;
    //short av_override_value=shooting_get_av96_override_value;
    //if (av_override_value) bracketing.av96=av_override_value;
    if (!(m==MODE_M || m==MODE_AV)) bracketing.av96=shooting_get_av96(); 
	else bracketing.av96=shooting_get_user_av96();
    bracketing.av96_step=32*conf.av_bracket_value;
  }
  // other shoots
   bracketing.shoot_counter++;   
   is_odd=(bracketing.shoot_counter&1);
   if (((!is_odd) || (conf.bracket_type>0)) || (((is_odd) && (conf.bracket_type==0)) && ((bracketing.av96-bracketing.dav96)<AV96_MIN))) 
       bracketing.dav96+=bracketing.av96_step;
   if ((((!is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==1)) && ((bracketing.av96-bracketing.dav96)>=AV96_MIN))
     {
     value=bracketing.av96-bracketing.dav96;
     shooting_set_av96_direct(value, SET_NOW);
     }
   else if (((is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==2)  || (((!is_odd) && (conf.bracket_type==0)) && ((bracketing.av96-bracketing.dav96)<AV96_MIN)))
     { 
     value=bracketing.av96+bracketing.dav96;
     shooting_set_av96_direct(value, SET_NOW);
     }
}


void shooting_iso_bracketing(){
 short value=0, is_odd;
 if (bracketing.shoot_counter==0) { // first shoot
    bracketing.shoot_counter=1;
    bracketing.iso=shooting_get_iso_real();
    bracketing.iso_step=shooting_get_iso_bracket_value();
    }
  // other shoots
   bracketing.shoot_counter++;   
   is_odd=(bracketing.shoot_counter&1);
   
   if (((!is_odd) || (conf.bracket_type>0)) || (((is_odd) && (conf.bracket_type==0)) && (bracketing.iso<=bracketing.diso))) 
    {
   	   bracketing.diso+=bracketing.iso_step;
    }
   if ((((!is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==1)) && (bracketing.iso>bracketing.diso))
     {
     value=bracketing.iso-bracketing.diso;
     shooting_set_iso_real(value, SET_NOW);
     }
   else if ((((is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==2)) || (((!is_odd) && (conf.bracket_type==0)) && (bracketing.iso<=bracketing.diso)))
     {
     value=bracketing.iso+bracketing.diso;
     shooting_set_iso_real(value, SET_NOW);
     }
}

void shooting_subject_distance_bracketing(){
 short value=0, is_odd;
 if (bracketing.shoot_counter==0) { // first shoot
    bracketing.shoot_counter=1;
    bracketing.subj_dist=shooting_get_focus();
    bracketing.subj_dist_step=shooting_get_subject_distance_bracket_value();
 }
  // other shoots
   bracketing.shoot_counter++;   
   is_odd=(bracketing.shoot_counter&1);
   if (((!is_odd) || (conf.bracket_type>0)) || (((is_odd) && (conf.bracket_type==0)) && (bracketing.subj_dist<=bracketing.dsubj_dist)))
   {
	   bracketing.dsubj_dist+=bracketing.subj_dist_step;
   }
   if ((((!is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==1)) && (bracketing.subj_dist>bracketing.dsubj_dist))
     {
     value=bracketing.subj_dist-bracketing.dsubj_dist;
     shooting_set_focus(value, SET_NOW);
     }
   else if ((((is_odd) && (conf.bracket_type==0)) || (conf.bracket_type==2)) || (((!is_odd) && (conf.bracket_type==0)) && (bracketing.subj_dist<=bracketing.dsubj_dist)))
     {
     value=bracketing.subj_dist+bracketing.dsubj_dist;
     shooting_set_focus(value, SET_NOW);
    }
}


void shooting_bracketing(void){
  
  short drive_mode=shooting_get_drive_mode();
  if (shooting_get_drive_mode()!=0)  {
     int m=mode_get()&MODE_SHOOTING_MASK;
     if (m!=MODE_STITCH) {
       if (state_shooting_progress != SHOOTING_PROGRESS_PROCESSING) { 
           bracketing.shoot_counter=0;
           bracketing.av96=0;
           bracketing.dav96=0;
           bracketing.tv96=0;
           bracketing.dtv96=0;
           bracketing.sv96=0;
           bracketing.dsv96=0;
           bracketing.iso=0;
           bracketing.diso=0;
           bracketing.subj_dist=0;
           bracketing.dsubj_dist=0;
           bracketing.type=0;
       }
           if (conf.tv_bracket_value && !(conf.override_disable==1 && conf.override_disable_all))  shooting_tv_bracketing(); 
    	      else if (conf.av_bracket_value && !(conf.override_disable==1 && conf.override_disable_all)) shooting_av_bracketing(); 
    	      else if ((conf.iso_bracket_value && !(conf.override_disable==1 && conf.override_disable_all)) && (conf.iso_bracket_koef)) {
			  shooting_iso_bracketing();
   	       }
    	      else if ((conf.subj_dist_bracket_value && !(conf.override_disable==1 && conf.override_disable_all)) && (conf.subj_dist_bracket_koef)) shooting_subject_distance_bracketing();   	      else if ((conf.subj_dist_bracket_value) && (conf.subj_dist_bracket_koef)) shooting_subject_distance_bracketing();
      }
   }
}

#if CAM_REAR_CURTAIN
  void shooting_set_flash_sync_curtain(int curtain){
   _SetPropertyCase(PROPCASE_FLASH_SYNC_CURTAIN, &curtain, sizeof(curtain));
  }
#endif

// forces manual flash. if set, flash will ALWAYS be triggered (manual)
	void shooting_set_flash_video_override(int flash, int power){
		int mode = 1;
		if ((conf.flash_manual_override && conf.flash_video_override && (movie_status > 1)) || (conf.flash_manual_override && !conf.flash_video_override)) {
						_SetPropertyCase(PROPCASE_FLASH_ADJUST_MODE, &mode, sizeof(mode));
						_SetPropertyCase(PROPCASE_FLASH_FIRE, &flash, sizeof(flash));
						_SetPropertyCase(PROPCASE_FLASH_MANUAL_OUTPUT, &power, sizeof(power));
					}
  }

// TODO sd990 hack for overrides
// caller must save regs
int captseq_hack_override_active() {
 if (state_kbd_script_run)
 	if ( photo_param_put_off.tv96 || photo_param_put_off.sv96 )
		return 1;
 if(conf.override_disable==1)
 	return 0;
 if(conf.iso_override_value && conf.iso_override_koef)
 	return 1;
 if((conf.tv_enum_type || conf.tv_override_value) && conf.tv_override_koef)
 	return 1;
 return 0;
}

void __attribute__((naked,noinline)) shooting_expo_param_override(void){
 asm volatile("STMFD   SP!, {R0-R12,LR}\n");

 //if (conf.tv_override) shooting_set_tv96_direct(-384-32*conf.tv_override);
 //short drive_mode=shooting_get_drive_mode();
/*if(drive_mode!=last_drive_mode)
 {
  if (last_drive_mode==0) shoot_counter=0;
  last_drive_mode=drive_mode;
 }*/
 //int m=mode_get()&MODE_SHOOTING_MASK;
 if ((state_kbd_script_run) && (photo_param_put_off.tv96)) {
  shooting_set_tv96_direct(photo_param_put_off.tv96, SET_NOW);	
  photo_param_put_off.tv96=0;
 }
   else if (((conf.tv_enum_type) || (conf.tv_override_value)) && (conf.tv_override_koef) && !(conf.override_disable==1))
   { 
   if (conf.tv_enum_type) 
     shooting_set_tv96_direct(32*(conf.tv_override_value-(tv_override_zero_shift)),SET_NOW);
   else   
    shooting_set_tv96_direct(shooting_get_tv96_from_shutter_speed(shooting_get_shutter_speed_override_value()), SET_NOW); 
   }
 if ((state_kbd_script_run) && (photo_param_put_off.sv96)) {
  shooting_set_sv96(photo_param_put_off.sv96, SET_NOW);
  photo_param_put_off.sv96=0; 
  }
else if ((conf.iso_override_value) && (conf.iso_override_koef) && !(conf.override_disable==1))
  shooting_set_iso_real(shooting_get_iso_override_value(), SET_NOW);
 else if (conf.autoiso_enable && shooting_get_flash_mode()/*NOT FOR FLASH AUTO MODE*/ && !(conf.override_disable==1 && conf.override_disable_all))
  shooting_set_autoiso(shooting_get_iso_mode());
 if ((state_kbd_script_run) && (photo_param_put_off.av96)) {
  shooting_set_av96_direct(photo_param_put_off.av96, SET_NOW);
  photo_param_put_off.av96=0;
  }
 else if (conf.av_override_value && !(conf.override_disable==1))
 shooting_set_av96_direct(shooting_get_av96_override_value(), SET_NOW);
 if ((state_kbd_script_run) && (photo_param_put_off.subj_dist)) {
  shooting_set_focus(photo_param_put_off.subj_dist, SET_NOW);
  photo_param_put_off.subj_dist=0;  
  }
  else if ((conf.subj_dist_override_value) && (conf.subj_dist_override_koef) && !(conf.override_disable==1))
   shooting_set_focus(shooting_get_subject_distance_override_value(), SET_NOW);
#if CAM_HAS_ND_FILTER
 if ((state_kbd_script_run) && (photo_param_put_off.nd_filter)) {
   shooting_set_nd_filter_state(photo_param_put_off.nd_filter, SET_NOW);
   photo_param_put_off.nd_filter=0;  
  }
 else if (conf.nd_filter_state && !(conf.override_disable==1)) 
   shooting_set_nd_filter_state(conf.nd_filter_state, SET_NOW);
#endif  

#if CAM_REAR_CURTAIN
  shooting_set_flash_sync_curtain(conf.flash_sync_curtain);
#endif


  shooting_set_flash_video_override(conf.flash_manual_override,conf.flash_video_override_power);
#if CAM_QUALITY_OVERRIDE
 // this doesn't really need to be set in the override hook. 
 // should only need to be set once if the users doesn't change back, but doing it here ensures it is set
 shooting_set_image_quality(conf.fast_image_quality);
#endif
 asm volatile("LDMFD   SP!, {R0-R12,PC}\n");
}

void unlock_optical_zoom(void){

#if CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
 if (conf.unlock_optical_zoom_for_video) _UnsetZoomForMovie();
#endif

#if CAM_EV_IN_VIDEO
 set_ev_video_avail(0);
#endif

}


#if CAM_EV_IN_VIDEO

int ev_video_avail;
int ev_video;
int save_tv_video;
int tv_min_video;

int get_ev_video_avail(void){
 return ev_video_avail;
}

void set_ev_video_avail(int x){
 if (ev_video_avail==x) return;
 ev_video_avail=x;
 if (x) {
  ev_video=0;
  _ExpCtrlTool_StopContiAE(0,0);
  _GetPropertyCase(PROPCASE_TV,&save_tv_video,2);
  if ((mode_get()&MODE_SHOOTING_MASK)==MODE_VIDEO_SPEED) tv_min_video=577;  // 1/60
   else tv_min_video=480; //1/30
 }
 else _ExpCtrlTool_StartContiAE(0,0);
}

int get_ev_video(void){
 return ev_video;
}

void set_ev_video(int x){
 short ev, tv;
 if ((x<-4)||(x>4)) return;
 ev=48*x;
 tv=save_tv_video-ev;
 if (tv>=tv_min_video) {
  ev_video=x;
  _SetAE_ShutterSpeed(&tv);
 }
}

#endif
