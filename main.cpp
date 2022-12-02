// Erick Schiller Echavarría | A01740804
// Alejandro Guzmán Bortoni | A01740787

// ACT integral 3.4
// 

// Compilacion para ejecucion:
//    g++ -std=c++17 -Wall -O3 -o main *.cpp

#include <iostream>
#include <vector>

#include "DataMethods.h"
#include "MaxHeap.h"
#include "BST.h"



int main(){
  
  unsigned int i;
  DataMethods methods;
  unsigned int ipIntResultado, veces;
  std::string resultado, resultado2;
  std::vector<std::string> bitacora;
  std::vector<unsigned int> sortedVector;
  std::vector<unsigned int> sortedVectorProcesado;
  std::vector<std::string> vectResultados; 
  BST<unsigned int> registrosBST;
  
  // Guardar bitacora en un vector
  methods.saveFileIntoVect("bitacoraHeap.txt", bitacora);

  
  MaxHeap<unsigned int> ipIntHeap(bitacora.size());
  
  
  // Crear un heap con las IPs convertidas a entero
  for(i = 0; i < bitacora.size(); i++){
    ipIntHeap.pushWBitacora(methods.IPtoInt(bitacora[i]), bitacora);
  }
    
  
  /// heapSort()
  ipIntHeap.heapSort(sortedVector, ipIntHeap.getSize(), bitacora);
  methods.saveVectIntoFile("bitacora_ordenada.txt", bitacora);

  // Meter datos a BST
  unsigned int cont, indice;
  std::string registro;
  indice = 0;
  
  while(indice < sortedVector.size()){
    cont = methods.getNumRepetidos(indice, sortedVector);
    registrosBST.insert(sortedVector[indice-1], bitacora[indice-1], cont);
  }

  // Crear maxHeap
    MaxHeap<int> maxHeapContador(bitacora.size()); 
  
  // Checar duplicados
  maxHeapContador.procesarDuplicados(sortedVector, bitacora, sortedVectorProcesado);


  // Obtener IPs con mayor numero de accesos accesos
std::cout << "Las 5 IPs con mayor numero de accesos son: " << std::endl;
  
  for(int i = 0; i<5; i++){
    ipIntResultado = maxHeapContador.getMax(sortedVectorProcesado);
    resultado = methods.getIP(registrosBST.getRegistroWInt(ipIntResultado));
    veces = registrosBST.getVecesWInt(ipIntResultado);
    resultado2 = "La IP " + resultado + " tiene " + std::to_string(veces) + " accesos.";
    vectResultados.push_back(resultado2);
  }

  
  methods.printVector(vectResultados);
  


  //Guardar resultados en archivo
  methods.saveVectIntoFile("ips_con_mayor_acceso.txt", vectResultados);

}
