#include <map>

class PolarView {
public:
    virtual PolarView& collapse() = 0;

    virtual void rotate(r2d2::Angle angle) = 0;

    virtual double match(PolarView& v) = 0;

    virtual std::tuple<r2d2::Angle, double> find_best_match(PolarView& v) = 0;

    virtual std::map<int, DistanceReading> & get_distances() = 0;

    virtual PolarView& scale(double frac) = 0;

    virtual PolarView& operator+=(PolarView& v) = 0;

    virtual PolarView& operator+(PolarView& v) = 0;

    virtual void add_distancereading(r2d2::Angle angle, r2d2::Length len, DistanceReading::ResultType type) = 0;

    virtual void add_distancereading(r2d2::Angle angle, DistanceReading dist) = 0;
};
