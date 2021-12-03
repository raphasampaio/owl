#pragma once

#ifndef OWL_MATH_H
#define OWL_MATH_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <limits>

namespace owl::math {
    inline int double_to_int(double value) {
        return (int)std::lround(value);
    }

    inline bool approximately_equal(double a, double b, double epsilon = 1e-4) {
        return std::abs(a - b) <= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
    }

    inline bool essentially_equal(double a, double b, double epsilon = 1e-4) {
        return std::abs(a - b) <= ((std::abs(a) > std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
    }

    inline bool definitely_greater_than(double a, double b, double epsilon = 1e-4) {
        return (a - b) > ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
    }

    inline bool definitely_less_than(double a, double b, double epsilon = 1e-4) {
        return (b - a) > ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
    }

    inline std::vector<std::pair<double, int>> vector_with_indices(std::vector<double>& v) {
        std::vector<std::pair<double, int>> pairs;
        for (size_t i = 0, size = v.size(); i < size; ++i) { pairs.push_back(std::make_pair(v[i], i)); }
        return pairs;
    }

    inline int nth_element(std::vector<double>& v, double alpha) {
        auto size = v.size();
        if (size == 1) { return 0; }

        auto pairs = owl::math::vector_with_indices(v);
        auto shift = (std::min)((std::size_t)std::floor((alpha * size) / 100), size - 1);

        auto nth = pairs.begin() + shift;
        std::nth_element(pairs.begin(), nth, pairs.end());
        return (*nth).second;
    }

    inline double quantile(std::vector<double>& v, double alpha) {
        if (v.size() == 0) return 0;

        auto nth = owl::math::nth_element(v, alpha);
        return v[nth];
    }

    inline double cvar(std::vector<double>& v, double alpha, bool left = true) {
        auto size = v.size();

        auto pairs = owl::math::vector_with_indices(v);
        auto shift = (std::max)((std::size_t)std::ceil((alpha * size) / 100), (std::size_t)1);

        if (left) {
            std::sort(std::begin(pairs), std::end(pairs));
        } else {
            std::sort(std::begin(pairs), std::end(pairs), std::greater<std::pair<double, int>>());
        }

        double sum = 0;
        for (size_t i = 0; i < shift; ++i) {
            sum += pairs[i].first;
        }
        return sum / shift;
    }

    inline double cvar_left(std::vector<double>& v, double alpha) {
        return cvar(v, alpha, true);
    }

    inline double cvar_right(std::vector<double>& v, double alpha) {
        return cvar(v, alpha, false);
    }

    inline double stddev(std::vector<double>& v) {
        auto size = v.size();
        if (size == 1) {
            return 0;
        }

        double sum = std::accumulate(v.begin(), v.end(), 0.0);
        double mean = sum / size;

        std::vector<double> difference(v.size());
        std::transform(v.begin(), v.end(), difference.begin(), [mean](double x) { return x - mean; });

        double square_sum = std::inner_product(difference.begin(), difference.end(), difference.begin(), 0.0);
        return std::sqrt(square_sum / (size - 1));
    }

    inline double round(double v, int digits) {
        return std::floor((v * std::pow(10.0, digits)) + .5) / std::pow(10.0, digits);
    }

    inline double significant_digits(double v, int digits) {
        if (v == 0.0) // otherwise it will return 'nan' due to the log10() of zero
            return 0.0;
        double factor = std::pow(10.0, digits - std::ceil(std::log10(std::fabs(v))));
        return std::round(v * factor) / factor;
    }

    inline std::pair<size_t, size_t> find_nearest(std::vector<double>& v, double t) {
        auto [min, max] = std::minmax_element(std::begin(v), std::end(v));

        auto lb = *min;
        size_t lb_index = min - std::begin(v);
        
        auto ub = *max;
        size_t ub_index = max - std::begin(v);

        for (size_t i = 0, size = v.size(); i < size; ++i) {
            int value = v[i];

            if (lb < value && value <= t) {
                lb = value;
                lb_index = i;
            } 
            
            if (t <= value && value < ub) {
                ub = value;
                ub_index = i;
            }
        }

        return std::make_pair(lb_index, ub_index);
    }

    inline double npv(std::vector<double>& v, double rate) {
        double sum = 0;
        for (size_t i = 0, size = v.size(); i < size; ++i) { sum += v[i] / std::pow(1.0 + rate, i + 1); }
        return sum;
    }

    inline double average(std::vector<double>& v) {
        auto size = v.size();
        return size == 0 ? 0 : (std::accumulate(std::begin(v), std::end(v), 0.0) / size);
    }

    inline double multiply(std::vector<double>& v) {
        auto size = v.size();
        return size == 0 ? 0 : std::accumulate(std::begin(v), std::end(v), 1.0, std::multiplies<double>());
    }

    inline double sum(std::vector<double>& v) {
        return std::accumulate(std::begin(v), std::end(v), 0.0);
    }

    inline double minimum(std::vector<double>& v) {
        return *std::min_element(std::begin(v), std::end(v));
    }

    inline double maximum(std::vector<double>& v) {
        return *std::max_element(std::begin(v), std::end(v));
    }
}

#endif