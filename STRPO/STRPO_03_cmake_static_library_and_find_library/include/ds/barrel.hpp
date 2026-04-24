#pragma once

namespace ds {

class Barrel {
public:
    Barrel();
    Barrel(double capacity_liters, double initial_liters = 0.0, double spirit_fraction = 0.0);

    static Barrel spirit_barrel(double capacity_liters, double fill_liters, double strength = 0.96);
    static Barrel water_barrel(double capacity_liters, double fill_liters);

    double capacity() const;
    double liters() const;
    double spirit_liters() const;
    double water_liters() const;
    double spirit_fraction() const;
    double free_space() const;
    bool empty() const;

    void fill(double liters, double spirit_fraction = 0.0);
    double pour_to(Barrel& other, double liters);

    static int iteration_until_fraction_below(Barrel first, Barrel second,
                                              double mug_liters,
                                              double threshold_fraction = 0.5);

private:
    double capacity_liters_;
    double liters_;
    double spirit_liters_;
};

}  // namespace ds
