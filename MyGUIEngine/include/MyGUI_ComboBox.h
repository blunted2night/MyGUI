/*!
	@file
	@author		Albert Semenov
	@date		12/2007
	@module
*/
#ifndef __MYGUI_COMBO_BOX_H__
#define __MYGUI_COMBO_BOX_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Edit.h"

namespace MyGUI
{

	class _MyGUIExport ComboBox : public Edit
	{
		// ��� ������ ��������� ������������
		friend class factory::ComboBoxFactory;

	protected:
		ComboBox(const IntCoord& _coord, char _align, const WidgetSkinInfoPtr _info, CroppedRectanglePtr _parent, WidgetCreator * _creator, const Ogre::String & _name);
		~ComboBox();

		static Ogre::String WidgetTypeName;

	public:
		//! @copydoc Widget::_getType()
		inline static const Ogre::String & _getType() {return WidgetTypeName;}
		//!	@copydoc Widget::getWidgetType()
		virtual const Ogre::String & getWidgetType() { return _getType(); }

		//------------------------------------------------------------------------------------//
		// ������ ��� ����������� ��������
		//! Get number of items
		size_t getItemCount();

		//! Insert an item into a list at a specified position
		void insertItem(size_t _index, const Ogre::DisplayString & _item);
		//! Add an item to the end of a list
		void addItem(const Ogre::DisplayString & _item);
		//! Replace an item at a specified position
		void setItem(size_t _index, const Ogre::DisplayString & _item);
		//! Get item from specified position
		const Ogre::DisplayString & getItem(size_t _index);

		//! Delete item at a specified position
		void deleteItem(size_t _index);
		//! Delete all items
		void deleteAllItems();

		//! Get number of selected item (ITEM_NONE if none selected)
		void setItemSelect(size_t _index);
		//! Reset item selection
		inline void resetItemSelect() {setItemSelect(ITEM_NONE);}
		//! Set item selection at a specified position
		inline size_t getItemSelect() { return mItemIndex; }

		//------------------------------------------------------------------------------------//
		// ������ ��� ���������� ������������
		//! Set drop list mode (text can not be edited)
		void setComboModeDrop(bool _drop);
		//! Get drop list mode
		inline bool getComboModeDrop() { return mModeDrop; }

		//! Set smooth show of list
		inline void setSmoothShow(bool _smooth) { mShowSmooth = _smooth; }
		//! Get smooth show of list
		inline bool getSmoothShow() { return mShowSmooth; }

		//! Set max list height
		inline int getMaxListHeight() { return mMaxHeight; }
		//! Get max list height
		inline void setMaxListHeight(int _height) { mMaxHeight = _height; }

		//------------------------------------------------------------------------------------//

		/** Event : Enter pressed in combo mode or item selected in drop.\n
			signature : void method(MyGUI::WidgetPtr _sender)
		*/
		EventInfo_WidgetVoid eventComboAccept;

		/** Event : Position changed.\n
			signature : void method(MyGUI::WidgetPtr _sender, size_t _index)\n
			_index of new position
		*/
		EventInfo_WidgetSizeT eventComboChangePosition;

	protected:
		virtual void _onKeyButtonPressed(int _key, Char _char);

		void notifyButtonPressed(MyGUI::WidgetPtr _sender, bool _left);
		void notifyListLostFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new);
		void notifyListSelectAccept(MyGUI::WidgetPtr _widget, size_t _position);
		void notifyListMouseItemActivate(MyGUI::WidgetPtr _widget, size_t _position);
		void notifyListChangePosition(MyGUI::WidgetPtr _widget, size_t _position);
		void notifyMouseWheel(MyGUI::WidgetPtr _sender, int _rel);
		void notifyMousePressed(MyGUI::WidgetPtr _sender, bool _left);
		void notifyEditTextChange(MyGUI::WidgetPtr _sender);

		void showList();
		void hideList();

	private:
		ButtonPtr mButton;
		ListPtr mList;

		bool mListShow;
		int mMaxHeight;
		size_t mItemIndex;
		bool mModeDrop;
		bool mDropMouse;
		bool mShowSmooth;

		//float mDoAlpha;

	}; // class _MyGUIExport ComboBox : public Edit

} // namespace MyGUI

#endif // __MYGUI_COMBO_BOX_H__
