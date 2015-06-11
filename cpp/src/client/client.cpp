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

void addPhone(std::vector<Phone>& phones,
	const std::string& num, PhoneType::type type)
{
	Phone phone;
	phone.phoneNumber = num;
	phone.type = type;
	phones.push_back(phone);
}

bool runTest(shared_ptr<DummyServiceClient> client)
{
	int result = client->add(2, 3);
	if (result != 5)
		return false;

	Person person;
	client->getPerson(person, "11");
	if (("11" != person.id) ||
		("Person 11" != person.basicInfo.name) ||
		(123 != person.basicInfo.age) ||
		(Sex::Male != person.basicInfo.sex) ||
		(3 != person.phones.size()) ||
		(PhoneType::Home != person.phones[0].type) ||
		("111" != person.phones[0].phoneNumber) ||
		(PhoneType::Work != person.phones[1].type) ||
		("222" != person.phones[1].phoneNumber) ||
		(PhoneType::Mobile != person.phones[2].type) ||
		("333" != person.phones[2].phoneNumber))
			return false;

	Person person2;
	addPhone(person2.phones, "121212", PhoneType::Home);
	addPhone(person2.phones, "232323", PhoneType::Work);
	int phoneCount = client->getPersonPhoneCount(person2);
	if (phoneCount != 2)
		return false;

	return true;
}

int main(int argc, char **argv) 
{
	const std::string DEFAULT_TRANSPORT = "http";
	const std::string DEFAULT_PROTOCOL = "json";
	const int DEFAULT_PORT = 80;

	std::string host("localhost");//("192.168.197.161");
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
	if (runTest(client))
		printf("Test is passed");
	else
		printf("Test is failed");
	return 0;
}

