//STUDENT.CPP
#include <string>
#include "Student.hpp"


Student::Student(){}

Student::Student(std::string name, std::string ID)
	:name{name}, ID{ID}
{
}

void Student::setName(std::string name)
{
    this->name = name;
}

void Student::setID(std::string ID)
{
    this->ID = ID;
}

std::string Student::getName()
{
    return this->name;
}

std::string Student::getID()
{
    return this->ID;
}
