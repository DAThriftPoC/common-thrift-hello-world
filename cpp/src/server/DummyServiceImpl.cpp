#include "DummyServiceImpl.h"
#include <vector>

DummyServiceHandler::DummyServiceHandler()
{
}

DummyServiceHandler::~DummyServiceHandler()
{
}

int32_t DummyServiceHandler::add(const int32_t a, const int32_t b)
{
	printf("add\n");
	return a + b;
}

void addPhone(std::vector<Phone>& phones,
	const std::string& num, PhoneType::type type)
{
	Phone phone;
	phone.phoneNumber = num;
	phone.type = type;
	phones.push_back(phone);
}

void DummyServiceHandler::getPerson(Person& _return, const std::string& id)
{
	printf("getPerson\n");
	PersonBasicInfo personBasicInfo;
	personBasicInfo.name = "Person " + id;
	personBasicInfo.age = 123;
	personBasicInfo.sex = Sex::Male;

	_return.id = id;
	_return.basicInfo = personBasicInfo;
	addPhone(_return.phones, "111", PhoneType::Home);
	addPhone(_return.phones, "222", PhoneType::Work);
	addPhone(_return.phones, "333", PhoneType::Mobile);
}

int32_t DummyServiceHandler::getPersonPhoneCount(const Person& person)
{
	printf("getPersonPhoneCount\n");
	return person.phones.size();
}
