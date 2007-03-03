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
code.google.com/p/ashlar
*/

#ifndef DOMException
#define DOMException

#include <dom/idomstring.h>

namespace Dom
{
	class DOMException
	{ 
	public:
		enum ExceptionCode { 
			INDEX_SIZE_ERR = 1,
			DOMSTRING_SIZE_ERR = 2,
			HIERARCHY_REQUEST_ERR = 3,
			WRONG_DOCUMENT_ERR = 4,
			INVALID_CHARACTER_ERR = 5,
			NO_DATA_ALLOWED_ERR = 6,
			NO_MODIFICATION_ALLOWED_ERR = 7,
			NOT_FOUND_ERR = 8,
			NOT_SUPPORTED_ERR = 9,
			INUSE_ATTRIBUTE_ERR = 10,
			INVALID_STATE_ERR = 11,
			SYNTAX_ERR = 12,
			INVALID_MODIFICATION_ERR = 13,
			NAMESPACE_ERR = 14,
			INVALID_ACCESS_ERR = 15
		}; 
		ExceptionCode code; 
		const DOMString* msg;
	}; 

}
#endif
