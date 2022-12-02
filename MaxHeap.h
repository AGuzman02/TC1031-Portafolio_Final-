#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

  #include <vector>
  #include <iostream>
  #include <stdexcept>
  #include <algorithm>

  class MaxHeap {
    private:
      // contiene los elementos del heap
      std::vector<std::pair<std::string,int>> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   
      int parent(int i);
      int left(int i);
      int right(int i);

    public:
      MaxHeap(int capacity);
      ~MaxHeap();
      bool isEmpty();
      int getCapacity();
      void printMaxHeap();
      void push(std::pair<std::string,int> key);
      int getSize();
      std::pair<std::string,int> top();
      void pop();
      std::pair<std::string,int> getMax();
  };


#endif // __MAXHEAP_H_

//   g++ -std=c++17 -g -o main *.cpp