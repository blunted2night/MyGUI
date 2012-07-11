/*!
	@file
	@author		Albert Semenov
	@date		07/2012
*/
#ifndef _992be787_40d0_4bde_8e4c_db4ba7a18854_
#define _992be787_40d0_4bde_8e4c_db4ba7a18854_

#include "Command.h"
#include <string>
#include "Data.h"

namespace tools
{
	class CommandCreateData :
		public Command
	{
	public:
		CommandCreateData();
		virtual ~CommandCreateData();

		virtual void doCommand();
		virtual void undoCommand();

		void setName(const std::string& _value);

	private:
		std::string mName;
		Data* mData;
	};
}

#endif
