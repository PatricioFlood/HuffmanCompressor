#ifndef _DESCOMPRESOR_
#define _DESCOMPRESOR_

#include <iostream>
#include <string.h>
#include "biblioteca/tads/Arr.hpp"
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/BitWritter.hpp"
#include "biblioteca/tads/BitReader.hpp"
#include "biblioteca/tads/HuffmanSetup.hpp"


struct Tabla2
{
   unsigned char caracter;
   string codigo;
};


Tabla2 tabla2Create(unsigned char c, string codigo){
   return {c,codigo};
}


Arr<Tabla2> generarTabla2(FILE* f)
{

   //Leo la cantidad de hojas (como el numero 256 desborda el byte, lo leo como un 0)

   int hojas = read<unsigned char>(f);
   if( hojas==0 )
   {
      hojas = 256;
   }

   //Leo todas las hojas y guardo los codigos en un Arr de Tabla2.

   Arr<Tabla2> tabla = arr<Tabla2>();

   char c = read<char>(f);
   int longitud = read<char>(f);
   BitReader br = bitReaderCreate(f);

   for( int i = 0; i<hojas; i++ )
   {
      string codigo = "";
      for( int j = 0; j<longitud; j++ )
      {
         codigo += intToString(bitReaderRead(br));
      }
      bitReaderFlush(br);

      Tabla2 t = tabla2Create(c,codigo);

      arrAdd<Tabla2>(tabla,t);

      if( i<hojas-1 )
      {
         c = read<char>(f);
         longitud = read<char>(f);
      }

   }

   return tabla;
}

HuffmanTreeInfo* generarArbol2(Arr<Tabla2> tabla)
{

   HuffmanTreeInfo* arbol = new HuffmanTreeInfo;
   *arbol = huffmanTreeInfo(0,0,NULL,NULL);


   int tablaSize = arrSize(tabla);

   for( int i = 0; i<tablaSize; i++ )
   {

      Tabla2 t = *arrGet(tabla,i);

      int codeSize = length(t.codigo);


      HuffmanTreeInfo* arbolAux = arbol;

      for( int j = 0; j<codeSize; j++ )
      {

         if( t.codigo[j]=='0' )
         {
            if( j==codeSize-1 )
            {

               arbolAux->left = new HuffmanTreeInfo;
               *arbolAux->left = huffmanTreeInfo(t.caracter,1,NULL,NULL);
            }
            else
               if( arbolAux->left==NULL )
               {

                  arbolAux->left = new HuffmanTreeInfo;
                  *arbolAux->left = huffmanTreeInfo(0,0,NULL,NULL);
               }
            arbolAux = arbolAux->left;
         }
         else
         {
            if( j==codeSize-1 )
            {
               arbolAux->right = new HuffmanTreeInfo;
               *arbolAux->right = huffmanTreeInfo(t.caracter,1,NULL,NULL);

            }
            else
               if( arbolAux->right==NULL )
               {


                  arbolAux->right = new HuffmanTreeInfo;
                  *arbolAux->right = huffmanTreeInfo(0,0,NULL,NULL);
               }
            arbolAux = arbolAux->right;
         }

      }

   }

   return arbol;
}

void generarDescomprimido(FILE* f, string fName, HuffmanTreeInfo* arbol)
{

   /* Mensaje por Consola: */cout<<"                                               Descomprimiendo..."<<endl;

   int fNameSize = length(fName);
   fName = substring(fName,0,fNameSize-4);

   FILE* f2 = fopen(fName.c_str(),"w+b");

   unsigned int caracteres = read<unsigned int>(f);

   BitReader br = bitReaderCreate(f);


   // Agregado de porcentaje de carga
   Carga car = carga(caracteres);
   //--------------------------------------------------


   while( caracteres>0 )
   {
      HuffmanTreeInfo* arbolAux = arbol;
      char c;
      bool fin = false;
      while( !fin )
      {
         if( bitReaderRead(br)==0 )
         {
            arbolAux = arbolAux->left;
         }
         else
         {
            arbolAux = arbolAux->right;
         }
         if( arbolAux->n==1 )
         {
            fin = true;
            c = arbolAux->c;
         }
      }

      // Mostrar el porcentaje de proceso completado por consola.
      mostrarCarga(car);
      //----------------------------------------------------------

      write<char>(f2,c);
      caracteres--;
   }

   fclose(f2);
}


#endif
