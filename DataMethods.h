#ifndef _DATAMETHODS_H_
#define _DATAMETHODS_H_

  #include <iostream>
  #include <vector>
  #include <string>
  #include <fstream>


  class DataMethods {
  
    private:
      std::string captureIP(std::string element, int &i);
  
    public:
      void saveFileIntoVect(std::string fileName, std::vector<std::string> &vect);
      void saveVectIntoFile(std::string fileName, std::vector<std::string> &vect);
      void printVector(std::vector<std::string>);
      void printVector(std::vector<unsigned int>);
      unsigned int IPtoInt(std::string element);
      std::string getIP(std::string registro);
      unsigned int getNumRepetidos(unsigned int &indice, std::vector<unsigned int> sortedVector);
  };


  void DataMethods::saveFileIntoVect(std::string fileName, std::vector<std::string> &vect){ // Complejidad: O(n)
    std::fstream myFile;
    std::string element;
    // Meter datos de bitacora a un vector y obtener el tamano  
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()){ 
      while(getline(myFile, element)){ 
        vect.push_back(element);
      }
      myFile.close(); //close the file object.
    }
  }

  void DataMethods::saveVectIntoFile(std::string fileName, std::vector<std::string> &vect){ // Complejidad: O(n)
    std::fstream newFile;
    newFile.open(fileName,std::ios::out);
    if (newFile.is_open()){ 
      for(unsigned int i = 0; i < vect.size(); i++){
      newFile << vect[i] << "\n";
      }
    }
  }

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
    while(element[i] != '.'){
      i++;
    }
    i -= 2;
      
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

  std::string DataMethods::getIP(std::string registro){ // Complejidad: O(1)
    int i = 0;
    std::string IPstr;
    
    while(registro[i] != '.'){
      i++;
    }
    i -= 2;
    while(registro[i] != ':'){
      IPstr += registro[i];
      i++;
    }
    return IPstr;
    }

unsigned int DataMethods::getNumRepetidos(unsigned int &indice, std::vector<unsigned int> sortedVector){ // Complexity: O(n)
  unsigned int recorre, valor, contador;
  recorre = valor = sortedVector[indice];
  contador = 0;
  valor = sortedVector[indice];
  
  while(recorre == valor){
    contador++;
    indice++;
    recorre = sortedVector[indice];
  }

  return contador;
  
}

#endif // _DATAMETHODS_H_

//   g++ -std=c++17 -g -o main *.cpp