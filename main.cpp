#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

float randNum(){
    mt19937 generator(random_device{}());
	uniform_real_distribution<float> dist(0.f, 1.f);
	return dist(generator);
}

void forwardSelection(int numFeatures) {
    vector<int> currentFeatures;   
    vector<int> bestSubset;        
    float bestOverallAccuracy = 0.0;

    cout << "Beginning forward selection search...\n";

    for (int i = 0; i < numFeatures; i++) {
        int bestFeature = -1;      
        float maxAccuracy = 0.0;

        for (int feature = 1; feature <= numFeatures; feature++) {
            
            if (find(currentFeatures.begin(), currentFeatures.end(), feature) == currentFeatures.end()) {
                vector<int> tempFeatures = currentFeatures;
                tempFeatures.push_back(feature);

                float accuracy = randNum() * 100.0;
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
            cout << "Feature set {";
            for (int f : currentFeatures) cout << f << ",";
            cout << "} was best, accuracy is " << maxAccuracy << "%\n";
        }
    }


    cout << "\nFinished search!! The best feature subset is {";
    for (int f : bestSubset) cout << f << ",";
    cout << "} with an accuracy of " << bestOverallAccuracy << "%\n";
}


void backwardElimination(int numFeatures) {
    vector<int> currentFeatures;    
    for (int i = 1; i <= numFeatures; i++) {
        currentFeatures.push_back(i);  
    }

    float bestAccuracy = randNum() * 100.0; 
    vector<int> bestSubset = currentFeatures;

    cout << "Beginning backward elimination search...\n";
    cout << "Starting with all features: accuracy is " << bestAccuracy << "%\n";

    
    while (currentFeatures.size() > 1) { 
        int worstFeature = -1;
        float maxAccuracy = 0.0;

        for (int j = 0; j < currentFeatures.size(); j++) {

            vector<int> tempFeatures = currentFeatures;
            tempFeatures.erase(tempFeatures.begin() + j);

            float accuracy = randNum() * 100.0;
            cout << "Using feature(s) { ";
            for (int f : tempFeatures) cout << f << " ";
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
            cout << "Feature set { ";
            for (int f : currentFeatures) cout << f << " ";
            cout << "} was best, accuracy is " << maxAccuracy << "%\n";
        }
    }

    cout << "\nFinished search!! The best feature subset is {";
    for (int f : bestSubset) cout << f << ",";
    cout << "} with an accuracy of " << bestAccuracy << "%\n";
}

int main() {
    cout << "Welcome to David Frias-Sanchez Feature Selection Algorithm.\n";
    cout << "Please enter total number of features: ";
    int numFeatures = 0;
    cin >> numFeatures;

    cout << "Type the number of the algorithm you want to run.\n";
    cout << "(1)Forward Selection\n(2)Backward Elimination\n";
    int selected =0;
    cin >> selected;
    cout << fixed << setprecision(2);
    cout << "Using no features and random evalution, I get an accuaracy of ";
    cout << randNum() * 100.0 << "%\n";

    if (selected == 1) {
        forwardSelection(numFeatures);
    } else {
        backwardElimination(numFeatures);
    }
    
    return 0;
}