#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Model.h"
#include "CommandInterpreter.h"
#include "Command.h"
#include "TextView.h"
#include "GraphicsView.h"
#include "QuadrisException.h"

using namespace std;

void executeCommand(const CommandInterpreter &interpreter, string &commandName, Model &model){

	// extract args
	size_t firstSpaceId = commandName.find(" ");
	string args;
	// if there is no space or the last character is space
	// then no args is provided, so the string commandName is the real command name
	if (firstSpaceId == string::npos || firstSpaceId == commandName.size() - 1) args = "";
	else{
		args = commandName.substr(firstSpaceId + 1);
		commandName = commandName.substr(0, firstSpaceId);
	}

	if (commandName == "sequence"){

		ifstream f{args};
		if (f.is_open()){
			while (getline(f, commandName)) executeCommand(interpreter, commandName, model);
		}
		else cout << "invalid file" << endl;
	}
	// only execute the command when commandName is not sequence
	else{

		// before executing any command, clear the hint block first
		model.clearHint();

		try { interpreter.getCommand(commandName, model)->execute(model, args); }
		catch (const QuadrisException &ex){	cout << ex.what() << endl; }
		// update UI no matter an exception has been thrown or not
		model.notifyObservers();
	}
}

void gameover(Model &model){

	string choice;
	getline(cin, choice);

	if (choice == "y"){
		model.restartGame();
		// update UI
		model.notifyObservers();
	}
	else if (choice == "n"){
		exit(0);
	}
	else {
		cout << "Please press y or n" << endl;
		gameover(model);
	}
}

int main(int argc, char** argv){

	string fileName = "sequence.txt";
	unsigned int startLevel = 0;
	int seed = 0;
	bool textOnly = false;

	// extract command line arguments
	// (no error checking)
	for (int i=0;i<argc;++i){
		string arg = argv[i];
		if (arg.size() > 0 && arg[0] == '-'){
			arg = arg.substr(1);
			if (arg == "text") textOnly = true;
			else if (arg == "seed"){
				istringstream iss{argv[++i]};
				iss >> seed;
			}
			else if (arg == "scriptfile") fileName = argv[++i];
			else if (arg == "startlevel"){
				istringstream iss{argv[++i]};
				iss >> startLevel;
			}
		}
	}

	// assume that the fileName is valid
	ifstream file{fileName};
	vector<char> sequence;
	char c;
	while (file >> c) sequence.emplace_back(c);

	Model model(move(sequence), startLevel, seed);

	// kind of controller
	CommandInterpreter interpreter;

	TextView textView{&model};
	model.attach(&textView);

	unique_ptr<GraphicsView> graphicsView;
	if (!textOnly){
		// only heap allocated a GraphicsView object when needed
		graphicsView = make_unique<GraphicsView>(&model);
		model.attach(graphicsView.get());
	}

	// display UI
	model.notifyObservers();

	string commandName;
	while (getline(cin, commandName)){
		executeCommand(interpreter, commandName, model);	
		if (model.isGameover()){
			cout << "Press y to restart, n to exit" << endl;
			gameover(model);
		}
	}
}
