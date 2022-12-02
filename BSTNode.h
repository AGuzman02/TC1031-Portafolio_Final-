#ifndef _BSTNODE_H_
#define _BSTNODE_H_

#include <string>

template <class T>
class BSTNode {
  public:
    T data;
    std::string registro;
    unsigned int contador;
    BSTNode<T> *left;
    BSTNode<T> *right;
    BSTNode();
    BSTNode(T value, std::string acceso, unsigned int count);
};

template <class T>
BSTNode<T>::BSTNode() : data{}, registro{}, contador{}, left{nullptr}, right{nullptr} {}

template <class T>
BSTNode<T>::BSTNode(T value, std::string acceso, unsigned int count) : data{value}, registro{acceso}, contador{count}, left{nullptr}, right{nullptr} {}


#endif   // _BSTNODE_H_