#include "gtest/gtest.h"
#include "../source/include/DistanceReading.hpp"


TEST(GetResultType, GetResultType) {
	ResultType didnt = DIDNT_CHECK;
	ResultType range = OUT_OF_RANGE;
	ResultType check = CHECKED;
	
	Distance distance();
	
	DistanceReading a(DistanceReading(distance, didnt));
	DistanceReading b(DistanceReading(distance, range));
	DistanceReading c(DistanceReading(distance, check));
	
	EXPECT_EQ(a->GetResultType(), DIDNT_CHECK);
	EXPECT_EQ(b->GetResultType(), OUT_OF_RANGE);
	EXPECT_EQ(c->GetResultType(), CHECKED);
}

/*
TEST(GetDistance, GetDistance) {
	DistanceReading a(DistanceReading(, DIDNT_CHECK));
	
	EXPECT_EQ(a->GetDistance(), );
}
*/