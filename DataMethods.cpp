#include "DataMethods.h"

void DataMethods::printVector(std::vector<std::string> vect){
      for(unsigned int i = 0; i<vect.size(); i++){ // Complejidad: O(n)
        std::cout << vect[i] << std::endl;
      }
  }

void DataMethods::printVector(std::vector<unsigned int> vect){
      for(unsigned int i = 0; i<vect.size(); i++){ // Complejidad: O(n)
        std::cout << vect[i] << std::endl;
      }
  }

void DataMethods::printVector(std::vector<int> vect){
      for(int i = 0; i<vect.size(); i++){ // Complejidad: O(n)
        std::cout << vect[i] << std::endl;
      }
  }

void DataMethods::savePairVectIntoFile(std::string fileName, std::vector<std::pair<std::string,int>> &vect){ // Complejidad: O(n)
    std::fstream newFile;
    newFile.open(fileName,std::ios::out);
    if (newFile.is_open()){ 
      for(int i = 0; i < vect.size(); i++){
      newFile << "{ " <<vect[i].first << ", " << vect[i].second << " }" << "\n";
      }
    }
  }

void DataMethods::saveIPSWInt(std::string fileName, std::vector<std::string> &vect, std::vector<unsigned int> &vectInts){
  std::fstream myFile;
  std::string element;
  vect.push_back(" ");
  vectInts.push_back(0);

  try {
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()){ 
      
      while(getline(myFile, element)){ 
        if(element[5] == ' '){
          continue;
        }
        else if(element[3] == ' '){
          break;
        }
        vect.push_back(element);
        vectInts.push_back(IPtoInt(element));
      }
      myFile.close(); //close the file object.
    
    }
    else {
      throw(fileName);
    }
  }catch(std::string fName){
    std::cout << "No se pudo acceder al archivo " << fName << std::endl;
  }
}

std::string DataMethods::captureIP(std::string element, int &i){ // Complejidad: O(1)
    std::string ipStr;
    while(element[i] != '.' && element[i] != ':'){
        ipStr += element[i];
        i++;
      }
    return ipStr;
  }

unsigned int DataMethods::IPtoInt(std::string element){ // Complejidad: O(1)
    unsigned int ip0, ip1, ip2, ip3, ipInt;
    int i = 0;

      
    ip3 = std::stoi(captureIP(element, i));
    i++;
    ip2 = std::stoi(captureIP(element, i));
    i++;
    ip1 = std::stoi(captureIP(element, i));
    i++;
    ip0 = std::stoi(captureIP(element, i));
    i++;
    

    ip1 *= 256;
    ip2 *= 65536;
    ip3 *= 16777216;

    ipInt = ip0 + ip1 + ip2 + ip3;
    return ipInt;
    
  }


void DataMethods::merge(std::vector<unsigned int> &valuesIPInt, std::vector<std::string> &valuesIPStr, int low, int m, int high) { // Complejidad: O(log(n))
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  
  // crear vectores auxiliares L y R
  std::vector<unsigned int> L1(n1);
  std::vector<unsigned int> R1(n2);
  std::vector<std::string> L2(n1);
  std::vector<std::string> R2(n2);
  for (i = 0; i < n1; i++){
    L1[i] = valuesIPInt[low + i];
    L2[i] = valuesIPStr[low + i];   
  }
  for (j = 0; j < n2; j++){
    R1[j] = valuesIPInt[m + 1 + j];
    R2[j] = valuesIPStr[m + 1 + j];    
  }
  // Fusionar los subarreglos L y R
  i = j = 0;
  k = low;
  while (i < n1 && j < n2) {
    if (L1[i] <= R1[j]) {
      valuesIPInt[k] = L1[i];
      valuesIPStr[k] = L2[i];
      i++;
    } else {
      valuesIPInt[k] = R1[j];
      valuesIPStr[k] = R2[j];
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1) {
    valuesIPInt[k] = L1[i];
    valuesIPStr[k] = L2[i];
    i++;
    k++;
  }
  while (j < n2) {
    valuesIPInt[k] = R1[j];
    valuesIPStr[k] = R2[j];
    j++;
    k++;
  }
}


void DataMethods::mergeSort(std::vector<unsigned int> &valuesIPInt, std::vector<std::string> &valuesIPStr, int low, int high) { // Complejidad: O(nlog(n))
  if (low < high) {
    // encontrar el punto medio
    int m = low + (high - low) / 2;
    // Ordenar dos mitades
    mergeSort(valuesIPInt, valuesIPStr, low, m);
    mergeSort(valuesIPInt, valuesIPStr, m + 1, high);
    // Fusionar ambas mitades
    merge(valuesIPInt, valuesIPStr, low, m, high);
  }
}

int DataMethods::binarySearch(std::vector<unsigned int> &A, int key){ // Complejidad: O(log(n))
  int low = 0;
  int high = A.size()-1;
  int mid = 0;
  while (low <= high){
    mid = low + (high-low)/2;
    if (key == A[mid]) return mid;
    else if (key < A[mid]) high = mid-1;
    else low = mid+1;
  } 
  return -1;
}

