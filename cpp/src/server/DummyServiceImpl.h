#ifndef DUMMY_SERVICE_IMPL_H
#define DUMMY_SERVICE_IMPL_H

#include "DummyService.h"

class DummyServiceHandler : virtual public DummyServiceIf
{
public:
	DummyServiceHandler();
	virtual ~DummyServiceHandler();
	int32_t add(const int32_t a, const int32_t b);
	void getPerson(Person& _return, const std::string& id);
	int32_t getPersonPhoneCount(const Person& person);	
};

#endif // DUMMY_SERVICE_IMPL_H
