/*!
	@file
	@author		Albert Semenov
	@date		01/2009
	@module
*/
#pragma once

#include <MyGUI.h>
#include "MMyGUI_Macros.h"

namespace MMyGUI
{

	public value struct IntSize
	{

		MMYGUI_MANAGED_NATIVE_CONVERSIONS_FOR_VALUE(IntSize);
		MMYGUI_DECLARE_EQUALS(IntSize)

		int width, height;

		IntSize( int _width, int _height ) : width( _width ), height( _height ) { }

		static bool operator == ( IntSize lvalue, IntSize rvalue )
        {
            return ( lvalue.width == rvalue.width && lvalue.height == rvalue.height );
        }

	};

} // namespace MMyGUI
