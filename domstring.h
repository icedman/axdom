/*
Version: MPL 1.1/GPL 2.0/LGPL 2.1

The contents of this file are subject to the Mozilla Public License Version
1.1 (the "License")=0; you may not use this file except in compliance with
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

#ifndef AX_DOMSTRING
#define AX_DOMSTRING

#include <dom/domcfg.h>
#include <string.h>

namespace Dom
{
	typedef unsigned short* DOMString;

#define DOMSTR (Dom::DOMString*)

	// no support for unicode yet
#ifdef DOM_UNICODE
#define UNICODE
#define _UNICODE
#include <wchar.h>
	typedef wchar_t DOMCHAR;
#else
	typedef char DOMCHAR;
#endif

	inline bool IsWhiteSpace(DOMString *s)
	{
		int space = 0;
		char *str =(DOMCHAR*)s;
		int len = strlen(str);
		for(int i=0;i<len;i++)
		{
			if (str[i]==' ' || str[i]=='\t' || str[i]=='\n')
				space++;
		}
		return space == len;
	}

}

#endif