/*!
	@file
	@author		Albert Semenov
	@date		08/2008
	@module
*/
/*
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
#ifndef __BASE_MANAGER_H__
#define __BASE_MANAGER_H__

#include <Ogre.h>
#include <OIS.h>
#include <MyGUI.h>
#include "Base/StatisticInfo.h"

namespace MyGUI { class OgrePlatform; }

namespace base
{

	class BaseManager : public Ogre::FrameListener, public OIS::MouseListener , public OIS::KeyListener, public Ogre::WindowEventListener
	{
	public:
		static BaseManager & getInstance();

		BaseManager();
		~BaseManager();

		virtual void prepare(int argc, char **argv); // ������������� ���������� ������
		bool create(); // ������� ��������� ����� ������� ����������
		void destroy(); // ������� ��� ��������� ������� ����������
		void run();
		void quit() { m_exit = true; }

		int getWidth() { return mWidth; }
		int getHeight() { return mHeight; }

		void addResourceLocation(const std::string & _name, const std::string & _group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, const std::string & _type = "FileSystem", bool _recursive = false);

		void setWindowCaption(const std::string & _text);

		void setWallpaper(const std::string & _filename);
		void setDescriptionText(const MyGUI::UString & _text);
		void createDefaultScene();

		statistic::StatisticInfo * getStatisticInfo() { return mInfo; }

	/*internal:*/
		Ogre::SceneManager* getSceneManager() { return mSceneMgr; }
		Ogre::Camera* getCamera() { return mCamera; }

	protected:
		void createInput(); // ������� ������� �����
		void destroyInput(); // ������� ������� �����

		void createGui();
		void destroyGui();

		virtual void createScene() { }
		virtual void destroyScene() { }

		virtual void setupResources(); // ��������� ��� ������� ����������

		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased( const OIS::KeyEvent &arg );

		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);

	protected:
		std::string mRootMedia;
		MyGUI::Gui* mGUI;

	private:
		static BaseManager * m_instance;

		//OIS Input devices
		OIS::InputManager* mInputManager;
		OIS::Keyboard* mKeyboard;
		OIS::Mouse*    mMouse;

		Ogre::Root *mRoot;
		Ogre::Camera* mCamera;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mWindow;
		Ogre::String mResourcePath;

		bool m_exit; // ������� �� ����� ����������
		int mWidth;
		int mHeight; // ������ � ������ ������

		MyGUI::OgrePlatform* mPlatform;
		statistic::StatisticInfo* mInfo;

		std::string mPluginCfgName;
		std::string mResourceXMLName;
		Ogre::SceneNode* mNode;
	};

} // namespace base

#endif // __BASE_MANAGER_H__
