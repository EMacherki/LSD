
/*
MIT License

Copyright (c) [2019] [Med Ezzeddine Macherki]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* this code is an implimentation of LSD radix sort dezigned for 32 bit integer. It
 * uses 4 key with 8 bit  for each bucket (counts array).
 * this a hybrid radix sort  allows to avoid unnecessery key pass by testing:
 *  1- if the size of data is less then 2
 *  2- if the array is only a repeated value
 *  3- static state defined by the existing of bucket value equal to the size of array.  
 * 
 */

#define  INTMIN  -2147483648u



inline void lsd_sort( 
    unsigned   *arr_begin,   //iterator
    unsigned   *arr_end      
){
  
  int N=arr_end-arr_begin;
  if(N<2)return;  // test 1
  unsigned *i;int tmp;
  
  unsigned int *arr=arr_begin;
  
  int count1[0x100]={0};   
  int count2[0x100]={0};   
  int count3[0x100]={0};   
  int count4[0x100]={0};  
  
  for(i=arr;i!=arr+N;i++)
  {   
    count1[ (*i^= INTMIN)&0XFF]++; // this sign is reversed
    count2[ (*i>>0X8)  &   0XFF]++;
    count3[ (*i>>0X10) &   0XFF]++;
    count4[ (*i>>0X18) &   0XFF]++;
  }
  
  
  int  used =0; // a bit mask to get which count array is in use 
  
  for(int j=0;j<0X100;j++) if(count1[j]==N) {used+=0X8;break;}
  for(int j=0;j<0X100;j++) if(count2[j]==N) {used+=0X4;break;}
  for(int j=0;j<0x100;j++) if(count3[j]==N) {used+=0X2;break;}
  for(int j=0;j<0X100;j++) if(count4[j]==N) {used+=0X1;break;}
  
  
  
  used=0XF-used; // flip bit
  
  
  
  
  if(!used){                           // test 2 :no data to be sorted
    for(i=arr_begin;i!=arr_end;i++) *i^= INTMIN;
    return;
  }
  int index1[0x100];
  int index2[0x100];
  int index3[0x100];
  int index4[0x100];
  
  index1[0]=0;tmp=0;for(int i=1;i<0x100;i++) index1[i]=tmp+=count1[i-1];
  index2[0]=0;tmp=0;for(int i=1;i<0x100;i++) index2[i]=tmp+=count2[i-1];
  index3[0]=0;tmp=0;for(int i=1;i<0x100;i++) index3[i]=tmp+=count3[i-1];
  index4[0]=0;tmp=0;for(int i=1;i<0x100;i++) index4[i]=tmp+=count4[i-1];
  
  
  // a helper array is required
  unsigned int *stack =new unsigned int [N];
  // helper iterator
  unsigned *sta_begin=stack;
  unsigned *sta_end=stack+N;
   // test 3 :we manage each case alone
  switch(used){
  // cas mono
  case 0X8:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i     & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0X4:
    for(i=arr_begin;i!=arr_end;i++)  stack[index2[ (*i>>0X8)     & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0X2:
    for(i=arr_begin;i!=arr_end;i++)  stack[index3[ (*i>>0X10)& 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0X1:
    for(i=arr_begin;i!=arr_end;i++)  stack[index4[ (*i>>0X18)     & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
    //cas bis
  case 0XC:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i     & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index2[(*i>>0X8)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
  case 0XA:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i     & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index3[(*i>>0X10)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
  case 0X9:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i     & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index4[(*i>>0X18)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
    
  case 0X6:
    for(i=arr_begin;i!=arr_end;i++)  stack[index2[ (*i>>0X8) & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index3[(*i>>0X10)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
  case 0X5:
    for(i=arr_begin;i!=arr_end;i++)  stack[index2[ (*i>>0X8) & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index4[(*i>>0X18)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
  case 0X3:
    for(i=arr_begin;i!=arr_end;i++)  stack[index3[ (*i>>0X10) & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index4[(*i>>0X18)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
    
    // cas trio
  case 0XE:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index2[(*i>>0X8)&  0XFF]++]=*i;
    for(i=arr_begin;i!=arr_end;i++)  stack[index3[ (*i>>0X10) & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0XD:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index2[(*i>>0X8)&  0XFF]++]=*i;
    for(i=arr_begin;i!=arr_end;i++)  stack[index4[ (*i>>0X18) & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0XB:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index3[(*i>>0X10)&  0XFF]++]=*i;
    for(i=arr_begin;i!=arr_end;i++)  stack[index4[ (*i>>0X18) & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0X7:
    for(i=arr_begin;i!=arr_end;i++)  stack[index2[ (*i>>0X8) & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index3[(*i>>0X10)&  0XFF]++]=*i;
    for(i=arr_begin;i!=arr_end;i++)  stack[index4[ (*i>>0X18) & 0XFF]++]=*i;
    for(int j=0;j<N;j++) arr[j]=stack[j]^INTMIN;
    delete stack;return;
    break;
  case 0XF:
    for(i=arr_begin;i!=arr_end;i++)  stack[index1[ *i & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index2[(*i>>0X8)&  0XFF]++]=*i;
    for(i=arr_begin;i!=arr_end;i++)  stack[index3[ (*i>>0X10) & 0XFF]++]=*i;
    for(i=sta_begin;i!=sta_end;i++)  arr[index4[(*i>>0X18)&  0XFF]++]=*i^INTMIN;
    delete stack;return;
    break;
    
    
    
  }
  
  
  
}
