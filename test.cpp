

// Run: g++ test.cpp -o lsd_test 

#include "lsd.h"
#include <iostream>




using namespace std;


int main (){
 
  cout<<endl;
  cout<<endl;
  cout<< "* -This a test of lsd radix sort, one from the fastest sorting method of integer" <<endl;
  cout<< "* -The algorithm used is written with C++ and dezigned to IntegerSort R package" <<endl;
  cout<< "* -It avoids swap and extrat pass within buckets" <<endl;
  cout<<endl;
  cout<<endl;
  cout<< "*** Created by :         MACHERKI M. E. 2019" <<endl;
  cout<<endl;
  cout<<endl;
  
  
  
  int x_size=14;
  int x[]={88,11,77,-5,99,12,3654,88,6547,2301,-9658,785418544,-23145,-988566421};
  cout<< "* -Data simple   :" <<endl<<endl;
  for(int i=0;i<x_size;i++) cout<<"  "<<x[i];
  unsigned *tmp=(unsigned *)x;
  lsd_sort(tmp,tmp+x_size);
  cout<<endl<<endl;
  cout<< "* -after running the algorithm" <<endl<<endl;
  for(int i=0;i<x_size;i++) cout<<"  "<<x[i];
  cout<<endl<<endl;
  cout<< "DONE" <<endl; 
  
}