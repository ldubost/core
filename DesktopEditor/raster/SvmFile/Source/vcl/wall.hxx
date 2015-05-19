/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: wall.hxx,v $
 * $Revision: 1.3 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _SV_WALL_HXX
#define _SV_WALL_HXX
#ifdef AVS
#include <vcl/sv.h>
#include <vcl/dllapi.h>
#include <tools/color.hxx>
#endif
#include "../tools/color.hxx"

namespace SVMCore{

class Rectangle;
class Gradient;
class BitmapEx;
class ImplWallpaper;

// -------------------
// - Wallpaper-Types -
// -------------------

#define	WALLPAPER_NULL 					WallpaperStyle_NULL
#define	WALLPAPER_TILE					WallpaperStyle_TILE
#define	WALLPAPER_CENTER				WallpaperStyle_CENTER
#define	WALLPAPER_SCALE					WallpaperStyle_SCALE
#define	WALLPAPER_TOPLEFT				WallpaperStyle_TOPLEFT
#define	WALLPAPER_TOP					WallpaperStyle_TOP
#define	WALLPAPER_TOPRIGHT				WallpaperStyle_TOPRIGHT
#define	WALLPAPER_LEFT					WallpaperStyle_LEFT
#define	WALLPAPER_RIGHT					WallpaperStyle_RIGHT
#define	WALLPAPER_BOTTOMLEFT			WallpaperStyle_BOTTOMLEFT
#define	WALLPAPER_BOTTOM				WallpaperStyle_BOTTOM
#define	WALLPAPER_BOTTOMRIGHT			WallpaperStyle_BOTTOMRIGHT
#define	WALLPAPER_APPLICATIONGRADIENT	WallpaperStyle_APPLICATIONGRADIENT
#define	WALLPAPER_FORCE_EQUAL_SIZE		WallpaperStyle_FORCE_EQUAL_SIZE

#ifndef ENUM_WALLPAPERSTYLE_DECLARED
#define ENUM_WALLPAPERSTYLE_DECLARED

enum WallpaperStyle 
{
	WALLPAPER_NULL, 
	WALLPAPER_TILE,
	WALLPAPER_CENTER,
	WALLPAPER_SCALE,
	WALLPAPER_TOPLEFT,		
	WALLPAPER_TOP,		
	WALLPAPER_TOPRIGHT,
	WALLPAPER_LEFT,								
	WALLPAPER_RIGHT,
	WALLPAPER_BOTTOMLEFT,	
	WALLPAPER_BOTTOM,	
	WALLPAPER_BOTTOMRIGHT,
	WALLPAPER_APPLICATIONGRADIENT,          // defines a gradient that internally covers the whole application
                                            // and uses a color derived from the face color
	WALLPAPER_FORCE_EQUAL_SIZE = 0x7fffffff
};

#endif

// -------------
// - Wallpaper -
// -------------

class  Wallpaper
{
private:
	ImplWallpaper*	mpImplWallpaper;

	 void			  ImplMakeUnique( BOOL bReleaseCache = TRUE );
#ifdef AVS
     Gradient       ImplGetApplicationGradient() const;
#endif

//#if 0 // _SOLAR__PRIVATE
public:
	 ImplWallpaper* ImplGetImpWallpaper() const { return mpImplWallpaper; }
//#endif

public:
					Wallpaper();
					Wallpaper( const Wallpaper& rWallpaper );
					Wallpaper( const Color& rColor );
					Wallpaper( const BitmapEx& rBmpEx );
					Wallpaper( const Gradient& rGradient );
					~Wallpaper();

	void			SetColor( const Color& rColor );
	const Color&	GetColor() const;
#ifdef AVS
	void			SetStyle( WallpaperStyle eStyle );
#endif
	WallpaperStyle	GetStyle() const;

	void			SetBitmap( const BitmapEx& rBitmap );
	void			SetBitmap();
	BitmapEx		GetBitmap() const;
	BOOL			IsBitmap() const;

	void			SetGradient( const Gradient& rGradient );
	void			SetGradient();
	Gradient		GetGradient() const;
	BOOL			IsGradient() const;

	void			SetRect( const Rectangle& rRect );
	void			SetRect();
	Rectangle		GetRect() const;
	BOOL			IsRect() const;

	BOOL			IsFixed() const;
	BOOL			IsScrollable() const;

	Wallpaper&		operator=( const Wallpaper& rWallpaper );
#ifdef AVS
	BOOL			operator==( const Wallpaper& rWallpaper ) const;
	BOOL			operator!=( const Wallpaper& rWallpaper ) const
						{ return !(Wallpaper::operator==( rWallpaper )); }
#endif
	BOOL			IsSameInstance( const Wallpaper& rWallpaper ) const
						{ return (mpImplWallpaper == rWallpaper.mpImplWallpaper); }

	friend  SvStream& operator>>( SvStream& rIStm, Wallpaper& rWallpaper );
#ifdef AVS
	friend  SvStream& operator<<( SvStream& rOStm, const Wallpaper& rWallpaper );
#endif
};

}//SVMCore
#endif	// _SV_WALL_HXX
