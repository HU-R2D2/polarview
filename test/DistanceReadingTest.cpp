//! \addtogroup 0012 Polar view
//! \brief A polar view is a 360 degree view around a point.
//!    
//! A polar view is what a distance meter sees if it is turned around to
//! look in all directions: for each direction (angle) a distance to the
//! nearest object (for now we ‘think’ in 2D only). Such a view could be
//! delivered from a Lidar, or from a robot, with an UltraSonic distance
//! sensor, by turning around its axis.         
//!
//! \file   DistanceReadingTest.cpp
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
#include "../source/include/DistanceReading.hpp"

//  Test set_result_type()
//
//  Test case for the set_result_type() function
//  Create a DistanceReading object, check it's ResultType,
//     set it's ResultType and check again.
 // Repeat for every possible ResultType.

TEST(DistanceReading, SetResultType) {

    r2d2::Length len;

    DistanceReading a(DistanceReading(len,
                                     DistanceReading::ResultType::DIDNT_CHECK));

    EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::DIDNT_CHECK);

    a.set_result_type(DistanceReading::ResultType::OUT_OF_RANGE);
    EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::OUT_OF_RANGE);

    a.set_result_type(DistanceReading::ResultType::CHECKED);
    EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::CHECKED);
}

//  Test get_result_type()
//
//  Test case for the get_result_type() function
//  Create multiple DistanceReading objects and compare their ResultType
//  against ResultType objects

TEST(DistanceReading, GetResultType) {
    r2d2::Length len;

    DistanceReading a(DistanceReading(len,
                                     DistanceReading::ResultType::DIDNT_CHECK));
    DistanceReading b(DistanceReading(len,
                                    DistanceReading::ResultType::OUT_OF_RANGE));
    DistanceReading c(DistanceReading(len,
                                      DistanceReading::ResultType::CHECKED));
    
    EXPECT_EQ(a.get_result_type(), DistanceReading::ResultType::DIDNT_CHECK);
    EXPECT_EQ(b.get_result_type(), DistanceReading::ResultType::OUT_OF_RANGE);
    EXPECT_EQ(c.get_result_type(), DistanceReading::ResultType::CHECKED);
}

 // Test set_length()
 //
 // Test case for the set_length() function
 // Create a DistanceReading object and get it's length object.
 // Check if this length is within range of another length.
 // Uses a very precise offset of (1000 * 1000 * 1000)
 // to see if 2 length's are equal

TEST(DistanceReading, SetDistance) {
    r2d2::Length len1(200 * r2d2::Length::METER);
    r2d2::Length len2(200 * r2d2::Length::METER);

    DistanceReading a(DistanceReading(len2,
                                     DistanceReading::ResultType::DIDNT_CHECK));
    r2d2::Length tempmax(a.get_length());
    // Extremely precise offset for measurement
    const r2d2::Length offset(len1 / (1000 * 1000 * 1000));

    // Lengths are both 200, so in range
    EXPECT_TRUE(((len1 - offset) < tempmax) && (tempmax < (len1 + offset)));

    // Set the length to a different value
    a.set_length(201 * r2d2::Length::METER);
    tempmax = a.get_length();

    // Length is no longer in range of 200, so it should be false
    EXPECT_FALSE(((len1 - offset) < tempmax) && (tempmax < (len1 + offset)));
}

//  Test get_length()
//
//  Test case for the get_length() function
//  Create a DistanceReading object and get it's length object.
//  Check if this length is within range of another length.

TEST(DistanceReading, GetDistance) {
    r2d2::Length len1(200 * r2d2::Length::METER);
    r2d2::Length len2(200.01 * r2d2::Length::METER);

    DistanceReading a(DistanceReading(len2,
                                     DistanceReading::ResultType::DIDNT_CHECK));
    r2d2::Length tempmax(a.get_length());

    const r2d2::Length offset(len1 / 10000);

    EXPECT_TRUE(((len1 - offset) < tempmax) && (tempmax < (len1 + offset)));
}
