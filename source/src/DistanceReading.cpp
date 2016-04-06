#include "../include/DistanceReading.hpp"

DistanceReading::DistanceReading(Length len, ResultType type) :
	length(len), type(type)
{
	
}

void DistanceReading::set_result_type(ResultType t) {
	this->type = t;
}

ResultType DistanceReading::get_result_type() {
	return this->type;
}

void DistanceReading::set_length(Length l) {
	this->length = l;
}

Length & DistanceReading::get_length() {
	return length;
}