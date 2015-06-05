#include "Calculator.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/THttpTransport.h>
#include <thrift/transport/TSSLSocket.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

int main(int argc, char **argv) 
{
	boost::shared_ptr<TSSLSocketFactory> factory = boost::shared_ptr<TSSLSocketFactory>(new TSSLSocketFactory());
  factory->loadTrustedCertificates(std::string("../../keys/CA.pem").c_str());
	factory->authenticate(false);
  boost::shared_ptr<TSocket> socket = factory->createSocket("localhost", 9090);
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));

	shared_ptr<CalculatorClient> client(new CalculatorClient(protocol));
  transport->open();
  printf("%d\n", client->add(0xFF, 10));
  return 0;
}
