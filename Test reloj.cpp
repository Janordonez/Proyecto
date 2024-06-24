#include <iostream>
#include <sstream>
#include <ctime>
#include <windows.h>

using namespace std;





void reloj(){

        time_t now = time(0);
        tm * time = localtime(&now);
        int año = time->tm_year;
        int mes = time->tm_mon;
        int dia = time->tm_mday;

        cout << dia << ":" << mes + 1 << ":" << año - 100;
}

int main(){
  reloj();
  system("pause");
  return 0;
}


