#ifndef _TADBITREADER_
#define _TADBITREADER_

#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"
#include <iostream>
using namespace std;

struct BitReader
{
   int pos;
   FILE* file;
   char save;
};

void bitReaderPos(BitReader& br, int pos)
{
   br.pos = pos;
}

BitReader bitReaderCreate(FILE* f)
{
   BitReader r;
   r.file = f;
   r.pos = 0;
   return r;
}

int bitReaderRead(BitReader& br)
{
   if( br.pos==0 )
   {
      br.save = read<char>(br.file);
   }
   char c = br.save;
   int pos = br.pos;

   c = c>>(7-pos);
   c = c&1;

   if( br.pos==7 )
   {
      br.pos = 0;
   }
   else
   {
      br.pos++;
   }

   return c;
}

void bitReaderFlush(BitReader& br)
{
   br.pos = 0;
}

string bitReaderToString(BitReader& br)
{
   string r = "";
   while( !feof(br.file) )
   {
      r = r+intToString(bitReaderRead(br));
      if( !feof(br.file) )
      {
         if( br.pos%8==0&&br.pos%64!=0 )
         {
            r = r+" | ";
         }
         else
            if( br.pos%64==0 )
            {
               r = r+"\n";
            }
            else
            {
               r = r+" ";
            }
      }
   }
   return r;
}

#endif
