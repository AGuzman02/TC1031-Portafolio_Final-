#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <iostream>
#include <vector>
#include <stdexcept> 
#include <string> 
#include "HashIPNode.h"
#include "DataMethods.h"
#include "MinHeap.h"
#include "Graph.h"

template<class K>
class HashTable {
  private:
    std::vector<HashIPNode<K>> table;
    int currentSize;
    // Preferible usar un numero primo
    // https://numerosprimos.org/numeros-primos-de-1-a-100000/
    int maxSize;      

  public:
    HashTable(int selectedMaxSize);
    int getHashIndex(K keyVal); // Funcion hash
    int getCurrentSize();
    void print();
    void add(K keyValue, std::string ipStr, int gradoInt, int accesos, int &colisiones, std::vector<int> vectNodosAccesos);
    int find(K keyValue);
    std::string getIPAt(int index);
    int getGradoAt(int index);
    int getCantIntentosAccesoAt(int index);
    void remove(K keyValue);
    void getIPSummary(std::string inputIP, std::vector<std::string> &vectIPS, std::vector<unsigned int> &vectIPSInt);

};    

template<class K>
HashTable<K>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  currentSize = 0;
  table = std::vector<HashIPNode<K>>(maxSize);
}

template<class K>
int HashTable<K>::getHashIndex(K keyVal) {
  // metodo de residuales (llave mod maxSize)
  return keyVal % maxSize;
}

template<class K>
int HashTable<K>::getCurrentSize() { // Complejidad: O(1)
  return currentSize;
}

template<class K>
void HashTable<K>::print() { // Complejidad: O(n)
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // status:  0 empty, 1 used, 2 deleted
    if (table[i].getStatus() == 1) // Cell is used
      std::cout << "Cell: " << i << " Key: " << table[i].getKey() << ", IP: " << table[i].getIP() << ", Overflow.size: " << table[i].getOverflowSize() << std::endl;
  }
}

template<class K>
void HashTable<K>::add(K keyVal, std::string ipStr, int gradoInt, int accesos, int &colisiones, std::vector<int> vectNodosAccesos) { // Complejidad: O(1)
  if (currentSize == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  // Compute the index of the table using a key and a hash function
  int hashVal = getHashIndex(keyVal); 
  HashIPNode<K> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() != 1) { // Cell is free
    node.setKey(keyVal);
    node.setIP(ipStr);
    node.setGrado(gradoInt);
    node.setCantIntentosAcceso(accesos);
    node.setVectNodosAccesos(vectNodosAccesos);
    table[hashVal] = node;
  }
  else { // Cell is already taken
    // Find next free space using quadratic probing
    // https://www.geeksforgeeks.org/quadratic-probing-in-hashing/
    int i = 1;
    colisiones++;
    int currentHashVal = getHashIndex(hashVal + i * i);
    HashIPNode<K> currentNode = table[currentHashVal];
    while (currentNode.getStatus() == 1) { // Cell is used
      i++;
      colisiones++;
      currentHashVal = getHashIndex(hashVal + i * i);
      currentNode = table[currentHashVal];
    }
    // A free cell was found
    currentNode.setKey(keyVal);
    currentNode.setIP(ipStr);
    currentNode.setGrado(gradoInt);
    currentNode.setCantIntentosAcceso(accesos);
    currentNode.setVectNodosAccesos(vectNodosAccesos);
    node.addToOverflow(currentHashVal);
    table[currentHashVal] = currentNode;
    table[hashVal] = node;
  }
  currentSize++;
}

template<class K>
int HashTable<K>::find(K keyVal) { // Complejidad: O(1)
  int hashVal = getHashIndex(keyVal); 
  HashIPNode<K> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() == 1) { // Cell is used
    if (node.getKey() == keyVal) {
      return hashVal;
    }
    for (int i = 0; i < (int)node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyVal) {
        return overflowIndex;
      }
    }
    return -1;
  }
  return -1;
}

template<class K>
std::string HashTable<K>::getIPAt(int index){ // Complejidad: O(1)
  return table[index].getIP();
}

template<class K>
int HashTable<K>::getGradoAt(int index){ // Complejidad: O(1)
  return table[index].getGrado();
}

template<class K>
int HashTable<K>::getCantIntentosAccesoAt(int index){ // Complejidad: O(1)
  return table[index].getCantIntentosAcceso();
}


template<class K>
void HashTable<K>::remove(K keyVal) { // Complejidad: O(1)
  int pos, hashVal;
  pos = find(keyVal);
  if (pos == -1) {
    throw std::invalid_argument("Element does not exist in hash table");
  }
  hashVal = getHashIndex(keyVal);
  if (pos != hashVal) {
    HashIPNode<K> node = table[hashVal];
    node.removeFromOverflow(pos);
    table[hashVal] = node;
  }
  table[pos].clearData(); 
}

template <class K>
void HashTable<K>::getIPSummary(std::string inputIP, std::vector<std::string> &vectIPS, std::vector<unsigned int> &vectIPSInt){ // Complejidad: O(1)
  DataMethods methods;
  int ipInt = methods.IPtoInt(inputIP);
  int indexIP = methods.binarySearch(vectIPSInt, ipInt);
  HashIPNode<K> tmpNode = table[find(ipInt)];
  
  std::cout << "\n\n---getIPSummary()---" << std::endl;
  std::cout << "\nIP: " << tmpNode.getIP() << std::endl;
  std::cout << "\nTotal direcciones accesadas: " << tmpNode.getGrado() << std::endl;
  std::cout << "\nTotal direcciones que intentaron acceder: " << tmpNode.getCantIntentosAcceso() << std::endl;
  std::cout << "\nIPs accesadas en orden ascendente:" << std::endl;
  MinHeap myMinHeap(tmpNode.getGrado());
  std::vector<int> vectNodosAccesos = tmpNode.getVectNodosAccesos();
  for(int i = 0; i < vectNodosAccesos.size(); i++){
    std::pair<std::string, unsigned int> par;
    par.first = vectIPS[vectNodosAccesos[i]];
    par.second = vectIPSInt[vectNodosAccesos[i]];
    myMinHeap.push(par);
  
  }
  for(int i = 0; i < tmpNode.getGrado(); i++){
    std::cout << "\t" << myMinHeap.getMin().first << std::endl;
  }
}


 

#endif  // _HASH_TABLE_H_

// g++ -std=c++17 -O3 -o main *.cpp
