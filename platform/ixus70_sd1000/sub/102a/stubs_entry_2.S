#include "stubs_asm.h"


NHSTUB(Close,  0xFFA9A008) // found in "aClose"
NHSTUB(DisplayImagePhysicalScreen, 0xFFA25068) //found in "ImgDDev.c"
NHSTUB(Mount_FileSystem, 0xFFA9932C) //found in "Mounter.c"
NHSTUB(Read,   0xFFA9A09C) // found in "aRead"
NHSTUB(Remove, 0xFFA9A028) // found in "remove"
NHSTUB(Write,  0xFFA9A0A8) // found in "aWrite"
NHSTUB(free, 0xFF9201CC) // found in "memPartFree"
NHSTUB(kbd_read_keys_r2, 0xFFA30724) //ok

NHSTUB(AllocateMemory, 0xFF818664) // found in "AllocateMemory"
NHSTUB(FreeMemory, 0xFF818650) // found in "aFreememory"
NHSTUB(GetFocusLensSubjectDistance, 0xFFAD4FBC) // found in "GetFocusLensSubjectDistance"
NHSTUB(TakeSemaphore, 0xFFB141D4) // found in "TakeSemaphore"
NHSTUB(kbd_pwr_off, 0xFFA30C58) // ok
NHSTUB(kbd_pwr_on, 0xFFA30C18) // ok
//NHSTUB(localtime, 0xFFB20DA4) // found in "Localtime"
NHSTUB(SetPropertyCase, 0xFF81BB60) // found in "PropertyCase.c"*/

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF9AD778) //null stub 104

NHSTUB(GetDrive_ClusterSize, 0xFFA997F4) // found in "GetCatFs_ClusterSize"
NHSTUB(GetDrive_TotalClusters, 0xFFA99830) // found in "GetCatFs_TotalClusters"
//NHSTUB(GetDrive_FreeClusters, 0xFFA9986C) // found in "GetCatFs_FreeClusters"

/*
NHSTUB(Fopen_Fut, 0xFFA95710) // found in "Fopen_Fut"
NHSTUB(Fclose_Fut, 0xFFA95750) // found in "Fclose_Fut"
NHSTUB(Fread_Fut, 0xFFA9580C) // found in "Fread_Fut"
NHSTUB(Fwrite_Fut, 0xFFA95860) // found in "Fwrite_Fut"
NHSTUB(Fseek_Fut, 0xFFA95900) // found in "Fseek_Fut"
*/
