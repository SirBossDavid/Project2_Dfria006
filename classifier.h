#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include "Instance.h"  
#include <iostream>
using namespace std;

class Classifier {
private:
    vector<Instance> trainingInstances;  

   
    double EuclideanDistance(const vector<double>& features1, const vector<double>& features2);

public:
   
    Classifier();

    
    void Train(const vector<Instance>& trainingData);

    
    int Test(const Instance& testInstance);  
};

#endif 
