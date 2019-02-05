﻿/*
 * (c) Copyright Ascensio System SIA 2010-2019
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#ifndef _ASC_WIN_API
#define _ASC_WIN_API

#ifndef _WIN32

// from winuser.h ( http://msdn.microsoft.com/en-us/library/windows/desktop/ms724371(v=vs.85).aspx )
#ifndef COLOR_3DDKSHADOW
#define COLOR_3DDKSHADOW            21
#endif

#ifndef COLOR_3DFACE
#define COLOR_3DFACE                15
#endif

#ifndef COLOR_3DHIGHLIGHT
#define COLOR_3DHIGHLIGHT           20
#endif

#ifndef COLOR_3DHILIGHT
#define COLOR_3DHILIGHT             20
#endif

#ifndef COLOR_3DLIGHT
#define COLOR_3DLIGHT               22
#endif

#ifndef COLOR_3DSHADOW
#define COLOR_3DSHADOW              16
#endif

#ifndef COLOR_ACTIVEBORDER
#define COLOR_ACTIVEBORDER          10
#endif

#ifndef COLOR_ACTIVECAPTION
#define COLOR_ACTIVECAPTION         2
#endif

#ifndef COLOR_APPWORKSPACE
#define COLOR_APPWORKSPACE          12
#endif

#ifndef COLOR_BACKGROUND
#define COLOR_BACKGROUND            1
#endif

#ifndef COLOR_BTNFACE
#define COLOR_BTNFACE               15
#endif

#ifndef COLOR_BTNHIGHLIGHT
#define COLOR_BTNHIGHLIGHT          20
#endif

#ifndef COLOR_BTNHILIGHT
#define COLOR_BTNHILIGHT            20
#endif

#ifndef COLOR_BTNSHADOW
#define COLOR_BTNSHADOW             16
#endif

#ifndef COLOR_BTNTEXT
#define COLOR_BTNTEXT               18
#endif

#ifndef COLOR_CAPTIONTEXT
#define COLOR_CAPTIONTEXT           9
#endif

#ifndef COLOR_DESKTOP
#define COLOR_DESKTOP               1
#endif

#ifndef COLOR_GRAYTEXT
#define COLOR_GRAYTEXT              17
#endif

#ifndef COLOR_HIGHLIGHT
#define COLOR_HIGHLIGHT             13
#endif

#ifndef COLOR_HIGHLIGHTTEXT
#define COLOR_HIGHLIGHTTEXT        14
#endif

#ifndef COLOR_HOTLIGHT
#define COLOR_HOTLIGHT              26
#endif

#ifndef COLOR_INACTIVEBORDER
#define COLOR_INACTIVEBORDER        11
#endif

#ifndef COLOR_INACTIVECAPTION
#define COLOR_INACTIVECAPTION        3
#endif


#ifndef COLOR_INACTIVECAPTIONTEXT
#define COLOR_INACTIVECAPTIONTEXT    19
#endif

#ifndef COLOR_INFOBK
#define COLOR_INFOBK                24
#endif

#ifndef COLOR_INFOTEXT
#define COLOR_INFOTEXT              23
#endif

#ifndef COLOR_MENU
#define COLOR_MENU                  4
#endif

#ifndef COLOR_GRADIENTACTIVECAPTION
#define COLOR_GRADIENTACTIVECAPTION 27
#endif

#ifndef COLOR_GRADIENTINACTIVECAPTION
#define COLOR_GRADIENTINACTIVECAPTION 28
#endif

#ifndef COLOR_MENUHILIGHT
#define COLOR_MENUHILIGHT       29
#endif

#ifndef COLOR_MENUBAR
#define COLOR_MENUBAR           30
#endif


#ifndef COLOR_MENUTEXT
#define COLOR_MENUTEXT          7
#endif

#ifndef COLOR_SCROLLBAR
#define COLOR_SCROLLBAR         0
#endif

#ifndef COLOR_WINDOW
#define COLOR_WINDOW            5
#endif

#ifndef COLOR_WINDOWFRAME
#define COLOR_WINDOWFRAME       6
#endif

#ifndef COLOR_WINDOWTEXT
#define COLOR_WINDOWTEXT        8
#endif

static DWORD GetSysColor(const int nIndex)
{
    // get color values from any windows theme
    // http://msdn.microsoft.com/en-us/library/windows/desktop/ms724371(v=vs.85).aspx
    // generated by test from: \TeamlabOffice\trunk\ServerComponents\Test\Applications\Tokenize_Test
    //***************** GetSysColor values begin (Win7 x64) *****************
    DWORD nValue = 0x0;
    //***************** GetSysColor values begin (Win7 x64) *****************
    switch (nIndex) {
    case COLOR_3DDKSHADOW: nValue = 0x696969; break;
    case COLOR_3DFACE: nValue = 0xf0f0f0; break;
    case COLOR_3DHIGHLIGHT: nValue = 0xffffff; break;
    // case COLOR_3DHILIGHT: nValue = 0xffffff; break; // is COLOR_3DHIGHLIGHT
    case COLOR_3DLIGHT: nValue = 0xe3e3e3; break;
    case COLOR_3DSHADOW: nValue = 0xa0a0a0; break;
    case COLOR_ACTIVEBORDER: nValue = 0xb4b4b4; break;
    case COLOR_ACTIVECAPTION: nValue = 0xd1b499; break;
    case COLOR_APPWORKSPACE: nValue = 0xababab; break;
    case COLOR_BACKGROUND: nValue = 0x0; break;
    // case COLOR_BTNFACE: nValue = 0xf0f0f0; break; // is COLOR_3DFACE
    // case COLOR_BTNHIGHLIGHT: nValue = 0xffffff; break; // is COLOR_3DHIGHLIGHT
    // case COLOR_BTNHILIGHT: nValue = 0xffffff; break; // is COLOR_3DHIGHLIGHT
    // case COLOR_BTNSHADOW: nValue = 0xa0a0a0; break; // is COLOR_3DSHADOW
    case COLOR_BTNTEXT: nValue = 0x0; break;
    case COLOR_CAPTIONTEXT: nValue = 0x0; break;
    // case COLOR_DESKTOP: nValue = 0x0; break; // is COLOR_BACKGROUND
    case COLOR_GRADIENTACTIVECAPTION: nValue = 0xead1b9; break;
    case COLOR_GRADIENTINACTIVECAPTION: nValue = 0xf2e4d7; break;
    case COLOR_GRAYTEXT: nValue = 0x6d6d6d; break;
    case COLOR_HIGHLIGHT: nValue = 0xff9933; break;
    case COLOR_HIGHLIGHTTEXT: nValue = 0xffffff; break;
    case COLOR_HOTLIGHT: nValue = 0xcc6600; break;
    case COLOR_INACTIVEBORDER: nValue = 0xfcf7f4; break;
    case COLOR_INACTIVECAPTION: nValue = 0xdbcdbf; break;
    case COLOR_INACTIVECAPTIONTEXT: nValue = 0x544e43; break;
    case COLOR_INFOBK: nValue = 0xe1ffff; break;
    case COLOR_INFOTEXT: nValue = 0x0; break;
    case COLOR_MENU: nValue = 0xf0f0f0; break;
    case COLOR_MENUHILIGHT: nValue = 0xff9933; break;
    case COLOR_MENUBAR: nValue = 0xf0f0f0; break;
    case COLOR_MENUTEXT: nValue = 0x0; break;
    case COLOR_SCROLLBAR: nValue = 0xc8c8c8; break;
    case COLOR_WINDOW: nValue = 0xffffff; break;
    case COLOR_WINDOWFRAME: nValue = 0x646464; break;
    case COLOR_WINDOWTEXT: nValue = 0x0; break;
    default: nValue = 0x0; break;
    } // switch (nIndex)
    //***************** GetSysColor values end *****************
    return nValue;
}


#else
	#include <windows.h>

	#ifndef COLOR_HOTLIGHT
		#define COLOR_HOTLIGHT          26
	#endif

	#ifndef COLOR_GRADIENTACTIVECAPTION
		#define COLOR_GRADIENTACTIVECAPTION 27
	#endif

	#ifndef COLOR_GRADIENTINACTIVECAPTION
		#define COLOR_GRADIENTINACTIVECAPTION 28
	#endif

	#ifndef COLOR_MENUHILIGHT
		#define COLOR_MENUHILIGHT       29
	#endif

	#ifndef COLOR_MENUBAR
		#define COLOR_MENUBAR           30
	#endif
#endif //#ifndef _WIN32
#endif // #ifndef _ASC_WIN_API
