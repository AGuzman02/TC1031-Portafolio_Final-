#include "MaxHeap.h"

MaxHeap::MaxHeap(int capacity) {
    //std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
}

MaxHeap::~MaxHeap() {
    //std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
    data.clear();
}

bool MaxHeap::isEmpty() { // Complejidad: O(1)
  return (size <= 0);
}

int MaxHeap::getCapacity() {// Complejidad: O(1)
  return maxSize;
}

void MaxHeap::printMaxHeap() {// Complejidad: O(n)
  for (int i=0; i < size; i++)
    std::cout << "{ "<< data[i].first << ", " << data[i].second << " }" << " ";
  std::cout << std::endl;
}

int MaxHeap::parent(int i) {// Complejidad: O(1)
  return (i-1)/2; 
}

int MaxHeap::left(int i) {// Complejidad: O(1)
  return (2*i + 1); 
}

int MaxHeap::right(int i) {// Complejidad: O(1)
  return (2*i + 2);
}

void MaxHeap::push(std::pair<std::string,int> key) {// Complejidad: O(log(n))
  if (size == maxSize) {
    throw std::out_of_range("Overflow: no se puede insertar la llave: " + key.first);
  }
  // Insertamos la nueva llave al final del vector
  int i = size;
  data[i] = key;
  size++;
  // Reparar las propiedades del max heap si son violadas
  while (i != 0 && data[parent(i)].second < data[i].second) {
     std::swap(data[i], data[parent(i)]);
     i = parent(i);
  }
}

int MaxHeap::getSize() { // Complejidad: O(1)
  return size;
}

std::pair<std::string,int> MaxHeap::top() { // Complejidad: O(1)
  // Si el arbol esta vacio
  if(isEmpty()){
   std::cout << "El Heap esta vacio" << std::endl;
  }
  // Si no esta vacio imprimir el primer elemento
  return data[0];
}

void MaxHeap::pop() { // Complejidad: O(n)
  // Si el arbol esta vacio
  if(isEmpty()){
   std::cout << "El Heap esta vacio" << std::endl;
  }
  // Si no esta vacio
  else{
    int i;
    // Poner el ultimo valor como el primero
    data[0] = data[size-1];
    data[size-1].first = "";
    data[size-1].second = -1000;
    size--;
    // Acomodar el arbol
    for(i = size-1; i > 0; i--){
      if(data[i].second > data[parent(i)].second){
        std::swap(data[i], data[parent(i)]);   
      } 
    }  
  }
}

std::pair<std::string,int> MaxHeap::getMax(){ // Complejidad: O(n)
  std::pair<std::string,int> pair = data[0];
  
  // Poner el ultimo valor como el primero
  data[0] = data[size-1];
  data[size-1].first = "";
  data[size-1].second = -1000;
  size--;
  // Acomodar el arbol
  for(int i = size-1; i > 0; i--){
    if(data[i].second > data[parent(i)].second){
      std::swap(data[i], data[parent(i)]);           
    }
  }
  
  return pair;
}