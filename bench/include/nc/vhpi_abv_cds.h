/*
 * |-----------------------------------------------------------------------|
 * |                                                                       |
 * |   Copyright Cadence Design Systems, Inc. 2003.                        |
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


#ifndef ABV_VHPI_H
#define ABV_VHPI_H

#ifdef  __cplusplus
extern "C" {
#endif

/* For the primary VHPI definitions, see 'vhpi_user.h'.  */

/***************************************************************************/
/*                   Cadence Assertion Language Extensions                 */
/***************************************************************************/

/* Object kinds */
#define vhpiAssertSeqK        1252
#define vhpiAssertEndptK      1254
#define vhpiAssertPropertyK   1255
#define vhpiAssertDirectiveK  1256

/* Relationships (one-to-many) */
#define vhpiALObjects         1703
#define vhpiALDecls           1704
#define vhpiALStmts           1705

/* Relationships (one-to-one) */
#define vhpiEdgeCond          1455

/* Integer Properties */
#define vhpiALFinishCountP    1202
#define vhpiALFailureCountP   1203
#define vhpiALCheckedCountP   1204
#define vhpiDirectiveKindP    1207
#define vhpiAssertHasModelP   1208
#define vhpiALDisabledCountP  1210

/* String Properties */
#define vhpiDirectiveKindStrP 1550

/* Assertion state encodings for integer form of vhpi_get_value */
#define vhpiAssertInactive       1
#define vhpiAssertActive         2
#define vhpiAssertFinished       3
#define vhpiAssertFailed         4
#define vhpiAssertDisabled       5
#define vhpiAssertSuspended      6
#define vhpiAssertOff            7

/* Directive kind codes (vhpiDirectiveKindP) */
#define vhpiDirAssert         1001
#define vhpiDirAssume         1002
#define vhpiDirRestrict       1004
#define vhpiDirCover          1006


#ifdef  __cplusplus
}
#endif

#endif
