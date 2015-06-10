package com.dataart.javathrifthelloworld;

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.*;

public class App {
    public static void main(String[] args) throws InterruptedException, TTransportException {
        DummyServiceImpl calculator = new DummyServiceImpl();
        final DummyService.Processor calculatorProcessor = new DummyService.Processor(calculator);
        TServerTransport serverTransport = new TServerSocket(2302);
        final TServer server = new TSimpleServer(new TServer.Args(serverTransport).processor(calculatorProcessor));

        Thread serverThread = new Thread(new Runnable() {
            @Override
            public void run() {
                server.serve();
            }
        });
        serverThread.start();

        Thread.sleep(1000); // how do I reliably determine if it's ready?

        TTransport transport = new TSocket("localhost", 2302);
        transport.open();

        TProtocol protocol = new TBinaryProtocol(transport);
        DummyService.Client client = new DummyService.Client(protocol);

        try {
            int result = client.add(2, 3);
            System.out.printf("the result is %d\n", result);
        } catch (TException e) {
            e.printStackTrace();
        } finally {
            transport.close();
        }

        server.stop();
        serverThread.join();
    }
}
