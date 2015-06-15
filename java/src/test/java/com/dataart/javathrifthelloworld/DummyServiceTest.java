package com.dataart.javathrifthelloworld;

import org.apache.thrift.TException;
import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.protocol.TProtocolException;
import org.apache.thrift.server.TServer;
import org.apache.thrift.server.TSimpleServer;
import org.apache.thrift.transport.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

import static org.junit.Assert.*;

public class DummyServiceTest {
    private final static int PORT = 2302;

    private TServer server;
    private Thread serverThread;
    private TTransport transport;
    private DummyService.Client client;

    @Before
    public void startServer() throws InterruptedException, TTransportException {
        DummyServiceImpl dummyService = new DummyServiceImpl();
        final DummyService.Processor dummyServiceProcessor = new DummyService.Processor(dummyService);
        TServerTransport serverTransport = new TServerSocket(PORT);
        server = new TSimpleServer(new TServer.Args(serverTransport).processor(dummyServiceProcessor));

        serverThread = new Thread(new Runnable() {
            @Override
            public void run() {
                server.serve();
            }
        });
        serverThread.start();

        Thread.sleep(1000); // how do I reliably determine if it's ready?

        transport = new TSocket("localhost", PORT);
        transport.open();

        TProtocol protocol = new TBinaryProtocol(transport);
        client = new DummyService.Client(protocol);
    }

    @After
    public void stopServer() throws InterruptedException {
        client = null;

        transport.close();
        transport = null;

        server.stop();
        server = null;

        serverThread.join();
        serverThread = null;
    }

    @Test
    public void thereAreNoPeopleByDefault() throws TException {
        assertEquals(0, client.getPersonCount());
    }

    @Test
    public void canCreateANewPerson() throws TException {
        Person person = new Person();
        person.setId("person1");
        person.setName("John");
        person.setNickname("johnny");
        person.setInterests(new HashSet<>(Arrays.asList("java", "c++")));
        person.setContactMethods(Arrays.asList(
                new ContactMethod(
                        ContactMethod._Fields.PHONE,
                        new PhoneContactMethod(PhoneType.Home, "111")),
                new ContactMethod(
                        ContactMethod._Fields.EMAIL,
                        new EmailContactMethod("11@11"))));
        person.setExtras(new HashMap<String, String>() {{
            put("age", "40");
            put("style", "freestyler");
        }});
        person.setSex(Sex.Female);
        client.putPerson(person);

        assertEquals(1, client.getPersonCount());

        person = client.getPerson("person1");
        assertEquals("person1", person.getId());
        assertEquals("John", person.getName());
        assertEquals("johnny", person.getNickname());
        assertEquals(2, person.getInterestsSize());
        assertTrue(person.getInterests().contains("java"));
        assertTrue(person.getInterests().contains("c++"));
        assertEquals(2, person.getContactMethodsSize());
        assertEquals(ContactMethod._Fields.PHONE, person.getContactMethods().get(0).getSetField());
        assertEquals(PhoneType.Home, person.getContactMethods().get(0).getPhone().getType());
        assertEquals("111", person.getContactMethods().get(0).getPhone().getNumber());
        assertEquals(ContactMethod._Fields.EMAIL, person.getContactMethods().get(1).getSetField());
        assertEquals("11@11", person.getContactMethods().get(1).getEmail().getAddress());
        assertEquals(2, person.getExtrasSize());
        assertEquals("40", person.getExtras().get("age"));
        assertEquals("freestyler", person.getExtras().get("style"));
        assertEquals(Sex.Female, person.getSex());
    }

    @Test
    public void canCreateANewPersonWhenOptionalFieldAreNotSet() throws TException {
        Person person = new Person();
        person.setId("person1");
        person.setName("John");
        client.putPerson(person);

        assertEquals(1, client.getPersonCount());
    }

    @Test
    public void canCreateANewPersonWithDefaults() throws TException {
        {
            Person person = new Person();
            person.setId("person1");
            person.setName("John");
            client.putPerson(person);
        }

        Person person = client.getPerson("person1");
        assertEquals(Sex.Male, person.getSex());
    }

    @Test
    public void cantCreateANewPersonWhenRequiredFieldIsNotSet() throws TException {
        Person person = new Person();
        person.setId("person1");

        try {
            client.putPerson(person);
        } catch (TProtocolException e) {
            assertTrue(e.getMessage().contains("Required field"));
            assertTrue(e.getMessage().contains("'name'"));
        }
    }

    @Test
    public void canUpdateAnExistingPerson() throws TException {
        {
            Person person = new Person();
            person.setId("person1");
            person.setName("John");
            client.putPerson(person);
        }

        {
            Person person = new Person();
            person.setId("person1");
            person.setName("John2");
            client.putPerson(person);
        }

        assertEquals(1, client.getPersonCount());
    }

    @Test
    public void cantGetAPersonThatDoesNotExist() throws TException {
        try {
            client.getPerson("111");
            fail();
        } catch (PersonNotFoundException e) {
            assertEquals("111", e.getRequestedId());
            assertEquals("No person with id 111", e.getErrorMessage());
        }
    }
}
