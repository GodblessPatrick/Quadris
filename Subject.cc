#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer *observer){
	observers.emplace_back(observer);	
}

void Subject::notifyObservers(){
	for (auto ob : observers){
		ob->update();
	}
}

Subject::~Subject() = default;
