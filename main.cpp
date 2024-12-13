#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "validator.h"
#include "Classifier.h"
#include "Instance.h"
using namespace std;

// load the dataset
void loadDataset(const string& filePath, vector<Instance>& records) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        exit(1);
    }
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Instance instance;
        double value;

        ss >> value;
        instance.classifier = static_cast<int>(value);

        while (ss >> value) {
            instance.features.push_back(value);
        }

        records.push_back(instance);
    }

    if (!records.empty()) {
        cout << "Dataset loaded successfully with " << records.size() << " instances and "
             << records[0].features.size() << " features.\n";
    } else {
        cerr << "Error: Dataset is empty.\n";
        exit(1);
    }
}

void normalizeData(vector<Instance>& records) {
    if (records.empty()) return;

    int numFeatures = records[0].features.size();

    vector<double> max(numFeatures, numeric_limits<double>::lowest());
    vector<double> min(numFeatures, numeric_limits<double>::max());

    for (int i = 0; i < numFeatures; ++i) {
        for (const auto& record : records) {
            double value = record.features[i];
            if (value > max[i]) max[i] = value;
            if (value < min[i]) min[i] = value;
        }
    }

    for (auto& record : records) {
        for (int i = 0; i < numFeatures;++i) {
            if (max[i] != min[i]) {
                record.features[i] =(record.features[i] - min[i]) / (max[i] - min[i]);
            } else {
                record.features[i] = 0; 
            }
        }
    }
}

// Forward Selection Algorithm
void forwardSelection(Validator& validator, int numFeatures) {
    vector<int> currentFeatures;
    vector<int> bestSubset;
    double bestOverallAccuracy = 0.0;

    cout << "Beginning forward selection search...\n";

    for (int i = 0; i < numFeatures; i++) {
        int bestFeature = -1;
        double maxAccuracy = 0.0;

        for (int feature = 1; feature <= numFeatures; feature++) {
            if (find(currentFeatures.begin(), currentFeatures.end(), feature) == currentFeatures.end()) {
                vector<int> tempFeatures = currentFeatures;
                tempFeatures.push_back(feature);

                double accuracy = validator.validate(tempFeatures);
                cout << "Using feature(s) {";
                for (int f : tempFeatures) cout << f << ",";
                cout << "} accuracy is " << accuracy << "%\n";

                if (accuracy > maxAccuracy) {
                    maxAccuracy = accuracy;
                    bestFeature = feature;
                }

                if (accuracy > bestOverallAccuracy) {
                    bestOverallAccuracy = accuracy;
                    bestSubset = tempFeatures;
                }
            }
        }

        if (bestFeature != -1) {
            currentFeatures.push_back(bestFeature);
            cout << "\n";
            cout << "Feature set {";
            for (int f : currentFeatures) cout << f << ",";
            cout << "} was best, accuracy is " << maxAccuracy << "%\n\n";
        }
    }

    cout << "\nFinished search!! The best feature subset is {";
    for (int f : bestSubset) cout << f << ",";
    cout << "} with an accuracy of " << bestOverallAccuracy << "%\n";
}

// Backward Elimination Algorithm
void backwardElimination(Validator& validator, int numFeatures) {
    vector<int> currentFeatures;
    for (int i = 1; i <= numFeatures; i++) {
        currentFeatures.push_back(i);
    }

    double bestAccuracy = validator.validate(currentFeatures);
    vector<int> bestSubset = currentFeatures;

    cout << "Beginning backward elimination search...\n";
    cout << "Starting with all features: accuracy is " << bestAccuracy << "%\n";

    while (currentFeatures.size() > 1) {
        int worstFeature = -1;
        double maxAccuracy = 0.0;

        for (size_t j = 0; j < currentFeatures.size(); j++) {
            vector<int> tempFeatures = currentFeatures;
            tempFeatures.erase(tempFeatures.begin() + j);

            double accuracy = validator.validate(tempFeatures);
            cout << "Using feature(s) {";
            for (int f : tempFeatures) cout << f << ",";
            cout << "} accuracy is " << accuracy << "%\n";

            if (accuracy > maxAccuracy) {
                maxAccuracy = accuracy;
                worstFeature = j;
            }

            if (accuracy > bestAccuracy) {
                bestAccuracy = accuracy;
                bestSubset = tempFeatures;
            }
        }
        
        if (worstFeature != -1) {
            currentFeatures.erase(currentFeatures.begin() + worstFeature);
            cout << "\n";
            cout << "Feature set {";
            for (int f : currentFeatures) cout << f << ",";
            cout << "} was best, accuracy is " << maxAccuracy << "%\n";
        }
    }

    cout << "\nFinished search!! The best feature subset is {";
    for (int f : bestSubset) cout << f << ",";
    cout << "} with an accuracy of " << bestAccuracy << "%\n";
}

int main() {
    cout << "Welcome to David Frias-Sanchez's Feature Selection Algorithm.\n";

    cout << "Please enter the path to the dataset file: ";
    string filePath;
    cin >> filePath;

    vector<Instance> records;
    loadDataset(filePath, records);

    cout << "Normalizing data...\n";
    normalizeData(records);

    Validator validator(records);

    cout << "Type the number of the algorithm you want to run.\n";
    cout << "(1) Forward Selection\n(2) Backward Elimination\n";
    int selected = 0;
    cin >> selected;

    int numFeatures = records[0].features.size();

    if (selected == 1) {
        forwardSelection(validator, numFeatures);
    } else if (selected == 2) {
        backwardElimination(validator, numFeatures);
    } else {
        cout << "Invalid selection. Exiting program.\n";
    }

    return 0;
}
