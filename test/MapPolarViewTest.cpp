#include "gtest/gtest.h"
#include "../source/include/MapPolarView.hpp"

TEST(MapPolarView, Constructor){
    MapPolarView mpv = MapPolarView();
}

TEST(MapPolarView, Collapse){
	MapPolarView mpv = MapPolarView();
	DistanceReading distRead(Length(6*Length::METER), DistanceReading::ResultType::CHECKED);
	mpv.add_distancereading(370, distRead);
	std::map<int, DistanceReading>& map = mpv.get_distances();
	mpv.collapse();
	// EXPECT_EQ(map.at(10).get_length(), distRead.get_length());
}

TEST(MapPolarView, Scale){
    MapPolarView mpv = MapPolarView();
    mpv.scale(2);
    mpv.scale(0.5);
}

TEST(MapPolarView, addAssignOperator){
    MapPolarView mpv = MapPolarView();
    MapPolarView mv = MapPolarView();
    mpv += mv;
}

TEST(MapPolarView, addOperator){
    MapPolarView mpv = MapPolarView();
    MapPolarView mv = MapPolarView();
    MapPolarView result = mpv + mv;
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

    mpv.add_distancereading(354, dist);
    mpv.add_distancereading(355, dist);
    mpv.add_distancereading(356, dist);
    mpv.add_distancereading(357, dist);
    mpv.add_distancereading(358, dist);
    mpv.add_distancereading(359, dist);
    mpv.rotate(5);
    // std::map<int,DistanceReading> testmap = mpv.get_distances();

    // for(int i = 0; i < 15; i++){
    //     std::cout << i<< ":" << testmap.at(i).get_length() << " ";
    // }
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

    mpv.find_best_match(pv);
}
