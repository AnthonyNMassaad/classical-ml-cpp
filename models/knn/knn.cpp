#include "knn.hpp"
#include <cmath>
#include <algorithm>
using namespace std;

KNN::KNN(int k) : k(k) {}

double KNN::distance(const vector<double> &x, const vector<double> &y) const
{
    double sum = 0.0;
    for (int i = 0; i < x.size(); ++i)
    {
        sum += (x[i] - y[i]) * (x[i] - y[i]);
    }
    return sqrt(sum);
}

int KNN::predictOne(const vector<Sample> &train, const vector<double> &x) const
{
    vector<pair<double, int>> distances;

    for (auto &sample : train)
    {
        double dist = distance(sample.features, x);
        distances.push_back({dist, sample.label});
    }

    sort(distances.begin(), distances.end(), [](auto& a, auto& b) { return a.first < b.first; });

    vector<int> votes(3, 0);

    for (int i = 0; i < k; i++)
    {
        votes[distances[i].second]++;
    }

    return max_element(votes.begin(), votes.end()) - votes.begin();
}

vector<int> KNN::predict(const vector<Sample> &train, const vector<Sample> &test) const
{
    vector<int> predictions;
    for (auto &sample : test)
    {
        int pred = predictOne(train, sample.features);
        predictions.push_back(pred);
    }
    return predictions;
}