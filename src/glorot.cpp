#include "glorot.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <random>
#include <vector>

#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/distributions/students_t.hpp>

#include <numeric>


std::vector<float> glorot_initializer(int fan_in, int fan_out) {
    const std::size_t size = fan_in * fan_out;
    const auto stddev = static_cast<float>(std::sqrt(2. / (fan_in + fan_out)));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<float> distribution(.0, stddev);
    std::vector<float> result(size);
    std::generate(result.begin(), result.end(), [&generator, &distribution]() { return distribution(generator); });
    return result;
}

/**
 * The NULL hypothesis states sample_std eq population_std
 *
 * This function returns true if the NULL hypothesis was rejected
 */
bool chi_squared_test(float population_std, float sample_std, int sample_size, float alpha) {
    float variance_rate = sample_std / population_std;
    variance_rate = variance_rate * variance_rate;
    float t_stat = static_cast<float>(sample_size - 1) * variance_rate;

    boost::math::chi_squared distro(sample_size - 1);

    const auto upper_limit = static_cast<float>(quantile(complement(distro, alpha / 2)));
    const auto lower_limit = static_cast<float>(quantile(distro, alpha / 2));

    return t_stat > upper_limit && t_stat < lower_limit;
}

/**
 * The NULL hypothesis states sample_mean eq population_mean
 *
 * This function returns true if the NULL hypothesis was rejected
 */
bool t_test(float population_mean, float sample_mean, float sample_std_dev, int sample_size, float alpha) {
    float diff = sample_mean - population_mean;

    auto t_stat = static_cast<float>(diff * sqrt(double(sample_size)) / sample_std_dev);

    unsigned degree_of_freedom = sample_size - 1;
    boost::math::students_t distro(degree_of_freedom);
    const auto q = static_cast<float>(cdf(complement(distro, fabs(t_stat))));

    const auto alpha_2 = static_cast<float>(alpha / 2.);

    return q < alpha_2;
}
