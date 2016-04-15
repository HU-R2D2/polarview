////
// Roborescue
//
// \file DistanceReading.hpp
// \date Created: 07-04-2016
// \version 1.0.0
//
// \author Aydin Biber, Jasper van hulst, Christiaan van de Berg, Dimitry Volker
//
// \section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms,
// with or without modification, are permitted
// provided that the following conditions are met:
// - Redistributions of source code must retain the
// above copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce
// the above copyright notice, this list of conditions
// and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht
// nor the names of its contributors may be used to
// endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
// HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE
// HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
////
#include "../include/MapPolarView.hpp"
#include "../include/DistanceReading.hpp"

MapPolarView::MapPolarView() {
    for(int i = 0; i < 360; i++) {
        readings.insert(std::pair<int, DistanceReading>(
							i,
							DistanceReading(
                                DistanceReading(
                                    r2d2::Length(),
                                    DistanceReading::ResultType::DIDNT_CHECK
                                )
                            )
                        )
                        );
    }
}

PolarView& MapPolarView::collapse() {
	std::vector<int> keyValues;
	for(auto & angle: readings) {
		if(angle.first > 359){
			keyValues.push_back(angle.first);
		}
	}
	for(auto & extraAngle: keyValues) {
		DistanceReading & tbAdd = readings.at(extraAngle);
		DistanceReading & temp = readings.at(extraAngle % 360);
		if(temp.get_result_type() != DistanceReading::ResultType::CHECKED) {
			temp.set_length(tbAdd.get_length());
		}
		readings.erase(extraAngle);
	}
	return (*this);
}

void MapPolarView::rotate(r2d2::Angle angle){
    int degrees = round(angle.get_angle() * (180 / M_PI));

    std::map<int, DistanceReading> buffer;
    for(int i = 0; i <= degrees; i++){
        buffer.insert(std::pair<int,DistanceReading>(i, readings.at(readings.size()-1+i-degrees) ));
    }
    for(int i = readings.size()-1; i > 0+degrees; i--){
        readings.at(i) = readings.at(i-degrees);
    }
    for(int i = 0; i < buffer.size(); i++){
        readings.at(i) = buffer.at(i);
    }
}

double MapPolarView::match(PolarView& v) {
    double c = 0;
    double len1, len2;
    double offset = 0.0001; // Precise value to measure by
    for(int i = 0; i < 360; i++) {
        len1 = (readings.at(i).get_length() / r2d2::Length::METER);
        len2 = (v.get_distances().at(i).get_length() / r2d2::Length::METER);

        if(((len1  - offset) < len2) && (len2 < (len1  + offset))) {
            c++;
        }
    }
    return (c/360)*100;
}

std::tuple<r2d2::Angle, double> MapPolarView::find_best_match(PolarView& v){
    int rotateFactor = 1 ;
    double scaleFactor = 0.5;
    double preifmatch;

    int bestRotation;
    double bestScale;
    double bestMatch;
    std::map<int, DistanceReading> readingsBackup = readings;
    for(double d = scaleFactor; d <= 2 ; d+=scaleFactor) {
        scale(d);
        for(int i = 0; i < 360/rotateFactor; i++){
            preifmatch = match(v);
            if(preifmatch > bestMatch){
                bestRotation = i;
                bestMatch = preifmatch;
                bestScale = d;

            }
            r2d2::Angle rotateAngle = rotateFactor * r2d2::Angle::deg;
            rotate(rotateAngle);
        }
        readings = readingsBackup;
    }
    r2d2::Angle bestAngle = bestRotation * r2d2::Angle::deg;
    return std::tuple<r2d2::Angle, double>(bestAngle, bestScale);
}

std::map<int, DistanceReading> & MapPolarView::get_distances() {
    return readings;
}


    // std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;

PolarView& MapPolarView::scale(double frac) {
    for(int i = 0; i < 360; i++) {
        DistanceReading & temp = readings.at(i);
        temp.set_length(temp.get_length() * frac);
    }
    return (*this);
}

// At the moment it assumes both PolarViews have the same starting point
PolarView& MapPolarView::operator+=(PolarView& v) {
    std::map<int, DistanceReading> tbadd = v.get_distances();
    for(int i = 0; i < 360; i++){
        DistanceReading & temp = readings.at(i);
        if(temp.get_result_type() !=
           DistanceReading::ResultType::CHECKED) {
            DistanceReading addtemp = tbadd.at(i);

            if(addtemp.get_result_type() ==
               DistanceReading::ResultType::CHECKED) {
                temp.set_length(addtemp.get_length());
                temp.set_result_type(addtemp.get_result_type());
            }
        }
    }
    return (*this);
}

PolarView& MapPolarView::operator+(PolarView& v) {
    MapPolarView retPV = (*this);
    return retPV += v;
}

void MapPolarView::add_distancereading(r2d2::Angle angle, r2d2::Length len, DistanceReading::ResultType type){
    int degrees = round(angle.get_angle() * (180 / M_PI));
    if(readings.count(degrees) > 0){
        readings.at(degrees).set_length(len);
        readings.at(degrees).set_result_type(type);
    }
	else{
		readings.insert(std::pair<int, DistanceReading>(degrees, DistanceReading(len, type)));
	}
}
void MapPolarView::add_distancereading(r2d2::Angle angle, DistanceReading dist){
    int degrees = round(angle.get_angle() * (180 / M_PI));
    if(readings.count(degrees) > 0){
        readings.at(degrees) = dist;
    }
	else{
		readings.insert(std::pair<int, DistanceReading>(degrees, dist));
	}
}
