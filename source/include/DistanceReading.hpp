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
	//! DistanceReading constructor
	DistanceReading(Distance dist, ResultType type);
	
	//! set_result_type
	/*!
	 Setter for the ResultType object
	 \param ResultType
	 \return
	 */
	void set_result_type(ResultType t);
	
	//! get_result_type
	/*!
	 Getter for the ResultType object
	 \param
	 \return ResultType type
	 */
	ResultType get_result_type();
	
	//! set_distance
	/*!
	 Setter for the Distance object
	 \param Distance
	 \return
	 */
	void set_distance(Distance d);
	
	//! get_distance
	/*!
	 Getter for the Distance object
	 \param
	 \return Distance distance
	*/
	Distance get_distance();
};

#endif // DISTANCEREADING_H