//
// Created by Nathan Teeter on 2019-04-27.
//

#include <string>
#include "csv_data.h"

class name_grad : public csv_data {
public:
	bool operator <=(name_grad data) {
		if (this->getName() == data.getName()) {
			return this->getGradDate() <= data.getGradDate();
		} else {
			return this->getName() <= data.getName();
		}
	}
};