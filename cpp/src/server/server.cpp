#include "Calculator.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSSLSocket.h>
#include "TSSLServerSocket.h"


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

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
  shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));
  
  shared_ptr<TSSLSocketFactory> sslSocketFactory(new TSSLSocketFactory());
  sslSocketFactory->loadCertificate(std::string("../../keys/server.crt").c_str());
  sslSocketFactory->loadPrivateKey(std::string("../../keys/server.key").c_str());
  shared_ptr<TServerSocket> serverSocket(new TSSLServerSocket(port, sslSocketFactory));

  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverSocket, transportFactory, protocolFactory);
	server.serve();
  return 0;
}
