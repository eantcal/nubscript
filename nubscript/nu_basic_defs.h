//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#ifndef __NUBSCRIPT_DEFS_H__
#define __NUBSCRIPT_DEFS_H__


/* -------------------------------------------------------------------------- */

// Scanner config. data
#define NUBSCRIPT_BLANKS " \t\r"
#define NUBSCRIPT_NEWLINES "\n"

#define NUBSCRIPT_OP_INC "++"
#define NUBSCRIPT_OP_DEC "--"

#define NUBSCRIPT_BEGIN_SUBEXPR '('
#define NUBSCRIPT_END_SUBEXPR ')'
#define NUBSCRIPT_BEGIN_STRING "\""
#define NUBSCRIPT_END_STRING "\""
#define NUBSCRIPT_ESCAPE_CHAR '\\'
#define NUBSCRIPT_BEGIN_SUBSCR '['
#define NUBSCRIPT_END_SUBSCR ']'

#define NUBSCRIPT_PARAM_SEP ","

#define NUBSCRIPT_EXPONENT_SYMB 'E'

#define NUBSCRIPT_BEGIN_SUBEXPR_OP "("
#define NUBSCRIPT_END_SUBEXPR_OP ")"
#define NUBSCRIPT_BEGIN_SUBSCR_OP "["
#define NUBSCRIPT_END_SUBSCR_OP "]"

#define NUBSCRIPT_SINGLE_CHAR_OPS ".+-*/^,\\=\";:<>?'"
#define NUBSCRIPT_WORD_OPS                                                      \
    {                                                                          \
        "bxor", "band", "bshr", "bshl", "bor", NUBSCRIPT_OP_INC,                \
            NUBSCRIPT_OP_DEC, "mod", "div", "xor", "and", "or", "<>", "<=",     \
            ">="                                                               \
    }
#define NUBSCRIPT_BEGIN_SUBEXPR '('
#define NUBSCRIPT_END_SUBEXPR ')'
#define NUBSCRIPT_BEGIN_STRING "\""
#define NUBSCRIPT_END_STRING "\""
#define NUBSCRIPT_ESCAPE_CHAR '\\'


/* -------------------------------------------------------------------------- */

// Error strings
#define NUBSCRIPT_ERROR_STR__SYNTAXERROR "Syntax Error"
#define NUBSCRIPT_ERROR_STR__ERRORLOADING "Error loading file or file not found"


/* -------------------------------------------------------------------------- */

// Console prompt
#define NUBSCRIPT_MSG_STR__READY "Ready."
#define NUBSCRIPT_PROMPT_STR "Ok."
#define NUBSCRIPT_PROMPT_NEWLINE "\n"


/* -------------------------------------------------------------------------- */

// Xterm config
#define NUBSCRIPT_HELP "-h"


/* -------------------------------------------------------------------------- */

// Command line shortcut

#define NUBSCRIPT_HELP_MACRO 'h' // -h --> HELP "<argument>"
#define NUBSCRIPT_EXEC_MACRO 'e' // -e --> EXEC "<argument>"
#define NUBSCRIPT_LOAD_MACRO 'l' // -l --> LOAD "<argument>"


/* -------------------------------------------------------------------------- */

#endif
