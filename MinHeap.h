#ifndef __MINHEAP_H_
#define __MINHEAP_H_

  #include <vector>
  #include <iostream>
  #include <stdexcept>
  #include <algorithm>
  #include <string>

  
  class MinHeap {
    private:
      // contiene los elementos del heap
      std::vector<std::pair<int, int>> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   
      int parent(int i);
      int left(int i);
      int right(int i);

    public:
      MinHeap(int capacity);
      ~MinHeap();
      bool isEmpty();
      int getCapacity();
      void printMinHeap();
      void push(std::pair<int, int> key);
      int getSize();
      std::pair<int, int> top();
      void pop();
      std::pair<int, int> getMin();
  };

    

    

#endif // __MINHEAP_H_

//   g++ -std=c++17 -g -o main *.cpp