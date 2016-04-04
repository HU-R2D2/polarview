#include "../include/DistanceReading.hpp"

DistanceReading::DistanceReading(Distance dist, ResultType type) : distance(dist), type(type) {
	
}

ResultType DistanceReading::get_result_type() {
	return this->type;
}

Distance DistanceReading::get_distance() {
	return this->distance;
}