#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* nodo;
   Node<T>* actual;
   int size;
};

template<typename T>
List<T> list()
{
   return {NULL,NULL,0};
}

template<typename T>
T* listAdd(List<T>& lst,T v)
{

   T* t = &add(lst.nodo,v)->info;
   lst.size++;
   return t;
}

template<typename T>
T* listAddFirst(List<T>& lst,T v){
   T* t = &addFirst(lst.nodo,v)->info;
      lst.size++;
      return t;
}

template<typename T,typename K>
T listRemove(List<T>& lst,K k, int cmpTK(T,K))
{
   lst.size--;
  return remove(lst.nodo,k,cmpTK);
}

template<typename T>
T listRemoveFirst(List<T>& lst)
{
   lst.size--;
  return removeFirst(lst.nodo);
}

template<typename T,typename K>
T* listFind(List<T> lst,K k, int cmpTK(T,K))
{
   return &find(lst.nodo,k,cmpTK)->info;
}

template<typename T>
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   lst.size++;
   return &orderedInsert(lst.nodo,t,cmpTT)->info;
}

template<typename T>
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort(lst.nodo,cmpTT);
}

template<typename T>
bool listHasNext(List<T>& lst)
{
   bool r = false;
      if (lst.actual == NULL || lst.actual->sig != NULL) r = true;
   return r;
}

template<typename T>
T* listNext(List<T>& lst)
{
   if(lst.actual==NULL){
      lst.actual = lst.nodo;
   } else {
      lst.actual = lst.actual->sig;
   }
   return &lst.actual->info;
}

template<typename T>
void listReset(List<T>& lst)
{
   lst.actual = NULL;
   lst.size = 0;
}

template<typename T>
void listFree(List<T>& lst)
{
   free(lst.nodo);
}

template<typename T>
bool listIsEmpty(List<T> lst){
   return isEmpty(lst.nodo);
}

template<typename T>
int listSize(List<T> lst){
   return lst.size;
}


#endif
