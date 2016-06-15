#include "../source/include/DistanceReading.hpp"
#include "../source/include/MapPolarView.hpp"
#include "../source/include/PolarView.hpp"
#include "Angle.hpp"

int main(int ac, char* av[]){

// Creating length variables
r2d2::Length len1 = 6 * r2d2::Length::METER;
r2d2::Length len2 = 3 * r2d2::Length::METER;
r2d2::Length len3 = 5 * r2d2::Length::METER;

// creating distancereading objects
r2d2::DistanceReading distRead1(r2d2::DistanceReading(len2,
            r2d2::DistanceReading::ResultType::OUT_OF_RANGE));
r2d2::DistanceReading distRead2(len3,
            r2d2::DistanceReading::ResultType::CHECKED);

//creating mappolarview object
r2d2::MapPolarView mpv = r2d2::MapPolarView();
r2d2::MapPolarView mv = r2d2::MapPolarView();

//sets result type for distancereading object
r2d2::DistanceReading distRead3(r2d2::DistanceReading(len1,
            r2d2::DistanceReading::ResultType::DIDNT_CHECK));
distRead3.set_result_type(r2d2::DistanceReading::ResultType::OUT_OF_RANGE);

//depending on distancereading used checks values
mpv.add_distancereading(r2d2::Angle(10 * r2d2::Angle::deg), distRead1);
mv.add_distancereading(r2d2::Angle(370 * r2d2::Angle::deg), distRead2);

// erases all values aside fom the chosen ones
mpv.collapse();

// rotates objects
r2d2::Angle a = 10 * r2d2::Angle::deg;
mpv.rotate(a);

// scales polarview (doubles can be used)
mpv.scale(2); // multiplication
mpv.scale(0.5); // division

//This stores the map as copy. Any changes to the MapPolarView afterwards will
//not be visible with the map.
std::map<r2d2::Angle, r2d2::DistanceReading> map = mpv.get_distances();

//This will return a reference to the map. Any changes to the MapPolarView
//afterwards will still be visible with the map.
const std::map<r2d2::Angle, r2d2::DistanceReading> &map1 = mpv.get_distances();

}
