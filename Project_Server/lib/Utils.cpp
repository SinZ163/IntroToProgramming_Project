/*
* Generated by SGWrapperGen - DO NOT EDIT!
*
* SwinGame wrapper for C - Utils
*
* Wrapping sgUtils.pas
*/

#include "SGSDK.h"
#include "Utils.h"

#include "Types.h"

#ifdef __cplusplus

void calculate_framerate(char *average, char *highest, char *lowest, color &textColor)
{
    sg_Utils_CalculateFramerate(average, highest, lowest, &textColor);
}

#endif

void calculate_framerate(char *average, char *highest, char *lowest, color *textColor)
{
    sg_Utils_CalculateFramerate(average, highest, lowest, textColor);
}

void delay(uint32_t time)
{
    sg_Utils_Delay(time);
}

void exception_message(char *result)
{
    sg_Utils_ExceptionMessage(result);
}

bool exception_occured()
{
    return sg_Utils_ExceptionOccured() != 0;
}

int32_t get_framerate()
{
    return sg_Utils_GetFramerate();
}

uint32_t get_ticks()
{
    return sg_Utils_GetTicks();
}

float rnd()
{
    return sg_Utils_Rnd();
}

#ifdef __cplusplus

int32_t rnd(int32_t ubound)
{
    return sg_Utils_RndUpto(ubound);
}

#endif

int32_t rnd_upto(int32_t ubound)
{
    return sg_Utils_RndUpto(ubound);
}

void swin_game_version(char *result)
{
    sg_Utils_SwinGameVersion(result);
}

