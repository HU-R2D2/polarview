#include <map>

namespace r2d2{

	class PolarView {
	public:
		//Collapse the PolarView into a PolarView that contains every datapoint only once.
		//For instance: when the robot spins twice, the values will
		//overlap at the 360th degree.
		//Collapse will get rid of the duplicate values.
		//However: when for example the 16th
		//degree wasn't captured and the 376th is available,
		//it will use that value instead.
		virtual PolarView& collapse() = 0;

		//Rotates the PolarView with a given angle
		virtual void rotate(r2d2::Angle angle) = 0;

		//Finds the best match with the given PolarView
		//Returns a value that is a percentage that indicates how much
		//the two PolarViews are alike
		virtual double match(PolarView& v) = 0;

		//Finds the best match with the given PolarView.
		//Returns the rotation and the multiplication factor that best matches in a
		//std::tuple
		virtual std::tuple<r2d2::Angle, double> find_best_match(PolarView& v) = 0;

		//Returns all distance readings in the PolarView
		virtual std::map<r2d2::Angle, DistanceReading> & get_distances() = 0;

		//Returns a DistanceReading at a specified angle
		virtual DistanceReading get_distance(r2d2::Angle angle) = 0;

		//Increase the distance readings in the PolarView with a factor growth
		virtual PolarView& scale(double frac) = 0;

		//Adds two PolarViews together. This does not add two values together
		//but rather 'merges' the two PolarViews
		virtual PolarView& operator+=(PolarView& v) = 0;

		//Adds two PolarViews together. This does not add two values together
		//but rather 'merges' the two PolarViews
		virtual PolarView& operator+(PolarView& v) = 0;

		//Add a distancereading with a set length to the map, using angle as key
		virtual void add_distancereading(r2d2::Angle angle, r2d2::Length len, DistanceReading::ResultType type) = 0;

		//Add a distancereading to the map, using angle as key
		virtual void add_distancereading(r2d2::Angle angle, DistanceReading dist) = 0;
	};

}
