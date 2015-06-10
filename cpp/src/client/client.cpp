#include <algorithm>
#include <string>

#include "Calculator.h"
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

int main(int argc, char **argv) 
{
	const std::string DEFAULT_TRANSPORT = "http";
	const std::string DEFAULT_PROTOCOL = "json";
	const int DEFAULT_PORT = 80;

	std::string host("192.168.197.161");
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
	
	shared_ptr<CalculatorClient> client(new CalculatorClient(protocol));
  transport->open();
  printf("%d\n", client->add(0xFF, 10));
  return 0;
}

