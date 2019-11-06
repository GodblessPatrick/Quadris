#include "Model.h"
#include "NorandomCommand.h"
#include "QuadrisException.h"
#include <string>
#include <fstream>
using namespace std;

void NorandomCommand::execute(Model &model,const string &args) const
{
	ifstream file;
	vector<char> sequence;
	char c;
	file.open(args);
	if(!file){
		throw QuadrisException{"Given file cannot be opened!"};
	}
	while(file >> c){
		sequence.push_back(c);
	}
	model.setNoRandomSequence(move(sequence));
}
