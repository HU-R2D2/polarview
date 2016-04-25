//! \addtogroup 0012 Polar view
//! \brief A polar view is a 360 degree view around a point.
//!    
//! A polar view is what a distance meter sees if it is turned around to
//! look in all directions: for each direction (angle) a distance to the
//! nearest object (for now we ‘think’ in 2D only). Such a view could be
//! delivered from a Lidar, or from a robot, with an UltraSonic distance
//! sensor, by turning around its axis.         
//!
//! \file   MapPolarView.hpp
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

#ifndef _MAPPOLARVIEW_H
#define _MAPPOLARVIEW_H

#include "DistanceReading.hpp"
#include "../../../adt/source/include/Angle.hpp"
#include "PolarView.hpp"
#include <map>
#include <algorithm>
#include <tuple>
#include <vector>

class MapPolarView : public PolarView{
public:
    //Default constructor
    MapPolarView();

    //Collapses the PolarView into a PolarView
    // that contains every datapoint only once
    // For instance: when the robot spins twice, the values will
    // overlap at the 360th degree.
    // Collapse will get rid of the duplicate values.
    // However: when for example the 16th degree
    // wasn't captured and the 376th is available,
    // it will use that value instead.
    PolarView& collapse();

    //Rotates the PolarView with a given angle.
    void rotate(r2d2::Angle angle);

    //Matches the PolarView with a given PolarView
    //Returns a value that is a perentage that indicates how much
    //the PolarViews are alike.
    double match(PolarView& v);

    //Finds the best match with the given PolarView.
    //Returns the rotation and the multiplication factor
    //that best matches in a std::tuple
    std::tuple<r2d2::Angle, double> find_best_match(PolarView& v);

    //Returns all the distance readings in the polarview
    std::map<r2d2::Angle, DistanceReading> & get_distances();

    //Multiplies the distances with a given multiplier
    PolarView& scale(double frac);

    //  += operator
    //
    //  Adds 2 ArrayPolarviews together. This does not add
    //  two values together but rather 'merges' the two PolarViews
    //  \param MapPolarView
    //  \return
    PolarView& operator+=(PolarView& v);

    //  + operator
    //
    //  Adds 2 ArrayPolarviews together. This does not add
    //  two values together but rather 'merges' the two PolarViews
    //  \param MapPolarView
    //  \return
    PolarView& operator+(PolarView& v);

    void add_distancereading(r2d2::Angle angle, r2d2::Length len,
                             DistanceReading::ResultType type);
    void add_distancereading(r2d2::Angle angle, DistanceReading dist);

private:
    std::map <r2d2::Angle, DistanceReading> readings;

};

#endif //_MAPPOLARVIEW_H
