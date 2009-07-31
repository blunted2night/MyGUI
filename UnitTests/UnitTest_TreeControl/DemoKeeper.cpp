/*!
	@file
	@author     George Evmenov
	@date       08/2009
	@module
*/
#include "DemoKeeper.h"
#include "Base/Main.h"

#include "BaseLayout/BaseLayout.h"
#include "TreeControl.h"
#include "TreeControlItem.h"

class SampleLayout : public wraps::BaseLayout
{
public:
	SampleLayout();

	void notifyTreeNodePrepare(MyGUI::TreeControl* pTreeControl, MyGUI::TreeControl::Node* pNode);
	MyGUI::UString getPath(MyGUI::TreeControl::Node* pNode) const;

private:
	MyGUI::TreeControl * mpResourcesTree;
};

SampleLayout * mSampleLayout;

SampleLayout::SampleLayout() : BaseLayout("SampleLayout.layout")
{
	assignWidget(mpResourcesTree, "ResourcesTree");
	mpResourcesTree->eventTreeNodePrepare = newDelegate(this, &SampleLayout::notifyTreeNodePrepare);

	MyGUI::TreeControl::Node* pRoot = mpResourcesTree->getRoot();
	Ogre::ArchiveManager::ArchiveMapIterator ArchiveIterator = Ogre::ArchiveManager::getSingleton().getArchiveIterator();
	while (ArchiveIterator.hasMoreElements())
	{
		Ogre::Archive* pArchive = ArchiveIterator.getNext();

		MyGUI::TreeControl::Node* pNode = new MyGUI::TreeControl::Node(pArchive->getName(), "Data");
		pNode->setData(pArchive);
		pRoot->add(pNode);
	}
}

void SampleLayout::notifyTreeNodePrepare(MyGUI::TreeControl* pTreeControl, MyGUI::TreeControl::Node* pNode)
{
	if (pNode == pTreeControl->getRoot())
		return;

	pNode->removeAll();
	Ogre::Archive* pArchive = *(pNode->getData<Ogre::Archive*>());

	MyGUI::UString strPath(getPath(pNode));
	Ogre::StringVectorPtr Resources = pArchive->find(strPath + "*", false, true);
	for (Ogre::StringVector::iterator Iterator = Resources->begin(); Iterator != Resources->end(); Iterator++)
	{
		MyGUI::TreeControl::Node* pChild = new MyGUI::TreeControl::Node(*Iterator, "Folder");
		pChild->setData(pArchive);
		pNode->add(pChild);
	}

	Resources = pArchive->find(strPath + "*", false, false);
	for (Ogre::StringVector::iterator Iterator = Resources->begin(); Iterator != Resources->end(); Iterator++)
	{
		MyGUI::UString strName(*Iterator);
		MyGUI::UString strExtension;
		size_t nPosition = strName.rfind(".");
		if (nPosition != MyGUI::UString::npos)
		{
			strExtension = strName.substr(nPosition + 1);
			std::transform(strExtension.begin(), strExtension.end(), strExtension.begin(), tolower);
		}

		MyGUI::UString strImage;
		if (strExtension == "png" || strExtension == "tif" || strExtension == "tiff" || strExtension == "jpg" || strExtension == "jpeg")
			strImage = "Image";
		else
		if (strExtension == "mat" || strExtension == "material")
			strImage = "Material";
		else
		if (strExtension == "layout")
			strImage = "Layout";
		else
		if (strExtension == "ttf" || strExtension == "font" || strExtension == "fontdef")
			strImage = "Font";
		else
		if (strExtension == "txt" || strExtension == "text")
			strImage = "Text";
		else
		if (strExtension == "xml")
			strImage = "XML";
		else
		if (strExtension == "mesh")
			strImage = "Mesh";
		else
		if (strExtension == "htm" || strExtension == "html")
			strImage = "HTML";
		else
			strImage = "Unknown";

		MyGUI::TreeControl::Node* pChild = new MyGUI::TreeControl::Node(strName, strImage);
		pChild->setPrepared(true);
		pNode->add(pChild);
	}
}

MyGUI::UString SampleLayout::getPath(MyGUI::TreeControl::Node* pNode) const
{
	if (!pNode || pNode == mpResourcesTree->getRoot())
	return MyGUI::UString();

	MyGUI::UString strPath;
	while (pNode->getParent() != mpResourcesTree->getRoot())
	{
		strPath = pNode->getText() + "/" + strPath;
		pNode = pNode->getParent();
	}

	return strPath;
}

namespace demo
{
    void DemoKeeper::createScene()
    {
		this->addResourceLocation("../../Media/UnitTests/UnitTest_TreeControl");

		MyGUI::FactoryManager& factory = MyGUI::FactoryManager::getInstance();
		factory.registryFactory<MyGUI::TreeControl>("Widget");
		factory.registryFactory<MyGUI::TreeControlItem>("Widget");

		mSampleLayout = new SampleLayout();
	}

    void DemoKeeper::destroyScene()
    {
    }
} // namespace demo

MYGUI_APP(demo::DemoKeeper)
