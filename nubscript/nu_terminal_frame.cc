//  
// This file is part of nuBScript Project
// Copyright (c) Antonino Calderone (antonino.calderone@gmail.com)
// All rights reserved.  
// Licensed under the MIT License. 
// See COPYING file in the project root for full license information.
//


/* -------------------------------------------------------------------------- */

#include "nu_basic_defs.h"

#ifndef _WIN32
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <vector>
#else
#include "nu_about.h"
#include <windows.h>
#endif


/* -------------------------------------------------------------------------- */

namespace nu {


/* -------------------------------------------------------------------------- */

#ifdef _WIN32

int create_terminal_frame(int argc, char* argv[])
{
    SetConsoleTitle(nu::about::progname);
    return 0;
}

#else


/* -------------------------------------------------------------------------- */

int create_terminal_frame(int argc, char* argv[])
{
    return 0;
}


/* -------------------------------------------------------------------------- */

#endif


/* -------------------------------------------------------------------------- */

} // namespace nu
