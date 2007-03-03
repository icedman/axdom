/*
Version: MPL 1.1/GPL 2.0/LGPL 2.1

The contents of this file are subject to the Mozilla Public License Version
1.1 (the "License"); you may not use this file except in compliance with
the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the
License.

Copyright 2007
Marvin Sanchez
http://code.google.com/u/m4rvin2005/
*/

#ifndef AX_DOM_CONFIG
#define AX_DOM_CONFIG

#ifdef DOM_DLL
#define DOM_CLASS_EXPORT __declspec(dllexport)
#else
#define DOM_CLASS_EXPORT __declspec(dllimport)
#endif

#ifdef DEBUG
#include <crtdbg.h>
#define LEAK_TRACE { _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF); }
#else
#define LEAK_TRACE
#endif

#endif
