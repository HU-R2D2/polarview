#include "../include/MapPolarView.hpp"
#include "../include/DistanceReading.hpp"

MapPolarView::MapPolarView(){
	for(int i = 0; i < 360; i++){
		readings.insert(std::pair<int, DistanceReading>(i,DistanceReading(DistanceReading(Length(), DistanceReading::ResultType::DIDNT_CHECK))));

	}
	std::cout << readings.size() << " size of map" << std::endl;
	rotate(5);
}

	//PolarView collapse() = 0;

void MapPolarView::rotate(int angle){
	for(int i = 0; i < angle; i++){
		DistanceReading & buffer = readings.at(readings.size()-1);
		for(int i = readings.size()-1; i > 0; i--){
			readings.at(i) = readings.at(i-1);
		}
		readings.at(0) = buffer;
	}
}

std::map<int, DistanceReading> & MapPolarView::get_distances() {
	return readings;
}

double MapPolarView::match(MapPolarView v) {
	int c = 0;
	for(int i = 0; i < 360; i++) {
		Length len1 = this->get_distances().at(i).get_length();
		Length len2 = v.get_distances().at(i).get_length();

		const Length offset(len1 / 10000);

		if(((len1 - offset) < len2) && (len2 < (len1 + offset))) {
			c++;
		}
	}
	return (c/360)*100;
}

	// std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;

	//std::map<Angle, DistanceReading> get_distance() = 0;

MapPolarView MapPolarView::scale(double frac){
	for(int i = 0; i < 360; i++){
		DistanceReading & temp = readings.at(i);
		temp.set_length(temp.get_length() * frac);
	}
	return (*this);
}

// At the moment it assumes both PolarViews have the same starting point
MapPolarView MapPolarView::operator+=(MapPolarView v){
	std::map<int, DistanceReading> tbadd = v.get_distances();
	for(int i = 0; i < 360; i++){
		DistanceReading & temp = readings.at(i);
		if(temp.get_result_type() != DistanceReading::ResultType::CHECKED){
			DistanceReading addtemp = tbadd.at(i);
			if(addtemp.get_result_type() == DistanceReading::ResultType::CHECKED){
				temp.set_length(addtemp.get_length());
				temp.set_result_type(addtemp.get_result_type());
			}
		}
	}
	return (*this);
}

MapPolarView MapPolarView::operator+(MapPolarView v){
	MapPolarView retPV = (*this);
	return retPV += v;
}
