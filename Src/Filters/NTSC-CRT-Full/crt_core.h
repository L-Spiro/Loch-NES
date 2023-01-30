/*****************************************************************************/
/*
 * NTSC/CRT - integer-only NTSC video signal encoding / decoding emulation
 *
 *   by EMMIR 2018-2023
 *
 *   YouTube: https://www.youtube.com/@EMMIR_KC/videos
 *   Discord: https://discord.com/invite/hdYctSmyQJ
 */
/*****************************************************************************/
#ifndef _CRT_CORE_H_
#define _CRT_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* crt_core.h
 *
 * The demodulator. This is also where you can define which system to emulate.
 * 
 */
    
/* library version */
#define CRT_MAJOR 2
#define CRT_MINOR 0
#define CRT_PATCH 1

    
#define CRT_SYSTEM_NTSC 0 /* standard NTSC */
#define CRT_SYSTEM_NES  1 /* decode 6 or 9-bit NES pixels */

/* the system to be compiled */
#define CRT_SYSTEM CRT_SYSTEM_NES

#if (CRT_SYSTEM == CRT_SYSTEM_NES)
#include "crt_nes.h"
#elif (CRT_SYSTEM == CRT_SYSTEM_NTSC)
#include "crt_ntsc.h"
#else
#error No system defined
#endif

/* do bloom emulation (side effect: makes screen have black borders) */
#define CRT_DO_BLOOM    0  /* does not work for NES */
#define CRT_DO_VSYNC    1  /* look for VSYNC */
#define CRT_DO_HSYNC    1  /* look for HSYNC */

struct CRT {
    signed char analog[CRT_INPUT_SIZE];
    signed char inp[CRT_INPUT_SIZE]; /* CRT input, can be noisy */

    int outw, outh; /* output width/height */
    int *out; /* output image */

    int hue, brightness, contrast, saturation; /* common monitor settings */
    int black_point, white_point; /* user-adjustable */
    int scanlines; /* leave gaps between lines if necessary */
    int blend; /* blend new field onto previous image */
    
    /* internal data */
    int ccf[4][4]; /* faster color carrier convergence */
    int cc_period; /* vertically */
    int hsync, vsync; /* keep track of sync over frames */
    int rn; /* seed for the 'random' noise */
};

/* Initializes the library. Sets up filters.
 *   w   - width of the output image
 *   h   - height of the output image
 *   out - pointer to output image data 32-bit RGB packed as 0xXXRRGGBB
 */
extern void crt_init_full(struct CRT *v, int w, int h, int *out);

/* Updates the output image parameters
 *   w   - width of the output image
 *   h   - height of the output image
 *   out - pointer to output image data 32-bit RGB packed as 0xXXRRGGBB
 */
extern void crt_resize_full(struct CRT *v, int w, int h, int *out);

/* Resets the CRT settings back to their defaults */
extern void crt_reset_full(struct CRT *v);

/* Modulates RGB image into an analog NTSC signal
 *   s - struct containing settings to apply to this field
 */
extern void crt_modulate_full(struct CRT *v, struct NTSC_SETTINGS *s);
    
/* Demodulates the NTSC signal generated by crt_modulate_full()
 *   noise - the amount of noise added to the signal (0 - inf)
 */
extern void crt_demodulate_full(struct CRT *v, int noise);

/*****************************************************************************/
/*************************** FIXED POINT SIN/COS *****************************/
/*****************************************************************************/

#define T14_2PI           16384
#define T14_MASK          (T14_2PI - 1)
#define T14_PI            (T14_2PI / 2)

extern void crt_sincos14_full(int *s, int *c, int n);

#ifdef __cplusplus
}
#endif

#endif /* _CRT_SINCOS_H_ */
