#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "DLLNode.h"
#include <vector>


template <class T>
class DLinkedList {
  private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;
    void merge(int low, int m, int high, DLinkedList<T> &L, DLinkedList<T> &R, DLinkedList<int> &L1, DLinkedList<int> &R1, DLinkedList<int> &unixTimeList);
    void ordenaMerge(int low, int high, DLinkedList<T> &L, DLinkedList<T> &R, DLinkedList<int> &L1, DLinkedList<int> &R1, DLinkedList<int> &unixTimeList);

  public:
    DLinkedList();
    ~DLinkedList();
    int getNumElements();
    void addFirst(T value);
    void addLast(T value);
    bool deleteAt(int position);
    T getData(int position);
    void updateAt(int position, T newValue);
    void operator =(const DLinkedList<T> &other);
    void clear();
    void sortWUnixTime(DLinkedList<int> &unixTimeList);
    int DLLLinearSearch(T value);
    
};

template <class T> 
DLinkedList<T>::DLinkedList() {
  //std::cout << "---> Creando una lista ligada vacia: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
  //std::cout << "---> Liberando memoria de la lista ligada: " << this << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template <class T> 
int DLinkedList<T>::getNumElements() {
  return numElements;
}

template <class T>
void DLinkedList<T>::addFirst(T value){
  DLLNode<T>* newNode = new DLLNode<T>(value);
  // si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  }
  else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  numElements++;
}

template <class T>
void DLinkedList<T>::addLast(T value) {
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  }
  else {
    DLLNode<T>* newNode = new DLLNode<T>(value);
    tail->next = newNode;
    newNode->prev  = tail;
    tail = newNode;
    numElements++;
  }
}

template <class T>
bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else if (position == 0) { // borrar primer elemento en la lista
    DLLNode<T> *p = head;
    // si la lista contiene solo un nodo
    if (head != nullptr && head->next == nullptr)
      head = tail = nullptr;  
    else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    numElements--;
    return true;
  }
  else { // si la lista contiene mas de un nodo
    DLLNode<T> *p = head;
    DLLNode<T> *prev = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      prev = p;
      p = p->next;
      index++;
    }
    // si debe borrarse el ultimo nodo
    if (p->next == nullptr) {
      prev->next = nullptr;
      tail = prev;
    }
    else { // borrar cualquier otro nodo
      prev->next = p->next;
      p->next->prev = prev;
    }
    delete p;
    numElements--;
    return true;
  }
}

template<class T>
T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else {
    if (position == 0)
      return head->data;
    DLLNode<T> *p = head;
    int index = 0;
    while (p != nullptr) {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    return {};
  }
}


template<class T>
void DLinkedList<T>::updateAt(int position, T newValue) { // Complejidad: O(n)
  
  //Si el indice esta fuera de rango
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else if (position == 0) { // actualizar primer elemento en la lista
    head->data = newValue;
  }
  else {
    DLLNode<T> *p = head;
    int index = 0;
    // buscar el indice del elemento a actualizar
    while (index != position) {
      p = p->next;
      index++;
    }
    // si debe actualizarse el ultimo nodo
    if (p->next == nullptr) {
      tail->data = newValue;
    }
    p->data = newValue;
  }
}

template<class T>
void DLinkedList<T>::operator =(const DLinkedList<T> &other) { // Complejidad: O(n)
  // Borrar la memoria de listaIzq
  while(head != nullptr){
    deleteAt(0);
  }

  DLLNode<T> *pDer;
  
  pDer = other.head;
  while (pDer != nullptr){
    addLast(pDer->data);
    pDer = pDer->next;
  }
  
}

template<class T>
void DLinkedList<T>::clear(){
  while(head != nullptr){
    deleteAt(0);
  }
}

template<class T>
void DLinkedList<T>::merge(int low, int m, int high, DLinkedList<T> &L, DLinkedList<T> &R, DLinkedList<int> &L1, DLinkedList<int> &R1, DLinkedList<int> &unixTimeList) {

  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m; 
  L1.clear();
  R1.clear();
  L.clear();
  R.clear();

  for (i = 0; i < n1; i++){
    L1.addLast(unixTimeList.getData(low + i));
    L.addLast(getData(low + i));
  }  
  for (j = 0; j < n2; j++){
    R1.addLast(unixTimeList.getData(m + 1 + j));
    R.addLast(getData(m + 1 + j));
  } 
  // Fusionar las listas L y R
  i = j = 0; k = low;
  while (i < n1 && j < n2) {

    if (L1.getData(i) <= R1.getData(j)){
      unixTimeList.updateAt(k, L1.getData(i));
      updateAt(k, L.getData(i));
      i++;
    } 
    else {
      unixTimeList.updateAt(k, R1.getData(j));
      updateAt(k, R.getData(j));
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1) {
    unixTimeList.updateAt(k, L1.getData(i));
    updateAt(k, L.getData(i));
	  i++;
	  k++;
  }
  while (j < n2) {
    unixTimeList.updateAt(k, R1.getData(j));
    updateAt(k, R.getData(j));
	  j++;
	  k++;
  } 
}

template<class T>
void DLinkedList<T>::ordenaMerge(int low, int high, DLinkedList<T> &L, DLinkedList<T> &R, DLinkedList<int> &L1, DLinkedList<int> &R1, DLinkedList<int> &unixTimeList) {
  if (low < high) {
    
    // encontrar el punto medio
    int m = low + (high - low) / 2;
    
    // Ordenar dos mitades
    ordenaMerge(low, m, L, R, L1, R1, unixTimeList);
    ordenaMerge(m+1, high, L, R, L1, R1, unixTimeList);

    // Fusionar ambas mitades
    merge(low, m, high, L, R, L1, R1, unixTimeList);

  }
}

template<class T>
void DLinkedList<T>::sortWUnixTime(DLinkedList<int> &unixTimeList){
  DLinkedList<T> L, R;
  DLinkedList<int> L1, R1;
  ordenaMerge(0, unixTimeList.getNumElements() - 1, L, R, L1, R1, unixTimeList);
  }

template<class T> 
int DLinkedList<T>::DLLLinearSearch(T value){
  DLLNode<T> *p;
  int index = 0;
  p = head;
  while(p != nullptr){
    if(p->data == value){
      return index;
    }
    p = p->next;
    index++;
  }
  return -1;
}


 // * Compilacion para debug:
 // *    g++ -std=c++17 -Wall -g -o main *.cpp

#endif // _LINKEDLIST_H_
 