#include <iostream>
#include "roster.h"
#include "student.h"

int main()
{
	int amountStudents = 5;

	const string studentData[] = {
	"A1,John,Smith,John1989@gm ail.com,20,30,35,40,SECURITY",
	"A2,Suzan,Erickson,Erickson_1990@gmailcom,19,50,30,40,NETWORK",
	"A3,Jack,Napoli,The_lawyer99yahoo.com,19,20,40,33,SOFTWARE",
	"A4,Erin,Black,Erin.black@comcast.net,22,50,58,40,SECURITY",
	"001473748,Chance,Crawford,ccra147@wgu.edu,28,7,15,30,SOFTWARE"
	};

	// required performance assessment information
	cout << "Scripting and Programming - Applications – C867" << endl;
	cout << "Programming Language Used: C++" << endl;
	cout << "Student ID: 001473748" << endl;
	cout << "Chance Crawford\n \n" << endl;

	cout << "Populating student roster...\n" << endl;
	// amountStudents can and should be something more dynamic than a static int
	Roster* studentRoster = new Roster(amountStudents);
	// iterate through data to parse and add to roster
	for (const auto& rowData : studentData) {
		studentRoster->parseThenAddRow(rowData);
	}

	studentRoster->printAll();
	cout << endl;

	cout << "Locating invalid emails...\n" << endl;
	studentRoster->printInvalidEmails();
	cout << endl;

	cout << "Calculating average course days for students...\n" << endl;
	for (int i = 0; i < amountStudents; i++) {
		studentRoster->printAvgDaysInCourse(studentRoster->retrieveStudent(i)->getStudentID());
	}
	cout << endl;

	cout << "Organizing roster by SOFTWARE degree...\n" << endl;
	studentRoster->printByDegreeProgram(DegreeProgram::SOFTWARE);
	cout << endl;

	cout << "Removing student A3 from roster...\n" << endl;
	studentRoster->remove("A3");
	cout << endl;

	cout << "Updating student roster...\n" << endl;
	studentRoster->printAll();
	cout << endl;

	cout << "Removing student A3 from roster...\n" << endl;
	// should print out error message after this attempt
	studentRoster->remove("A3");
	cout << endl;

	studentRoster->~Roster();

	return 0;
}