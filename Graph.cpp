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


void Graph::BFS(int u) { // Complejidad: O(n)
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos una queue 
  QueueLinkedList<int> queue;
  // Marcamos el vertice actual u como visitado y entra al queue
  visited.insert(u);
  queue.enqueue(u);
  std::cout << "Recorrido BFS " << std::endl;
  while(!queue.isEmpty()) {
    // Extraemos un vertice del queue y lo procesamos (print) 
    u = queue.dequeue();  
    std::cout << u << " ";
    // Obtenemos los vertices adyacentes del vertice u
    // Si estos no han sido visitados entonces se marcan como visitados
    // y los metemos al queue
    LLNode<std::pair<int,int>> *ptr = adjList[u].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int v = par.first;
      // Verifica si v ya fue visitado en tiempo O(log n)
      bool isInVisited = visited.find(v) != visited.end();
      if (!isInVisited) {
        visited.insert(v);
        queue.enqueue(v);
      }
      ptr = ptr->next;
    }
  }
  std::cout << std::endl;
}

void Graph::calcGrados(std::vector<std::pair<std::string,int>> &vectGrados, std::vector<std::string> &vectIPS){ // Complejidad: O(n)
  
  for (int nodeU = 1; nodeU <= numNodes; nodeU++){
    std::string nodeUIP = vectIPS[nodeU];
    int j = 0;
    LLNode<std::pair<int,int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      ptr = ptr->next;
      j++;
    }
    std::pair<std::string,int> par;
    par.first = nodeUIP;
    par.second = j;
    vectGrados.push_back(par);
        
  }
}

// Dikjstra's algorithm
// Agregar: 
// -vector: distancias del nodo a cada nodo
// -vector: nodo antes de cada nodo en el camino seleccionado
// -Si vuelve a encontrar otro camino con un nodo, checar si es mas corto que el que se tenia

void Graph::DijkstraAlgorithm(int indexNodoU, std::vector<int> &distancias) { // Complejidad: O(n)
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos una queue 
  // QueueLinkedList<int> queue;
  MinHeap myMinHeap(numNodes);
  // Extra
  std::vector<int> prev;
  //Iniciar valores de los vectores
  for(int i = 0; i < numNodes; i++){
    std::pair<std::string, int> tempPar;
    distancias.push_back(-1);
    prev.push_back(-1);
  }
  
  distancias[indexNodoU] = 0;
  prev[indexNodoU] = indexNodoU;
  
  // Marcamos el vertice actual u como visitado y entra al queue
  visited.insert(indexNodoU);
  // queue.enqueue(indexNodoU);
  std::pair<int, int> par1;
  par1.first = indexNodoU;
  par1.second = 0;
  myMinHeap.push(par1);
    
  while(!myMinHeap.isEmpty()) {
    // Extraemos un vertice del queue y lo procesamos (print) 
    // indexNodoU = queue.dequeue();
    indexNodoU = myMinHeap.getMin().first;
    

    // Obtenemos los vertices adyacentes del vertice u
    // Si estos no han sido visitados entonces se marcan como visitados
    // y los metemos al queue
    LLNode<std::pair<int,int>> *ptr = adjList[indexNodoU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int v = par.first;
      int distancia = par.second;
      distancia += distancias[indexNodoU];
      // Verifica si v ya fue visitado en tiempo O(log n)
      bool isInVisited = visited.find(v) != visited.end();
      if (!isInVisited) {
        par.second = distancia;
        visited.insert(v);
        // queue.enqueue(v);
        myMinHeap.push(par);
        distancias[v] = distancia;
        prev[v] = indexNodoU;
      }
      else {
        if(distancia < distancias[v] && indexNodoU != prev[v]){
          distancias[v] = distancia;
          prev[v] = indexNodoU;
        }
      }
      ptr = ptr->next;
    }
  }
  std::cout << std::endl;
}
