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
        readings.insert(std::pair<int, DistanceReading>
                        (i, DistanceReading(
                                DistanceReading(
                                    Length(),
                                    DistanceReading::ResultType::DIDNT_CHECK
                                )
                            )
                        )
                       );
    }
}

MapPolarView MapPolarView::collapse() {
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

void MapPolarView::rotate(int angle){
    std::map<int, DistanceReading> buffer;
    for(int i = 0; i <= angle; i++){
        buffer.insert(std::pair<int,DistanceReading>(i, readings.at(readings.size()-1+i-angle)));
    }
    for(int i = readings.size()-1; i > 0+angle; i--){
        readings.at(i) = readings.at(i-angle);
    }
    for(int i = 0; i < buffer.size(); i++){
        readings.at(i) = buffer.at(i);
    }
}

double MapPolarView::match(MapPolarView v) {
    double c = 0;
    double len1, len2;
    double offset = 0.0001;
    for(int i = 0; i < 360; i++) {
        len1 = (readings.at(i).get_length() / Length::METER);
        len2 = (v.get_distances().at(i).get_length() / Length::METER);

        if(((len1  - offset) < len2) && (len2 < (len1  + offset))) {
            c++;
        }
    }
    return (c/360)*100;
}

std::tuple<int, double> MapPolarView::find_best_match(MapPolarView v) {
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
            rotate(rotateFactor);
        }
        readings = readingsBackup;
    }
    return std::tuple<int, double>(bestRotation, bestScale);
}

std::map<int, DistanceReading> & MapPolarView::get_distances() {
    return readings;
}


    // std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;

MapPolarView MapPolarView::scale(double frac) {
    for(int i = 0; i < 360; i++) {
        DistanceReading & temp = readings.at(i);
        temp.set_length(temp.get_length() * frac);
    }
    return (*this);
}

// At the moment it assumes both PolarViews have the same starting point
MapPolarView MapPolarView::operator+=(MapPolarView v) {
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

MapPolarView MapPolarView::operator+(MapPolarView v) {
    MapPolarView retPV = (*this);
    return retPV += v;
}

void MapPolarView::add_distancereading(int angle,
                                       Length len,
                                       DistanceReading::ResultType type
                                      ) {
    if(readings.count(angle) > 0) {
        readings.at(angle).set_length(len);
        readings.at(angle).set_result_type(type);
    } else {
		readings.insert(std::pair<int, DistanceReading>(angle,
                                                        DistanceReading(len,
                                                                        type
                                                                        )
                                                        )
                        );
	}
}

void MapPolarView::add_distancereading(int angle, DistanceReading dist) {
    if(readings.count(angle) > 0) {
        readings.at(angle) = dist;
    } else {
		readings.insert(std::pair<int, DistanceReading>(angle, dist));
	}
}
