#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <WinSock2.h>
#include <windows.h>
#include <objbase.h>
#include <shellapi.h>

#include "resource.h"
#include "DuiLib\UIlib.h"

#include "document.h"
#include "prettywriter.h"
#include "stringbuffer.h"
#include <string>
#include <fstream>

#include "ostreamwrapper.h"
#include "istreamwrapper.h"

using namespace DuiLib;
using namespace rapidjson;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
