#include "Date.h"

#include <iostream>

// Date stores a date in one 32-bit int.
// The 2 most significant bytes are the year,
// the next byte is the month,
// the final byte is the day.

int Date::getYear() {
	return this->date >> 16;
}

int Date::getMonth() {
	return (this->date >> 8) & 0xff;
}

int Date::getDay() {
	return this->date & 0xff;
}

Date::Date(std::string dateString) {
	std::string monthString = dateString.substr(0, 3);
	int month;
	if (monthString == "Jan") { month = 0; }
	else if (monthString == "Feb") { month = 1; }
	else if (monthString == "Mar") { month = 2; }
	else if (monthString == "Apr") { month = 3; }
	else if (monthString == "May") { month = 4; }
	else if (monthString == "Jun") { month = 5; }
	else if (monthString == "Jul") { month = 6; }
	else if (monthString == "Aug") { month = 7; }
	else if (monthString == "Sep") { month = 8; }
	else if (monthString == "Oct") { month = 9; }
	else if (monthString == "Nov") { month = 10; }
	else if (monthString == "Dec") { month = 11; }
	else {
		std::cout << "Invalid month: " << monthString << std::endl;
		exit(1);
	}
	int date = std::stoi(dateString.substr(3));
	int year = std::stoi(dateString.substr(dateString.length() - 4, 4));
	this->date = (year << 16) | (month << 8) | date;
}

bool Date::operator==(Date other) {
	return this->date == other.date;
}

bool Date::operator<=(Date other) {
	return this->date <= other.date;
}

std::string Date::toString() {
	std::string result;
	switch (this->getMonth()) {
		case 0:
			result += "Jan";
			break;
		case 1:
			result += "Feb";
			break;
		case 2:
			result += "Mar";
			break;
		case 3:
			result += "Apr";
			break;
		case 4:
			result += "May";
			break;
		case 5:
			result += "Jun";
			break;
		case 6:
			result += "Jul";
			break;
		case 7:
			result += "Aug";
			break;
		case 8:
			result += "Sep";
			break;
		case 9:
			result += "Oct";
			break;
		case 10:
			result += "Nov";
			break;
		case 11:
			result += "Dec";
			break;
	}
	result += " " + std::to_string(this->getDay()) + ", " + std::to_string(this->getYear());
	return result;
}
