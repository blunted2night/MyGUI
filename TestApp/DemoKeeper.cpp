/*!
    @file
    @author     Albert Semenov
    @date       08/2008
    @module
*/
#include "precompiled.h"
#include "DemoKeeper.h"

//#include "OgreMemoryManager.h"
#include "MyGUI_LayerKeeper.h"

namespace demo
{

	void diagnosticRenderItem(MyGUI::WidgetPtr _widget)
	{
		// ��� ������� ����, � �������� ���������� ���� ��������, ���� �� 0 � ����,
		// �� �� ����� � ��� �� �����
		MyGUI::LayerKeeper * layer = _widget->getLayerKeeper();

		// ��� ��� �����, �.�. ����� ��������, ���� ����� ���������������, �� ������� ���� ������,
		// ���� ���, �� ���� ������� �� ���� ��� � ���� ����
		MyGUI::LayerItemKeeper * layer_item = _widget->getLayerItemKeeper();

		// �� ���
		if (layer) {

			if (!_widget->isRootWidget()) {
				MYGUI_EXCEPT("layer != null && !isRootWidget()");
			}

			if (!layer_item) {
				MYGUI_EXCEPT("layer != null && layer_item == null");
			}

			// ��������� ������������ ������ � ��� ������
			bool exist = layer->existItem(layer_item);
			if (!exist) {
				MYGUI_EXCEPT("layer item is not exist");
			}

		}
		// �� �� ���
		else {
			if (layer_item) {
				// ���� �������� ����
				MyGUI::ICroppedRectangle * parent = _widget->getCroppedParent();
				if (!parent) {
					MYGUI_EXCEPT("cropped parent == null");
				}

				while (parent->getCroppedParent()) {

					// � �� �����, �� ������ ���� �����
					MyGUI::LayerKeeper * layer3 = static_cast<MyGUI::WidgetPtr>(parent)->getLayerKeeper();
					if (layer3) {
						MYGUI_EXCEPT("layer != null");
					}

					parent = parent->getCroppedParent();
				};
				MyGUI::LayerKeeper * layer3 = static_cast<MyGUI::WidgetPtr>(parent)->getLayerKeeper();

				// � ���� ������ ���� �����
				if (!layer3) {
					MYGUI_EXCEPT("layer == null");
				}

				// ��������� ������������ ������ � ��� ������
				bool exist = layer3->existItem(layer_item);
				if (!exist) {
					MYGUI_EXCEPT("layer item is not exist");
				}
				
			}
			// �� ����������
			else {
			}

			// ��������� ��� �� ������ ���� ����������
		}
	}

	void notifyRootMouseChangeFocus(MyGUI::WidgetPtr _sender, bool _focus)
	{
		_sender->setAlpha(_focus ? 1 : 0.5);
	}

	void notifyMouseButtonClick(MyGUI::WidgetPtr _sender)
	{
		MyGUI::WindowPtr window = *_sender->getUserData<MyGUI::WindowPtr>();
		window->destroySmooth();
	}

	void notifyRootKeyChangeFocus(MyGUI::WidgetPtr _sender, bool _focus)
	{
		_sender->setState(_focus ? "pushed" : "normal");
	}

    void DemoKeeper::createScene()
    {
		MyGUI::helper::addResourceLocation("D:/MyGUI_Source/trunk/Media/TestApp", "FileSystem", "General", false, false);
		MyGUI::ResourceManager::getInstance().load("test_skin.xml");

		base::BaseManager::getInstance().addResourceLocation("../../Media/Wallpapers");
        base::BaseManager::getInstance().setWallpaper("wallpaper0.jpg");

		//MyGUI::Gui::getInstance().hidePointer();
		//delete mInfo;
		//mInfo = null;//*/


		//MyGUI::WidgetPtr widget1 = mGUI->createWidget<MyGUI::Widget>("WindowCSX", MyGUI::IntCoord(200, 20, 150, 100), MyGUI::Align::Default, "Overlapped");
		//MyGUI::WidgetPtr widget2 = widget1->createWidget<MyGUI::Widget>("ButtonX", MyGUI::IntCoord(10, 10, 50, 50), MyGUI::Align::Default);

		//MyGUI::WidgetPtr widget3 = widget1->createWidgetRoot<MyGUI::Widget>("Test", MyGUI::IntCoord(50, 50, 100, 100), MyGUI::Align::Default, "Back");
		//MyGUI::WidgetPtr widget4 = widget3->createWidgetRoot<MyGUI::Widget>("ButtonV", MyGUI::IntCoord(10, 10, 50, 50), MyGUI::Align::Default, "Overlapped");

		//widget1->attachToLayer("Back");
		//widget3->detachFromWidget();

		//widget3->changeWidgetSkin("ScrollView");

		//diagnosticRenderItem(widget1);
		//diagnosticRenderItem(widget3);

		//widget1->eventRootMouseChangeFocus = MyGUI::newDelegate(notifyRootMouseChangeFocus);
		//widget3->eventRootMouseChangeFocus = MyGUI::newDelegate(notifyRootMouseChangeFocus);


		/*MyGUI::WindowPtr window = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(400, 400, 200, 200), MyGUI::Align::Default, "Back");
		MyGUI::ButtonPtr button = window->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(0, 0, 20, 20), MyGUI::Align::Default);
		MyGUI::RenderBoxPtr render = window->createWidget<MyGUI::RenderBox>("RenderBox", MyGUI::IntCoord(30, 30, 100, 100), MyGUI::Align::Default);
		render->setRenderTarget(this->mCamera);

		button->setUserData(window);
		button->eventMouseButtonClick = MyGUI::newDelegate(notifyMouseButtonClick);*/
		//window->destroySmooth();

		
		/*MyGUI::WidgetPtr menu = mGUI->createWidget<MyGUI::MenuCtrl>("PopupMenu", MyGUI::IntCoord(200, 20, 150, 100), MyGUI::Align::Default, "Overlapped");

		MyGUI::WidgetPtr item1 = menu->createWidget<MyGUI::MenuItem>("", MyGUI::IntCoord(), MyGUI::Align::Default);
		MyGUI::WidgetManager::getInstance().parse(item1, "Widget_Caption", "line1");
		MyGUI::WidgetManager::getInstance().parse(item1, "MenuItem_Type", "Popup");

		MyGUI::WidgetPtr item2 = menu->createWidget<MyGUI::MenuItem>("", MyGUI::IntCoord(), MyGUI::Align::Default);
		MyGUI::WidgetManager::getInstance().parse(item2, "Widget_Caption", "line2");
		MyGUI::WidgetManager::getInstance().parse(item2, "MenuItem_Type", "Normal");

		MyGUI::WidgetPtr item_child = item1->createWidget<MyGUI::MenuCtrl>("PopupMenu", MyGUI::IntCoord(), MyGUI::Align::Default);

		MyGUI::WidgetPtr subitem1 = item_child->createWidget<MyGUI::MenuItem>("", MyGUI::IntCoord(), MyGUI::Align::Default);
		MyGUI::WidgetManager::getInstance().parse(subitem1, "Widget_Caption", "subline1");

		MyGUI::WidgetPtr subitem2 = item_child->createWidget<MyGUI::MenuItem>("", MyGUI::IntCoord(), MyGUI::Align::Default);
		MyGUI::WidgetManager::getInstance().parse(subitem2, "Widget_Caption", "subline2");
		MyGUI::WidgetManager::getInstance().parse(subitem2, "MenuItem_Type", "Popup");

		MyGUI::WidgetPtr subsubmenu = subitem2->createWidget<MyGUI::MenuCtrl>("PopupMenu", MyGUI::IntCoord(), MyGUI::Align::Default);

		MyGUI::WidgetPtr subsubitem1 = subsubmenu->createWidget<MyGUI::MenuItem>("", MyGUI::IntCoord(), MyGUI::Align::Default);
		MyGUI::WidgetManager::getInstance().parse(subsubitem1, "Widget_Caption", "finish");

		menu->show();*/

		MyGUI::MenuCtrlPtr menu = mGUI->createWidget<MyGUI::MenuBar>("MenuBar", MyGUI::IntCoord(420, 20, 750, 30), MyGUI::Align::Default, "Overlapped");

		MyGUI::MenuItemPtr item1 = menu->addItem("line1", MyGUI::MenuItemType::Popup);
		MyGUI::MenuItemPtr item2 = menu->addItem("line2", MyGUI::MenuItemType::Normal);
		MyGUI::MenuItemPtr item3 = menu->addItem("line3", MyGUI::MenuItemType::Popup);

		MyGUI::MenuCtrlPtr submenu1 = item1->createItemChild();
		MyGUI::MenuItemPtr subitem1 = submenu1->addItem("subline1", MyGUI::MenuItemType::Normal);
		MyGUI::MenuItemPtr subitem2 = submenu1->addItem("subline2", MyGUI::MenuItemType::Popup);

		MyGUI::MenuCtrlPtr submenu2 = item3->createItemChild();
		MyGUI::MenuItemPtr subitem21 = submenu2->addItem("subline21", MyGUI::MenuItemType::Normal);
		MyGUI::MenuItemPtr subitem22 = submenu2->addItem("subline22", MyGUI::MenuItemType::Normal);

		MyGUI::MenuCtrlPtr submenu21 = subitem2->createItemChild();
		MyGUI::MenuItemPtr subitem31 = submenu21->addItem("subline31", MyGUI::MenuItemType::Popup);

		MyGUI::MenuCtrlPtr submenu41 = subitem31->createItemChild();
		MyGUI::MenuItemPtr subitem41 = submenu41->addItem("subline41", MyGUI::MenuItemType::Normal);

		menu->show();

		//MyGUI::InputManager::getInstance().setKeyFocusWidget(item1);
		//MyGUI::InputManager::getInstance().setKeyFocusWidget(subitem1);



		//MyGUI::WindowPtr window_back = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(20, 20, 200, 150), MyGUI::Align::Default, "Back");
		//window_back->setCaption("Back");

		/*MyGUI::LayerKeeper * layer_keeper = 0;
		MyGUI::EnumeratorLayerKeeperPtr layer = MyGUI::LayerManager::getInstance().getEnumerator();
		while (layer.next()) {
			if (layer->getName() == "Back") {
				layer_keeper = layer.current();
				break;
			}
		}

		size_t first = layer_keeper->getItemCount();

		MyGUI::WindowPtr window_overlapped1 = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(320, 120, 200, 150), MyGUI::Align::Default, "Back");
		window_overlapped1->setCaption("Overlapped1");

		MyGUI::WindowPtr window_overlapped_child1 = window_overlapped1->createWidget<MyGUI::Window>(MyGUI::WidgetType::Popup, "WindowCSX", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::Align::Default, "Back");
		window_overlapped_child1->setCaption("child1");

		MyGUI::WindowPtr window_overlapped_child2 = window_overlapped1->createWidget<MyGUI::Window>(MyGUI::WidgetType::Overlapped, "WindowCSX", MyGUI::IntCoord(10, 10, 100, 100), MyGUI::Align::Default);
		window_overlapped_child2->setCaption("child2");

		MyGUI::WindowPtr window_overlapped_child3 = window_overlapped1->createWidget<MyGUI::Window>(MyGUI::WidgetType::Child, "WindowCSX", MyGUI::IntCoord(40, 40, 100, 100), MyGUI::Align::Default);
		window_overlapped_child3->setCaption("child3");

		MyGUI::WidgetManager::getInstance().destroyWidget(window_overlapped1);

		size_t last = layer_keeper->getItemCount();
		mInfo->change("LOST", last - first);*/
		//window_overlapped1->changeWidgetSkin("WindowCS");
		//window_overlapped_child1->changeWidgetSkin("WindowCS");
		//window_overlapped_child3->changeWidgetSkin("WindowCS");

		//window_overlapped1->setWidgetType(MyGUI::WidgetType::Child);
		//window_overlapped1->setWidgetType(MyGUI::WidgetType::Overlapped);
		//window_overlapped1->setWidgetType(MyGUI::WidgetType::Popup);
		//MyGUI::LayerManager::getInstance().attachToLayerKeeper("Main", window_overlapped1);

		//window_overlapped_child1->setWidgetType(MyGUI::WidgetType::Child);
		//window_overlapped_child1->setWidgetType(MyGUI::WidgetType::Overlapped);
		//window_overlapped_child1->setWidgetType(MyGUI::WidgetType::Popup);
		//MyGUI::LayerManager::getInstance().attachToLayerKeeper("Main", window_overlapped_child1);

		//window_overlapped_child2->setWidgetType(MyGUI::WidgetType::Child);
		//window_overlapped_child2->setWidgetType(MyGUI::WidgetType::Overlapped);
		//window_overlapped_child2->setWidgetType(MyGUI::WidgetType::Popup);
		//MyGUI::LayerManager::getInstance().attachToLayerKeeper("Overlapped", window_overlapped_child2);

		//window_overlapped_child3->setWidgetType(MyGUI::WidgetType::Child);
		//window_overlapped_child3->setWidgetType(MyGUI::WidgetType::Overlapped);
		//window_overlapped_child3->setWidgetType(MyGUI::WidgetType::Popup);
		//MyGUI::LayerManager::getInstance().attachToLayerKeeper("Overlapped", window_overlapped_child3);


		//window_overlapped1->_detachFromLayerItemKeeper();

		//MyGUI::WindowPtr window_overlapped2 = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(460, 260, 200, 150), MyGUI::Align::Default, "Overlapped");
		//window_overlapped2->setCaption("Overlapped2");

		//MyGUI::WindowPtr window_main = mGUI->createWidget<MyGUI::Window>("WindowCSX", MyGUI::IntCoord(620, 420, 200, 150), MyGUI::Align::Default, "Main");
		//window_main->setCaption("Main");

		//MyGUI::LayerManager::getInstance().detachFromLayerKeeper(window_overlapped1);


		//item2->detachFromLayer();

		/*MyGUI::LayerKeeper * layer = item2->getLayerKeeper();
		MyGUI::LayerItemKeeper * layer_item = item2->getLayerItemKeeper();
		MyGUI::ICroppedRectangle * cropped = item1->getCroppedParent();*/

		/*MyGUI::ComboBoxPtr combo = mGUI->createWidget<MyGUI::ComboBox>("ComboBox", MyGUI::IntCoord(20, 20, 200, 26), MyGUI::Align::Default, "Main");
		combo->addItem("line1");
		combo->addItem("line2");*/

		/*MyGUI::WidgetPtr widget1 = mGUI->createWidget<MyGUI::Widget>("Button", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::Align::Default, "Overlapped");
		widget1->setNeedKeyFocus(true);
		widget1->eventRootKeyChangeFocus = MyGUI::newDelegate(notifyRootKeyChangeFocus);

		widget1 = widget1->createWidget<MyGUI::Widget>(MyGUI::WidgetType::Child, "Button", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::Align::Default);
		//widget1->setNeedKeyFocus(true);
		widget1->eventRootKeyChangeFocus = MyGUI::newDelegate(notifyRootKeyChangeFocus);

		widget1 = widget1->createWidget<MyGUI::Widget>(MyGUI::WidgetType::Child, "Button", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::Align::Default);
		//widget1->setNeedKeyFocus(true);
		widget1->eventRootKeyChangeFocus = MyGUI::newDelegate(notifyRootKeyChangeFocus);

		widget1 = widget1->createWidget<MyGUI::Widget>(MyGUI::WidgetType::Popup, "Button", MyGUI::IntCoord(120, 120, 100, 100), MyGUI::Align::Default, "Overlapped");
		widget1->setNeedKeyFocus(true);
		widget1->eventRootKeyChangeFocus = MyGUI::newDelegate(notifyRootKeyChangeFocus);
		
		widget1 = widget1->createWidget<MyGUI::Widget>(MyGUI::WidgetType::Child, "Button", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::Align::Default);
		//widget1->setNeedKeyFocus(true);
		widget1->eventRootKeyChangeFocus = MyGUI::newDelegate(notifyRootKeyChangeFocus);

		widget1 = widget1->createWidget<MyGUI::Widget>(MyGUI::WidgetType::Child, "Button", MyGUI::IntCoord(20, 20, 100, 100), MyGUI::Align::Default);
		widget1->setNeedKeyFocus(true);
		widget1->eventRootKeyChangeFocus = MyGUI::newDelegate(notifyRootKeyChangeFocus);*/

	}
 
    void DemoKeeper::destroyScene()
    {
    }

	bool DemoKeeper::keyPressed( const OIS::KeyEvent &arg )
	{
		return BaseManager::keyPressed(arg);
	}
	 
} // namespace demo
