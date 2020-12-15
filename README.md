# Scripting and Programming - Applications – C867
C++ program made for the above course with WGU.

## Student.h and Student.cpp
Student object that has getters/setters for variables needed and a print function.

## Roster.h and Roster.cpp
Contains functions for displaying and altering data in the `studentRoster` array of pointers:
- printThenAddRow()
- isValidEmail()
- retrieveStudent()
- add()
- remove()
- printAll()
- printAvgDaysInCourse()
- printInvalidEmails()
- printByDegreeProgram()

## Degree.h
Houses the enum for the degrees: NETWORK, SECURITY, SOFTWARE.

## Main.cpp
Instantiates the `studentData` array, loops through this array to parse and add as Student objects to `studentRoster`. Afterwards, all of the various functions required for the performance assessment are performed.
