#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "Instance.h"
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;

class Classifier {
private:
    vector<Instance> trainInstance;  
    
    
    double EuclidDistance(const vector<double>& features1, const vector<double>& features2) {
        double distance = 0.0;
        for (int i = 0; i < features1.size(); ++i) {
            distance += pow(features1.at(i) - features2.at(i), 2);
        }
        return sqrt(distance);
    }

public:
   
    Classifier() {}

    void Train(const vector<Instance>& trainingData) {
        trainInstance = trainingData;  
    }

    int Test(const Instance& testInstance) {
        double minDistance = numeric_limits<double>::max();  
        int prediction = -1;

        for (int i = 0; i < trainInstance.size(); ++i) { 
            double distance = EuclidDistance(testInstance.features, trainInstance.at(i).features);
            if (distance < minDistance) {
                minDistance = distance;
                prediction = trainInstance.at(i).classifier;
            }
        }
        return prediction;
    }
};

#endif
