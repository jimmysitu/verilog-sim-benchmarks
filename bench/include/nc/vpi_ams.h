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

/*************************** File vpi_ams.h **************************/
/* This file is to be included in files which call VPI routines with Mixed
 * Signal Simulator 
 * 
 * The constant values from 2000 to 2499 (inclusive) are reserved for VPI AMS
 * (Analog Mixed Signal).  Please do not use them.
 */

#ifndef VPI_AMS_H
#define VPI_AMS_H

#ifdef  __cplusplus
extern "C" {
#endif

/************************ DOMAIN TYPES  ************************/
#define vpiDiscrete      1      /* of discrete type (owned by digital) */
#define vpiContinuous    2      /* of continuous type (owned by analog) */
#define vpiMixed         3      /* of mixed type (handle mixed bus) 
                                 * see vpi_ams documentation for examples 
				 * of using these definitions */
/************************ generic object properties ***********************/
#define vpiDomain        2001   /* domain of object */
 
#ifdef  __cplusplus
}
#endif

#endif
