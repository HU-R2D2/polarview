#include "../include/DistanceReading.hpp"

DistanceReading::DistanceReading(){
	std::cout << "Default" << std::endl;
}

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

void DistanceReading::set_length(Length d) {
	this->length = d;
}

Translation DistanceReading::get_length() {
	return this->length;
}

bool operator==(Length lhs, Length rhs){
	Length offset(lhs / 100);
	return ((lhs -= offset) < rhs) & (rhs < (lhs += offset));
}
