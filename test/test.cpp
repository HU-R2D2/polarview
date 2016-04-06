#include "gtest/gtest.h"
#include "../source/include/DistanceReading.hpp"
#include "../source/include/MapPolarView.hpp"

//! Test set_result_type()
/*!
 Test case for the set_result_type() function
 Create a DistanceReading object, check it's ResultType,
	set it's ResultType and check again.
 Repeat for every possible ResultType.
 */
TEST(SetResultType, SetResultType) {

	Length len;

	DistanceReading a(DistanceReading(len, DistanceReading::ResultType::DIDNT_CHECK));

	EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::DIDNT_CHECK);

	a.set_result_type(DistanceReading::ResultType::OUT_OF_RANGE);
	EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::OUT_OF_RANGE);

	a.set_result_type(DistanceReading::ResultType::CHECKED);
	EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::CHECKED);
}

//! Test get_result_type()
/*!
 Test case for the get_result_type() function
 Create multiple DistanceReading objects and compare their ResultType
 against ResultType objects
 */
TEST(GetResultType, GetResultType) {

	Length len;

	DistanceReading a(DistanceReading(len, DistanceReading::ResultType::DIDNT_CHECK));
	DistanceReading b(DistanceReading(len, DistanceReading::ResultType::OUT_OF_RANGE));
	DistanceReading c(DistanceReading(len, DistanceReading::ResultType::CHECKED));
}

//! Test set_length()
/*!
 Test case for the set_length() function
 Create a DistanceReading object and get it's length object.
 Check if this length is within range of another length.
 Uses a very precise offset of (1000 * 1000 * 1000) to see if 2 length's are equal
 */
TEST(SetDistance, SetDistance) {
	Length len1(200 * Length::METER);
	Length len2(200 * Length::METER);

	DistanceReading a(DistanceReading(len2, DistanceReading::ResultType::DIDNT_CHECK));
	Length tempmax(a.get_length());
	// Extremely precise offset for measurement
	const Length offset(len1 / (1000 * 1000 * 1000));

	// Lengths are both 200, so in range
	EXPECT_TRUE(((len1 - offset) < tempmax) && (tempmax < (len1 + offset)));

	// Set the length to a different value
	a.set_length(201 * Length::METER);
	tempmax = a.get_length();

	// Length is no longer in range of 200, so it should be false
	EXPECT_FALSE(((len1 - offset) < tempmax) && (tempmax < (len1 + offset)));
}

//! Test get_length()
/*!
 Test case for the get_length() function
 Create a DistanceReading object and get it's length object.
 Check if this length is within range of another length.
 */
TEST(GetDistance, GetDistance) {
	Length len1(200 * Length::METER);
	Length len2(200.01 * Length::METER);

	DistanceReading a(DistanceReading(len2, DistanceReading::ResultType::DIDNT_CHECK));
	Length tempmax(a.get_length());

	const Length offset(len1 / 10000);

	EXPECT_TRUE(((len1 - offset) < tempmax) && (tempmax < (len1 + offset)));
}

//MapPolarView TESTING SECTION -------------------------------------------------
TEST(Polarview, Constructor){
	MapPolarView mpv = MapPolarView();
}

TEST(Polarview, Scale){
	MapPolarView mpv = MapPolarView();
	mpv.scale(2);
	mpv.scale(0.5);
}

TEST(Polarview, addAssignOperator){
	MapPolarView mpv = MapPolarView();
	MapPolarView mv = MapPolarView();
	mpv += mv;
}

TEST(Polarview, addOperator){
	MapPolarView mpv = MapPolarView();
	MapPolarView mv = MapPolarView();
	MapPolarView result = mpv + mv;
}

TEST(Polarview, add_distancereadingOne){
	MapPolarView mpv = MapPolarView();
	mpv.add_distancereading(0, 3 * Length::METER, DistanceReading::ResultType::CHECKED);
	// std::map<int, DistanceReading> testmap = mpv.get_distances();
	// std::cout << testmap.at(0).get_length() << " add_distancereadingOne length" << std::endl;

}
TEST(Polarview, add_distancereadingTwo){
	DistanceReading dist = DistanceReading(2*Length::METER, DistanceReading::ResultType::CHECKED);
	MapPolarView mpv = MapPolarView();
	mpv.add_distancereading(1, dist);
	// std::map<int, DistanceReading> testmap = mpv.get_distances();
	// std::cout << testmap.at(1).get_length()<< " add_distancereadingTwo length" << std::endl;
}
TEST(Polarview, rotate){
	MapPolarView mpv = MapPolarView();
	DistanceReading dist = DistanceReading(5*Length::METER, DistanceReading::ResultType::CHECKED);

	mpv.add_distancereading(0, dist);
	mpv.add_distancereading(3, dist);
	mpv.add_distancereading(5, dist);
	mpv.add_distancereading(6, dist);
	mpv.add_distancereading(357, dist);
	mpv.add_distancereading(359, dist);
	mpv.rotate(5);
	std::map<int,DistanceReading> testmap = mpv.get_distances();

	// for(int i = 0; i < 15; i++){
	// 	std::cout << testmap.at(i).get_length() << " ";
	// }
	// std::cout << "<<< Post-rotate" << std::endl;
}

// Test get_distances()
//  Test case for the get_distances() function
//  Create a MapPolarView object and get it's std::map.

TEST(MapPolarView, get_distances) {
	MapPolarView v;
	std::map<int, DistanceReading> m = v.get_distances();
}

// TEST(MapPolarView, Match) {
// 	MapPolarView v, w;
//
// 	EXPECT_EQ(v.match(w), 50.0);
// }
