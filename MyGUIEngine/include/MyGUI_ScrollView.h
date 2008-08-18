/*!
	@file
	@author		Albert Semenov
	@date		08/2008
	@module
*/
#ifndef __MYGUI_SCROLL_VIEW_H__
#define __MYGUI_SCROLL_VIEW_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Widget.h"

namespace MyGUI
{

	class _MyGUIExport ScrollView : public Widget
	{
		// ��� ������ ��������� ������������
		friend class factory::ScrollViewFactory;

	protected:
		ScrollView(const IntCoord& _coord, Align _align, const WidgetSkinInfoPtr _info, CroppedRectanglePtr _parent, WidgetCreator * _creator, const Ogre::String & _name);
		virtual ~ScrollView();

		static Ogre::String WidgetTypeName;

	public:
		//! @copydoc Widget::_getType()
		inline static const Ogre::String & _getType() {return WidgetTypeName;}
		//! @copydoc Widget::getWidgetType()
		virtual const Ogre::String & getWidgetType() { return _getType(); }

		//! @copydoc Widget::setTextAlign
		virtual void setTextAlign(Align _align);

		//! @copydoc Widget::setPosition(const IntCoord& _coord)
		void setPosition(const IntCoord& _coord);
		//! @copydoc Widget::setSize(const IntSize& _size)
		void setSize(const IntSize& _size);
		//! @copydoc Widget::setPosition(int _left, int _top)
		inline void setPosition(int _left, int _top) { Widget::setPosition(IntPoint(_left, _top)); }
		//! @copydoc Widget::setPosition(int _left, int _top, int _width, int _height)
		inline void setPosition(int _left, int _top, int _width, int _height) { setPosition(IntCoord(_left, _top, _width, _height)); }
		//! @copydoc Widget::setSize(int _width, int _height)
		inline void setSize(int _width, int _height) { setSize(IntSize(_width, _height)); }

		inline void showVScroll(bool _show) { mShowVScroll = _show; updateView(); }
		inline bool isShowVScroll() { return mShowVScroll; }

		inline void showHScroll(bool _show) { mShowHScroll = _show; updateView(); }
		inline bool isShowHScroll() { return mShowHScroll; }

		inline Align getCanvasAlign() { return mAlignCanvas; }
		inline void setCanvasAlign(Align _align) { mAlignCanvas = _align; updateView(); }

		inline IntSize getCanvasSize() { return mWidgetCanvas->getSize(); }
		inline void setCanvasSize(const IntSize & _size) { mWidgetCanvas->setSize(_size); updateView(); }
		inline void setCanvasSize(int _left, int _top) { mWidgetCanvas->setSize(_left, _top); updateView(); }

		// �������������� ��� ���������� ������
		virtual WidgetPtr _createWidget(const std::string & _type, const std::string & _skin, const IntCoord& _coord, Align _align, const std::string & _layer, const std::string & _name);

		// �������������� ��� �������� ����� ������
		virtual EnumeratorWidgetPtr getEnumerator();

	protected:

		void notifyMouseSetFocus(WidgetPtr _sender, WidgetPtr _old);
		void notifyMouseLostFocus(WidgetPtr _sender, WidgetPtr _new);
		void notifyMousePressed(WidgetPtr _sender, int _left, int _top, MouseButton _id);
		void notifyMouseReleased(WidgetPtr _sender, int _left, int _top, MouseButton _id);

		void notifyScrollChangePosition(WidgetPtr _sender, size_t _position);
		void notifyMouseWheel(WidgetPtr _sender, int _rel);

		virtual void _onKeyLostFocus(WidgetPtr _new);
		virtual void _onKeySetFocus(WidgetPtr _old);

		void updateScrollViewState();

		// ���������� �������������
		void updateView();

		void updateScroll();

	protected:
		bool mIsFocus;
		bool mIsPressed;

		VScrollPtr mVScroll;
		HScrollPtr mHScroll;

		bool mShowHScroll;
		bool mShowVScroll;

		size_t mVRange;
		size_t mHRange;

		WidgetPtr mWidgetCanvas;
		Align mAlignCanvas;

	}; // class ScrollView : public Widget

} // namespace MyGUI

#endif // __MYGUI_SCROLL_VIEW_H__
