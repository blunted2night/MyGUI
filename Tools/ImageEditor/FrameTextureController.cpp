/*!
	@file
	@author		Albert Semenov
	@date		07/2012
*/

#include "Precompiled.h"
#include "FrameTextureController.h"
#include "FactoryManager.h"
#include "DataSelectorManager.h"
#include "DataManager.h"
#include "PropertyUtility.h"
#include "ScopeManager.h"

namespace tools
{

	FACTORY_ITEM_ATTRIBUTE(FrameTextureController)

	FrameTextureController::FrameTextureController() :
		mControl(nullptr),
		mParentData(nullptr),
		mActivated(false)
	{
	}

	FrameTextureController::~FrameTextureController()
	{
	}

	void FrameTextureController::setTarget(Control* _control)
	{
		mControl = _control->findControl<ScopeTextureControl>();
	}

	void FrameTextureController::activate()
	{
		mParentTypeName = "Index";
		mTypeName = "Frame";

		ScopeManager::getInstance().eventChangeScope.connect(this, &FrameTextureController::notifyChangeScope);
		notifyChangeScope(ScopeManager::getInstance().getCurrentScope());
	}

	void FrameTextureController::deactivate()
	{
		ScopeManager::getInstance().eventChangeScope.disconnect(this);
	}

	void FrameTextureController::notifyChangeDataSelector(Data* _data, bool _changeOnlySelection)
	{
		mParentData = _data;
		if (mParentData != nullptr && mParentData->getType()->getName() != mParentTypeName)
			mParentData = nullptr;

		std::string texture;
		std::string coord;

		if (mParentData != nullptr)
		{
			Property* property = mParentData->getParent()->getProperty("Texture");
			texture = property->getValue();

			if (!property->eventChangeProperty.exist(this, &FrameTextureController::notifyChangeProperty))
				property->eventChangeProperty.connect(this, &FrameTextureController::notifyChangeProperty);

			property = mParentData->getParent()->getProperty("Size");
			coord = property->getValue();

			if (!property->eventChangeProperty.exist(this, &FrameTextureController::notifyChangeProperty))
				property->eventChangeProperty.connect(this, &FrameTextureController::notifyChangeProperty);

			Data* data = mParentData;
			if (data != nullptr)
			{
				for (Data::VectorData::const_iterator child = data->getChilds().begin(); child != data->getChilds().end(); child ++)
				{
					property = (*child)->getProperty("Point");
					if (!property->eventChangeProperty.exist(this, &FrameTextureController::notifyChangeProperty))
						property->eventChangeProperty.connect(this, &FrameTextureController::notifyChangeProperty);
				}
			}
		}

		mControl->setTextureValue(texture);

		updateCoords(coord);
	}

	void FrameTextureController::notifyChangeProperty(Property* _sender)
	{
		if (mParentData != nullptr &&
			mParentData->getType()->getName() == mParentTypeName)
		{
			if (mParentData->getParent() == _sender->getOwner())
			{
				if (_sender->getType()->getName() == "Texture")
				{
					mControl->setTextureValue(_sender->getValue());
				}
				else if (_sender->getType()->getName() == "Size")
				{
					updateCoords(_sender->getValue());
				}
			}
			else if (mParentData == _sender->getOwner())
			{
				if (_sender->getType()->getName() == "Point")
				{
					updateFrames();
				}
			}
		}
	}

	void FrameTextureController::notifyChangeScope(const std::string& _scope)
	{
		if (_scope == mTypeName)
		{
			if (!mActivated)
			{
				if (mControl != nullptr)
				{
					mControl->clearAll();

					DataSelectorManager::getInstance().getEvent(mParentTypeName)->connect(this, &FrameTextureController::notifyChangeDataSelector);
					mParentData = DataManager::getInstance().getSelectedDataByType(mParentTypeName);
					notifyChangeDataSelector(mParentData, false);

					mControl->getRoot()->setUserString("CurrentScopeController", mParentTypeName);
				}

				mActivated = true;
			}
		}
		else
		{
			if (mActivated)
			{
				if (mControl != nullptr)
				{
					DataSelectorManager::getInstance().getEvent(mParentTypeName)->disconnect(this);
					mParentData = nullptr;

					// �� ��� ��������� �������� ���������� ���
					std::string value = mControl->getRoot()->getUserString("CurrentScopeController");
					if (value == mParentTypeName)
					{
						mControl->getRoot()->setUserString("CurrentScopeController", "");
						notifyChangeDataSelector(mParentData, false);

						mControl->clearAll();
					}
				}

				mActivated = false;
			}
		}
	}

	void FrameTextureController::updateCoords(const std::string& _value)
	{
		MyGUI::IntCoord coord;
		if (MyGUI::utility::parseComplex(_value, coord.left, coord.top, coord.width, coord.height))
			mSize = coord.size();
		else
			mSize.clear();

		for (VectorCoord::iterator frame = mFrames.begin(); frame != mFrames.end(); frame ++)
		{
			(*frame).width = mSize.width;
			(*frame).height = mSize.height;
		}

		updateFrames();
	}

	void FrameTextureController::updateFrames()
	{
		mFrames.clear();

		Data* selected = mParentData->getChildSelected();
		if (mParentData != nullptr)
		{
			for (Data::VectorData::const_iterator child = mParentData->getChilds().begin(); child != mParentData->getChilds().end(); child ++)
			{
				if (selected == (*child))
				{
				}
				else
				{
					MyGUI::IntPoint value = (*child)->getPropertyValue<MyGUI::IntPoint>("Point");
					mFrames.push_back(MyGUI::IntCoord(value, mSize));
				}
			}
		}

		if (mControl != nullptr)
			mControl->setViewSelectors(mFrames);
	}

}
