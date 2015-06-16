// expmain.cpp
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the code in the "core" directory or with any additional libraries
// that are part of the project, outside of the context of the main
// application or Google Test.
#include <sstream>
#include <string>
#include <iostream>
#include "ArrayList.hpp"
#include "Student.hpp"

using namespace std;




void gatherInput(ArrayList<Student>& studentList, const int SIZE){
    cout << "Enter a new student in the following format (ID Name): " << endl;
   
   for (int i = 0; i < SIZE; i++)
    {
         string input;
         cout << "Student " + to_string(i+1) + ": "; 
         getline(cin, input);

         size_t position = input.find(" ");
         Student s(input.substr(position + 1), input.substr(0, position));
         studentList.add(s);
     }

}


int main()
{
    const int ARRAY_CAP = 10;
   
   ArrayList<Student> students;
   gatherInput(students, ARRAY_CAP);


   for (int i = 0; i < ARRAY_CAP; i++)
   {
      cout << students.at(i).getName() << " (#ID" << students.at(i).getID() << ")" << endl;
   } 
    
    return 0;
}

