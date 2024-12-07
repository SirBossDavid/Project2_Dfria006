#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include <cmath>
#include <limits>
#include "Classifier.h" 
#include "Instance.h"   
using namespace std;

class Validator {
private:
    vector<Instance> instances;

public:
    
    Validator(const vector<Instance>& data)
        : instances(data) {}

    double calculateDistance(const vector<double>& a, const vector<double>& b) {
        double distance = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            distance += pow(a[i] - b[i], 2);
        }
        return sqrt(distance);
    }


    double validate(const vector<int>& featureSubset) {
        int correctPredictions = 0;

        vector<Instance> reducedInstances;
        for (const auto& instance : instances) {
            vector<double> subsetFeatures;
            for (int feature : featureSubset) {
                subsetFeatures.push_back(instance.features[feature - 1]);
            }
            reducedInstances.emplace_back(subsetFeatures, instance.classifier);
        }

        for (size_t i = 0; i < reducedInstances.size(); ++i) {
            vector<Instance> trainData;
            Instance testInstance = reducedInstances[i]; 

            for (size_t j = 0; j < reducedInstances.size(); ++j) {
                if (i != j) {
                    trainData.push_back(reducedInstances[j]);
                }
            }

        
            Classifier classifier;
            classifier.Train(trainData); 
            int predictedLabel = classifier.Test(testInstance); 

           
            if (predictedLabel == testInstance.classifier) {
                correctPredictions++;
            }
        }

        return static_cast<double>(correctPredictions) / reducedInstances.size() * 100.0;
    }
};

#endif 
