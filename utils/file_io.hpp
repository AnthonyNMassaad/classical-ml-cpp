#pragma once
#include <vector>
#include <string>
using namespace std;

struct Sample
{
    vector<double> features;
    int label;
};

vector<Sample> load_csv(const string &filename);