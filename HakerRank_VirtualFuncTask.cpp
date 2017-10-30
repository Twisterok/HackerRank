#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#include <string>
#include <memory>
#include <numeric>

class Person
{
public:
    Person() :
        age(0)
    {}

    virtual ~Person() {}

    const string& GetName() const { return name; }
    int           GetAge() const { return age; }    

    virtual void getdata() = 0;
    virtual void putdata() const = 0;

protected:
    string  name;
    int     age;
};

class Professor : public Person
{
public:
    Professor() :
        Person(),
        publicationsCount(0),
        id(0)
    {
        id = nextProfessorId++;
    }

    virtual ~Professor() {}
    
    int GetId() const { return id; }

    virtual void getdata() override
    {
        cin >> name;
        cin >> age;
        cin >> publicationsCount;
    }

    virtual void putdata() const override
    {
        cout << GetName() << " "
             << GetAge() << " "
             << GetPublicationsCount() << " "
             << GetId() << endl;
    }

    int GetPublicationsCount() const { return publicationsCount; }    

private:
    int publicationsCount;    
    int id;
    static  int nextProfessorId;
};
int Professor::nextProfessorId = 1;

namespace
{
    const int kMarksCount = 6;
}

class Student : public Person
{
public:

    Student() :
        Person(),
        id(0)
    {
        id = nextStudentId++;
    }

    int GetMarksSum() const
    {
        return std::accumulate(marks.begin(), marks.end(), 0);
    }

    int GetId() const { return id; }

    virtual void getdata() override
    {
        cin >> name;
        cin >> age;
        for (int i = 0; i < kMarksCount; ++i)
        {
            int mark = 0;
            cin >> mark;
            marks.push_back(mark);
        }
    }

    virtual void putdata() const override
    {
        cout << GetName() << " "
             << GetAge() << " "
             << GetMarksSum() << " "
             << GetId() << endl;
    }

private:
    std::vector<int> marks;
    int id;
    static  int nextStudentId;
};

int Student::nextStudentId = 1;


namespace PersonFactory
{
    std::unique_ptr<Person> CreatePerson(int personType)
    {
        switch (personType)
        {
        case 1:
            return std::unique_ptr<Person>(new Professor());
        case 2:
            return std::unique_ptr<Person>(new Student());
        }
        return nullptr;
    }
}

/*int main()
{
    int personsCount = 0;
    cin >> personsCount;

    std::vector<std::unique_ptr<Person>> persons;
    for (int i = 0; i < personsCount; ++i)
    {
        int personType;
        cin >> personType;
        auto person = PersonFactory::CreatePerson(personType);
        if (!person)
            continue;

        person->getdata();
        persons.push_back(std::move(person));
    }
    
    for (const auto& person : persons)
        person->putdata();

    return 0;
}*/