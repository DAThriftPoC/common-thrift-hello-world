package com.dataart.javathrifthelloworld;

import org.apache.thrift.TException;

import java.util.Arrays;
import java.util.List;

public class DummyServiceImpl implements DummyService.Iface {
    @Override
    public int add(int a, int b) throws TException {
        return a + b;
    }

    @Override
    public Person getPerson(String id) throws TException {
        PersonBasicInfo personBasicInfo = new PersonBasicInfo();
        personBasicInfo.setName(String.format("Person %s", id));
        personBasicInfo.setAge(123);
        personBasicInfo.setSex(Sex.Male);

        List<Phone> phones = Arrays.asList(
                phone(PhoneType.Home, "111"),
                phone(PhoneType.Work, "222"),
                phone(PhoneType.Mobile, "333"));

        Person person = new Person();
        person.setId(id);
        person.setBasicInfo(personBasicInfo);
        person.setPhones(phones);

        return person;
    }

    @Override
    public int getPersonPhoneCount(Person person) throws TException {
        return person.getPhones().size();
    }

    public static Phone phone(PhoneType phoneType, String phoneNumber) {
        Phone phone = new Phone();
        phone.setType(phoneType);
        phone.setPhoneNumber(phoneNumber);
        return phone;
    }
}
