#ifndef DISTANCEREADING_H
#define DISTANCEREADING_H

#include "../../../adt/source/include/Distance.hpp"
#include "../../../adt/source/include/Length.hpp"

enum class ResultType {
	DIDNT_CHECK,
	OUT_OF_RANGE,
	CHECKED
};

class DistanceReading {
private:
	Distance distance;
	ResultType type;
public:
	DistanceReading(Distance dist, ResultType type);
	ResultType get_result_type();
	Distance get_distance();
};

#endif // DISTANCEREADING_H