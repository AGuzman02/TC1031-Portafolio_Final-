#include "Graph.h"

Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
}

Graph::~Graph() {
  adjList.clear();
}

void Graph::split(std::string line, std::vector<int> & res) { // Complejidad: O(n)
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::split(std::string line, std::vector<std::string> & res) { // Complejidad: O(n)
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(line.substr(lastPos, strPos - lastPos));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(line.substr(lastPos, line.size() - lastPos));
}

std::string Graph::removePort(std::string data){ // Complejidad: O(n)
  std::string IP;
  int i = 0;
  while(data[i] != ':'){
    IP += data[i];
    i++;
  }
  return IP;
}

void Graph::loadDirWeightedGraph(std::string fileName, std::vector<unsigned int> &vectIPSInt) { // Complejidad: O(n)
  DataMethods methods;
  std::string element;
  std::fstream myFile;
  int i = 0;
  //
  try{
    myFile.open(fileName, std::ios::in);
    if (myFile.is_open()){ 
      
      while(getline(myFile, element)){ 
        if(element[5] == ' '){
          std::vector<std::string> result;
          split(element, result);
          numNodes = stoi(result[0]);
          numEdges = stoi(result[1]);
          adjList.resize(numNodes + 1);
  
          for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::pair<int,int>> tmpList;
          adjList[k] = tmpList;
          }
        }
        else if(element[3] == ' '){
          std::vector<std::string> result;
          split(element, result);
          int nodoU = methods.IPtoInt(removePort(result[3]));
          int nodoUIndex = methods.binarySearch(vectIPSInt, nodoU);// Convertir result[3] en indice
          int nodoV = methods.IPtoInt(removePort(result[4])); // Convertir result[4] en indice
          int nodoVIndex = methods.binarySearch(vectIPSInt, nodoV);
          int peso = stoi(result[5]);
          adjList[nodoUIndex].addLast(std::make_pair(nodoVIndex, peso));
        }
        i++;
      }
      myFile.close(); //close the file object.
      
    }
    else {
      throw (fileName);
    }
    
  } catch (std::string fName){
    std::cout << "Error: no se pudo acceder al archivo " << fName << std::endl;
  }

}


void Graph::print(){ // Complejidad: O(n)
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 1; nodeU <= numNodes; nodeU++){
      std::cout << "vertex " << nodeU << ": ";
      LLNode<std::pair<int,int>> *ptr = adjList[nodeU].getHead();
      while (ptr != nullptr) {
        std::pair<int, int> par = ptr->data;
        std::cout << "{"<< par.first << "," << par.second << "}  ";
        ptr = ptr->next;
      }
      std::cout << std::endl;  
  }
}

void Graph::calcGradosAccesos(std::vector<int> &vectGrados, std::vector<int> &vectAccesos){ // Complejidad: O(n)
  vectGrados.push_back(0);
  
  for (int nodeU = 1; nodeU <= numNodes; nodeU++){
    int j = 0;
    LLNode<std::pair<int,int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      vectAccesos[par.first]++;
      ptr = ptr->next;
      j++;
    }
    vectGrados.push_back(j);      
  }
}

std::vector<int> Graph::getNodosAccesos(int adjListIndex){
  std::vector<int> vectAccesos;
  
  LLNode<std::pair<int,int>> *ptr = adjList[adjListIndex].getHead();
  while (ptr != nullptr) {
    std::pair<int, int> par = ptr->data;
    int nodoAdj = par.first;
    vectAccesos.push_back(nodoAdj);
    ptr = ptr->next;
  }
  return vectAccesos;
}


