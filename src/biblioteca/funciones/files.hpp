#ifndef _TFILES_T_
#define _TFILES_T_

#include "../funciones/strings.hpp"
#include <iostream>
#include <stdio.h>

template <typename T> void write(FILE* f, T v);


template <typename T> T read(FILE* f)
{
   T x;
   fread(&x,sizeof(x),1,f);
   return x;
}

template <typename T> void write(FILE* f, T v)
{
   fwrite(&v,sizeof(v),1,f);
}

template <typename T> void seek(FILE* f, int n)
{
   fseek(f,n*sizeof(T),SEEK_SET);
}
template <typename T> void seekin(FILE* f, int n)
{
   fseek(f,n*sizeof(T),SEEK_CUR);
}

long fileSizeBytes(FILE* f)
{
   long mem = ftell(f);
   fseek(f,0,SEEK_END);
   long i = ftell(f);
   fseek(f,mem,SEEK_SET);
   return i;
}

template <typename T> long fileSize(FILE* f)
{
   return fileSizeBytes(f)/sizeof(T);
}

template <typename T> long filePos(FILE* f)
{

   return ftell(f)/sizeof(T);
}

template <typename T, typename K> int fileBinarySearch(FILE* f, K k, int cmpTK(T, K))
{
   bool fin = false;
   seek<T>(f,0);
   int i = 0;
   T t = read<T>(f);
   if( cmpTK(t,k)!=0 )
   {
      while( !feof(f)&&!fin )
      {
         fin = cmpTK(t,k)==0?true:false;
         t = read<T>(f);
         i++;
      }
   }
   if( fin )
   {
      return i;
   }
   return -1;
}

void stringToFile(FILE* f, string s)
{
   for( int i = 0; i<length(s); i++ )
   {
      char c = s[i];
      write<char>(f,c);
   }
}
string fileToString(FILE* f){
   char c = read<char>(f);
   string s = "";
   while( !feof(f) )
      {
      s = s + c;
      c = read<char>(f);
      }
   return s;
}
void copyFile(FILE* a, FILE* b){
   seek<char>(a,0);
   stringToFile(b,fileToString(a));
}


#endif
