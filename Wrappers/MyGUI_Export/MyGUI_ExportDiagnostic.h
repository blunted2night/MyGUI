/*!
	@file
	@author		Albert Semenov
	@date		08/2012
*/

#ifndef __MYGUI_EXPORT_DIAGNOSTIC_H__
#define __MYGUI_EXPORT_DIAGNOSTIC_H__

#include "MyGUI_Prerequest.h"

#define MYGUI_PLATFORM_LOG_SECTION "Platform"
#define MYGUI_PLATFORM_LOG_FILENAME "MyGUI.log"
#define MYGUI_PLATFORM_LOG(level, text) MYGUI_LOGGING(MYGUI_PLATFORM_LOG_SECTION, level, text)

#define MYGUI_PLATFORM_EXCEPT(dest) \
{ \
	MYGUI_PLATFORM_LOG(Critical, dest); \
	MYGUI_DBG_BREAK;\
	std::ostringstream stream; \
	stream << dest << "\n"; \
	MYGUI_BASE_EXCEPT(stream.str().c_str(), "MyGUI"); \
}

#define MYGUI_PLATFORM_ASSERT(exp, dest) \
{ \
	if ( ! (exp) ) \
	{ \
		MYGUI_PLATFORM_LOG(Critical, dest); \
		MYGUI_DBG_BREAK;\
		std::ostringstream stream; \
		stream << dest << "\n"; \
		MYGUI_BASE_EXCEPT(stream.str().c_str(), "MyGUI"); \
	} \
}

#endif // __MYGUI_EXPORT_DIAGNOSTIC_H__
