#ifndef _COMPRESOR_
#define _COMPRESOR_

#include <iostream>
#include <string.h>
#include "biblioteca/tads/Arr.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/BitWritter.hpp"
#include "biblioteca/tads/BitReader.hpp"
#include "biblioteca/tads/HuffmanSetup.hpp"
#include "biblioteca/tads/Carga.hpp"
using namespace std;

struct Tabla
{
   unsigned char caracter;
   unsigned int contador;
};

Tabla tablaCreate(unsigned char c, unsigned int n){
   return {c,n};
}

int cmpTabla(Tabla t1, Tabla t2)
{
   int r = t1.contador-t2.contador;
   if( r==0 )
   {
      r = t1.caracter-t2.caracter;
   }
   return r;
}

int cmpCharTabla(Tabla t, char c)
{
   return t.caracter-c;
}

int cmpHuffInfo(HuffmanTreeInfo h1, HuffmanTreeInfo h2)
{
   int r = h1.n-h2.n;
     if( r==0 )
     {
        r = h1.c-h2.c;
     }
     return r;
}

Arr<Tabla> generarTabla(string fName)
{

   /* Mensaje por Consola: */ cout<<"                                              Leyendo el Archivo..."<<endl;

   FILE* f = fopen(fName.c_str(),"r+b");

   Arr<Tabla> tablaAux = arr<Tabla>(256);


   //Inicializo el Arr de Tabla
   for( int i = 0; i<256; i++ )
   {
      arrAdd<Tabla>(tablaAux,tablaCreate((unsigned char)i,0));
   }

   unsigned int longitud = fileSizeBytes(f);

   Carga car = carga(longitud);

   unsigned char c = read<unsigned char>(f);
   while( !feof(f) )
   {
      arrGet(tablaAux,(int)c)->contador++;
      mostrarCarga(car);
      c = read<char>(f);
   }

   //Ordeno crecientemente la tablaAux
   arrSort(tablaAux,cmpTabla);

   //Elimino los caracteres que no existen en el archivo.
   while( arrGet(tablaAux,0)->contador==0 )
   {
      arrRemove(tablaAux,0);
   }


   fclose(f);

   return tablaAux;
}

HuffmanTreeInfo* generarArbol(Arr<Tabla> tabla)
{

   int size = arrSize(tabla);
   //Creo un Arr
   Arr<HuffmanTreeInfo> arbol = arr<HuffmanTreeInfo>(size);

   //Agrego todos los elementos al Arr

   for( int i = 0; i<size; i++ )
   {
      Tabla t = *arrGet(tabla,i);
      HuffmanTreeInfo info = huffmanTreeInfo(t.caracter,t.contador,NULL,NULL);

      arrAdd(arbol,info);
   }

   // Aplico el algoritmo para generar el arbol de Huffman
   for( int i = 1; arrSize(arbol)>1; i++ )
   {
      HuffmanTreeInfo info;
      HuffmanTreeInfo* info1 = new HuffmanTreeInfo;
      HuffmanTreeInfo* info2 = new HuffmanTreeInfo;
      *info1 = arrRemove(arbol,0);
      *info2 = arrRemove(arbol,0);

      info = huffmanTreeInfo(256+i,info1->n+info2->n,info1,info2);

      arrOrderedInsert(arbol,info,cmpHuffInfo);
   }

   //Retorno la raiz
   return arrGet(arbol,0);
}

void recorrerArbol(HuffmanTreeInfo* root, string codigo[])
{
   HuffmanTree ht = huffmanTree(root);

   //Guardo los codigos que me entrega el arbol de huffman
   string cod;
   while( huffmanTreeHasNext(ht) )
   {
      HuffmanTreeInfo* x = huffmanTreeNext(ht,cod);
      codigo[x->c] = cod;
   }

}


void generarArchivo(string fName, Arr<Tabla> tabla,string codigo[], unsigned int longitud)
{

   /* Mensaje por Consola: */cout<<endl << "                                              Comprimiendo..."<<endl;

   FILE* fAnt = fopen(fName.c_str(),"r+b");

   fName += ".huf";
   FILE* f = fopen(fName.c_str(),"w+b");

   int tamanio = arrSize(tabla);

   //Escribo la cantidad de hojas que conforman el arbol en 1 byte
   write<char>(f,(char)tamanio);

   BitWriter bw = bitWriterCreate(f);


   //Escribo cada una de las hojas
   for( int i = 0; i<tamanio; i++ )
   {
      Tabla t = *arrGet(tabla,i);
      write<char>(f,t.caracter);

      string code = codigo[(unsigned char)t.caracter];
      int ln = length(code);
      write<char>(f,(char)ln);

      for( int j = 0; j<ln; j++ )
      {
         bitWriterWrite(bw,charToInt((char)code[j]));
      }
      bitWriterFlush(bw);
   }

   //Excribo la longitud de bytes del archivo
   write<unsigned int>(f,longitud);

   // AUX -> Inicio variables para mostrar porcentaje por pantalla.
   Carga car = carga(longitud);
   // ---------------------------------------------------------------

   //Leo bit por bit y escribo su equivalente en el arbol huffman
   char c = read<char>(fAnt);
   for( unsigned int i = 0; i<longitud; i++ )
   {
      string code = codigo[(unsigned char)c];
      int ln = length(code);

      for( int j = 0; j<ln; j++ )
      {
         bitWriterWrite(bw,charToInt((char)code[j]));
      }


      //Aux para mostrar porcentaje
     mostrarCarga(car);
      // ----------------------

      c = read<char>(fAnt);
   }
   bitWriterFlush(bw);


   fclose(f);
   fclose(fAnt);
}


#endif
