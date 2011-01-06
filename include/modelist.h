#ifndef MODELIST_H
#define MODELIST_H

/*
CHDK capture mode constants.
WARNING: This file is used with gen_modelist_lua.sed to generate modelist.lua
WARNING: These are used for platform independent script values.
Changing order or inserting new values will break script compatibility.
ADD NEW VALUES AT THE END!

0 is used as an invalid value
not every value is valid on every camera

Single line comments on the enum values will be carried over to lua

modemap notes:
- On cameras where the "manual" mode only allows +/- ev, rather than direct shutter
control, it should be mapped to P, not M
- Modes should be mapped to an enum value that matches their canon name. This is
displayed as a string when the mode is set, and can also be found in canon
manuals and spec lists. If in doubt refer to the canon manuals for description of
the modes function, and compare with existing cameras. Add a new enum value at the
end of the list if it doesn't closely match any existing function.
- Currently, modes under the SCN menu are given the SCN prefix, even if an equivalent
non-scene constant already exists.
- Some cameras have C, or C1 and C2 modes. These are not actual shooting modes, but
are used to load saved settings for other modes like M, P etc. These modes can be
set using _SetCurrrentCaptureMode, but are not currently supported by the modemap
system. If a C mode is set this way, the propcase used for PROPCASE_SHOOTING_MODE
on propset 2 cameras (49) reflects the actual mode. Propcase 50 appears to show the
set mode. Propset 1 behavior is unknown.
- Although canon mode values are similar between many cameras, they are not always the same!
- a list of valid canon modes can be found in the firmware, see existing cameras
for examples. This can be found several function calls after a reference to the
string AC:PTM_Init or similar
*/
enum {
    MODE_AUTO               =1,
    MODE_P                  , // Called "camera manual" on many cameras without a true manual mode, only allows +/- Ev adjustment
    MODE_TV                 ,
    MODE_AV                 ,
    MODE_M                  , // note, use only for true manual modes that allow direct control of Tv/Av
    MODE_PORTRAIT           ,
    MODE_NIGHT_SCENE        , // "night scene" mode. Note, this can be a dail position, or under the scene menu (SCN_NIGHT_SCENE).
    MODE_LANDSCAPE          ,
    MODE_VIDEO_STD          ,
    MODE_VIDEO_SPEED        ,
    MODE_VIDEO_COMPACT      ,
    MODE_VIDEO_MY_COLORS    ,
    MODE_VIDEO_COLOR_ACCENT ,
    MODE_VIDEO_COLOR_SWAP   ,
    MODE_STITCH             ,
    MODE_MY_COLORS          ,
    MODE_SCN_UNDERWATER     ,
    MODE_SCN_NIGHT_SNAPSHOT ,
    MODE_LONG_SHUTTER       , // "long shutter" mode on cameras without true manual mode. Allows manual shutter >= 1 second, uses manual shutter value propcase. Usually found under func menu in "manual" mode.
    MODE_SCN_LANDSCAPE      ,
    MODE_COLOR_SWAP         ,
    MODE_SCN_SNOW           ,
    MODE_SCN_BEACH          ,
    MODE_SCN_FIREWORK       ,
    MODE_SCN_COLOR_ACCENT   ,
    MODE_SCN_COLOR_SWAP     ,
    MODE_VIDEO_HIRES        ,
    MODE_SCN_AQUARIUM       ,
    MODE_COLOR_ACCENT       ,
    MODE_SCN_NIGHT_SCENE    ,
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
    MODE_VIDEO_PORTRAIT     , // tx1 junk
    MODE_VIDEO_NIGHT        , // tx1 junk
    MODE_VIDEO_INDOOR       , // tx1 junk
    MODE_VIDEO_FOLIAGE      , // tx1 junk
    MODE_VIDEO_SNOW         , // tx1 junk
    MODE_VIDEO_BEACH        , // tx1 junk
    MODE_VIDEO_AQUARIUM     , // tx1 junk
    MODE_VIDEO_SUPER_MACRO  , // tx1 junk
    MODE_VIDEO_STITCH       , // tx1 junk
    MODE_VIDEO_MANUAL       , // tx1 junk
    MODE_SPORTS             ,
    MODE_QUICK              ,
    MODE_SCN_SUNSET         ,
    MODE_SCN_CREATIVE_EFFECT, // "creative light effect", only known on ixus950_sd850
    MODE_EASY               ,
    MODE_SCN_DIGITAL_MACRO  ,
    MODE_SCN_STITCH         ,
    MODE_SCN_LONG_SHUTTER   , // only known on sx1, d10
    MODE_LOWLIGHT           , // g11
    MODE_SCN_NOSTALGIC      , // s90
	MODE_SCN_SMART_SHUTTER	, // sx30
	MODE_SCN_LOWLIGHT		, // sx30
	MODE_SCN_SUPER_VIVID	, // sx30
	MODE_SCN_POSTER_EFFECT	, // sx30
	MODE_SCN_FISHEYE		, // sx30
	MODE_SCN_MINIATURE		, // sx30
	MODE_SCN_HDR			, // g12
};

#endif
