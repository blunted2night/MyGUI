/*!
	@file
	@author		Albert Semenov
	@date		08/2010
*/
#include "precompiled.h"
#include "StateTextureControl.h"
#include "SkinManager.h"

namespace tools
{

	StateTextureControl::StateTextureControl(MyGUI::Widget* _parent) :
		wraps::BaseLayout("StateTextureControl.layout", _parent),
		mTypeName("StateTextureControl"),
		mView(nullptr),
		mTexture(nullptr),
		mBackgroundColour(nullptr),
		mBackground(nullptr),
		mRegionSelectorControl(nullptr),
		mCurrentSkin(nullptr),
		mCurrentState(nullptr),
		mScale(nullptr),
		mScaleValue(1)
	{
		assignWidget(mView, "View");
		assignWidget(mTexture, "Texture");
		assignWidget(mBackgroundColour, "BackgroundColour");
		assignWidget(mBackground, "Background");
		assignWidget(mScale, "Scale");
		assignBase(mRegionSelectorControl, "Texture");

		fillColours(mBackgroundColour);
		mBackgroundColour->eventComboChangePosition += MyGUI::newDelegate(this, &StateTextureControl::notifyComboChangePosition);

		fillScale();
		mScale->eventComboChangePosition += MyGUI::newDelegate(this, &StateTextureControl::notifyComboChangePosition);

		SkinManager::getInstance().eventChangeSelection += MyGUI::newDelegate(this, &StateTextureControl::notifyChangeSelection);
		advice();

		mRegionSelectorControl->eventChangePosition += MyGUI::newDelegate(this, &StateTextureControl::notifyChangePosition);

		updateAllProperties();
	}

	StateTextureControl::~StateTextureControl()
	{
		mRegionSelectorControl->eventChangePosition -= MyGUI::newDelegate(this, &StateTextureControl::notifyChangePosition);

		mBackgroundColour->eventComboChangePosition -= MyGUI::newDelegate(this, &StateTextureControl::notifyComboChangePosition);
		mScale->eventComboChangePosition -= MyGUI::newDelegate(this, &StateTextureControl::notifyComboChangePosition);

		SkinManager::getInstance().eventChangeSelection -= MyGUI::newDelegate(this, &StateTextureControl::notifyChangeSelection);
		unadvice();
	}

	void StateTextureControl::notifyChangeSelection()
	{
		unadvice();
		advice();

		updateAllProperties();
		updateAllStateProperties();
	}

	void StateTextureControl::unadvice()
	{
		if (mCurrentSkin != nullptr)
		{
			unadviceState();

			mCurrentSkin->getPropertySet()->eventChangeProperty -= MyGUI::newDelegate(this, &StateTextureControl::notifyChangeProperty);
			mCurrentSkin->eventStateChangeSelection -= MyGUI::newDelegate(this, &StateTextureControl::notifyStateChangeSelection);
			mCurrentSkin = nullptr;
		}
	}

	void StateTextureControl::advice()
	{
		mCurrentSkin = SkinManager::getInstance().getItemSelected();

		if (mCurrentSkin != nullptr)
		{
			mCurrentSkin->getPropertySet()->eventChangeProperty += MyGUI::newDelegate(this, &StateTextureControl::notifyChangeProperty);
			mCurrentSkin->eventStateChangeSelection += MyGUI::newDelegate(this, &StateTextureControl::notifyStateChangeSelection);

			adviceState();
		}
	}

	void StateTextureControl::adviceState()
	{
		mCurrentState = mCurrentSkin->getStateSelected();
		if (mCurrentState != nullptr)
		{
			mCurrentState->getPropertySet()->eventChangeProperty += MyGUI::newDelegate(this, &StateTextureControl::notifyChangePropertyState);
		}
	}

	void StateTextureControl::unadviceState()
	{
		if (mCurrentState != nullptr)
		{
			mCurrentState->getPropertySet()->eventChangeProperty -= MyGUI::newDelegate(this, &StateTextureControl::notifyChangePropertyState);
			mCurrentState = nullptr;
		}
	}

	void StateTextureControl::notifyChangePropertyState(Property* _sender, const MyGUI::UString& _owner)
	{
		if (_owner != mTypeName)
		{
			if (_sender->getName() == "Visible")
				updateVisible();
			else if (_sender->getName() == "Position")
				updatePosition();
		}
	}

	void StateTextureControl::updateAllStateProperties()
	{
		updateVisible();
		updatePosition();
	}

	void StateTextureControl::updateVisible()
	{
		MyGUI::UString visible;

		if (mCurrentState != nullptr)
		{
			Property* prop = mCurrentState->getPropertySet()->getChild("Visible");
			if (prop != nullptr)
				visible = prop->getValue();
		}

		mRegionSelectorControl->setVisible(visible == "True");
	}

	void StateTextureControl::updatePosition()
	{
		MyGUI::UString value;

		if (mCurrentState != nullptr)
		{
			Property* prop = mCurrentState->getPropertySet()->getChild("Position");
			if (prop != nullptr)
				value = prop->getValue();
		}

		MyGUI::IntPoint position;
		if (MyGUI::utility::parseComplex(value, position.left, position.top))
		{
			mRegionSelectorControl->setPosition(position);
		}
	}

	void StateTextureControl::notifyStateChangeSelection()
	{
		unadviceState();
		adviceState();

		updateAllProperties();
		updateAllStateProperties();
	}

	void StateTextureControl::notifyChangeProperty(Property* _sender, const MyGUI::UString& _owner)
	{
		if (_owner != mTypeName)
		{
			if (_sender->getName() == "Texture")
				updateTexture();
			else if (_sender->getName() == "Coord")
				updateCoord();
		}
	}

	void StateTextureControl::updateAllProperties()
	{
		updateTexture();
		updateCoord();
	}

	void StateTextureControl::updateTexture()
	{
		MyGUI::UString texture;

		if (mCurrentSkin != nullptr)
		{
			Property* prop = mCurrentSkin->getPropertySet()->getChild("Texture");
			if (prop != nullptr)
				texture = prop->getValue();
		}

		mTextureSize = MyGUI::texture_utility::getTextureSize(texture);
		mTexture->setImageTexture(texture);

		updateScale();
	}

	void StateTextureControl::updateCoord()
	{
		MyGUI::UString value;

		if (mCurrentSkin != nullptr)
		{
			Property* prop = mCurrentSkin->getPropertySet()->getChild("Coord");
			if (prop != nullptr)
				value = prop->getValue();
		}

		MyGUI::IntCoord coord;
		if (MyGUI::utility::parseComplex(value, coord.left, coord.top, coord.width, coord.height))
		{
			mCoordValue = coord;
			mRegionSelectorControl->setVisible(true);
			updateRegionCoord();
		}
		else
		{
			mRegionSelectorControl->setVisible(false);
		}
	}

	void StateTextureControl::fillColours(MyGUI::ComboBox* _combo)
	{
		_combo->removeAllItems();

		_combo->addItem("Zero", MyGUI::Colour::Zero);
		_combo->addItem("Black", MyGUI::Colour::Black);
		_combo->addItem("White", MyGUI::Colour::White);
		_combo->addItem("Red", MyGUI::Colour::Red);
		_combo->addItem("Green", MyGUI::Colour::Green);
		_combo->addItem("Blue", MyGUI::Colour::Blue);

		_combo->setIndexSelected(0);

		updateColour(_combo);
	}

	void StateTextureControl::notifyComboChangePosition(MyGUI::ComboBox* _sender, size_t _index)
	{
		updateColour(_sender);
	}

	void StateTextureControl::updateColour(MyGUI::ComboBox* _sender)
	{
		if (_sender == mBackgroundColour)
		{
			size_t index = mBackgroundColour->getIndexSelected();
			if (index != MyGUI::ITEM_NONE)
			{
				MyGUI::Colour colour = *mBackgroundColour->getItemDataAt<MyGUI::Colour>(index);
				mBackground->setColour(colour);
				mBackground->setAlpha(colour.alpha);
			}
		}
		else if (_sender == mScale)
		{
			size_t index = mScale->getIndexSelected();
			if (index != MyGUI::ITEM_NONE)
			{
				mScaleValue = *mScale->getItemDataAt<double>(index);
				updateScale();
			}
		}
	}

	void StateTextureControl::fillScale()
	{
		mScale->removeAllItems();

		mScale->addItem("50 %", (double)0.5);
		mScale->addItem("100 %", (double)1);
		mScale->addItem("200 %", (double)2);
		mScale->addItem("400 %", (double)4);
		mScale->addItem("800 %", (double)8);
		mScale->addItem("1600 %", (double)16);

		size_t index = 1;

		mScale->setIndexSelected(index);
		mScaleValue = *mScale->getItemDataAt<double>(index);

		updateScale();
	}

	void StateTextureControl::updateScale()
	{
		double width = (double)mTextureSize.width * mScaleValue;
		double height = (double)mTextureSize.height * mScaleValue;

		mView->setCanvasSize(MyGUI::IntSize((int)width, (int)height));
		mRegionSelectorControl->setScale(mScaleValue);
	}

	void StateTextureControl::updateRegionCoord()
	{
		mRegionSelectorControl->setSize(mCoordValue.size());
	}

	void StateTextureControl::notifyChangePosition()
	{
		MyGUI::IntPoint point = mRegionSelectorControl->getPosition();

		if (mCurrentState != nullptr)
		{
			Property* prop = mCurrentState->getPropertySet()->getChild("Position");
			if (prop != nullptr)
				prop->setValue(point.print(), mTypeName);
		}
	}

} // namespace tools
