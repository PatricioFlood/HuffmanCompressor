#ifndef _TADBITWRITTER_
#define _TADBITWRITTER_

#include "../funciones/strings.hpp"
#include <iostream>
using namespace std;

struct BitWriter
{
   int pos;
   FILE* file;
   char byte;
};

BitWriter bitWriterCreate(FILE* f)
{
   BitWriter br;
   br.file = f;
   br.byte = 0;
   br.pos = 0;
   return br;
}

void bitWriterFlush(BitWriter& bw)
{
   if( bw.pos!=0 )
   {
      write<char>(bw.file,bw.byte);
      bw.pos = 0;
      bw.byte = 0;
   }
}

void bitWriterWrite(BitWriter& bw, int bit)
{
   if( bit==1 )
   {
      char c = 1;
      c = c<<(7-bw.pos);
      bw.byte = bw.byte|c;
   }
   bw.pos++;
   if( bw.pos==8 )
   {
      write<char>(bw.file,bw.byte);
      bw.pos = 0;
      bw.byte = 0;
   }
}

#endif
