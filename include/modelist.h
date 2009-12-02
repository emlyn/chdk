#ifndef MODELIST_H
#define MODELIST_H
/*
CHDK capture mode constants.
WARNING: This file is used with gen_modelist_lua.sed to generate modelist.lua
WARNING: These are used for platform independent script values. 
DO NOT CHANGE THE ORDER OR REMOVE VALUES. ADD NEW VALUES AT THE END

0 is used as an invalid value
not every value is valid on every camera
on cameras where the setting called manual is actually a P mode, use MODE_P in the modemap
*/
enum {
MODE_AUTO               =1,
MODE_P                  ,
MODE_TV                 ,
MODE_AV                 ,
MODE_M                  ,
MODE_PORTRAIT           ,
MODE_NIGHT              ,
MODE_LANDSCAPE          ,
MODE_VIDEO_STD          ,
MODE_VIDEO_SPEED        ,
MODE_VIDEO_COMPACT      ,
MODE_VIDEO_MY_COLORS    ,
MODE_VIDEO_COLOR_ACCENT ,
MODE_VIDEO_COLOR_SWAP   ,
MODE_STITCH             ,
MODE_MY_COLORS          ,
MODE_SCN_WATER          ,
MODE_SCN_NIGHT          ,
MODE_SCN_CHILD          ,
MODE_SCN_PARTY          ,
MODE_SCN_GRASS          ,
MODE_SCN_SNOW           ,
MODE_SCN_BEACH          ,
MODE_SCN_FIREWORK       ,
MODE_SCN_COLOR_ACCENT   ,
MODE_SCN_COLOR_SWAP     ,
MODE_VIDEO_HIRES        ,
MODE_SCN_AQUARIUM       ,
MODE_COLOR_ACCENT       ,
MODE_SCN_NIGHT1         ,
MODE_SCN_ISO_3200       ,
MODE_SCN_SPORT          ,
MODE_SCN_KIDS_PETS      ,
MODE_INDOOR             ,
MODE_KIDS_PETS          ,
MODE_NIGHT_SNAPSHOT     ,
MODE_DIGITAL_MACRO      ,
MODE_SCN_FOLIAGE        ,
MODE_VIDEO_TIME_LAPSE   ,
MODE_SCN_INDOOR         ,
MODE_SCN_PORTRAIT       ,
MODE_SUPER_MACRO        ,
MODE_VIDEO_PORTRAIT     ,
MODE_VIDEO_NIGHT        ,
MODE_VIDEO_INDOOR       ,
MODE_VIDEO_FOLIAGE      ,
MODE_VIDEO_SNOW         ,
MODE_VIDEO_BEACH        ,
MODE_VIDEO_AQUARIUM     ,
MODE_VIDEO_SUPER_MACRO  ,
MODE_VIDEO_STITCH       ,
MODE_VIDEO_MANUAL       ,
MODE_SPORTS             ,
MODE_QUICK			    ,
MODE_SCN_SUNSET         ,
MODE_SCN_UNDERWATER     ,
MODE_EASY               ,
MODE_SCN_DIGITAL_MACRO  ,
MODE_SCN_STITCH         ,
};
#endif
