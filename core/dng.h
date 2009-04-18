//DNG related stuff

#ifndef DNG_H
#define DNG_H

struct dir_entry{unsigned short tag; unsigned short type; unsigned int count; unsigned int offset;};

#define T_BYTE 1
#define T_ASCII 2
#define T_SHORT 3
#define T_LONG 4
#define T_RATIONAL 5
#define T_SBYTE 6
#define T_UNDEFINED 7
#define T_SSHORT 8
#define T_SLONG 9
#define T_SRATIONAL 10
#define T_FLOAT 11
#define T_DOUBLE 12

#define CAM_DEFAULT_CROP_ORIGIN_W ((CAM_ACTIVE_AREA_X2-CAM_ACTIVE_AREA_X1-CAM_JPEG_WIDTH )/2)
#define CAM_DEFAULT_CROP_ORIGIN_H ((CAM_ACTIVE_AREA_Y2-CAM_ACTIVE_AREA_Y1-CAM_JPEG_HEIGHT)/2)

//thumbnail
#define DNG_TH_WIDTH 128
#define DNG_TH_HEIGHT 96
// higly recommended that DNG_TH_WIDTH*DNG_TH_HEIGHT would be divisible by 512

struct t_data_for_exif{
 unsigned long time;
 short iso;
 short tv;
 short av;
 short exp_bias;
 int exp_program;
 short max_av;
 int focal_length;
 int effective_focal_length;
 short orientation;
 short flash_mode;
 short flash_fired;
 short metering_mode;
};

void create_dng_header(struct t_data_for_exif* exif_data);
void free_dng_header(void);
char* get_dng_header(void);
int get_dng_header_size(void);

struct t_data_for_exif* capture_data_for_exif(void);

char *get_date_for_exif(unsigned long time);
unsigned int* get_av_for_exif(short av);
int* get_tv_for_exif(short tv);
unsigned int* get_max_av_for_exif(short max_av);
int* get_exp_bias_for_exif(short exp_bias);
unsigned short get_exp_program_for_exif(int exp_program);
unsigned int* get_focal_length_for_exif(int focal_length);
unsigned short get_orientation_for_exif(short orientation);
unsigned short get_flash_mode_for_exif(short mode, short fired);
unsigned short get_metering_mode_for_exif(short metering_mode);
int* get_shutter_speed_for_exif(short tv);
int* get_aperture_for_exif(short av);

void convert_dng_to_chdk_raw(char* fn);

#endif
