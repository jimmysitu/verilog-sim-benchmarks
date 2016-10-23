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

#ifndef VXL_ACC_USER_H
#define VXL_ACC_USER_H

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
/* object is imported by the application */
#define XXTERN PLI_EXTERN PLI_DLLISPEC
/* object is exported by the application */
#define EETERN PLI_EXTERN PLI_DLLESPEC
#endif

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/

/*------------------------------- object types ------------------------------*/

#define    accMem                  40
#define    accPath                206
#define    accPrimPath            232
#define    accModNetPath          236
#define    accTermPath            238
#define    accModTermPath         240
#define    accTermModPath         242
#define    accCollapsedNet        304
#define    accVlogSimPath         310
#define    accExpandedPath        312
#define    accSwXlInvisibleNet    314
#define    accAcceleratedNet      316
#define    accAssignmentStat      526
#define    accContAssignStat      527
#define    accNullStat            528
#define    accDelayStat           530
#define    accAssignDelayStat     532
#define    accRtlDelayStat        534
#define    accAssignEventStat     536
#define    accAssignMultiStat     537
#define    accRtlEventStat        538
#define    accRtlMultiStat        539
#define    accGenEventStat        540
#define    accDisableStat         542
#define    accRecrem              543
#define    accAssignStat          544
#define    accRemoval             545
#define    accDeassignStat        546
#define    accForceStat           548
#define    accReleaseStat         550
#define    accInitialStat         552
#define    accAlwaysStat          554
#define    accAtEventStat         556
#define    accUnnamedBeginStat    558
#define    accUnnamedForkStat     562
#define    accIfStat              566
#define    accCaseStat            568
#define    accCaseZStat           570
#define    accCaseXStat           572
#define    accForeverStat         574
#define    accRepeatStat          576
#define    accWhileStat           578
#define    accForStat             580
#define    accWaitStat            582
#define    accPlusOp              630
#define    accMinusOp             632
#define    accLogNotOp            634
#define    accBitNegOp            636
#define    accRedAndOp            638
#define    accRedNandOp           640
#define    accRedOrOp             642
#define    accRedNorOp            644
#define    accRedXorOp            646
#define    accRedXnorOp           648
#define    accSubOp               650
#define    accDivOp               652
#define    accModOp               654
#define    accEqOp                656
#define    accNeqOp               658
#define    accEqeOp               660
#define    accNeeOp               662
#define    accGtOp                664
#define    accGeOp                666
#define    accLtOp                668
#define    accLeOp                670
#define    accLshOp               672
#define    accRshOp               674
#define    accAddOp               676
#define    accMultOp              678
#define    accLogAndOp            680
#define    accLogOrOp             682
#define    accBitAndOp            684
#define    accBitOrOp             686
#define    accBitXorOp            688
#define    accBitXnorOp           690
#define    accCondOp              692
#define    accExprList            694
#define    accDupConcat           698
#define    accUdpDefn             700
#define    accSeqUdpDefn          702
#define    accCombUdpDefn         704
#define    accUdpEntry            706
#define    accContAssign          708
#define    accExpNamedPort        710
#define    accAssignDriver        712
#define    accModportDriver       714
#define    accModPathHasIfnone    715
#define    accTwoLimitTchk        716
#define    accTimingModel         718
#define    accMultiSrcInt         720
#define    accIsLineBreakable     721
#define    accWriteAccess         722
#define    accReadAccess          724
#define    accConnectivityAccess  726

/*------------------ parameter values for acc_configure() -------------------*/

#define    accSpecitemScope         7
#define    accWarnNestedLoconn      9
#define    accWarnNestedHiconn     10
#define    accMinMultiplier        12
#define    accTypMultiplier        13
#define    accMaxMultiplier        14
#define    accAttrDelimStr         15
#define    accDelayCount           16
#define    accDelayArrays          18
#define    accUserErrorString      20
#define    accTwoLimitChecks       21
#define    accEnableUdpDefn        22
#define    accSplitSetuphold       23
#define    accSplitSetupHold       23
#define    accBehavDrivers         24
#define    accReturnExpPortNames   25
#define    accShowContAssignLoads  26
#define    accNoUnExpPortsErrors   27
#define    accScaleDelays          28
#define    accReturnModDefnHandle  29
#define    accSplitRecRem          30

/*------------ values for type field in t_setval_value structure ------------*/

#define accCompactVal               9
#define accTimeVal                 11

/*----------- values for vc_reason field in t_vc_record structure -----------*/

#define compact_value_change       11

/*------------------------------ product types ------------------------------*/

#define accVerilog                  1
#define accVeritime                 2
#define accVerifault                3

/*--------------------- includes for the time callbacks ---------------------*/

#define reason_begin_of_simtime     1
#define reason_end_of_simtime       2

/*------------------------------- delay modes -------------------------------*/

#define accDelayModeVeritime        5

/*----------------- include information for stability checks ----------------*/

#define accTaskFuncStable                 0x0001
#define accSystfStable                    0x0002
#define accPrimStable                     0x0004
#define accContAssignStable               0x0008
#define accBehavStable                    0x0010
#define accNetRegVarStable                0x0020
#define acc_taskfunc_stable               accTaskFuncStable
#define acc_systf_stable                  accSystfStable
#define acc_primitive_stable              accPrimStable
#define acc_contassign_stable             accContAssignStable
#define acc_behav_stable                  accBehavStable
#define acc_netreg_stable                 accNetRegVarStable
#define acc_setstabflags_m(_flags,_pos)   (_flags |= _pos)
#define acc_clearstabflags_m(_flags,_pos) (_flags &= ~_pos)
#define acc_isstabflags_m(_flags,_pos)    (_flags & _pos)

/*---------------------------------------------------------------------------*/
/*-------------------------- routine declarations ---------------------------*/
/*---------------------------------------------------------------------------*/

XXTERN PLI_BYTE8 *acc_cond_fetch_fullname PROTO_PARAMS((handle object_handle));
XXTERN PLI_BYTE8 *acc_cond_fetch_name PROTO_PARAMS((handle object_handle));
XXTERN PLI_BYTE8 *acc_cond_fetch_defname PROTO_PARAMS((handle object_handle));
XXTERN PLI_BYTE8 *acc_cond_fetch_type_str PROTO_PARAMS((PLI_INT32 type));
XXTERN PLI_BYTE8 *acc_decompile_expr PROTO_PARAMS((handle object));
XXTERN double     acc_fetch_attribute_real PROTO_PARAMS((handle object, ...));
XXTERN PLI_INT32  acc_fetch_paramval_int PROTO_PARAMS((handle param));
XXTERN double     acc_fetch_paramval_real PROTO_PARAMS((handle param));
XXTERN PLI_BYTE8 *acc_fetch_paramval_str PROTO_PARAMS((handle param));
XXTERN void       acc_fetch_paramval_mtm PROTO_PARAMS((handle param, double *min, double *type, double *max));
XXTERN handle     acc_handle_defn PROTO_PARAMS((handle prim));
XXTERN handle     acc_next_table_entry PROTO_PARAMS((handle defn, handle entry));
XXTERN handle     acc_next_topudp PROTO_PARAMS((handle defn));
XXTERN PLI_INT32  acc_stability PROTO_PARAMS((handle scope));
XXTERN PLI_INT32  acc_vcl_monitored PROTO_PARAMS((handle object_p, PLI_INT32 (*consumer)(), PLI_BYTE8 **user_data));


/*---------------------------------------------------------------------------*/
/*---------------------------- macro definitions ----------------------------*/
/*---------------------------------------------------------------------------*/


#undef PLI_EXTERN
#undef PLI_VEXTERN

#ifdef VXL_ACC_USER_DEFINED_DLLISPEC
#undef VXL_ACC_USER_DEFINED_DLLISPEC
#undef PLI_DLLISPEC
#endif
#ifdef VXL_ACC_USER_DEFINED_DLLESPEC
#undef VXL_ACC_USER_DEFINED_DLLESPEC
#undef PLI_DLLESPEC
#endif

#ifdef PLI_PROTOTYPES
#undef PLI_PROTOTYPES
#undef PROTO_PARAMS
#undef XXTERN
#undef EETERN
#endif

#ifdef __cplusplus
}
#endif

#endif /* VXL_ACC_USER_H */
