#include "gtest/gtest.h"
#include "../source/include/DistanceReading.hpp"


TEST(GetResultType, GetResultType) {
	ResultType didnt = ResultType::DIDNT_CHECK;
	ResultType range = ResultType::OUT_OF_RANGE;
	ResultType check = ResultType::CHECKED;
	
	Distance dist;
	
	DistanceReading a = DistanceReading(dist, didnt);
	DistanceReading b(DistanceReading(dist, range));
	DistanceReading c(DistanceReading(dist, check));
	
	EXPECT_EQ(a.get_result_type(), ResultType::DIDNT_CHECK);
	EXPECT_EQ(b.get_result_type(), ResultType::OUT_OF_RANGE);
	EXPECT_EQ(c.get_result_type(), ResultType::CHECKED);
}


TEST(GetDistance, GetDistance) {
	Distance dist1;
	Distance dist2(4 * Length::METER, 5 * Length::METER, 6 * Length::METER);
	DistanceReading a = DistanceReading(dist1, ResultType::DIDNT_CHECK);
	
	EXPECT_EQ(a.get_distance(), dist1);
	EXPECT_NE(a.get_distance(), dist2);
}