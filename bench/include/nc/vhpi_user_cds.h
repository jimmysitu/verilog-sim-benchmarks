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

/*************************** File vhpi_user_cds.h **************************/
/***** This file is to be included in files which call VHPI routines *******/
/************* and require access to non-IEEE compliant aspects ***********/

#ifndef VHPI_USER_CDS_H
#define VHPI_USER_CDS_H

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

/* Use to export a symbol */
#ifndef PLI_DLLISPEC
#define PLI_DLLISPEC
#endif

/* Use to import a symbol */
#ifndef PLI_DLLESPEC
#define PLI_DLLESPEC
#endif

/* Use to mark a function as external */
#ifndef PLI_EXTERN
#define PLI_EXTERN
#endif

/* Use to mark a variable as external */
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
/*------------------------------ Array sizes --------------------------------*/
/*---------------------------------------------------------------------------*/

/****************************** OBJECT TYPES ******************************/

#ifndef INT_CLASSES
#define INT_CLASSES
#endif
#ifndef INT_AMS_CLASSES
#define INT_AMS_CLASSES
#endif

#ifdef VHPIEXTEND_CLASSES 
#undef VHPIEXTEND_CLASSES 
#endif

#define VHPIEXTEND_CLASSES \
  INT_CLASSES \
  INT_AMS_CLASSES

/******************************** METHODS *********************************/
/************* methods used to traverse 1 to 1 relationships **************/

#ifndef INT_ONE_METHODS
#define INT_ONE_METHODS
#endif
#ifndef INT_AMS_ONE_METHODS
#define INT_AMS_ONE_METHODS
#endif


#ifdef VHPIEXTEND_ONE_METHODS 
#undef VHPIEXTEND_ONE_METHODS 
#endif

#define VHPIEXTEND_ONE_METHODS \
  INT_ONE_METHODS \
  INT_AMS_ONE_METHODS

/************ methods used to traverse 1 to many relationships ************/

#ifndef INT_MANY_METHODS
#define INT_MANY_METHODS
#endif
#ifndef INT_AMS_MANY_METHODS
#define INT_AMS_MANY_METHODS
#endif


#ifdef VHPIEXTEND_MANY_METHODS 
#undef VHPIEXTEND_MANY_METHODS 
#endif

#define VHPIEXTEND_MANY_METHODS \
  INT_MANY_METHODS \
  INT_AMS_MANY_METHODS

/******************************* PROPERTIES *******************************/
/************************ integer properties ***********************/

#ifndef INT_INT_PROPERTIES
#define INT_INT_PROPERTIES
#endif
#ifndef INT_AMS_INT_PROPERTIES
#define INT_AMS_INT_PROPERTIES
#endif

#ifdef VHPIEXTEND_INT_PROPERTIES 
#undef VHPIEXTEND_INT_PROPERTIES 
#endif

#define VHPIEXTEND_INT_PROPERTIES , \
  vhpiIsProtectedP = 1254 /* check for IEEE protection property */ \
  INT_INT_PROPERTIES \
  INT_AMS_INT_PROPERTIES
  
/************************** string properties ***************************/

#ifndef INT_STR_PROPERTIES
#define INT_STR_PROPERTIES
#endif
#ifndef INT_AMS_STR_PROPERTIES
#define INT_AMS_STR_PROPERTIES
#endif

#ifdef VHPIEXTEND_STR_PROPERTIES 
#undef VHPIEXTEND_STR_PROPERTIES 
#endif

#define VHPIEXTEND_STR_PROPERTIES \
  INT_STR_PROPERTIES \
  INT_AMS_STR_PROPERTIES

/********************** real properties **********************/

#ifndef INT_REAL_PROPERTIES
#define INT_REAL_PROPERTIES
#endif
#ifndef INT_AMS_REAL_PROPERTIES
#define INT_AMS_REAL_PROPERTIES
#endif

#ifdef VHPIEXTEND_REAL_PROPERTIES 
#undef VHPIEXTEND_REAL_PROPERTIES 
#endif

#define VHPIEXTEND_REAL_PROPERTIES \
  INT_REAL_PROPERTIES \
  INT_AMS_REAL_PROPERTIES

/************************ physical properties *************************/

#ifndef INT_PHYS_PROPERTIES
#define INT_PHYS_PROPERTIES
#endif
#ifndef INT_AMS_PHYS_PROPERTIES
#define INT_AMS_PHYS_PROPERTIES
#endif

#ifdef VHPIEXTEND_PHYS_PROPERTIES 
#undef VHPIEXTEND_PHYS_PROPERTIES 
#endif

#define VHPIEXTEND_PHYS_PROPERTIES \
  INT_PHYS_PROPERTIES \
  INT_AMS_PHYS_PROPERTIES

/*************************** value formats ****************************/

#ifndef INT_VAL_FORMATS
#define INT_VAL_FORMATS
#endif
#ifndef INT_AMS_VAL_FORMATS
#define INT_AMS_VAL_FORMATS
#endif

#ifdef VHPIEXTEND_VAL_FORMATS 
#undef VHPIEXTEND_VAL_FORMATS 
#endif

#define VHPIEXTEND_VAL_FORMATS \
  INT_VAL_FORMATS \
  INT_AMS_VAL_FORMATS

/************************* attribute types ***************************/

#ifndef INT_ATTR
#define INT_ATTR
#endif
#ifndef INT_AMS_ATTR
#define INT_AMS_ATTR
#endif

#ifdef VHPIEXTEND_ATTR 
#undef VHPIEXTEND_ATTR 
#endif

#define VHPIEXTEND_ATTR \
  INT_ATTR \
  INT_AMS_ATTR

/************************* prototypes **************************/

#ifndef INT_PROTOTYPES
#define INT_PROTOTYPES
#endif
#ifndef INT_AMS_PROTOTYPES
#define INT_AMS_PROTOTYPES
#endif

#ifdef VHPIEXTEND_PROTOTYPES 
#undef VHPIEXTEND_PROTOTYPES 
#endif

#define VHPIEXTEND_PROTOTYPES \
  INT_PROTOTYPES \
  INT_AMS_PROTOTYPES


#undef PLI_XXTERN
#undef PLI_EETERN

#ifdef VPI_USER_CDS_DEFINED_DLLISPEC
#undef VPI_USER_CDS_DEFINED_DLLISPEC
#undef PLI_DLLISPEC
#endif
#ifdef VPI_USER_CDS_DEFINED_DLLESPEC
#undef VPI_USER_CDS_DEFINED_DLLESPEC
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

#endif  /* VHPI_USER_CDS_H */
