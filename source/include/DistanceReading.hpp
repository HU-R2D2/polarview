#ifndef DISTANCEREADING_H
#define DISTANCEREADING_H

#include "../../../adt/source/include/Length.hpp"

class DistanceReading {
public:
	enum class ResultType {
		DIDNT_CHECK,
		OUT_OF_RANGE,
		CHECKED
	};

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

	//! set_length
	/*!
	 Setter for the Length object
	 \param Length
	 \return
	 */
	void set_length(Length len);

	//! get_distance
	/*!
	 Getter for the Length object
	 \param
	 \return Length length
	*/
	Length & get_length();
private:
	Length length;
	ResultType type;
};

#endif // DISTANCEREADING_H
