#include "../include/PolarView.hpp"

	ArrayPolarView::PolarView():{
		for(int i = 0; i < 360; i++){
			readings[i] = DistanceReading(Distance(), ResultType::DIDNT_CHECK);
		}
	}
	
	//PolarView collapse() = 0;
	
	//rotate(Angle angle) = 0;
	
	// double match(PolarView v) = 0;
	
	// std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;
	
	// std::map<Angle, DistanceReading> get_distance() = 0;
	
	// PolarView operator+(double frac) = 0;
	
	// PolarView operator/(double frac) = 0;
	
	// PolarView operator+(PolarView v) = 0;	