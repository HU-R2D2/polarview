//! \addtogroup 0012 Polar view
//! \brief A polar view is a 360 degree view around a point.
//!
//! A polar view is what a distance meter sees if it is turned around to
//! look in all directions: for each direction (angle) a distance to the
//! nearest object (for now we ‘think’ in 2D only). Such a view could be
//! delivered from a Lidar, or from a robot, with an UltraSonic distance
//! sensor, by turning around its axis.
//!
//! \file   MapPolarView.cpp
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

#include "../include/MapPolarView.hpp"
#include "../include/DistanceReading.hpp"

namespace r2d2{

	bool angle_range(r2d2::Angle angle1, r2d2::Angle angle2,
		double offset = 0.0001){
		return ((angle1 - (offset * r2d2::Angle::rad)) < angle2) &&
			(angle2 < (angle1 + (offset * r2d2::Angle::rad)));
	}

	PolarView& MapPolarView::collapse(){

		std::vector<r2d2::Angle> keyValues;
		r2d2::Angle circle(M_PI * 2 * r2d2::Angle::rad);
		for (const auto & angle : readings){
			if (r2d2::Angle(angle.first) > circle){
				keyValues.push_back(angle.first);
			}
		}
		for (const auto & extraAngle : keyValues){
			r2d2::Angle adjustedAngle(extraAngle);

			while (adjustedAngle > circle){
				adjustedAngle -= circle;
			}

			bool used = false;
			for (const auto & read : readings){
				r2d2::Angle angle(read.first);
				if (angle_range(adjustedAngle, angle)){
					used = true;
					DistanceReading & tbAdd = readings.at(extraAngle);
					DistanceReading & temp = readings.at(angle);
					if (temp.get_result_type() !=
						DistanceReading::ResultType::CHECKED) {
						temp.set_length(tbAdd.get_length());
					}
					readings.erase(extraAngle);

				}
			}
			if (!used) {
				int angle = round(adjustedAngle.get_angle() * (180 / M_PI));
				readings.insert(std::pair<r2d2::Angle, DistanceReading>(r2d2::Angle(angle*r2d2::Angle::deg),
					readings.at(extraAngle)));
				readings.erase(extraAngle);
			}

		}

		return (*this);
	}

	void MapPolarView::rotate(r2d2::Angle angle){
		int degrees = round(angle.get_angle() * (180 / M_PI));

		std::map<r2d2::Angle, DistanceReading> buffer;

		for (auto i : readings){
			r2d2::Angle adjAngle(i.first + angle);
			buffer.insert(std::pair<r2d2::Angle, DistanceReading>
				(adjAngle, i.second));
		}

		readings.clear();

		readings = buffer;
	}

	double MapPolarView::match(PolarView& v) {
		double count = 0;
		double len1, len2;
		double offset = 0.0001; // Precise value to measure by
		std::map<r2d2::Angle, DistanceReading> compMap = v.get_distances();
		for (const auto & read : readings){
			len1 = (readings.at(read.first).get_length() /
				r2d2::Length::METER);
			for (const auto & compare : compMap){
				if (angle_range(compare.first, read.first)){
					DistanceReading temp = compare.second;
					len2 = temp.get_length() / r2d2::Length::METER;
					break;
				}
			}

			if (((len1 - offset) < len2) && (len2 < (len1 + offset))) {
				count++;
			}
		}
		return (count / readings.size()) * 100;
	}

	std::tuple<r2d2::Angle, double> MapPolarView::find_best_match(PolarView& v){
		int rotateFactor = 1;
		double scaleFactor = 0.5;
		double preifmatch;

		//left unitialized these values are undefined
		int bestRotation = 0;
		double bestScale = 0;
		double bestMatch = 0;
		std::map<r2d2::Angle, DistanceReading> readingsBackup = readings;
		for (double d = scaleFactor; d <= 2; d += scaleFactor) {
			scale(d);
			for (int i = 0;
				i < ((readings.size() > 360) ? readings.size() : 360) / rotateFactor;
				i++){
				preifmatch = match(v);
				if (preifmatch > bestMatch){
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

	DistanceReading MapPolarView::get_distance(r2d2::Angle angle) {
		for (auto i : readings){
			if (angle_range(i.first, angle)){
				return readings.at(i.first);
			}
		}
		return DistanceReading(r2d2::Length(),
			DistanceReading::ResultType::DIDNT_CHECK);
	}

	std::map<r2d2::Angle, DistanceReading> & MapPolarView::get_distances() {
		return readings;
	}

	PolarView& MapPolarView::scale(double frac) {
		for (const auto & read : readings){
			DistanceReading & temp = readings.at(read.first);
			temp.set_length(temp.get_length() * frac);
		}
		return (*this);
	}

	PolarView& MapPolarView::operator+=(PolarView& v) {
		std::map<r2d2::Angle, DistanceReading> tbadd = v.get_distances();
		for (const auto & read : readings){
			DistanceReading & temp = readings.at(read.first);
			if (temp.get_result_type() !=
				DistanceReading::ResultType::CHECKED) {
				DistanceReading addtemp = tbadd.at(read.first);

				if (addtemp.get_result_type() ==
					DistanceReading::ResultType::CHECKED) {
					temp.set_length(addtemp.get_length());
					temp.set_result_type(addtemp.get_result_type());
				}
			}
			tbadd.erase(read.first);
		}
		for (const auto & read : tbadd){
			readings.insert(std::pair<r2d2::Angle, DistanceReading>(read.first,
				read.second));
		}

		return (*this);
	}

	PolarView& MapPolarView::operator+(PolarView& v) {
		MapPolarView retPV = (*this);
		MapPolarView& copyPV =
			*(new MapPolarView(static_cast<MapPolarView&>(retPV += v)));
		return copyPV;
	}

	void MapPolarView::add_distancereading(r2d2::Angle angle, r2d2::Length len,
		DistanceReading::ResultType type){
		if (readings.count(angle) > 0){
			readings.at(angle).set_length(len);
			readings.at(angle).set_result_type(type);
		}
		else{
			readings.insert(std::pair<r2d2::Angle, DistanceReading>(angle,
				DistanceReading(len, type)));
		}
	}
	void MapPolarView::add_distancereading(r2d2::Angle angle, DistanceReading dist){
		if (readings.count(angle) > 0){
			readings.at(angle) = dist;
		}
		else{
			readings.insert(std::pair<r2d2::Angle, DistanceReading>(angle, dist));
		}
	}

}