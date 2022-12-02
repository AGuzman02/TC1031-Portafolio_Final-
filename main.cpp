// Erick Schiller Echavarria, A01740804
// Alejandro Guzman Bortoni, A01740787

/** 
* ACT Integral 4.3
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
*    ./main < TestCases/graph01.txt
**/

#include <iostream>
#include <sstream>
#include "Graph.h"
#include "DataMethods.h"
#include "MaxHeap.h"

int main() {
  
  DataMethods methods;
  std::vector<std::string> vectIPS;
  std::vector<unsigned int> vectIPSInt;
  std::vector<std::pair<std::string,int>> vectGrados;
  std::vector<int> vectDistancias;
  std::vector<std::pair<std::string, int>> vectParesDistancias;
  Graph g1;
  

  methods.saveIPSWInt("bitacoraGrafos.txt", vectIPS, vectIPSInt);
  methods.mergeSort(vectIPSInt, vectIPS, 0, vectIPSInt.size()-1);

  g1.loadDirWeightedGraph("bitacoraGrafos.txt", vectIPSInt);

  g1.calcGrados(vectGrados, vectIPS);

  methods.savePairVectIntoFile("grados_ips.txt", vectGrados);

  MaxHeap maxHeap1(vectGrados.size());
  std::vector<std::pair<std::string,int>> vectMayorGrado;

  for(int j = 0; j < vectGrados.size()-1; j++){
    maxHeap1.push(vectGrados[j]);
  }

  std::pair<std::string,int> max = maxHeap1.getMax();
  
  for(int j = 0; j < 3; j++){
    vectMayorGrado.push_back(maxHeap1.getMax());
  }

  methods.savePairVectIntoFile("mayores_grados_ips.txt", vectMayorGrado);

  std::string bootMasterIP = vectMayorGrado[0].first;
  int bootMasterIndex = methods.binarySearch(vectIPSInt, methods.IPtoInt(bootMasterIP));
  

  std::cout << "El boot master se encuentra en la direccion de IP: " << bootMasterIP << std::endl;
  

  g1.DijkstraAlgorithm(bootMasterIndex, vectDistancias);


  for(int j = 1; j < vectIPS.size(); j++){
    std::pair<std::string, int> par;
    par.first = vectIPS[j];
    par.second = vectDistancias[j];
    vectParesDistancias.push_back(par);
  }

  methods.savePairVectIntoFile("distancia_bootmaste.txt", vectParesDistancias);

  MaxHeap myMaxHeap2(vectIPS.size());

  for(int j = 0; j < vectIPS.size(); j++){
    myMaxHeap2.push(vectParesDistancias[j]);
  }

  std::pair<std::string, int> IPLejana = myMaxHeap2.getMax();

  std::cout << "La IP que requiere mas esfuerzo para ser atacada es la " << IPLejana.first << " con distancia de " << IPLejana.second;


  
  
  
  return 0;
} 
 

// g++ -std=c++17 -O3 -o main *.cpp