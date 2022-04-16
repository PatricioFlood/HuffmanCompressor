#ifndef _TGOTOXY_T_
#define _TGOTOXY_T_

#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y)
{
   HANDLE hCon;
   hCon = GetStdHandle(STD_OUTPUT_HANDLE);
   COORD dwPos;
   dwPos.X = x;
   dwPos.Y = y;
   SetConsoleCursorPosition(hCon,dwPos);
}

void ocultarCursor()
{
   HANDLE hCon;
   hCon = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO cci;
   cci.dwSize = 2;
   cci.bVisible = false;
   SetConsoleCursorInfo(hCon,&cci);
}

COORD getXY()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition;
}

struct Carga{
      unsigned int i;
      int porcentaje;
      unsigned int carga;
      double long100;
      int x;
      int y;
};

Carga carga(double longitud){
   COORD cord = getXY();
   return {1,1,1,longitud/(double)100,cord.X+45,cord.Y};
}

void mostrarCarga(Carga& c){
   if(c.i==1){
      ocultarCursor();
      gotoxy(c.x,c.y);
      cout << (char)179;
      gotoxy(c.x+21,c.y);
      cout << (char)179;
   }
   if( c.i==c.carga )
        {
            int resto = c.porcentaje%5;
            resto = resto==1?176:resto==2?177:resto==3?178:resto==0?219:0;
            if(resto>0){
               gotoxy(c.x+((c.porcentaje-1)/5)+1,c.y);
                           cout << (char)resto;
            }


            gotoxy(c.x+24,c.y);
           cout<<c.porcentaje<<"%"<<endl;
           c.porcentaje += 1;
           c.carga = c.long100*c.porcentaje;
        }
   c.i++;
}


#endif
