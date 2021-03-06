//! \addtogroup 0012 Polar view
//! \brief A polar view is a 360 degree view around a point.
//!
//! A polar view is what a distance meter sees if it is turned around to
//! look in all directions: for each direction (angle) a distance to the
//! nearest object (for now we ‘think’ in 2D only). Such a view could be
//! delivered from a Lidar, or from a robot, with an UltraSonic distance
//! sensor, by turning around its axis.
//!
//! \file   DistanceReading.hpp
//! \author Aydin Biber - 1666849, Jasper van hulst - 1660498,
//!         Christiaan van de Berg - 1660475, Dimitry Volker - 1661152
//! \date   Created: 07-04-2016
//! \date   Last Modified: 25-04-2016
//! \brief  A container for the length and the state of that length.
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

#ifndef DISTANCEREADING_H
#define DISTANCEREADING_H

#include "Length.hpp"

namespace r2d2{
    class DistanceReading {
    public:
        enum class ResultType {
            DIDNT_CHECK,
            OUT_OF_RANGE,
            CHECKED
        };

        //  DistanceReading constructor
        DistanceReading(r2d2::Length len, ResultType type);

        //  set_result_type
        //
        //  Setter for the ResultType object
        //  \param ResultType What type the distancereading has to be set to.
        void set_result_type(ResultType t);

        //  get_result_type

        //  Getter for the ResultType object
        //  \return returns the resulttype of the distancereading
        const ResultType & get_result_type() const;

        //  set_length
        //
        //  Setter for the Length object
        //  \param Length The length it has to be set to.
        void set_length(r2d2::Length len);

        //  get_distance
        //
        //  Getter for the Length object
        //  \return Returns the length of the distancereading
        const r2d2::Length & get_length() const;

    private:
        r2d2::Length length;
        ResultType type;
    };
}
#endif // DISTANCEREADING_H
