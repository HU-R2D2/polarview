//! \addtogroup 0012 Polar view
//! \brief A polar view is a 360 degree view around a point.
//!
//! A polar view is what a distance meter sees if it is turned around to
//! look in all directions: for each direction (angle) a distance to the
//! nearest object (for now we ‘think’ in 2D only). Such a view could be
//! delivered from a Lidar, or from a robot, with an UltraSonic distance
//! sensor, by turning around its axis.
//!
//! \file   MapPolarViewTest.cpp
//! \author Aydin Biber - 1666849, Jasper van hulst - 1660498,
//!         Christiaan van de Berg - 1660475, Dimitry Volker - 1661152
//! \date   Created: 07-04-2016
//! \date   Last Modified: 25-04-2016
//!
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht.
//! All rights reserved.
//!
//! License: newBSD
//!
//! Redistribution and use in source and binary forms,
//! with or without modification, are permitted provided that
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht
//!   nor the names of its contributors may be used to endorse or promote
//!   products derived from this software without specific prior written
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~

#include "gtest/gtest.h"
#include "../source/include/MapPolarView.hpp"
#include <stdlib.h>

r2d2::Angle make_degree_angle(int angle){
    r2d2::Angle a = angle * r2d2::Angle::deg;
    return a;
}

int get_degree_angle(r2d2::Angle angle){
    int degrees = round(angle.get_angle() * (180 / M_PI));
    return degrees;
}

//Temporary implemented to check 2 lengths with a offset.
//Will be replaced by ADT comparator lateron.
bool length_range(r2d2::Length len1, r2d2::Length len2, double offset = 0.0001){
    return ((len1 - (offset * r2d2::Length::METER)) < len2) &&
     (len2 < (len1 + (offset * r2d2::Length::METER)));
}

TEST(MapPolarView, Constructor){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
}

TEST(MapPolarView, get_distance){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::Length len1 = 6*r2d2::Length::METER;
    r2d2::Length len2 = 3*r2d2::Length::METER;

    r2d2::DistanceReading distRead1(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead2(len2,
                                    r2d2::DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(r2d2::Angle(10*r2d2::Angle::deg), distRead1);

    mpv.add_distancereading(r2d2::Angle(370*r2d2::Angle::deg), distRead2);

    EXPECT_TRUE(length_range(mpv.get_distance(10*r2d2::Angle::deg).get_length()
                            ,distRead1.get_length())) <<
                             "incorrect DistanceReading";
    EXPECT_TRUE(length_range(mpv.get_distance(370*r2d2::Angle::deg).get_length()
                            ,distRead2.get_length())) <<
                        "incorrect DistanceReading";

    EXPECT_TRUE(length_range(mpv.get_distance(15*r2d2::Angle::deg).get_length()
                            ,0*r2d2::Length::METER)) <<
                     "incorrect DistanceReading";

}

//DONE
TEST(MapPolarView, Collapse){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::Length len1 = 12*r2d2::Length::METER;
    r2d2::Length len2 = 9*r2d2::Length::METER;
    r2d2::Length len3 = 6*r2d2::Length::METER;
    r2d2::Length len4 = 3*r2d2::Length::METER;

    r2d2::DistanceReading distRead1(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead2(len2,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead3(len3,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead4(len4,
                                    r2d2::DistanceReading::ResultType::CHECKED);

   //Checks it doesn't override the same angle which already has a value
    mpv.add_distancereading(r2d2::Angle(10*r2d2::Angle::deg), distRead1);

    mpv.add_distancereading(r2d2::Angle(370*r2d2::Angle::deg), distRead2);
    //checks if current values are kept.
    mpv.add_distancereading(r2d2::Angle(20*r2d2::Angle::deg), distRead3);
    //checks if outside range value is merged
    mpv.add_distancereading(r2d2::Angle(375*r2d2::Angle::deg), distRead4);

    mpv.collapse();
    std::map<r2d2::Angle, r2d2::DistanceReading> map = mpv.get_distances();


    EXPECT_TRUE(length_range(mpv.get_distance(
                             r2d2::Angle(10*r2d2::Angle::deg)).get_length(),
                             distRead1.get_length())) <<
                             "got overridden by outside value";
    EXPECT_TRUE(length_range(mpv.get_distance(
                             r2d2::Angle(20*r2d2::Angle::deg)).get_length(),
                             distRead3.get_length())) << "check of kept value";
    EXPECT_TRUE(length_range(mpv.get_distance(
                             r2d2::Angle(15*r2d2::Angle::deg)).get_length(),
                             distRead4.get_length())) <<
                             "check if collapse value addded";
    EXPECT_FALSE(map.count(r2d2::Angle(375*r2d2::Angle::deg)) > 0) <<
                             "outside value has been deleted";
}
//DONE
TEST(MapPolarView, Scale){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::Length len1 = 6*r2d2::Length::METER;
    r2d2::DistanceReading distRead1(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    mpv.add_distancereading(make_degree_angle(10), distRead1);

  //  std::map<r2d2::Angle, DistanceReading>& map = mpv.get_distances();

    mpv.scale(2); // multiplication test
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(10)).get_length(),len1 * 2));

    mpv.scale(0.5); // division test
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(10)).get_length(), len1));
}
//DONE
TEST(MapPolarView, addAssignOperator){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::MapPolarView mv = r2d2::MapPolarView();
    r2d2::Length len1 = 6*r2d2::Length::METER;
    r2d2::Length len2 = 3*r2d2::Length::METER;
    r2d2::DistanceReading distRead1(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead2(len2,
                                    r2d2::DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(make_degree_angle(10), distRead1);
    mv.add_distancereading(make_degree_angle(10), distRead2);

    mpv.add_distancereading(make_degree_angle(20), distRead1);
    mv.add_distancereading(make_degree_angle(30), distRead2);

    mpv += mv;


    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(10)).get_length(), len1));
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(20)).get_length(), len1));
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(30)).get_length(), len2));
}
//DONE
TEST(MapPolarView, addOperator){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::MapPolarView mv = r2d2::MapPolarView();
    r2d2::Length len1 = 6*r2d2::Length::METER;
    r2d2::Length len2 = 3*r2d2::Length::METER;
    r2d2::DistanceReading distRead1(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead2(len2,
                                    r2d2::DistanceReading::ResultType::CHECKED);

    mpv.add_distancereading(make_degree_angle(10), distRead1);
    mv.add_distancereading(make_degree_angle(10), distRead2);

    mpv.add_distancereading(make_degree_angle(20), distRead1);
    mv.add_distancereading(make_degree_angle(30), distRead2);


    auto copyMap = mpv + mv;

    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(10)).get_length(), len1));
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(20)).get_length(), len1));
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(30)).get_length(),
                             r2d2::Length()));

    EXPECT_TRUE(length_range(copyMap->get_distance(
                            make_degree_angle(10)).get_length(), len1));
    EXPECT_TRUE(length_range(copyMap->get_distance(
                            make_degree_angle(20)).get_length(), len1));
    EXPECT_TRUE(length_range(copyMap->get_distance(
                            make_degree_angle(30)).get_length(), len2));

}

//DONE
TEST(MapPolarView, add_distancereadingOne){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::Length len1 = 3 * r2d2::Length::METER;

    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(0)).get_length(),r2d2::Length()));
    mpv.add_distancereading(make_degree_angle(0), len1,
                            r2d2::DistanceReading::ResultType::CHECKED);
    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(0)).get_length(), len1));

}
//DONE
TEST(MapPolarView, add_distancereadingTwo){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::Length len1 = 3 * r2d2::Length::METER;

    EXPECT_TRUE(length_range(mpv.get_distance(
                            make_degree_angle(0)).get_length(),r2d2::Length()));
    r2d2::DistanceReading distRead(len1,
                            r2d2::DistanceReading::ResultType::CHECKED);
    mpv.add_distancereading(make_degree_angle(0), distRead);
    mpv.add_distancereading(make_degree_angle(600), distRead);
    EXPECT_TRUE(length_range(mpv.get_distance(make_degree_angle(600)).get_length(), len1));
    EXPECT_TRUE(length_range(mpv.get_distance(make_degree_angle(0)).get_length(), len1));
}
//DONE
TEST(MapPolarView, rotate){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    std::map<r2d2::Angle, r2d2::DistanceReading> testMap = mpv.get_distances();
    r2d2::Length len1 = 5*r2d2::Length::METER;
    r2d2::DistanceReading dist = r2d2::DistanceReading(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);

    int mapSize = testMap.size();
    mpv.add_distancereading(make_degree_angle(mapSize-12), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-11), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-10), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-9), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-8), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-7), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-6), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-5), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-4), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-3), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-2), dist);
    mpv.add_distancereading(make_degree_angle(mapSize-1), dist);
    mpv.add_distancereading(make_degree_angle(0), dist);
    mpv.add_distancereading(make_degree_angle(1), dist);
    mpv.add_distancereading(make_degree_angle(2), dist);
    mpv.add_distancereading(make_degree_angle(3), dist);
    mpv.add_distancereading(make_degree_angle(4), dist);
    mpv.add_distancereading(make_degree_angle(5), dist);

   // std::map<r2d2::Angle, DistanceReading>& map = mpv.get_distances();
    for(int i = mapSize-2; i < mapSize; i++){
        EXPECT_TRUE(length_range(mpv.get_distance(
                        r2d2::Angle(i * r2d2::Angle::deg)).get_length(), len1));
    }
    for(int i = 6; i < 15; i++){
        EXPECT_TRUE(length_range(mpv.get_distance(
              r2d2::Angle(i * r2d2::Angle::deg)).get_length(), r2d2::Length()));
    }

    mpv.rotate(make_degree_angle(10));

    for(int i = mapSize-12; i < mapSize-2; i++){
        EXPECT_TRUE(length_range(mpv.get_distance(
              r2d2::Angle(i * r2d2::Angle::deg)).get_length(), r2d2::Length()));
    }

    for(int i = 0; i < 15; i++){
        EXPECT_TRUE(length_range(mpv.get_distance(
                        r2d2::Angle(i * r2d2::Angle::deg)).get_length(), len1));
    }

}

// Test get_distances()
//  Test case for the get_distances() function
//  Create a MapPolarView object and get it's std::map.
//DONE
TEST(MapPolarView, get_distances) {
    r2d2::MapPolarView mpv;

    r2d2::Length len1 = 12*r2d2::Length::METER;
    r2d2::Length len2 = 9*r2d2::Length::METER;
    r2d2::Length len3 = 6*r2d2::Length::METER;
    r2d2::Length len4 = 3*r2d2::Length::METER;

    r2d2::DistanceReading distRead1(len1,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead2(len2,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead3(len3,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading distRead4(len4,
                                    r2d2::DistanceReading::ResultType::CHECKED);


    mpv.add_distancereading(r2d2::Angle(10*r2d2::Angle::deg), distRead1);
    mpv.add_distancereading(r2d2::Angle(370*r2d2::Angle::deg), distRead2);
    mpv.add_distancereading(r2d2::Angle(20*r2d2::Angle::deg), distRead3);
    mpv.add_distancereading(r2d2::Angle(375*r2d2::Angle::deg), distRead4);

    std::map<r2d2::Angle, r2d2::DistanceReading> map = mpv.get_distances();
    std::map<r2d2::Angle, r2d2::DistanceReading> testMap;

    testMap.insert(std::pair<r2d2::Angle, r2d2::DistanceReading>(
                   r2d2::Angle(10* r2d2::Angle::deg),
                   distRead1));
    testMap.insert(std::pair<r2d2::Angle, r2d2::DistanceReading>(
                   r2d2::Angle(370* r2d2::Angle::deg),
                   distRead2));
    testMap.insert(std::pair<r2d2::Angle, r2d2::DistanceReading>(
                   r2d2::Angle(20* r2d2::Angle::deg),
                   distRead3));
    testMap.insert(std::pair<r2d2::Angle, r2d2::DistanceReading>(
                   r2d2::Angle(375* r2d2::Angle::deg),
                   distRead4));

EXPECT_TRUE(length_range(map.at(r2d2::Angle(10 * r2d2::Angle::deg)).
                        get_length(),testMap.at(r2d2::Angle(10 *
                        r2d2::Angle::deg)).get_length()));
EXPECT_TRUE(length_range(map.at(r2d2::Angle(370 * r2d2::Angle::deg)).
                        get_length(),testMap.at(r2d2::Angle(370 *
                        r2d2::Angle::deg)).get_length()));
EXPECT_TRUE(length_range(map.at(r2d2::Angle(20 * r2d2::Angle::deg)).
                        get_length(),testMap.at(r2d2::Angle(20 *
                        r2d2::Angle::deg)).get_length()));
EXPECT_TRUE(length_range(map.at(r2d2::Angle(375 * r2d2::Angle::deg)).
                        get_length(),testMap.at(r2d2::Angle(375 *
                        r2d2::Angle::deg)).get_length()));


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
    r2d2::MapPolarView mpv1 = r2d2::MapPolarView();
    r2d2::MapPolarView mpv2 = r2d2::MapPolarView();
    r2d2::DistanceReading dist = r2d2::DistanceReading(5*r2d2::Length::METER,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading dist2 = r2d2::DistanceReading(4*r2d2::Length::METER,
                                    r2d2::DistanceReading::ResultType::CHECKED);

    mpv1.add_distancereading(make_degree_angle(0), dist);
    mpv1.add_distancereading(make_degree_angle(3), dist);
    mpv1.add_distancereading(make_degree_angle(5), dist);
    mpv1.add_distancereading(make_degree_angle(6), dist);
    mpv1.add_distancereading(make_degree_angle(356), dist);
    mpv1.add_distancereading(make_degree_angle(357), dist);
    mpv1.add_distancereading(make_degree_angle(358), dist);
    mpv1.add_distancereading(make_degree_angle(359), dist);
    std::map<r2d2::Angle, r2d2::DistanceReading> map1 = mpv1.get_distances();

    mpv2.add_distancereading(make_degree_angle(0), dist);
    mpv2.add_distancereading(make_degree_angle(3), dist);
    mpv2.add_distancereading(make_degree_angle(5), dist);
    mpv2.add_distancereading(make_degree_angle(6), dist);
    mpv2.add_distancereading(make_degree_angle(356), dist);
    mpv2.add_distancereading(make_degree_angle(357), dist);
    mpv2.add_distancereading(make_degree_angle(358), dist);
    mpv2.add_distancereading(make_degree_angle(359), dist);
    std::map<r2d2::Angle, r2d2::DistanceReading> map2 = mpv2.get_distances();

    EXPECT_EQ(mpv1.match(mpv2), 100);
    EXPECT_NE(mpv1.match(mpv2), 99.9);
    EXPECT_EQ(mpv1.match(mpv1), 100);

    mpv1.add_distancereading(make_degree_angle(359), dist2);
    map1 = mpv1.get_distances();
    EXPECT_NE(mpv1.match(mpv2), 100);
}
//DONE
TEST(MapPolarView, find_best_match){
    r2d2::MapPolarView mpv = r2d2::MapPolarView();
    r2d2::MapPolarView pv = r2d2::MapPolarView();

    r2d2::DistanceReading dist = r2d2::DistanceReading(5*r2d2::Length::METER,
                                    r2d2::DistanceReading::ResultType::CHECKED);
    r2d2::DistanceReading dist2 = r2d2::DistanceReading(10*r2d2::Length::METER,
                                    r2d2::DistanceReading::ResultType::CHECKED);

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

    std::tuple<r2d2::Angle, double> result = mpv.find_best_match(pv);
    std::tuple<r2d2::Angle, double> testResult =
                                   std::make_tuple(make_degree_angle(20), 2.0);
    int resultAngle = get_degree_angle(get<0>(result));
    int testResultAngle = get_degree_angle(get<0>(testResult));

    EXPECT_EQ(resultAngle, testResultAngle);
    EXPECT_EQ(get<1>(result), get<1>(testResult));
}
