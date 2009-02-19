﻿/*!
	@file
	@author		Generate utility by Albert Semenov
	@date		01/2009
	@module
*/

#include "../ExportDefine.h"
#include "../ExportMarshaling.h"
#include <MyGUI.h>

namespace Export
{

	//InsertPoint

   	namespace
	{
		MYGUIEXPORT Convert<bool>::Type MYGUICALL ExportTab_GetSmoothShow( MyGUI::Widget* _native )
		{
			return Convert<bool>::To( static_cast< MyGUI::Tab * >(_native)->getSmoothShow( ) );
		}
		MYGUIEXPORT void MYGUICALL ExportTab_SetSmoothShow( MyGUI::Widget* _native , Convert<bool>::Type _value )
		{
			static_cast< MyGUI::Tab * >(_native)->setSmoothShow( Convert<bool>::From( _value ) );
		}
	}
	


   	namespace
	{
		MYGUIEXPORT Convert<bool>::Type MYGUICALL ExportTab_GetButtonAutoWidth( MyGUI::Widget* _native )
		{
			return Convert<bool>::To( static_cast< MyGUI::Tab * >(_native)->getButtonAutoWidth( ) );
		}
		MYGUIEXPORT void MYGUICALL ExportTab_SetButtonAutoWidth( MyGUI::Widget* _native , Convert<bool>::Type _value )
		{
			static_cast< MyGUI::Tab * >(_native)->setButtonAutoWidth( Convert<bool>::From( _value ) );
		}
	}
	


   	namespace
	{
		MYGUIEXPORT Convert<int>::Type MYGUICALL ExportTab_GetButtonDefaultWidth( MyGUI::Widget* _native )
		{
			return Convert<int>::To( static_cast< MyGUI::Tab * >(_native)->getButtonDefaultWidth( ) );
		}
		MYGUIEXPORT void MYGUICALL ExportTab_SetButtonDefaultWidth( MyGUI::Widget* _native , Convert<int>::Type _value )
		{
			static_cast< MyGUI::Tab * >(_native)->setButtonDefaultWidth( Convert<int>::From( _value ) );
		}
	}
	


   	namespace
	{
		MYGUIEXPORT Convert<int>::Type MYGUICALL ExportTab_GetButtonWidth_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			return Convert<int>::To( static_cast< MyGUI::Tab * >(_native)->getButtonWidth(
				Convert< MyGUI::TabItem * >::From(_item) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<int>::Type MYGUICALL ExportTab_GetButtonWidthAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			return Convert<int>::To( static_cast< MyGUI::Tab * >(_native)->getButtonWidthAt(
				Convert<size_t>::From(_index) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetButtonWidth_item_width( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item ,
			Convert<int>::Type _width )
		{
			static_cast< MyGUI::Tab * >(_native)->setButtonWidth(
				Convert< MyGUI::TabItem * >::From(_item) ,
				Convert<int>::From(_width) );
		}
	}


   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetButtonWidth_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			static_cast< MyGUI::Tab * >(_native)->setButtonWidth(
				Convert< MyGUI::TabItem * >::From(_item) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetButtonWidthAt_index_width( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index ,
			Convert<int>::Type _width )
		{
			static_cast< MyGUI::Tab * >(_native)->setButtonWidthAt(
				Convert<size_t>::From(_index) ,
				Convert<int>::From(_width) );
		}
	}


   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetButtonWidthAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			static_cast< MyGUI::Tab * >(_native)->setButtonWidthAt(
				Convert<size_t>::From(_index) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_BeginToItemSelected( MyGUI::Widget* _native )
		{
			static_cast< MyGUI::Tab * >(_native)->beginToItemSelected( );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_BeginToItemLast( MyGUI::Widget* _native )
		{
			static_cast< MyGUI::Tab * >(_native)->beginToItemLast( );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_BeginToItemFirst( MyGUI::Widget* _native )
		{
			static_cast< MyGUI::Tab * >(_native)->beginToItemFirst( );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_BeginToItem_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			static_cast< MyGUI::Tab * >(_native)->beginToItem(
				Convert< MyGUI::TabItem * >::From(_item) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_BeginToItemAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			static_cast< MyGUI::Tab * >(_native)->beginToItemAt(
				Convert<size_t>::From(_index) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<const Ogre::UTFString &>::Type MYGUICALL ExportTab_GetItemName_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			return Convert<const Ogre::UTFString &>::To( static_cast< MyGUI::Tab * >(_native)->getItemName(
				Convert< MyGUI::TabItem * >::From(_item) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<const Ogre::UTFString &>::Type MYGUICALL ExportTab_GetItemNameAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			return Convert<const Ogre::UTFString &>::To( static_cast< MyGUI::Tab * >(_native)->getItemNameAt(
				Convert<size_t>::From(_index) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetItemName_item_name( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			static_cast< MyGUI::Tab * >(_native)->setItemName(
				Convert< MyGUI::TabItem * >::From(_item) ,
				Convert<const Ogre::UTFString &>::From(_name) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetItemNameAt_index_name( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			static_cast< MyGUI::Tab * >(_native)->setItemNameAt(
				Convert<size_t>::From(_index) ,
				Convert<const Ogre::UTFString &>::From(_name) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_ClearItemData_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			static_cast< MyGUI::Tab * >(_native)->clearItemData(
				Convert< MyGUI::TabItem * >::From(_item) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_ClearItemDataAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			static_cast< MyGUI::Tab * >(_native)->clearItemDataAt(
				Convert<size_t>::From(_index) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetItemData_item_data( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item ,
			Convert< MyGUI::Any >::Type _data )
		{
			static_cast< MyGUI::Tab * >(_native)->setItemData(
				Convert< MyGUI::TabItem * >::From(_item) ,
				Convert< MyGUI::Any >::From(_data) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_SetItemDataAt_index_data( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index ,
			Convert< MyGUI::Any >::Type _data )
		{
			static_cast< MyGUI::Tab * >(_native)->setItemDataAt(
				Convert<size_t>::From(_index) ,
				Convert< MyGUI::Any >::From(_data) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_ClearIndexSelected( MyGUI::Widget* _native )
		{
			static_cast< MyGUI::Tab * >(_native)->clearIndexSelected( );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_GetItemSelected( MyGUI::Widget* _native )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->getItemSelected( ) );
		}
		MYGUIEXPORT void MYGUICALL ExportTab_SetItemSelected( MyGUI::Widget* _native , Convert< MyGUI::TabItem * >::Type _value )
		{
			static_cast< MyGUI::Tab * >(_native)->setItemSelected( Convert< MyGUI::TabItem * >::From( _value ) );
		}
	}
	


   	namespace
	{
		MYGUIEXPORT Convert<size_t>::Type MYGUICALL ExportTab_GetIndexSelected( MyGUI::Widget* _native )
		{
			return Convert<size_t>::To( static_cast< MyGUI::Tab * >(_native)->getIndexSelected( ) );
		}
		MYGUIEXPORT void MYGUICALL ExportTab_SetIndexSelected( MyGUI::Widget* _native , Convert<size_t>::Type _value )
		{
			static_cast< MyGUI::Tab * >(_native)->setIndexSelected( Convert<size_t>::From( _value ) );
		}
	}
	


   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_FindItemWith_name( MyGUI::Widget* _native ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->findItemWith(
				Convert<const Ogre::UTFString &>::From(_name) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<size_t>::Type MYGUICALL ExportTab_FindItemIndexWith_name( MyGUI::Widget* _native ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			return Convert<size_t>::To( static_cast< MyGUI::Tab * >(_native)->findItemIndexWith(
				Convert<const Ogre::UTFString &>::From(_name) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<size_t>::Type MYGUICALL ExportTab_FindItemIndex_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			return Convert<size_t>::To( static_cast< MyGUI::Tab * >(_native)->findItemIndex(
				Convert< MyGUI::TabItem * >::From(_item) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<size_t>::Type MYGUICALL ExportTab_GetItemIndex_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			return Convert<size_t>::To( static_cast< MyGUI::Tab * >(_native)->getItemIndex(
				Convert< MyGUI::TabItem * >::From(_item) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_GetItemAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->getItemAt(
				Convert<size_t>::From(_index) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_RemoveAllItems( MyGUI::Widget* _native )
		{
			static_cast< MyGUI::Tab * >(_native)->removeAllItems( );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_RemoveItem_item( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _item )
		{
			static_cast< MyGUI::Tab * >(_native)->removeItem(
				Convert< MyGUI::TabItem * >::From(_item) );
		}
	}



   	namespace
	{
		MYGUIEXPORT void MYGUICALL ExportTab_RemoveItemAt_index( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index )
		{
			static_cast< MyGUI::Tab * >(_native)->removeItemAt(
				Convert<size_t>::From(_index) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_AddItem_name_data( MyGUI::Widget* _native ,
			Convert<const Ogre::UTFString &>::Type _name ,
			Convert< MyGUI::Any >::Type _data )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->addItem(
				Convert<const Ogre::UTFString &>::From(_name) ,
				Convert< MyGUI::Any >::From(_data) ) );
		}
	}


   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_AddItem_name( MyGUI::Widget* _native ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->addItem(
				Convert<const Ogre::UTFString &>::From(_name) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_InsertItem_to_name_data( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _to ,
			Convert<const Ogre::UTFString &>::Type _name ,
			Convert< MyGUI::Any >::Type _data )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->insertItem(
				Convert< MyGUI::TabItem * >::From(_to) ,
				Convert<const Ogre::UTFString &>::From(_name) ,
				Convert< MyGUI::Any >::From(_data) ) );
		}
	}


   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_InsertItem_to_name( MyGUI::Widget* _native ,
			Convert< MyGUI::TabItem * >::Type _to ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->insertItem(
				Convert< MyGUI::TabItem * >::From(_to) ,
				Convert<const Ogre::UTFString &>::From(_name) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_InsertItemAt_index_name_data( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index ,
			Convert<const Ogre::UTFString &>::Type _name ,
			Convert< MyGUI::Any >::Type _data )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->insertItemAt(
				Convert<size_t>::From(_index) ,
				Convert<const Ogre::UTFString &>::From(_name) ,
				Convert< MyGUI::Any >::From(_data) ) );
		}
	}


   	namespace
	{
		MYGUIEXPORT Convert< MyGUI::TabItem * >::Type MYGUICALL ExportTab_InsertItemAt_index_name( MyGUI::Widget* _native ,
			Convert<size_t>::Type _index ,
			Convert<const Ogre::UTFString &>::Type _name )
		{
			return Convert< MyGUI::TabItem * >::To( static_cast< MyGUI::Tab * >(_native)->insertItemAt(
				Convert<size_t>::From(_index) ,
				Convert<const Ogre::UTFString &>::From(_name) ) );
		}
	}



   	namespace
	{
		MYGUIEXPORT Convert<size_t>::Type MYGUICALL ExportTab_GetItemCount( MyGUI::Widget* _native )
		{
			return Convert<size_t>::To( static_cast< MyGUI::Tab * >(_native)->getItemCount( ) );
		}
	}
	


}
