#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

  #include <vector>
  #include <iostream>
  #include <stdexcept>
  #include <algorithm>

  template<class T>
  class MaxHeap {
    private:
      // contiene los elementos del heap
      std::vector<T> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   
      int parent(int i);
      int left(int i);
      int right(int i);
      void acomodarHeap(int size, int index, std::vector<std::string> &bitacora);

    public:
      MaxHeap(int capacity);
      ~MaxHeap();
      bool isEmpty();
      int getCapacity();
      void printMaxHeap();
      void push(T key);
      void pushWBitacora(T key, std::vector<std::string> &bitacora);
      void pushWCounter(T key, std::vector<unsigned int> &vectorProcesado);
      int getSize();
      T top();
      void pop();
      void heapSort(std::vector<T> &emptyVect, int size, std::vector<std::string> &bitacora);
      unsigned int getMax(std::vector<unsigned int> &sortedVectorProcesado);
     void procesarDuplicados(std::vector<unsigned int> &sortedVector, std::vector<std::string> &bitacora, std::vector<unsigned int> &sortedVectorProcesado);
  };

  template <class T> 
  MaxHeap<T>::MaxHeap(int capacity) {
      //std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
      size = 0;
      maxSize = capacity;
      data.resize(maxSize);
  }

  template <class T> 
  MaxHeap<T>::~MaxHeap() {
      //std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
      data.clear();
  }
  
  template <class T> 
  bool MaxHeap<T>::isEmpty() { // Complejidad: O(1)
    return (size <= 0);
  }

  template <class T> 
  int MaxHeap<T>::getCapacity() {// Complejidad: O(1)
    return maxSize;
  }

  template <class T> 
  void MaxHeap<T>::printMaxHeap() {// Complejidad: O(n)
    for (int i=0; i < size; i++)
      std::cout << data[i] << " ";
    std::cout << std::endl;
  }

  template <class T> 
  int MaxHeap<T>::parent(int i) {// Complejidad: O(1)
    return (i-1)/2; 
  }
  
  template <class T> 
  int MaxHeap<T>::left(int i) {// Complejidad: O(1)
    return (2*i + 1); 
  }

  template <class T> 
  int MaxHeap<T>::right(int i) {// Complejidad: O(1)
    return (2*i + 2);
  }

  template <class T> 
  void MaxHeap<T>::push(T key) {// Complejidad: O(log(n))
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave: " + key);
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i]) {
       std::swap(data[i], data[parent(i)]);
       i = parent(i);
    }
  }

  template <class T> 
  void MaxHeap<T>::pushWBitacora(T key, std::vector<std::string> &bitacora) {// Complejidad: O(log(n))
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave: " + key);
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i]) {
       std::swap(data[i], data[parent(i)]);
       std::swap(bitacora[i], bitacora[parent(i)]);
       i = parent(i);
    }
  }

  template <class T> 
  void MaxHeap<T>::pushWCounter(T key, std::vector<unsigned int> &vectorProcesado) {// Complejidad: O(log(n))
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave: " + key);
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i]) {
       std::swap(data[i], data[parent(i)]);
       std::swap(vectorProcesado[i], vectorProcesado[parent(i)]);
       i = parent(i);
    }
  }

  template <class T> 
  int MaxHeap<T>::getSize() { // Complejidad: O(1)
    return size;
  }

  template <class T> 
  T MaxHeap<T>::top() { // Complejidad: O(1)
    // Si el arbol esta vacio
    if(isEmpty()){
     std::cout << "El Heap esta vacio" << std::endl;
    }
    // Si no esta vacio imprimir el primer elemento
    return data[0];
  }

  template <class T> 
  void MaxHeap<T>::pop() { // Complejidad: O(n)
    // Si el arbol esta vacio
    if(isEmpty()){
     std::cout << "El Heap esta vacio" << std::endl;
    }
    // Si no esta vacio
    else{
      int i;
      // Poner el ultimo valor como el primero
      data[0] = data[size-1];
      data[size-1] = -1000;
      size--;
      // Acomodar el arbol
      for(i = size-1; i > 0; i--){
        if(data[i] > data[parent(i)]){
          std::swap(data[i], data[parent(i)]);   
        } 
      }  
    }
  }


  // Codigo basado en:
  // GeeksforGeeks. (2022, 22 septiembre). Heap Sort. https://www.geeksforgeeks.org/heap-sort/
  template <class T>
  void MaxHeap<T>::acomodarHeap(int size, int index, std::vector<std::string> &bitacora){ // Complejidad: O(log(n))
    // Initialize largest as root
    int largest = index;
 
    // left = 2*i + 1
    int l = 2 * index + 1;
 
    // right = 2*i + 2
    int r = 2 * index + 2;
 
    // If left child is larger than root
    if (l < size && data[l] > data[largest])
        largest = l;
 
    // If right child is larger than largest
    // so far
    if (r < size && data[r] > data[largest])
        largest = r;
 
    // If largest is not root
    if (largest != index) {
        std::swap(data[index], data[largest]);
        std::swap(bitacora[index], bitacora[largest]);
 
        // Recursively heapify the affected
        // sub-tree
        acomodarHeap(size, largest, bitacora);
    }
  }

  template <class T>
  void MaxHeap<T>::heapSort(std::vector<T> &emptyVect, int size, std::vector<std::string> &bitacora){ // Complejidad: O(nlog(n))
    // Asegurarse que el heap este acomodado
    for (int i = size / 2 - 1; i >= 0; i--)
        acomodarHeap(size, i, bitacora);
 
    // Ir extrayendo la raiz y acomodando los vectores
    for (int i = size - 1; i >= 0; i--) {
 
        // Move current root to end
        maxSize--;
        emptyVect.insert(emptyVect.begin(), data[0]);
        std::swap(data[0], data[i]);
        std::swap(bitacora[0], bitacora[i]);
      
        // Acomodar el heap
        acomodarHeap(i, 0, bitacora);
    }
  }

  template<class T>
  unsigned int MaxHeap<T>::getMax(std::vector<unsigned int> &sortedVectorProcesado){ // Complejidad: O(n)
    unsigned int ipInt = sortedVectorProcesado[0];
    

    // Poner el ultimo valor como el primero
    data[0] = data[size-1];
    data[size-1] = -1000;
    size--;
    // Acomodar el arbol
    for(int i = size-1; i > 0; i--){
      if(data[i] > data[parent(i)]){
        std::swap(data[i], data[parent(i)]);      
        std::swap(sortedVectorProcesado[i], sortedVectorProcesado[parent(i)]);      
      }
    }
    
    return ipInt;
  }



template <class T>
 void MaxHeap<T>::procesarDuplicados(std::vector<unsigned int> &sortedVector, std::vector<std::string> &bitacora, std::vector<unsigned int> &sortedVectorProcesado){ // Complejidad: O(n)
  int valor, recor, contador;
  unsigned int x = 0;
  while(x < sortedVector.size()){
    contador = 0;
    recor = sortedVector[x];
    valor = sortedVector[x];
    while(recor == valor){
      recor = sortedVector[x];
      contador++;
      x++;
    }
    sortedVectorProcesado.push_back(valor);
    pushWCounter(contador, sortedVectorProcesado);
  }
   
 }

  

#endif // __MAXHEAP_H_

//   g++ -std=c++17 -g -o main *.cpp