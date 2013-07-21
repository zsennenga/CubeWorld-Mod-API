#include <unordered_map>
#include <string>

#include "EntityHandler.h"

#ifndef Executor_H
#define Executor_H

using namespace std;

typedef void (*eventHandler)(EntityHandler);

enum eventTypes {
	test,
	NO_EVENT_TYPE
};

class Executor {
private:
	unordered_map<int,vector<eventHandler *>*> eventFunctions;
public:
	Executor::Executor()	{
		for (int i = 0; i < eventTypes::NO_EVENT_TYPE; i++)	{
			eventFunctions[i] = new vector<eventHandler *>;
		}
	}

	bool addEventHandler(int event, eventHandler * function)	{
		if (event >= eventTypes::NO_EVENT_TYPE)	return false;
		eventFunctions[event]->push_back(function);
		return true;
	}

	eventHandler * getEventHandlers(int handler)	{
		return *eventFunctions[handler]->data();
	}
};

#endif