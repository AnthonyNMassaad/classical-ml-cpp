#include "file_io.hpp"
#include <fstream>
#include <sstream>
using namespace std;

vector<Sample> load_csv(const string& filename) {
    vector<Sample> data;
    ifstream file(filename);
    string line;

    getline(file, line);

    while (getline(file, line)) {
        if (line.size() < 5) continue;

        stringstream ss(line);
        string val;

        Sample s;

        getline(ss, val, ',');

        for (int i = 0; i < 4; i++) {
            getline(ss, val, ',');
            s.features.push_back(stod(val));
        }

        getline(ss, val, ',');

        if (val == "Iris-setosa") s.label = 0;
        else if (val == "Iris-versicolor") s.label = 1;
        else if (val == "Iris-virginica") s.label = 2;
        else continue;

        data.push_back(s);
    }

    return data;
}
