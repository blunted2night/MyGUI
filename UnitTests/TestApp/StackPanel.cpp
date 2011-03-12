/*!
	@file
	@author		Albert Semenov
	@date		02/2011
*/

#include "StackPanel.h"

namespace MyGUI
{

	StackPanel::StackPanel()
	{
	}

	IntSize StackPanel::overrideMeasure(const IntSize& _sizeAvailable)
	{
		IntSize result;

		size_t count = getChildCount();
		for (size_t index = 0; index < count; ++ index)
		{
			Widget* child = getChildAt(index);
			Panel::updateMeasure(child, _sizeAvailable);
			IntSize size = Panel::getDesiredSize(child);

			result.width = std::max(result.width, size.width);
			result.height += size.height;
		}

		return result;
	}

	void StackPanel::overrideArrange()
	{
		int offset = 0;

		EnumeratorWidgetPtr child = getEnumerator();
		while (child.next())
		{
			const IntSize& childSize = Panel::getDesiredSize(child.current());
			IntCoord coord;

			int height = childSize.height;
			coord.set(0, offset, getWidth(), height);

			if (offset < getHeight())
			{
				Panel::updateArrange(child.current(), coord);
			}
			else if (child.current()->getTop() < getHeight())
			{
				child.current()->setPosition(0, getHeight() + 2000);
			}

			offset += height;
		}
	}

} // namespace MyGUI
