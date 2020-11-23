//
// Created by Nathan Teeter on 2019-04-27.
//

#include <string>
#include "csv_data.h"

class grad_name : public csv_data {
public:
	bool operator <=(grad_name data) {
		if (this->getGradDate() == data.getGradDate()) {
			return this->getName() <= data.getName();
		} else {
			return this->getGradDate() <= data.getGradDate();
		}
	}
};