#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../funciones/arrays.hpp"

using namespace std;

template <typename T>
struct Arr
{
   T* array;
   int len;
   int size;
};

template <typename T>
Arr<T> arr(int size)
{
   Arr<T> a;
   a.array = new T[size];
   a.size = size;
   a.len = 0;
   return a;
}

template <typename T>
Arr<T> arr()
{
   Arr<T> a;
   a.size = 0;
   a.len = 0;
   return a;
}

template <typename T>
void arrResize(Arr<T>& a, int size)
{
   T* n = new T[size];
   for( int i = 0; i<a.len&&i<size; i++ )
   {
      n[i] = a.array[i];
   }
   if(a.size>0){
      delete a.array;
   }
   a.array = n;
   a.size = size;
}

template <typename T>
int arrAdd(Arr<T>& a, T v)
{
   if( a.len>=a.size )
   {
      arrResize(a,a.size+1);
   }
   return add(a.array,a.len,v);
}

template <typename T>
T* arrGet(Arr<T> a, int p)
{
   return a.array+p;
}

template <typename T>
void arrInsert(Arr<T>& a, T v, int p)
{
   if( a.len>=a.size )
   {
      arrResize(a,a.size+1);
   }
   insert(a.array,a.len,v,p);
}

template <typename T>
int arrSize(Arr<T> a)
{
   return a.len;
}

template <typename T>
T arrRemove(Arr<T>& a, int p)
{
   T t = remove(a.array,a.len,p);
   arrResize(a,a.size-1);
   return t;
}

template <typename T>
void arrRemoveAll(Arr<T>& a)
{
   delete a.array;
   Arr<T> n = arr<T>();
   a = n;
}

template <typename T, typename K>
int arrFind(Arr<T>& a, K k, int cmpTK(T, K))
{
   return find(a.array,a.len,k,cmpTK);
}

template <typename T>
int arrOrderedInsert(Arr<T>& a, T t, int cmpTT(T, T))
{
   if( a.len>=a.size )
   {
      arrResize(a,a.size+1);
   }
   return orderedInsert(a.array,a.len,t,cmpTT);
}

template <typename T>
void arrSort(Arr<T>& a, int cmpTT(T, T))
{
   sort(a.array,a.len,cmpTT);
}

template <typename T, typename K>
void arrSort(Arr<T>& a, Arr<K>& b, int cmpTT(T, T))
{
   sort(a.array,b.array,a.len,cmpTT);
}

template <typename T>
void arrSet(Arr<T>& a, T v, int p)
{
   a.array[p] = v;
}

#endif
