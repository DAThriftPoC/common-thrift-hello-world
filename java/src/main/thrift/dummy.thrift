namespace java com.dataart.javathrifthelloworld

typedef string Id

enum PhoneType {
    Home
    Work
}

struct PhoneContactMethod {
    1: PhoneType type
    2: string number
}

struct EmailContactMethod {
    1: string address
}

union ContactMethod {
    1: PhoneContactMethod phone
    2: EmailContactMethod email
}

enum Sex {
    Male
    Female
}

struct Person {
    1: required Id id
    2: required string name
    3: optional string nickname
    4: optional set<string> interests
    5: optional list<ContactMethod> contactMethods
    6: optional map<string, string> extras
    7: optional Sex sex = Sex.Male
}

exception PersonNotFoundException {
    1: required Id requestedId
    2: required string errorMessage
}

service DummyService {
    void putPerson(1: Person person)
    Person getPerson(1: Id id) throws (1: PersonNotFoundException e)
    i32 getPersonCount()
}
