#ifndef DISTANCEREADING_H
#define DISTANCEREADING_H

#include "../../../adt/source/include/Length.hpp"

class DistanceReading {

private:
	Length len;

public:
	enum class ResultType {
		DIDNT_CHECK,
		OUT_OF_RANGE,
		CHECKED
	};

	DistanceReading(Length len);
	//! DistanceReading constructor
	DistanceReading(Length len, ResultType type);

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
	void set_length(Length len);

	//! get_distance
	/*!
	 Getter for the Distance object
	 \param
	 \return Distance distance
	*/
	Translation get_length();
};

#endif // DISTANCEREADING_H
