﻿/*!
	@file
	@author		Generate utility by Albert Semenov
	@date		01/2009
	@module
*/
#pragma once

#include "MMyGUI_Widget.h"


namespace MMyGUI
{

	public ref class VScroll : public Widget
	{

		//--------------------------------------------------------------------
		// объявление типов и конструкторов
		MMYGUI_DECLARE_DERIVED( VScroll, Widget );

		//InsertPoint

   	public:
		delegate void HandleScrollChangePosition( Convert<MyGUI::Widget *>::Type _value1, Convert<size_t>::Type _value2 );
		event HandleScrollChangePosition^ ScrollChangePosition
		{
			void add(HandleScrollChangePosition^ _value)
			{
				mDelegateScrollChangePosition += _value;
				static_cast<ThisType*>(mNative)->eventScrollChangePosition = new Delegate2< HandleScrollChangePosition^, MyGUI::Widget *, size_t >(mDelegateScrollChangePosition);
			}
			void remove(HandleScrollChangePosition^ _value)
			{
				mDelegateScrollChangePosition -= _value;
				if (mDelegateScrollChangePosition == nullptr)
					static_cast<ThisType*>(mNative)->eventScrollChangePosition = nullptr;
				else
					static_cast<ThisType*>(mNative)->eventScrollChangePosition = new Delegate2< HandleScrollChangePosition^, MyGUI::Widget *, size_t >(mDelegateScrollChangePosition);
			}
		}
	private:
		HandleScrollChangePosition^ mDelegateScrollChangePosition;




   	public:
		void SetCoord( Convert<int>::Type _left, Convert<int>::Type _top, Convert<int>::Type _width, Convert<int>::Type _height )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setCoord( Convert<int>::From(_left), Convert<int>::From(_top), Convert<int>::From(_width), Convert<int>::From(_height) );
		}



   	public:
		void SetSize( Convert<int>::Type _width, Convert<int>::Type _height )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setSize( Convert<int>::From(_width), Convert<int>::From(_height) );
		}



   	public:
		void SetPosition( Convert<int>::Type _left, Convert<int>::Type _top )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setPosition( Convert<int>::From(_left), Convert<int>::From(_top) );
		}



   	public:
		void SetCoord( Convert<const MyGUI::types::TCoord< int > &>::Type _coord )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setCoord( Convert<const MyGUI::types::TCoord< int > &>::From(_coord) );
		}



   	public:
		void SetSize( Convert<const MyGUI::types::TSize< int > &>::Type _size )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setSize( Convert<const MyGUI::types::TSize< int > &>::From(_size) );
		}



   	public:
		void SetPosition( Convert<const MyGUI::types::TPoint< int > &>::Type _point )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setPosition( Convert<const MyGUI::types::TPoint< int > &>::From(_point) );
		}



   	public:
		property Convert<int>::Type MinTrackSize
		{
			Convert<int>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<int>::To( static_cast<ThisType*>(mNative)->getMinTrackSize() );
			}
			void set(Convert<int>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setMinTrackSize( Convert<int>::From(_value) );
			}
		}



   	public:
		Convert<int>::Type GetTrackSize( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<int>::To( static_cast<ThisType*>(mNative)->getTrackSize( ) );
		}



   	public:
		void SetTrackSize( Convert<size_t>::Type _size )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setTrackSize( Convert<size_t>::From(_size) );
		}



   	public:
		Convert<int>::Type GetLineSize( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<int>::To( static_cast<ThisType*>(mNative)->getLineSize( ) );
		}



   	public:
		property Convert<size_t>::Type ScrollViewPage
		{
			Convert<size_t>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getScrollViewPage() );
			}
			void set(Convert<size_t>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setScrollViewPage( Convert<size_t>::From(_value) );
			}
		}



   	public:
		property Convert<size_t>::Type ScrollPage
		{
			Convert<size_t>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getScrollPage() );
			}
			void set(Convert<size_t>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setScrollPage( Convert<size_t>::From(_value) );
			}
		}



   	public:
		property Convert<size_t>::Type ScrollPosition
		{
			Convert<size_t>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getScrollPosition() );
			}
			void set(Convert<size_t>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setScrollPosition( Convert<size_t>::From(_value) );
			}
		}



   	public:
		property Convert<size_t>::Type ScrollRange
		{
			Convert<size_t>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getScrollRange() );
			}
			void set(Convert<size_t>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setScrollRange( Convert<size_t>::From(_value) );
			}
		}



   	public:
		Convert<const std::string &>::Type GetTypeName( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<const std::string &>::To( static_cast<ThisType*>(mNative)->getTypeName( ) );
		}



	};

} // namespace MMyGUI
