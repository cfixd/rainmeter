/*
  Copyright (C) 2013 Birunthan Mohanathas

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef RM_GFX_TEXTFORMATD2D_H_
#define RM_GFX_TEXTFORMATD2D_H_

#include "TextFormat.h"
#include <string>
#include <dwrite.h>

namespace Gfx {

// Provides a Direct2D/DirectWrite implementation of TextFormat for use with CanvasD2D.
class TextFormatD2D : public TextFormat
{
public:
	TextFormatD2D();
	virtual ~TextFormatD2D();

	virtual bool IsInitialized() const override { return m_TextFormat != nullptr; }

	virtual void SetProperties(
		const WCHAR* fontFamily, int size, bool bold, bool italic,
		const FontCollection* fontCollection) override;

	virtual void SetTrimming(bool trim) override;

	virtual void SetHorizontalAlignment(HorizontalAlignment alignment) override;
	virtual void SetVerticalAlignment(VerticalAlignment alignment) override;

private:
	friend class CanvasD2D;

	TextFormatD2D(const TextFormatD2D& other) {}

	void Dispose();

	// Creates a new DirectWrite text layout if |str| has changed since last call. Since creating
	// the layout is costly, it is more efficient to keep reusing the text layout until the text
	// changes.
	void CreateLayout(const WCHAR* str, UINT strLen, float maxW, float maxH);

	// Maps the GDI family name and italic/bold flags to the DirectWrite family name, weight, style,
	// and stretch.
	static bool GetDWPropertiesFromGDIProperties(
		const WCHAR* gdiFamilyName, const bool gdiBold, const bool gdiItalic,
		DWRITE_FONT_WEIGHT& dwFontWeight, DWRITE_FONT_STYLE& dwFontStyle,
		DWRITE_FONT_STRETCH& dwFontStretch, WCHAR* dwFamilyName, UINT dwFamilyNameSize);

	// Creates a IDWriteFont using the GDI family name instead of the DirectWrite family name. For
	// example, 'Segoe UI' and 'Segoe UI Semibold' are separate family names with GDI whereas
	// DirectWrite uses the family name 'Segoe UI' for both and differentiates them by the font
	// style.
	static IDWriteFont* CreateDWFontFromGDIFamilyName(const WCHAR* fontFamily);

	static bool GetFamilyNameFromDWFont(IDWriteFont* font, WCHAR* buffer, UINT bufferSize);
	static bool GetFamilyNameFromDWFontFamily(IDWriteFontFamily* fontFamily, WCHAR* buffer, UINT bufferSize);

	IDWriteTextFormat* m_TextFormat;
	IDWriteTextLayout* m_TextLayout;
	IDWriteInlineObject* m_InlineEllipsis;

	std::wstring m_LastString;
};

}  // namespace Gfx

#endif