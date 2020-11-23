//
// Created by Nathan Teeter on 2019-04-23.
//

#include "csv_data.h"
#include <string>
#include <iostream>
#include "Date.h"

//constructor
csv_data::csv_data():gradDate("Jan 0, 0000"){
}

csv_data::~csv_data() {

}

//methods
const void csv_data::print() {
	std::cout << "\n" << this->getName() << "\t";
	std::cout << this->getDonorStatus() << "\t";
	if (this->getGradDate() == Date("Jan 0, 0000")) {
		std::cout << "";
	} else {
		std::cout << this->getGradDate().toString() << "\t";
		std::cout << this->getInstitution();
	}
}

const std::string csv_data::value() {
	std::string str;

    str.append("\"");
    str.append(this->getName());
	str.append("\"");
	str.append(",");
	str.append(this->getDonorStatus());
	str.append(",");
    if (this->getGradDate()== Date("Jan 0, 0000")) {
        str.append("");
        str.append(",");
    } else {
        str.append("\"");
        str.append(this->getGradDate().toString());
		str.append("\"");
        str.append(",");
        str.append(this->getInstitution());
    }

	return str;
}

//setters
void csv_data::setName(std::string name) {
	this->name = name;
}

void csv_data::setDonorStatus(std::string donorStatus) {
	this->donorStatus = donorStatus;
}

void csv_data::setGradDate(std::string gradDate) {
	Date date(gradDate);
	this->gradDate = date;
}

void csv_data::setInstitution(std::string institution) {
	this->institution = institution;
}

//getters
 std::string csv_data::getName() {
	return this->name;
}

std::string csv_data::getDonorStatus() {
	return this->donorStatus;
}

Date csv_data::getGradDate() {
	return this->gradDate;
}

std::string csv_data::getInstitution() {
	return this->institution;
}
