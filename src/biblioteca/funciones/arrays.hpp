#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>
#include "strings.hpp"
using namespace std;

template <typename T>
int add(T arr[], int& len, T v)
{
   arr[len] = v;
   len++;
   return len-1;
}

template <typename T, typename K>
int find(T arr[], int len, K v, int cmpTK(T, K))
{
   int pos = -1;
   for( int i = 0; i<len; i++ )
   {
      if( cmpTK(arr[i],v)==0 )
      {
         pos = i;
         i = len;
      }
   }
   return pos;
}

template <typename T>
T remove(T arr[], int& len, int pos)
{
   len--;
   T r = arr[pos];
   for( int i = pos; i<len; i++ )
   {
      arr[i] = arr[i+1];
   }
   return r;
}

template <typename T>
void insert(T arr[], int& len, T v, int pos)
{
   for( int i = len; i>pos; i-- )
   {
      arr[i] = arr[i-1];
   }
   len++;
   arr[pos] = v;
}

template <typename T>
int orderedInsert(T arr[], int& len, T v, int cmpTT(T, T))
{
   int pos = len;
   for( int i = 0; i<len; i++ )
   {
      if( cmpTT(arr[i],v)>=0 )
      {
         pos = i;
         i = len;
      }
   }
   insert<T>(arr,len,v,pos);
   return pos;
}

template <typename T>
void sort(T arr[], int len, int cmpTT(T, T))
{
   int i,j = len-1;
   while( j>0 )
   {
      i = 0;
      while( i<j )
      {
         if( cmpTT(arr[i],arr[i+1])>0 )
         {
            T save = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = save;
         }
         i++;
      }
      j--;
   }

}

template <typename T,typename K>
void sort(T arr[], K arr2[], int len, int cmpTT(T, T))
{
   int i,j = len-1;
   while( j>0 )
   {
      i = 0;
      while( i<j )
      {
         if( cmpTT(arr[i],arr[i+1])>0 )
         {
            T save = arr[i];
            K save2 = arr2[i];
            arr[i] = arr[i+1];
            arr2[i] = arr2[i+1];
            arr[i+1] = save;
            arr2[i+1] = save2;
         }
         i++;
      }
      j--;
   }

}

template <typename T>
void arrayDebug(T arr[], int len)
{
   cout<<"[";
   for( int i = 0; i<len; i++ )
   {
      cout<<arr[i];
      if( i<len-1 )
      {
         cout<<", ";
      }
   }
   cout<<"]"<<endl;
}

template <typename T, typename K>
int binarySearch(T arr[], int len, K v, int cmpTK(T, K))
{
   int i = 0;
   int j = len-1;
   bool fin = false;
   int pos = -1;
   while( !fin )
   {
      int k = (i+j)/2;
      int cmp = cmpTK(v,arr[k]);
      if( cmp>0 )
      {
         i = k+1;
      }
      else
         if( cmp<0 )
         {
            j = k-1;
         }
         else
         {
            j = k;
            i = k;
         }

      if( i==j )
      {
         pos = i;
         fin = true;
      }
      else
         if( i>j )
         {
            fin = true;
         }
   }
   return pos;
}

template <typename T>
void moundHeap(T arr[], int i, int cmpTT(T, T), int n, int &change, T& max, int& posh)
{
   posh = 2*i+1;
   change = 0;
   max = arr[i];

   T hijo1 = arr[posh];
   if( cmpTT(max,hijo1)<0 )
   {
      max = hijo1;
      change = 1;
   }
   if( posh+1<=n )
   {
      T hijo2 = arr[posh+1];
      if( cmpTT(max,hijo2)<0 )
      {
         posh++;
         max = hijo2;
         change = 2;
      }
   }

}

template <typename T>
int changeHeap(T arr[], T max, int i, int posh)
{

   arr[posh] = arr[i];
   arr[i] = max;
   return posh;
}

template <typename T>
void heapSort(T arr[], int len, int cmpTT(T, T))
{
   int n = len-1;
   int pos = (double)(((double)n/2)+0.5-1);

   int change;
   T max;
   int posh = 0;

   for( int i = pos; i>=0; i-- )
   {

      moundHeap(arr,i,cmpTT,n,change,max,posh);

      if( change>0 )
      {

         int i2 = changeHeap(arr,max,i,posh);

         while( posh<=pos )
         {
            moundHeap(arr,i2,cmpTT,n,change,max,posh);

            if( change>0 )
            {

               i2 = changeHeap(arr,max,i2,posh);

            }
         }

      }

   }

   T temp = arr[n];
   arr[n] = arr[0];
   arr[0] = temp;
   n--;

   while( n>0 )
   {
      pos = (double)(((double)n/2)+0.5-1);
      int i = 0;

      moundHeap(arr,i,cmpTT,n,change,max,posh);

      if( change>0 )
      {

         int i2 = changeHeap(arr,max,i,posh);

         while( posh<=pos )
         {

            moundHeap(arr,i2,cmpTT,n,change,max,posh);

            if( change>0 )
            {
               i2 = changeHeap(arr,max,i2,posh);
            }
         }
      }

      temp = arr[n];
      arr[n] = arr[0];
      arr[0] = temp;
      n--;
   }

}

void radixSort(int arr[], int len)
{
   int arr2[len];
   for( int i = 0; i<len; i++ )
   {
      arr2[i] = arr[i];
   }
   int len2 = len;
   int max = 0;

   for( int i = 0; i<len; i++ )
   {
      int aux = digitCount(arr[i]);
      if( aux>max )
      {
         max = aux;
      }
   }

   for( int h = 0; h<max; h++ )
   {
      len = 0;
      for( int i = 0; i<10; i++ )
      {
         for( int j = 0; j<len2; j++ )
         {
            if( getDigit(arr2[j],h)==i )
            {
               add(arr,len,arr2[j]);
            }
         }

      }

      for( int i = 0; i<len; i++ )
      {
         arr2[i] = arr[i];
      }
   }
}

int* crearArray(int n)
{
   // creo dinamicamente un array de n enteros
   int* arr = new int[n];
   // inicializo el array
   for( int i = 0; i<n; i++ )
   {
      arr[i] = 0;
   }
   return arr;
}

#endif
