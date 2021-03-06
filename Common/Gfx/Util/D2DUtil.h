/* Copyright (C) 2016 Rainmeter Project Developers
 *
 * This Source Code Form is subject to the terms of the GNU General Public
 * License; either version 2 of the License, or (at your option) any later
 * version. If a copy of the GPL was not distributed with this file, You can
 * obtain one at <https://www.gnu.org/licenses/gpl-2.0.html>. */

#ifndef RM_GFX_D2D_UTIL_H_
#define RM_GFX_D2D_UTIL_H_

#include <d2d1.h>
#include <gdiplus.h>

namespace Gfx {
namespace Util {

D2D1_COLOR_F ToColorF(const Gdiplus::Color& color);
D2D1_RECT_F ToRectF(const Gdiplus::Rect& rect);
D2D1_RECT_F ToRectF(const Gdiplus::RectF& rect);

}  // namespace Util
}  // namespace Gfx

#endif
