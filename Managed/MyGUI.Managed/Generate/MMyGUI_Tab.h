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

	public ref class Tab : public Widget
	{

		//--------------------------------------------------------------------
		// объявление типов и конструкторов
		MMYGUI_DECLARE_DERIVED( Tab, Widget );

		//InsertPoint

   	public:
		delegate void HandleTabChangeSelect( Convert<MyGUI::Widget *>::Type _value1, Convert<size_t>::Type _value2 );
		event HandleTabChangeSelect^ TabChangeSelect
		{
			void add(HandleTabChangeSelect^ _value)
			{
				mDelegateTabChangeSelect += _value;
				static_cast<ThisType*>(mNative)->eventTabChangeSelect = new Delegate2< HandleTabChangeSelect^, MyGUI::Widget *, size_t >(mDelegateTabChangeSelect);
			}
			void remove(HandleTabChangeSelect^ _value)
			{
				mDelegateTabChangeSelect -= _value;
				if (mDelegateTabChangeSelect == nullptr)
					static_cast<ThisType*>(mNative)->eventTabChangeSelect = nullptr;
				else
					static_cast<ThisType*>(mNative)->eventTabChangeSelect = new Delegate2< HandleTabChangeSelect^, MyGUI::Widget *, size_t >(mDelegateTabChangeSelect);
			}
		}
	private:
		HandleTabChangeSelect^ mDelegateTabChangeSelect;




   	public:
		property Convert<bool>::Type SmoothShow
		{
			Convert<bool>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<bool>::To( static_cast<ThisType*>(mNative)->getSmoothShow() );
			}
			void set(Convert<bool>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setSmoothShow( Convert<bool>::From(_value) );
			}
		}



   	public:
		property Convert<bool>::Type ButtonAutoWidth
		{
			Convert<bool>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<bool>::To( static_cast<ThisType*>(mNative)->getButtonAutoWidth() );
			}
			void set(Convert<bool>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setButtonAutoWidth( Convert<bool>::From(_value) );
			}
		}



   	public:
		property Convert<int>::Type ButtonDefaultWidth
		{
			Convert<int>::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert<int>::To( static_cast<ThisType*>(mNative)->getButtonDefaultWidth() );
			}
			void set(Convert<int>::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setButtonDefaultWidth( Convert<int>::From(_value) );
			}
		}



   	public:
		Convert<int>::Type GetButtonWidth( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<int>::To( static_cast<ThisType*>(mNative)->getButtonWidth( Convert< MyGUI::TabItem * >::From(_item) ) );
		}



   	public:
		Convert<int>::Type GetButtonWidthAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<int>::To( static_cast<ThisType*>(mNative)->getButtonWidthAt( Convert<size_t>::From(_index) ) );
		}



   	public:
		void SetButtonWidth( Convert< MyGUI::TabItem * >::Type _item, Convert<int>::Type _width )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setButtonWidth( Convert< MyGUI::TabItem * >::From(_item), Convert<int>::From(_width) );
		}



   	public:
		void SetButtonWidthAt( Convert<size_t>::Type _index, Convert<int>::Type _width )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setButtonWidthAt( Convert<size_t>::From(_index), Convert<int>::From(_width) );
		}



   	public:
		void BeginToItemSelected( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->beginToItemSelected( );
		}



   	public:
		void BeginToItemLast( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->beginToItemLast( );
		}



   	public:
		void BeginToItemFirst( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->beginToItemFirst( );
		}



   	public:
		void BeginToItem( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->beginToItem( Convert< MyGUI::TabItem * >::From(_item) );
		}



   	public:
		void BeginToItemAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->beginToItemAt( Convert<size_t>::From(_index) );
		}



   	public:
		Convert<const Ogre::UTFString &>::Type GetItemName( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<const Ogre::UTFString &>::To( static_cast<ThisType*>(mNative)->getItemName( Convert< MyGUI::TabItem * >::From(_item) ) );
		}



   	public:
		Convert<const Ogre::UTFString &>::Type GetItemNameAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<const Ogre::UTFString &>::To( static_cast<ThisType*>(mNative)->getItemNameAt( Convert<size_t>::From(_index) ) );
		}



   	public:
		void SetItemName( Convert< MyGUI::TabItem * >::Type _item, Convert<const Ogre::UTFString &>::Type _name )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setItemName( Convert< MyGUI::TabItem * >::From(_item), Convert<const Ogre::UTFString &>::From(_name) );
		}



   	public:
		void SetItemNameAt( Convert<size_t>::Type _index, Convert<const Ogre::UTFString &>::Type _name )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setItemNameAt( Convert<size_t>::From(_index), Convert<const Ogre::UTFString &>::From(_name) );
		}



   	public:
		void ClearItemData( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->clearItemData( Convert< MyGUI::TabItem * >::From(_item) );
		}



   	public:
		void ClearItemDataAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->clearItemDataAt( Convert<size_t>::From(_index) );
		}



   	public:
		void SetItemData( Convert< MyGUI::TabItem * >::Type _item, Convert< MyGUI::Any >::Type _data )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setItemData( Convert< MyGUI::TabItem * >::From(_item), Convert< MyGUI::Any >::From(_data) );
		}



   	public:
		void SetItemDataAt( Convert<size_t>::Type _index, Convert< MyGUI::Any >::Type _data )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setItemDataAt( Convert<size_t>::From(_index), Convert< MyGUI::Any >::From(_data) );
		}



   	public:
		void ClearItemSelected( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->clearItemSelected( );
		}



   	public:
		property Convert< MyGUI::TabItem * >::Type ItemSelected
		{
			Convert< MyGUI::TabItem * >::Type get( )
			{
				MMYGUI_CHECK_NATIVE(mNative);
				return Convert< MyGUI::TabItem * >::To( static_cast<ThisType*>(mNative)->getItemSelected() );
			}
			void set(Convert< MyGUI::TabItem * >::Type _value)
			{
				MMYGUI_CHECK_NATIVE(mNative);
				static_cast<ThisType*>(mNative)->setItemSelected( Convert< MyGUI::TabItem * >::From(_value) );
			}
		}



   	public:
		void SetItemSelectedAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->setItemSelectedAt( Convert<size_t>::From(_index) );
		}



   	public:
		Convert<size_t>::Type GetItemIndexSelected( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getItemIndexSelected( ) );
		}



   	public:
		Convert< MyGUI::TabItem * >::Type FindItemWith( Convert<const Ogre::UTFString &>::Type _name )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert< MyGUI::TabItem * >::To( static_cast<ThisType*>(mNative)->findItemWith( Convert<const Ogre::UTFString &>::From(_name) ) );
		}



   	public:
		Convert<size_t>::Type FindItemIndexWith( Convert<const Ogre::UTFString &>::Type _name )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<size_t>::To( static_cast<ThisType*>(mNative)->findItemIndexWith( Convert<const Ogre::UTFString &>::From(_name) ) );
		}



   	public:
		Convert<size_t>::Type FindItemIndex( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<size_t>::To( static_cast<ThisType*>(mNative)->findItemIndex( Convert< MyGUI::TabItem * >::From(_item) ) );
		}



   	public:
		Convert<size_t>::Type GetItemIndex( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getItemIndex( Convert< MyGUI::TabItem * >::From(_item) ) );
		}



   	public:
		Convert< MyGUI::TabItem * >::Type GetItemAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert< MyGUI::TabItem * >::To( static_cast<ThisType*>(mNative)->getItemAt( Convert<size_t>::From(_index) ) );
		}



   	public:
		void RemoveAllItems( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->removeAllItems( );
		}



   	public:
		void RemoveItem( Convert< MyGUI::TabItem * >::Type _item )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->removeItem( Convert< MyGUI::TabItem * >::From(_item) );
		}



   	public:
		void RemoveItemAt( Convert<size_t>::Type _index )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			static_cast<ThisType*>(mNative)->removeItemAt( Convert<size_t>::From(_index) );
		}



   	public:
		Convert< MyGUI::TabItem * >::Type AddItem( Convert<const Ogre::UTFString &>::Type _name, Convert< MyGUI::Any >::Type _data )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert< MyGUI::TabItem * >::To( static_cast<ThisType*>(mNative)->addItem( Convert<const Ogre::UTFString &>::From(_name), Convert< MyGUI::Any >::From(_data) ) );
		}



   	public:
		Convert< MyGUI::TabItem * >::Type InsertItem( Convert< MyGUI::TabItem * >::Type _to, Convert<const Ogre::UTFString &>::Type _name, Convert< MyGUI::Any >::Type _data )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert< MyGUI::TabItem * >::To( static_cast<ThisType*>(mNative)->insertItem( Convert< MyGUI::TabItem * >::From(_to), Convert<const Ogre::UTFString &>::From(_name), Convert< MyGUI::Any >::From(_data) ) );
		}



   	public:
		Convert< MyGUI::TabItem * >::Type InsertItemAt( Convert<size_t>::Type _index, Convert<const Ogre::UTFString &>::Type _name, Convert< MyGUI::Any >::Type _data )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert< MyGUI::TabItem * >::To( static_cast<ThisType*>(mNative)->insertItemAt( Convert<size_t>::From(_index), Convert<const Ogre::UTFString &>::From(_name), Convert< MyGUI::Any >::From(_data) ) );
		}



   	public:
		Convert<size_t>::Type GetItemCount( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<size_t>::To( static_cast<ThisType*>(mNative)->getItemCount( ) );
		}



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
		Convert<const std::string &>::Type GetTypeName( )
		{
			MMYGUI_CHECK_NATIVE(mNative);
			return Convert<const std::string &>::To( static_cast<ThisType*>(mNative)->getTypeName( ) );
		}



	};

} // namespace MMyGUI
