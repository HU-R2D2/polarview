#ifndef _POLARVIEW_H
#define _POLARVIEW_H

#include DistanceReading.hpp
#include <array>
#include <map>

class ArrayPolarView{
public:
	//Default constructor
	PolarView();
	
	virtual PolarView collapse() = 0;
	
	virtual rotate(Angle angle) = 0;
	
	virtual double match(PolarView v) = 0;
	
	virtual std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;
	
	virtual std::map<Angle, DistanceReading> get_distances() = 0;
	
	virtual PolarView operator*(double frac);
	
	virtual PolarView operator/(double frac);
	
	//Adds 2 Polarviews together, this does not add them together but merges them
	virtual PolarView operator+(PolarView v);
	
private:	
	std::array<DistanceReading, 360> readings;
}

#endif //_POLARVIEW_H