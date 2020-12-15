#pragma once
#include <iostream>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include "roster.h"
#include "student.h"

using namespace std;

// default constructor
Roster::Roster() {
	this->rosterSize = 0;
	this->rosterIndex = -1;
	this->classRosterArray = nullptr;
};
// overloaded constructor
Roster::Roster(int rosterSize) {
	this->rosterSize = rosterSize;
	this->rosterIndex = -1;
	this->classRosterArray = new Student * [rosterSize];
};
// destructor
Roster::~Roster() {};

void Roster::parseThenAddRow(string row) {
	// opted to parse string into vector here for easier separation, more readable code,
	// and straight-forward variable assignment
	vector<string> rowData;
	stringstream rowStream(row);
	while (rowStream.good()) {
		string substr;
		getline(rowStream, substr, ',');
		rowData.push_back(substr);
	}

	// assign and convert from string to int where needed
	string studentIDTemp = rowData.at(0);
	string firstNameTemp = rowData.at(1);
	string lastNameTemp = rowData.at(2);
	string emailAddressTemp = rowData.at(3);
	int ageTemp = stoi(rowData.at(4));
	int courseDays1Temp = stoi(rowData.at(5));
	int courseDays2Temp = stoi(rowData.at(6));
	int courseDays3Temp = stoi(rowData.at(7));
	string degreeProgramString = rowData.at(8);

	// determine degree from string
	DegreeProgram degreeProgramTemp = DegreeProgram::NETWORK;
	if (degreeProgramString == "NETWORK") {
		degreeProgramTemp = DegreeProgram::NETWORK;
	}
	else if (degreeProgramString == "SECURITY") {
		degreeProgramTemp = DegreeProgram::SECURITY;
	}
	else if (degreeProgramString == "SOFTWARE") {
		degreeProgramTemp = DegreeProgram::SOFTWARE;
	}

	add(
		studentIDTemp,
		firstNameTemp,
		lastNameTemp,
		emailAddressTemp,
		ageTemp,
		courseDays1Temp,
		courseDays2Temp,
		courseDays3Temp,
		degreeProgramTemp
	);
}

// regex from here: https://www.codespeedy.com/program-to-validate-email-id-using-regex-in-cpp/
bool Roster::isValidEmail(string email) {
	const regex regexPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, regexPattern);
}

// for locating specific students in studentRoster
Student* Roster::retrieveStudent(int index) {
	return classRosterArray[index];
}

void Roster::add(
	string studentID,
	string firstName,
	string lastName,
	string studentEmail,
	int studentAge,
	int courseDays1st,
	int courseDays2nd,
	int courseDays3rd,
	DegreeProgram degree
) {
	// increase index to empty one
	rosterIndex++;
	// add new student object
	classRosterArray[rosterIndex] = new Student(
		studentID,
		firstName,
		lastName,
		studentEmail,
		studentAge,
		courseDays1st,
		courseDays2nd,
		courseDays3rd,
		degree
	);
}

void Roster::remove(string studentID) {
	// to know if to raise error or not
	bool recordLocated = false;
	// iterate through records for a match
	for (int i = 0; i <= rosterIndex; i++) {
		if (this->classRosterArray[i]->getStudentID() == studentID) {
			recordLocated = true;
			delete this->classRosterArray[i];
			// switch position with last element to avoid gaps in array
			this->classRosterArray[i] = this->classRosterArray[rosterIndex];
			rosterIndex--;
		}
	}
	// print out error if student not located
	if (!recordLocated) {
		cout << "Student with ID " << studentID << " not located\n";
	}
}

void Roster::printAll() {
	for (int i = 0; i <= this->rosterIndex; i++) {
		this->classRosterArray[i]->print();
	}
}

void Roster::printAvgDaysInCourse(string studentID) {
	for (int i = 0; i <= rosterIndex; i++) {
		if (this->classRosterArray[i]->getStudentID() == studentID) {
			vector<int> courseDays = classRosterArray[i]->getCourseDays();
			// this should allow for easier expansion of courseDays if needed
			int avgCourseDays = accumulate(courseDays.begin(), courseDays.end(), courseDays.size()) / courseDays.size();
			cout << "Average Days In Course: " << avgCourseDays << endl;
		}
	}
}

void Roster::printInvalidEmails() {
	for (int i = 0; i <= this->rosterIndex; i++) {
		string tempEmail = this->classRosterArray[i]->getEmail();
		if (!isValidEmail(tempEmail)) {
			cout << "The email " << tempEmail << " for student " << this->classRosterArray[i]->getStudentID() << " is invalid." << endl;
		}
	}
}

// use degree to ensure no unintended type conversion with int
void Roster::printByDegreeProgram(DegreeProgram degree) {
	for (int i = 0; i <= rosterIndex; i++) {
		if (this->classRosterArray[i]->getDegreeProgram() == degree) {
			this->classRosterArray[i]->print();
		}
	}
}