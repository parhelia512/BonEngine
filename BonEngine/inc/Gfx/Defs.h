/*****************************************************************//**
 * \file   Defs.h
 * \brief  Misc defs and enum related to GFX.
 * 
 * \author Ronen Ness
 * \date   May 2020
 *********************************************************************/
#pragma once
#include "../dllimport.h"

namespace bon
{
	namespace gfx
	{
		/**
		 * Window modes.
		 */
		enum class BON_DLLEXPORT WindowModes
		{
			Windowed,
			WindowedBorderless,
			Fullscreen,
		};

		/**
		 * Blending modes.
		 */
		enum class BON_DLLEXPORT BlendModes
		{
			// render without any transparency or opacity.
			Opaque = 0,

			// render with alpha channels.
			AlphaBlend = 1,

			// render with additive effect.
			Additive = 2,

			// render with Darken effect.
			Darken = 3,

			// render with multiply effect.
			Multiply = 4,

			// render with screen effect.
			Screen = 5,

			// invert dest pixels.
			Invert = 6,

			// render with difference blending.
			Difference = 7,

			// render with lighten effect.
			Lighten = 8,

			// additive with alpha channels
			AdditiveAlpha = 9,

			// blend modes count
			_Count = 10,
		};
	}
}