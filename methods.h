#ifndef _METHODS_H_
#define _METHODS_H_

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

class Methods {

  private:
    std::string month, day, hour, minute, second;
    vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void merge(std::vector<int> &values1, std::vector<std::string> &values2, int low, int m, int high);
    struct tm dateStruct;
    time_t unixTime;

  public: 
    void getUnixTime();
    void getUnixTime(std::string registro, int &unixTimeVar, int kindOfInput);
    int busquedaBinaria(vector<int> &values1, int key);
    void mergeSort(std::vector<int> &values1, std::vector<std::string> &values2, int low, int high);
};


// Convierte un registro a en un unixTime
void Methods::getUnixTime(std::string registro, int &unixTimeVar, int kindOfregistro){
  int i;
  month = day = hour = minute = second = "";

  // Si registro es de bitacora: 1
  if(kindOfregistro == 1){
    
    for(i = 0; i<3; i++){
      month += registro[i];
    }
    for(i = 4; i<6; i++){
      day += registro[i];
    }
    for(i = 7; i<9; i++){
      hour += registro[i];
    }
    for(i = 10; i<12; i++){
      minute += registro[i];
    }
    for(i = 13; i<15; i++){
      second += registro[i];
    }
    
  }
  // Si registro es de un test case: 2
  else if(kindOfregistro == 2){
    for(i = 9; i<12; i++){
      month += registro[i];
    }
    for(i = 13; i<15; i++){
      day += registro[i];
    }
    for(i = 16; i<18; i++){
      hour += registro[i];
    }
    for(i = 19; i<21; i++){
      minute += registro[i];
    }
    for(i = 22; i<24; i++){
      second += registro[i];
    }
  }
  

dateStruct.tm_isdst = 0;
  for (i = 0; i < (int)months.size(); i++) {
    if (months[i] == month)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2022 - 1900;
  dateStruct.tm_mday = std::stoi(day);
  dateStruct.tm_hour = std::stoi(hour);
  dateStruct.tm_min = std::stoi(minute);
  dateStruct.tm_sec = std::stoi(second);

  unixTimeVar = mktime(&dateStruct);  
  
}

int Methods::busquedaBinaria(vector<int> &values1, int key){
  int low = 0;
  int high = values1.size()-1;
  int mid = 0;
  while (low <= high){
    mid = low + (high-low)/2;
    if (key == values1[mid]) return mid;
    else if (key < values1[mid]) high = mid-1;
    else low = mid+1;
  } 
  return -1;
}

void Methods::merge(std::vector<int> &values1, std::vector<std::string> &values2, int low, int m, int high) {
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  // crear vectores auxiliares L y R
  std::vector<int> L1(n1);
  std::vector<int> R1(n2);
  std::vector<std::string> L2(n1);
  std::vector<std::string> R2(n2);
  for (i = 0; i < n1; i++)  L1[i] = values1[low + i];
  for (j = 0; j < n2; j++)  R1[j] = values1[m + 1 + j];
  for (i = 0; i < n1; i++)  L2[i] = values2[low + i];
  for (j = 0; j < n2; j++)  R2[j] = values2[m + 1 + j];
  // Fusionar los subarreglos L y R
  i = j = 0; k = low;
  while (i < n1 && j < n2) {
    if (L1[i] <= R1[j]){
      values1[k] = L1[i];
      values2[k] = L2[i];
      i++;
    } 
    else {
      values1[k] = R1[j];
      values2[k] = R2[j];
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1) {
	  values1[k] = L1[i];
	  values2[k] = L2[i];
	  i++;
	  k++;
  }
  while (j < n2) {
	  values1[k] = R1[j];
	  values2[k] = R2[j];
	  j++;
	  k++;
  }  
}

void Methods::mergeSort(std::vector<int> &values1, std::vector<std::string> &values2, int low, int high) {
  if (low < high) {
    // encontrar el punto medio
    int m = low +(high - low) / 2;
    // Ordenar dos mitades
    mergeSort(values1, values2, low, m);
    mergeSort(values1, values2, m+1, high);
    // Fusionar ambas mitades
    merge(values1, values2, low, m, high);
  }
}
#endif // _METHODS_H_