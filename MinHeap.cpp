#include "MinHeap.h"

   
  MinHeap::MinHeap(int capacity) {
      //std::cout << "--->Creando un MinHeap: " <<  this << std::endl;
      size = 0;
      maxSize = capacity;
      data.resize(maxSize);
  }

   
  MinHeap::~MinHeap() {
      //std::cout << "--->Liberando memoria del MinHeap: " <<  this << std::endl;
      data.clear();
  }
  
   
  bool MinHeap::isEmpty() { // Complejidad: O(1)
    return (size <= 0);
  }

   
  int MinHeap::getCapacity() {// Complejidad: O(1)
    return maxSize;
  }

   
  void MinHeap::printMinHeap() {// Complejidad: O(n)
    for (int i=0; i < size; i++)
      std::cout << "{ " << data[i].first <<", " << data[i].second << " }" << " ";
      std::cout << std::endl;
  }

   
  int MinHeap::parent(int i) {// Complejidad: O(1)
    return (i-1)/2; 
  }
  
   
  int MinHeap::left(int i) {// Complejidad: O(1)
    return (2*i + 1); 
  }

   
  int MinHeap::right(int i) {// Complejidad: O(1)
    return (2*i + 2);
  }

   
  void MinHeap::push(std::pair<int, int> key) {// Complejidad: O(log(n))
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave");
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)].second > data[i].second) {
       std::swap(data[i], data[parent(i)]);
       i = parent(i);
    }
  }

   
  int MinHeap::getSize() { // Complejidad: O(1)
    return size;
  }

   
  std::pair<int, int> MinHeap::top() { // Complejidad: O(1)
    // Si el arbol esta vacio
    if(isEmpty()){
     std::cout << "El Heap esta vacio" << std::endl;
    }
    // Si no esta vacio imprimir el primer elemento
    return data[0];
  }

   
  void MinHeap::pop() { // Complejidad: O(n)
    // Si el arbol esta vacio
    if(isEmpty()){
     std::cout << "El Heap esta vacio" << std::endl;
    }
    // Si no esta vacio
    else{
      int i;
      // Poner el ultimo valor como el primero
      data[0] = data[size-1];
      data[size-1].first = 100000;
      data[size-1].second = 100000;
      size--;
      // Acomodar el arbol
      for(i = size-1; i > 0; i--){
        if(data[i].second < data[parent(i)].second){
          std::swap(data[i], data[parent(i)]);   
        } 
      }  
    }
  }


std::pair<int, int> MinHeap::getMin(){ // Complejidad: O(n)
  std::pair<int, int> min = data[0];
  
  // Poner el ultimo valor como el primero
  data[0] = data[size-1];
  data[size-1].first = 100000;
  data[size-1].second = 100000;
  size--;
  // Acomodar el arbol
  for(int i = size-1; i > 0; i--){
    if(data[i].second < data[parent(i)].second){
      std::swap(data[i], data[parent(i)]);           
    }
  }
  
  return min;
}


//   g++ -std=c++17 -g -o main *.cpp