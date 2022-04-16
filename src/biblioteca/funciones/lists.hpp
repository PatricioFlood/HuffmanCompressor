#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node* sig;
};

template <typename T> Node<T>* add(Node<T>*& p, T x)
{
   Node<T>* n = new Node<T>;
   n->info = x;
   n->sig = NULL;
   if( p==NULL )
   {
      p = n;
   }
   else
   {
      Node<T>* aux = p;
      while( aux->sig!=NULL )
      {
         aux = aux->sig;
      }
      aux->sig = n;
   }

   return n;
}

template <typename T> Node<T>* addFirst(Node<T>*& p, T x)
{
   Node<T>* n = new Node<T>;
   n->info = x;
   n->sig = p;

   p = n;
   return p;
}

template <typename T> void free(Node<T>*& p)
{
   while( p!=NULL )
   {
      Node<T>* aux = p->sig;
      delete p;
      p = aux;
   }
}

template <typename T, typename K>
Node<T>* find(Node<T>* p, K v, int cmpTK(T, K))
{

   Node<T>* n = NULL;
   Node<T>* aux = p;
   while( aux!=NULL )
   {
      if( cmpTK(aux->info,v)==0 )
      {
         n = aux;
         aux = NULL;
      } else {
      aux = aux->sig;
      }
   }

   return n;
}

template <typename T>
T removeFirst(Node<T>*& p)
{
   T t = p->info;
   if( p!=NULL )
   {
      Node<T>* aux = p;
      p = p->sig;
      delete aux;
   }
   return t;
}

template <typename T, typename K>
T remove(Node<T>*& p, K v, int cmpTK(T, K))
{
   Node<T>* aux = p;
   Node<T>* ant = NULL;
   while( aux!=NULL&&cmpTK(aux->info,v)!=0 )
   {
      ant = aux;
      aux = aux->sig;
   }
   if( ant==NULL )
   {
      p = aux->sig;
   }
   else
   {
      ant->sig = aux->sig;
   }
   T t = aux->info;
   delete aux;
   return t;
}

template <typename T>
Node<T>* orderedInsert(Node<T>*& p, T v, int cmpTT(T, T))
{
   Node<T>* aux = p;
   Node<T>* ant = NULL;
   Node<T>* ins = new Node<T>;
   ins->info = v;
   if( p==NULL )
   {
      ins->sig = NULL;
      p = ins;
   }
   else
   {
      bool fin = false;
      while( aux!=NULL&&!fin )
      {
         if( cmpTT(aux->info,v)>0 )
         {
            ins->sig = aux;
            if( ant!=NULL )
            {
               ant->sig = ins;
            }
            else
            {
               p = ins;
            }
            fin = true;
         }
         else
         {
            ant = aux;
            aux = aux->sig;
         }
      }
      if( aux==NULL )
      {
         ins->sig = NULL;
         ant->sig = ins;
      }

   }
   return ins;
}

template <typename T>
Node<T>* searchAndInsert(Node<T>*& p, T e, bool& enc, int cmpTT(T, T))
{
   Node<T>* search = find(p,e,cmpTT);
   if( search==NULL )
   {
      enc = false;
      search = orderedInsert(p,e,cmpTT);
   }
   else
   {
      enc = true;
   }
   return search;
}

template <typename T>
void sort(Node<T>*& p, int cmpTT(T, T))
{
   Node<T>* aux = new Node<T>;
   aux->info = p->info;
   aux->sig = NULL;
   removeFirst(p);
   while( p!=NULL )
   {
      orderedInsert(aux,p->info,cmpTT);
      removeFirst(p);
   }
   p = aux;
}

template <typename T> bool isEmpty(Node<T>* p)
{
   return p==NULL;
}

template <typename T> void push(Node<T>*& p, T v)
{
   addFirst(p,v);
}

template <typename T> T pop(Node<T>*& p)
{
   return removeFirst(p);
}

template <typename T>
void enqueue(Node<T>*& p, Node<T>*& q, T v)
{
   Node<T>* nuevo = new Node<T>;
   nuevo->info = v;
   nuevo->sig = NULL;
   if( q!=NULL )
   {
      q->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }
   q = nuevo;
}

template <typename T>
Node<T>* enqueue(Node<T>*& q, T e)
{
   Node<T>* n = new Node<T>;
   n->info = e;

   if( q==NULL )
   {
      n->sig = n;
      q = n;
   }
   else
   {
      n->sig = q->sig;
      q = n;
   }

   return q;
}

template <typename T>
T dequeue(Node<T>*& p, Node<T>*& q)
{
   T t = removeFirst(p);
   if( p==NULL )
      q = p;
   return t;
}

template <typename T>
T dequeue(Node<T>*& q)
{
   Node<T> aux = q->sig;
   T t = aux->info;
   q->sig = aux->sig;
   delete aux;
   return t;
}

#endif
