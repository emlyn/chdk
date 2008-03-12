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
    
    #undef  CAM_DIGIC2                      // Camera is based on Digic-II processor
    #undef  CAM_DIGIC3                      // Camera is based on Digic-III processor
    
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






//----------------------------------------------------------
// Overrided values for each camera
//----------------------------------------------------------

//==========================================================
// G-series
//==========================================================
#if   defined (CAMERA_g7)
    #define CAM_DIGIC2                  1       //???

    #define CAM_RAW_ROWPIX              3736   // for 10 MP
    #define CAM_RAW_ROWS                2772   // for 10 MP
    
    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_MULTIPART               1
    #define CAM_HAS_ND_FILTER           1
    

//==========================================================
// A-series
//==========================================================
#elif defined (CAMERA_a460)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              2664   // for 5 MP 1/3" sensor size
    #define CAM_RAW_ROWS                1968   // for 5 MP 1/3" sensor size

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ZOOM_LEVER
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    
//----------------------------------------------------------
#elif defined (CAMERA_a550)
    #define CAM_DIGIC3                  1       //???

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_a560)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_REMOTE
    #define CAM_MULTIPART               1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM

//----------------------------------------------------------
#elif defined (CAMERA_a570)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP
    #define CAM_MULTIPART               1
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_a610)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #define CAM_SWIVEL_SCREEN           1


//----------------------------------------------------------
#elif defined (CAMERA_a620)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP
    
    #define CAM_SWIVEL_SCREEN           1


//----------------------------------------------------------
#elif defined (CAMERA_a630)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              3344   // for 8 MP
    #define CAM_RAW_ROWS                2484   // for 8 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_MULTIPART               1


//----------------------------------------------------------
#elif defined (CAMERA_a640)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              3736   // for 10 MP
    #define CAM_RAW_ROWS                2772   // for 10 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_MULTIPART               1


//----------------------------------------------------------
#elif defined (CAMERA_a650)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              4104   // for 12 MP
    #define CAM_RAW_ROWS                3048   // for 12 MP
    
    #define CAM_SWIVEL_SCREEN           1


//----------------------------------------------------------
#elif defined (CAMERA_a700)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_REMOTE

//----------------------------------------------------------
#elif defined (CAMERA_a710)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #define CAM_MULTIPART               1
    #define CAM_HAS_ND_FILTER           1      // really ???

//----------------------------------------------------------
#elif defined (CAMERA_a720)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP


//==========================================================
// SD-Series (IXUS-Series)
//==========================================================
#elif defined (CAMERA_ixus55_sd450)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_ixus65_sd630)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_ixus70_sd1000)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_ixus700_sd500)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_ixus800_sd700)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_ixus850_sd800)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              3152   // for 7 MP
    #define CAM_RAW_ROWS                2340   // for 7 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #define CAM_DRAW_EXPOSITION         1
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//----------------------------------------------------------
#elif defined (CAMERA_ixus950_sd850)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP

    #undef  CAM_USE_ZOOM_FOR_MF
    #undef  CAM_HAS_ERASE_BUTTON
    #undef  CAM_HAS_IRIS_DIAPHRAGM
    #define CAM_HAS_ND_FILTER           1

//==========================================================
// S-Series
//==========================================================
#elif defined (CAMERA_s2is)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2672   // for 5 MP
    #define CAM_RAW_ROWS                1968   // for 5 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1


//----------------------------------------------------------
#elif defined (CAMERA_s3is)
    #define CAM_DIGIC2                  1

    #define CAM_RAW_ROWPIX              2888   // for 6 MP
    #define CAM_RAW_ROWS                2136   // for 6 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1
    #define CAM_MULTIPART               1


//----------------------------------------------------------
#elif defined (CAMERA_s5is)
    #define CAM_DIGIC3                  1

    #define CAM_RAW_ROWPIX              3336   // for new 8 MP
    #define CAM_RAW_ROWS                2480   // for new 8 MP
    
    #define CAM_SWIVEL_SCREEN           1
    #define CAM_ADJUSTABLE_ALT_BUTTON   1


//----------------------------------------------------------
#else
#error camera type not defined
#endif

#endif
