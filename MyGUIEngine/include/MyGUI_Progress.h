/*!
	@file
	@author		Albert Semenov
	@date		01/2008
	@module
*/
#ifndef __MYGUI_PROGRESS_H__
#define __MYGUI_PROGRESS_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Align.h"
#include "MyGUI_Widget.h"

namespace MyGUI
{

	class _MyGUIExport Progress : public Widget
	{
		// ��� ������ ��������� ������������
		friend class factory::ProgressFactory;

		MYGUI_RTTI_CHILD_HEADER;

	protected:
		Progress(const IntCoord& _coord, Align _align, const WidgetSkinInfoPtr _info, ICroppedRectangle * _parent, IWidgetCreator * _creator, const Ogre::String & _name);
		~Progress();

		void frameEntered(float _time);

	public:
		/** Set progress range */
		void setProgressRange(size_t _range);
		/** Get progress range */
		inline size_t getProgressRange() {return mRange;}

		/** Set progress position */
		void setProgressPosition(size_t _pos);
		/** Get progress position */
		inline size_t getProgressPosition() {return mEndPosition;}

		/** FIXME ��� ��� ������? ������ ��� � ������� ������? */
		void setProgressFillTrack(bool _fill);
		/** Get progress fill track flag */
		inline bool getProgressFillTrack() {return mFillTrack;}

		/** Enable or disable progress auto tracking */
		void setProgressAutoTrack(bool _auto);
		/** Get progress auto tracking flag */
		inline bool getProgressAutoTrack() {return mAutoTrack;}

		/** Set progress start point
			For example with Align::Top if will be filled from top to bottom.
		*/
		void setProgressStartPoint(Align _align = Align::Left);
		/** Get progress start point */
		inline Align getProgressStartPoint() {return mStartPoint;}

		//! @copydoc Widget::setPosition(const IntCoord& _coord)
		void setPosition(const IntCoord& _coord);
		//! @copydoc Widget::setSize(const IntSize& _size)
		void setSize(const IntSize& _size);
		//! @copydoc Widget::setPosition(int _left, int _top)
		inline void setPosition(int _left, int _top) {Widget::setPosition(IntPoint(_left, _top));}
		//! @copydoc Widget::setPosition(int _left, int _top, int _width, int _height)
		inline void setPosition(int _left, int _top, int _width, int _height) {setPosition(IntCoord(_left, _top, _width, _height));}
		//! @copydoc Widget::setSize(int _width, int _height)
		inline void setSize(int _width, int _height) {setSize(IntSize(_width, _height));}

	private:
		void updateTrack();

		inline int getClientWidth() {return ((mStartPoint.isLeft()) || (mStartPoint.isRight())) ? mWidgetClient->getWidth() : mWidgetClient->getHeight();}
		inline int getClientHeight() {return ((mStartPoint.isLeft()) || (mStartPoint.isRight())) ? mWidgetClient->getHeight() : mWidgetClient->getWidth();}

		void setTrackPosition(WidgetPtr _widget, int _left, int _top, int _width, int _height);

	private:
		std::string mTrackSkin;
		int mTrackWidth;
		int mTrackStep;
		int mTrackMin;

		VectorWidgetPtr mVectorTrack;
		size_t mRange;
		size_t mStartPosition, mEndPosition;
		float mAutoPosition;
		bool mAutoTrack;
		bool mFillTrack;

		Align mStartPoint;

	}; // class _MyGUIExport Progress : public Widget

} // namespace MyGUI

#endif // __MYGUI_PROGRESS_H__
