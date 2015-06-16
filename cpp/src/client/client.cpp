#include <algorithm>
#include <string>

#include "DummyService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/THttpClient.h>
#include <thrift/transport/TSocket.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}

bool thereAreNoPeopleByDefault(shared_ptr<DummyServiceClient> client)
{
	return client->getPersonCount() == 0;
}

bool canCreateANewPerson(shared_ptr<DummyServiceClient> client)
{
	Person person;
	person.__set_id("person1");
	person.__set_name("John");
    person.__set_nickname("johnny");
	std::set<std::string> interests;
	interests.insert("java");
	interests.insert("c++");
	person.__set_interests(interests);
	std::vector<ContactMethod> methods;
	{
		ContactMethod method;
		PhoneContactMethod phone;
		phone.type = PhoneType::Home;
		phone.number = "111";
		method.phone = phone;
		methods.push_back(method);
	}
	{
		ContactMethod method;
		EmailContactMethod email;
		email.address = "11@11";
		method.email = email;
		methods.push_back(method);
	}
	person.__set_contactMethods(methods);
	std::map<std::string, std::string> extras;
	extras["age"] = "40";
	extras["style"] = "freestyler";
	person.__set_extras(extras);
	person.__set_sex(Sex::Female);
	client->putPerson(person);

	if (client->getPersonCount() != 1)
		return false;

	Person testPerson;
	client->getPerson(testPerson, "person1");
	std::map<std::string, std::string>::iterator age = testPerson.extras.find("age");
	std::map<std::string, std::string>::iterator style = testPerson.extras.find("style");
	if (("person1" != testPerson.id) ||
		("John" != testPerson.name) ||
        ("johnny" != testPerson.nickname) ||
		(2 != testPerson.interests.size()) ||
		(testPerson.interests.find("java") == testPerson.interests.end()) ||
		(testPerson.interests.find("c++") == testPerson.interests.end()) ||
		(2 != testPerson.contactMethods.size()) ||
		(PhoneType::Home != testPerson.contactMethods[0].phone.type) ||
		("111" != testPerson.contactMethods[0].phone.number) ||
		("11@11" != testPerson.contactMethods[1].email.address) ||
		(2 != testPerson.extras.size()) ||
		(age == testPerson.extras.end()) ||
		(age->second != "40") ||
		(style == testPerson.extras.end()) ||
		(style->second != "freestyler") ||
		(Sex::Female != testPerson.sex))
			return false;
	return true;
}

bool canCreateANewPersonWhenOptionalFieldAreNotSet(shared_ptr<DummyServiceClient> client)
{
	Person person;
	person.__set_id("person1");
	person.__set_name("John");
	client->putPerson(person);
	return (1 == client->getPersonCount());
}

bool canCreateANewPersonWithDefaults(shared_ptr<DummyServiceClient> client)
{
	{
		Person person;
		person.__set_id("person1");
		person.__set_name("John");
		client->putPerson(person);
	}

	Person person;
	client->getPerson(person, "person1");
	return (Sex::Male == person.sex);
}

bool canUpdateAnExistingPerson(shared_ptr<DummyServiceClient> client)
{
	{
		Person person;
		person.__set_id("person1");
		person.__set_name("John");
		client->putPerson(person);
	}

	{
		Person person;
		person.__set_id("person1");
		person.__set_name("John2");
		client->putPerson(person);
	}

	return (1 == client->getPersonCount());
}

bool cantGetAPersonThatDoesNotExist(shared_ptr<DummyServiceClient> client)
{
	try
	{
		Person person;
		client->getPerson(person, "111");
		return false;
	}
	catch (PersonNotFoundException e)
	{
		return ("111" == e.requestedId) && (e.errorMessage.compare("No person with id 111") == 0);
	}
}

int main(int argc, char **argv) 
{
	const std::string DEFAULT_TRANSPORT = "http";
	const std::string DEFAULT_PROTOCOL = "json";
	const int DEFAULT_PORT = 80;

	std::string host/*("localhost");*/("192.168.197.161");
	int port;
	std::string transportType("");
	std::string protocolType("");

	if (cmdOptionExists(argv, argv + argc, "--json"))
		protocolType = "json";
	else if (cmdOptionExists(argv, argv + argc, "--compact"))
		protocolType = "compact";
	else if (cmdOptionExists(argv, argv + argc, "--binary"))
		protocolType = "binary";
	else
		protocolType = DEFAULT_PROTOCOL;

	if (cmdOptionExists(argv, argv + argc, "--http"))
	{
		transportType = "http";
		port = 80;
	}
	else if (cmdOptionExists(argv, argv + argc, "--buffered"))
	{
		transportType = "buffered";
		port = 9090;
	}
	else
	{
		transportType = DEFAULT_TRANSPORT;
		port = DEFAULT_PORT;
	}

	int i = 1;
	std::string portOpt("--port");
	bool portOptFound = false;
	while ((i < argc - 1) && !(portOptFound))
	{
		if (portOpt.compare(argv[i]) == 0)
		{
			port = atoi(argv[i + 1]);
			portOptFound = true;
		}
		++i;
	}

	boost::shared_ptr<TSocket> socket;
	socket = boost::shared_ptr<TSocket>(new TSocket(host, port));

	boost::shared_ptr<TTransport> transport;
	if (transportType.compare("http") == 0)
	{
		boost::shared_ptr<TTransport> httpSocket(new THttpClient(socket, host, "/"));
		transport = httpSocket;
	}
	else if (transportType.compare("buffered") == 0)
	{
		boost::shared_ptr<TBufferedTransport> bufferedSocket(new TBufferedTransport(socket));
		transport = bufferedSocket;
	}

	boost::shared_ptr<TProtocol> protocol;
	if (protocolType.compare("json") == 0)
	{
		boost::shared_ptr<TProtocol> jsonProtocol(new TJSONProtocol(transport));
		protocol = jsonProtocol;
	}
	else if (protocolType.compare("compact") == 0)
	{
		boost::shared_ptr<TProtocol> compactProtocol(new TCompactProtocol(transport));
		protocol = compactProtocol;
	}
	else
	{
		boost::shared_ptr<TBinaryProtocol> binaryProtocol(new TBinaryProtocol(transport));
		protocol = binaryProtocol;
	}

	shared_ptr<DummyServiceClient> client(new DummyServiceClient(protocol));
	transport->open();
	if (thereAreNoPeopleByDefault(client) &&
		canCreateANewPerson(client) &&
		canCreateANewPersonWhenOptionalFieldAreNotSet(client) &&
		canCreateANewPersonWithDefaults(client) &&
		canUpdateAnExistingPerson(client) &&
		cantGetAPersonThatDoesNotExist(client))
	{
		printf("Test is passed");
	}
	else
		printf("Test is failed");
	return 0;
}

