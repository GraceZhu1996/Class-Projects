//STUDENT.HPP

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
class Student
{
public:
   Student();
   Student(std::string name, std::string ID);
   void setName(std::string name);
   void setID(std::string ID);
   std::string getName();
   std::string getID();

private:
    std::string name;
    std::string ID;
};

#endif //STUDENT.HPP
