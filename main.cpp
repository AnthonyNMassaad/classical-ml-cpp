#include "utils/logger.hpp"
#include <chrono>
#include <numeric>
#include "utils/file_io.hpp"
#include "preprocessing/split.hpp"
#include "models/knn/knn.hpp"
#include "utils/metrics.hpp"

using namespace std;

int main()
{
    vector<double> accuracies;
    vector<long long> times;

    for (int run = 1; run <= 20; run++)
    {
        auto program_start = chrono::high_resolution_clock::now();
        Log::print(Log::INFO, "Run " + to_string(run) + " started");

        // LOAD DATASET
        Log::startTimer("Load dataset");
        auto data = load_csv("datasets/iris.csv");
        Log::endTimer("Load dataset");

        // SPLIT
        Log::startTimer("Split dataset");
        vector<Sample> train, test;
        train_test_split(data, train, test);
        Log::endTimer("Split dataset");

        // KNN CLASSIFICATION
        Log::startTimer("KNN classification");
        KNN knn(5);
        auto predictions = knn.predict(train, test);
        Log::endTimer("KNN classification");

        // ACCURACY
        vector<int> trueLabels;
        for (auto &s : test)
            trueLabels.push_back(s.label);

        double acc = accuracy(trueLabels, predictions);
        accuracies.push_back(acc);
        Log::print(Log::SUCCESS, "Accuracy: " + to_string(acc * 100) + "%");

        // TOTAL TIME
        auto program_end = chrono::high_resolution_clock::now();
        long long total_ms =
            chrono::duration_cast<chrono::milliseconds>(program_end - program_start).count();

        times.push_back(total_ms);
        Log::print(Log::INFO, "Run time: " + to_string(total_ms) + " ms");
    }

    // ======== FINAL AVERAGES =========
    double avg_acc = accumulate(accuracies.begin(), accuracies.end(), 0.0) / accuracies.size();
    double avg_time = accumulate(times.begin(), times.end(), 0.0) / times.size();

    Log::print(Log::SUCCESS, "Average accuracy over 10 runs: " + to_string(avg_acc * 100) + "%");
    Log::print(Log::SUCCESS, "Average total runtime over 10 runs: " + to_string(avg_time) + " ms");

    return 0;
}
