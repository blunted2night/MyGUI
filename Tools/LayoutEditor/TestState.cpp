/*!
	@file
	@author		Albert Semenov
	@date		08/2010
*/
#include "precompiled.h"
#include "TestState.h"
#include "CommandManager.h"
#include "StateManager.h"
#include "DialogManager.h"
#include "MessageBoxManager.h"

namespace tools
{

	TestState::TestState()
	{
		CommandManager::getInstance().registerCommand("Command_Quit", MyGUI::newDelegate(this, &TestState::commandQuit));
	}

	TestState::~TestState()
	{
	}

	void TestState::initState()
	{
	}

	void TestState::cleanupState()
	{
	}

	void TestState::pauseState()
	{
	}

	void TestState::resumeState()
	{
	}

	void TestState::commandQuit(const MyGUI::UString& _commandName)
	{
		if (!checkCommand())
			return;

		StateManager::getInstance().stateEvent(this, "Exit");
	}

	bool TestState::checkCommand()
	{
		if (DialogManager::getInstance().getAnyDialog())
			return false;

		if (MessageBoxManager::getInstance().hasAny())
			return false;

		if (!StateManager::getInstance().getStateActivate(this))
			return false;

		return true;
	}

} // namespace tools
