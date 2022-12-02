// Erick Schiller Echavarria, A01740804
// Alejandro Guzman Bortoni, A01740787

/** 
* ACT Integral 5.2 - Codigos Hash
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main < TestCases/graph01.txt
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/

#include <iostream>
#include "Graph.h"
#include "DataMethods.h"
#include "HashTable.h"


int main() {
  int colisiones = 0;
  DataMethods methods;
  std::vector<std::string> vectIPS;
  std::vector<unsigned int> vectIPSInt;
  std::vector<int> vectGrados;
  std::vector<int> vectAccesos;
  Graph g1;

  methods.saveIPSWInt("bitacoraGrafos.txt", vectIPS, vectIPSInt);
  methods.mergeSort(vectIPSInt, vectIPS, 0, vectIPSInt.size()-1);

  g1.loadDirWeightedGraph("bitacoraGrafos.txt", vectIPSInt);

  vectAccesos.resize(vectIPS.size(), 0);
  g1.calcGradosAccesos(vectGrados, vectAccesos);
  
  HashTable<unsigned int> ipHashTable(vectIPS.size());
  
  for(int i = 1; i < vectIPS.size(); i++){
    std::vector<int> vectNodosAccesos = g1.getNodosAccesos(i);
    unsigned int key = vectIPSInt[i];
    std::string ip = vectIPS[i];
    int grado = vectGrados[i];
    int cantAccesos = vectAccesos[i];
    ipHashTable.add(key, ip, grado, cantAccesos, colisiones, vectNodosAccesos);
  }

  std::cout << "\nTotal de colisiones: " << colisiones << std::endl;

  

  std::string inputIP;
  std::cout << "\nIngrese IP: ";
  std::cin >> inputIP;

  
  int inputIPInt = methods.IPtoInt(inputIP);
  int indexInputIP = methods.binarySearch(vectIPSInt, inputIPInt);
  if (indexInputIP == -1){
    std::cout << "Error: IP no existe en bitacora" << std::endl;
  }
  else{
    ipHashTable.getIPSummary(inputIP, vectIPS, vectIPSInt);
    
  }


}