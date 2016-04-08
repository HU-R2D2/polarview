class PolarView {
public:
    virtual PolarView collapse() = 0;

    virtual rotate(Angle angle) = 0;

    virtual double match(PolarView v) = 0;

    virtual std::tuple<Angle, double mul_fac> find_best_match(PolarView v) = 0;

    virtual std::map<Angle, DistanceReading> & get_distances() = 0;

    virtual PolarView scale(double frac) = 0;

    virtual PolarView operator+=(PolarView v) = 0;
    
    virtual PolarView operator+(PolarView v) = 0;

    virtual void add_distancereading(int angle, Length len, DistanceReading::ResultType type) = 0;

    virtual void add_distancereading(int angle, DistanceReading dist) = 0;
}