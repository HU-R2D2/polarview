#include <map>

class PolarView {
public:
    virtual PolarView& collapse() = 0;

    virtual void rotate(Angle angle) = 0;

    virtual double match(PolarView& v) = 0;

    virtual std::tuple<Angle, double> find_best_match(PolarView& v) = 0;

    virtual std::map<int, DistanceReading> & get_distances() = 0;

    virtual PolarView& scale(double frac) = 0;

    virtual PolarView& operator+=(PolarView& v) = 0;

    virtual PolarView& operator+(PolarView& v) = 0;

    virtual void add_distancereading(Angle angle, Length len, DistanceReading::ResultType type) = 0;

    virtual void add_distancereading(Angle angle, DistanceReading dist) = 0;
};
