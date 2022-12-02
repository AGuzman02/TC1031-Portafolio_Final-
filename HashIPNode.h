#ifndef _HASHIPNODE_H_
#define _HASHIPNODE_H_

#include <vector>
#include <algorithm>
#include <iterator>
#include <vector>

template<class K>
class HashIPNode {
  private:
    K key;
    std::string ip;
    int grado;
    int cantIntentosAcceso;
    std::vector<int> vectNodosAccesos;
    int status; // 0 empty,  1 used,  2 deleted
    std::vector<int> overflow; // used to easily find collision elements

  public:
    HashIPNode();
    K getKey();
    std::string getIP();
    int getGrado();
    int getCantIntentosAcceso();
    int getStatus();
    std::vector<int> getVectNodosAccesos();
    void setKey(K keyValue);
    void setIP(std::string IP);
    void setGrado(int gradoInt);
    void setCantIntentosAcceso( int accesos);
    void setStatus(int);
    void setVectNodosAccesos(std::vector<int>);
    void clearData();
    void addToOverflow(int hashIndex);
    int getOverflowSize();
    int getOverflowAt(int index);
    void removeFromOverflow(int value);
};


template<class K>
HashIPNode<K>::HashIPNode() {
  key = 0;
  ip = " ";
  grado = 0;
  cantIntentosAcceso = 0;
  status = 0;
  overflow.clear(); 
}

template<class K>
K HashIPNode<K>::getKey() {
  return key;
}

template<class K>
std::string HashIPNode<K>::getIP(){
  return ip;
}

template<class K>
int HashIPNode<K>::getGrado(){
  return grado;
}

template<class K>
int HashIPNode<K>::getCantIntentosAcceso(){
  return cantIntentosAcceso;
}

template<class K>
int HashIPNode<K>::getStatus() {
  return status;
}
template<class K>
std::vector<int> HashIPNode<K>::getVectNodosAccesos(){
  return vectNodosAccesos;
}

template<class K>
void HashIPNode<K>::setKey(K keyValue) {
  key = keyValue;
}

template<class K>
void HashIPNode<K>::setIP(std::string IP){
  ip = IP;
  status = 1;
}

template<class K>
void HashIPNode<K>::setGrado(int gradoInt){
  grado = gradoInt;
}

template<class K>
void HashIPNode<K>::setCantIntentosAcceso( int accesos){
  cantIntentosAcceso = accesos;
}

template<class K>
void HashIPNode<K>::setStatus(int statusValue) {
  status = statusValue;
}

template<class K>
void HashIPNode<K>::setVectNodosAccesos(std::vector<int> vectNodos){
  vectNodosAccesos = vectNodos;
}

template<class K>
void HashIPNode<K>::clearData() {
  ip = " ";
  grado = 0;
  cantIntentosAcceso = 0;
  status = 0;
}

template<class K>
void HashIPNode<K>::addToOverflow(int hashIndex) {
  overflow.push_back(hashIndex);
}

template<class K>
int HashIPNode<K>::getOverflowSize() {
  return overflow.size();
}

template<class K>
int HashIPNode<K>::getOverflowAt(int index) { 
  return overflow[index];}

template<class K>
void HashIPNode<K>::removeFromOverflow(int value) {
  std::vector<int>::iterator it = std::find(overflow.begin(), overflow.end(), value);
  // if value was found the remove it
  if (it != overflow.end()) {
    overflow.erase(overflow.begin()+(it - overflow.begin()));
  }
}




#endif  // _HASHIPNODE_H_
