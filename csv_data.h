//
// Created by Nathan Teeter on 2019-04-23.
//

#ifndef TBB_MERGESORT_CSV_DATA_H
#define TBB_MERGESORT_CSV_DATA_H


#include <string>
#include "Date.h"

class csv_data {
private:
	std::string name;
	std::string donorStatus;
	Date gradDate;
	std::string institution;
public:
    csv_data();
    ~csv_data();

	//methods
    const void print();
	const std::string value();

	//getters
	std::string getName();
	std::string getDonorStatus();
	Date getGradDate();
	std::string getInstitution();

	//setters
	void setName(std::string);
	void setDonorStatus(std::string);
	void setGradDate(std::string);
	void setInstitution(std::string);
};


#endif //TBB_MERGESORT_CSV_DATA_H
