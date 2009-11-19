/*!
	@file
	@author		Albert Semenov
	@date		11/2009
	@module
*/

#ifndef __RESOURCE_W32_POINTER_H__
#define __RESOURCE_W32_POINTER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_IResource.h"

namespace demo
{

	class ResourceW32Pointer :
		public MyGUI::IResource
	{
		MYGUI_RTTI_DERIVED( ResourceW32Pointer );

	public:
		ResourceW32Pointer();
		virtual ~ResourceW32Pointer() { }

		virtual void deserialization(MyGUI::xml::ElementPtr _node, MyGUI::Version _version);

		std::string getPointer() { return mPointer; }

	private:
		std::string mPointer;
	};

}

#endif // __RESOURCE_W32_POINTER_H__
