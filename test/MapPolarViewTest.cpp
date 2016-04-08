#include "gtest/gtest.h"
#include "../source/include/MapPolarView.hpp"
#include <stdlib.h>

TEST(MapPolarView, Constructor){
    MapPolarView mpv = MapPolarView();
}

TEST(MapPolarView, Collapse){
	MapPolarView mpv = MapPolarView();
	DistanceReading distRead1(Length(6*Length::METER), DistanceReading::ResultType::CHECKED);
	DistanceReading distRead2(Length(3*Length::METER), DistanceReading::ResultType::CHECKED);

	//Checks it doesn't override the same angle which already has a value
	mpv.add_distancereading(10, distRead1);
	mpv.add_distancereading(370, distRead2);
	//checks if current values are kept.
	mpv.add_distancereading(20, distRead1);
	//checks if outside range value is merged
	mpv.add_distancereading(375, distRead2);

	std::map<int, DistanceReading>& map = mpv.get_distances();
	mpv.collapse();

	// EXPECT_EQ(map.at(10).get_length(), distRead1.get_length()) << "got overridden by outside value";
	// EXPECT_EQ(map.at(20).get_length(), distRead1.get_length()) << "check of kept value";
	// EXPECT_EQ(map.at(15).get_length(), distRead2.get_length()) << "check if collapse value addded";

	EXPECT_FALSE(map.count(375) > 0) << "outside value has been deleted";
}

TEST(MapPolarView, Scale){
    MapPolarView mpv = MapPolarView();
	Length len1 = (6*Length::METER);
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	mpv.add_distancereading(10, distRead1);

	std::map<int, DistanceReading>& map = mpv.get_distances();

    mpv.scale(2); // multiplication test
	// EXPECT_EQ(map.at(10).get_length(), len1 * 2);

    mpv.scale(0.5); // division test
	// EXPECT_EQ(map.at(10).get_length(), len1);
}

TEST(MapPolarView, addAssignOperator){
    MapPolarView mpv = MapPolarView();
    MapPolarView mv = MapPolarView();
	Length len1(6*Length::METER);
	Length len2(3*Length::METER);
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	DistanceReading distRead2(len2, DistanceReading::ResultType::CHECKED);

	mpv.add_distancereading(10, distRead1);
	mv.add_distancereading(10, distRead2);

	mpv.add_distancereading(20, distRead1);
	mv.add_distancereading(30, distRead2);

	mpv += mv;

	std::map<int, DistanceReading>& map = mpv.get_distances();

	// EXPECT_EQ(map.at(10).get_length(), len1);
	// EXPECT_EQ(map.at(20).get_length(), len1);
	// EXPECT_EQ(map.at(30).get_length(), len2);
}

TEST(MapPolarView, addOperator){
    MapPolarView mpv = MapPolarView();
    MapPolarView mv = MapPolarView();
	Length len1(6*Length::METER);
	Length len2(3*Length::METER);
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	DistanceReading distRead2(len2, DistanceReading::ResultType::CHECKED);

	mpv.add_distancereading(10, distRead1);
	mv.add_distancereading(10, distRead2);

	mpv.add_distancereading(20, distRead1);
	mv.add_distancereading(30, distRead2);

	MapPolarView copyMap = mpv + mv;
	std::map<int, DistanceReading>& map = mpv.get_distances();

	// EXPECT_EQ(map.at(10).get_length(), len1);
	// EXPECT_EQ(map.at(20).get_length(), len1);
	// EXPECT_EQ(map.at(30).get_length(), Length());

	std::map<int, DistanceReading>& cMap = copyMap.get_distances();
	// EXPECT_EQ(cMap.at(10).get_length(), len1);
	// EXPECT_EQ(cMap.at(20).get_length(), len1);
	// EXPECT_EQ(cMap.at(30).get_length(), len2);
}

TEST(MapPolarView, add_distancereadingOne){
    MapPolarView mpv = MapPolarView();
    mpv.add_distancereading(0, 3 * Length::METER, DistanceReading::ResultType::CHECKED);
    // std::map<int, DistanceReading> testmap = mpv.get_distances();
    // std::cout << testmap.at(0).get_length() << " add_distancereadingOne length" << std::endl;

}
TEST(MapPolarView, add_distancereadingTwo){
    DistanceReading dist = DistanceReading(2*Length::METER, DistanceReading::ResultType::CHECKED);
    MapPolarView mpv = MapPolarView();
    mpv.add_distancereading(1, dist);
    // std::map<int, DistanceReading> testmap = mpv.get_distances();
    // std::cout << testmap.at(1).get_length()<< " add_distancereadingTwo length" << std::endl;
}
TEST(MapPolarView, rotate){
    MapPolarView mpv = MapPolarView();
    DistanceReading dist = DistanceReading(5*Length::METER, DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(348, dist);
    mpv.add_distancereading(349, dist);
    mpv.add_distancereading(350, dist);
    mpv.add_distancereading(351, dist);
    mpv.add_distancereading(352, dist);
    mpv.add_distancereading(353, dist);
    mpv.add_distancereading(354, dist);
    mpv.add_distancereading(355, dist);
    mpv.add_distancereading(356, dist);
    mpv.add_distancereading(357, dist);
    mpv.add_distancereading(358, dist);
    mpv.add_distancereading(359, dist);
    mpv.add_distancereading(0, dist);
    mpv.add_distancereading(1, dist);
    mpv.add_distancereading(2, dist);
    mpv.add_distancereading(3, dist);
    mpv.add_distancereading(4, dist);
    mpv.add_distancereading(5, dist);
    mpv.rotate(10);

    std::map<int,DistanceReading> testmap = mpv.get_distances();
    for(int i = 0; i < 30; i++){
        std::cout << i<< ":" << testmap.at(i).get_length() << " ";
    }
    // std::cout << " <<< Post-rotate" << std::endl;
}

// Test get_distances()
//  Test case for the get_distances() function
//  Create a MapPolarView object and get it's std::map.

TEST(MapPolarView, get_distances) {
    MapPolarView v;
    std::map<int, DistanceReading> m = v.get_distances();
}

//  Test match()
//
//  Test case for the match() function
//  Create 2 MapPolarView's to compare. Create 2 different DistanceReading objects to use in testing.
//  Fill the MapPolarView object and compare how many of their lists are the same.
//  Add a wrong value and check again. Expect the value to not be 100%

TEST(MapPolarView, Match) {
    MapPolarView mpv1 = MapPolarView();
    MapPolarView mpv2 = MapPolarView();
    DistanceReading dist = DistanceReading(5*Length::METER, DistanceReading::ResultType::CHECKED);
    DistanceReading dist2 = DistanceReading(4*Length::METER, DistanceReading::ResultType::CHECKED);

    mpv1.add_distancereading(0, dist);
    mpv1.add_distancereading(3, dist);
    mpv1.add_distancereading(5, dist);
    mpv1.add_distancereading(6, dist);
    mpv1.add_distancereading(356, dist);
    mpv1.add_distancereading(357, dist);
    mpv1.add_distancereading(358, dist);
    mpv1.add_distancereading(359, dist);
    std::map<int, DistanceReading> map1 = mpv1.get_distances();

    mpv2.add_distancereading(0, dist);
    mpv2.add_distancereading(3, dist);
    mpv2.add_distancereading(5, dist);
    mpv2.add_distancereading(6, dist);
    mpv2.add_distancereading(356, dist);
    mpv2.add_distancereading(357, dist);
    mpv2.add_distancereading(358, dist);
    mpv2.add_distancereading(359, dist);
    std::map<int, DistanceReading> map2 = mpv2.get_distances();

    EXPECT_EQ(mpv1.match(mpv2), 100);
    EXPECT_NE(mpv1.match(mpv2), 99.9);
    EXPECT_EQ(mpv1.match(mpv1), 100);

    mpv1.add_distancereading(359, dist2);
    map1 = mpv1.get_distances();
    EXPECT_NE(mpv1.match(mpv2), 100);
}

TEST(MapPolarView, find_best_match){
    MapPolarView mpv = MapPolarView();
    MapPolarView pv = MapPolarView();

    DistanceReading dist = DistanceReading(5*Length::METER, DistanceReading::ResultType::CHECKED);
    DistanceReading dist2 = DistanceReading(10*Length::METER, DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(0, dist);
    mpv.add_distancereading(3, dist);
    mpv.add_distancereading(5, dist);
    mpv.add_distancereading(6, dist);
    mpv.add_distancereading(356, dist);
    mpv.add_distancereading(357, dist);
    mpv.add_distancereading(358, dist);
    mpv.add_distancereading(359, dist);

    pv.add_distancereading(0, dist2);
    pv.add_distancereading(3, dist2);
    pv.add_distancereading(5, dist2);
    pv.add_distancereading(6, dist2);
    pv.add_distancereading(356, dist2);
    pv.add_distancereading(357, dist2);
    pv.add_distancereading(358, dist2);
    pv.add_distancereading(359, dist2);

    pv.rotate(20);

    std::tuple<int, double> result = mpv.find_best_match(pv);
    std::cout << "Rotate factor: " << std::get<0>(result) << "| Scale factor: " << std::get<1>(result) << std::endl;
    mpv.scale(get<1>(result));
    mpv.rotate(get<0>(result));
    std::cout << "Match: " <<mpv.match(pv) << "%" << std::endl;
}
