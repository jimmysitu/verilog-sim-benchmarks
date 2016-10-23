/*
 * |---------------------------------------------------------------|
 * |                                                               |
 * |   Copyright Cadence Design Systems, Inc. 1985, 1988.          |
 * |     All Rights Reserved.       Licensed Software.             |
 * |                                                               |
 * |                                                               |
 * | THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF CADENCE DESIGN |
 * | SYSTEMS. The copyright notice above does not evidence any     |
 * | actual or intended publication of such source code.           |
 * |                                                               |
 * |---------------------------------------------------------------|
 */

/*
 * |-------------------------------------------------------------|
 * |                                                             |
 * | PROPRIETARY INFORMATION, PROPERTY OF CADENCE DESIGN SYSTEMS |
 * |                                                             |
 * |-------------------------------------------------------------|
 */
/*** File vhpi_user.h ***/
/*** This file describe the procedural interface to access VHDL 
     compiled, instantiated and run-time data. It is derived from 
     the vhpimodel file. ***/

#ifndef VHPI_USER_H
#define VHPI_USER_H

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

typedef void            PLI_VOID;

/* Use to export a symbol */
#if WIN32
#ifndef PLI_DLLISPEC
#define PLI_DLLISPEC __declspec(dllimport)
#define VHPI_USER_DEFINED_DLLISPEC 1
#endif
#else
#ifndef PLI_DLLISPEC
#define PLI_DLLISPEC
#endif
#endif

/* Use to import a symbol */
#if WIN32
#ifndef PLI_DLLESPEC
#define PLI_DLLESPEC __declspec(dllexport)
#define VHPI_USER_DEFINED_DLLESPEC 1
#endif
#else
#ifndef PLI_DLLESPEC
#define PLI_DLLESPEC
#endif
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


/* basic typedefs */
#ifndef VHPI_TYPES
#define VHPI_TYPES
typedef PLI_UINT32 *vhpiHandleT;
typedef PLI_UINT32 vhpiEnumT;
typedef PLI_UINT32 vhpiIntT;
typedef char vhpiCharT;
typedef double vhpiRealT;
typedef struct vhpiPhysS
{
  PLI_INT32 high;
  PLI_UINT32 low;
} vhpiPhysT;

/********************** time structure ****************************/
typedef struct vhpiTimeS
{
  PLI_UINT32 high;
  PLI_UINT32 low;
} vhpiTimeT;

/********************** value structure **************************/

/* value formats */
typedef enum {
  vhpiBinStrVal        = 1, /* do not move */
  vhpiOctStrVal        = 2, /* do not move */
  vhpiDecStrVal        = 3, /* do not move */
  vhpiHexStrVal        = 4, /* do not move */
  vhpiEnumVal          = 5, 
  vhpiIntVal           = 6,
  vhpiLogicVal         = 7,
  vhpiRealVal          = 8,
  vhpiStrVal           = 9,
  vhpiCharVal          = 10,
  vhpiTimeVal          = 11,
  vhpiPhysVal          = 12 ,
  vhpiObjTypeVal       = 13,
  vhpiPtrVal           = 14,
  vhpiEnumVecVal       = 15,
  vhpiIntVecVal	       = 16,
  vhpiLogicVecVal      = 17,
  vhpiRealVecVal       = 18,
  vhpiTimeVecVal       = 19,
  vhpiPhysVecVal       = 20,
  vhpiPtrVecVal        = 21,
  vhpiRawDataVal       = 22

#ifdef VHPIEXTEND_VAL_FORMATS
  VHPIEXTEND_VAL_FORMATS
#endif

} vhpiFormatT;


/* value structure */
typedef struct vhpiValueS
{
  vhpiFormatT format;  	/* vhpi[Char,[Bin,Oct,Dec,Hex]Str,
                                Logic,Int,Real,Phys,Ptr,Time,
			        IntVect,RealVec,PhysVec,TimeVec,PtrVec,
                                ObjType,RawData]Val */
  PLI_UINT32 bufSize;  /* the size in bytes of the value buffer; this is set
                          by the user */
  PLI_INT32 numElems;
  /* different meanings depending on the format:
     vhpiStrVal, vhpi{Bin...}StrVal: size of string
     array type values: number of array elements
     scalar type values: undefined
  */

  vhpiPhysT unit;     /* changed to vhpiPhysT in charles */
  union 
    {
      vhpiEnumT enumv, *enumvs;
      vhpiIntT  intg, *intgs;
      vhpiRealT real, *reals;
      vhpiPhysT phys, *physs;
      vhpiTimeT time, *times;
      vhpiCharT ch, *str;
      void *ptr, **ptrs;
    } value;
} vhpiValueT;

#endif

/* Following are the constant definitions. They are divided into 
   three major areas:

 1) object types

 2) access methods

 3) properties

*/
#define vhpiUndefined 1000

/*************** OBJECT KINDS *******************/
typedef enum {
	vhpiAccessTypeDeclK = 1001,	/* Access Type Declaration */
	vhpiAggregateK = 1002,		/* Aggregate */
	vhpiAliasDeclK = 1003,		/* Alias Declaration */
	vhpiAllK = 1004,		 
	vhpiAllocatorK = 1005,
	vhpiAnyCollectionK = 1006,	/* Collection of objects */
	vhpiArchBodyK = 1007,		/* Architecture design unit */
	vhpiArgvK = 1008,		/* Argument vector */
	vhpiArrayTypeDeclK = 1009,	/* Array Type Declaration */
	vhpiAssertStmtK = 1010,		/* Assert statement */
	vhpiAssocElemK = 1011,		/* Association element */
	vhpiAttrDeclK = 1012,		/* Attribute declaration */
	vhpiAttrSpecK = 1013,		/* Attribute Specification */
	vhpiBinaryExprK = 1014,		/* Binary Expression */
	vhpiBitStringLiteralK = 1015,	/* One-dimensional array of characters */
	vhpiBlockConfigK = 1016,	/* Block configuration */
	vhpiBlockStmtK = 1017,		/* Block Statement */
	vhpiBranchK = 1018,
	vhpiCallbackK = 1019,
	vhpiCaseStmtK = 1020,		/* Case Statement */
	vhpiCharLiteralK = 1021,	/* Character within single quotation marks */
	vhpiCompConfigK = 1022,		/* Component Configuration */
	vhpiCompDeclK = 1023,		/* Component Declaration */
	vhpiCompInstStmtK = 1024,	/* Component Instantiation Statement */
	vhpiCondSigAssignStmtK = 1025,	/* Conditional signal assignment Statement */
	vhpiCondWaveformK = 1026,	/* Conditional waveform */
	vhpiConfigDeclK = 1027,		/* Configuration declaration */
	vhpiConstDeclK = 1028,		/* Constant declaration */
	vhpiConstParamDeclK = 1029,	/* Parameter of class constant */
	vhpiConvFuncK = 1030,		/* Conversion Function */
	vhpiDeRefObjK = 1031,		/* Dereferenced object */
	vhpiDisconnectSpecK = 1032,	/* Disconnection Specification */
	vhpiDriverK = 1033,		/* Driver */
	vhpiDriverCollectionK = 1034,	/* Collection of drivers */
	vhpiElemAssocK = 1035,		 
	vhpiElemDeclK = 1036,		/* Field of a Record */
	vhpiEntityClassEntryK = 1037,
	vhpiEntityDeclK = 1038,		/* Entity declaration */
	vhpiEnumLiteralK = 1039,	/* Literal of enumeration type */
	vhpiEnumRangeK = 1040,    
	vhpiEnumTypeDeclK = 1041,	/* Enumeration type definition */
	vhpiExitStmtK = 1042,		/* Exit Statement */
	vhpiFileDeclK = 1043,		/* File declaration */
	vhpiFileParamDeclK = 1044,	/* Parameters of class file */
	vhpiFileTypeDeclK = 1045,	/* File Type Declaration */
	vhpiFloatRangeK = 1046,		/* Float Range */
	vhpiFloatTypeDeclK = 1047,	/* Floating point type Declaration */
	vhpiForGenerateK = 1048,	/* For generate statement */
	vhpiForLoopK = 1049,		/* For Loop statement */
	vhpiForeignfK = 1050,		/* Foreign Function */
	vhpiFuncCallK = 1051,		/* Function Call Statement */
	vhpiFuncDeclK = 1052,		/* Function Declaration */
	vhpiGenericDeclK = 1053,	/* Generic Declaration */
	vhpiGroupDeclK = 1054,		/* Group Declaration */
	vhpiGroupTempDeclK = 1055,	/* Group Template Declaration */
	vhpiIfGenerateK = 1056,		/* If Generate Statement */
	vhpiIfStmtK = 1057,		/* If statement */
	vhpiInPortK = 1058,		/* IN Port */
	vhpiIndexedNameK = 1059,	/* Indexed name */
	vhpiIntLiteralK = 1060,		/* Literal of type universal_integer */
	vhpiIntRangeK = 1061,		/* Integer Range */
	vhpiIntTypeDeclK = 1062,	/* Integer Type Declaration */
	vhpiIteratorK = 1063,		/* Iterator */
	vhpiLibraryDeclK = 1064,	/* Library Declaration */
	vhpiLoopStmtK = 1065,		/* Loop Statement */
	vhpiNextStmtK = 1066,		/* Next Statement */
	vhpiNullLiteralK = 1067,	/* Literal represented by the VHDL keyword "null" */
	vhpiNullStmtK = 1068,		/* Null statement */
	vhpiOperatorK = 1069,		/* Belongs to a class of operators */
	vhpiOthersK = 1070,		/* 'Others' in case stmt */
	vhpiOutPortK = 1071,		/* OUT Port */
	vhpiPackBodyK = 1072,		/* Package Body */
	vhpiPackDeclK = 1073,		/* Package Declaration */
	vhpiPackInstK = 1074,		/* Package Instance */
	vhpiParamAttrNameK = 1075,	/* Formal parameter has an Attribute */
	vhpiPhysLiteralK = 1076,	/* Literal of type Physical */
	vhpiPhysRangeK = 1077,		/* Physical Range */
	vhpiPhysTypeDeclK = 1078,	/* Physical Type Declaration */
	vhpiPortDeclK = 1079,		/* Port Declaration */
	vhpiProcCallStmtK = 1080,	/* Procedure call statement */
	vhpiProcDeclK = 1081,		/* Procedure Declaration */
	vhpiProcessStmtK = 1082,	/* Process statement */
	vhpiProtectedTypeK = 1083,	
	vhpiProtectedTypeBodyK = 1084,
	vhpiProtectedTypeDeclK = 1085,
	vhpiRealLiteralK = 1086,	/* Literal of type universal_real */
	vhpiRecordTypeDeclK = 1087,	/* Record Type Declaration */
	vhpiReportStmtK = 1088,		/* Report Statement */
	vhpiReturnStmtK = 1089,		/* Return Statement */
	vhpiRootInstK = 1090,		/* Top Architecture Instance */
	vhpiSelectSigAssignStmtK = 1091,/* Selected signal assignment statement */
	vhpiSelectWaveformK = 1092,	/* Selected Waveform */
	vhpiSelectedNameK = 1093,	/* Selected name */
	vhpiSigDeclK = 1094,		/* Signal Declaration */
	vhpiSigParamDeclK = 1095,	/* Parameter of class signal */
	vhpiSimpAttrNameK = 1096,	/* Simple Attribute Name */
	vhpiSimpleSigAssignStmtK = 1097,/* Simple signal assignment statement */
	vhpiSliceNameK = 1098,		/* Slice Name */
	vhpiStringLiteralK = 1099,	/* Sequence of characters inside double quotation marks */
	vhpiSubpBodyK = 1100,		/* Subprogram Body */
	vhpiSubtypeDeclK = 1101,	/* Subtype Declaration */
	vhpiSubtypeIndicK = 1102,	/* Subtype Indication */
	vhpiToolK = 1103,		/* NCSIM Tool */
	vhpiTransactionK = 1104,	 
	vhpiTypeConvK = 1105,		/* Type Conversion */
	vhpiUnaryExprK = 1106,		/* Unary Expression */
	vhpiUnitDeclK = 1107,		/* Unit in Physical type */
	vhpiUserAttrNameK = 1108,	/* User-defined attribute */
	vhpiVarAssignStmtK = 1109,	/* Variable assignment statement */
	vhpiVarDeclK = 1110,		/* Variable Declaration */
	vhpiVarParamDeclK = 1111,	/* Parameter of class Variable */
	vhpiWaitStmtK = 1112,		/* Wait Statement */
	vhpiWaveformElemK = 1113,	/* Waveform Element */
	vhpiWhileLoopK = 1114,		/* While Loop Statement */

        /* CADENCE NON STD CLASS */
        vhpiUseClauseK = 1200           

#ifdef VHPIEXTEND_CLASSES
	VHPIEXTEND_CLASSES
#endif

} vhpiClassKindT;


/************** methods used to traverse 1 to 1 relationships *******************/
typedef enum {
	vhpiAbstractLiteral = 1301,	/* Abstract Literal */
	vhpiActual = 1302,		/* Actual value of ports/parameters */
	vhpiAll = 1303,			 
	vhpiAttrDecl = 1304,		/* Attribute Declaration */
	vhpiAttrSpec = 1305,		/* Attribute Specification */
	vhpiBaseType = 1306,		/* Base Type */
	vhpiBaseUnit = 1307,		/* The base (primary) unit of the physical type */
	vhpiBasicSignal = 1308,		/* Basic Signal */
	vhpiBlockConfig = 1309,		/* Block Configuration */
	vhpiCaseExpr = 1310,		/* Case Expression */
	vhpiCondExpr = 1311,		/* Conditional Expression */
	vhpiConfigDecl = 1312,		/* Configuration Declaration */
	vhpiConfigSpec = 1313,		/* Configuration Specification */
	vhpiConstraint = 1314,		/* Bound Range constraint */
	vhpiContributor = 1315,		/* Currently executing callback if any */
	vhpiCurCallback = 1316,		/* Currently executing callback if any */
	vhpiCurEqProcess = 1317,	/* Currently executing process(equivalent process) */ 
	vhpiCurStackFrame = 1318,	/* Current executing or suspended stack frame */
	vhpiDeRefObj = 1319,		/* DeReferenced Object */
	vhpiDecl = 1320,		/* Decl of the operator */
	vhpiDesignUnit = 1321,		/* To which this instance is bound to */
	vhpiDownStack = 1322,		/* Moving down stack frame */ 
	vhpiElemSubtype = 1323,		/* Subtype of the element (array or record field) */
	vhpiEntityAspect = 1324,	/* Entity aspect */
	vhpiEntityDecl = 1325,		/* Entity Declaration */
	vhpiEqProcessStmt = 1326,	/* Equivalent Process for Driver */ 
	vhpiExpr = 1327,		/* Expression */
	vhpiFormal = 1328,		/* Handle to Formal port/parameter */ 
	vhpiFuncDecl = 1329,		/* Function Declaration */
	vhpiGroupTempDecl = 1330,	/* Group Template Declaration */
	vhpiGuardExpr = 1331,		/* Guard Expression */
	vhpiGuardSig = 1332,		/* Guard Signal */
	vhpiImmRegion = 1333,		/* Immediate scope of the handle */
	vhpiInPort = 1334,		/* In Port */
	vhpiInitExpr = 1335,		/* Initial expression of the declared item */
	vhpiIterScheme = 1336,		/* Iteration scheme of loop statement */
	vhpiLeftExpr = 1337,		/* Left hand expression for a range or binaryExpression */
	vhpiLexicalScope = 1338,	/* Enclosing Lexical Scope of that declaration */
	vhpiLhsExpr = 1339,		/* Target of a signal assignment */
	vhpiLocal = 1340,		/* Local of the association element */
	vhpiLogicalExpr = 1341,		/* Logical name of a file declaration */
	vhpiName = 1342,		/* Name of an alias decl */
	vhpiOperator = 1343,		/* Returns the operator */
	vhpiOthers = 1344,		/* Handle to vhpiOthersK of a Disconnection Specification */
	vhpiOutPort = 1345,		/* Output side of an INOUT port */
	vhpiParamDecl = 1346,		/* Parameter decl of the handle */
	vhpiParamExpr = 1347,		/* Attribute parameter expression */
	vhpiParent = 1348,		/* Parent of the sequential statement */
	vhpiPhysLiteral = 1349,		/* Phys literal from a UnitDecl */
	vhpiPrefix = 1350,		/* Prefix of a prefixedName or attrName */
	vhpiPrimaryUnit = 1351,		/* Primary unit of the design unit */
	vhpiProtectedTypeBody = 1352,	
	vhpiProtectedTypeDecl = 1353,
	vhpiRejectTime = 1354,		/* Reject time expr of SigAssignStmt */
	vhpiReportExpr = 1355,		/* Report expr of the handle */
	vhpiResolFunc = 1356,		/* Resolution function for the object */
	vhpiReturnExpr = 1357,		/* Return expression */
	vhpiReturnTypeMark = 1358,	/* Subtype of the function return value */
	vhpiRhsExpr = 1359,		/* Right hand-side expr of the variable assignment stmt */
	vhpiRightExpr = 1360,		/* Right hand expression for a range or binaryExpression */
	vhpiRootInst = 1361,		/* Root instance of the design */
	vhpiSelectExpr = 1362,		/* Select expr in a select signal assignment */
	vhpiSeverityExpr = 1363,	/* Severity expr of the handle */
	vhpiSimpleName = 1364,		/* Simple name */
	vhpiSubpBody = 1365,		/* Handle to the subprogbody */
	vhpiSubpDecl = 1366,		/* Subprogram decl of the subprogram call */
	vhpiSubtype = 1367,		/* Subtype of the decl item */
	vhpiSuffix = 1368,		/* Suffix of a  selected Name */
	vhpiTimeExpr = 1369,		/* Time expr of the waveformElem or disconnectSpec */
	vhpiTimeOutExpr = 1370,		/* Time out expression of the wait stmt */
	vhpiTool = 1371,		/* NCTool */
	vhpiType = 1372,		/* Type of the expr */
	vhpiTypeMark = 1373,		/* Type mark of the handle */
	vhpiUnitDecl = 1374,		/* Handle of the Unit decl */
	vhpiUpStack = 1375,		/* Moving Up stack frame */
	vhpiUpperRegion = 1376,		/* Scope which contains the handle */
	vhpiUse = 1377,			 
	vhpiValExpr = 1378,		/* Value expr of the waveformElem */
	vhpiValSubtype = 1379,		/* Subtype indication of the access/file decl */
        /* CADENCE NON STD METHOD */
        vhpiSimNet = 1400

#ifdef VHPIEXTEND_ONE_METHODS
        VHPIEXTEND_ONE_METHODS
#endif

} vhpiOneToOneT;

/************** methods used to traverse 1 to many relationships *******************/
typedef enum {
	vhpiAliasDecls = 1501,		/* Iterator for alias declarations */ 
	vhpiArgvs = 1502,		/* Iterator for argument vectors */
	vhpiAttrDecls = 1503,		/* Iterator for attribute declarations */
	vhpiAttrSpecs = 1504,		/* Iterator for attribute specification */
	vhpiBasicSignals = 1505,	/* Iterator for Basic Signals of a sigDecl */
	vhpiBlockStmts = 1506,		/* Iterator for Block Statements */
	vhpiBranchs = 1507,		/* Iterator for branches of a statement */
	vhpiCallbacks = 1508,		/* Iterator for callbacks registered on a given object */
	vhpiChoices = 1509,		/* Iterator for choices of the select waveform or an aggregate */
	vhpiCompInstStmts = 1510,	/* Iterator for the VHDL CompInst */
	vhpiCondExprs = 1511,		/* Iterator for conditional expression */
	vhpiCondWaveforms = 1512,	/* Iterator for conditional waveforms */
	vhpiConfigItems = 1513,		/* Iterator for configuration items */
	vhpiConfigSpecs = 1514,		/* Iterator for configuration specifications of the architecture */
	vhpiConstDecls = 1515,		/* Iterator for the constant decls */
	vhpiConstraints = 1516,		/* Constraints for subtypeDecl,arrayTypeDecl and subtypeIndic */
	vhpiContributors = 1517,	/* Iterator for contributors in a region */
	vhpiCurRegions = 1518,		/* Currently executing region instances */
	vhpiDecls = 1519,		/* Iterator on declared objects */
	vhpiDepUnits = 1520,		/* Iterator for dependent units of a design unit */
	vhpiDesignUnits = 1521,		/* Iterator for design units */
	vhpiDrivenSigs = 1522,		 
	vhpiDrivers = 1523,		/* Iterator for drivers in a region */
	vhpiElemAssocs = 1524,		/* Iterator for elem assocs of an aggregate */
	vhpiEntityClassEntrys = 1525,	
	vhpiEntityDesignators = 1526,	/* Iterator for specification names of the configuration */
	vhpiEnumLiterals = 1527,	/* Iterator for literal values of an enumeration decl */
	vhpiForeignfs = 1528,		/* Iterator for foreign models which have been registered */
	vhpiGenericAssocs = 1529,	/* Iterator for generic assocs */
	vhpiGenericDecls = 1530,	/* Iterator for generic decls */
	vhpiIndexExprs = 1531,		/* Iterator for index expression */
	vhpiIndexedNames = 1532,	/* Iterator for indexed names of an array */
	vhpiInternalRegions = 1533,	/* Iterator for internal scopes */
	vhpiMembers = 1534,		/* Iterator for the members of collection */
	vhpiPackInsts = 1535,		/* Iterator for package instances */
	vhpiParamAssocs = 1536,		/* Iterator for param assocs */
	vhpiParamDecls = 1537,		/* Parameter declarations of a subprogram declaration or subprogram call */
	vhpiPortAssocs = 1538,		/* Iterator for port assocs */
	vhpiPortDecls = 1539,		/* Iterator for port decls */
	vhpiRecordElems = 1540,		/* Iterator for fields of a record */
	vhpiSelectWaveforms = 1541,	/* Iterator for select waveforms */
	vhpiSelectedNames = 1542,	/* Iterator for selected names of a record */
	vhpiSensitivitys = 1543,	/* Iterator for sensitivities */
	vhpiSeqStmts = 1544,		/* Iterator for sequential statements */
	vhpiSigAttrs = 1545,		/* Iterator for signal attributes */
	vhpiSigDecls = 1546,		/* Iterator for signal Declarations */
	vhpiSigNames = 1547,		/* Iterator for signal in the qualified expression */
	vhpiSignals = 1548,		/* Iterator for signal names of a disconnect specification */
	vhpiSpecNames = 1549,		/* Iterator for specification names of the configuration */
	vhpiSpecs = 1550,		/* Iterator for specifications  defined in a region */
	vhpiStmts = 1551,		/* Iterator for statements */
	vhpiTransactions = 1552,	/* Iterator for transactions */
	vhpiTypeMarks = 1553,		/* Iterator for type marks of a subprogram */
	vhpiUnitDecls = 1554,		/* Iterator for units of a physical */
	vhpiUses = 1555,		/* Iterator for uses  clauses */
	vhpiVarDecls = 1556,		/* Iterator for variable declarations */
	vhpiWaveformElems = 1557,	/* Iterator for waveform elements */
	vhpiLibraryDecls = 1558,	/* Iterator for library declarations */
        vhpiLocalLoads = 1559,          /* iterator for loads */

        /* CADENCE NON STD METHOD */
        vhpiUseClauses = 1650           /* Iterator for use clauses */

#ifdef VHPIEXTEND_MANY_METHODS
        VHPIEXTEND_MANY_METHODS
#endif

} vhpiOneToManyT;

/****************** PROPERTIES *******************/
/******* INTEGER or BOOLEAN PROPERTIES **********/
typedef enum {
	vhpiAccessP = 1001,		/* Access type of an object */
	vhpiArgcP = 1002,		/* Number of Argument vectors */
	vhpiAttrKindP = 1003,		/* AttrKind property for Attributes(predefined) */
	vhpiBaseIndexP = 1004,		/* Offset of the indexedname to the base of the entire declaration */
	vhpiBeginLineNoP = 1005,	/* Line number within the file of the begin line */
	vhpiEndLineNoP = 1006,		/* Last line of the unit */
	vhpiEntityClassP = 1007,	/* Entity class */
	vhpiForeignKindP = 1008,	/* Kind of the foreign model func/arch/proc */
	vhpiFrameLevelP = 1009,		/* Stack frame level of the subprogram call */
	vhpiGenerateIndexP = 1010,	/* Generate Index for forGenerate */
	vhpiIntValP = 1011,		/* Integer value of the literal */
	vhpiIsAnonymousP = 1012,	/* Check if the type is anonymous */
	vhpiIsBasicP = 1013,		/* Check if the Signal/Port is Basic */
	vhpiIsCompositeP = 1014,	/* Check if the type is composite */
	vhpiIsDefaultP = 1015,		/* Check if it's a default CompInst */
	vhpiIsDeferredP = 1016,		/* Check if the constant is deferred */
	vhpiIsDiscreteP = 1017,		/* Check if the range is discrete */
	vhpiIsForcedP = 1018,		/* Determines if the object has been externally forced */
	vhpiIsForeignP = 1019,		/* Check if the region is foreign */
	vhpiIsGuardedP = 1020,		/* Determines if the stmt is guarded */
	vhpiIsImplicitDeclP = 1021,	/* Determines if the declaration is implicit */
	vhpiIsInvalidP = 1022,		/* Determines if the handle is invalid */
	vhpiIsLocalP = 1023,		/* Determines if the port or generic is local */
	vhpiIsNamedP = 1024,		/* Determines if the association is named(1) or positional(0)*/
	vhpiIsNullP = 1025,		/* Determines if the range is null */
	vhpiIsOpenP = 1026,		/* Determines if the port is open */
	vhpiIsPLIP = 1027,		/* For VHPI interface */
	vhpiIsPassiveP = 1028,		/* Determines if the procedure or process is passive */
	vhpiIsPostponedP = 1029,	/* Determines if the process is postponed */
	vhpiIsProtectedTypeP = 1030,	/* Determines if the object has a protected type */
	vhpiIsPureP = 1031,		/* Determines if the function is pure */
	vhpiIsResolvedP = 1032,		/* Determines if the sig/port/type is resolved */
	vhpiIsScalarP = 1033,		/* Determines if the type is scalar */
	vhpiIsSeqStmtP = 1034,		/* Determines if the Statement is sequential */
	vhpiIsSharedP = 1035,		/* Determines if the variable is shared */
	vhpiIsTransportP = 1036,	/* Determines if the stmt is transport */
	vhpiIsUnaffectedP = 1037,	/* Determines if the waveform is 'unaffected' */
	vhpiIsUnconstrainedP = 1038,	/* Determines if the range is Unconstrained */
	vhpiIsUninstantiatedP = 1039,	/* Determines if the given handle is un-instantiated */
	vhpiIsUpP = 1040,		/* Returns the direction of the range */
	vhpiIsVitalP = 1041,		 
	vhpiIteratorTypeP = 1042,	
	vhpiKindP = 1043,		/* Kind of the object */
	vhpiLeftBoundP = 1044,		/* Left value of the range */
	vhpiLevelP = 1045,		/* VHDL conformance level : 0,1,2 or 3 */
	vhpiLineNoP = 1046,		/* Line number within the file of an object */
	vhpiLineOffsetP = 1047,		/* Line offset in the source file */
	vhpiLoopIndexP = 1048,		/* Index of a for loop */
	vhpiModeP = 1049,		/* Mode of a declaration */
	vhpiNumDimensionsP = 1050,	/* Dimension of an array */
	vhpiNumFieldsP = 1051,		/* Number of fields in a record */
	vhpiNumGensP = 1052,		/* Number of generics */
	vhpiNumLiteralsP = 1053,	/* Number of literals in an enumeration type */
	vhpiNumMembersP = 1054,		/* Number of members in collection */
	vhpiNumParamsP = 1055,		/* Number of parameters in the function and procedure declaration */
	vhpiNumPortsP = 1056,		/* Number of Ports */
	vhpiOpenModeP = 1057,		/* Open mode of a file declaration */
	vhpiPhaseP = 1058,		/* Different phase of simulation see:vhpiPhaseP */
	vhpiPositionP = 1059,		/* Position of the interface declaration in the interface list */
	vhpiPredefAttrP = 1060,		/* Predefined Attribute values:vhpiStablePA,vhpiQuietPA .. */
	vhpiProtectedLevelP = 1061,	/* Level of protection of design unit */
	vhpiReasonP = 1062,		/* Callback reason */
	vhpiRightBoundP = 1063,		/* Right value of the range */
	vhpiSigKindP = 1064,		/* Signal kind */
	vhpiSizeP = 1065,		/* Scalar size of the valued object */
	vhpiStartLineNoP = 1066,	/* Line number within the file of the first line of the unit */
	vhpiStateP = 1067,		/* State of a callback */
	vhpiStaticnessP = 1068,		/* Expression is locally_static,globally_static or dynamic */
	vhpiVHDLversionP = 1069,	/* VHDL version the tool is compliant with:83,93 or 99 */

        /* MIXED_LANG_PROPERTY */
        vhpiLanguageP = 1200,		/* Language domain (Verilog/VHDL/SysC) of the given object */
	/* CADENCE NON STD PROPERTY */
	vhpiIsDynamicP = 1250		/* Check if the object is declared within a subprogram */

#ifdef VHPIEXTEND_INT_PROPERTIES
        VHPIEXTEND_INT_PROPERTIES
#endif

} vhpiIntPropertyT;

/******* STRING PROPERTIES **********/
typedef enum {
	vhpiCaseNameP = 1301,		/* Name in the case it was declared in */
	vhpiCompNameP = 1302,		/* Component name of the stmt */
	vhpiDefNameP = 1303,		/* DefName of the object e.g: lib:entity:arch */ 
	vhpiFileNameP = 1304,		/* Pathname of the source file */
	vhpiFullCaseNameP = 1305,	/* Case reserved full name */
	vhpiFullNameP = 1306,		/* Full hierarchical from the top of the hierarchy */
	vhpiKindStrP = 1307,		/* Handle Kind */
	vhpiLabelNameP = 1308,		/* Label string of the stmt */
	vhpiLibLogicalNameP = 1309,	/* Logical name where a design unit can be found */
	vhpiLibPhysicalNameP = 1310,	/* Physical name where design unit has been compiled */
	vhpiLogicalNameP = 1311,	/* Logical name of the file decl */
	vhpiLoopLabelNameP = 1312,	/* Loop label name of the stmt */
	vhpiNameP = 1313,		/* Name of the given object handle */
	vhpiOpNameP = 1314,		/* Operator name of the operator */
	vhpiStrValP = 1315,		/* String value of the literal */
	vhpiToolVersionP = 1316,	/* Tool release Version number */
	vhpiUnitNameP = 1317,		/* UnitName of the designUnit */

        /* MIXED LANG PROPERTIES */
	vhpiFullVlogNameP = 1500,	/* Full path name (VHDL names are Verilogized) */
	vhpiFullVHDLNameP = 1501,	/* Full path name (Verilog names are vhdlized) */
	vhpiFullLSNameP = 1502,		/* Full path name (Upper case) using ':' and '.' separators */
	vhpiFullLSCaseNameP = 1503	/* Full path name (VHDL case sensitive) */

#ifdef VHPIEXTEND_STR_PROPERTIES
        VHPIEXTEND_STR_PROPERTIES
#endif

} vhpiStrPropertyT;
/******* REAL PROPERTIES **********/
typedef enum {
	vhpiFloatLeftBoundP = 1601,	/* Float Left Bound of the Range */ 
	vhpiFloatRightBoundP = 1602,	/* Float Right Bound of the Range */
	vhpiRealValP = 1603		/* Real value of the object */
        
#ifdef VHPIEXTEND_REAL_PROPERTIES
        VHPIEXTEND_REAL_PROPERTIES
#endif

} vhpiRealPropertyT;

/******* PHYSICAL PROPERTIES **********/
typedef enum {
	vhpiPhysLeftBoundP = 1651,	/* LeftBound of a Physical Range */
        vhpiPhysPositionP = 1652,	/* Position number of the physical literal */
	vhpiPhysRightBoundP = 1653,	/* RightBound of a Physical Range */
        vhpiPhysValP = 1654,		/* Physical value of the object */
	vhpiPrecisionP = 1655,		/* Simulator precision for representing Time values */
	vhpiSimTimeUnitP = 1656		/* Simulator Tool time unit */

#ifdef VHPIEXTEND_PHYS_PROPERTIES
        VHPIEXTEND_PHYS_PROPERTIES
#endif

} vhpiPhysPropertyT;

/******************* PROPERTY VALUES ************************/

/* vhpiOpenModeP */
#define vhpiInOpen                1001
#define vhpiOutOpen               1002
#define vhpiReadOpen              1003
#define vhpiWriteOpen             1004
#define vhpiAppendOpen            1005

/* vhpiModeP */
#define vhpiInMode                1001
#define vhpiOutMode               1002
#define vhpiInoutMode             1003
#define vhpiBufferMode            1004
#define vhpiLinkageMode           1005

/* vhpiSigKindP */
#define vhpiRegister              1001
#define vhpiBus                   1002
#define vhpiNormal                1003

/* vhpiStaticnessP */
#define vhpiLocallyStatic         1001
#define vhpiGloballyStatic        1002
#define vhpiDynamic               1003

/* vhpiPredefAttrP */
#define vhpiActivePA              1001
#define vhpiAscendingPA           1002
#define vhpiBasePA                1003
#define vhpiDelayedPA             1004
#define vhpiDrivingPA             1005
#define vhpiDriving_valuePA       1006
#define vhpiEventPA               1007
#define vhpiHighPA                1008
#define vhpiImagePA               1009
#define vhpiInstance_namePA       1010
#define vhpiLast_activePA         1011
#define vhpiLast_eventPA          1012
#define vhpiLast_valuePA          1013
#define vhpiLeftPA                1014
#define vhpiLeftofPA              1015
#define vhpiLengthPA              1016
#define vhpiLowPA                 1017
#define vhpiPath_namePA           1018
#define vhpiPosPA                 1019
#define vhpiPredPA                1020
#define vhpiQuietPA               1021
#define vhpiRangePA               1022
#define vhpiReverse_rangePA        1023
#define vhpiRightPA               1024
#define vhpiRightofPA             1025
#define vhpiSimple_namePA          1026
#define vhpiStablePA              1027
#define vhpiSuccPA                1028
#define vhpiTransactionPA         1029
#define vhpiValPA                 1030
#define vhpiValuePA               1031

/* vhpiAttrKindP */
typedef enum {
  vhpiFunctionAK    = 1,
  vhpiRangeAK       = 2,
  vhpiSignalAK      = 3,
  vhpiTypeAK        = 4,
  vhpiValueAK       = 5

#ifdef VHPIEXTEND_ATTR
  VHPIEXTEND_ATTR
#endif

} vhpiAttrKindT;

/* vhpiEntityClassP */
#define vhpiEntityEC		  1001
#define vhpiArchitectureEC	  1002
#define vhpiConfigurationEC	  1003
#define vhpiProcedureEC	  	  1004
#define vhpiFunctionEC	  	  1005
#define vhpiPackageEC	  	  1006
#define vhpiTypeEC	  	  1007
#define vhpiSubtypeEC	  	  1008
#define vhpiConstantEC	  	  1009
#define vhpiSignalEC	  	  1010
#define vhpiVariableEC	  	  1011
#define vhpiComponentEC           1012
#define vhpiLabelEC	  	  1013
#define vhpiLiteralEC	  	  1014
#define vhpiUnitsEC	  	  1015
#define vhpiFileEC		  1016
#define vhpiGroupEC               1017

/* vhpiAccessP */
#define vhpiRead		  1
#define vhpiWrite		  2
#define vhpiConnectivity	  4
#define vhpiNoAccess		  8

/* value for vhpiStateP property for callbacks */
typedef enum {
	vhpiEnable,
	vhpiDisable,
	vhpiMature /* callback has occured */
} vhpiStateT;

/* MIXED LANGUAGE PROPERTY VALUES */
/* vhpiLanguageP */
#define vhpiVHDL                  1001
#define vhpiVerilog               1002
#define vhpiSystemC               1003


/* the following enumeration types are used only for vhpiSimTimeUnitP 
and vhpiPrecisionP property and for setting the unit field of the value 
structure; they represent the physical position of a given
VHDL time unit */
/* time unit physical position values {high, low} */
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiFS;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiPS;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiNS;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiUS;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiMS;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiS;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiMN;
PLI_VEXTERN PLI_DLLISPEC const vhpiPhysT  vhpiHR;

/********************** delay structures **************************/
/* removed ; postponed to next version of the standard */


/* IEEE std_logic values */
#define vhpiU                  0   /* uninitialized */
#define vhpiX                  1   /* unknown */
#define vhpi0                  2   /* forcing 0 */
#define vhpi1                  3   /* forcing 1 */
#define vhpiZ                  4   /* high impedance */
#define vhpiW                  5   /* weak unknown */
#define vhpiL                  6   /* weak 0 */
#define vhpiH                  7   /* weak 1 */
#define vhpiDontCare           8   /* don't care */

/* IEEE std bit values */
#define vhpibit0                0   /* bit 0 */
#define vhpibit1                1   /* bit 1 */

/* IEEE std boolean values */
#define vhpiFalse              0   /* false */
#define vhpiTrue               1   /* true */

/* access types, NULL value */
#define vhpiNullAccess         0   /* equivalent to null */


/************** vhpiPhaseP property values *************/
typedef enum {
       vhpiRegistrationPhase   = 1,
       vhpiAnalysisPhase       = 2,
       vhpiElaborationPhase    = 3,
       vhpiInitializationPhase = 4,
       vhpiSimulationPhase     = 5,
       vhpiTerminationPhase    = 6,
       vhpiSavePhase           = 7,
       vhpiRestartPhase        = 8,
       vhpiResetPhase          = 9
} vhpiPhaseT ;
/**************** PLI error information structure ****************/

typedef enum {
	vhpiNote        = 1, /* same as vpiNotice */
	vhpiWarning     = 2, /* same as vpiWarning */
	vhpiError       = 3, /* same as vpiError */
	vhpiFailure     = 6, /* keep it like that for interoperability with VPI */
	vhpiSystem      = 4, /* same as vpiSystem */
	vhpiInternal    = 5 /* same as vpiInternal */
} vhpiSeverityT;

typedef struct vhpiErrorInfoS
{
  vhpiSeverityT    severity;
  PLI_BYTE8       *message;
  PLI_BYTE8       *str;
  PLI_BYTE8       *file; /* Name of the VHDL file where the VHPI error
                            originated */
  PLI_INT32        line; /* Line number in the VHDL file */
} vhpiErrorInfoT;


/********************* callback structures ************************/
/* callback user data structure */

typedef struct vhpiCbDataS 
{
  PLI_INT32 reason;            /* callback reason */
  PLI_VOID (*cb_rtn) (const struct vhpiCbDataS *);  /* call routine */
  vhpiHandleT obj;             /* trigger object */
  vhpiTimeT *time;             /* callback time */
  vhpiValueT *value;           /* trigger object value */
  PLI_VOID *user_data;         /* pointer to user data to be passed to the
				  callback function */
} vhpiCbDataT;

typedef struct vhpiObjDataS {
    struct vhpiObjDataS *next;
    void     *user_data;
    vhpiValueT   *value;
    void(*cb_rtn)(const struct vhpiCbDataS *);
    vhpiHandleT cb_hdl;
} vhpiObjDataT;
/**************************** CALLBACK REASONS ****************************/
/*************************** Simulation object related ***********************/
/* These are repetitive callbacks */
#define vhpiCbValueChange          1001
#define vhpiCbForce                1002
#define vhpiCbRelease              1003
#define vhpiCbTransaction          1004 /* optional callback reason */

/****************************** Statement related ****************************/
/* These are repetitive callbacks */
#define vhpiCbStmt                 1005
#define vhpiCbResume               1006  /* ganges */
#define vhpiCbSuspend              1007  /* ganges */
/* issue: one time or repetitive callbacks */
#define vhpiCbStartOfSubpCall      1008  /* ganges */
#define vhpiCbEndOfSubpCall        1009  /* ganges */

/****************************** Time related ******************************/
/* the Rep callback reasons are the repeated versions of the callbacks */

#define vhpiCbAfterDelay           1010
#define vhpiCbRepAfterDelay        1011
/*************************** Simulation cycle phase  related *****************/
#define vhpiCbNextTimeStep         1012
#define vhpiCbRepNextTimeStep      1013
#define vhpiCbStartOfNextCycle     1014
#define vhpiCbRepStartOfNextCycle  1015
#define vhpiCbStartOfProcesses     1016 /* new in charles */
#define vhpiCbRepStartOfProcesses  1017 /* new in ldv 3.3 */
#define vhpiCbEndOfProcesses       1018 /* ganges */
#define vhpiCbRepEndOfProcesses    1019 /* new ldv 3.3 */
#define vhpiCbLastKnownDeltaCycle  1020 /* new in ldv 3.3 */
#define vhpiCbRepLastKnownDeltaCycle 1021 /* new in ldv 3.3 */
#define vhpiCbStartOfPostponed     1022 /* ganges */
#define vhpiCbRepStartOfPostponed  1023 /* new in ldv 3.3 */
#define vhpiCbEndOfTimeStep        1024 /* ganges */
#define vhpiCbRepEndOfTimeStep     1025 /* new in ldv 3.3 */

/***************************** Action related *****************************/
/* these are one time callback unless otherwise noted */
#define vhpiCbStartOfTool            1026 /* new in charles */
#define vhpiCbEndOfTool              1027 /* new in charles */
#define vhpiCbStartOfAnalysis        1028 /* new in charles */
#define vhpiCbEndOfAnalysis          1029 /* new in charles */

#define vhpiCbStartOfElaboration   1030 /* new in charles */
#define vhpiCbEndOfElaboration     1031 /* name was cbkEndOfElaboration in tiber */
#define vhpiCbStartOfInitialization 1032 /* Name change in charles */
#define vhpiCbEndOfInitialization  1033 /* new in ldv 3.3 */
#define vhpiCbStartOfSimulation    1034
#define vhpiCbEndOfSimulation      1035
#define vhpiCbQuiescense           1036 /* repetitive */
#define vhpiCbPLIError             1037 /* repetitive */
#define vhpiCbStartOfSave          1038
#define vhpiCbkEndOfSave           1039
#define vhpiCbStartOfRestart       1040
#define vhpiCbEndOfRestart         1041
#define vhpiCbStartOfReset         1042
#define vhpiCbEndOfReset           1043
#define vhpiCbEnterInteractive     1044 /* repetitive */
#define vhpiCbExitInteractive      1045 /* repetitive */
#define vhpiCbSigInterrupt         1046 /* repetitive */

/* Foreign model callbacks */
#define vhpiCbTimeOut              1047 /* non repetitive */
#define vhpiCbRepTimeOut           1048 /* repetitive */
#define vhpiCbSensitivity          1049 /* repetitive */


/**************************** CALLBACK FLAGS ******************************/
#define vhpiReturnCb  0x00000001
#define vhpiDisableCb 0x00000010

/******************** FUNCTION DECLARATIONS *********************/
/* assertion new in ganges */
XXTERN PLI_INT32 vhpi_assert PROTO_PARAMS((PLI_BYTE8 *msg, vhpiSeverityT severity));
/* callback related */

XXTERN vhpiHandleT  vhpi_register_cb     PROTO_PARAMS((vhpiCbDataT *cb_data_p, PLI_INT32 flags));
XXTERN PLI_INT32          vhpi_remove_cb       PROTO_PARAMS((vhpiHandleT cb_obj));
XXTERN PLI_INT32          vhpi_disable_cb      PROTO_PARAMS((vhpiHandleT cb_obj));
XXTERN PLI_INT32          vhpi_enable_cb       PROTO_PARAMS((vhpiHandleT cb_obj));
XXTERN PLI_INT32          vhpi_get_cb_info     PROTO_PARAMS((vhpiHandleT object, vhpiCbDataT *cb_data_p));

/* for obtaining handles */
XXTERN vhpiHandleT   vhpi_handle_by_name  PROTO_PARAMS((const PLI_BYTE8 *name, vhpiHandleT scope));

XXTERN vhpiHandleT   vhpi_handle_by_index PROTO_PARAMS((vhpiOneToManyT itRel, vhpiHandleT parent, PLI_INT32 indx)); 

/* for traversing relationships */
XXTERN vhpiHandleT   vhpi_handle          PROTO_PARAMS((vhpiOneToOneT type, vhpiHandleT referenceHandle));
XXTERN vhpiHandleT   vhpi_iterator         PROTO_PARAMS((vhpiOneToManyT type, vhpiHandleT referenceHandle));
XXTERN vhpiHandleT   vhpi_scan            PROTO_PARAMS((vhpiHandleT iterator));

/* for processsing properties */
XXTERN PLI_INT32          vhpi_get             PROTO_PARAMS((vhpiIntPropertyT property, vhpiHandleT object));
XXTERN const PLI_BYTE8 *       vhpi_get_str         PROTO_PARAMS((vhpiStrPropertyT property, vhpiHandleT object));
XXTERN vhpiRealT       vhpi_get_real        PROTO_PARAMS((vhpiRealPropertyT property, vhpiHandleT object));
/* vhpi_get_phys new in charles */
XXTERN vhpiPhysT       vhpi_get_phys        PROTO_PARAMS((vhpiPhysPropertyT property, vhpiHandleT object));


/* for access to protected types: new in ganges  */
typedef int (*vhpiUserFctT)();
XXTERN PLI_INT32 vhpi_protected_call  PROTO_PARAMS((vhpiHandleT varHdl, vhpiUserFctT userFct, PLI_VOID *userData));

/* value processing */
XXTERN PLI_INT32          vhpi_get_value       PROTO_PARAMS((vhpiHandleT expr, vhpiValueT *value_p));
XXTERN PLI_INT32  vhpi_put_value       PROTO_PARAMS((vhpiHandleT object, vhpiValueT *value_p, PLI_INT32 flags));

/* vhpi_put_value flags */
typedef enum {
  vhpiDeposit,
  vhpiDepositPropagate,
  vhpiForce,
  vhpiForcePropagate,
  vhpiRelease,
  vhpiSizeConstraint,
  /* CADENCE NON STANDARD INTERNAL FLAGS */
  vhpiReleaseKV = 15,
  vhpiSNForcePropagate = 16,
  vhpiForcePropagateDla = 17
} vhpiPutValueFlagsT;

/* vhpi_schedule_transaction: new in ganges */
XXTERN PLI_INT32  vhpi_schedule_transaction PROTO_PARAMS((vhpiHandleT drivHdl, vhpiValueT *value_p, PLI_INT32 numValues, vhpiTimeT *delayp,PLI_INT32 delayMode, vhpiTimeT * pulseRejp));
typedef enum {
  vhpiInertial,
  vhpiTransport
} vhpidelayModeT;

XXTERN PLI_INT32          vhpi_format_value	PROTO_PARAMS((vhpiValueT *in_value_p, vhpiValueT *out_value_p));

/* time processing */
/* the current simulation time is retrieved */
XXTERN void         vhpi_get_time        PROTO_PARAMS((vhpiTimeT  *time_p, long *cycles)); 
/* The next active time */
#define vhpiNoActivity -1
XXTERN PLI_INT32         vhpi_get_nextTime        PROTO_PARAMS((vhpiTimeT  *time_p)); 

/* tool control */
typedef enum {
  vhpiStop,
  vhpiFinish,
  vhpiReset,
  /* CADENCE NON STD ENUM TYPE */
  vhpiRunCmd = 15,
  vhpiSetVar = 16,
  vhpiEnDCMP = 17,
  vhpiEnableSelectTxtRefs = 18,
  vhpiEnableUseClauseNames = 19,
  vhpiEnableCVAEnhancements = 20 /* Flag to activate enhancements requested by CVA in hotfix */
} vhpiControlT;
/* vhpi_control :new in ganges */

XXTERN PLI_INT32   vhpi_control PROTO_PARAMS((vhpiControlT command,
                                                  ...));
/* I/O routine */
XXTERN PLI_INT32          vhpi_printf          PROTO_PARAMS((const PLI_BYTE8 *format,...));

/* utility routines */
XXTERN PLI_INT32          vhpi_compare_handles PROTO_PARAMS((vhpiHandleT handle1, vhpiHandleT handle2));
XXTERN PLI_INT32          vhpi_check_error       PROTO_PARAMS((vhpiErrorInfoT *error_info_p));
/* name change was vhpi_free_handle in charles */
XXTERN PLI_INT32          vhpi_release_handle     PROTO_PARAMS((vhpiHandleT object));

/* creation functions */
XXTERN vhpiHandleT vhpi_create PROTO_PARAMS((vhpiClassKindT kind, vhpiHandleT handle1, vhpiHandleT handle2));

/* Foreign model data structures and functions */
typedef enum {
   vhpiArchF, 
   vhpiFuncF,
   vhpiProcF,
   vhpiLibF,
   vhpiAppF
} vhpiForeignT;

typedef struct vhpiForeignDataS {
    vhpiForeignT kind;
    PLI_BYTE8 * libraryName;
    PLI_BYTE8 * modelName;
    PLI_VOID (*elabf)(const struct vhpiCbDataS *cb_data_p);
    PLI_VOID (*execf)(const struct vhpiCbDataS *cb_data_p);
} vhpiForeignDataT;


XXTERN vhpiHandleT vhpi_register_foreignf PROTO_PARAMS((vhpiForeignDataT *foreignDatap));
XXTERN int vhpi_get_foreign_info PROTO_PARAMS((vhpiHandleT hdl, vhpiForeignDataT *foreignDatap));
/* for saving and restoring foreign models data */
XXTERN PLI_INT32 vhpi_get_data PROTO_PARAMS((PLI_INT32 id, PLI_VOID * dataLoc, PLI_INT32 numBytes));
XXTERN PLI_INT32 vhpi_put_data PROTO_PARAMS((PLI_INT32 id, PLI_VOID * dataLoc, PLI_INT32 numBytes));

/* Cadence non std function prototypes */
XXTERN PLI_INT32          vhpi_is_object_active PROTO_PARAMS((vhpiHandleT stackFrameHdl, vhpiHandleT objHdl)); \
XXTERN PLI_INT32          vhpi_get_dyn_object_value PROTO_PARAMS((vhpiHandleT objHdl, vhpiHandleT stackFrameHdl, vhpiValueT *valuep)); \
XXTERN PLI_INT32          vhpi_get_dynamic PROTO_PARAMS((vhpiIntPropertyT property, vhpiHandleT object, vhpiHandleT subp));

/* internal function prototypes from vhpi_internal.h */

#ifdef VHPIEXTEND_PROTOTYPES
VHPIEXTEND_PROTOTYPES
#endif

/**************************** GLOBAL VARIABLES ****************************/
typedef PLI_VOID (*vhpiBootstrapFctT)();

extern PLI_DLLESPEC vhpiBootstrapFctT *vhpiBootstrapArray[]; /* array of function pointers, */
                                                       /* last pointer should be null */

#undef PLI_EXTERN
#undef PLI_VEXTERN

#ifdef VHPI_USER_DEFINED_DLLISPEC
#undef VHPI_USER_DEFINED_DLLISPEC
#undef PLI_DLLISPEC
#endif
#ifdef VHPI_USER_DEFINED_DLLESPEC
#undef VHPI_USER_DEFINED_DLLESPEC
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

#endif /* VHPI_USER_H */
