#pragma once
#include <vector>
#include "../../utils/file_io.hpp"
using namespace std;

class KNN
{
private:
    int k;
    double distance(const vector<double> &x, const vector<double> &y) const;

public:
    KNN(int k);
    int predictOne(const vector<Sample> &train, const vector<double> &x) const;

    vector<int> predict(const vector<Sample> &train, const vector<Sample> &test) const;
};