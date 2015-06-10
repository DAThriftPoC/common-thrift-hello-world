#include <algorithm>
#include <string>

#include "Calculator.h"
#include <thrift/server/TSimpleServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/THttpServer.h>
#include <thrift/transport/TServerSocket.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class CalculatorHandler : virtual public CalculatorIf {
 public:
  CalculatorHandler() {
    // Your initialization goes here
  }

  int32_t add(const int32_t a, const int32_t b) {
    // Your implementation goes here
    printf("add\n");
	return a + b;
  }

};

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char **argv)
{
	const std::string DEFAULT_TRANSPORT = "http";
	const std::string DEFAULT_PROTOCOL = "json";
	const int DEFAULT_PORT = 80;
	
	shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
	shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));
	std::string transportType("");
	std::string protocolType("");
	int port;

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
		if (std::string("--port").compare(argv[i]) == 0)
		{
			port = atoi(argv[i + 1]);
			portOptFound = true;
		}
		++i;
	}

	boost::shared_ptr<TServerSocket> serverSocket(new TServerSocket(port));

	boost::shared_ptr<TProtocolFactory> protocolFactory;
	if (protocolType.compare("json") == 0)
	{
		boost::shared_ptr<TProtocolFactory> jsonProtocolFactory(new TJSONProtocolFactory());
		protocolFactory = jsonProtocolFactory;
	}
	else if (protocolType.compare("compact") == 0)
	{
		boost::shared_ptr<TProtocolFactory> compactProtocolFactory(new TCompactProtocolFactory());
		protocolFactory = compactProtocolFactory;
	}
	else
	{
		boost::shared_ptr<TProtocolFactory> binaryProtocolFactory(new TBinaryProtocolFactoryT<TBufferBase>());
		protocolFactory = binaryProtocolFactory;
	}

	boost::shared_ptr<TTransportFactory> transportFactory;
	if (transportType.compare("http") == 0)
	{
		boost::shared_ptr<TTransportFactory> httpTransportFactory(new THttpServerTransportFactory());
		transportFactory = httpTransportFactory;
	}
	else if (transportType.compare("buffered") == 0)
	{
		boost::shared_ptr<TTransportFactory> bufferedTransportFactory(new TBufferedTransportFactory());
		transportFactory = bufferedTransportFactory;
	}

	TSimpleServer server(processor, serverSocket, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

