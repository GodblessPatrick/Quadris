#ifndef OBSERVER_H
#define OBSERVER_H

class Model;

class Observer {
protected:
	Model const * const model;
public:
	Observer(Model const * const model);
	virtual void update() = 0;
	virtual ~Observer();
};

#endif
