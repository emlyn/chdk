#include "camera.h"

#if DNG_SUPPORT

#include "stdlib.h"
#include "string.h"
#include "platform.h"
#include "math.h"
#include "dng.h"

const int cam_DefaultCropSize[]={CAM_JPEG_WIDTH, CAM_JPEG_HEIGHT};    // jpeg size
const int cam_ActiveArea[]={CAM_ACTIVE_AREA_Y1, CAM_ACTIVE_AREA_X1, CAM_ACTIVE_AREA_Y2, CAM_ACTIVE_AREA_X2};
const int cam_DefaultCropOrigin[]={CAM_DEFAULT_CROP_ORIGIN_W,CAM_DEFAULT_CROP_ORIGIN_H};
const int cam_BaselineExposure[]={-1,2};
const int cam_BaselineNoise[]={1,1};
const int cam_BaselineSharpness[]={4,3};
const int cam_LinearResponseLimit[]={1,1};
const int cam_AnalogBalance[]={1,1,1,1,1,1};
const int cam_ColorMatrix1[9*2]={CAM_COLORMATRIX1};
const char cam_name[32];
const short cam_PreviewBitsPerSample[]={8,8,8};
const char cam_chdk_ver[]=HDK_VERSION" ver. "BUILD_NUMBER;
const int cam_Resolution[]={180,1};

// warning: according to TIFF format specification, elements must be sorted by tag value in ascending order!

struct dir_entry IFD0[]={
 {0xFE,   T_LONG,      1,  1},       // NewSubFileType: Preview Image
 {0x100,  T_LONG,      1,  DNG_TH_WIDTH},   // ImageWidth
 {0x101,  T_LONG,      1,  DNG_TH_HEIGHT},   // ImageLength
 {0x102,  T_SHORT,     3,  (int)cam_PreviewBitsPerSample},   // BitsPerSample: 8,8,8
 {0x103,  T_SHORT,     1,  1},   // Compression: Uncompressed
 {0x106,  T_SHORT,     1,  2}, //PhotometricInterpretation: RGB
 {0x10E,  T_ASCII,     1,  0}, // ImageDescription
 {0x10F,  T_ASCII,     sizeof(CAM_MAKE),  (int)CAM_MAKE}, // Make
 {0x110,  T_ASCII,     32, (int)cam_name}, //Model: Filled at header generation.
 {0x111,  T_LONG,      1,  0}, //StripOffsets: Offset
 {0x112,  T_SHORT,     1,  1}, //Orientation: 1 - 0th row is top, 0th column is left
 {0x115,  T_SHORT,     1,  3}, // SamplesPerPixel: 3
 {0x116,  T_SHORT,     1,  DNG_TH_HEIGHT}, //RowsPerStrip
 {0x117,  T_LONG,      1,  DNG_TH_WIDTH*DNG_TH_HEIGHT*3}, // StripByteCounts = preview size
 {0x11C,  T_SHORT,     1,  1}, // PlanarConfiguration: 1
 {0x131,  T_ASCII,     sizeof(cam_chdk_ver),  (int)cam_chdk_ver}, //Software
 {0x132,  T_ASCII,     20, 0}, // DateTime
 {0x14A,  T_LONG,      1,  0}, //SubIFDs offset
 {0x8298, T_ASCII,     1,  0}, // Copyright
 {0x8769, T_LONG,      1,  0}, //EXIF_IFD offset
 {0x9216, T_BYTE,      4,  0x00000001},  // TIFF/EPStandardID: 1.0.0.0
 {0xC612, T_BYTE,      4,  0x00000101}, //DNGVersion: 1.1.0.0
 {0xC614, T_ASCII,     32, (int)cam_name}, //UniqueCameraModel. Filled at header generation.
 {0xC621, T_SRATIONAL, 9,  (int)cam_ColorMatrix1},
 {0xC627, T_RATIONAL,  3,  (int)cam_AnalogBalance},
 {0xC62A, T_SRATIONAL, 1,  (int)cam_BaselineExposure},
 {0xC62B, T_RATIONAL,  1,  (int)cam_BaselineNoise},
 {0xC62C, T_RATIONAL,  1,  (int)cam_BaselineSharpness},
 {0xC62E, T_RATIONAL,  1,  (int)cam_LinearResponseLimit},
 {0xC65A, T_SHORT,     1,  cam_CalibrationIlluminant1}, 
 {0}
};

                                                                                      
struct dir_entry IFD1[]={
 {0xFE,   T_LONG,      1,  0},       // NewSubFileType: Main Image
 {0x100,  T_LONG,      1,  CAM_RAW_ROWPIX},   // ImageWidth
 {0x101,  T_LONG,      1,  CAM_RAW_ROWS},   // ImageLength
 {0x102,  T_SHORT,     1,  CAM_SENSOR_BITS_PER_PIXEL},   // BitsPerSample
 {0x103,  T_SHORT,     1,  1},   // Compression: Uncompressed
 {0x106,  T_SHORT,     1,  0x8023}, //PhotometricInterpretation: CFA
 {0x111,  T_LONG,      1,  0}, //StripOffsets: Offset
 {0x115,  T_SHORT,     1,  1}, // SamplesPerPixel: 1
 {0x116,  T_SHORT,     1,  CAM_RAW_ROWS}, //RowsPerStrip
 {0x117,  T_LONG,      1,  CAM_RAW_ROWPIX*CAM_RAW_ROWS*CAM_SENSOR_BITS_PER_PIXEL/8}, // StripByteCounts = CHDK RAW size
 {0x11A,  T_RATIONAL,  1,  (int)cam_Resolution}, // XResolution
 {0x11B,  T_RATIONAL,  1,  (int)cam_Resolution}, // YResolution
 {0x11C,  T_SHORT,     1,  1}, // PlanarConfiguration: 1
 {0x128,  T_SHORT,     1,  2}, // ResolutionUnit: inch
 {0x828D, T_SHORT,     2,  0x00020002}, // CFARepeatPatternDim: Rows = 2, Cols = 2
 {0x828E, T_BYTE,      4,  cam_CFAPattern},
 {0xC61A, T_LONG,      1,  CAM_BLACK_LEVEL}, // BlackLevel
 {0xC61D, T_LONG,      1,  CAM_WHITE_LEVEL}, // WhiteLevel
 {0xC61F, T_LONG,      2,  (int)cam_DefaultCropOrigin},
 {0xC620, T_LONG,      2,  (int)cam_DefaultCropSize},
 {0xC68D, T_LONG,      4,  (int)cam_ActiveArea},
 {0}
};


struct dir_entry EXIF_IFD[]={
 {0x829A, T_RATIONAL,  1,  0}, //ExposureTime
 {0x829D, T_RATIONAL,  1,  0}, //FNumber
 {0x8822, T_SHORT,     1,  0}, //ExposureProgram
 {0x8827, T_SHORT,     1,  0}, //ISOSpeedRatings
 {0x9000, T_UNDEFINED, 4,  0x31323230}, // ExifVersion: 2.21
 {0x9003, T_ASCII,     20, 0}, // DateTimeOriginal
 {0x9201, T_SRATIONAL, 1,  0}, // ShutterSpeedValue
 {0x9202, T_RATIONAL,  1,  0}, // ApertureValue
 {0x9204, T_SRATIONAL, 1,  0}, // ExposureBias
 {0x9205, T_RATIONAL,  1,  0}, //MaxApertureValue
 {0x9207, T_SHORT,     1,  0}, // Metering mode
 {0x9209, T_SHORT,     1,  0}, // Flash mode
 {0x920A, T_RATIONAL,  1,  0}, //FocalLength
 {0xA405, T_SHORT,     1,  0}, //FocalLengthIn35mmFilm
 {0}
};


int get_type_size(int type){
 switch(type){
  case T_BYTE:      return 1;
  case T_ASCII:     return 1; 
  case T_SHORT:     return 2;
  case T_LONG:      return 4;
  case T_RATIONAL:  return 8;
  case T_SBYTE:     return 1;
  case T_UNDEFINED: return 1;
  case T_SSHORT:    return 2;
  case T_SLONG:     return 4;
  case T_SRATIONAL: return 8;
  case T_FLOAT:     return 4;
  case T_DOUBLE:    return 8;
  default: return 0;
 }
}

struct {struct dir_entry* entry; int count;} IFD_LIST[]={{IFD0,0}, {IFD1,0}, {EXIF_IFD,0}};

#define IFDs (sizeof(IFD_LIST)/sizeof(IFD_LIST[0]))

#define TIFF_HDR_SIZE (8)

char* tmp_buf;
int tmp_buf_size;
int tmp_buf_offset;
void add_to_buf(void* var, int size){
 memcpy(tmp_buf+tmp_buf_offset,var,size);
 tmp_buf_offset+=size;
}
 
void create_dng_header(struct t_data_for_exif* exif_data){
 int var;
 int i,j;
 int extra_offset;
 int raw_offset;

 // filling EXIF fields

 for (j=0;j<IFDs;j++) {
  for(i=0; IFD_LIST[j].entry[i].tag; i++) {
    switch (IFD_LIST[j].entry[i].tag) {
     case 0x132 :
     case 0x9003: IFD_LIST[j].entry[i].offset=(int)get_date_for_exif(exif_data->time); break; //DateTimeOriginal
     case 0x8827: IFD_LIST[j].entry[i].offset=exif_data->iso; break;//ISOSpeedRatings
     case 0x829D: IFD_LIST[j].entry[i].offset=(int)get_av_for_exif(exif_data->av); break; //FNumber
     case 0x829A: IFD_LIST[j].entry[i].offset=(int)get_tv_for_exif(exif_data->tv); break; //ExposureTime
     case 0x9205: IFD_LIST[j].entry[i].offset=(int)get_max_av_for_exif(exif_data->max_av); break; //MaxApertureValue
     case 0x9204: IFD_LIST[j].entry[i].offset=(int)get_exp_bias_for_exif(exif_data->exp_bias); break; //ExposureBias
     case 0x8822: IFD_LIST[j].entry[i].offset=get_exp_program_for_exif(exif_data->exp_program); break;//ExposureProgram
     case 0x920A: IFD_LIST[j].entry[i].offset=(int)get_focal_length_for_exif(exif_data->focal_length); break; //FocalLength
     case 0xA405: IFD_LIST[j].entry[i].offset=exif_data->effective_focal_length/1000; break; ////FocalLengthIn35mmFilm
     case 0x0112: IFD_LIST[j].entry[i].offset=get_orientation_for_exif(exif_data->orientation); break; //Orientation
     case 0x9209: IFD_LIST[j].entry[i].offset=get_flash_mode_for_exif(exif_data->flash_mode, exif_data->flash_fired); break; //Flash mode
     case 0x9207: IFD_LIST[j].entry[i].offset=get_metering_mode_for_exif(exif_data->metering_mode); break; // Metering mode
     case 0x9201: IFD_LIST[j].entry[i].offset=(int)get_shutter_speed_for_exif(exif_data->tv); break; // ShutterSpeedValue
     case 0x9202: IFD_LIST[j].entry[i].offset=(int)get_aperture_for_exif(exif_data->av); break; // ApertureValue
    }
  }
 }
  
 // calculating offset of RAW data and count of directories for each IFD

 raw_offset=TIFF_HDR_SIZE;

 for (j=0;j<IFDs;j++) {
  IFD_LIST[j].count=0;
  raw_offset+=6; // IFD header+footer
  for(i=0; IFD_LIST[j].entry[i].tag; i++) {
   int size_ext;
   IFD_LIST[j].count++;
   raw_offset+=12; // IFD directory size
   size_ext=get_type_size(IFD_LIST[j].entry[i].type)*IFD_LIST[j].entry[i].count;
   if (size_ext>4) raw_offset+=size_ext+(size_ext&1);
  }
 }

 // creating buffer for writing data
 raw_offset=(raw_offset/512+1)*512; // exlusively for CHDK fast file writing
 tmp_buf_size=raw_offset;
 tmp_buf=umalloc(raw_offset);
 tmp_buf_offset=0;
 if (!tmp_buf) return;

 //  writing  offsets for EXIF IFD and RAW data and calculating offset for extra data

 extra_offset=TIFF_HDR_SIZE;

 for (j=0;j<IFDs;j++) {
  extra_offset+=6+IFD_LIST[j].count*12; // IFD header+footer
  for(i=0; IFD_LIST[j].entry[i].tag; i++) {
   if (IFD_LIST[j].entry[i].tag==0x8769) IFD_LIST[j].entry[i].offset=TIFF_HDR_SIZE+(IFD_LIST[0].count+IFD_LIST[1].count)*12+6+6;  // EXIF IFD offset
   if (IFD_LIST[j].entry[i].tag==0x14A)  IFD_LIST[j].entry[i].offset=TIFF_HDR_SIZE+IFD_LIST[0].count*12+6; // SubIFDs offset
   if (IFD_LIST[j].entry[i].tag==0x111)  {
    if (j==1) IFD_LIST[j].entry[i].offset=raw_offset+DNG_TH_WIDTH*DNG_TH_HEIGHT*3;  //StripOffsets for main image
    if (j==0) IFD_LIST[j].entry[i].offset=raw_offset;  //StripOffsets for thumbnail
   }
  }
 }

 // TIFF file header

 var=0x4949; // little endian
 add_to_buf(&var, sizeof(short));
 var=42; //An arbitrary but carefully chosen number that further identifies the file as a TIFF file.
 add_to_buf(&var, sizeof(short));
 var=0x8; // offset of first IFD
 add_to_buf(&var, sizeof(int));


 // writing IFDs

 for (j=0;j<IFDs;j++) {
  int size_ext;
  var=IFD_LIST[j].count;
  add_to_buf(&var, sizeof(short));
  for(i=0; IFD_LIST[j].entry[i].tag; i++) {
   add_to_buf(&IFD_LIST[j].entry[i].tag, sizeof(short));
   add_to_buf(&IFD_LIST[j].entry[i].type, sizeof(short));
   add_to_buf(&IFD_LIST[j].entry[i].count, sizeof(int));
   size_ext=get_type_size(IFD_LIST[j].entry[i].type)*IFD_LIST[j].entry[i].count;
   if (size_ext<=4) add_to_buf(&IFD_LIST[j].entry[i].offset, sizeof(int));
   else {
    add_to_buf(&extra_offset, sizeof(int));
    extra_offset+=size_ext+(size_ext&1);    
   }
  }
 var=0; 
 add_to_buf(&var, sizeof(int));
 }


 // writing extra data

 for (j=0;j<IFDs;j++) {
  int size_ext;
  char zero=0;
  for(i=0; IFD_LIST[j].entry[i].tag; i++) {
   size_ext=get_type_size(IFD_LIST[j].entry[i].type)*IFD_LIST[j].entry[i].count;
   if (size_ext>4){
    add_to_buf((void*)IFD_LIST[j].entry[i].offset, size_ext);
    if (size_ext&1) add_to_buf(&zero, 1);
   }
  }
 }


 // writing zeros to tail of dng header (just for fun)
 for (i=tmp_buf_offset; i<tmp_buf_size; i++) tmp_buf[i]=0;

}

void free_dng_header(void){
 ufree(tmp_buf);
 tmp_buf=NULL;
}

char* get_dng_header(void){
 return tmp_buf;
}

int get_dng_header_size(void){
 return tmp_buf_size;
}

char *get_date_for_exif(unsigned long time){
 static char buf[20];
 struct tm *ttm;
 ttm = localtime(&time);
 sprintf(buf, "%04d:%02d:%02d %02d:%02d:%02d", ttm->tm_year+1900, ttm->tm_mon+1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
 return buf;
}

unsigned int* get_av_for_exif(short av){
 static unsigned int fnumber[2]={0,10};
 fnumber[0]=10*pow(2,av/192.0);
 return fnumber;
}

int* get_tv_for_exif(short tv){
 static int exp_time[2]={0,1000000};
 exp_time[0]=1000000*pow(2,-tv/96.0);
 return exp_time;
}

unsigned int* get_max_av_for_exif(short max_av){
 static unsigned int mav[2]={0,96};
 mav[0]=max_av;
 return mav;
}

int* get_exp_bias_for_exif(short exp_bias){
 static int bias[2]={0,96};
 bias[0]=exp_bias;
 return bias;
}

int* get_shutter_speed_for_exif(short tv){
 static int speed[2]={0,96};
 speed[0]=tv;
 return speed;
}

int* get_aperture_for_exif(short av){
 static int aperture[2]={0,96};
 aperture[0]=av;
 return aperture;
}


unsigned short get_exp_program_for_exif(int exp_program){
 switch(exp_program){
  case MODE_M: return 1;
  case MODE_P: return 2;
  case MODE_AV: return 3;
  case MODE_TV: return 4;
  default: return 0;
 }
}

unsigned int* get_focal_length_for_exif(int focal_length){
 static int fl[2]={0,1000};
 fl[0]=focal_length;
 return fl;
}

unsigned short get_orientation_for_exif(short orientation){
 switch(orientation){
  case 90:  return 6;
  case 270: return 8;
  default: return 1;
 }
}

unsigned short get_flash_mode_for_exif(short mode, short fired){
 fired&=1;
 switch(mode){
  case 0: return (3<<3)|fired; // auto
  case 1: return (1<<3)|fired; // on
  case 2: return (2<<3)|fired; // off
  default: return fired;
 };
}

unsigned short get_metering_mode_for_exif(short metering_mode){
 switch (metering_mode){
  case 0: return 5; // Evaluative
  case 1: return 3; // Spot
  case 2: return 2; // CenterWeightedAverage
  default: return 255; // other
 }
}

struct t_data_for_exif* capture_data_for_exif(void){
 static struct t_data_for_exif data;
 extern volatile long shutter_open_time; // defined in platform/generic/capt_seq.c
 data.iso=shooting_get_iso_market();
 get_property_case(PROPCASE_TV, &data.tv, sizeof(data.tv));
 if (shutter_open_time) { data.time=shutter_open_time+pow(2,-data.tv/96.0); shutter_open_time=0;} // shutter closing time
 else  data.time=time(NULL);
 get_property_case(PROPCASE_AV, &data.av, sizeof(data.av));
 get_property_case(PROPCASE_MIN_AV, &data.max_av, sizeof(data.max_av));
 get_property_case(PROPCASE_EV_CORRECTION_2, &data.exp_bias, sizeof(data.exp_bias));
 data.exp_program=mode_get() & MODE_SHOOTING_MASK;
 data.focal_length=get_focal_length(shooting_get_zoom());
 data.effective_focal_length=get_effective_focal_length(shooting_get_zoom());
 get_property_case(PROPCASE_ORIENTATION_SENSOR, &data.orientation, sizeof(data.orientation));
 get_parameter_data(PARAM_CAMERA_NAME, &cam_name, sizeof(cam_name));
 get_property_case(PROPCASE_FLASH_MODE, &data.flash_mode, sizeof(data.flash_mode));
 get_property_case(PROPCASE_FLASH_FIRE, &data.flash_fired, sizeof(data.flash_fired));
 get_property_case(PROPCASE_METERING_MODE, &data.metering_mode, sizeof(data.metering_mode));
 return &data;
}

#endif //DNG_SUPPORT
