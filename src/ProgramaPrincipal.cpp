#ifndef _MAIN
#define _MAIN

#include <iostream>
#include <string.h>
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/tads/Arr.hpp"
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/HuffmanSetup.hpp"
#include "Compresor.hpp"
#include "Descompresor.hpp"
using namespace std;

// -------------------------------------------------------------- Compresor ---------------------------------------------------------------------------------------

void comprimir(string fName)
{
   //Cuento los caracteres y genero un Arr de Tabla que solo contendrá los caracteres utilizados y ordenados segun la cantidad de caracteres.
   // Tambien guardo la longitud de bytes en una variable long long (8 bytes).
   Arr<Tabla> tabla = generarTabla(fName);
   //Genero el arbol a partir de la tabla.
   HuffmanTreeInfo* root = generarArbol(tabla);

   //Creo un array de string que contedra los codigos de cada caracter segun su codigo ASCII.
    string codigo[256];

   //Recorro el arbol y guardo los códigos en el array de string.
   recorrerArbol(root,codigo);

   //Genero el archivo comprimido.
   generarArchivo(fName,tabla,codigo,root->n);
}

// -------------------------------------------------------------- Descompresor ---------------------------------------------------------------------------------------

void descomprimir(string fName)
{
   //Abro el archivo
   FILE* f = fopen(fName.c_str(),"r+b");

   //Genero la tabla de codigos
   Arr<Tabla2> tabla = generarTabla2(f);

   //Genero el arbol
   HuffmanTreeInfo* arbol = generarArbol2(tabla);

   //Genero el archivo descomprimido
   generarDescomprimido(f,fName,arbol);

   //cierro el archivo.
   fclose(f);

}

// -------------------------------------------------------------- Main---------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
   system("TITLE Compresor Huffman");
   cout <<          "                                    -------------------------------------------" << endl;
   cout<< "                                    --- COMPRESOR HUFFMAN by Patricio Flood ---" << endl;
   cout <<          "                                    -------------------------------------------" << endl << endl;

   string fName;

   if( argc==1 ) // Si no recibe el nombre del archivo lo pide por consola.
   {
      cout<<"Ingrese el nombre del archivo: ";
      cin>>fName;
      cout << endl;
   }
   else
   {
      fName = argv[1];
   }

   if( !endsWith(fName,".huf") )
   {
      if(argc!=1){
         cout<< "Archivo a comprimir: " << getTokenAt(fName,'\\',tokenCount(fName,'\\')-1) << endl << endl;
      }
      comprimir(fName);
   }
   else
   {
      if(argc!=1){
               cout<< "Archivo a descomprimir: " << getTokenAt(fName,'\\',tokenCount(fName,'\\')-1) << endl << endl;
            }
      descomprimir(fName);
   }

   return 0;
}

#endif
