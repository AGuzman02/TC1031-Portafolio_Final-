#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <vector>
#include <string>
#include "BSTNode.h"

template <class T> 
class BST {
  private:
    BSTNode<T> *root;
    BSTNode<T>* insertRecursive(BSTNode<T> *p, T value, std::string registro, unsigned int contador);
    BSTNode<T>* getSuccessor(BSTNode<T> *p);
    BSTNode<T>* deleteRecursive(BSTNode<T> *p, T value);
    void print2D(BSTNode<T> *p, int space);
    void recursiveInorder(BSTNode<T> *p);
    void recursivePostorder(BSTNode<T> *p);
    void recursivePreorder(BSTNode<T> *p);
    void recursiveLevelByLevel(BSTNode<T> *p);
    int heightRecursive(BSTNode<T> *p);
    int recursiveAncestors(BSTNode<T> *p, int value);
    void printLevelRecursive(BSTNode<T> *p, int level);
    

  public:
    BST();
    ~BST();
    void clearMemory(BSTNode<T> *p);
    bool search(T value);
    void insert(T value, std::string registro, unsigned int contador);
    void deleteNode(T value);
    void print();
    void inorder();
    void postorder();
    void preorder();
    // hacer
    void levelByLevel();
    void visit(int order);
    int height();
    void ancestors(T value);
    int whatLevelAmI(T value);
    std::string getRegistroWInt(T value);
    unsigned int getVecesWInt(T value);
    

};

template <class T>
BST<T>::BST() {
  //std::cout << "---> Creando un BinarySearchTree vacio: " <<  this << std::endl;
  root = nullptr;
}
  
template <class T>
BST<T>::~BST() {
  //std::cout << "---> Liberando memoria del BinarySearchTree: " << this << std::endl;
  clearMemory(root);
}

template <class T>
void BST<T>::clearMemory(BSTNode<T> *p) { // Complexity: O(n)
  if (p != nullptr) {
    clearMemory(p->left);
    clearMemory(p->right);
    delete p;
    p = nullptr;
  }
}

template <class T>
bool BST<T>::search(T value) { // Complexity: O(n)
  BSTNode<T> *p = root;
  while (p != nullptr) {
    if (p->data == value) {
      return true;
    }
    else {
      p = (value < p->data ? p->left : p->right);
    }
  }
  return false;
}

template <class T>
BSTNode<T>* BST<T>::insertRecursive(BSTNode<T> *p, T value, std::string registro, unsigned int contador) { // Complexity: O(log(n))
  if (p == nullptr) // El BST esta vacio
    p = new BSTNode<T>(value, registro, contador);
  else if (value < p->data)
    p->left = insertRecursive(p->left, value, registro, contador);
  else if (value > p->data)
    p->right = insertRecursive(p->right, value, registro, contador);
  else
    std::cout << "El elemento " << value << " ya existe en el BST" << std::endl;
  return p;
}

template <class T>
void BST<T>::insert(T value, std::string registro, unsigned int contador) { // Complexity: O(log(n))
  root = insertRecursive(root, value, registro, contador);
}

template <class T>
BSTNode<T> * BST<T>::getSuccessor(BSTNode<T> *p) { // Complexity: O(n)
  BSTNode<T> *current = p;
  while (current && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <class T>
BSTNode<T>* BST<T>::deleteRecursive(BSTNode<T> *p, T value) { // Complexity: O(n)
  BSTNode<T> *current = p;
  // caso base, arbol vacio
  if (p == nullptr)
    return p;
  if (value < p->data)
    p->left = deleteRecursive(p->left, value);
  else if (value > p->data)
    p->right = deleteRecursive(p->right, value);
  else { // Hemos localizado el nodo a borrar
    // El nodo a borrar no tiene ningun hijo
    if (p->left == nullptr && p->right == nullptr) {
      delete p;
      p = nullptr;
      return p;
    }
    else if (p->left == nullptr) { // El nodo a borrar solo tiene hijo derecho
      current = p->right;
      delete p;
      p = nullptr;
      return current;
    } 
    else if (p->right == nullptr) { // El nodo a borrar solo tiene hijo izquierdo
      current = p->left;
      delete p;
      p = nullptr;
      return current;
    }
    // El nodo a borrar tiene dos hijos
    current = getSuccessor(p->right);
    p->data = current->data;
    p->right = deleteRecursive(p->right, current->data);
  }
  return p;
}

template <class T>
void BST<T>::deleteNode(T value) { // Complexity: O(n)
   root = deleteRecursive(root, value);
}

template <class T>
void BST<T>::print2D(BSTNode<T> *root, int space) { // Complexity: O(n)
    // Caso base
    if (root == nullptr)
        return;
    // Incrementa la distancia entre niveles
    space += 5;
 
    // Procesa hijo derecho
    print2D(root->right, space);
    // Imprime el nodo actual despues de los espacios necesarios
    std::cout << std::endl;
    for (int i = 5; i < space; i++)
        std::cout << " ";
    std::cout << root->data << std::endl;
    // Procesa el hijo izquierdo 
    print2D(root->left, space);

  
}

template <class T>
void BST<T>::print() { // Complexity: O(n)
    print2D(root, 0);
}

template <class T>
void BST<T>::recursiveInorder(BSTNode<T> *p) { // Complexity: O(n)
  if (p != nullptr) {
    recursiveInorder(p->left);
    std::cout << p->contador<< " ";
    recursiveInorder(p->right);
  }
}

template <class T>
void BST<T>::inorder() { // Complexity: O(n)
    std::cout << "inorder():" << std::endl;
    recursiveInorder(root);
    std::cout << std::endl;
}

template <class T>
void BST<T>::recursivePostorder(BSTNode<T> *p) { // Complexity: O(n)
  if (p != nullptr) {
    recursivePostorder(p->left);
    recursivePostorder(p->right);
    std::cout << p->contador << " ";
  }
}

template <class T>
void BST<T>::postorder() { // Complexity: O(n)
    std::cout << "postorder():" << std::endl;
    recursivePostorder(root);
    std::cout << std::endl;
}

template <class T>
void BST<T>::recursivePreorder(BSTNode<T> *p) { // Complexity: O(n)
  if (p != nullptr) {
    std::cout << p->contador << " ";
    recursivePreorder(p->left);
    recursivePreorder(p->right);
  }
}

template <class T>
void BST<T>::preorder() { // Complexity: O(n)
    std::cout << "preorder():" << std::endl;
    recursivePreorder(root);
    std::cout << std::endl;
}

template <class T> 
void BST<T>::printLevelRecursive(BSTNode<T> *p, int level){ // Complexity: O(n)
    // Si se llega
    if (p == NULL)
        return;
    if (level == 1)
        std::cout << p->data << " ";
    else if (level > 1) {
        printLevelRecursive(p->left, level - 1);
        printLevelRecursive(p->right, level - 1);
    }
}

//Codigo basado en:
// GeeksforGeeks. (2022, 22 septiembre). Level Order Binary Tree Traversal. Recuperado 20 de octubre de 2022, de https://www.geeksforgeeks.org/level-order-tree-traversal/
template <class T>
void BST<T>::levelByLevel(){ // Complexity: O(n)
    
   int altura = height();
  int i;
  // Se imprime el nivel i dependiendo de la altura del arbol
    for (i = 1; i <= altura; i++)
        printLevelRecursive(root, i);
}


// Codigo basado en:
// https://www.youtube.com/watch?v=qjD-CmuC0MQ

template <class T>
void BST<T>::visit(int order){ // Complexity: O(n)
  // Imprimir el arbol en base al orden del input
  switch (order){
    case 1:
      preorder();
    break;
    case 2:
      inorder();
    break;

    case 3:
      postorder();
    break;

    case 4: 
      levelByLevel();
    
    default:
      std::cout << "orden no existente" << std::endl;
    break;
  }
}

template <class T>
int BST<T>::heightRecursive(BSTNode<T> *p){ // Complexity: O(log(n))
  int leftH, rightH;
  if (p == nullptr)
    return -1;
  // valida que existe el nodo
  
  leftH = heightRecursive(p -> left );
  // guarda el valor del nodo a la izquierda
  rightH = heightRecursive(p -> right);
  // guarda el valor del nodo a la derecha
  if (leftH > rightH)
    return leftH + 1;
  else 
    return rightH + 1;
  // regresa el total de la izquierda o de la derecha
    
  }
  


template <class T>
int BST<T>::height(){ // Complexity: O(log(n))
  return heightRecursive(root) + 1;
  
}

template <class T>
int BST<T>::recursiveAncestors(BSTNode<T> *p, int value){ //Complexity: 0(log(n))

  if (p == nullptr)
    return 0;
  // valida que hay un nodo
  if (p->data == value)
   return 1;
  //confirma si el value es el target buscado
  if (recursiveAncestors(p -> left, value) || recursiveAncestors(p -> right, value)){
    std::cout << p -> data << std::endl;
    return 1;
    }
  // imprime el valor del nodo antes del value
  return 0;
}

template <class T>
void BST<T>::ancestors(T value){
  recursiveAncestors(root, value);
  }

// Ancestros

template <class T>
int BST<T>::whatLevelAmI(T value){ // Complexity: O(n)
  BSTNode<T> *p = root;
  int level = 1;
  // Recorrer la lista en busca del valor
  while (p != nullptr) {
    //Si el valor se encuentra en p
    if (p->data == value) {
      return level;
    }
    // Si el valor no se encuentra en p
    else {
      //Sumar 1 a nivel cada que se recorr p a un nuevo nivel
      p = (value < p->data ? p->left : p->right);
      level++;
    }
  }
  //Si el valor no se encuentra en el arbol
  std::cout << "\nError: Valor no encontrado" << std::endl;
  return -1;
}

template <class T>
std::string BST<T>::getRegistroWInt(T value){ // Complexity: O(n)
  BSTNode<T> *p = root;
  while (p != nullptr) {
    if (p->data == value) {
      return p->registro;
    }
    else {
      p = (value < p->data ? p->left : p->right);
    }
  }
  throw std::out_of_range("El valor no existe");
}

template <class T>
unsigned int BST<T>::getVecesWInt(T value){ // Complexity: O(n)
  BSTNode<T> *p = root;
  while (p != nullptr) {
    if (p->data == value) {
      return p->contador;
    }
    else {
      p = (value < p->data ? p->left : p->right);
    }
  }
  throw std::out_of_range("El valor no existe");
}

#endif  //_BST_H_

// https://www.geeksforgeeks.org/level-order-tree-traversal/
