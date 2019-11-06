#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <map>
#include <memory>
#include <string>
class Command;
class Model;

class CommandInterpreter {
	std::map<std::string, std::unique_ptr<Command>> commands;
	bool prefix(const std::string &longer, const std::string &shorter) const;
public:
	CommandInterpreter();
	void registerCommand(std::string &&commandName, std::unique_ptr<Command> &&command);
	const std::unique_ptr<const Command> getCommand(const std::string &commandNname, const Model &model) const;
};

#endif
