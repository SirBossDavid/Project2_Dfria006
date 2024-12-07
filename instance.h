#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>

using namespace std;

class Instance {
public:
    vector<double> features;  
    int classifier;           

    Instance() : classifier(0) {}
    
    Instance(const vector<double>& featureVec, int label)
        : features(featureVec), classifier(label) {}

    void print() const {
        cout << "Features: ";
        for (const double& feature : features) {
            cout << feature << " ";
        }
        cout << " Class: " << classifier << endl;
    }
};

#endif 
