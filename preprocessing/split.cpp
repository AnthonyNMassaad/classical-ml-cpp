#include "split.hpp"
#include <algorithm>
#include <random>
using namespace std;

void shuffle_data(vector<Sample>& data) {
    static random_device rd;
    static mt19937 g(rd());
    shuffle(data.begin(), data.end(), g);
}

void train_test_split(const vector<Sample> &dataset, vector<Sample> &train, vector<Sample> &test, double test_ratio)
{
    vector<Sample> shuffled_data = dataset;
    shuffle_data(shuffled_data);

    int split = shuffled_data.size() * (1 - test_ratio);

    train.assign(shuffled_data.begin(), shuffled_data.begin() + split);
    test.assign(shuffled_data.begin() + split, shuffled_data.end());
}