#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Stack
{
   Node<T>* nodo;
   int size;
};

template<typename T>
Stack<T> stack()
{
   return {NULL,0};
}

template<typename T>
void stackPush(Stack<T>& st,T v)
{
   push(st.nodo,v);
   st.size++;
}

template<typename T>
T stackPop(Stack<T>& st)
{
   st.size--;
   return pop(st.nodo);
}

template<typename T>
bool stackIsEmpty(Stack<T> st)
{
  return isEmpty(st.nodo);
}

template<typename T>
int stackSize(Stack<T> st)
{
   return st.size;
}

#endif
