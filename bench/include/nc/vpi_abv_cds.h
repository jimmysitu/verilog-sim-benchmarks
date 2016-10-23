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


#ifndef ABV_VPI_H
#define ABV_VPI_H

#ifdef  __cplusplus
extern "C" {
#endif

/* For the primary VPI definitions, see 'vpi_user.h'.  */

/***************************************************************************/
/*                   Cadence Assertion Language Extensions                 */
/***************************************************************************/

/* Object types */
#ifndef vpiImmediateAssert
#define vpiImmediateAssert     665  /* IEEE std now- also in sv_vpi_user.h */
#endif

#define vpiAssertDirective    3817
#define vpiAssertEndpt        3818
#define vpiAssertPropertyCDN  3820
#define vpiAssertSeq          3822

/* Relationships */
#define vpiALObjects          3829
#define vpiALDecls            3827
#define vpiALStmts            3828
#define vpiEdgeCond           3825

/* Properties */
#define vpiALFinishCount      3815
#define vpiALFailureCount     3814
#define vpiALCheckedCount     3813
#define vpiALDisabledCount    3871
#define vpiDirectiveType      3831
#define vpiAssertHasModel     3824

/* Assertion state encodings for integer form of vpi_get_value */
#define vpiAssertInactive     1
#define vpiAssertActive       2
#define vpiAssertFinished     3
#define vpiAssertFailed       4
#define vpiAssertDisabled     5
#define vpiAssertSuspended    6
#define vpiAssertOff          7

/* Directive type codes */
#define vpiDirAssert          1
#define vpiDirAssume          2
#define vpiDirRestrict        4
#define vpiDirCover           6


#ifdef  __cplusplus
}
#endif

#endif
