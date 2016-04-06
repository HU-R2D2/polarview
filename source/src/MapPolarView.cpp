#include "../include/MapPolarView.hpp"

	MapPolarView::MapPolarView(){
		for(int i = 0; i < 360; i++){
			//readings[i] = DistanceReading(Length(), DistanceReading::ResultType::DIDNT_CHECK);
		}
		std::cout << readings.size() << " size of map" << std::endl;
	}

	//PolarView collapse() = 0;

	//rotate(Angle angle) = 0;

	// double match(PolarView v) = 0;

	// std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;

	//std::map<Angle, DistanceReading> get_distance() = 0;

	// ArrayPolarView ArrayPolarView::operator*(double frac){
	// 	for(int i = 0; i < 360; i++){
	// 		DistanceReading & temp = readings[i];
	// 		temp.set_distance(temp.get_distance() * frac);
	// 	}
	// }
	//
	// ArrayPolarView ArrayPolarView::operator/(double frac){
	// 	for(int i = 0; i < 360; i++){
	// 		DistanceReading & temp = readings[i];
	// 		temp.set_distance(temp.get_distance() / frac);
	// 	}
	// }

//At the moment it assumes both PolarViews have the same starting point TODO NOT FINISHED
// ArrayPolarView ArrayPolarView::operator+(ArrayPolarView v){
	// std::map tbadd{v.get_distances()};
	// for(int i = 0; i < 360; i++){
		// DistanceReading & temp = readings[i];
		// if(temp.get_result_type() != ResultType::CHECKED){
			// if(tbadd[i].get_result_type() == ResultType::CHECKED){
				// temp.set_distance(tbadd.get_distance());
				// temp.set_result_type(tbadd.get_result_type());
			// }
		// }
	// }
// }
