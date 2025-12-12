#pragma once
#include "../utils/file_io.hpp"
using namespace std;

void train_test_split(const vector<Sample> &dataset, vector<Sample> &train, vector<Sample> &test, double test_ratio = 0.2);

void shuffle_data(std::vector<Sample>& data);