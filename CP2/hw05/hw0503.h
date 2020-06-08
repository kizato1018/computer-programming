#ifndef __HW0503_H__
#define __HW0503_H__

#if defined(DEBUG_LEVEL_ERROR)
    #define DEBUG_LEVEL_VVERBOSE 0 
    #define DEBUG_LEVEL_VERBOSE 0
    #define DEBUG_LEVEL_INFO 0
#elif defined(DEBUG_LEVEL_INFO)
    #define DEBUG_LEVEL_ERROR 1
    #define DEBUG_LEVEL_VERBOSE 0
    #define DEBUG_LEVEL_VVERBOSE 0
#elif defined(DEBUG_LEVEL_VERBOSE)
    #define DEBUG_LEVEL_INFO 1
    #define DEBUG_LEVEL_ERROR 1
    #define DEBUG_LEVEL_VVERBOSE 0
#elif defined(DEBUG_LEVEL_VVERBOSE)
    #define DEBUG_LEVEL_VERBOSE 1
    #define DEBUG_LEVEL_INFO 1
    #define DEBUG_LEVEL_ERROR 1
#endif

#ifdef DEBUG_LEVEL_NONE
    #define debug_printf(level, fmt, ...) 
#else
    #define debug_printf(level, fmt, ...) if(level)printf(fmt, __VA_ARGS__)
#endif

#endif