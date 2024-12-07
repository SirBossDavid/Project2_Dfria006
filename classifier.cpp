#include "classifier.h"
#include <cmath>
#include <limits>


Classifier::Classifier() {}

void Classifier::Train(const vector<Instance>& trainingData) {
    trainingInstances = trainingData;  
}

int Classifier::Test(const Instance& testInstance) {
    double minDistance = numeric_limits<double>::max();  
    int predection = -1;

    for (int i = 0; i < trainingInstances.size(); ++i) { 

        double distance = EuclideanDistance(testInstance.features, trainingInstances.at(i).features);
        if (distance < minDistance) {
            minDistance = distance;
            predection = trainingInstances.at(i).classifier;
        }
    }
    return predection;
}

double Classifier::EuclideanDistance(const vector<double>& features1, const vector<double>& features2) {
    double distance = 0.0;
    
    for (int i = 0; i < features1.size(); ++i) {
        distance += pow(features1.at(i) - features2.at(i), 2);
    }
    return sqrt(distance);
}
