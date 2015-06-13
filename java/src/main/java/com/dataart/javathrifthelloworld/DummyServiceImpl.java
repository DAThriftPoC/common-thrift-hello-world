package com.dataart.javathrifthelloworld;

import org.apache.thrift.TException;

import java.util.HashMap;
import java.util.Map;

public class DummyServiceImpl implements DummyService.Iface {
    private final Map<String, Person> people = new HashMap<String, Person>();

    @Override
    public void putPerson(Person person) throws TException {
        people.put(person.getId(), person);
    }

    @Override
    public Person getPerson(String id) throws PersonNotFoundException, TException {
        Person person = people.get(id);
        if(person == null) {
            String message = String.format("No person with id %s", id);
            throw new PersonNotFoundException(id, message);
        }

        return person;
    }

    @Override
    public int getPersonCount() throws TException {
        return people.size();
    }
}
