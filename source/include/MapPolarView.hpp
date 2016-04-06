#ifndef _ARRAYPOLARVIEW_H
#define _ARRAYPOLARVIEW_H

#include "DistanceReading.hpp"
#include <map>
#include <algorithm>

class MapPolarView{
public:
	//Default constructor
	MapPolarView();

	// virtual ArrayPolarView collapse() = 0;

	// virtual rotate(Angle angle) = 0;

	// virtual double match(PolarView v) = 0;

	// virtual std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;

	//virtual std::map<Angle, DistanceReading> get_distances() = 0;

	MapPolarView operator*(double frac);

	MapPolarView operator/(double frac);

	//Adds 2 ArrayPolarviews together, this does not add them together but merges them
	MapPolarView operator+(MapPolarView v);

private:
	std::map <int, DistanceReading> readings;

};

#endif //_ARRAYPOLARVIEW_H
