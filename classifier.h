#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "Instance.h"  
#include <iostream>
using namespace std;

class Classifier {
private:
    vector<Instance> trainInstance;  
    double EuclidDistance(const vector<double>& features1, const vector<double>& features2);

public:
    Classifier();
    void Train(const vector<Instance>&);

    int Test(const Instance&);  
};

#endif 
