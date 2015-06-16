#include "DummyServiceImpl.h"
#include <map>

DummyServiceHandler::DummyServiceHandler()
{
}

DummyServiceHandler::~DummyServiceHandler()
{
}

void DummyServiceHandler::putPerson(const Person& person)
{
	printf("putPerson\n");
	people[person.id] = person;
}

void DummyServiceHandler::getPerson(Person& _return, const std::string& id)
{
	printf("getPerson\n");
	std::map<std::string, Person>::iterator it  = people.find(id);
	if (it == people.end())
	{
		PersonNotFoundException e;
		e.requestedId = id;
		e.errorMessage = "No person with id " + id;
		throw e;
	}
	else
		_return = it->second;
}

int32_t DummyServiceHandler::getPersonCount()
{
	printf("getPersonCount\n");
	return people.size();
}

