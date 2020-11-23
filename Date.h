#ifndef TBB_MERGESORT_DATE_H
#define TBB_MERGESORT_DATE_H

#include <string>

class Date {
private:
	uint32_t date;
	int getYear();
	int getMonth();
	int getDay();
public:
	Date(std::string dateString);
	bool operator==(Date other);
	bool operator<=(Date other);
	std::string toString();
};

#endif //TBB_MERGESORT_DATE_H
