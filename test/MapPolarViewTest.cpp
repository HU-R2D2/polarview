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
	EXPECT_EQ(map.at(10).get_length(), distRead.get_length());
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

    mpv.add_distancereading(0, dist);
    mpv.add_distancereading(3, dist);
    mpv.add_distancereading(5, dist);
    mpv.add_distancereading(6, dist);
    mpv.add_distancereading(357, dist);
    mpv.add_distancereading(359, dist);
    mpv.rotate(5);
    std::map<int,DistanceReading> testmap = mpv.get_distances();

    // for(int i = 0; i < 15; i++){
    //     std::cout << testmap.at(i).get_length() << " ";
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
//     MapPolarView v, w;
//
//     EXPECT_EQ(v.match(w), 50.0);
// }
