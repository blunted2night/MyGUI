/*!
	@file
	@author		Albert Semenov
	@date		01/2008
	@module
*/
#ifndef __MYGUI_TAB_H__
#define __MYGUI_TAB_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Widget.h"
#include "MyGUI_Any.h"

namespace MyGUI
{

	typedef std::vector<TabItemPtr> VectorTabItemPtr;

	struct TabItemInfo
	{
		TabItemInfo(int _width, const Ogre::UTFString& _name, TabItemPtr _item, Any _data) :
			width(_width),
			name(_name),
			item(_item),
			data(_data)
		{
		}

		int width;
		Ogre::UTFString name;
		TabItemPtr item;
		Any data;
	};

	typedef std::vector<TabItemInfo> VectorTabItemInfo;

	class MYGUI_EXPORT Tab : public Widget
	{
		// для вызова закрытого конструктора
		friend class factory::BaseWidgetFactory<Tab>;
		// для уведобления об удалении
		friend class TabItem;

		MYGUI_RTTI_CHILD_HEADER( Tab, Widget );

	public:

		//! @copydoc Widget::setPosition(const IntPoint & _point)
		virtual void setPosition(const IntPoint & _point);
		//! @copydoc Widget::setSize(const IntSize& _size)
		virtual void setSize(const IntSize & _size);
		//! @copydoc Widget::setCoord(const IntCoord & _coord)
		virtual void setCoord(const IntCoord & _coord);

		/** @copydoc Widget::setPosition(int _left, int _top) */
		void setPosition(int _left, int _top) { setPosition(IntPoint(_left, _top)); }
		/** @copydoc Widget::setSize(int _width, int _height) */
		void setSize(int _width, int _height) { setSize(IntSize(_width, _height)); }
		/** @copydoc Widget::setCoord(int _left, int _top, int _width, int _height) */
		void setCoord(int _left, int _top, int _width, int _height) { setCoord(IntCoord(_left, _top, _width, _height)); }

		MYGUI_OBSOLETE("use Widget::setCoord(const IntCoord& _coord)")
		void setPosition(const IntCoord & _coord) { setCoord(_coord); }
		MYGUI_OBSOLETE("use Widget::setCoord(int _left, int _top, int _width, int _height)")
		void setPosition(int _left, int _top, int _width, int _height) { setCoord(_left, _top, _width, _height); }

		//------------------------------------------------------------------------------//
		// манипуляции айтемами

		//! Get number of items
		size_t getItemCount() { return mItemsInfo.size(); }

		//! Insert an item into a array at a specified position
		TabItemPtr insertItemAt(size_t _index, const Ogre::UTFString & _name, Any _data = Any::Null);
		//! Insert an item into a array
		TabItemPtr insertItem(TabItemPtr _to, const Ogre::UTFString & _name, Any _data = Any::Null) {
			return insertItemAt(getItemIndex(_to), _name, _data);
		}

		//! Add an item to the end of a array
		TabItemPtr addItem(const Ogre::UTFString & _name, Any _data = Any::Null) {
			return insertItemAt(ITEM_NONE, _name, _data);
		}

		//! Remove item at a specified position
		void removeItemAt(size_t _index);
		//! Remove item
		void removeItem(TabItemPtr _item) { removeItemAt(getItemIndex(_item)); }

		//! Remove all items
		void removeAllItems();



		//! Get item from specified position
		TabItemPtr getItemAt(size_t _index);

		//! Get item index
		size_t getItemIndex(TabItemPtr _item)
		{
			for (size_t pos=0; pos<mItemsInfo.size(); pos++) {
				if (mItemsInfo[pos].item == _item) return pos;
			}
			MYGUI_EXCEPT("item (" << _item << ") not found, source 'Tab::getItemIndex'");
		}

		//! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
		size_t findItemIndex(TabItemPtr _item)
		{
			for (size_t pos=0; pos<mItemsInfo.size(); pos++) {
				if (mItemsInfo[pos].item == _item) return pos;
			}
			return ITEM_NONE;
		}

		//! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
		size_t findItemIndexWith(const Ogre::UTFString & _name)
		{
			for (size_t pos=0; pos<mItemsInfo.size(); pos++) {
				if (mItemsInfo[pos].name == _name) return pos;
			}
			return ITEM_NONE;
		}

		//! Search item, returns the item of the first occurrence in array or null if item not found
		TabItemPtr findItemWith(const Ogre::UTFString & _name)
		{
			for (size_t pos=0; pos<mItemsInfo.size(); pos++) {
				if (mItemsInfo[pos].name == _name) return mItemsInfo[pos].item;
			}
			return null;
		}


		//------------------------------------------------------------------------------//
		// манипуляции выделениями

		//! Get index of selected item (ITEM_NONE if none selected)
		size_t getItemIndexSelected() { return mIndexSelect; }

		//! Get selected item (null if none selected)
		TabItemPtr getItemSelected() { return getItemIndexSelected() != ITEM_NONE ? getItemAt(getItemIndexSelected()) : null; }

		//! Select specified _index
		void setItemSelectedAt(size_t _index);

		//! Select item
		void setItemSelected(TabItemPtr _item) { setItemSelectedAt(getItemIndex(_item)); }

		//! Clear item selection
		void clearItemSelected() { setItemSelectedAt(ITEM_NONE); }


		//------------------------------------------------------------------------------//
		// манипуляции данными

		//! Replace an item data at a specified position
		void setItemDataAt(size_t _index, Any _data);
		//! Replace an item data
		void setItemData(TabItemPtr _item, Any _data) { setItemDataAt(getItemIndex(_item), _data); }

		//! Clear an item data at a specified position
		void clearItemDataAt(size_t _index) { setItemDataAt(_index, Any::Null); }
		//! Clear an item data
		void clearItemData(TabItemPtr _item) { clearItemDataAt(getItemIndex(_item)); }

		//! Get item data from specified position
		template <typename ValueType>
		ValueType * getItemDataAt(size_t _index, bool _throw = true)
		{
			MYGUI_ASSERT_RANGE(_index, mItemsInfo.size(), "Tab::getItemDataAt");
			return mItemsInfo[_index].data.castType<ValueType>(_throw);
		}
		//! Get item data
		template <typename ValueType>
		ValueType * getItemData(TabItemPtr _item, bool _throw = true)
		{
			return getItemData<ValueType>(getItemIndex(_item), _throw);
		}


		//------------------------------------------------------------------------------//
		// манипуляции отображением

		//! Replace an item name at a specified position
		void setItemNameAt(size_t _index, const Ogre::UTFString & _name);

		//! Replace an item name
		void setItemName(TabItemPtr _item, const Ogre::UTFString & _name) { setItemNameAt(getItemIndex(_item), _name); }

		//! Get item name from specified position
		const Ogre::UTFString & getItemNameAt(size_t _index);

		//! Get item name
		const Ogre::UTFString & getItemName(TabItemPtr _item) { return getItemNameAt(getItemIndex(_item)); }


		//------------------------------------------------------------------------------//
		// манипуляции выдимостью

		//! Move all elements so specified becomes visible
		void beginToItemAt(size_t _index);

		//! Move all elements so specified becomes visible
		void beginToItem(TabItemPtr _item) { beginToItemAt(getItemIndex(_item)); }

		//! Move all elements so first becomes visible
		void beginToItemFirst() { if (getItemCount()) beginToItemAt(0); }

		//! Move all elements so last becomes visible
		void beginToItemLast() { if (getItemCount()) beginToItemAt(getItemCount() - 1); }

		//! Move all elements so selected becomes visible
		void beginToItemSelected() { if (getItemIndexSelected() != ITEM_NONE) beginToItemAt(getItemIndexSelected()); }


		//------------------------------------------------------------------------------//
		// остальные манипуляции

		//! Set button width at a specified position
		void setButtonWidthAt(size_t _index, int _width = DEFAULT);
		//! Set button width
		void setButtonWidth(TabItemPtr _item, int _width = DEFAULT) { setButtonWidthAt(getItemIndex(_item), _width); }

		//! Get button width at a specified position
		int getButtonWidthAt(size_t _index);
		//! Get button width
		int getButtonWidth(TabItemPtr _item) { return getButtonWidthAt(getItemIndex(_item)); }

		//------------------------------------------------------------------------------//

		/** Set default button width and disable autowidth mode */
		void setButtonDefaultWidth(int _width);
		/** Get default button width */
		int getButtonDefaultWidth() { return mButtonDefaultWidth; }

		/** Enable or disable button auto width */
		void setButtonAutoWidth(bool _auto);
		/** Get button auto width flag */
		bool getButtonAutoWidth() { return mButtonAutoWidth; }

		/** Enable or disable smooth sheets showing*/
		void setSmoothShow(bool _smooth) { mSmoothShow = _smooth; }
		/** Get smooth sheets showing flag */
		bool getSmoothShow() { return mSmoothShow; }



		// #ifdef MYGUI_USING_OBSOLETE

		MYGUI_OBSOLETE("use Tab::getButtonWidthAt(size_t _index)")
		int getSheetButtonWidthIndex(size_t _index) { return getButtonWidthAt(_index); }

		MYGUI_OBSOLETE("use Tab::getButtonWidth(TabItemPtr _item)")
		int getSheetButtonWidth(TabItemPtr _sheet) { return getButtonWidth(_sheet); }

		MYGUI_OBSOLETE("use Tab::setButtonWidthAt(size_t _index, int _width)")
		void setSheetButtonWidthIndex(size_t _index, int _width = DEFAULT) { setButtonWidthAt(_index, _width); }

		MYGUI_OBSOLETE("use Tab::setButtonWidth(TabItemPtr _item, int _width)")
		void setSheetButtonWidth(TabItemPtr _sheet, int _width = DEFAULT) { setButtonWidth(_sheet, _width); }

		MYGUI_OBSOLETE("use Tab::beginToItemAt(size_t _index)")
		void showBarButton(size_t _index) { beginToItemAt(_index); }

		MYGUI_OBSOLETE("use Tab::beginToItemSelected()")
		void showBarSelectButton() { beginToItemSelected(); }

		MYGUI_OBSOLETE("use Tab::getItemCount()")
		size_t getSheetCount() { return getItemCount(); }

		MYGUI_OBSOLETE("use Tab::getItemName(TabItemPtr _item)")
		const Ogre::UTFString& getSheetName(TabItemPtr _sheet) { return getItemName(_sheet); }

		MYGUI_OBSOLETE("use Tab::getItemNameAt(size_t _index)")
		const Ogre::UTFString& getSheetNameIndex(size_t _index) { return getItemNameAt(_index); }

		MYGUI_OBSOLETE("use Tab::getItemAt(size_t _index)")
		TabItemPtr getSheet(size_t _index) { return getItemAt(_index); }

		MYGUI_OBSOLETE("use Tab::setItemNameAt(size_t _index, const Ogre::UTFString & _name)")
		void setSheetNameIndex(size_t _index, const Ogre::UTFString& _name, int _width = DEFAULT) { setItemNameAt(_index, _name); }

		MYGUI_OBSOLETE("use Tab::setItemName(TabItemPtr _item, const Ogre::UTFString & _name)")
		void setSheetName(TabItemPtr _sheet, const Ogre::UTFString& _name, int _width = DEFAULT) { setItemName(_sheet, _name); }

		MYGUI_OBSOLETE("use Tab::addItem(const Ogre::UTFString & _name, Any _data)")
		TabItemPtr addSheet(const Ogre::UTFString& _name, int _width = DEFAULT) { return addItem(_name, _width); }

		MYGUI_OBSOLETE("use Tab::insertItemAt(size_t _index, const Ogre::UTFString & _name, Any _data)")
		TabItemPtr insertSheet(size_t _index, const Ogre::UTFString& _name, int _width = DEFAULT) { return insertItemAt(_index, _name); }

		MYGUI_OBSOLETE("use Tab::removeItemAt(size_t _index)")
		void removeSheetIndex(size_t _index) { removeItemAt(_index); }

		MYGUI_OBSOLETE("use Tab::removeItem(TabItemPtr _item)")
		void removeSheet(TabItemPtr _sheet) { removeItem(_sheet); }

		MYGUI_OBSOLETE("use Tab::setItemSelectedAt(size_t _index)")
		void selectSheetIndex(size_t _index, bool _smooth = true) { setItemSelectedAt(_index); }

		MYGUI_OBSOLETE("use Tab::setItemSelected(TabItemPtr _item)")
		void selectSheet(TabItemPtr _sheet, bool _smooth = true) { setItemSelected(_sheet); }

		MYGUI_OBSOLETE("use Tab::getItemIndexSelected()")
		size_t getSelectSheetIndex() { return getItemIndexSelected(); }

		// #endif // MYGUI_USING_OBSOLETE



		/** Event : Active Tab sheet changed \n
			signature : void method(MyGUI::WidgetPtr _sender, size_t _index)\n
			@param _index Index of selected sheet
		*/
		EventInfo_WidgetSizeT eventTabChangeSelect;

	protected:
		Tab(WidgetStyle _style, const IntCoord& _coord, Align _align, const WidgetSkinInfoPtr _info, WidgetPtr _parent, ICroppedRectangle * _croppedParent, IWidgetCreator * _creator, const std::string & _name);
		virtual ~Tab();

		void baseChangeWidgetSkin(WidgetSkinInfoPtr _info);

		// переопределяем для особого обслуживания страниц
		virtual WidgetPtr baseCreateWidget(WidgetStyle _style, const std::string & _type, const std::string & _skin, const IntCoord& _coord, Align _align, const std::string & _layer, const std::string & _name);

		void updateBar();

		void notifyPressedButtonEvent(MyGUI::WidgetPtr _sender);
		void notifyPressedBarButtonEvent(MyGUI::WidgetPtr _sender);

		int _getTextWidth(const Ogre::UTFString& _text);

		void _showItem(TabItemPtr _sheet, bool _show, bool _smooth);

		void _createItemButton();

		void _insertItem(size_t _index, const Ogre::UTFString & _name, TabItemPtr _sheet, Any _data);

		// вкладка при удалении уведомляет таб
		void _notifyDeleteItem(TabItemPtr _item);

	private:
		void initialiseWidgetSkin(WidgetSkinInfoPtr _info);
		void shutdownWidgetSkin();
		void actionWidgetHide(WidgetPtr _widget);

	private:
		int mOffsetTab; // смещение бара при показе кнопок
		bool mButtonShow;
		int mWidthBar; // ширина в которую помещаються все кнопки
		VectorWidgetPtr mItemButton; // список кнопок, не должно равно списку страниц
		std::string mButtonSkinName, mEmptySkinName;

		WidgetPtr mWidgetBar;
		ButtonPtr mButtonLeft, mButtonRight, mButtonList;
		WidgetPtr mButtonDecor;
		VectorWidgetPtr mWidgetsPatch; // список виджетов которые нужно показать при показе кнопки
		WidgetPtr mEmptyBarWidget;
		WidgetPtr mItemTemplate;

		// информация о вкладках
		VectorTabItemInfo mItemsInfo;
		size_t mStartIndex;
		size_t mIndexSelect;

		int mButtonDefaultWidth;
		bool mSmoothShow;
		bool mButtonAutoWidth;

		// флаг, чтобы отсеч уведомления от вкладок, при общем шутдауне виджета
		bool mShutdown;

	};

} // namespace MyGUI

#endif // __MYGUI_TAB_H__

