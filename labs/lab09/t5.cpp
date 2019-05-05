/*  dao2019   */
#include "mlisp.h"
double __dao2019__try(double x);
//________________ 
double __dao2019__try(double x) {
  x = x * x;
return x;
}
int main(){
 display("Calculations!");newline();
 display(__dao2019__try( 2)); newline();

 std::cin.get();
 return 0;
}

