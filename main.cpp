// Erick Schiller Echavarría | A01740804
// Alejandro Guzmán Bortoni | A01740787

// ACT integral estructuras de datos lineales
// Imprime los registros en un periodo de tiempo entre dos fechas dadas

/**
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

// * Ejecución:
// *  ./main < TestCases/test01.txt
// *  ./main < TestCases/test02.txt
// *  ./main < TestCases/test03.txt



#include <iostream>
#include <fstream>
#include "DLinkedList.h"
#include "methods.h"

int main() {
  std::fstream newfile;
  std::string element;
  DLinkedList<std::string> bitacora;
  DLinkedList<int> unixTimeList;
  int i, unixTime;
  Methods methods;
  std::string fechaInicio, fechaFinal;
  int unixFechaInicio, unixFechaFinal, indexInicio, indexFinal;


  
  // Meter datos de bitacora a un vector y obtener el tamano  
  newfile.open("bitacora.txt",std::ios::in);
  if (newfile.is_open()){ 
    while(getline(newfile, element)){ 
      bitacora.addLast(element);
    }
  newfile.close(); //close the file object.
  }  

  for(i = 0; i<bitacora.getNumElements(); i++){
    methods.getUnixTime(bitacora.getData(i), unixTime, 1);
    unixTimeList.addLast(unixTime);
  }


  bitacora.sortWUnixTime(unixTimeList); // EL METODO DE MERGE SORT TARDA, PERO SI ACOMODA LOS DATOS

  // Guardar en archivo "bitacora_ordenada.txt" la bitacora ordenada
  newfile.open("bitacora_ordenada.txt",std::ios::out);
  if (newfile.is_open()){ 
    for(i = 0; i < bitacora.getNumElements(); i++){
    newfile << bitacora.getData(i) << "\n";
  }
    
  newfile.close();
  }

//Leer fecha inicial y convertirla a unixTime
  std::getline(std::cin, fechaInicio);
  
  methods.getUnixTime(fechaInicio, unixFechaInicio, 2);
   
  //Leer fecha final y convertirla unixTime
  std::getline(std::cin, fechaFinal);

  methods.getUnixTime(fechaFinal, unixFechaFinal, 2);

  // Buscar el indice de unixInicio
  indexInicio = unixTimeList.DLLLinearSearch(unixFechaInicio);
  
  // Buscar el indice de unixFinal
  indexFinal = unixTimeList.DLLLinearSearch(unixFechaFinal);

  if (indexInicio == -1 || indexFinal == -1){
    std::cout << "Error: Una de las fechas ingresadas no se encuentra en la bitacora" << std::endl;
  }
  
  // Imprimir los registros dentro del intervalo ingresado
  std::cout << "\nResultado: " << indexFinal - indexInicio + 1 << " Registros" << std::endl;
  for(i = indexInicio; i <= indexFinal; i++){
    std::cout << bitacora.getData(i) << std::endl;
  }
  // Guardar en archivo "resultado_busqueda" los resultados
  newfile.open("resultado_busqueda.txt",std::ios::out);
  if (newfile.is_open()){ 
    newfile << "Resultado: " << indexFinal - indexInicio + 1 << " Registros\n";
    for(i = indexInicio; i <= indexFinal; i++){
    newfile << bitacora.getData(i) << "\n";
  }
    
  newfile.close();
  }  
}

 // * Compilacion para debug:
 // *    g++ -std=c++17 -Wall -g -o main *.cpp