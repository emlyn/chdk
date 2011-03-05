#ifndef CAMERA_H
#define CAMERA_H

//==========================================================
// Camera-dependent settings
//==========================================================

//----------------------------------------------------------
// Default values
//----------------------------------------------------------
    #undef  CAM_RAW_ROWPIX                          // Number of pixels in RAW row
    #undef  CAM_RAW_ROWS                            // Number of rows in RAW

    #undef  CAM_DRYOS                               // Camera is DryOS-based
    #undef  CAM_PROPSET                             // Camera's properties group (the generation)

    #undef  CAM_SWIVEL_SCREEN                       // Camera has rotated LCD screen
    #define CAM_USE_ZOOM_FOR_MF         1           // Zoom lever can be used for manual focus adjustments
    #undef  CAM_ADJUSTABLE_ALT_BUTTON               // ALT-button can be set from menu
    #define CAM_REMOTE                  1           // Camera supports USB-remote
    #define CAM_SYNCH                   1           // Camera supports SDM precision synch
    #undef  CAM_MULTIPART                           // Camera supports SD-card multipartitioning
    #define CAM_HAS_ZOOM_LEVER          1           // Camera has dedicated zoom buttons
    #undef  CAM_DRAW_EXPOSITION                     // Output expo-pair on screen (for cameras which (sometimes) don't do that)
    #define CAM_HAS_ERASE_BUTTON        1           // Camera has dedicated erase button
    #define CAM_HAS_IRIS_DIAPHRAGM      1           // Camera has real diaphragm mechanism
    #undef  CAM_HAS_ND_FILTER                       // Camera has build-in ND filter
    #define CAM_CAN_SD_OVER_NOT_IN_MF   1           // Camera allows subject distance (focus) override when not in manual focus mode
    #define CAM_CAN_SD_OVERRIDE         1           // Camera allows to do subject distance override
    #define CAM_HAS_MANUAL_FOCUS        1           // Camera has manual focus mode
    #define CAM_HAS_USER_TV_MODES       1           // Camera has tv-priority or manual modes with ability to set tv value
    #undef  CAM_SHOW_OSD_IN_SHOOT_MENU              // On some cameras Canon shoot menu has additional functionality and useful in this case to see CHDK OSD in this mode
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1 // Camera can unlock optical zoom in video (if it is locked)
    #undef  CAM_FEATURE_FEATHER                     // Cameras with "feather" or touch wheel.
    #define CAM_HAS_IS                  1           // Camera has image stabilizer
    #undef  CAM_HAS_JOGDIAL                         // Camera has a "jog dial"

    #undef  CAM_CONSOLE_LOG_ENABLED                 // Development: internal camera stdout -> A/stdout.txt
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU 1           // In CHDK for this camera realized adjustable video compression
    #undef  CAM_CAN_MUTE_MICROPHONE                 // Camera has function to mute microphone

    #define CAM_EMUL_KEYPRESS_DELAY     40          // Delay to interpret <alt>-button press as longpress
    #define CAM_EMUL_KEYPRESS_DURATION  5           // Length of keypress emulation

    #define CAM_MENU_BORDERWIDTH        30          // Related to screen layout somehow.
                                                    // TODO someone explain what this does, probably doesn't really belong here

    #undef  CAM_AF_SCAN_DURING_VIDEO_RECORD         // CHDK can make single AF scan during video record
    #undef  CAM_HAS_VIDEO_BUTTON                    // Camera can take stills in video mode, and vice versa
    #undef  CAM_EV_IN_VIDEO                         // CHDK can change exposure in video mode
    #define CAM_VIDEO_CONTROL           1           // pause / unpause video recordings
    #undef  CAM_VIDEO_QUALITY_ONLY                  // Override Video Bitrate is not supported

    #define ZOOM_OVERRIDE               0           // Shall zoom-override be used? default 0 becoz not implemented right now

    #define DNG_SUPPORT                 1           // Camera supports DNG format for saving of RAW images

    #undef  CAM_REAR_CURTAIN                        // Camera do not have front/rear curtain flash sync in menu
    #undef  CAM_BRACKETING                          // Cameras that have bracketing (focus & ev) in original firmware already, most likely s- & g-series (propcase for digic III not found yet!)
    #undef  CAM_EXT_TV_RANGE                        // CHDK can make exposure time longer than 64s
    #undef  CAM_CHDK_PTP                            // include CHDK PTP support

    #define CAM_UNCACHED_BIT            0x10000000  // bit indicating the uncached memory

    #define CAM_MAKE                    "Canon"
    #define CAM_SENSOR_BITS_PER_PIXEL   10          // Bits per pixel. 10 is standard, 12 is supported except for curves
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             31

    #define CAM_BITMAP_PALETTE          1           // which color set is used for this camera

    #undef CAM_HAS_VARIABLE_ASPECT                  // can switch between 16:9 and 4:3
    #define DEFAULT_RAW_EXT             1           // extension to use for raw (see raw_exts in conf.c)

    // by nandoide sept-2009
    // zebra adjust buffer height: show use at sx200is: needed for save memory space
    #define ZEBRA_HMARGIN0              0

    // aspect corrections
    #define CAM_USES_ASPECT_CORRECTION  0           // if true, camera uses a modified graphics primitives to draw with exact display aspect-ratio.
                                                    // Could slow the graphics output (but not perceived on sx200is), but adds rectangle drawing optimizations to compensate.
                                                    // To extend to other cameras see sx200is camera.h comments in  and comments on core gui_draw.c
    #define CAM_USES_ASPECT_YCORRECTION 0

    // menu, alt (default)
    #define ASPECT_XCORRECTION(x)  ( ((x)<<1) )     // see comments on 200is
    #define ASPECT_YCORRECTION(y)  ( (y) )          // no correction the same for coordinate y. I think there are no cameras actually needing both corrections.
    // viewport, defaults used if there is no aspect correction
    #define ASPECT_VIEWPORT_XCORRECTION(x) ( (x) )  // see comments on 200is
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )  // no correction

    #define EDGE_HMARGIN                0           // define sup and inf screen margins on edge overlay without overlay.  Necessary to save memory buffer space. sx200is needs values other than 0
    // end of section by nandoid

    #undef CAM_QUALITY_OVERRIDE                     // camera may need shooting quality override (sx200is lacks SuperFine quality)

    #undef CAM_ZEBRA_ASPECT_ADJUST                  // zebra needs to account for real bitmap size being different from what lib.c reports
                                                    // also used by some cameras with normal bitmap layouts for memory saving ?
    #undef CAM_ZEBRA_NOBUF                          // zebra draws directly on bitmap buffer. Requires above as well

    #undef CAM_DATE_FOLDER_NAMING                   // set if camera uses date based folder naming and get_target_dir_name is implemented

//----------------------------------------------------------
// Override Default values for Camera if necessary
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
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL             1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                              \
      575419, 1000000,-185557, 1000000, -77898,  1000000, \
     -213702, 1000000, 733569, 1000000,   81514, 1000000, \
      -24604, 1000000, 131906, 1000000,  280378, 1000000

    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 14
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3682
    #define CAM_ACTIVE_AREA_Y2 2764
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #define CAM_BRACKETING              1    
    #define DNG_EXT_FROM ".DPS"
//----------------------------------------------------------

#elif defined (CAMERA_g9)
	#define CAM_PROPSET							2
	#define CAM_DRYOS							1

	#define CAM_RAW_ROWPIX						4104	// for 12 MP
	#define CAM_RAW_ROWS						3048	// for 12 MP
	#define CAM_HAS_ND_FILTER					1
	#define CAM_ADJUSTABLE_ALT_BUTTON			1
	#undef  CAM_EMUL_KEYPRESS_DURATION
	#define CAM_EMUL_KEYPRESS_DURATION			10
	#define CAM_AF_SCAN_DURING_VIDEO_RECORD		1
	#define CAM_HAS_JOGDIAL						1
	// #define CAM_CONSOLE_LOG_ENABLED			1
	#define CAM_BRACKETING						1
	#define CAM_MULTIPART						1
	#define CAM_EXT_TV_RANGE					1

	// camera name
	#define PARAM_CAMERA_NAME					4	// parameter number for GetParameterData

	// pattern
	#define cam_CFAPattern						0x02010100	// Red  Green  Green  Blue
	// color (alternativ: http://lclevy.free.fr/cr2/)
	#define CAM_COLORMATRIX1 \
	1679727, 1000000,  422803, 1000000,  803343, 1000000, \
	 220204, 1000000, 1784845, 1000000,  -63290, 1000000, \
	-282882, 1000000, -475034, 1000000, 4502592, 1000000

	#define cam_CalibrationIlluminant1			1	// Daylight

	// cropping
	#define CAM_JPEG_WIDTH						4000
	#define CAM_JPEG_HEIGHT						3000
	#define CAM_ACTIVE_AREA_X1					52
	#define CAM_ACTIVE_AREA_Y1					14
	#define CAM_ACTIVE_AREA_X2					4076
	#define CAM_ACTIVE_AREA_Y2					3030
//----------------------------------------------------------


//==========================================================
// A-series
//==========================================================
#elif defined (CAMERA_a430)
	#define CAM_PROPSET						1

	#define CAM_RAW_ROWPIX					2392  // for 4 MP 1/3" sensor size
	#define CAM_RAW_ROWS					1752  // for 4 MP 1/3" sensor size

	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_HAS_ZOOM_LEVER
	#define CAM_DRAW_EXPOSITION				1
	#undef  CAM_HAS_ERASE_BUTTON
	#undef  CAM_HAS_IRIS_DIAPHRAGM
	#define CAM_HAS_ND_FILTER				1
	#undef  CAM_HAS_MANUAL_FOCUS
	#undef  CAM_HAS_USER_TV_MODES
	#define CAM_SHOW_OSD_IN_SHOOT_MENU		1
	#undef  CAM_HAS_IS
	#define CAM_CAN_MUTE_MICROPHONE			1
	#define CAM_AF_SCAN_DURING_VIDEO_RECORD	1
	#define CAM_EV_IN_VIDEO					1
	// pattern
	#define cam_CFAPattern 0x01000201  // Green Blue Red Green
	// color
	#define CAM_COLORMATRIX1                                \
      479627,  1000000, -156240, 1000000,  -84926, 1000000, \
     -215238,  1000000,  534902, 1000000,   60219, 1000000, \
      -96906,  1000000,  148194, 1000000,  191583, 1000000

	#define CAM_CONSOLE_LOG_ENABLED			1
	#define cam_CalibrationIlluminant1		1 // Daylight
	// cropping
	#define CAM_JPEG_WIDTH			2272
	#define CAM_JPEG_HEIGHT			1704
	#define CAM_ACTIVE_AREA_X1		0
	#define CAM_ACTIVE_AREA_Y1		8
	#define CAM_ACTIVE_AREA_X2		2336
	#define CAM_ACTIVE_AREA_Y2		1748
	// camera name
	#define PARAM_CAMERA_NAME		3 // parameter number for GetParameterData
	#define CAM_BRACKETING			1
//	#define CAM_MULTIPART			1
//----------------------------------------------------------

#elif defined (CAMERA_a450)
	#define CAM_PROPSET						2

	#define CAM_RAW_ROWPIX					2664   // for 5 MP 1/3" sensor size
	#define CAM_RAW_ROWS					1968   // for 5 MP 1/3" sensor size

	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_HAS_ZOOM_LEVER
	#define CAM_DRAW_EXPOSITION				1
	#undef  CAM_HAS_ERASE_BUTTON
	#undef  CAM_HAS_IRIS_DIAPHRAGM
	#define CAM_HAS_ND_FILTER				1
	#undef  CAM_HAS_MANUAL_FOCUS
	#undef  CAM_HAS_USER_TV_MODES
	#define CAM_SHOW_OSD_IN_SHOOT_MENU		1
	#undef  CAM_HAS_IS
	#define CAM_CAN_MUTE_MICROPHONE			1
	#define CAM_AF_SCAN_DURING_VIDEO_RECORD	1
	#define CAM_EV_IN_VIDEO					1
	// pattern
	#define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
	// color
	#define CAM_COLORMATRIX1                               \
      652279,  1000000, -199279, 1000000, -101833, 1000000, \
     -159819,  1000000,  619308, 1000000,   78172, 1000000, \
      -58827,  1000000,  150963, 1000000,  264216, 1000000

	#define cam_CalibrationIlluminant1		1 // Daylight
	// cropping
	#define CAM_JPEG_WIDTH			2592
	#define CAM_JPEG_HEIGHT			1944
	#define CAM_ACTIVE_AREA_X1		6
	#define CAM_ACTIVE_AREA_Y1		6
	#define CAM_ACTIVE_AREA_X2		2618
	#define CAM_ACTIVE_AREA_Y2		1962
	// camera name
	#define PARAM_CAMERA_NAME		4 // parameter number for GetParameterData
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
    #define DNG_EXT_FROM ".DPS"
//----------------------------------------------------------

#elif defined (CAMERA_a470)
	#define CAM_PROPSET                 2
	#define CAM_DRYOS                   1

	#define CAM_RAW_ROWPIX              3152   // for 7 MP
	#define CAM_RAW_ROWS               2340   // for 7 MP

	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_HAS_ZOOM_LEVER
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
	#define CAM_MULTIPART               1
	
	// pattern
	#define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
	// color
	#define CAM_COLORMATRIX1                             \
	673251,  1000000,-200684, 1000000, -98680, 1000000,  \
	-163638, 1000000, 651247, 1000000,  74004, 1000000,  \
	14221,   1000000, 52979,  1000000, 265291, 1000000    
	#define cam_CalibrationIlluminant1 1 // Daylight
	// cropping
	#define CAM_JPEG_WIDTH  3096
	#define CAM_JPEG_HEIGHT 2324
	#define CAM_ACTIVE_AREA_X1 12
	#define CAM_ACTIVE_AREA_Y1 8
	#define CAM_ACTIVE_AREA_X2 3108
	#define CAM_ACTIVE_AREA_Y2 2332
	// camera name
	#define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
	//#define DNG_EXT_FROM ".DPS"	
//----------------------------------------------------------

#elif defined (CAMERA_a480)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3720   
    #define CAM_RAW_ROWS                2772   

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #undef  CAM_HAS_IS
    #define CAM_MULTIPART               1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_REAR_CURTAIN            1
    #undef  DEFAULT_RAW_EXT 
    #define DEFAULT_RAW_EXT             2   // use .CR2 
    #define CAM_EXT_TV_RANGE            1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_EV_IN_VIDEO             1

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 3690
    #define CAM_ACTIVE_AREA_Y2 2772

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127
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
    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
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
    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1

    #define  CAM_CHDK_PTP               1 // include CHDK PTP support

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
    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
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
    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
//----------------------------------------------------------

#elif defined (CAMERA_a570)
	#define CAM_PROPSET                 2

	#define CAM_RAW_ROWPIX              3152	// for 7 MP
	#define CAM_RAW_ROWS                2340	// for 7 MP
	#define CAM_MULTIPART               1
	#define CAM_CAN_MUTE_MICROPHONE     1
	#define CAM_ADJUSTABLE_ALT_BUTTON   1
	#define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
	#define CAM_EV_IN_VIDEO             1
	#define CAM_REAR_CURTAIN            1
	// pattern
	#define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
	// color
	#define CAM_COLORMATRIX1                            \
    528283, 1000000,-144259, 1000000, -85966, 1000000,  \
    -202789, 1000000, 736563, 1000000, 73008, 1000000,  \
    -27130,  1000000, 107702, 1000000, 264543, 1000000

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

	#define DNG_EXT_FROM ".DPS"
	#define CAM_EXT_TV_RANGE            1
        #define CAM_CHDK_PTP                1 // include CHDK PTP support
//----------------------------------------------------------

#elif defined (CAMERA_a590)
#define CAM_ADJUSTABLE_ALT_BUTTON   1
#define CAM_PROPSET                 2
#define CAM_DRYOS                   1

#define CAM_RAW_ROWPIX              3336   // for new 8 MP
#define CAM_RAW_ROWS                2480   // for new 8 MP

#define CAM_USE_ZOOM_FOR_MF         1

#define CAM_CAN_MUTE_MICROPHONE     1
#define CAM_HAS_IRIS_DIAPHRAGM      1
#undef  CAM_HAS_ND_FILTER

#define CAM_HAS_MANUAL_FOCUS        1

#define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
//#define CAM_EV_IN_VIDEO             1      // not working on 101b!!!
// pattern
#define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green 
// color                                                      
#define CAM_COLORMATRIX1                              \
 726857, 1000000, -176454, 1000000, -124118, 1000000, \
 -71340, 1000000,  592001, 1000000,   75622, 1000000, \
  63222, 1000000,   50547, 1000000,  219582, 1000000

#define cam_CalibrationIlluminant1 1 // Daylight
// cropping
#define CAM_JPEG_WIDTH  3264
#define CAM_JPEG_HEIGHT 2448
#define CAM_ACTIVE_AREA_X1 12
#define CAM_ACTIVE_AREA_Y1 10
// note: the above contains some pixels which have valid data, 
// but are not at the same levels as the rest of the frame
// the values below crop the "different" looking pixels.
//#define CAM_ACTIVE_AREA_X1 16
//#define CAM_ACTIVE_AREA_Y1 18
#define CAM_ACTIVE_AREA_X2 3300
#define CAM_ACTIVE_AREA_Y2 2480

// camera name
#define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

#define CAM_EXT_TV_RANGE            1
#define CAM_MULTIPART               1
#define  CAM_CHDK_PTP               1 // include CHDK PTP support
//----------------------------------------------------------

#elif defined (CAMERA_a610)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_MULTIPART               1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
    #define CAM_EXT_TV_RANGE            1

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

    #define DNG_EXT_FROM ".DPS"
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support
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
    #define DNG_EXT_FROM ".DPS"
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
    #define DNG_EXT_FROM ".DPS"
    #define CAM_EXT_TV_RANGE            1
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
    #define DNG_EXT_FROM ".DPS"
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

    #define DNG_EXT_FROM ".CR2"
//----------------------------------------------------------

#elif defined (CAMERA_a700)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_HAS_IS
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 2
    #define CAM_EV_IN_VIDEO             1
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
    #define DNG_EXT_FROM ".DPS"
//----------------------------------------------------------

#elif defined (CAMERA_a710)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #define CAM_MULTIPART               1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #define CAM_REAR_CURTAIN            1 // http://chdk.setepontos.com/index.php/topic,650.msg54434.html#msg54434 
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

    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
//----------------------------------------------------------

#elif defined (CAMERA_a720)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP

    #define CAM_MULTIPART               1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_CAN_MUTE_MICROPHONE     1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_EV_IN_VIDEO             1
    #undef  CAM_VIDEO_CONTROL
    #define CAM_EXT_TV_RANGE            1

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

    #define DNG_EXT_FROM ".CR2"
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support
//----------------------------------------------------------

#elif defined (CAMERA_a2000)
	////////////////////////////////
	// Sure values
	////////////////////////////////
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3720  
    #define CAM_RAW_ROWS                2772  

    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736


    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

    ////////////////////////////////
    // Almost sure, sensor data taken from 
    // ixus870_sd880 which should have same sensor..
    ////////////////////////////////
    #undef CAM_SENSOR_BITS_PER_PIXEL
    #undef CAM_WHITE_LEVEL
    #undef CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #define cam_CFAPattern              0x02010100 // Red  Green  Green  Blue
    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000 
    #define cam_CalibrationIlluminant1  1 // Daylight

    // cropping (from ixus870_sd880)
    #define CAM_ACTIVE_AREA_X1          14
    #define CAM_ACTIVE_AREA_Y1          8
    #define CAM_ACTIVE_AREA_X2          3682
    #define CAM_ACTIVE_AREA_Y2          2764

    #undef  CAM_HAS_MANUAL_FOCUS
// for the purposes of CHDK, the FACE button is treated as the erase button
//    #undef  CAM_HAS_ERASE_BUTTON
//----------------------------------------------------------

#elif defined (CAMERA_d10)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4104		// 12 MP 12bpp
    #define CAM_RAW_ROWS                3048		// from " CrwAddress %lx, CrwSize H %ld V %ld\r"

    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

    #define CAM_HAS_ZOOM_LEVER          1 // note, has zoom in/out buttons, not lever


// TODO
//    #define CAM_CAN_SD_OVER_NOT_IN_MF   1			// Camera allows subject distance (focus) override when not in manual focus mode
//    #define CAM_CAN_SD_OVERRIDE         1			// Camera allows to do subject distance override

    #define CAM_HAS_MANUAL_FOCUS		1
// long shutter is acutally user TV, may work ?
    #undef 	CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU            1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1
// TODO this doesn't seem to be working
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD       1
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU   1 // In CHDK for this camera realized adjustable video compression

    #define CAM_HAS_IS                  1
    #undef CAM_HAS_JOGDIAL

    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY      1


//    #define CAM_EXT_TV_RANGE            1

    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000

    #undef CAM_BITMAP_PALETTE
// OK looks similar to ixus100 based on forum posts
    #define CAM_BITMAP_PALETTE          5

    #define CAM_QUALITY_OVERRIDE 1
    #undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #undef CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127

	#define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green 

    #define CAM_COLORMATRIX1                               \
      14052, 10000, -5229, 10000, -1156, 10000, \
      -1325, 10000,  9420, 10000,  2252, 10000, \
       -498, 10000,  1957, 10000,  4116, 10000
    #define cam_CalibrationIlluminant1  21			// D65

	// cropping OK
    #define CAM_JPEG_WIDTH              4000
    #define CAM_JPEG_HEIGHT             3000
    #define CAM_ACTIVE_AREA_X1          0 // some data all the way to left, normal 8 ?
    #define CAM_ACTIVE_AREA_Y1          10
    #define CAM_ACTIVE_AREA_X2          4072 // or 4024 
    #define CAM_ACTIVE_AREA_Y2          3040 // or 3041 or 3020

    // camera name OK
    #define PARAM_CAMERA_NAME           4			// parameter number for GetParameterData

    // XXXX
    #undef CAM_USES_ASPECT_CORRECTION
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)   ( ((x)<<1) )

    // Note color palette affects grids!
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)   ( (x) )

    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x)
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

    // Note color palette affects games!
	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (trhough new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #define CAM_ZEBRA_ASPECT_ADJUST 1

    #define  CAM_CHDK_PTP               1 // include CHDK PTP support

//----------------------------------------------------------


//==========================================================
// SD-Series (IXUS-Series)
//==========================================================
#elif defined (CAMERA_ixus40_sd300)
    #define CAM_PROPSET                 1

    #define CAM_RAW_ROWPIX              2400
    #define CAM_RAW_ROWS                1766

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
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 2356
    #define CAM_ACTIVE_AREA_Y2 1764
    // camera name
    #define PARAM_CAMERA_NAME 2 // parameter number for GetParameterData
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
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                                  \
      685247,  1000000, -204939,  1000000, -106531,  1000000, \
     -267616,  1000000,  790509,  1000000,   73359,  1000000, \
       32401,  1000000,   15655,  1000000,  314892,  1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  2592
    #define CAM_JPEG_HEIGHT 1944
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 2628
    #define CAM_ACTIVE_AREA_Y2 1968
    // camera name
    #define PARAM_CAMERA_NAME 2 // parameter number for GetParameterData
//----------------------------------------------------------

#elif defined (CAMERA_ixusizoom_sd30)
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
	#undef  DNG_SUPPORT
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
    #define DNG_EXT_FROM ".DPS"
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
    #define CAM_FEATURE_FEATHER         1

//    #define CAM_CONSOLE_LOG_ENABLED     1  //100a won't compile if this is defined ("undefined reference to `_iosDevFind'")
    #undef  CAM_CHDK_HAS_EXT_VIDEO_MENU
    #undef  CAM_HAS_IS
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
    #define DNG_EXT_FROM ".DPS"
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
    #define CAM_MULTIPART               1   // Camera supports SD-card multipartitioning 
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
    
    #define DNG_EXT_FROM ".DPS"
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
    #define CAM_MULTIPART               1
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

    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
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

    #define CAM_EXT_TV_RANGE            1
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
    #define DNG_EXT_FROM ".DPS"
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
    #define DNG_EXT_FROM ".DPS"
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
    #define CAM_MULTIPART               1 
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

    #define DNG_EXT_FROM ".DPS"
//----------------------------------------------------------

#elif defined (CAMERA_ixus900_sd900)
    #define CAM_PROPSET                 1   // ToDo: test if correct

    #define CAM_RAW_ROWPIX              3672   // value from RAW file (3648px + 24px)
    #define CAM_RAW_ROWS                2760   // value from RAW file (2736 + 24px)

    //#undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1   // ToDo: test if required
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    //#undef  CAM_CAN_SD_OVER_NOT_IN_MF
    //#undef  CAM_CAN_SD_OVERRIDE
    #undef  CAM_HAS_IS
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1   // force CHDK OSD to show in record more
    #define CAM_FEATURE_FEATHER         1
    //#define CAM_CONSOLE_LOG_ENABLED     1   // ToDo: LOG stuff is disabled/removed
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_MULTIPART               1

    // pattern
    #define cam_CFAPattern 0x02010100   // Red  Green  Green  Blue
    // color (from G7)
    #define CAM_COLORMATRIX1                              \
      575419, 1000000,-185557, 1000000, -77898,  1000000, \
     -213702, 1000000, 733569, 1000000,   81514, 1000000, \
      -24604, 1000000, 131906, 1000000,  280378, 1000000
    /*
    // SD800
    #define CAM_COLORMATRIX1                               \
      661014, 1000000, -189364, 1000000, -115797, 1000000, \
     -168772, 1000000,  661827, 1000000,   47392, 1000000, \
      -35846, 1000000,  107148, 1000000,  233705, 1000000
    */
    #define cam_CalibrationIlluminant1 1   // ToDo: Daylight (first selectable Illuminant Calibration mode ?)

    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 14   // ??? from G7, A640
    #define CAM_ACTIVE_AREA_Y1 8   // ??? from G7, A640
    //#define CAM_ACTIVE_AREA_X2 3672   // from RAW file
    //#define CAM_ACTIVE_AREA_Y2 2760   // from RAW file
    #define CAM_ACTIVE_AREA_X2 3682   // ??? from G7, A640, CAM_JPEG_WIDTH + 40
    #define CAM_ACTIVE_AREA_Y2 2764   // ??? from G7, A640, CAM_JPEG_HEIGHT + 40
    // camera name
    #define PARAM_CAMERA_NAME 4   // camera param id of EXIF camera model

    #define DNG_EXT_TO   ".DPS"
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

    #define DNG_EXT_FROM ".CR2"
//----------------------------------------------------------

#elif defined (CAMERA_ixus870_sd880)
    // Camera details
    #define CAM_DRYOS                   1
    #define CAM_PROPSET                 2

    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_BITMAP_PALETTE          1
    #define CAM_BRACKETING              1   // XXX 
    #define CAM_CAN_SD_OVER_NOT_IN_MF   1
    #define CAM_CAN_SD_OVERRIDE         1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #define CAM_EXT_TV_RANGE            1
    #define CAM_HAS_IS                  1
    #define CAM_HAS_JOGDIAL             1
    #define CAM_HAS_ND_FILTER           1
    #define CAM_HAS_ZOOM_LEVER          1
    #define CAM_MULTIPART               1
    #define CAM_REMOTE                  1
    #define CAM_SYNCH                   1
    #define CAM_CHDK_PTP                1
    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000  // 0xFF874198 (via ExMem.FreeCacheable
    #define PARAM_CAMERA_NAME           4 // parameter number for GetParameterData

    #undef  CAM_CAN_MUTE_MICROPHONE         // XXX
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #undef  CAM_HAS_MANUAL_FOCUS
    #undef  CAM_HAS_USER_TV_MODES           // XXX
    #undef  CAM_HAS_VIDEO_BUTTON            // XXX
    #undef  CAM_EV_IN_VIDEO                 // XXX
    #undef  CAM_REAR_CURTAIN 

    #define CAM_JPEG_WIDTH              3648
    #define CAM_JPEG_HEIGHT             2736
    #define CAM_RAW_ROWPIX              3720
    #define CAM_RAW_ROWS                2772
    #define CAM_ACTIVE_AREA_X1          14       // XXX
    #define CAM_ACTIVE_AREA_Y1          8        // XXX
    #define CAM_ACTIVE_AREA_X2          3682     // XXX
    #define CAM_ACTIVE_AREA_Y2          2764     // XXX

    #undef CAM_SENSOR_BITS_PER_PIXEL
    #undef CAM_WHITE_LEVEL
    #undef CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1) // XXX
    #define CAM_BLACK_LEVEL             127 // XXX

    #define cam_CFAPattern              0x02010100 // Red  Green  Green  Blue
    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000    // XXX
    #define cam_CalibrationIlluminant1  1 // Daylight       XXX


    // CHDK functionality
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU 1   // XXX
    #define CAM_EMUL_KEYPRESS_DELAY     40
    #define CAM_EMUL_KEYPRESS_DURATION  5
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #undef  DEFAULT_RAW_EXT 
    #define DEFAULT_RAW_EXT             2   // use .CR2 
    
    #undef  CAM_ADJUSTABLE_ALT_BUTTON
    #undef  CAM_CONSOLE_LOG_ENABLED 
    #undef  CAM_DRAW_EXPOSITION             // XXX
    #undef  CAM_FEATURE_FEATHER             // XXX
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_VIDEO_CONTROL               // XXX
//----------------------------------------------------------

#elif defined (CAMERA_ixus950_sd850)
    #define CAM_EXT_TV_RANGE            1
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
    #define DNG_EXT_FROM ".DPS"
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

    #define DNG_EXT_FROM ".CR2"
//----------------------------------------------------------

#elif defined (CAMERA_ixus970_sd890)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3720
    #define CAM_RAW_ROWS                2772

    #undef CAM_USE_ZOOM_FOR_MF
    #undef CAM_HAS_ERASE_BUTTON
    #undef CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #undef CAM_HAS_MANUAL_FOCUS
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_EXT_TV_RANGE            1

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue

    // color
    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000
    #define cam_CalibrationIlluminant1 1 // Daylight

    // cropping 
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 3690
    #define CAM_ACTIVE_AREA_Y2 2772

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

    // 12 bit support
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support
//----------------------------------------------------------

#elif defined (CAMERA_ixus980_sd990)
    #define CAM_PROPSET                 2 // all values checked so far match propset 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4480 // 14.7 MP 12bpp
    #define CAM_RAW_ROWS                3348   

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1
    #define  CAM_HAS_MANUAL_FOCUS		1
    #define  CAM_HAS_USER_TV_MODES		1 //include M/P ? needed to make Tv bracketing work
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU 1
    #undef  CAM_VIDEO_CONTROL
    #undef CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000
    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    2

	#undef CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127
    #define CAM_HAS_JOGDIAL             1
//    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_VIDEO_QUALITY_ONLY          1  
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
	#undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
	#undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)

    // pattern
    #define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
    // color preliminary
    #define CAM_COLORMATRIX1                               \
      837237, 1000000, -290137, 1000000, -128156, 1000000, \
      -127762, 1000000, 643909, 1000000,  52973,  1000000, \
      4446,  1000000, 88354,   1000000,  224246, 1000000
    
    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping 
    #define CAM_JPEG_WIDTH  4416
    #define CAM_JPEG_HEIGHT 3312
    #define CAM_ACTIVE_AREA_X1 12
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 4444
    #define CAM_ACTIVE_AREA_Y2 3324
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData sd990: OK

    // copied from DavidBs D10 stuff
    #undef CAM_USES_ASPECT_CORRECTION
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)   ( ((x)<<1) )

    // Note color palette affects grids!
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)   ( (x) )

    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x)
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

    // Note color palette affects games!
	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (through new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

   #define CAM_ZEBRA_ASPECT_ADJUST 1

//    #define DNG_EXT_FROM ".CR2"
//----------------------------------------------------------

#elif defined (CAMERA_ixus100_sd780)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4080		// 12 MP 12bpp
    #define CAM_RAW_ROWS                3048		// VERIFY_SD780 Found RAW #s by searching " CrwAddress %lx, CrwSize H %ld V %ld\r"

    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

    #undef CAM_REMOTE
    #undef CAM_SYNCH

    #define CAM_HAS_ZOOM_LEVER          1

//    #define CAM_CAN_SD_OVER_NOT_IN_MF   1			// Camera allows subject distance (focus) override when not in manual focus mode
//    #define CAM_CAN_SD_OVERRIDE         1			// Camera allows to do subject distance override

    #undef  CAM_HAS_MANUAL_FOCUS
    #define CAM_HAS_USER_TV_MODES                 1
    #define CAM_SHOW_OSD_IN_SHOOT_MENU            1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD       1
    #define CAM_CHDK_HAS_EXT_VIDEO_MENU           1

    #define CAM_HAS_IS                  1
    #undef CAM_HAS_JOGDIAL

    #undef  CAM_VIDEO_CONTROL
    #define CAM_VIDEO_QUALITY_ONLY      1

    #define CAM_EXT_TV_RANGE            1

    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE          5

    #undef ZEBRA_HMARGIN0
    #define ZEBRA_HMARGIN0              150			//zebra adjust buffer height: show use at sx200is: needed for save memory space

    #define CAM_QUALITY_OVERRIDE 1
    #undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #undef CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127

    // pattern
    //RealRom:FFA99FB4                    ADR     R0, aObRG1G2BLdLdLd ; "\n  OB : (R, G1, G2, B) = (%ld, %ld, %ld"...
    #define cam_CFAPattern              0x02010100		// Red  Green  Green  Blue

    // color preliminary (see DNG4PS2 wiki)
    #define CAM_COLORMATRIX1                               \
      661840,  1000000, -185671, 1000000, -97110,  1000000, \
      -83661,  1000000, 578860, 1000000,   32308,  1000000, \
      -8681,    1000000, 70356,   1000000, 207341, 1000000

    //Here is an alternate CAM_COLORMATRIX1 - Current one is nice for me but hey I'm no colour expert.
    //XYZ -> Camera matrix:
    //0.459395 -0.129083 -0.068085
    //-0.055837 0.400827 0.020378
    //-0.004622 0.048662 0.139970

    #define cam_CalibrationIlluminant1  17			// Standard Light A

	// cropping
    #define CAM_JPEG_WIDTH              4000
    #define CAM_JPEG_HEIGHT             3000
    #define CAM_ACTIVE_AREA_X1          40
    #define CAM_ACTIVE_AREA_Y1          24
    #define CAM_ACTIVE_AREA_X2          4056
    #define CAM_ACTIVE_AREA_Y2          3040
    // camera name
    #define PARAM_CAMERA_NAME           4			// parameter number for GetParameterData sd990: OK

    #undef CAM_USES_ASPECT_CORRECTION
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)   ( ((x)<<1) )

    // Note color palette affects grids!
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)   ( (x) )

    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x)
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

    // Note color palette affects games!
	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (through new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none
    #define CAM_ZEBRA_ASPECT_ADJUST 1
	// camera has little free memory
    #define CAM_ZEBRA_NOBUF 1
//----------------------------------------------------------

#elif defined (CAMERA_ixus90_sd790)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3720
    #define CAM_RAW_ROWS                2772

    #undef CAM_USE_ZOOM_FOR_MF
    #undef CAM_HAS_ERASE_BUTTON
    #define CAM_MULTIPART               1
    #undef CAM_HAS_IRIS_DIAPHRAGM
    #undef CAM_HAS_MANUAL_FOCUS

    #define CAM_HAS_ND_FILTER           1
    #undef CAM_HAS_USER_TV_MODES
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #define CAM_HAS_JOGDIAL             1
    #undef CAM_VIDEO_CONTROL
    #define CAM_EXT_TV_RANGE            1          // CHDK can make exposure time longer than 64s

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000
    #define cam_CalibrationIlluminant1 1 // Daylight

    // cropping 
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 3690
    #define CAM_ACTIVE_AREA_Y2 2772

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127
//----------------------------------------------------------

#elif defined (CAMERA_ixus85_sd770)
	#define CAM_PROPSET                 2
	#define CAM_DRYOS                   1

	#define CAM_RAW_ROWPIX              3720
	#define CAM_RAW_ROWS                2772

	#undef CAM_USE_ZOOM_FOR_MF
	#undef CAM_HAS_ERASE_BUTTON
	#define CAM_MULTIPART               1
	#undef CAM_HAS_IRIS_DIAPHRAGM
	#undef CAM_HAS_MANUAL_FOCUS

	#define CAM_HAS_ND_FILTER           1
	#undef CAM_HAS_USER_TV_MODES
	#define CAM_SHOW_OSD_IN_SHOOT_MENU  1
	 #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
	#undef CAM_HAS_JOGDIAL
	#undef CAM_VIDEO_CONTROL
	#define CAM_EXT_TV_RANGE            1          // CHDK can make exposure time longer than 64s

	// pattern
	#define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
	// color
	#define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000
	#define cam_CalibrationIlluminant1 1 // Daylight

	// cropping 
	#define CAM_JPEG_WIDTH  3648
	#define CAM_JPEG_HEIGHT 2736
	#define CAM_ACTIVE_AREA_X1 6
	#define CAM_ACTIVE_AREA_Y1 12
	#define CAM_ACTIVE_AREA_X2 3690
	#define CAM_ACTIVE_AREA_Y2 2772

	// camera name
	#define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
	#undef  CAM_SENSOR_BITS_PER_PIXEL
	#undef  CAM_WHITE_LEVEL
	#undef  CAM_BLACK_LEVEL
	#define CAM_SENSOR_BITS_PER_PIXEL   12
	#define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	#define CAM_BLACK_LEVEL             127
//----------------------------------------------------------

#elif defined (CAMERA_ixus95_sd1200)
	#define CAM_PROPSET                  2 
	#define CAM_DRYOS                    1

	#define CAM_RAW_ROWPIX               3720
	#define CAM_RAW_ROWS                 2772

	#undef   CAM_HAS_ERASE_BUTTON
	#define  CAM_USE_ZOOM_FOR_MF         1
	#define  CAM_MULTIPART               1
	#undef   CAM_HAS_IRIS_DIAPHRAGM
	#define  CAM_HAS_ND_FILTER           1

	#undef CAM_SYNCH

	#define CAM_HAS_ZOOM_LEVER          1

	#undef  CAM_HAS_MANUAL_FOCUS
	#define  CAM_HAS_USER_TV_MODES		 1 
	#define  CAM_SHOW_OSD_IN_SHOOT_MENU	 1
	#define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO  1
	//#define CAM_AF_SCAN_DURING_VIDEO_RECORD       1
	#undef CAM_AF_SCAN_DURING_VIDEO_RECORD		//TODO: change to define and find NSTUB    
	#define  CAM_CHDK_HAS_EXT_VIDEO_MENU	 1

	#define CAM_HAS_IS						 1
	#undef CAM_HAS_JOGDIAL

	#undef   CAM_VIDEO_CONTROL
	#define  CAM_VIDEO_QUALITY_ONLY		 	1

	//#define CAM_EXT_TV_RANGE            1

	#undef   CAM_UNCACHED_BIT            // shut up compiler
	#define  CAM_UNCACHED_BIT            0x40000000

	#undef   CAM_BITMAP_PALETTE
	#define  CAM_BITMAP_PALETTE          2

	#define CAM_QUALITY_OVERRIDE 1	
	#undef   CAM_SENSOR_BITS_PER_PIXEL
	#define  CAM_SENSOR_BITS_PER_PIXEL   12
	#undef   CAM_WHITE_LEVEL
	#define  CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	#undef   CAM_BLACK_LEVEL
	#define  CAM_BLACK_LEVEL             127

	// pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue

	// color preliminary
	// from para in forum
	#define  CAM_COLORMATRIX1                             \
    1484685, 1000000, -530958, 1000000, -208054, 1000000, \
    143142, 1000000, 793552, 1000000, 83907, 1000000, \
    146290, 1000000, -44679, 1000000, 430414, 1000000

	#define  cam_CalibrationIlluminant1 1 // Daylight

	// cropping 
	#define  CAM_JPEG_WIDTH  3648
	#define  CAM_JPEG_HEIGHT 2736
	#define  CAM_ACTIVE_AREA_X1 8
	#define  CAM_ACTIVE_AREA_Y1 12
	#define  CAM_ACTIVE_AREA_X2 3692
	#define  CAM_ACTIVE_AREA_Y2 2772

	// camera name
	#define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData

	// aspect correction
    #undef CAM_USES_ASPECT_CORRECTION
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)   ( ((x)<<1) )

    // Note color palette affects grids!
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)   ( (x) )

    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x)
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (trhough new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #define CAM_ZEBRA_ASPECT_ADJUST 1
	// camera has very little free memory
    #define CAM_ZEBRA_NOBUF 1
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support

//----------------------------------------------------------


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
    #define DNG_EXT_FROM ".DPS"
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
    #define DNG_EXT_FROM ".DPS"

    #define CAM_EXT_TV_RANGE            1
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
    #define CAM_HAS_VIDEO_BUTTON       1
    #define CAM_EXT_TV_RANGE            1
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
    #define CAM_BRACKETING              1 
    #define DNG_EXT_FROM ".DPS"
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support
//----------------------------------------------------------


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
    #define DNG_EXT_FROM ".DPS"
//----------------------------------------------------------


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

    #define DNG_EXT_FROM ".CR2"
    #define CAM_MULTIPART               1
//----------------------------------------------------------

#elif defined (CAMERA_sx10)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              3720   
    #define CAM_RAW_ROWS                2772   

    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON       1
    #define CAM_VIDEO_QUALITY_ONLY          1  
    #define CAM_BRACKETING              1 
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 6
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 3690
    #define CAM_ACTIVE_AREA_Y2 2772
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #define CAM_EXT_TV_RANGE            1
//----------------------------------------------------------

#elif defined (CAMERA_sx1)
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4152 
    #define CAM_RAW_ROWS                2772  

    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_HAS_VIDEO_BUTTON       1
    #define CAM_VIDEO_QUALITY_ONLY          1  
    #define CAM_BRACKETING              1 
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 344
    #define CAM_ACTIVE_AREA_Y1 24
    #define CAM_ACTIVE_AREA_X2 3991
    #define CAM_ACTIVE_AREA_Y2 2759  
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127
 
    #define CAM_EXT_TV_RANGE            1
 
    #define CAM_HAS_VARIABLE_ASPECT 1 
//---------------------------------------------------------- 

	//********
	/////SX110
	//********
#elif defined (CAMERA_sx110is)
	#define CAM_COLORMATRIX1                               \
      530200, 1000000, -42600,  1000000, -33000,  1000000, \
     -525400,  1000000, 1092700,  1000000,  223700,  1000000, \
     -103700,  1000000, 117900,   1000000,  421600,  1000000
    #define CAM_ACTIVE_AREA_X1 8
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3688
    #define CAM_ACTIVE_AREA_Y2 2772

    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1
    #define CAM_RAW_ROWPIX              3720  
    #define CAM_RAW_ROWS                2772  
    #undef CAM_SYNCH 
    #define CAM_CAN_MUTE_MICROPHONE     1 
    #define CAM_SHOW_OSD_IN_SHOOT_MENU  1
    #define CAM_REAR_CURTAIN            1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1 
    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_USE_ZOOM_FOR_MF
	#undef CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
	#undef CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	// black level set to 128 per reports on the forum
    #undef  CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             128
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    #define cam_CalibrationIlluminant1 1 // Daylight
    #define CAM_JPEG_WIDTH  3456 
    #define CAM_JPEG_HEIGHT 2592
//----------------------------------------------------------

	//********
	/////SX200
	//********
#elif defined (CAMERA_sx200is)
    // copied from SX10 and modified
    #define CAM_PROPSET                 2
    #define CAM_DRYOS                   1
    #define CAM_RAW_ROWPIX              4080 // from calcs see 100C lib.c 
    #define CAM_RAW_ROWS                3048 //  "     "    "    "    "  
    
    #undef  CAM_CAN_SD_OVER_NOT_IN_MF
    #undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1

    #define CAM_VIDEO_QUALITY_ONLY          1  

    #undef  CAM_VIDEO_CONTROL
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                               \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
     -1991,  1000000, 10719,  1000000, 1273,   1000000, \
      -1158,   1000000, 1929,   1000000, 3581,  1000000

    #define cam_CalibrationIlluminant1 17 // Standard Light A
    // cropping
    #define CAM_JPEG_WIDTH  4000
    #define CAM_JPEG_HEIGHT 3000
    #define CAM_ACTIVE_AREA_X1 52
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 4052
    #define CAM_ACTIVE_AREA_Y2 3014
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #define CAM_EXT_TV_RANGE            1
    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    3
    #undef CAM_HAS_ERASE_BUTTON
    #define  CAM_SHOW_OSD_IN_SHOOT_MENU  1
        
    //nandoide sept-2009
    #undef CAM_USES_ASPECT_CORRECTION   
    #undef CAM_USES_ASPECT_YCORRECTION  
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate

// reyalp TODO not sure this stuff belongs in camera.h there will probably only be a few different setups
// maybe we can just have one CAM_ options that picks what to use ?
// values need to be better documented
	// reyalp - I guess these are bitmap ?
    //default mappings
    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )   //correction x*screen_buffer_width/screen_width = x*720/320 = x*9/4 = (x<<3 + x)>>2
    
    //grids
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.
    
    //viewport
    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) ) 
    #undef EDGE_HMARGIN 
    #define EDGE_HMARGIN 28
    
    //games mappings
   #undef GAMES_SCREEN_WIDTH
   #undef GAMES_SCREEN_HEIGHT
   #define GAMES_SCREEN_WIDTH 360
   #define GAMES_SCREEN_HEIGHT 240
   #undef ASPECT_GAMES_XCORRECTION
   // 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
   // used by gui.c that configures the draw environment (through new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
   // other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
   #define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )  
   #undef ASPECT_GAMES_YCORRECTION
   #define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

   //zebra letterbox for saving memory
   #undef ZEBRA_HMARGIN0
   #define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).

   //end nandoide sept-2009
   #define CAM_QUALITY_OVERRIDE 1
   #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
   #define CAM_ZEBRA_ASPECT_ADJUST 1
    #define  CAM_CHDK_PTP               1 // include CHDK PTP support
//----------------------------------------------------------

#elif defined (CAMERA_g11)
    #define CAM_DRYOS_2_3_R39			1
    #define CAM_PROPSET                 3
    #define CAM_DRYOS                   1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_RAW_ROWPIX              3744   // See g11 lib.c
    #define CAM_RAW_ROWS                2784   // See g11 lib.c
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10

    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	10

	#define CAM_QUALITY_OVERRIDE 1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL             1
    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_BRACKETING              1
    #define CAM_MULTIPART               1
    #define CAM_EXT_TV_RANGE            1
    #undef OPT_CURVES
    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000  // G11 @FF888204(via ExMem.FreeCacheable)

	#define CAM_SWIVEL_SCREEN			1
	#define CAM_SHOW_OSD_IN_SHOOT_MENU  1

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #undef CAM_USES_ASPECT_CORRECTION   
    #undef CAM_USES_ASPECT_YCORRECTION  
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate
    //games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH 360
	#define GAMES_SCREEN_HEIGHT 240

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    4


    #undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )
	#undef ASPECT_GAMES_XCORRECTION 
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )  
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) ) 
    #undef EDGE_HMARGIN 
    #define EDGE_HMARGIN 28

	/**** From SX200IS, ok for G11 ?*/
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                               \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
     -1991,  1000000, 10719,  1000000, 1273,   1000000, \
      -1158,   1000000, 1929,   1000000, 3581,  1000000
    #define cam_CalibrationIlluminant1 17 // Standard Light A

    // cropping
	//g11 values from Amit Talwar
    #define CAM_JPEG_WIDTH  3648
    #define CAM_JPEG_HEIGHT 2736
    #define CAM_ACTIVE_AREA_X1 16
    #define CAM_ACTIVE_AREA_Y1 8
    #define CAM_ACTIVE_AREA_X2 3692
    #define CAM_ACTIVE_AREA_Y2 2776
	
	  /**** From SX200IS, ok for G11 END?*/
   #define CAM_ZEBRA_ASPECT_ADJUST 1
//----------------------------------------------------------

#elif defined (CAMERA_s90)
    #define CAM_DRYOS_2_3_R39			1
    #define CAM_PROPSET                 3
    #define CAM_DRYOS                   1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_RAW_ROWPIX              3744   // See g11 lib.c
    #define CAM_RAW_ROWS                2784   // See g11 lib.c
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10

    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	10

	#define CAM_QUALITY_OVERRIDE 1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL             1
	#undef CAM_HAS_ERASE_BUTTON
    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_BRACKETING              1
    #define CAM_MULTIPART               1
    #define CAM_EXT_TV_RANGE            1
    #undef OPT_CURVES
    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000  // S90 @FF8875FC(via ExMem.FreeCacheable)

	#define CAM_SHOW_OSD_IN_SHOOT_MENU  1

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #undef CAM_USES_ASPECT_CORRECTION   
    #undef CAM_USES_ASPECT_YCORRECTION  
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate
    //games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH 360
	#define GAMES_SCREEN_HEIGHT 240

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    4

    #undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )
	#undef ASPECT_GAMES_XCORRECTION 
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )  
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

    #undef ASPECT_VIEWPORT_XCORRECTION 
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION 
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) ) 
    #undef EDGE_HMARGIN 
    #define EDGE_HMARGIN 28

	/**** From SX200IS, ok for S90 ?*/
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                               \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
     -1991,  1000000, 10719,  1000000, 1273,   1000000, \
      -1158,   1000000, 1929,   1000000, 3581,  1000000
    #define cam_CalibrationIlluminant1 17 // Standard Light A

    // cropping -> G11
    #define CAM_JPEG_WIDTH              3648
    #define CAM_JPEG_HEIGHT             2736
    #define CAM_ACTIVE_AREA_X1          16
    #define CAM_ACTIVE_AREA_Y1          8
    #define CAM_ACTIVE_AREA_X2          3692
    #define CAM_ACTIVE_AREA_Y2          2776
    /**** From SX200IS, ok for S90 END?*/

   #define CAM_ZEBRA_ASPECT_ADJUST 1
//----------------------------------------------------------

#elif defined (CAMERA_sx20)
	#define CAM_PROPSET					3
	#define CAM_DRYOS					1
	#define CAM_DRYOS_2_3_R39			1

	#define CAM_RAW_ROWPIX				4080
	#define CAM_RAW_ROWS				3048

	#define CAM_SWIVEL_SCREEN			1
	#define CAM_ADJUSTABLE_ALT_BUTTON	1
	#undef  CAM_CAN_SD_OVER_NOT_IN_MF
	#undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
	#define CAM_HAS_VIDEO_BUTTON		1
	#define CAM_VIDEO_QUALITY_ONLY		1
	#define CAM_BRACKETING				1
	#undef  CAM_VIDEO_CONTROL
	#define CAM_MULTIPART				1
	#define CAM_HAS_JOGDIAL				1
	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_UNCACHED_BIT			// shut up compiler
	#define CAM_UNCACHED_BIT			0x40000000

	// pattern
	#define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
	// color

	#define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
      -12829, 1000000,  530507, 1000000,   50537, 1000000, \
        5181, 1000000,   48183, 1000000,  245014, 1000000

	#define cam_CalibrationIlluminant1	1 // Daylight
	// cropping
	#define CAM_JPEG_WIDTH				4000
	#define CAM_JPEG_HEIGHT				3000
	#define CAM_ACTIVE_AREA_X1			24
	#define CAM_ACTIVE_AREA_Y1			12
	#define CAM_ACTIVE_AREA_X2			4080-48
	#define CAM_ACTIVE_AREA_Y2			3048-24
	// camera name
	#define PARAM_CAMERA_NAME			4 // parameter number for GetParameterData
	#undef  CAM_SENSOR_BITS_PER_PIXEL
	#undef  CAM_WHITE_LEVEL
	#undef  CAM_BLACK_LEVEL
	#define CAM_SENSOR_BITS_PER_PIXEL	12
	#define CAM_WHITE_LEVEL				((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	#define CAM_BLACK_LEVEL				127

	#define CAM_EXT_TV_RANGE			1
	#define CAM_QUALITY_OVERRIDE		1

	// copied from the SX200 which has the same video buffer size
	#undef CAM_USES_ASPECT_CORRECTION
	#undef CAM_USES_ASPECT_YCORRECTION
	#define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
	#define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

	#undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )  //correction x*screen_buffer_width/screen_width = x*720/320 = x*9/4 = (x<<3 + x)>>2

	#undef ASPECT_GRID_XCORRECTION
	#define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
	#undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )  //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

	#undef ASPECT_VIEWPORT_XCORRECTION 
	#define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
	#undef ASPECT_VIEWPORT_YCORRECTION 
	#define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240
	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (trhough new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #define CAM_ZEBRA_ASPECT_ADJUST 1
    #define CAM_ZEBRA_NOBUF 1

	#undef CAM_BITMAP_PALETTE
	#define CAM_BITMAP_PALETTE		6

   //zebra letterbox for saving memory
   #undef ZEBRA_HMARGIN0
   #define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).
  
   #undef EDGE_HMARGIN
   #define EDGE_HMARGIN 28
   #define CAM_CHDK_PTP 1
//----------------------------------------------------------

#elif defined (CAMERA_s95)
    #define CAM_DRYOS_2_3_R39			1
    #define CAM_PROPSET                 4
    #define CAM_DRYOS                   1
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_RAW_ROWPIX              3744
    #define CAM_RAW_ROWS                2784
    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10
    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	10
	#define CAM_QUALITY_OVERRIDE 1
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_HAS_JOGDIAL             1
	#undef CAM_HAS_ERASE_BUTTON
    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_BRACKETING              1
	#undef  CAM_VIDEO_CONTROL
	#define CAM_VIDEO_QUALITY_ONLY		1
    #define CAM_MULTIPART               1
    #define CAM_EXT_TV_RANGE            1
    #undef OPT_CURVES
    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000  // S94 100E @FF89100C
	#define CAM_SHOW_OSD_IN_SHOOT_MENU  1

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #undef  CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #undef  CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate

    //games mappings
	#undef GAMES_SCREEN_WIDTH
	#define GAMES_SCREEN_WIDTH 360
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_HEIGHT 240

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    7

    #undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )
	#undef ASPECT_GAMES_XCORRECTION
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

    #undef ASPECT_VIEWPORT_XCORRECTION
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )
    #undef EDGE_HMARGIN
    #define EDGE_HMARGIN 28

    #define DNG_SUPPORT    1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                               \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
     -1991,  1000000, 10719,  1000000, 1273,   1000000, \
      -1158,   1000000, 1929,   1000000, 3581,  1000000
    #define cam_CalibrationIlluminant1 17 // Standard Light A

    // cropping
    #define CAM_JPEG_WIDTH  3600
    #define CAM_JPEG_HEIGHT 2700
    #define CAM_ACTIVE_AREA_X1 52
    #define CAM_ACTIVE_AREA_Y1 14
    #define CAM_ACTIVE_AREA_X2 3648
    #define CAM_ACTIVE_AREA_Y2 2736

   #define CAM_ZEBRA_ASPECT_ADJUST 1

   // todo - we may need this to save memory
    //#define CAM_ZEBRA_NOBUF 1
//==========================================================
// END of Camera-dependent settings
//==========================================================

#elif defined (CAMERA_sx30)
	#define CAM_PROPSET					4
	#define CAM_DRYOS					1
	#define CAM_DRYOS_2_3_R39			1

	#define CAM_RAW_ROWPIX				4464
	#define CAM_RAW_ROWS				3276

	#define CAM_SWIVEL_SCREEN			1
	#define CAM_ADJUSTABLE_ALT_BUTTON	1
	#undef  CAM_CAN_SD_OVER_NOT_IN_MF
	#undef  CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO
	#define CAM_HAS_VIDEO_BUTTON		1
	#define CAM_VIDEO_QUALITY_ONLY		1
	#define CAM_BRACKETING				1
	#undef  CAM_VIDEO_CONTROL
	#define CAM_MULTIPART				1
	#define CAM_HAS_JOGDIAL				1
	#undef  CAM_USE_ZOOM_FOR_MF
	#undef  CAM_UNCACHED_BIT			// shut up compiler
	#define CAM_UNCACHED_BIT			0x40000000

	// pattern
	#define cam_CFAPattern 0x01000201 // Green  Blue  Red  Green
	// color

	// TODO - Still needs work 
	#define cam_CalibrationIlluminant1	1 // Daylight

	#define CAM_COLORMATRIX1                               \
	  1301431, 1000000,  -469837, 1000000, -102652, 1000000, \
	  -200195, 1000000,   961551, 1000000,  238645, 1000000, \
	   -16441, 1000000,   142319, 1000000,  375979, 1000000

	// cropping
	#define CAM_JPEG_WIDTH				4368 //4320
	#define CAM_JPEG_HEIGHT				3254 //3240
	#define CAM_ACTIVE_AREA_X1			24
	#define CAM_ACTIVE_AREA_Y1			10
	#define CAM_ACTIVE_AREA_X2			(4464-72)
	#define CAM_ACTIVE_AREA_Y2			(3276-12)
	// camera name
	#define PARAM_CAMERA_NAME			4 // parameter number for GetParameterData
	#undef  CAM_SENSOR_BITS_PER_PIXEL
	#undef  CAM_WHITE_LEVEL
	#undef  CAM_BLACK_LEVEL
	#define CAM_SENSOR_BITS_PER_PIXEL	12
	#define CAM_WHITE_LEVEL				((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
	#define CAM_BLACK_LEVEL				127

	#define CAM_EXT_TV_RANGE			1
	#define CAM_QUALITY_OVERRIDE		1

	// copied from the SX200 which has the same video buffer size
	#undef CAM_USES_ASPECT_CORRECTION
	#undef CAM_USES_ASPECT_YCORRECTION
	#define CAM_USES_ASPECT_CORRECTION		1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized 
	#define CAM_USES_ASPECT_YCORRECTION		0  //only uses mappings on x coordinate

	#undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )  //correction x*screen_buffer_width/screen_width = x*720/320 = x*9/4 = (x<<3 + x)>>2

	#undef ASPECT_GRID_XCORRECTION
	#define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
	#undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )  //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

	#undef ASPECT_VIEWPORT_XCORRECTION 
	#define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
	#undef ASPECT_VIEWPORT_YCORRECTION 
	#define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )

	#undef ASPECT_GAMES_XCORRECTION
	// 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
	// used by gui.c that configures the draw environment (trhough new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
	// other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

	//games mappings
	#undef GAMES_SCREEN_WIDTH
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_WIDTH		360
	#define GAMES_SCREEN_HEIGHT		240

    #define CAM_ZEBRA_ASPECT_ADJUST 1
    #define CAM_ZEBRA_NOBUF 1

	#undef CAM_BITMAP_PALETTE
	#define CAM_BITMAP_PALETTE		7

   //zebra letterbox for saving memory
   #undef ZEBRA_HMARGIN0
   #define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).
  
   #undef EDGE_HMARGIN
   #define EDGE_HMARGIN 2
   #define CAM_CHDK_PTP 1
	
	#define	CAM_DATE_FOLDER_NAMING	1

	// EXMEM memory allocation values
	#define EXMEM_HEAP_SKIP (0x08000000-0x07D08A00)			// G12 & SX30 uses movie memory buffers at the top of the memory allocated by exmem_alloc
	#define EXMEM_BUFFER_SIZE (1024*1024*2)					// desired amount of exmem memory to allocate

//----------------------------------------------------------
#elif defined (CAMERA_g12)
    #define CAM_PROPSET                 4
    #define CAM_DRYOS                   1
    #define CAM_DRYOS_2_3_R39			1

    #define CAM_RAW_ROWPIX              3744
    #define CAM_RAW_ROWS                2784

	#define CAM_SWIVEL_SCREEN			1
	//#define CAM_ADJUSTABLE_ALT_BUTTON	1

    #undef  CAM_EMUL_KEYPRESS_DURATION
    #define CAM_EMUL_KEYPRESS_DURATION  10
    #undef CAM_MENU_BORDERWIDTH
    #define CAM_MENU_BORDERWIDTH	10
    #define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_MULTIPART               1
    #define CAM_HAS_JOGDIAL             1
	#undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_CONSOLE_LOG_ENABLED         // Development: internal camera stdout -> A/stdout.txt
    #define CAM_BRACKETING              1
	#undef  CAM_VIDEO_CONTROL
	#define CAM_VIDEO_QUALITY_ONLY		1
    #define CAM_EXT_TV_RANGE            1
	#define CAM_QUALITY_OVERRIDE 1
    #undef OPT_CURVES
    #undef CAM_UNCACHED_BIT
    #define CAM_UNCACHED_BIT            0x40000000  // S90 @FF8875FC(via ExMem.FreeCacheable)
	#define CAM_SHOW_OSD_IN_SHOOT_MENU  1

    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #undef  CAM_WHITE_LEVEL
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #undef  CAM_BLACK_LEVEL
    #define CAM_BLACK_LEVEL             127

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    7

    #undef CAM_USES_ASPECT_CORRECTION
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate

    #undef ASPECT_XCORRECTION
	#define ASPECT_XCORRECTION(x)  ( ( ((x)<<3) + (x) )  >>2 )

    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( ((x)<<3)/9  )  //grids are designed on a 360x240 basis and screen is 320x240, we need x*320/360=x*8/9
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

    #undef ASPECT_VIEWPORT_XCORRECTION
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION
    #define ASPECT_VIEWPORT_YCORRECTION(y) (y)

    #undef EDGE_HMARGIN
    #define EDGE_HMARGIN 2

    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color
    //need fixing *****************************************************
    #define CAM_COLORMATRIX1                               \
      14134, 1000000, -5576, 1000000, -1527, 1000000, \
     -1991,  1000000, 10719,  1000000, 1273,   1000000, \
      -1158,   1000000, 1929,   1000000, 3581,  1000000
    #define cam_CalibrationIlluminant1 17 // Standard Light A

    // cropping
    #define CAM_JPEG_WIDTH  3684
    #define CAM_JPEG_HEIGHT 2760
    #define CAM_ACTIVE_AREA_X1 52
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 (CAM_RAW_ROWPIX-8)
    #define CAM_ACTIVE_AREA_Y2 (CAM_RAW_ROWS-12)

	#undef ASPECT_GAMES_XCORRECTION
	#define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
	#undef ASPECT_GAMES_YCORRECTION
	#define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

    //games mappings
	#undef GAMES_SCREEN_WIDTH
	#define GAMES_SCREEN_WIDTH 360
	#undef GAMES_SCREEN_HEIGHT
	#define GAMES_SCREEN_HEIGHT 240

	#define CAM_ZEBRA_ASPECT_ADJUST 1

   //zebra letterbox for saving memory
   #undef ZEBRA_HMARGIN0
   #define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).
	
	#define	CAM_DATE_FOLDER_NAMING	1

	#define CAM_CHDK_PTP 1

	// EXMEM memory allocation values
	#define EXMEM_HEAP_SKIP (0x08000000-0x07D08A00)			// G12 & SX30 uses movie memory buffers at the top of the memory allocated by exmem_alloc
	#define EXMEM_BUFFER_SIZE (1024*1024*2)					// desired amount of exmem memory to allocate

//----------------------------------------------------------

#elif defined (CAMERA_ixus120_sd940)
	#define CAM_DRYOS_2_3_R39			1  //stat is different, as well as some other functions
	#define SYNCHABLE_REMOTE_NOT_ENABLED 1
    #define CAM_PROPSET                 3
    #define CAM_DRYOS                   1

    #define CAM_RAW_ROWPIX              4080  //  12M 41044080 ?? // from calcs see 100C lib.c
    #define CAM_RAW_ROWS                3048  //  "     "    "    "    "
											
    #undef CAM_SWIVEL_SCREEN
    #undef CAM_ADJUSTABLE_ALT_BUTTON
    #define CAM_CAN_SD_OVER_NOT_IN_MF	1
    #define CAM_CAN_UNLOCK_OPTICAL_ZOOM_IN_VIDEO 1
    #undef CAM_HAS_VIDEO_BUTTON
    #define CAM_VIDEO_QUALITY_ONLY          1
	#define CAM_AF_SCAN_DURING_VIDEO_RECORD 1
    #define CAM_BRACKETING              1
    #undef  CAM_VIDEO_CONTROL
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_MULTIPART               1
    #undef CAM_HAS_JOGDIAL
    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_UNCACHED_BIT  // shut up compiler
    #define CAM_UNCACHED_BIT    0x40000000
    #define CAM_HAS_ND_FILTER           1
    #define CAM_CAN_SD_OVERRIDE         1

    #define DNG_SUPPORT                 1
    // pattern
    #define cam_CFAPattern 0x02010100 // Red  Green  Green  Blue
    // color

    #undef CAM_BITMAP_PALETTE
    #define CAM_BITMAP_PALETTE    3  

    #define CAM_COLORMATRIX1                               \
      827547, 1000000, -290458, 1000000, -126086, 1000000, \
     -12829,  1000000, 530507,  1000000, 50537,   1000000, \
      5181,   1000000, 48183,   1000000, 245014,  1000000

    #define cam_CalibrationIlluminant1 1 // Daylight
    // cropping
    #define CAM_JPEG_WIDTH  4000
    #define CAM_JPEG_HEIGHT 3000
    #define CAM_ACTIVE_AREA_X1 20
    #define CAM_ACTIVE_AREA_Y1 12
    #define CAM_ACTIVE_AREA_X2 4056
    #define CAM_ACTIVE_AREA_Y2 3038
    // camera name
    #define PARAM_CAMERA_NAME 4 // parameter number for GetParameterData
    #undef  CAM_SENSOR_BITS_PER_PIXEL
    #undef  CAM_WHITE_LEVEL
    #undef  CAM_BLACK_LEVEL
    #define CAM_SENSOR_BITS_PER_PIXEL   12
    #define CAM_WHITE_LEVEL             ((1<<CAM_SENSOR_BITS_PER_PIXEL)-1)
    #define CAM_BLACK_LEVEL             127

    #define CAM_EXT_TV_RANGE            1

    #define  CAM_SHOW_OSD_IN_SHOOT_MENU  1

    //nandoide sept-2009
    #undef CAM_USES_ASPECT_CORRECTION
    #undef CAM_USES_ASPECT_YCORRECTION
    #define CAM_USES_ASPECT_CORRECTION  1  //camera uses the modified graphics primitives to map screens an viewports to buffers more sized
    #define CAM_USES_ASPECT_YCORRECTION  0  //only uses mappings on x coordinate


    #undef ASPECT_XCORRECTION
    #define ASPECT_XCORRECTION(x)  (((x)<<1))   //correction x*screen_buffer_width/screen_width 
    #undef ASPECT_GRID_XCORRECTION
    #define ASPECT_GRID_XCORRECTION(x)  ( (x) )  //grids are designed on a 360x240 basis 
    #undef ASPECT_GRID_YCORRECTION
    #define ASPECT_GRID_YCORRECTION(y)  ( (y) )       //y correction for grids  made on a 360x240 As the buffer is 720x240 we have no correction here.

    #undef ASPECT_VIEWPORT_XCORRECTION
    #define ASPECT_VIEWPORT_XCORRECTION(x) ASPECT_GRID_XCORRECTION(x) //viewport is 360x240 and screen 320x240, we need x*320/360=x*8/9, equal than grids, used by edgeoverlay
    #undef ASPECT_VIEWPORT_YCORRECTION
    #define ASPECT_VIEWPORT_YCORRECTION(y) ( (y) )
    #undef EDGE_HMARGIN
    #define EDGE_HMARGIN 20

    //games mappings
	// renamed GAMES_SCREEN_WIDTH / GAMES_SCREEN_HEIGHT
   #undef GAMES_SCREEN_WIDTH
   #undef GAMES_SCREEN_HEIGHT
   #define GAMES_SCREEN_WIDTH 360
   #define GAMES_SCREEN_HEIGHT 240
   #undef ASPECT_GAMES_XCORRECTION
   // 720/360=2 same aspect than grids and viewport but another approach: there is a lot of corrections to do in game's code, and we decide to paint directly on display buffer wirh another resolution
   // used by gui.c that configures the draw environment (trhough new draw_gui function) depending on gui_mode: we have then 360x240 for games (but deformed output:circles are not circles) and 320x240 for
   // other modes in perfect aspect ratio 4/3: slightly better visualization: file menus more readable, ...
   #define ASPECT_GAMES_XCORRECTION(x)   ( ((x)<<1) )
   #undef ASPECT_GAMES_YCORRECTION
   #define ASPECT_GAMES_YCORRECTION(y)   ( (y) )  //none

   //zebra letterbox for saving memory

   #undef ZEBRA_HMARGIN0
   #define ZEBRA_HMARGIN0  30 //this 30 rows are not used by the display buffer is 720x240 effective, no 960x270, i.e. (270-240) reduction in widht possible but not done (more difficult to manage it and slower).

   #define CAM_ZEBRA_ASPECT_ADJUST 1
   #define CAM_ZEBRA_NOBUF 1
   
   #define CAM_CHDK_PTP 1

   //----------------------------------------------------------

#else
	#error camera type not defined
#endif
//==========================================================
// END of Camera-dependent settings
//==========================================================


// curves only work in 10bpp for now
#if CAM_SENSOR_BITS_PER_PIXEL != 10
#undef OPT_CURVES
#endif

#ifndef OPT_PTP
#undef CAM_CHDK_PTP
#endif

#endif /* CAMERA_H */
