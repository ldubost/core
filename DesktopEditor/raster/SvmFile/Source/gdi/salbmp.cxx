/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: salbmp.cxx,v $
 * $Revision: 1.13 $
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
#ifdef AVS
// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_vcl.hxx"
#include <tools/svwin.h>
#include <wincomp.hxx>
#include <vcl/salbtype.hxx>
#include <salgdi.h>
#include <saldata.hxx>
#include <salbmp.h>
#include <vcl/bitmap.hxx> // for BitmapSystemData
#include <string.h>
#endif
#include "../ASC/OpenOfficeBasic.h"
#include "../vcl/salbtype.hxx"
#include "../vcl/salgdi.h"
#include "../vcl/salbmp.h"
#include "../vcl/bitmap.hxx"

namespace SVMCore{
SalBitmap* GetWinBitmap()
{
	return new WinSalBitmap();
}
}
// -----------
// - Inlines -
// -----------

inline void ImplSetPixel4( const HPBYTE pScanline, long nX, const BYTE cIndex )
{
	BYTE& rByte = pScanline[ nX >> 1 ];

	( nX & 1 ) ? ( rByte &= 0xf0, rByte |= ( cIndex & 0x0f ) ) :
				 ( rByte &= 0x0f, rByte |= ( cIndex << 4 ) );
}


// ----------------
// - WinSalBitmap -
// ----------------

WinSalBitmap::WinSalBitmap() :
		mhDIB		( 0 ),
		mhDDB		( 0 ),
		mnBitCount	( 0 )
{
}

// ------------------------------------------------------------------

WinSalBitmap::~WinSalBitmap()
{
	Destroy();
}


// ------------------------------------------------------------------

bool WinSalBitmap::Create( HANDLE hBitmap, bool bDIB, bool bCopyHandle )
{
	bool bRet = TRUE;

	if( bDIB )
		mhDIB = (HGLOBAL) ( bCopyHandle ? ImplCopyDIBOrDDB( hBitmap, TRUE ) : hBitmap );
	else
		mhDDB = (HBITMAP) ( bCopyHandle ? ImplCopyDIBOrDDB( hBitmap, FALSE ) : hBitmap );

	if( mhDIB )
	{
		PBITMAPINFOHEADER pBIH = (PBITMAPINFOHEADER) GlobalLock( mhDIB );

		maSize = SvmSize( pBIH->biWidth, pBIH->biHeight );
		mnBitCount = pBIH->biBitCount;

		if( mnBitCount )
			mnBitCount = ( mnBitCount <= 1 ) ? 1 : ( mnBitCount <= 4 ) ? 4 : ( mnBitCount <= 8 ) ? 8 : 24;

		GlobalUnlock( mhDIB );
	}
	else if( mhDDB )
	{
		BITMAP	aDDBInfo;

		if( WIN_GetObject( mhDDB, sizeof( BITMAP ), &aDDBInfo ) )
		{
			maSize = SvmSize( aDDBInfo.bmWidth, aDDBInfo.bmHeight );
			mnBitCount = aDDBInfo.bmPlanes * aDDBInfo.bmBitsPixel;

			if( mnBitCount )
			{
				mnBitCount = ( mnBitCount <= 1 ) ? 1 :
							 ( mnBitCount <= 4 ) ? 4 :
							 ( mnBitCount <= 8 ) ? 8 : 24;
			}
		}
		else
		{
			mhDDB = 0;
			bRet = FALSE;
		}
	}
	else
		bRet = FALSE;

	return bRet;
}

// ------------------------------------------------------------------

bool WinSalBitmap::Create( const SvmSize& rSize, USHORT nBitCount, const BitmapPalette& rPal )
{
	bool bRet = FALSE;

	mhDIB = ImplCreateDIB( rSize, nBitCount, rPal );

	if( mhDIB )
	{
		maSize = rSize;
		mnBitCount = nBitCount;
		bRet = TRUE;
	}

	return bRet;
}

// ------------------------------------------------------------------

bool WinSalBitmap::Create( const SalBitmap& rSSalBitmap )
{
	bool bRet = FALSE;
    const WinSalBitmap& rSalBitmap = static_cast<const WinSalBitmap&>(rSSalBitmap);

	if ( rSalBitmap.mhDIB || rSalBitmap.mhDDB )
	{
		HANDLE hNewHdl = ImplCopyDIBOrDDB( rSalBitmap.mhDIB ? rSalBitmap.mhDIB : rSalBitmap.mhDDB,
										   rSalBitmap.mhDIB != 0 );

		if ( hNewHdl )
		{
			if( rSalBitmap.mhDIB )
				mhDIB = (HGLOBAL) hNewHdl;
			else if( rSalBitmap.mhDDB )
				mhDDB = (HBITMAP) hNewHdl;

			maSize = rSalBitmap.maSize;
			mnBitCount = rSalBitmap.mnBitCount;

			bRet = TRUE;
		}
	}

	return bRet;
}

// ------------------------------------------------------------------

bool WinSalBitmap::Create( const SalBitmap& rSSalBmp, SalGraphics* pSGraphics )
{
	bool bRet = FALSE;

    const WinSalBitmap& rSalBmp = static_cast<const WinSalBitmap&>(rSSalBmp);
    WinSalGraphics* pGraphics = static_cast<WinSalGraphics*>(pSGraphics);

	if( rSalBmp.mhDIB )
	{
		PBITMAPINFO 		pBI = (PBITMAPINFO) GlobalLock( rSalBmp.mhDIB );
		PBITMAPINFOHEADER	pBIH = (PBITMAPINFOHEADER) pBI;
		HDC 				hDC  = pGraphics->mhDC;
		HBITMAP 			hNewDDB;
		BITMAP				aDDBInfo;
		PBYTE				pBits = (PBYTE) pBI + *(DWORD*) pBI +
							ImplGetDIBColorCount( rSalBmp.mhDIB ) * sizeof( RGBQUAD );

		if( pBIH->biBitCount == 1 )
		{
			hNewDDB = CreateBitmap( pBIH->biWidth, pBIH->biHeight, 1, 1, NULL );

			if( hNewDDB )
				SetDIBits( hDC, hNewDDB, 0, pBIH->biHeight, pBits, pBI, DIB_RGB_COLORS );
		}
		else
			hNewDDB = CreateDIBitmap( hDC, (PBITMAPINFOHEADER) pBI, CBM_INIT, pBits, pBI, DIB_RGB_COLORS );

		GlobalUnlock( rSalBmp.mhDIB );

		if( hNewDDB && WIN_GetObject( hNewDDB, sizeof( BITMAP ), &aDDBInfo ) )
		{
			mhDDB = hNewDDB;
			maSize = SvmSize( aDDBInfo.bmWidth, aDDBInfo.bmHeight );
			mnBitCount = aDDBInfo.bmPlanes * aDDBInfo.bmBitsPixel;

			bRet = TRUE;
		}
		else if( hNewDDB )
			DeleteObject( hNewDDB );
	}

	return bRet;
}

// ------------------------------------------------------------------

bool WinSalBitmap::Create( const SalBitmap& rSSalBmp, USHORT nNewBitCount )
{
	bool bRet = FALSE;

    const WinSalBitmap& rSalBmp = static_cast<const WinSalBitmap&>(rSSalBmp);

	if( rSalBmp.mhDDB )
	{
		mhDIB = ImplCreateDIB( rSalBmp.maSize, nNewBitCount, BitmapPalette() );

		if( mhDIB )
		{
			PBITMAPINFO pBI = (PBITMAPINFO) GlobalLock( mhDIB );
			const int	nLines = (int) rSalBmp.maSize.Height();
			HDC 		hDC = GetDC( 0 );
			PBYTE		pBits = (PBYTE) pBI + *(DWORD*) pBI +
								ImplGetDIBColorCount( mhDIB ) * sizeof( RGBQUAD );
#ifdef AVS
			SalData*	pSalData = GetSalData();
			HPALETTE	hOldPal = 0;

			if ( pSalData->mhDitherPal )
			{
				hOldPal = SelectPalette( hDC, pSalData->mhDitherPal, TRUE );
				RealizePalette( hDC );
			}
#endif
			if( GetDIBits( hDC, rSalBmp.mhDDB, 0, nLines, pBits, pBI, DIB_RGB_COLORS ) == nLines )
			{
				GlobalUnlock( mhDIB );
				maSize = rSalBmp.maSize;
				mnBitCount = nNewBitCount;
				bRet = TRUE;
			}
			else
			{
				GlobalUnlock( mhDIB );
				GlobalFree( mhDIB );
				mhDIB = 0;
			}
#ifdef AVS
			if( hOldPal )
				SelectPalette( hDC, hOldPal, TRUE );
#endif
			ReleaseDC( 0, hDC );
		}
	}

	return bRet;
}

// ------------------------------------------------------------------

void WinSalBitmap::Destroy()
{
	if( mhDIB )
		GlobalFree( mhDIB );
#ifdef AVS
	else if( mhDDB )
		DeleteObject( mhDDB );
#endif
	if( mhDDB ) //��-�� ���� ��� ��������� ������������� mhDDB -> mhDIB
		DeleteObject( mhDDB );

	maSize = SvmSize();
	mnBitCount = 0;
}

// ------------------------------------------------------------------

USHORT WinSalBitmap::ImplGetDIBColorCount( HGLOBAL hDIB )
{
	USHORT nColors = 0;

	if( hDIB )
	{
		PBITMAPINFO 		pBI = (PBITMAPINFO) GlobalLock( hDIB );
		PBITMAPINFOHEADER	pBIH = (PBITMAPINFOHEADER) pBI;

		if ( pBIH->biSize != sizeof( BITMAPCOREHEADER ) )
		{
			if( pBIH->biBitCount <= 8 )
			{
				if ( pBIH->biClrUsed )
					nColors = (USHORT) pBIH->biClrUsed;
				else
					nColors = 1 << pBIH->biBitCount;
			}
		}
		else if( ( (PBITMAPCOREHEADER) pBI )->bcBitCount <= 8 )
			nColors = 1 << ( (PBITMAPCOREHEADER) pBI )->bcBitCount;

		GlobalUnlock( hDIB );
	}

	return nColors;
}

// ------------------------------------------------------------------

HGLOBAL WinSalBitmap::ImplCreateDIB( const SvmSize& rSize, USHORT nBits, const BitmapPalette& rPal )
{
	//DBG_ASSERT( nBits == 1 || nBits == 4 || nBits == 8 || nBits == 16 || nBits == 24, "Unsupported BitCount!" );

	HGLOBAL hDIB = 0;

	if ( rSize.Width() && rSize.Height() )
	{
		const ULONG 	nImageSize = SVMCore::AlignedWidth4Bytes( nBits * rSize.Width() ) * rSize.Height();
		const USHORT	nColors = ( nBits <= 8 ) ? ( 1 << nBits ) : 0;

		hDIB = GlobalAlloc( GHND, sizeof( BITMAPINFOHEADER ) + nColors * sizeof( RGBQUAD ) + nImageSize );

		if( hDIB )
		{
			PBITMAPINFO 		pBI = (PBITMAPINFO) GlobalLock( hDIB );
			PBITMAPINFOHEADER	pBIH = (PBITMAPINFOHEADER) pBI;

			pBIH->biSize = sizeof( BITMAPINFOHEADER );
			pBIH->biWidth = rSize.Width();
			pBIH->biHeight = rSize.Height();
			pBIH->biPlanes = 1;
			pBIH->biBitCount = nBits;
			pBIH->biCompression = BI_RGB;
			pBIH->biSizeImage = nImageSize;
			pBIH->biXPelsPerMeter = 0;
			pBIH->biYPelsPerMeter = 0;
			pBIH->biClrUsed = 0;
			pBIH->biClrImportant = 0;

			if ( nColors )
			{
				const USHORT nMinCount = SVMCore::Min( nColors, rPal.GetEntryCount() );

				if( nMinCount )
					memcpy( pBI->bmiColors, rPal.ImplGetColorBuffer(), nMinCount * sizeof( RGBQUAD ) );
			}

			GlobalUnlock( hDIB );
		}
	}

	return hDIB;
}

// ------------------------------------------------------------------

HANDLE WinSalBitmap::ImplCopyDIBOrDDB( HANDLE hHdl, bool bDIB )
{
	HANDLE	hCopy = 0;

	if ( bDIB && hHdl )
	{
		const ULONG nSize = GlobalSize( hHdl );

		if ( (hCopy = GlobalAlloc( GHND, nSize  )) != 0 )
		{
			memcpy( (LPSTR) GlobalLock( hCopy ), (LPSTR) GlobalLock( hHdl ), nSize );

			GlobalUnlock( hCopy );
			GlobalUnlock( hHdl );
		}
	}
	else if ( hHdl )
	{
		BITMAP aBmp;

		// Source-Bitmap nach Groesse befragen
		WIN_GetObject( hHdl, sizeof( BITMAP ), (LPSTR) &aBmp );

		// Destination-Bitmap erzeugen
		if ( (hCopy = CreateBitmapIndirect( &aBmp )) != 0 )
		{
			HDC 	hBmpDC = CreateCompatibleDC( 0 );
			HBITMAP hBmpOld = (HBITMAP) SelectObject( hBmpDC, hHdl );
			HDC 	hCopyDC = CreateCompatibleDC( hBmpDC );
			HBITMAP hCopyOld = (HBITMAP) SelectObject( hCopyDC, hCopy );

			BitBlt( hCopyDC, 0, 0, aBmp.bmWidth, aBmp.bmHeight, hBmpDC, 0, 0, SRCCOPY );

			SelectObject( hCopyDC, hCopyOld );
			DeleteDC( hCopyDC );

			SelectObject( hBmpDC, hBmpOld );
			DeleteDC( hBmpDC );
		}
	}

	return hCopy;
}

// ------------------------------------------------------------------

BitmapBuffer* WinSalBitmap::AcquireBuffer( bool /*bReadOnly*/ )
{
	BitmapBuffer* pBuffer = NULL;
#ifndef AVS_INSERT
	if( mhDDB && !mhDIB )
	{
		BITMAPINFOHEADER	bi;
		LPBITMAPINFOHEADER 	lpbi;
		DWORD			dwLen;
		HANDLE			hDIB;
		HANDLE			handle;
		HDC 			hDC;
		HPALETTE		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
		DWORD dwCompression = BI_RGB;

		// Initialize the bitmapinfoheader
		bi.biSize		= sizeof(BITMAPINFOHEADER);
		bi.biWidth		= maSize.getWidth();
		bi.biHeight 		= maSize.getHeight();
		bi.biPlanes 		= 1;
		bi.biBitCount		= 1 * mnBitCount;
		bi.biCompression	= dwCompression;
		bi.biSizeImage		= 0;
		bi.biXPelsPerMeter	= 0;
		bi.biYPelsPerMeter	= 0;
		bi.biClrUsed		= 0;
		bi.biClrImportant	= 0;

		// Compute the size of the  infoheader and the color table
		int nColors = (1 << bi.biBitCount);
		if( nColors > 256 ) 
			nColors = 0;
		dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

		// We need a device context to get the DIB from
		hDC = GetDC(NULL);
		hPal = SelectPalette(hDC,hPal,FALSE);
		RealizePalette(hDC);

		// Allocate enough memory to hold bitmapinfoheader and color table
		hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

		if (!hDIB){
			SelectPalette(hDC,hPal,FALSE);
			ReleaseDC(NULL,hDC);
			return NULL;
		}

		lpbi = (LPBITMAPINFOHEADER)hDIB;

		*lpbi = bi;

		// Call GetDIBits with a NULL lpBits param, so the device driver 
		// will calculate the biSizeImage field 
		GetDIBits(hDC, mhDDB, 0L, (DWORD)bi.biHeight,
				(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

		bi = *lpbi;

		// If the driver did not fill in the biSizeImage field, then compute it
		// Each scan line of the image is aligned on a DWORD (32bit) boundary
		if (bi.biSizeImage == 0){
			bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
							* bi.biHeight;

			// If a compression scheme is used the result may infact be larger
			// Increase the size to account for this.
			if (dwCompression != BI_RGB)
				bi.biSizeImage = (bi.biSizeImage * 3) / 2;
		}

		// Realloc the buffer so that it can hold all the bits
		dwLen += bi.biSizeImage;
		if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
			hDIB = handle;
		else{
			GlobalFree(hDIB);

			// Reselect the original palette
			SelectPalette(hDC,hPal,FALSE);
			ReleaseDC(NULL,hDC);
			return NULL;
		}

		// Get the bitmap bits
		lpbi = (LPBITMAPINFOHEADER)hDIB;

		// FINALLY get the DIB
		BOOL bGotBits = GetDIBits( hDC, mhDDB,
					0L,				// Start scan line
					(DWORD)bi.biHeight,		// # of scan lines
					(LPBYTE)lpbi 			// address for bitmap bits
					+ (bi.biSize + nColors * sizeof(RGBQUAD)),
					(LPBITMAPINFO)lpbi,		// address of bitmapinfo
					(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

		if( !bGotBits )
		{
			GlobalFree(hDIB);
			
			SelectPalette(hDC,hPal,FALSE);
			ReleaseDC(NULL,hDC);
			return NULL;
		}

		SelectPalette(hDC,hPal,FALSE);
		ReleaseDC(NULL,hDC);
		mhDIB = hDIB;
	}
#endif
	if( mhDIB )
	{
		PBITMAPINFO 		pBI = (PBITMAPINFO) GlobalLock( mhDIB );
		PBITMAPINFOHEADER	pBIH = (PBITMAPINFOHEADER) pBI;

		if( ( pBIH->biCompression == BI_RLE4 ) || ( pBIH->biCompression == BI_RLE8 ) )
		{
			SvmSize	aSizePix( pBIH->biWidth, pBIH->biHeight );
			HGLOBAL hNewDIB = ImplCreateDIB( aSizePix, pBIH->biBitCount, BitmapPalette() );

			if( hNewDIB )
			{
				PBITMAPINFO 		pNewBI = (PBITMAPINFO) GlobalLock( hNewDIB );
				PBITMAPINFOHEADER	pNewBIH = (PBITMAPINFOHEADER) pNewBI;
				const USHORT		nColorCount = ImplGetDIBColorCount( hNewDIB );
				const ULONG 		nOffset = *(DWORD*) pBI + nColorCount * sizeof( RGBQUAD );
				BYTE*				pOldBits = (PBYTE) pBI + nOffset;
				BYTE*				pNewBits = (PBYTE) pNewBI + nOffset;

				memcpy( pNewBI, pBI, nOffset );
				pNewBIH->biCompression = 0;
				ImplDecodeRLEBuffer( pOldBits, pNewBits, aSizePix, pBIH->biCompression == BI_RLE4 );

				GlobalUnlock( mhDIB );
				GlobalFree( mhDIB );
				mhDIB = hNewDIB;
				pBI = pNewBI;
				pBIH = pNewBIH;
			}
		}

		if( pBIH->biPlanes == 1 )
		{
			pBuffer = new BitmapBuffer;

			pBuffer->mnFormat = BMP_FORMAT_BOTTOM_UP |
								( pBIH->biBitCount == 1 ? BMP_FORMAT_1BIT_MSB_PAL :
								  pBIH->biBitCount == 4 ? BMP_FORMAT_4BIT_MSN_PAL :
								  pBIH->biBitCount == 8 ? BMP_FORMAT_8BIT_PAL :
								  pBIH->biBitCount == 16 ? BMP_FORMAT_16BIT_TC_LSB_MASK :
								  pBIH->biBitCount == 24 ? BMP_FORMAT_24BIT_TC_BGR :
								  pBIH->biBitCount == 32 ? BMP_FORMAT_32BIT_TC_MASK : 0UL );

			if( BMP_SCANLINE_FORMAT( pBuffer->mnFormat ) )
			{
				pBuffer->mnWidth = maSize.Width();
				pBuffer->mnHeight = maSize.Height();
				pBuffer->mnScanlineSize = SVMCore::AlignedWidth4Bytes( maSize.Width() * pBIH->biBitCount );
				pBuffer->mnBitCount = (USHORT) pBIH->biBitCount;

				if( pBuffer->mnBitCount <= 8 )
				{
					const USHORT nPalCount = ImplGetDIBColorCount( mhDIB );

					pBuffer->maPalette.SetEntryCount( nPalCount );
					memcpy( pBuffer->maPalette.ImplGetColorBuffer(), pBI->bmiColors, nPalCount * sizeof( RGBQUAD ) );
					pBuffer->mpBits = (PBYTE) pBI + *(DWORD*) pBI + nPalCount * sizeof( RGBQUAD );
				}
				else if( ( pBIH->biBitCount == 16 ) || ( pBIH->biBitCount == 32 ) )
				{
					ULONG nOffset = 0UL;

					if( pBIH->biCompression == BI_BITFIELDS )
					{
						nOffset = 3 * sizeof( RGBQUAD );
						pBuffer->maColorMask = ColorMask( *(UINT32*) &pBI->bmiColors[ 0 ],
														  *(UINT32*) &pBI->bmiColors[ 1 ],
														  *(UINT32*) &pBI->bmiColors[ 2 ] );
					}
					else if( pBIH->biBitCount == 16 )
						pBuffer->maColorMask = ColorMask( 0x00007c00UL, 0x000003e0UL, 0x0000001fUL );
					else
						pBuffer->maColorMask = ColorMask( 0x00ff0000UL, 0x0000ff00UL, 0x000000ffUL );

					pBuffer->mpBits = (PBYTE) pBI + *(DWORD*) pBI + nOffset;
				}
				else
					pBuffer->mpBits = (PBYTE) pBI + *(DWORD*) pBI;
			}
			else
			{
				GlobalUnlock( mhDIB );
				delete pBuffer;
				pBuffer = NULL;
			}
		}
		else
			GlobalUnlock( mhDIB );
	}

	return pBuffer;
}

// ------------------------------------------------------------------

void WinSalBitmap::ReleaseBuffer( BitmapBuffer* pBuffer, bool bReadOnly )
{
	if( pBuffer )
	{
		if( mhDIB )
		{
			if( !bReadOnly && !!pBuffer->maPalette )
			{
				PBITMAPINFO 	pBI = (PBITMAPINFO) GlobalLock( mhDIB );
				const USHORT	nCount = pBuffer->maPalette.GetEntryCount();

				memcpy( pBI->bmiColors, pBuffer->maPalette.ImplGetColorBuffer(), nCount * sizeof( RGBQUAD ) );
				GlobalUnlock( mhDIB );
			}

			GlobalUnlock( mhDIB );
		}

		delete pBuffer;
	}
}

// ------------------------------------------------------------------

void WinSalBitmap::ImplDecodeRLEBuffer( const BYTE* pSrcBuf, BYTE* pDstBuf,
									 const SvmSize& rSizePixel, bool bRLE4 )
{
	HPBYTE			pRLE = (HPBYTE) pSrcBuf;
	HPBYTE			pDIB = (HPBYTE) pDstBuf;
	HPBYTE			pRow = (HPBYTE) pDstBuf;
	ULONG			nWidthAl = SVMCore::AlignedWidth4Bytes( rSizePixel.Width() * ( bRLE4 ? 4UL : 8UL ) );
	HPBYTE			pLast = pDIB + rSizePixel.Height() * nWidthAl - 1;
	ULONG			nCountByte;
	ULONG			nRunByte;
	ULONG			nX = 0;
	ULONG			i;
	BYTE			cTmp;
	bool			bEndDecoding = FALSE;

	if( pRLE && pDIB )
	{
		do
		{
			if( ( nCountByte = *pRLE++ ) == 0 )
			{
				nRunByte = *pRLE++;

				if( nRunByte > 2UL )
				{
					if( bRLE4 )
					{
						nCountByte = nRunByte >> 1UL;

						for( i = 0; i < nCountByte; i++ )
						{
							cTmp = *pRLE++;
							ImplSetPixel4( pDIB, nX++, cTmp >> 4 );
							ImplSetPixel4( pDIB, nX++, cTmp & 0x0f );
						}

						if( nRunByte & 1 )
							ImplSetPixel4( pDIB, nX++, *pRLE++ >> 4 );

						if( ( ( nRunByte + 1 ) >> 1 ) & 1 )
							pRLE++;
					}
					else
					{
						memcpy( &pDIB[ nX ], pRLE, nRunByte );
						pRLE += nRunByte;
						nX += nRunByte;

						if( nRunByte & 1 )
							pRLE++;
					}
				}
				else if( !nRunByte )
				{
					pDIB = ( pRow += nWidthAl );
					nX = 0UL;
				}
				else if( nRunByte == 1 )
					bEndDecoding = TRUE;
				else
				{
					nX += *pRLE++;
					pDIB = ( pRow += ( *pRLE++ ) * nWidthAl );
				}
			}
			else
			{
				cTmp = *pRLE++;

				if( bRLE4 )
				{
					nRunByte = nCountByte >> 1;

					for( i = 0; i < nRunByte; i++ )
					{
						ImplSetPixel4( pDIB, nX++, cTmp >> 4 );
						ImplSetPixel4( pDIB, nX++, cTmp & 0x0f );
					}

					if( nCountByte & 1 )
						ImplSetPixel4( pDIB, nX++, cTmp >> 4 );
				}
				else
				{
					for( i = 0; i < nCountByte; i++ )
						pDIB[ nX++ ] = cTmp;
				}
			}
		}
		while( !bEndDecoding && ( pDIB <= pLast ) );
	}
}
#ifdef AVS
bool WinSalBitmap::GetSystemData( BitmapSystemData& rData )
{
    bool bRet = false;
    if( mhDIB || mhDDB )
    {
        bRet = true;
        rData.pDIB = mhDIB;
        rData.pDDB = mhDDB;
        const SvmSize& rSize = GetSize ();
        rData.mnWidth = rSize.Width();
        rData.mnHeight = rSize.Height();
    }
    return bRet;
}
#endif