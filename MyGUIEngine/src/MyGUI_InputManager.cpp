/*!
	@file
	@author		Albert Semenov
	@date		11/2007
	@module
*/
#include "MyGUI_Common.h"
#include "MyGUI_XmlDocument.h"
#include "MyGUI_ResourceManager.h"
#include "MyGUI_InputManager.h"
#include "MyGUI_LayerManager.h"
#include "MyGUI_SkinManager.h"
#include "MyGUI_Widget.h"
#include "MyGUI_RenderOut.h"
#include "MyGUI_WidgetManager.h"
#include "MyGUI_PointerManager.h"
#include "MyGUI_Gui.h"

namespace MyGUI
{
	const std::string XML_TYPE("Lang");
	const std::string INPUT_DEFAULT_LANGUAGE("English");
	const unsigned long INPUT_TIME_DOUBLE_CLICK = 250; //measured in milliseconds
	const float INPUT_DELAY_FIRST_KEY = 0.4f;
	const float INPUT_INTERVAL_KEY = 0.05f;
	const size_t INPUT_COUNT_LOAD_CHAR = 116;
	const size_t INPUT_CHARSET_LIMIT = 65535;

	INSTANCE_IMPLEMENT(InputManager);

	void InputManager::initialise()
	{
		MYGUI_ASSERT(false == mIsInitialise, INSTANCE_TYPE_NAME << " initialised twice");
		MYGUI_LOG(Info, "* Initialise: " << INSTANCE_TYPE_NAME);

		mWidgetMouseFocus = 0;
		mWidgetKeyFocus = 0;
		//mWidgetRootMouseFocus = 0;
		mWidgetRootKeyFocus = 0;
		mIsWidgetMouseCapture = false;
		mIsShiftPressed = false;
		mIsControlPressed = false;
		mHoldKey = KC_UNASSIGNED;
		mHoldChar = 0;
		mFirstPressKey = true;
		mTimerKey = 0.0f;
		mOldAbsZ = 0;

		m_showHelpers = false;
		m_mouseHelper = null;
		m_keyHelper = null;

		createDefaultCharSet();

		WidgetManager::getInstance().registerUnlinker(this);
		Gui::getInstance().eventFrameStart += newDelegate(this, &InputManager::frameEntered);
		ResourceManager::getInstance().registerLoadXmlDelegate(XML_TYPE) = newDelegate(this, &InputManager::_load);

		MYGUI_LOG(Info, INSTANCE_TYPE_NAME << " successfully initialized");
		mIsInitialise = true;
	}

	void InputManager::shutdown()
	{
		if (false == mIsInitialise) return;
		MYGUI_LOG(Info, "* Shutdown: " << INSTANCE_TYPE_NAME);

		Gui::getInstance().eventFrameStart -= newDelegate(this, &InputManager::frameEntered);
		WidgetManager::getInstance().unregisterUnlinker(this);
		ResourceManager::getInstance().unregisterLoadXmlDelegate(XML_TYPE);

		MYGUI_LOG(Info, INSTANCE_TYPE_NAME << " successfully shutdown");
		mIsInitialise = false;
	}

	bool InputManager::injectMouseMove(int _absx, int _absy, int _absz)
	{
		// запоминаем позицию
		mMousePosition.set(_absx, _absy);

		// вычисляем прирост по колеса
		int relz = _absz - mOldAbsZ;
		mOldAbsZ = _absz;

		// двигаем курсор
		PointerManager::getInstance().setPosition(mMousePosition);

		// проверка на скролл
		if (relz != 0) {
			bool isFocus = isFocusMouse();
			if (mWidgetMouseFocus != null) mWidgetMouseFocus->onMouseWheel(relz);
			return isFocus;
		}

		if (mIsWidgetMouseCapture) {
			if (mWidgetMouseFocus != null) mWidgetMouseFocus->onMouseDrag(_absx, _absy);
			else mIsWidgetMouseCapture = false;
			return true;
		}

		// ищем активное окно
		LayerItem *  rootItem = null;
		WidgetPtr item = static_cast<WidgetPtr>(LayerManager::getInstance()._findLayerItem(_absx, _absy, rootItem));

		// спускаемся по владельцу
		if (null != rootItem) {
			while (null != static_cast<WidgetPtr>(rootItem)->_getOwner()) {
				rootItem = static_cast<WidgetPtr>(rootItem)->_getOwner();
			}
		}	

		// ничего не изменилось
		if (mWidgetMouseFocus == item) {
			bool isFocus = isFocusMouse();
			if (mWidgetMouseFocus != null) mWidgetMouseFocus->onMouseMove(_absx, _absy);
			return isFocus;
		}

		// проверяем на модальность
		if (0 != mVectorModalRootWidget.size()) {
			if (rootItem != mVectorModalRootWidget.back()) {
				rootItem = null;
				item = null;
			}
		}

		// новый вид рутового фокуса мыши
		WidgetPtr save_widget = null;

		// спускаемся по новому виджету и устанавливаем рутовый фокус
		WidgetPtr root_focus = item;
		while (root_focus != null) {
			if (root_focus->mRootMouseActive) {
				save_widget = root_focus;
				break;
			}
			root_focus->mRootMouseActive = true;
			root_focus->onMouseChangeRootFocus(true);

			root_focus = root_focus->_getOwner();
		};

		// спускаемся по старому виджету и сбрасываем фокус
		root_focus = mWidgetMouseFocus;
		while (root_focus != null) {
			if (root_focus == save_widget) {
				break;
			}
			root_focus->mRootMouseActive = false;
			root_focus->onMouseChangeRootFocus(false);

			root_focus = root_focus->_getOwner();
		};

		// смена фокуса, проверяем на доступность виджета
		if ((mWidgetMouseFocus != null) && (mWidgetMouseFocus->isEnabled())) {
			mWidgetMouseFocus->onMouseLostFocus(item);
		}

		if ((item != null) && (item->isEnabled())) {
			if (item->getPointer() != mPointer) {
				mPointer = item->getPointer();
				if (mPointer.empty()) {
					PointerManager::getInstance().setDefaultPointer();
					eventChangeMousePointer(PointerManager::getInstance().getDefaultPointer());
				}
				else {
					PointerManager::getInstance().setPointer(mPointer, item);
					eventChangeMousePointer(mPointer);
				}
			}
			item->onMouseMove(_absx, _absy);
			item->onMouseSetFocus(mWidgetMouseFocus);

		}
		// сбрасываем курсор
		else if (false == mPointer.empty()) {
			PointerManager::getInstance().setDefaultPointer();
			mPointer.clear();

			eventChangeMousePointer(PointerManager::getInstance().getDefaultPointer());
		}

		// изменился рутовый элемент
		//if (rootItem != mWidgetRootMouseFocus) {
			//if (mWidgetRootMouseFocus != null) mWidgetRootMouseFocus->onMouseChangeRootFocus(false);
			//if (rootItem != null) static_cast<WidgetPtr>(rootItem)->onMouseChangeRootFocus(true);
			//mWidgetRootMouseFocus = static_cast<WidgetPtr>(rootItem);
		//}

		// запоминаем текущее окно
		mWidgetMouseFocus = item;

		// обновляем данные
		if (m_showHelpers) updateFocusWidgetHelpers();

		return isFocusMouse();
	}

	bool InputManager::injectMousePress(int _absx, int _absy, MouseButton _id)
	{

		// если мы щелкнули не на гуй
		if (false == isFocusMouse()) {
			resetKeyFocusWidget();
			return false;
		}

		// если активный элемент заблокирован
		if (false == mWidgetMouseFocus->isEnabled()) return true;

		// захватываем только по левой клавише и только если виджету надо
		if (MB_Left == _id) {
			// захват окна
			mIsWidgetMouseCapture = true;
			// запоминаем место нажатия
			mLastLeftPressed.set(_absx, _absy);
		}

		// ищем вверх тот виджет который может принимать фокус
		WidgetPtr focus = mWidgetMouseFocus;
		while ((focus != null) && (false == focus->isNeedKeyFocus())) focus = focus->getParent();

		// устанавливаем перед вызовом т.к. возможно внутри ктонить поменяет фокус под себя
		setKeyFocusWidget(focus);

		if (mWidgetMouseFocus != null) {

			mWidgetMouseFocus->onMouseButtonPressed(_absx, _absy, _id);
			//mWidgetMouseFocus->onMouseButtonPressed(_id);

			// поднимаем виджет
			LayerManager::getInstance().upLayerItem(mWidgetMouseFocus);
		}
		return true;
	}

	bool InputManager::injectMouseRelease(int _absx, int _absy, MouseButton _id)
	{

		if (isFocusMouse()) {

			// если активный элемент заблокирован
			if (false == mWidgetMouseFocus->isEnabled()) return true;

			mWidgetMouseFocus->onMouseButtonReleased(_absx, _absy, _id);

			if (mIsWidgetMouseCapture) {

				// сбрасываем захват
				mIsWidgetMouseCapture = false;

				// после вызова, виджет может быть сброшен
				if (null != mWidgetMouseFocus) {

					if ((MB_Left == _id) && mTime.getMilliseconds() < INPUT_TIME_DOUBLE_CLICK) {
						mWidgetMouseFocus->onMouseButtonClick();
						// после вызова, виджет может быть сброшен
						if (null != mWidgetMouseFocus) mWidgetMouseFocus->onMouseButtonDoubleClick();
					}
					else {
						// проверяем над тем ли мы окном сейчас что и были при нажатии
						LayerItem * rootItem = null;
						WidgetPtr item = static_cast<WidgetPtr>(LayerManager::getInstance()._findLayerItem(_absx, _absy, rootItem));
						if ( item == mWidgetMouseFocus) {
							mWidgetMouseFocus->onMouseButtonClick();
						}
						mTime.reset();
					}
				}
			}

			// для корректного отображения
			injectMouseMove(_absx, _absy, mOldAbsZ);

			return true;
		}

		return false;
	}

	bool InputManager::injectKeyPress(KeyCode _key, Char _text)
	{
		// проверка на переключение языков
		firstEncoding(_key, true);

		Char ch = getKeyChar(_key, _text);

		// запоминаем клавишу
		storeKey(_key, ch);

		bool wasFocusKey = isFocusKey();

		//Pass keystrokes to the current active text widget
		if (isFocusKey()) {
			mWidgetKeyFocus->onKeyButtonPressed(_key, ch);
		}

		return wasFocusKey;
	}

	bool InputManager::injectKeyRelease(KeyCode _key)
	{
		// проверка на переключение языков
		firstEncoding(_key, false);

		// сбрасываем клавишу
		resetKey();

		bool wasFocusKey = isFocusKey();

		if (isFocusKey()) mWidgetKeyFocus->onKeyButtonReleased(_key);

		return wasFocusKey;
	}

	void InputManager::firstEncoding(KeyCode _key, bool bIsKeyPressed)
	{
#ifndef MYGUI_NO_OIS
		if ((_key == KC_LSHIFT) || (_key == KC_RSHIFT)) mIsShiftPressed = bIsKeyPressed;
		if ((_key == KC_LCONTROL) || (_key == KC_RCONTROL)) mIsControlPressed = bIsKeyPressed;
#else
		// если переключать не надо
		if (mMapLanguages.size() == 1) return;

		// для облегчения распознавания используются LeftAlt+LeftShift или LeftCtrl+LeftShift,LeftShift+LeftAlt или LeftShift+LeftCtrl
		static bool bIsFirstKeyPressed = false; // LeftAlt или LeftCtrl
		static bool bIsSecondKeyPressed = false; // LeftShift
		static bool bIsTwoKeyPressed = false; // обе были зажаты

		if ((_key == KC_LSHIFT) || (_key == KC_RSHIFT)) {
			if (bIsKeyPressed) {
				mIsShiftPressed = true;
				bIsSecondKeyPressed = true;
				if (bIsFirstKeyPressed) bIsTwoKeyPressed = true;
			}
			else {
				mIsShiftPressed = false;
				bIsSecondKeyPressed = false;
				if ((!bIsFirstKeyPressed) && (bIsTwoKeyPressed)) {
					bIsTwoKeyPressed = false;
					// следующий язык
					changeLanguage();
				}
			}
		}
		else if ((_key == KC_LMENU) || (_key == KC_RMENU)
			|| (_key == KC_LCONTROL) || (_key == KC_RCONTROL)) {

			if ((_key == KC_LCONTROL) || (_key == KC_RCONTROL)) mIsControlPressed = bIsKeyPressed;

			if (bIsKeyPressed) {
				bIsFirstKeyPressed = true;
				if (bIsSecondKeyPressed) bIsTwoKeyPressed = true;
			}
			else {
				bIsFirstKeyPressed = false;
				if ((!bIsSecondKeyPressed) && (bIsTwoKeyPressed)) {
					bIsTwoKeyPressed = false;
					// следующий язык
					changeLanguage();
				}
			}
		}
		else {
			bIsFirstKeyPressed = false;
			bIsSecondKeyPressed = false;
			bIsTwoKeyPressed = false;
		}
#endif
	}

#ifndef MYGUI_NO_OIS
#    if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32

	Char translateWin32Text( KeyCode kc )
	{
		static WCHAR deadKey = 0;

		BYTE keyState[256];
		HKL  layout = GetKeyboardLayout(0);
		if ( GetKeyboardState(keyState) == 0 )
			return 0;

		unsigned int vk = MapVirtualKeyEx(kc, 3, layout);
		if ( vk == 0 )
			return 0;

		WCHAR buff[3] = {0, 0, 0};
		int ascii = ToUnicodeEx(vk, kc, keyState, buff, 3, 0, layout);
		if (ascii == 1 && deadKey != '\0' ) {
			// A dead key is stored and we have just converted a character key
			// Combine the two into a single character
			WCHAR wcBuff[3] = {buff[0], deadKey, '\0'};
			WCHAR out[3];
			
			deadKey = '\0';
			if(FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuff, 3, (LPWSTR)out, 3))
				return out[0];
		}
		else if (ascii == 1) {
			// We have a single character
			deadKey = '\0';
			return buff[0];
		}
		else if(ascii == 2) {
			// Convert a non-combining diacritical mark into a combining diacritical mark
			// Combining versions range from 0x300 to 0x36F; only 5 (for French) have been mapped below
			// http://www.fileformat.info/info/unicode/block/combining_diacritical_marks/images.htm
			switch(buff[0])	{
			case 0x5E: // Circumflex accent: в
				deadKey = 0x302; break;
			case 0x60: // Grave accent: а
				deadKey = 0x300; break;
			case 0xA8: // Diaeresis: ь
				deadKey = 0x308; break;
			case 0xB4: // Acute accent: й
				deadKey = 0x301; break;
			case 0xB8: // Cedilla: з
				deadKey = 0x327; break;
			default:
				deadKey = buff[0]; break;
			}
		}

		return 0;
	}

#    endif
#endif

	Char InputManager::getKeyChar(KeyCode _key, Char _text) // возвращает символ по его скан коду
	{
		Char result = 0;
#ifndef MYGUI_NO_OIS
		// нумлок транслейтим ручками
		if (_key > 70 && _key < 84) {
			result = mNums[_key-71];
		}
		else if (_key == KC_DIVIDE) {
			result = '/';
		}
		//else if (_key == KC_OEM_102) {
		//	result = '\\';
		//}
		else {
#    if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
			result = translateWin32Text(_key);
#    else
			result = _text;
#    endif
		}
#else
		if (_key < 58) {
			result = mCurrentLanguage->second[_key + (mIsShiftPressed ? 58 : 0)];
		}
		else if (_key < 84) {
			if (_key > 70) {
				result = mNums[_key-71];
			}
		}
		else if (_key == KC_DIVIDE) {
			result = mCurrentLanguage->second[KC_SLASH + (mIsShiftPressed ? 58 : 0)];
		}
		//else if (_key == KC_OEM_102) {
		//	result = mCurrentLanguage->second[KC_BACKSLASH + (mIsShiftPressed ? 58 : 0)];
		//}
#endif
		return result;
	}

	void InputManager::createDefaultCharSet()
	{
#ifdef MYGUI_NO_OIS
		// вставляем английский язык
		mMapLanguages[INPUT_DEFAULT_LANGUAGE] = LangInfo();
		mCurrentLanguage = mMapLanguages.find(INPUT_DEFAULT_LANGUAGE);
		mCurrentLanguage->second.resize(INPUT_COUNT_LOAD_CHAR);

		// временный массив
		Char chars[INPUT_COUNT_LOAD_CHAR] = {
			0, 0, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 45, 61, 0, 0, 113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 91, 93, 0, 0, 97, 115, 100, 102, 103, 104, 106, 107, 108, 59, 39, 96, 0, 92, 122, 120, 99, 118, 98, 110, 109, 44, 46, 47, 0, 42, 0, 32, // normal
			0, 0, 33, 64, 35, 36, 37, 94, 38, 42, 40, 41, 95, 43, 0, 0, 81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 123, 125, 0, 0, 65, 83, 68, 70, 71, 72, 74, 75, 76, 58, 34, 126, 0, 124, 90, 88, 67, 86, 66, 78, 77, 60, 62, 63, 0, 42, 0, 32 // shift
		};
		// копируем в постоянное место
		LangInfo & lang = mCurrentLanguage->second;
		for (size_t i=0; i<INPUT_COUNT_LOAD_CHAR; i++) lang[i] = chars[i];
#endif
		// добавляем клавиши для нумлока
		Char nums[13] = {55, 56, 57, 45, 52, 53, 54, 43, 49, 50, 51, 48, 46};
		mNums.resize(13);
		// копируем в постоянное место
		for (size_t i=0; i<13; i++) mNums[i] = nums[i];
	}

#ifdef MYGUI_NO_OIS

	bool InputManager::load(const std::string & _file, const std::string & _group)
	{
		return ResourceManager::getInstance()._loadImplement(_file, _group, true, XML_TYPE, INSTANCE_TYPE_NAME);
	}

	void InputManager::setCurrentLanguage(const std::string & _lang)
	{
		MapLang::iterator iter = mMapLanguages.find(_lang);
		if (iter != mMapLanguages.end()) {
			mCurrentLanguage = iter;
		}
		else {
			MYGUI_LOG(Warning, "language '" << _lang << "' not found");
		}
	}

#endif

	void InputManager::_load(xml::xmlNodePtr _node, const std::string & _file, Version _version)
	{
#ifdef MYGUI_NO_OIS
		xml::xmlNodeIterator lang = _node->getNodeIterator();
		while (lang.nextNode(XML_TYPE)) {

			std::string name;
			if ( false == lang->findAttribute("name", name)) continue;

			std::vector<std::string> chars = utility::split(lang->getBody(), "\x09\x0a,");
			if (chars.size() == INPUT_COUNT_LOAD_CHAR) {

				// сначала проверяем есть ли такой язык уже
				MapLang::iterator iter = mMapLanguages.find(name);
				MYGUI_ASSERT(iter == mMapLanguages.end(), "language '" << name << "' already exist");

				// создаем язык
				mMapLanguages[name] = LangInfo();
				iter = mMapLanguages.find(name);
				iter->second.resize(INPUT_COUNT_LOAD_CHAR);
				LangInfo & lang = iter->second;

				// и заполняем его
				for (size_t j=0; j<INPUT_COUNT_LOAD_CHAR; j++) {
					Char ch = utility::parseUInt(chars[j]);
					if (INPUT_CHARSET_LIMIT < ch) {
						lang[j] = 0;
						MYGUI_LOG(Warning, "character with code '" << ch << "' out of range");
					}
					else {
						lang[j] = (Char)ch;
					}
				}

			}
			else {
				MYGUI_LOG(Warning, "Quantity of characters is not " << INPUT_COUNT_LOAD_CHAR);
			}

		};

		// обязательно обновляем итератор, так как не гарантируеться его сохранение
		mCurrentLanguage = mMapLanguages.find(INPUT_DEFAULT_LANGUAGE);
#endif
	}

	void InputManager::setKeyFocusWidget(WidgetPtr _widget)
	{
		// ищем рутовый фокус
		WidgetPtr root = _widget;
		if (root != null) { while (root->_getOwner() != null) root = root->_getOwner(); }

		// если рутовый фокус поменялся, то оповещаем
		if (mWidgetRootKeyFocus != root) {
			if (mWidgetRootKeyFocus != null) mWidgetRootKeyFocus->onKeyChangeRootFocus(false);
			if (root != null) root->onKeyChangeRootFocus(true);
			mWidgetRootKeyFocus = root;
		}

		// а вот тут уже проверяем обыкновенный фокус
		if (_widget != mWidgetKeyFocus) {
			if (isFocusKey()) mWidgetKeyFocus->onKeyLostFocus(_widget);
			if (_widget != null) {
				if (_widget->isNeedKeyFocus()) {
					_widget->onKeySetFocus(mWidgetKeyFocus);
					mWidgetKeyFocus = _widget;
					return;
				}
			}
			mWidgetKeyFocus = null;
		}

		// обновляем данные
		if (m_showHelpers) updateFocusWidgetHelpers();

	}

	void InputManager::resetMouseFocusWidget()
	{
		// спускаемся по старому виджету и сбрасываем фокус
		WidgetPtr root_focus = mWidgetMouseFocus;
		while (root_focus != null) {
			root_focus->mRootMouseActive = false;
			root_focus->onMouseChangeRootFocus(false);

			root_focus = root_focus->_getOwner();
		};

		mIsWidgetMouseCapture = false;
		if (null != mWidgetMouseFocus) {
			mWidgetMouseFocus->onMouseLostFocus(null);
			mWidgetMouseFocus = null;
		}

		/*if (null != mWidgetRootMouseFocus) {
			mWidgetRootMouseFocus->onMouseChangeRootFocus(false);
			mWidgetRootMouseFocus = null;
		}*/

		// обновляем данные
		if (m_showHelpers) updateFocusWidgetHelpers();

	}

	// удаляем данный виджет из всех возможных мест
	void InputManager::_unlinkWidget(WidgetPtr _widget)
	{
		if (null == _widget) return;
		if (_widget == mWidgetMouseFocus) {
			mIsWidgetMouseCapture = false;
			mWidgetMouseFocus = null;

			// обновляем данные
			if (m_showHelpers) updateFocusWidgetHelpers();
		}
		if (_widget == mWidgetKeyFocus) {
			mWidgetKeyFocus = null;

			// обновляем данные
			if (m_showHelpers) updateFocusWidgetHelpers();
		}
		//if (_widget == mWidgetRootMouseFocus) mWidgetRootMouseFocus = null;
		if (_widget == mWidgetRootKeyFocus) mWidgetRootKeyFocus = null;

		// ручками сбрасываем, чтобы не менять фокусы
		for (VectorWidgetPtr::iterator iter=mVectorModalRootWidget.begin(); iter!=mVectorModalRootWidget.end(); ++iter) {
			if ((*iter == _widget)) {
				mVectorModalRootWidget.erase(iter);
				break;
			}
		}

	}

	void InputManager::addWidgetModal(WidgetPtr _widget)
	{
		if (null == _widget) return;
		MYGUI_ASSERT(null == _widget->getParent(), "Modal widget must be root");

		resetMouseFocusWidget();
		removeWidgetModal(_widget);
		mVectorModalRootWidget.push_back(_widget);

		setKeyFocusWidget(_widget);
		LayerManager::getInstance().upLayerItem(_widget);
	}

	void InputManager::removeWidgetModal(WidgetPtr _widget)
	{
		resetKeyFocusWidget(_widget);
		resetMouseFocusWidget();

		for (VectorWidgetPtr::iterator iter=mVectorModalRootWidget.begin(); iter!=mVectorModalRootWidget.end(); ++iter) {
			if ((*iter == _widget)) {
				mVectorModalRootWidget.erase(iter);
				break;
			}
		}
		// если еще есть модальные то их фокусируем и поднимаем
		if (false == mVectorModalRootWidget.empty()) {
			setKeyFocusWidget(mVectorModalRootWidget.back());
			LayerManager::getInstance().upLayerItem(mVectorModalRootWidget.back());
		}
	}

	void InputManager::storeKey(KeyCode _key, Char _text)
	{
		mHoldKey = KC_UNASSIGNED;
		mHoldChar = 0;

		if ( false == isFocusKey() ) return;
		if ( (_key == KC_LSHIFT) || (_key == KC_RSHIFT)
			|| (_key == KC_LCONTROL) || (_key == KC_RCONTROL)
			|| (_key == KC_LMENU) || (_key == KC_RMENU)
			) return;

		mFirstPressKey = true;
		mHoldKey = _key;
		mHoldChar = _text;
		mTimerKey = 0.0f;
	}

	void InputManager::resetKey()
	{
		mHoldKey = KC_UNASSIGNED;
		mHoldChar = 0;
	}

	void InputManager::frameEntered(float _frame)
	{

		// обновляем данные
		if (m_showHelpers) updateFocusWidgetHelpers();

		if ( mHoldKey == KC_UNASSIGNED) return;
		if ( false == isFocusKey() ) {
			mHoldKey = KC_UNASSIGNED;
			mHoldChar = 0;
			return;
		}

		mTimerKey += _frame;

		if (mFirstPressKey) {
			if (mTimerKey > INPUT_DELAY_FIRST_KEY) {
				mFirstPressKey = false;
				mTimerKey = 0.0f;
			}
		}
		else {
			if (mTimerKey > INPUT_INTERVAL_KEY) {
				while (mTimerKey > INPUT_INTERVAL_KEY) mTimerKey -= INPUT_INTERVAL_KEY;
				mWidgetKeyFocus->onKeyButtonPressed(mHoldKey, mHoldChar);
				// focus can be dropped in onKeyButtonPressed
				if ( isFocusKey() ) mWidgetKeyFocus->onKeyButtonReleased(mHoldKey);
			}
		}

	}


	void InputManager::setShowFocus(bool _show)
	{
		m_showHelpers = _show;
		if (!m_showHelpers) {
			if (m_mouseHelper) m_mouseHelper->hide();
			if (m_keyHelper) m_keyHelper->hide();
		}
	}

	void InputManager::updateFocusWidgetHelpers()
	{

		static const std::string layer = "Statistic";
		static const std::string skin_mouse = "RectGreen";
		static const std::string skin_key = "RectBlue";

		static WidgetPtr mouse_focus = null;
		if ((mWidgetMouseFocus != mouse_focus) || ((mWidgetMouseFocus != null) && (m_mouseHelper != null) && mWidgetMouseFocus->getAbsoluteCoord() != m_mouseHelper->getAbsoluteCoord())) {
			mouse_focus = mWidgetMouseFocus;

			if (m_mouseHelper == null) {
				if (!LayerManager::getInstance().isExist(layer)) return;
				if (!SkinManager::getInstance().isExist(skin_mouse)) return;
				m_mouseHelper = Gui::getInstance().createWidget<Widget>(skin_mouse, IntCoord(), Align::Default, layer);
				m_mouseHelper->setNeedMouseFocus(false);
			}

			if (mWidgetMouseFocus) {
				MYGUI_OUT("mouse focus : ", mWidgetMouseFocus->getName());
				m_mouseHelper->setCoord(mWidgetMouseFocus->getAbsoluteCoord());
				m_mouseHelper->show();
			}
			else {
				MYGUI_OUT("mouse focus : null");
				m_mouseHelper->hide();
			}
		}

		static WidgetPtr key_focus = null;
		if ((mWidgetKeyFocus != key_focus) || ((mWidgetKeyFocus != null) && (m_keyHelper != null) && mWidgetKeyFocus->getAbsoluteCoord() != m_keyHelper->getAbsoluteCoord())) {
			key_focus = mWidgetKeyFocus;

			if (m_keyHelper == null) {
				if (!LayerManager::getInstance().isExist(layer)) return;
				if (!SkinManager::getInstance().isExist(skin_key)) return;
				m_keyHelper = Gui::getInstance().createWidget<Widget>(skin_key, IntCoord(), Align::Default, layer);
				m_keyHelper->setNeedMouseFocus(false);
			}
			if (mWidgetKeyFocus) {
				MYGUI_OUT("key focus : ", mWidgetKeyFocus->getName());
				m_keyHelper->setCoord(mWidgetKeyFocus->getAbsoluteCoord());
				m_keyHelper->show();
			}
			else {
				MYGUI_OUT("key focus : null");
				m_keyHelper->hide();
			}
		}
	}

} // namespace MyGUI
