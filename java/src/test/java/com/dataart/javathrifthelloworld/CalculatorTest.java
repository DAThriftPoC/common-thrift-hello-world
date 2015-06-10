package com.dataart.javathrifthelloworld;

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CalculatorTest {
    private final static int PORT = 2302;

    private TServer server;
    private Thread serverThread;

    @Before
    public void startServer() throws InterruptedException, TTransportException {
        CalculatorImpl calculator = new CalculatorImpl();
        final Calculator.Processor calculatorProcessor = new Calculator.Processor(calculator);
        TServerTransport serverTransport = new TServerSocket(PORT);
        server = new TSimpleServer(new TServer.Args(serverTransport).processor(calculatorProcessor));

        serverThread = new Thread(new Runnable() {
            @Override
            public void run() {
                server.serve();
            }
        });
        serverThread.start();

        Thread.sleep(1000); // how do I reliably determine if it's ready?
    }

    @After
    public void stopServer() throws InterruptedException {
        server.stop();
        server = null;

        serverThread.join();
        serverThread = null;
    }

    @Test
    public void dummy() throws InterruptedException, TTransportException {
        TTransport transport = new TSocket("localhost", PORT);
        transport.open();

        TProtocol protocol = new TBinaryProtocol(transport);
        Calculator.Client client = new Calculator.Client(protocol);

        try {
            int result = client.add(2, 3);
            assertEquals(5, result);
        } catch (TException e) {
            e.printStackTrace();
        } finally {
            transport.close();
        }
    }
}
