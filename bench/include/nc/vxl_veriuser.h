/*
 * |-----------------------------------------------------------------------|
 * |                                                                       |
 * |   Copyright Cadence Design Systems, Inc. 1985, 1988.                  |
 * |     All Rights Reserved.       Licensed Software.                     |
 * |                                                                       |
 * |                                                                       |
 * | THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF CADENCE DESIGN SYSTEMS |
 * | The copyright notice above does not evidence any actual or intended   |
 * | publication of such source code.                                      |
 * |                                                                       |
 * |-----------------------------------------------------------------------|
 */

/*
 * |-------------------------------------------------------------|
 * |                                                             |
 * | PROPRIETARY INFORMATION, PROPERTY OF CADENCE DESIGN SYSTEMS |
 * |                                                             |
 * |-------------------------------------------------------------|
 */


#ifndef VXL_VERIUSER_H
#define VXL_VERIUSER_H
#ifdef  __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*--------------------------- Portability Help ------------------------------*/
/*---------------------------------------------------------------------------*/
/* Sized variables */
#ifndef PLI_TYPES
#define PLI_TYPES
typedef int             PLI_INT32;
typedef unsigned int    PLI_UINT32;
typedef short           PLI_INT16;
typedef unsigned short  PLI_UINT16;
typedef char            PLI_BYTE8;
typedef unsigned char   PLI_UBYTE8;
#endif

/* export a symbol */
#ifndef PLI_DLLISPEC
#define PLI_DLLISPEC
#endif

/* import a symbol */
#ifndef PLI_DLLESPEC
#define PLI_DLLESPEC
#endif

/* mark a function as external */
#ifndef PLI_EXTERN
#define PLI_EXTERN
#endif

/* mark a variable as external */
#ifndef PLI_VEXTERN
#define PLI_VEXTERN extern
#endif

#ifndef PLI_PROTOTYPES
#define PLI_PROTOTYPES
#define PROTO_PARAMS(params) params
/* object is defined imported by the application */
#define XXTERN PLI_EXTERN PLI_DLLISPEC
/* object is exported by the application */
#define EETERN PLI_EXTERN PLI_DLLESPEC
#endif


/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/

#ifndef MAX_SYSTFS
#define MAX_SYSTFS 1024
#endif
#define TF_MAXARRAY 1024  /*
                           * This is the default size of the arrays located
                           * in the veriser.c file.  The need for this is
                           * due to a dynamic linking issue on the Solaris
                           * platform.  The linker/compilier stores size
                           * infomation about arrays in the generated .o,
                           * .so and exe files.  When the default executable
                           * is linked against the libvpi and libpli dynamic
                           * libraries the size of the arrays in the default
                           * libraries must be larger then the arrays in the 
                           * libraries being used.
                           */

/*-------------- values for reason parameter to misctf routines -------------*/

#define reason_diverge           12
#define REASON_DIVERGE            reason_diverge
#define reason_converge          13
#define REASON_CONVERGE           reason_converge
#define reason_vld_interact      14
#define REASON_VLD_INTERACT       reason_vld_interact
#define reason_snapsave          23
#define reason_endofsnapsave     24
#define reason_snaprestart       25
#define reason_endofsnaprestart  26

/*-- types used by tf_typep() and expr_type field in tf_exprinfo structure --*/

#define tf_specialparam        2
#define TF_SPECIALPARAM        tf_specialparam

/*------------- values for component 'type' in tfcell structure -------------*/
#define usertask                  1
#define USERTASK                  usertask
#define userfunction              2
#define USERFUNCTION              userfunction
#define userrealfunction          3
#define USERREALFUNCTION          userrealfunction

/*---------------------------------------------------------------------------*/
/*-------------------------- structure definitions --------------------------*/
/*---------------------------------------------------------------------------*/

/*----------------- structure used for the veriusertfs array ----------------*/
typedef struct t_tfcell
{
    PLI_INT16 type;
    PLI_INT16 data;
    PLI_INT32 (*checktf)();
    PLI_INT32 (*sizetf)();
    PLI_INT32 (*calltf)();
    PLI_INT32 (*misctf)();
    PLI_BYTE8 *tfname;
    PLI_INT32 forwref;
    PLI_BYTE8 *tfveritool;
    PLI_BYTE8 *tferrmessage;
    PLI_INT32 hash;
    struct t_tfcell *left_p;
    struct t_tfcell *right_p;
    PLI_BYTE8 *namecell_p;
    PLI_INT32 warning_printed;
} s_tfcell, *p_tfcell;

/*---------------------------------------------------------------------------*/
/*--------------------------- routine definitions ---------------------------*/
/*---------------------------------------------------------------------------*/

XXTERN PLI_BYTE8 *tf_dumpfilename PROTO_PARAMS((void));
XXTERN void       tf_dumpflush PROTO_PARAMS((void));
XXTERN PLI_INT32  tf_getlongsimtime PROTO_PARAMS((PLI_INT32 *aof_hightime));
XXTERN PLI_BYTE8 *tf_getroutine PROTO_PARAMS((void));
XXTERN PLI_BYTE8 *tf_gettflist PROTO_PARAMS((void));
XXTERN PLI_BYTE8 *tf_igetroutine PROTO_PARAMS((PLI_BYTE8 *inst));
XXTERN PLI_BYTE8 *tf_igettflist PROTO_PARAMS((PLI_BYTE8 *inst));
XXTERN PLI_INT32  tf_isetroutine PROTO_PARAMS((PLI_BYTE8 *(*routine)(), PLI_BYTE8 *inst));
XXTERN PLI_INT32  tf_isettflist PROTO_PARAMS((PLI_BYTE8 *tflist, PLI_BYTE8 *inst));
XXTERN PLI_INT32  tf_setroutine PROTO_PARAMS((PLI_BYTE8 *(*routine)()));
XXTERN PLI_INT32  tf_settflist PROTO_PARAMS((PLI_BYTE8 *tflist));
EETERN PLI_INT32  err_intercept PROTO_PARAMS((PLI_INT32 level, PLI_BYTE8 *facility, PLI_BYTE8 *code));


/*---------------------------------------------------------------------------*/
/*----------------------- global variable definitions -----------------------*/
/*---------------------------------------------------------------------------*/

PLI_VEXTERN PLI_DLLESPEC PLI_BYTE8 *tf_error_message;
PLI_VEXTERN PLI_DLLESPEC s_tfcell veriusertfs[];

#undef PLI_EXTERN
#undef PLI_VEXTERN

#ifdef VXL_VERIUSER_DEFINED_DLLISPEC
#undef VXL_VERIUSER_DEFINED_DLLISPEC
#undef PLI_DLLISPEC
#endif
#ifdef VXL_VERIUSER_DEFINED_DLLESPEC
#undef VXL_VERIUSER_DEFINED_DLLESPEC
#undef PLI_DLLESPEC
#endif

#ifdef PLI_PROTOTYPES
#undef PLI_PROTOTYPES
#undef PROTO_PARAMS
#undef XXTERN
#undef EETERN
#endif

#ifdef  __cplusplus
}
#endif
#endif /* VXL_VERIUSER_H */
