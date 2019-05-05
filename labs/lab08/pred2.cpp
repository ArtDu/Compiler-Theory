/*  xxx2019   */
#include "mlisp.h"
bool implication_Q(double x_Q, double y_Q);
//________________ 
bool implication_Q(double x_Q, double y_Q){
  return  ( (!x_Q) || y_Q ) ;
}

