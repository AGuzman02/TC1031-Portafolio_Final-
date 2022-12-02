#ifndef _DATAMETHODS_H_
#define _DATAMETHODS_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class DataMethods {
  private: 
    std::string captureIP(std::string element, int &i);
    void merge(std::vector<unsigned int> &values, std::vector<std::string> &valuesIPStr, int low, int m, int high);
    
  public:
    unsigned int IPtoInt(std::string element);
    void printVector(std::vector<std::string> vect);
    void printVector(std::vector<unsigned int> vect);
    void printVector(std::vector<int> vect);
    void saveIPSWInt(std::string fileName, std::vector<std::string> &vect, std::vector<unsigned int> &vectInts);
    void mergeSort(std::vector<unsigned int> &valuesIPInt, std::vector<std::string> &valuesIPStr, int low, int high);
    int binarySearch(std::vector<unsigned int> &A, int key);
    void savePairVectIntoFile(std::string fileName, std::vector<std::pair<std::string,int>> &vect);

};

#endif // _DATAMETHODS_H_
