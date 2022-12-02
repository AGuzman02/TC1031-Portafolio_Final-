// Erick Schiller Echavarría | A01740804
// Alejandro Guzmán Bortoni | A01740787


// Compilación:
// g++ -std=c++17 *.cpp -Wall -o main 

// * Ejecución:
// *  ./main < TestCases/test01.txt > ./bitacora_ordenada.txt
// *  ./main < TestCases/test02.txt > ./bitacora_ordenada.txt
// *  ./main < TestCases/test03.txt > ./bitacora_ordenada.txt


#include <iostream>
#include <fstream>
#include "methods.h"



int main() {
  std::string fechaInicio, fechaFinal, element;
  int i, size = 0;
  int unixTime, fechaInicioUnix, fechaFinalUnix, indiceInicio, indiceFinal;
  std::fstream newfile;
  vector<int> unixTimeVector;
  vector<std::string> bitacora;
  Methods methods;

  
  // Meter datos de bitacora a un vector y obtener el tamano  
  newfile.open("bitacora.txt",std::ios::in);
  if (newfile.is_open()){ 
    while(getline(newfile, element)){ 
      bitacora.push_back(element);
      size++; 
    }
  newfile.close(); //close the file object.
  }  

  // Crear el vector con los unixTime
  for(i = 0; i<size; i++){
    methods.getUnixTime(bitacora[i], unixTime, 1);
    unixTimeVector.push_back(unixTime);
  }


  // Acomodar los dos vectores
  methods.mergeSort(unixTimeVector, bitacora, 0, size-1);

  
  //Leer fecha inicial y convertirla a unixTime
  std::getline(std::cin, fechaInicio);
  std::cout << fechaInicio << std::endl;
  
  methods.getUnixTime(fechaInicio, fechaInicioUnix, 2);
   

  
  //Leer fecha final y convertirla unixTime
  std::getline(std::cin, fechaFinal);
  std::cout << fechaFinal << std::endl;

  methods.getUnixTime(fechaFinal, fechaFinalUnix, 2);

  

  // Buscar el indice de unixInicio
  indiceInicio = methods.busquedaBinaria(unixTimeVector, fechaInicioUnix);
  
  // Buscar el indice de unixFinal
  indiceFinal = methods.busquedaBinaria(unixTimeVector, fechaFinalUnix);

  if (indiceInicio == -1 || indiceFinal == -1){
    std::cout << "Error: Una de las fechas ingresadas no se encuentra en la bitacora" << std::endl;
  }
  else{
  // Imprimir los registros dentro del intervalo ingresado
    std::cout << "\nResultado: " << indiceFinal - indiceInicio + 1 << " registros" << std::endl;
  for(i = indiceInicio; i<=indiceFinal; i++){
    std::cout << bitacora[i] << std::endl;   
  }

  }

// Falta:
  // Guardar los vectores ordenados en un archivo llamado bitacora_ordenada.txt

  
  
}