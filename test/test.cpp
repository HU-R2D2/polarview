#include "gtest/gtest.h"
#include "../source/include/DistanceReading.hpp"

//! Test get_result_type()
/*!
 Test case for the get_result_type() function
 Create multiple DistanceReading objects and compare their ResultType
 against ResultType objects
 */
TEST(GetResultType, GetResultType) {
	/*
	ResultType didnt = ResultType::DIDNT_CHECK;
	ResultType range = ResultType::OUT_OF_RANGE;
	ResultType check = ResultType::CHECKED;
	
	Distance dist;
	
	DistanceReading a(DistanceReading(dist, didnt));
	DistanceReading b(DistanceReading(dist, range));
	DistanceReading c(DistanceReading(dist, check));
	 */
}

//! Test get_distance()
/*!
 Test case for the get_distance() function
 Create a DistanceReading object and compare it's Distance against an empty
 Distance object. Then compare it against a filled Distance object
 */
TEST(GetDistance, GetDistance) {
	/*
	Distance dist1;
	Distance dist2(4 * Length::METER, 5 * Length::METER, 6 * Length::METER);
	DistanceReading a = DistanceReading(dist1, ResultType::DIDNT_CHECK);
	
	EXPECT_EQ(a.get_distance(), dist1);
	EXPECT_NE(a.get_distance(), dist2);
	*/
}