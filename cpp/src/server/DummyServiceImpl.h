#ifndef DUMMY_SERVICE_IMPL_H
#define DUMMY_SERVICE_IMPL_H

#include "DummyService.h"
#include <vector>

class DummyServiceHandler : virtual public DummyServiceIf
{
public:
	DummyServiceHandler();
	virtual ~DummyServiceHandler();
	void putPerson(const Person& person);
	void getPerson(Person& _return, const std::string& id);
	int32_t getPersonCount();

private:
	std::map<std::string, Person> people;
};

#endif // DUMMY_SERVICE_IMPL_H
