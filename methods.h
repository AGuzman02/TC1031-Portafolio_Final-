#ifndef _METHODS_H_
#define _METHODS_H_

#include <iostream>
#include <vector>
#include <string>
#include <ctime>


class Methods {

  private:
    std::string month, day, hour, minute, second;
    std::vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void merge(std::vector<int> &values1, std::vector<std::string> &values2, int low, int m, int high);
    struct tm dateStruct;
    time_t unixTime;

  public: 
    void getUnixTime(std::string registro, int &unixTimeVar, int kindOfRegistro);
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

#endif // _METHODS_H_