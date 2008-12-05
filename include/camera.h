#ifndef CAMERA_H
#define CAMERA_H

//==========================================================
// Camera-dependent settings
//==========================================================

//----------------------------------------------------------
// Default values
//----------------------------------------------------------
    #undef  CAM_RAW_ROWPIX                  // Number of pixels in RAW row
    #undef  CAM_RAW_ROWS                    // Number of rows in RAW
    
    #undef  CAM_DRYOS                       // Camera is DryOS-based
    #undef  CAM_PROPSET                     // Camera's properties group (the generation)
    
    #undef  CAM_SWIVEL_SCREEN               // Camera has rotated LCD screen
    #define CAM_USE_ZOOM_FOR_MF         1   // Zoom lever can be used for manual focus adjustments
    #undef  CAM_ADJUSTABLE_ALT_BUTTON       // ALT-button can be set from menu
    #define CAM_REMOTE                  1   // Camera supports USB-remote
    #define CAM_SYNCH                   1   // Camera supports SDM precision synch
    #undef  CAM_MULTIPART                   // Camera supports SD-card multipartitioning 
    #define CAM_HAS_ZOOM_LEVER          1   // Camera has dedicated zoom buttons
    #undef  CAM_DRAW_EXPOSITION             // Output expo-pair on screen (for cameras which (sometimes) don't do that)
    #define CAM_HAS_ERASE_BUTTON        1   // Camera has dedicated erase button
    #define CAM_HAS_IRIS_DIAPHRAGM      1   // Camera has real diaphragm mechanism
    #undef  CAM_HAS_ND_FILTER               // Camera has build-in ND filter
    #define CAM_CAN_SD_OVER_NOT_IN_MF   1   // Camera allows subject distance (focus) override when not in manual focus mode
    #define CAM_CAN_SD_OVERRIDE         1   // Camera allows to do subject distance override
    #define CAM_HAS_MANUAL_FOCUS        1   // Camera has manual focus mode
    #define CAM_HAS_USER_TV_MODES       1   // Camera has tv-priority or manual modes with ability to set tv value
    #undef  CAM_SHOW_OSD_IN_SHOOT_MENU      // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode  
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1 // Camera can unlock optical zoom in video (if it is locked)
    #undef  CAM_FEATURE_FEATHER             // Cameras with "feather" or touch wheel.
    #define CAM_HAS_IS                  1   // Camera has image stabilizer
	#undef  CAM_HAS_JOGDIAL                 // Camera has a "jog dial"

    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU 1   // In CHDK for this camera realized adjustable video compression
    #undef  CAM_CAN_MUTE_MICROPHONE         // Camera has function to mute microphone

    #define CAM_EMUL_KEYPRESS_DELAY     40  // Delay to interpret <alt>-button press as longpress
    #define CAM_EMUL_KEYPRESS_DURATION  5   // Length of keypress emulation

    #undef  CAM_AF_SCAN_DURING_VIDEO_RECORD // CHDK can make single AF scan during video record 
    #undef  CAM_HAS_VIDEO_BUTTON            // Camera can take stills in video mode, and vice versa
    #undef  CAM_EV_IN_VIDEO                 // CHDK can change exposure in video mode
    #define CAM_VIDEO_CONTROL      1   // pause / unpause video recordings

    #define ZOOM_OVERRIDE               0   // Shall zoom-override be used? default 0 becoz not implemented right now
    #undef  DNG_SUPPORT                 
    #undef  CAM_REAR_CURTAIN                // Camera do not have front/rear curtain flash sync in menu
    #undef  CAM_BRACKETING                // Cameras that have bracketing (focus & ev) in original firmware already, most likely s- & g-series (propcase for digic III not found yet!)

//----------------------------------------------------------
// Overridden values for each camera
//----------------------------------------------------------

//==========================================================
// G-series
//==========================================================
#if   defined (CAMERA_g7)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3736   // for 10 MP
    #define CAM_RAW_ROWS                2772   // for 10 MP
    
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_MULTIPART               1
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_IS
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
	#define CAM_HAS_JOGDIAL             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      510370,  1000000, -68998,  1000000, -86859,  1000000, \
      -279980, 1000000, 766686,  1000000,  67944,  1000000, \
      -14382,  1000000, 113688,  1000000, 239853,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3108
    #define CAM_ACTIVE_AREA_Y2 2332
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #define CAM_BRACKETING              1    
 //----------------------------------------------------------
#elif defined (CAMERA_g9)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4104   // for 12 MP
    #define CAM_RAW_ROWS                3048   // for 12 MP
//  #define CAM_MULTIPART               1
    #define CAM_HAS_ND_FILTER           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL             1
    #define CAM_EV_IN_VIDEO             1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
//	#define CAM_CONSOLE_LOG_ENABLED     1
//  #define CAM_BRACKETING              1  //propcase still missing for dryos    
//==========================================================
// A-series
//==========================================================
#elif defined (CAMERA_a450)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              2664   // for 5 MP 1/3" sensor size
    #define CAM_RAW_ROWS                1968   // for 5 MP 1/3" sensor size

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ZOOM_LEVER
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      652279,  1000000,-199279, 1000000, -101833, 1000000, \
     -159819,  1000000, 619308, 1000000,   78172, 1000000, \
      -58827,  1000000, 150963, 1000000,  264216, 1000000 
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 6
    #define CAM_ACTIVE_AREA_X2 2618
    #define CAM_ACTIVE_AREA_Y2 1962
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

    
//----------------------------------------------------------
#elif defined (CAMERA_a460)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              2664   // for 5 MP 1/3" sensor size
    #define CAM_RAW_ROWS                1968   // for 5 MP 1/3" sensor size

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ZOOM_LEVER
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      649324,  1000000,-233893, 1000000, -88521, 1000000,  \
     -158955,  1000000, 593407, 1000000,  69775, 1000000,  \
      -44551,  1000000, 136891, 1000000, 254362, 1000000   
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 6
    #define CAM_ACTIVE_AREA_X2 2618
    #define CAM_ACTIVE_AREA_Y2 1962
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a530)
    #define CAM_PROPSET                 1

//  2672x1968 image - like most other 5m sensors
    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
//  2672x1992 image - eventually probably real sensor size
//  #define CAM_RAW_ROWPIX              2672   // for 5 MP
//  #define CAM_RAW_ROWS                1992   // for 5 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_HAS_ERASE_BUTTON	1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #define CAM_HAS_MANUAL_FOCUS	1
    #define CAM_DRAW_EXPOSITION		1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU	1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      725264,  1000000,-240542, 1000000, -122310, 1000000, \
     -210248,  1000000, 656077, 1000000,  52390,  1000000, \
      -11282,  1000000, 70400,  1000000,  300712, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 20
    #define CAM_ACTIVE_AREA_X2 2628
    #define CAM_ACTIVE_AREA_Y2 1968
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a540)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_HAS_ERASE_BUTTON	1
    #define CAM_HAS_IRIS_DIAPHRAGM	1
    #undef  CAM_HAS_ND_FILTER
    #define CAM_HAS_MANUAL_FOCUS	1
    #undef  CAM_DRAW_EXPOSITION
    #define CAM_SHOW_OSD_IN_SHOOT_MENU	1
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      687147,  1000000,-201964, 1000000, -125024, 1000000, \
     -148403,  1000000, 566810, 1000000,   45401, 1000000, \
     -9472,    1000000, 63186,  1000000,  208602, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2816
    #define CAM_JPEG_HEIGHT 2112
    #define CAM_ACTIVE_AREA_X1 44
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2884
    #define CAM_ACTIVE_AREA_Y2 2136
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a550)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      673251,  1000000,-200684, 1000000, -98680, 1000000,  \
     -163638,  1000000, 651247, 1000000,  74004, 1000000,  \
      14221,   1000000, 52979,  1000000, 265291, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 36
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 3148
    #define CAM_ACTIVE_AREA_Y2 2340
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    
//----------------------------------------------------------
#elif defined (CAMERA_a560)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      15265, 1, -6193, 1, -1558, 1,                        \
     -4125,  1, 12116, 1,  2010, 1,                        \
     -888,   1, 1639,  1,  5220, 1                         
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    
//----------------------------------------------------------
#elif defined (CAMERA_a570)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP
    #define CAM_MULTIPART               1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    #define CAM_REAR_CURTAIN            1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      528283,  1000000,-144259, 1000000, -85966, 1000000,  \
     -202789,  1000000, 736563, 1000000,  73008, 1000000,  \
     -27130,   1000000, 107702, 1000000, 264543, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a590)
#define CAM_PROPSET                 2
#define CAM_DRYOS                   1

#define CAM_RAW_ROWPIX              3336   // for new 8 MP
#define CAM_RAW_ROWS                2480   // for new 8 MP

#define CAM_USE_ZOOM_FOR_MF         1      // Zoom lever can be used for manual focus adjustments

// cannot mute during video-zoom through CHDK, it can mute in general firmware settings (non CHDK)
#undef  CAM_CAN_MUTE_MICROPHONE            // Camera has no function to mute microphone

#define CAM_HAS_IRIS_DIAPHRAGM      1      // it has a 6 blade iris diaphragm
#undef  CAM_HAS_ND_FILTER

#define CAM_HAS_MANUAL_FOCUS        1      // Camera has manual focus mode

#define CAM_AF_SCAN_DURING_VIDEO_RECORD 1   // Camera adapts focus in video recording
//#define CAM_EV_IN_VIDEO             1      // not working on 101b!!!
#define DNG_SUPPORT                 1
// pattern
// It has indeed Green Blue Red Green, so that makes 01 00 02 01
#define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
// color 
#define CAM_COLORMATRIX1                               \
0.647380, 1000000, -0.169846, 1000000, -0.115337, 1000000, \
-0.011566, 1000000, 0.451223, 1000000, 0.013279, 1000000, \
0.062541, 1000000, 0.054140, 1000000, 0.161148, 1000000

#define cam_CalibrationIlluminant1 1 // Daylight
// cropping
#define CAM_JPEG_WIDTH  3264
#define CAM_JPEG_HEIGHT 2448
#define CAM_ACTIVE_AREA_X1 10
#define CAM_ACTIVE_AREA_Y1 8
#define CAM_ACTIVE_AREA_X2 3302
#define CAM_ACTIVE_AREA_Y2 2474

// camera name
#define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData


//----------------------------------------------------------
#elif defined (CAMERA_a610)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF 
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      15887,  10000, -6524, 10000, -1622, 10000,           \
     -5467,   10000, 13449, 10000,  2209, 10000,           \
     -1325,   10000, 1859,  10000,  5172, 10000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 10
    #define CAM_ACTIVE_AREA_X2 2626
    #define CAM_ACTIVE_AREA_Y2 1966
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a620)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_HAS_IS    
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
     15265, 10000, -6193, 10000, -1558, 10000,             \
     -4125, 10000, 12116, 10000,  2010, 10000,             \
     -888,  10000,  1639, 10000,  5220, 10000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a630)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3344   // for 8 MP
    #define CAM_RAW_ROWS                2484   // for 8 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_MULTIPART               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      656080,  1000000,-226478, 1000000, -85884, 1000000,  \
     -194636,  1000000, 687905, 1000000,  37862, 1000000,  \
       22873,  1000000,  75523, 1000000, 265822, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3298
    #define CAM_ACTIVE_AREA_Y2 2476
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a640)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3736   // for 10 MP
    #define CAM_RAW_ROWS                2772   // for 10 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_MULTIPART               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      13124,  10000, -5329, 10000, -1390, 10000,           \
      -3602,  10000, 11658, 10000,  1944, 10000,           \
      -1612,  10000,  2863, 10000,  4885, 10000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3682
    #define CAM_ACTIVE_AREA_Y2 2764
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a650)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4104   // for 12 MP
    #define CAM_RAW_ROWS                3048   // for 12 MP
    
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_CAN_MUTE_MICROPHONE     1

    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      913762, 1000000, -261578, 1000000, -135582, 1000000, \
     -99049,  1000000, 1067089, 1000000,   61442, 1000000, \
      48717,  1000000, 96802,   1000000,  412056, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  4000
    #define CAM_JPEG_HEIGHT 3000
    #define CAM_ACTIVE_AREA_X1 52
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 4076
    #define CAM_ACTIVE_AREA_Y2 3030
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a700)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
     14062, 10000, -5199, 10000, -1446, 10000,             \
     -4712, 10000, 12470, 10000,  2243, 10000,             \
     -1286, 10000,  2028, 10000,  4836, 10000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  2816
    #define CAM_JPEG_HEIGHT 2112
    #define CAM_ACTIVE_AREA_X1 44
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2884
    #define CAM_ACTIVE_AREA_Y2 2136
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a710)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #define CAM_MULTIPART               1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                   \
     13349, 10000, -4141, 10000, -2128, 10000, \
     -4189, 10000, 13178, 10000,  1044, 10000, \
     -1037, 10000,  2326, 10000,  4720, 10000   
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_a720)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #undef  CAM_VIDEO_CONTROL
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                               \
      640019, 1000000, -220031, 1000000, -96241, 1000000,  \
     -77419,  1000000, 639766,  1000000,  44009, 1000000,  \
      17965,  1000000, 78396,   1000000, 231868, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 10
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3302
    #define CAM_ACTIVE_AREA_Y2 2474
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//==========================================================
// SD-Series (IXUS-Series)
//==========================================================
#elif defined (CAMERA_ixus40_sd300)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              (2376) //(2272+80) //for 4 MP guessed!!
    #define CAM_RAW_ROWS                (1704+24) // for 4 MP guessed!!

    #define CAM_USE_ZOOM_FOR_MF 1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #undef  CAM_HAS_IS
    #undef CAM_CONSOLE_LOG_ENABLED


/*   DNG support is blocked due to mismatch RAW size in this file and DNG4PS2 settings (2400x1720).

    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                 \
      652674,  1000000, -172074, 1000000, -107575,  1000000, \
      -139063, 1000000, 594517,  1000000,  60252,   1000000, \
      -9088,   1000000, 82013,   1000000,  238080,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2272
    #define CAM_JPEG_HEIGHT 1704
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 24
    #define CAM_ACTIVE_AREA_X2 2394
    #define CAM_ACTIVE_AREA_Y2 1708
    // camera name
    #define PARAM_CAMERA_NAME 2 // parameter number for GetParameterData

    */

//----------------------------------------------------------

#elif defined (CAMERA_ixus50_sd400)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP

    #undef  CAM_SYNCH  
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
	//#define CAM_CONSOLE_LOG_ENABLED     1
    #undef  CAM_VIDEO_CONTROL

//----------------------------------------------------------
#elif defined (CAMERA_ixus55_sd450)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      536034,  1000000, -173429, 1000000, -89823,  1000000, \
      -290416, 1000000, 735807,  1000000,  47894,  1000000, \
      -71455,  1000000, 114314,  1000000,  274533, 1000000          
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2628
    #define CAM_ACTIVE_AREA_Y2 1968
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_ixus60_sd600)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_SYNCH
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_DRAW_EXPOSITION		    1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_FEATURE_FEATHER         1

//    #define CAM_CONSOLE_LOG_ENABLED     1  //100a won't compile if this is defined ("undefined reference to `_iosDevFind'")
    #undef  CAM_HAS_IS
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      767398,  1000000, -227658, 1000000, -144213, 1000000, \
      -217466, 1000000, 669319,  1000000,  38180,  1000000, \
      -23152,  1000000, 77743,  1000000,   238669, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2816
    #define CAM_JPEG_HEIGHT 2112
    #define CAM_ACTIVE_AREA_X1 44
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2884
    #define CAM_ACTIVE_AREA_Y2 2136
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_ixus65_sd630)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_DRAW_EXPOSITION		    1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_FEATURE_FEATHER         1

    #define CAM_CONSOLE_LOG_ENABLED     1
    #undef  CAM_HAS_IS
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      783384,  1000000, -227078, 1000000, -127919, 1000000, \
      -181247, 1000000, 661743,  1000000,  58868,  1000000, \
       25727,  1000000, 43891,   1000000,  247655, 1000000          
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2816
    #define CAM_JPEG_HEIGHT 2112
    #define CAM_ACTIVE_AREA_X1 44
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2884
    #define CAM_ACTIVE_AREA_Y2 2136
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------

#elif defined (CAMERA_ixus75_sd750)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

/*
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    */
    
    #undef  CAM_SWIVEL_SCREEN               // Camera has rotated LCD screen
    #undef CAM_USE_ZOOM_FOR_MF            // Zoom lever can be used for manual focus adjustments
    #undef  CAM_ADJUSTABLE_ALT_BUTTON       // ALT-button can be set from menu
    #undef CAM_REMOTE                     // Camera supports USB-remote
    #undef  CAM_MULTIPART                   // Camera supports SD-card multipartitioning 
    #define CAM_HAS_ZOOM_LEVER          1   // Camera has dedicated zoom buttons
    #undef  CAM_DRAW_EXPOSITION             // Output expo-pair on screen (for cameras which (sometimes) don't do that)
    #undef CAM_HAS_ERASE_BUTTON           // Camera has dedicated erase button
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define  CAM_HAS_ND_FILTER         1      // Camera has build-in ND filter
    #undef CAM_CAN_SD_OVER_NOT_IN_MF      // Camera allows subject distance (focus) override when not in manual focus mode
    #undef CAM_CAN_SD_OVERRIDE            // Camera allows to do subject distance override
    #undef CAM_HAS_MANUAL_FOCUS           // Camera has manual focus mode
    #define CAM_HAS_USER_TV_MODES       1   // Camera has tv-priority or manual modes with ability to set tv value
    #define  CAM_SHOW_OSD_IN_SHOOT_MENU   1   // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode  
//    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO // adress for zoom_status missing, probably more
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1 // Camera can unlock optical zoom in video (if it is locked)
    #define  CAM_FEATURE_FEATHER        1     // Cameras with "feather" or touch wheel.
    #undef CAM_HAS_IS                     // Camera has image stabilizer

//    #define  CAM_CONSOLE_LOG_ENABLED   1      // Development: internal camera stdout -> A/stdout.txt        
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      689833,  1000000, -198299, 1000000, -101299, 1000000, \
      -164267, 1000000, 667466,  1000000,  74132,  1000000, \
       -36515,  1000000, 123872,   1000000,  248498, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
//----------------------------------------------------------
#elif defined (CAMERA_ixus70_sd1000)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      652674,  1000000, -172074, 1000000, -107575, 1000000, \
      -139063, 1000000, 594517,  1000000,  60252,  1000000, \
       -9088,  1000000, 82013,   1000000,  238048, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_ixus80_sd1100)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
	// TODO / test
	#undef  CAM_REMOTE
	#define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #undef  CAM_CAN_MUTE_MICROPHONE
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 0
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                                \
      893969,  1000000, -343107, 1000000, -119590, 1000000, \
      -41350,  1000000, 581255,  1000000,  49523,  1000000, \
       24221,  1000000, 47554,   1000000,  209996, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 6
    #define CAM_ACTIVE_AREA_X2 3304
    #define CAM_ACTIVE_AREA_Y2 2476
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_ixus700_sd500)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_SYNCH
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #undef  CAM_CAN_SD_OVERRIDE
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_MULTIPART               1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1         \
      15265, 1, -6193,  1, -1558, 1, \
     -4125,  1,  12116, 1,  2010, 1, \
      -888,  1,  1639,  1,  5220, 1
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 38
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3146
    #define CAM_ACTIVE_AREA_Y2 2338
    // camera name
    #define PARAM_CAMERA_NAME 2 // parameter number for GetParameterData

//----------------------------------------------------------

#elif defined (CAMERA_ixus750_sd550)
    #define CAM_PROPSET                1

    #define CAM_RAW_ROWPIX              3152  // for 7 MP
    #define CAM_RAW_ROWS                2340  // for 7 MP

    #define  CAM_USE_ZOOM_FOR_MF    1
    #define CAM_DRAW_EXPOSITION        1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER          1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define  CAM_CAN_SD_OVERRIDE    1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_HAS_IS
    #define CAM_MULTIPART              1 
    #undef CAM_SYNCH 
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      580280, 1000000, -172239, 1000000, -89707,  1000000, \
     -206596, 1000000,  634926, 1000000,  63877,  1000000, \
      10377,  1000000,  62053,  1000000,  242646, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 36
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 3148
    #define CAM_ACTIVE_AREA_Y2 2340
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_ixus800_sd700)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define DNG_SUPPORT                 1

 // Warning! DNG4PS2 has both ixus800 and sd700 support with different CFA patterns and color matrices. 
 // Used settings for IXUS800

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1          \
      14062, 1, -5199,  1, -1446,  1, \
      -4712, 1,  12470, 1,  2243,  1, \
      -1286, 1,  2028,  1,  4836,  1
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  2816
    #define CAM_JPEG_HEIGHT 2112
    #define CAM_ACTIVE_AREA_X1 44
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2884
    #define CAM_ACTIVE_AREA_Y2 2136
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData

    
//----------------------------------------------------------
#elif defined (CAMERA_ixus850_sd800)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      661014, 1000000, -189364, 1000000, -115797, 1000000, \
     -168772, 1000000,  661827, 1000000,   47392, 1000000, \
      -35846, 1000000,  107148, 1000000,  233705, 1000000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3108
    #define CAM_ACTIVE_AREA_Y2 2332
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    
//----------------------------------------------------------
#elif defined (CAMERA_ixus860_sd870)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
  	#define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #undef  CAM_CAN_MUTE_MICROPHONE
    #undef  CAM_VIDEO_CONTROL
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                               \
      747939, 1000000, -268233, 1000000, -129266, 1000000, \
     -50633,  1000000, 515687,  1000000,  23509,  1000000, \
     -21341,  1000000, 76495,   1000000, 186385,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight            	
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 10
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3302
    #define CAM_ACTIVE_AREA_Y2 2474
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------
#elif defined (CAMERA_ixus950_sd850)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_MULTIPART               1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1        \
      14573, 1, -5482, 1, -1546, 1, \
     -1266,  1, 9799,  1, 1468,  1, \
     -1040,  1, 1912,  1, 3810,  1
    
    #define cam_CalibrationIlluminant1 1 // Daylight            	
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 10
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3302
    #define CAM_ACTIVE_AREA_Y2 2474
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    
//----------------------------------------------------------
#elif defined (CAMERA_ixus960_sd950)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4104   
    #define CAM_RAW_ROWS                3048   

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      913762, 1000000, -261578, 1000000, -135582, 1000000, \
      -99049, 1000000, 1067089, 1000000,  61442,  1000000, \
      48717,  1000000, 96802,   1000000,  412056, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  4000
    #define CAM_JPEG_HEIGHT 3000
    #define CAM_ACTIVE_AREA_X1 48
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 4080
    #define CAM_ACTIVE_AREA_Y2 3036
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//==========================================================
// S-Series
//==========================================================
#elif defined (CAMERA_s2is)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #undef  CAM_SYNCH   
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define  CAM_HAS_VIDEO_BUTTON       1
    #undef  CAM_VIDEO_CONTROL
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      547708,  1000000, -143462, 1000000,  -99243, 1000000, \
     -186838,  1000000, 663925,  1000000,   50970, 1000000, \
     -5810,    1000000, 79162,   1000000,  266988, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 10
    #define CAM_ACTIVE_AREA_X2 2626
    #define CAM_ACTIVE_AREA_Y2 1966
    // camera name
    #define PARAM_CAMERA_NAME 2 // parameter number for GetParameterData
    #define CAM_BRACKETING              1
//----------------------------------------------------------
#elif defined (CAMERA_s3is)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP
    
    #undef  CAM_SYNCH  
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_MULTIPART               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define  CAM_HAS_VIDEO_BUTTON       1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
     14062, 10000, -5199, 10000, -1446, 10000,             \
     -4712, 10000, 12470, 10000,  2243, 10000,             \
     -1286, 10000,  2028, 10000,  4836, 10000
    
    #define cam_CalibrationIlluminant1 17 // Standard light A
    // cropping
    #define CAM_JPEG_WIDTH  2816
    #define CAM_JPEG_HEIGHT 2112
    #define CAM_ACTIVE_AREA_X1 44
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2884
    #define CAM_ACTIVE_AREA_Y2 2136
    // camera name
    #define PARAM_CAMERA_NAME 3 // parameter number for GetParameterData
    #define CAM_BRACKETING              1

//----------------------------------------------------------
#elif defined (CAMERA_s5is)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
    #define  CAM_HAS_VIDEO_BUTTON       1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                               \
      650591, 1000000, -199585, 1000000, -123118, 1000000, \
     -69617,  1000000, 583926,  1000000,  34354,  1000000, \
     -19113,  1000000, 82163,   1000000, 210786,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 10
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3302
    #define CAM_ACTIVE_AREA_Y2 2474
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
//  #define CAM_BRACKETING              1 //propcase for dryos not found yet

//==========================================================
// TX-Series
//==========================================================
#elif defined (CAMERA_tx1)
    #define CAM_PROPSET                 2
    
    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #define CAM_SWIVEL_SCREEN           1
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_MULTIPART               1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define  CAM_HAS_VIDEO_BUTTON       1
    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                \
      510370,  1000000, -68998,  1000000, -86859,  1000000, \
      -279980, 1000000, 766686,  1000000,  67944,  1000000, \
      -14382,  1000000, 113688,  1000000, 239853,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3072
    #define CAM_JPEG_HEIGHT 2304
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3108
    #define CAM_ACTIVE_AREA_Y2 2332
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//==========================================================
// SX-Series
//==========================================================
#elif defined (CAMERA_sx100is)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP
    #undef CAM_SYNCH 
    #define CAM_CAN_MUTE_MICROPHONE     1 
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1 
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  CAM_VIDEO_CONTROL
    #define DNG_SUPPORT                 1
    #define CAM_REAR_CURTAIN            1
    #define CAM_HAS_JOGDIAL             1
    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color
    #define CAM_COLORMATRIX1                               \
      656793, 1000000, -168702, 1000000, -108030, 1000000, \
      -2711,  1000000, 661538,  1000000,  37919,  1000000, \
      77255,  1000000, 48834,   1000000, 241797,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3264
    #define CAM_JPEG_HEIGHT 2448
    #define CAM_ACTIVE_AREA_X1 10
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3302
    #define CAM_ACTIVE_AREA_Y2 2474
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

//----------------------------------------------------------

#else
    #error camera type not defined

#endif

#endif /* CAMERA_H */
