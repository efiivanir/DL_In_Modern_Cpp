#include <eigen3/Eigen/Dense>
#include "glorot.h"
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <numeric>

int main() {
    int fan_in = 6;
    int fan_out = 5;

    auto weigths = glorot_initializer(fan_in, fan_out);

    const std::size_t N = weigths.size();

    const auto welcome_message =
        fmt::format("fan_in {} fan_out {}\n", fan_in, fan_out);
    spdlog::info(welcome_message);

    const auto sum = static_cast<float>(std::accumulate(weigths.begin(),
                                                    weigths.end(), 0.0));
    float weight_mean = sum / static_cast<float>(N);

    float acc = 0.0;

    auto differ = [&acc, &weight_mean](const float val) {
        const float diff = val - weight_mean;
        acc += diff * diff;
        const auto dif_fmt = fmt::format("acc {} weight_mean {} diff {} val {}",
            acc, weight_mean, diff, val);
        // spdlog::info(dif_fmt);

    };

    std::for_each(weigths.begin(), weigths.end(), differ);

    float actual_stdev = std::sqrt(acc / static_cast<float>(N - 1));

    const auto expected_stddev = static_cast<float>(std::sqrt(2. / (fan_in + fan_out)));

    bool std_dev_rejected = chi_squared_test(expected_stddev,
        actual_stdev, static_cast<int>(N), 0.05);

    if (std_dev_rejected) {
        spdlog::warn("The weights standard deviation do not look like expected by the Glorot initializer");
    }

    bool mean_rejected = t_test(0., weight_mean, actual_stdev, static_cast<int>(N), 0.05);

    if (mean_rejected) {
        spdlog::warn("The weights mean do not look like expected by the Glorot initializer");
    }


}
