namespace java com.dataart.javathrifthelloworld

enum Sex {
    Male = 1,
    Female = 2,
    NoIdea = 3
}

struct PersonBasicInfo {
    1:string name,
    2:i32 age,
    3:Sex sex
}

enum PhoneType {
    Home = 1,
    Work = 2,
    Mobile = 3
}

struct Phone {
    1:string phoneNumber,
    2:PhoneType type
}

struct Person {
    1:string id,
    2:PersonBasicInfo basicInfo,
    3:list<Phone> phones,
}

service DummyService {
    i32 add(1:i32 a, 2:i32 b)

    Person getPerson(1:string id)
    i32 getPersonPhoneCount(1:Person person)
}
