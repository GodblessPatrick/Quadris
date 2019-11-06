#include "CommandInterpreter.h"
#include "QuadrisException.h"
#include "Model.h"
#include "Block.h"
#include "Command.h"
#include "CompositeCommand.h"

#include "MoveCommand.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "DownCommand.h"
#include "ClockwiseCommand.h"
#include "CounterClockwiseCommand.h"

#include "DropCommand.h"

#include "LevelUpCommand.h"
#include "LevelDownCommand.h"

#include "RandomCommand.h"
#include "NoRandomCommand.h"

#include "ICommand.h"
#include "JCommand.h"
#include "LCommand.h"
#include "OCommand.h"
#include "SCommand.h"
#include "ZCommand.h"
#include "TCommand.h"

#include "RestartCommand.h"
#include "HintCommand.h"

#include <cctype>  // isdigit()
#include <sstream>

using namespace std;

bool CommandInterpreter::prefix(const string &longer, const string &shorter) const
{
	if (longer.substr(0, shorter.size()) == shorter) return true;
	return false;
}

CommandInterpreter::CommandInterpreter(){

	registerCommand("left", make_unique<LeftCommand>());
	registerCommand("right", make_unique<RightCommand>());
	registerCommand("down", make_unique<DownCommand>());
	registerCommand("clockwise", make_unique<ClockwiseCommand>());
	registerCommand("counterclockwise", make_unique<CounterClockwiseCommand>());
	
	registerCommand("drop", make_unique<DropCommand>());

	registerCommand("levelup", make_unique<LevelUpCommand>());
	registerCommand("leveldown", make_unique<LevelDownCommand>());

	registerCommand("random", make_unique<RandomCommand>());
	registerCommand("norandom", make_unique<NoRandomCommand>());

	registerCommand("I", make_unique<ICommand>());
	registerCommand("J", make_unique<JCommand>());
	registerCommand("L", make_unique<LCommand>());
	registerCommand("O", make_unique<OCommand>());
	registerCommand("S", make_unique<SCommand>());
	registerCommand("Z", make_unique<ZCommand>());
	registerCommand("T", make_unique<TCommand>());

	registerCommand("restart", make_unique<RestartCommand>());
	registerCommand("hint", make_unique<HintCommand>());

	// register other commands
}

void CommandInterpreter::registerCommand(string &&commandName, unique_ptr<Command> &&command){
	commands.insert(make_pair(move(commandName), move(command)));
}

const unique_ptr<const Command> CommandInterpreter::getCommand(const string &commandName, const Model &model) const
{
	// try to extract the multiplier
	int multiplier = 1;
	string requestCommandName;
	for (size_t i=0;i<commandName.size();++i){
		if (!isdigit(commandName[i])){
			// the provided parameter consists of only non-digit characters
			if (i == 0){
				requestCommandName = commandName;
			}
			else{
				// multiplier part
				string tmp = commandName.substr(0, i - 0);
				stringstream ss{tmp};
				ss >> multiplier;

				// real command part
				requestCommandName = commandName.substr(i);
			}
			break;
		}
	}

	// get the requested command
	Command *command_ptr;
	bool find = false;
	for (const auto &pair : commands){
		const string &curCommandName = pair.first;
		if (curCommandName >= requestCommandName && prefix(curCommandName, requestCommandName)){
			// the provided command name is matched with more than one command
			if (find){
				throw QuadrisException{commandName + " is not a valid command name."};
			}
			command_ptr = pair.second.get();
			find = true;
		}
	}

	if (!find) throw QuadrisException{commandName + " is not a valid command name."};

	auto res = make_unique<CompositeCommand>();

	// multiplier has no effect on restart, hint, random, norandom
	// can't directly check requestCommandName
	// because it may be a shortcut
	if (dynamic_cast<RestartCommand*>(command_ptr) ||
	    dynamic_cast<HintCommand*>(command_ptr) ||
		dynamic_cast<RandomCommand*>(command_ptr) ||
		dynamic_cast<NoRandomCommand*>(command_ptr))
	{
		multiplier = 1;		
	}

	for (int i=0;i<multiplier;++i){
		res->add(command_ptr);
	}
	
	if (multiplier > 0 && dynamic_cast<MoveCommand*>(command_ptr)){
		// since map[] returns a reference
		// so we must use find() in a const method
		if (model.getUndroppedBlock().isHeavy()) res->add(commands.find("down")->second.get());
	}

	// if multiplier == 0, then res will contain nothing
	return move(res);
}
