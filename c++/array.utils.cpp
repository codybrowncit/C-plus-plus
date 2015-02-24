//#include "array_utils.h"
#include <iostream>
int smallest_int(int a[], const int size){
    int i;
    int hold;
    bool sorted = false;
    while (!sorted){
        for (i=0; a[i] != 0; i++){
            if(a[i] > a[i+1]){
                hold = a[i+1];
                a[i+1] = a[i];
                a[i] = hold;
            }
            else{
                sorted = true;
            }
        }
    }
    return a[0];
}
int main (){
  int a[4];
  a[0]=14;
  a[1]=40;
  a[2]=2;
  a[3]=100;
  int sm = smallest_int(a, 4);
  std::cout << sm << std::endl;
  return 0;
}
