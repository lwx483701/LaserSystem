#ifndef TYPEDEF_H
#define TYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HSL_WINDOWS
//#define HSL_LINUX
#ifdef HSL_WINDOWS
  #define FNTYPE _stdcall
#endif

#ifdef HSL_LINUX
  #define FNTYPE 
#endif
/****************************************************************************/
/*      Typedef  Definitions                                                */
/****************************************************************************/
typedef unsigned char   U8;
typedef short           I16;
typedef unsigned short  U16;
typedef long            I32;
typedef unsigned long   U32;
typedef float           F32;
typedef double          F64;

typedef unsigned char	byte;	/* 8-bit  */
typedef unsigned short	word;	/* 16-bit */
typedef unsigned long	dword;	/* 32-bit */

#ifdef __cplusplus
}
#endif

#endif
