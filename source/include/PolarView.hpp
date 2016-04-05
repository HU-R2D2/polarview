#ifndef _POLARVIEW_H
#define _POLARVIEW_H

#include DistanceReading.hpp
#include <array>

class ArrayPolarView{
public:
	//Default constructor
	PolarView();
	
	virtual PolarView collapse() = 0;
	
	virtual rotate(Angle angle) = 0;
	
	virtual double match(PolarView v) = 0;
	
	virtual std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;
	
	virtual std::map<Angle, DistanceReading> get_distance() = 0;
	
	virtual PolarView operator+(double frac) = 0;
	
	virtual PolarView operator/(double frac) = 0;
	
	virtual PolarView operator+(PolarView v) = 0;
	
private:	
	std::array<DistanceReading, 360> readings;
}

#endif //_POLARVIEW_H