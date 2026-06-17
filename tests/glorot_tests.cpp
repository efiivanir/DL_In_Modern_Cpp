#include <gtest/gtest.h>

#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/distributions/students_t.hpp>

#include <cstddef>
#include <numeric>

#include "glorot.h"


TEST(CheckGlorot, StatCases) {
    int fan_in = 6;
    int fan_out = 5;

    auto weigths = glorot_initializer(fan_in, fan_out);

    const std::size_t N = weigths.size();

    EXPECT_EQ(N, fan_in * fan_out);

    const auto sum = static_cast<float>(std::accumulate(weigths.begin(), weigths.end(), 0.0));
    float weight_mean = sum / static_cast<float>(N);

    float acc = 0.0;

    auto differ = [&acc, &weight_mean](const float val) {
        const float diff = val - weight_mean;
        acc += diff * diff;
    };

    std::for_each(weigths.begin(), weigths.end(), differ);

    float actual_stdev = std::sqrt(acc / static_cast<float>(N - 1));

    const auto expected_stddev = static_cast<float>(std::sqrt(2. / (fan_in + fan_out)));

    bool std_dev_rejected = chi_squared_test(expected_stddev, actual_stdev, static_cast<int>(N), 0.05);

    if (std_dev_rejected) {
        FAIL() << "The weights standard deviation do not look like expected by the Glorot initializer";
    }

    bool mean_rejected = t_test(0., weight_mean, actual_stdev, static_cast<int>(N), 0.05);

    if (mean_rejected) {
        FAIL() << "The weights mean do not look like expected by the Glorot initializer";
    }
}
