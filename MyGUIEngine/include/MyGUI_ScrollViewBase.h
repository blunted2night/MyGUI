/*!
	@file
	@author		Albert Semenov
	@date		10/2008
	@module
*//*
	This file is part of MyGUI.
	
	MyGUI is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	MyGUI is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with MyGUI.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __MYGUI_SCROLL_VIEW_BASE_H__
#define __MYGUI_SCROLL_VIEW_BASE_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Common.h"

namespace MyGUI
{

	class ScrollViewBase
	{

	protected:
		ScrollViewBase();

		void updateScrollSize();
		void updateScrollPosition();

		// ������ ������
		virtual IntSize getContentSize() { return IntSize(); }
		// �������� ������
		virtual IntPoint getContentPosition() { return IntPoint(); }
		virtual void setContentPosition(const IntPoint& _point) { }
		// ������ ����, ����� ������� ����� ������
		virtual IntSize getViewSize() { return IntSize(); }
		// ������ �� ������� �������������� ������ ��� ������ �� ������
		virtual size_t getScrollPage() { return 1; }

		virtual Align getContentAlign() { return Align::Center; }

		virtual void eraseContent() { }

	protected:
		VScrollPtr mVScroll;
		HScrollPtr mHScroll;
		WidgetPtr mClient;

		bool mShowHScroll;
		bool mShowVScroll;

		size_t mVRange;
		size_t mHRange;

		// ���������� �� ���������� ��� �������
		bool mChangeContentByResize;

	};

} // namespace MyGUI

#endif // __MYGUI_SCROLL_VIEW_BASE_H__
