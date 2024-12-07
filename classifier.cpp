#include "classifier.h"
#include <cmath>
#include <limits>


Classifier::Classifier() {}

void Classifier::Train(const vector<Instance>& trainingData) {
    trainInstance = trainingData;  
}

int Classifier::Test(const Instance& testInstance) {
    double minDistance = numeric_limits<double>::max();  
    int predection = -1;

    for (int i = 0; i < trainInstance.size(); ++i) { 

        double distance = EuclidDistance(testInstance.features, trainInstance.at(i).features);
        if (distance < minDistance) {
            minDistance = distance;
            predection = trainInstance.at(i).classifier;
        }
    }
    return predection;
}

double Classifier::EuclidDistance(const vector<double>& features1, const vector<double>& features2) {
    double distance = 0.0;
    
    for (int i = 0; i < features1.size(); ++i) {
        distance += pow(features1.at(i) - features2.at(i), 2);
    }
    return sqrt(distance);
}
