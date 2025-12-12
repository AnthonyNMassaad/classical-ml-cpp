#include "metrics.hpp"
using namespace std;

double accuracy(const vector<int> &y_true, const vector<int> &y_pred)
{
    int correct = 0;

    for (int i = 0; i < y_true.size(); i++)
    {
        if (y_true[i] == y_pred[i])
        {
            correct++;
        }
    }

    return correct / (double)y_true.size();
}