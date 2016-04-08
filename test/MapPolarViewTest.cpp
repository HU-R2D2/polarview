#include "gtest/gtest.h"
#include "../source/include/MapPolarView.hpp"
#include <stdlib.h>

Angle make_degree_angle(int angle){
    Angle a = angle * Angle::deg;
    return a;
}

int get_degree_angle(Angle angle){
    int degrees = round(angle.get_angle() * (180 / M_PI));
    return degrees;
}
//Temporary implemented to check 2 lengths with a offset.
//Will be replaced by ADT comparator lateron.
bool length_range(Length len1, Length len2, double offset = 0.0001){
	return ((len1  - (offset * Length::METER)) < len2) && (len2 < (len1  + (offset * Length::METER)));
}

TEST(MapPolarView, Constructor){
    MapPolarView mpv = MapPolarView();
}
//DONE
TEST(MapPolarView, Collapse){
	MapPolarView mpv = MapPolarView();
	Length len1 = 6*Length::METER;
	Length len2 = 3*Length::METER;
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	DistanceReading distRead2(len2, DistanceReading::ResultType::CHECKED);

	//Checks it doesn't override the same angle which already has a value
	mpv.add_distancereading(make_degree_angle(10), distRead1);
	mpv.add_distancereading(make_degree_angle(370), distRead2);
	//checks if current values are kept.
	mpv.add_distancereading(make_degree_angle(20), distRead1);
	//checks if outside range value is merged
	mpv.add_distancereading(make_degree_angle(375), distRead2);

	std::map<int, DistanceReading>& map = mpv.get_distances();
	mpv.collapse();

	EXPECT_TRUE(length_range(map.at(10).get_length(),
                             distRead1.get_length())) << "got overridden by outside value";
	EXPECT_TRUE(length_range(map.at(20).get_length(),
                             distRead1.get_length())) << "check of kept value";
	EXPECT_TRUE(length_range(map.at(15).get_length(),
                             distRead2.get_length())) << "check if collapse value addded";

	EXPECT_FALSE(map.count(375) > 0) << "outside value has been deleted";
}
//DONE
TEST(MapPolarView, Scale){
    MapPolarView mpv = MapPolarView();
	Length len1 = 6*Length::METER;
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	mpv.add_distancereading(make_degree_angle(10), distRead1);

	std::map<int, DistanceReading>& map = mpv.get_distances();

    mpv.scale(2); // multiplication test
	EXPECT_TRUE(length_range(map.at(10).get_length(), len1 * 2));

    mpv.scale(0.5); // division test
	EXPECT_TRUE(length_range(map.at(10).get_length(), len1));
}
//DONE
TEST(MapPolarView, addAssignOperator){
    MapPolarView mpv = MapPolarView();
    MapPolarView mv = MapPolarView();
	Length len1 = 6*Length::METER;
	Length len2 = 3*Length::METER;
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	DistanceReading distRead2(len2, DistanceReading::ResultType::CHECKED);

	mpv.add_distancereading(make_degree_angle(10), distRead1);
	mv.add_distancereading(make_degree_angle(10), distRead2);

	mpv.add_distancereading(make_degree_angle(20), distRead1);
	mv.add_distancereading(make_degree_angle(30), distRead2);

	mpv += mv;

	std::map<int, DistanceReading>& map = mpv.get_distances();

	EXPECT_TRUE(length_range(map.at(10).get_length(), len1));
	EXPECT_TRUE(length_range(map.at(20).get_length(), len1));
	EXPECT_TRUE(length_range(map.at(30).get_length(), len2));
}
//DONE
TEST(MapPolarView, addOperator){
    MapPolarView mpv = MapPolarView();
    MapPolarView mv = MapPolarView();
	Length len1 = 6*Length::METER;
	Length len2 = 3*Length::METER;
	DistanceReading distRead1(len1, DistanceReading::ResultType::CHECKED);
	DistanceReading distRead2(len2, DistanceReading::ResultType::CHECKED);

	mpv.add_distancereading(make_degree_angle(10), distRead1);
	mv.add_distancereading(make_degree_angle(10), distRead2);

	mpv.add_distancereading(make_degree_angle(20), distRead1);
	mv.add_distancereading(make_degree_angle(30), distRead2);

	MapPolarView copyMap = mpv + mv;
	std::map<int, DistanceReading>& map = mpv.get_distances();

	EXPECT_TRUE(length_range(map.at(10).get_length(), len1));
	EXPECT_TRUE(length_range(map.at(20).get_length(), len1));
	EXPECT_TRUE(length_range(map.at(30).get_length(), Length()));

	std::map<int, DistanceReading>& cMap = copyMap.get_distances();
	EXPECT_TRUE(length_range(cMap.at(10).get_length(), len1));
	EXPECT_TRUE(length_range(cMap.at(20).get_length(), len1));
	EXPECT_TRUE(length_range(cMap.at(30).get_length(), len2));
}

//DONE
TEST(MapPolarView, add_distancereadingOne){
    MapPolarView mpv = MapPolarView();
	Length len1 = 3 * Length::METER;
	std::map<int, DistanceReading>& map = mpv.get_distances();

	EXPECT_TRUE(length_range(map.at(0).get_length(), Length()));
    mpv.add_distancereading(make_degree_angle(0), len1,
                            DistanceReading::ResultType::CHECKED);
	EXPECT_TRUE(length_range(map.at(0).get_length(), len1));

}
//DONE
TEST(MapPolarView, add_distancereadingTwo){
    MapPolarView mpv = MapPolarView();
	Length len1 = 3 * Length::METER;
	std::map<int, DistanceReading>& map = mpv.get_distances();

	EXPECT_TRUE(length_range(map.at(0).get_length(), Length()));
	DistanceReading distRead(len1,
                            DistanceReading::ResultType::CHECKED);
    mpv.add_distancereading(make_degree_angle(0), distRead);
	EXPECT_TRUE(length_range(map.at(0).get_length(), len1));
}
//DONE
TEST(MapPolarView, rotate){
    MapPolarView mpv = MapPolarView();
	Length len1 = 5*Length::METER;
    DistanceReading dist = DistanceReading(len1, DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(make_degree_angle(348), dist);
    mpv.add_distancereading(make_degree_angle(349), dist);
    mpv.add_distancereading(make_degree_angle(350), dist);
    mpv.add_distancereading(make_degree_angle(351), dist);
    mpv.add_distancereading(make_degree_angle(352), dist);
    mpv.add_distancereading(make_degree_angle(353), dist);
    mpv.add_distancereading(make_degree_angle(354), dist);
    mpv.add_distancereading(make_degree_angle(355), dist);
    mpv.add_distancereading(make_degree_angle(356), dist);
    mpv.add_distancereading(make_degree_angle(357), dist);
    mpv.add_distancereading(make_degree_angle(358), dist);
    mpv.add_distancereading(make_degree_angle(359), dist);
    mpv.add_distancereading(make_degree_angle(0), dist);
    mpv.add_distancereading(make_degree_angle(1), dist);
    mpv.add_distancereading(make_degree_angle(2), dist);
    mpv.add_distancereading(make_degree_angle(3), dist);
    mpv.add_distancereading(make_degree_angle(4), dist);
    mpv.add_distancereading(make_degree_angle(5), dist);

    std::map<int, DistanceReading>& map = mpv.get_distances();

    for(int i = 348; i < 360; i++){
        EXPECT_TRUE(length_range(map.at(i).get_length(), len1));
    }
    for(int i = 6; i < 15; i++){
        EXPECT_TRUE(length_range(map.at(i).get_length(), Length()));
    }

    mpv.rotate(make_degree_angle(10));

    for(int i = 348; i < 358; i++){
        EXPECT_TRUE(length_range(map.at(i).get_length(), Length()));
    }

    EXPECT_TRUE(length_range(map.at(358).get_length(), len1));
    EXPECT_TRUE(length_range(map.at(359).get_length(), len1));
    for(int i = 0; i < 15; i++){
        EXPECT_TRUE(length_range(map.at(i).get_length(), len1));
    }

}

// Test get_distances()
//  Test case for the get_distances() function
//  Create a MapPolarView object and get it's std::map.
//DONE
TEST(MapPolarView, get_distances) {
    MapPolarView mpv;
    std::map<int, DistanceReading> map = mpv.get_distances();
	std::map<int, DistanceReading> testMap;
	for(int i = 0; i < 360; i++) {
		testMap.insert(std::pair<int, DistanceReading>(
			i,
			DistanceReading(
				DistanceReading(
					Length(),
					DistanceReading::ResultType::DIDNT_CHECK
					)
				)
			)
		);
	}
	for(int i = 0; i < 360; i++){
		EXPECT_TRUE(length_range(map.at(i).get_length(), testMap.at(i).get_length()));
	}
}

//  Test match()
//
//  Test case for the match() function
//  Create 2 MapPolarView's to compare. Create 2 different
//  DistanceReading objects to use in testing.
//  Fill the MapPolarView object and compare how many of their lists are the same.
//  Add a wrong value and check again. Expect the value to not be 100%
//DONE
TEST(MapPolarView, Match) {
    MapPolarView mpv1 = MapPolarView();
    MapPolarView mpv2 = MapPolarView();
    DistanceReading dist = DistanceReading(5*Length::METER,
                                           DistanceReading::ResultType::CHECKED);
    DistanceReading dist2 = DistanceReading(4*Length::METER,
                                            DistanceReading::ResultType::CHECKED);

    mpv1.add_distancereading(make_degree_angle(0), dist);
    mpv1.add_distancereading(make_degree_angle(3), dist);
    mpv1.add_distancereading(make_degree_angle(5), dist);
    mpv1.add_distancereading(make_degree_angle(6), dist);
    mpv1.add_distancereading(make_degree_angle(356), dist);
    mpv1.add_distancereading(make_degree_angle(357), dist);
    mpv1.add_distancereading(make_degree_angle(358), dist);
    mpv1.add_distancereading(make_degree_angle(359), dist);
    std::map<int, DistanceReading> map1 = mpv1.get_distances();

    mpv2.add_distancereading(make_degree_angle(0), dist);
    mpv2.add_distancereading(make_degree_angle(3), dist);
    mpv2.add_distancereading(make_degree_angle(5), dist);
    mpv2.add_distancereading(make_degree_angle(6), dist);
    mpv2.add_distancereading(make_degree_angle(356), dist);
    mpv2.add_distancereading(make_degree_angle(357), dist);
    mpv2.add_distancereading(make_degree_angle(358), dist);
    mpv2.add_distancereading(make_degree_angle(359), dist);
    std::map<int, DistanceReading> map2 = mpv2.get_distances();

    EXPECT_EQ(mpv1.match(mpv2), 100);
    EXPECT_NE(mpv1.match(mpv2), 99.9);
    EXPECT_EQ(mpv1.match(mpv1), 100);

    mpv1.add_distancereading(make_degree_angle(359), dist2);
    map1 = mpv1.get_distances();
    EXPECT_NE(mpv1.match(mpv2), 100);
}
//DONE
TEST(MapPolarView, find_best_match){
    MapPolarView mpv = MapPolarView();
    MapPolarView pv = MapPolarView();

    DistanceReading dist = DistanceReading(5*Length::METER,
                                           DistanceReading::ResultType::CHECKED);
    DistanceReading dist2 = DistanceReading(10*Length::METER,
                                            DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(make_degree_angle(0), dist);
    mpv.add_distancereading(make_degree_angle(3), dist);
    mpv.add_distancereading(make_degree_angle(5), dist);
    mpv.add_distancereading(make_degree_angle(6), dist);
    mpv.add_distancereading(make_degree_angle(356), dist);
    mpv.add_distancereading(make_degree_angle(357), dist);
    mpv.add_distancereading(make_degree_angle(358), dist);
    mpv.add_distancereading(make_degree_angle(359), dist);

    pv.add_distancereading(make_degree_angle(0), dist2);
    pv.add_distancereading(make_degree_angle(3), dist2);
    pv.add_distancereading(make_degree_angle(5), dist2);
    pv.add_distancereading(make_degree_angle(6), dist2);
    pv.add_distancereading(make_degree_angle(356), dist2);
    pv.add_distancereading(make_degree_angle(357), dist2);
    pv.add_distancereading(make_degree_angle(358), dist2);
    pv.add_distancereading(make_degree_angle(359), dist2);

    pv.rotate(make_degree_angle(20));

    std::tuple<Angle, double> result = mpv.find_best_match(pv);
    std::tuple<Angle, double> testResult = std::make_tuple(make_degree_angle(20), 2.0);
    int resultAngle = get_degree_angle(get<0>(result));
    int testResultAngle = get_degree_angle(get<0>(testResult));

    EXPECT_EQ(resultAngle, testResultAngle);
    EXPECT_EQ(get<1>(result), get<1>(testResult));
}
