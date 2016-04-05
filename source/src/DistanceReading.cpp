#include "../include/DistanceReading.hpp"

DistanceReading::DistanceReading(Distance dist, ResultType type) :
	distance(dist), type(type)
{
	
}

void DistanceReading::set_result_type(ResultType t) {
	this->type = t;
}

ResultType DistanceReading::get_result_type() {
	return this->type;
}

void DistanceReading::set_distance(Distance d) {
	this->distance = d;
}

Distance & DistanceReading::get_distance() {
	return distance;
}

bool operator==(const Distance lhs, const Distance rhs){
	Distance tempmin(lhs);
	Distance tempmax(rhs);
	
	const Distance offset(tempmin / 100);
	return ((tempmin -= offset) < tempmax) & (tempmax < (tempmin += offset));
}