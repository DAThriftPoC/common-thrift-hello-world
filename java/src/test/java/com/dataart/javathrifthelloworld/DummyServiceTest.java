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

import static com.dataart.javathrifthelloworld.DummyServiceImpl.phone;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

public class DummyServiceTest {
    private final static int PORT = 2302;

    private TServer server;
    private Thread serverThread;

    @Before
    public void startServer() throws InterruptedException, TTransportException {
        DummyServiceImpl calculator = new DummyServiceImpl();
        final DummyService.Processor calculatorProcessor = new DummyService.Processor(calculator);
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
    public void canAddNumbers() throws InterruptedException, TException {
        TTransport transport = new TSocket("localhost", PORT);
        transport.open();

        TProtocol protocol = new TBinaryProtocol(transport);
        DummyService.Client client = new DummyService.Client(protocol);

        try {
            int result = client.add(2, 3);
            assertEquals(5, result);
        } finally {
            transport.close();
        }
    }

    @Test
    public void canGetPerson() throws TException {
        TTransport transport = new TSocket("localhost", PORT);
        transport.open();

        TProtocol protocol = new TBinaryProtocol(transport);
        DummyService.Client client = new DummyService.Client(protocol);

        try {
            Person person = client.getPerson("11");

            assertNotNull(person);
            assertEquals("11", person.getId());
            assertEquals("Person 11", person.getBasicInfo().getName());
            assertEquals(123, person.getBasicInfo().getAge());
            assertEquals(Sex.Male, person.getBasicInfo().getSex());
            assertEquals(3, person.getPhonesSize());
            assertEquals(PhoneType.Home, person.getPhones().get(0).getType());
            assertEquals("111", person.getPhones().get(0).getPhoneNumber());
            assertEquals(PhoneType.Work, person.getPhones().get(1).getType());
            assertEquals("222", person.getPhones().get(1).getPhoneNumber());
            assertEquals(PhoneType.Mobile, person.getPhones().get(2).getType());
            assertEquals("333", person.getPhones().get(2).getPhoneNumber());
        } finally {
            transport.close();
        }
    }

    @Test
    public void canGetPersonPhoneCount() throws TException {
        TTransport transport = new TSocket("localhost", PORT);
        transport.open();

        TProtocol protocol = new TBinaryProtocol(transport);
        DummyService.Client client = new DummyService.Client(protocol);

        try {
            Person person = new Person();
            person.addToPhones(phone(PhoneType.Home, "121212"));
            person.addToPhones(phone(PhoneType.Work, "232323"));

            int phoneCount = client.getPersonPhoneCount(person);
            assertEquals(2, phoneCount);
        } finally {
            transport.close();
        }
    }
}
