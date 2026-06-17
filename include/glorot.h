#pragma once
#include <vector>

float s(float z);

int find_median(const std::vector<int> &arr);

std::vector<float> glorot_initializer(int fan_in, int fan_out);

bool chi_squared_test(float population_std, float sample_std,
                    int sample_size, float alpha);

bool t_test(float population_mean, float sample_mean,
        float sample_std_dev, int sample_size, float alpha);

