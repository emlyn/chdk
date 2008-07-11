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

    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU 1   // In CHDK for this camera realized adjustable video compression
    #undef  CAM_CAN_MUTE_MICROPHONE         // Camera has function to mute microphone

    #define CAM_EMUL_KEYPRESS_DELAY     40  // Delay to interpret <alt>-button press as longpress
    #define CAM_EMUL_KEYPRESS_DURATION  5   // Length of keypress emulation

    #undef  CAM_AF_SCAN_DURING_VIDEO_RECORD // CHDK can make single AF scan during video record

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
    
//----------------------------------------------------------
#elif defined (CAMERA_a570)
    #define CAM_PROPSET                 2

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP
    #define CAM_MULTIPART               1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

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

//----------------------------------------------------------
#elif defined (CAMERA_a700)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2

//----------------------------------------------------------
#elif defined (CAMERA_a710)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #define CAM_MULTIPART               1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

//----------------------------------------------------------
#elif defined (CAMERA_a720)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1


//==========================================================
// SD-Series (IXUS-Series)
//==========================================================
#elif defined (CAMERA_ixus50_sd400)
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
	//#define CAM_CONSOLE_LOG_ENABLED     1

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

//----------------------------------------------------------
#elif defined (CAMERA_ixus700_sd500)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

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
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
    
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
    #define CAM_MULTIPART		1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

//==========================================================
// S-Series
//==========================================================
#elif defined (CAMERA_s2is)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO


//----------------------------------------------------------
#elif defined (CAMERA_s3is)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_MULTIPART               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO


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

//==========================================================
// SX-Series
//==========================================================
#elif defined (CAMERA_sx100is)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1

//----------------------------------------------------------

#else
    #error camera type not defined

#endif

#endif /* CAMERA_H */
