
/*******************************************************************************
 * File: rtCmd.h
 *
 *
 * This file contains type definitions as well as routine declarations used
 * by our Customers (Internal and External) to enhance NCSim command line. 
 *
 * Under no circumstances any value of the #define'ed in this file or function 
 * prototypes can be ultared. Any changes to this file will cause an error 
 * during runtime.
 * 
 ******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include "tcl.h"

typedef  void * rtCommandClassT;
typedef  void * rtCommandT;
typedef  void * rtCmdSwitchT;
typedef  void * rtCmdProc;
typedef  void   Tcl_cmdProc;

/*
 * getClassHandle
 * Params:
 *     pointer to handle for class to be returned
 *     name of class being created
 *     help string for class
 *
 * Returns:
 *     0 on success
 *     1 on failure
 *
 * If className exist, return that handle otherwise create a new class.
 * The class mechanism is used primarily to group commands in help messages.
 * 
 */
extern rtCommandClassT getClassHandle (char *className, char *help); 

/*
 * addCommand
 *
 * Params:
 *      pointer to handle to be returned
 *      command class in which it is being registered
 *      name of command being registered
 *
 * Returns:
 *      0 on success
 *      1 on failure - error message will be printed
 * 
 * Register a command name and a retrieve a handle for it
 *
 */
extern 	int 	addCommand (rtCommandT *cmd,
			    rtCommandClassT class,
               		    char *name,
			    char *args,
			    char *help,
			    int  flags,    
			    int  user_data,  
			    int match_chars, 
			    Tcl_CmdProc *tcl_proc );

extern 	void 	addSwitch (rtCmdSwitchT *modifier,
			   char *name,
			   char *args,
			   char *help,
			   int  flags,  
			   int  user_data, 
			   int match_chars);

extern 	void 	bindSwitchToCmd (rtCmdSwitchT modifier,
				 rtCommandT cmd);

extern 	void 	bindSwitchToSwitch (rtCmdSwitchT handle, 
				    rtCmdSwitchT modifier);

extern 	rtCmdProc     *initSimCmd();            /* allocate a new command struct */

extern 	int 	      getSimCmdID();	        /* Assign a new command ID  */

extern void     *getTclInterpHandle ();   /* Return Tcl_Interp use by NCSim  */

/*
 * The following flags are used when creating commands to indicate
 * special conditions. These are passed in the flags parameter
 */
#define CMD_NOFLAGS     0x0000 /* Use instead of NULL for flag word */
#define CMD_NEVER	  0x0001 /* Will never be implemented - obsolete */
#define CMD_FUTURE	  0x0002 /* Will not be implemented any time soon */
#define CMD_NOTYET	  0x0004 /* Should be implemented by and by */
#define CMD_HIDDEN      0x0008 /* Internal command, never seen by user */
#define CMD_ALT_REGISTER 0x0010 /* Alternative registration technique:
                                 * Used to register AMSUltra's TCL */

/*
 * The following flags are used in creating new switches to commands.
 */
#define CMD_MOD_NOFLAGS  0x0000  /* Use in place of NULL for modifier flag parameter */
#define CMD_MOD_OPTIONAL 0x0001  /* indicates to the interpreter that this option
				    should be returned if the given modifier is
				    NULL or unrecognized. */
#define CMD_MOD_DEFAULT  0x0002  /* Argument is optional, but not a default.
				    This only effects the help message */
#define CMD_MOD_NEVER    0x0010  /* Will never be implemented - obsolete */
#define CMD_MOD_FUTURE   0x0020  /* Will not be implemented any time soon */
#define CMD_MOD_NOTYET   0x0040  /* Should be implemented by and by */
#define CMD_MOD_HIDDEN   0x0080  /* Internal command, never seen by user */

/*
 * Legal values for user_data for the addSwitch()  routine 
 */
#define ATTRIBUTE_ACTIVE	0
#define ATTRIBUTE_DELAYED	1
#define ATTRIBUTE_EVENT		2
#define ATTRIBUTE_LAST_ACTIVE	3
#define ATTRIBUTE_LAST_EVENT	4
#define ATTRIBUTE_LAST_VALUE	5
#define ATTRIBUTE_QUIET		6
#define ATTRIBUTE_STABLE	7
#define ATTRIBUTE_TRANSACTION	8
#define ATTRIBUTE_NMODS		9
