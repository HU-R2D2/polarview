#ifndef _ARRAYPOLARVIEW_H
#define _ARRAYPOLARVIEW_H

#include "DistanceReading.hpp"
#include <array>
#include <map>
#include <algorithm>

class ArrayPolarView{
public:
	//Default constructor
	ArrayPolarView();
	
	// virtual ArrayPolarView collapse() = 0;
	
	// virtual rotate(Angle angle) = 0;
	
	// virtual double match(PolarView v) = 0;
	
	// virtual std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;
	
	//virtual std::map<Angle, DistanceReading> get_distances() = 0;
	
	ArrayPolarView operator*(double frac);
	
	ArrayPolarView operator/(double frac);
	
	//Adds 2 ArrayPolarviews together, this does not add them together but merges them
	ArrayPolarView operator+(ArrayPolarView v);
	
private:	
	std::array<DistanceReading, 360> readings = {DistanceReading(Distance(), ResultType::DIDNT_CHECK)};
	
};

#endif //_ARRAYPOLARVIEW_H