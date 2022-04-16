#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

long long int intPow(int i, int j)
{
   long long int r = i;
   if( j==0 )
   {
      return 1;
   }
   else
      if( j>0 )
      {
         for( int w = 1; w<j; w++ )
         {
            r = r*i;
         }
         return r;
      }
      else
      {
         for( int w = 0; w<j; w++ )
         {
            r = r/i;
         }
         return r;
      }

}

// --[ Funciones Basicas ]--

// Descripcion: Retorna la longitud de la cadena s
// Paramerto:
//    s - La cadena cuya longitud se desea conocer
// Retorna: la longitud de la cadena s
// Ejemplo: l

int cmpInt(int a, int b)
{
   return a-b;
}

int length(string s)
{
   int i;
   for( i = 0; s[i]!='\0'; i++ )
   {
   }
   return i;
}


// Retorna la cantidad de veces que la cadena s contiene a c
int charCount(string s, char c)
{
   int count = 0;
   for( int i = 0; s[i]!='\0'; i++ )
   {
      if( s[i]==c )
      {
         count = count+1;
      }
   }
   return count;
}

// Retorna la subcadena de s comprendida entre d (inclusive) y h (no inclusive)
string substring(string s, int d, int h)
{
   string sub = "";
   for( int i = 0; s[i]!='\0'; i++ )
   {
      if( (i>=(d))&&(i<(h)) )
      {
         sub = sub+s[i];
      }
   }
   return sub;
}

// Retorna la subcadena de s que va desde d (inclusive) hasta el final
string substring(string s, int d) // ok
{
   string sub = "";
   for( int i = 0; s[i]!='\0'; i++ )
   {
      if( i>=(d) )
      {
         sub = sub+s[i];
      }
   }
   return sub;
}

// Retorna la posicion de la primer ocurrencia
// de c dentro s, o -1 si s no contiene a c
int indexOf(string s, char c) // ok
{
   int posicion = -1;
   for( int i = 0; (s[i]!='\0')&&(posicion==-1); i++ )
   {
      if( s[i]==c )
      {
         posicion = i;
      }
   }

   return posicion;
}

// Retorna la posicion de la primer ocurrencia de c dentro de s
// considerando la subcadena de s que va desde offset hasta el final.
// Ejemplo: indexOf("ALGORITMOS",'O',7) retorna: 1
int indexOf(string s, char c, int offSet) // ok
{
   int posicion = -1;
   for( int i = offSet; (s[i]!='\0')&&(posicion==-1); i++ )
   {
      if( s[i]==c )
      {
         posicion = i-offSet;
      }
   }

   return posicion;
}

// Retorna la posicion de la ultima ocurrencia de c dentro de s
// o -1 si s no contiene a c
int lastIndexOf(string s, char c)
{
   int posicion = -1;
   for( int i = 0; (s[i]!='\0'); i++ )
   {
      if( s[i]==c )
      {
         posicion = i;
      }
   }

   return posicion;
}

// Retorna la posicion de la n-esima ocurrencia de c dentro de s.
// Por ejemplo: indexOfN("pedro|pablo|juan|rolo",'|',2) retorna 11.
int indexOfN(string s, char c, int n)
{
   int posicion = -1;
   for( int i = 0,j = 0; (s[i]!='\0')&&j<n; i++ )
   {
      if( s[i]==c )
      {
         posicion = i;
         j++;
      }
   }

   return posicion;
}

int cmpChar(char c1, char c2){
   return c1<c2?-1:c1>c2?1:0;
}

// Retorna el valor numerico de ch.
// Ejemplo: charToInt('4') retorna: 4.
int charToInt(char ch)
{
   int i = -1;
   if( (ch>47)&&(ch<58) )
   {
      i = ch-48;
   }
   else
      if( (ch>64)&&(ch<91) )
      {
         i = ch-55;
      }
      else
         if( (ch>96)&&(ch<123) )
         {
            i = ch-87;
         }
   return i;
}

// Retorna el valor char de i.
// Ejemplo: intToChar(4) retorna: '4'.
char intToChar(int i)
{
   char c = '!';
   if( (i>=0)&&(i<=9) )
   {
      c = i+48;
   }
   else
      if( (i>9)&&(i<36) )
      {
         c = i+55;
      }
   return c;
}

// retorna el i-esimo digito de n contando desde la derecha empezando de 0
int getDigit(int n, int i) // ok
{
   int p = intPow(10,i+1);
   n = n%p;
   int p1 = intPow(10,i);
   n = n/p1;
   return n;
}

int digitCount(int i) // ok
{
   if( i==0 )
   {
      return 1;
   }
   else
   {
      int h = 1;
      int j;
      double p = 1;
      for( j = 0; h!=0; j++ )
      {
         h = i/p;
         p = p*10;
      }
      return j-1;
   }
}

string intToString(int num) // ok
{
   string s = "";
   if( num<0 )
   {
      s = "-";
      num = num*-1;
   }
   for( int i = (digitCount(num)); i>0; i-- )
   {
      s = s+intToChar(getDigit(num,i-1));
   }

   return s;
}

int stringToInt(string s) // ok
{
   int res = 0;
   int l = length(s);
   for( int i = (l-1); i>=0; i-- )
   {
      char z = s[i];
      int c = charToInt(z);
      int d = l-i-1;
      int p = intPow(10,d);
      res = res+(c*p);
   }
   return res;
}

int stringToInt(string s, int b) // ok
{
   int res = 0;
   int l = length(s);
   for( int i = (l-1); i>=0; i-- )
   {
      char z = s[i];
      int c = charToInt(z);
      int d = l-i-1;
      int p = intPow(10,d);
      res = res+(c*p);
   }
   return res;
}

string boolToString(bool b) // ok
{
   return b?"1":"0";
}

bool stringToBool(string s)
{
   return s[0]==0?false:true;
}

string charToString(char c)
{
   string s = "";
   s = s+c;
   return s;
}

char stringToChar(string s)
{
   char c = s[0];
   return c;
}

string doubleToString(double d)
{
   int a = d;
   int b = (d-a)*1000000000;
   for( int i = 1; (b!=0)&&(b%10==0); i++ )
   {
      b = b/10;
   }
   string s = intToString(a)+"."+intToString(b);
   return s;
}

double stringToDouble(string s)
{
   int pos = indexOf(s,'.');
   string entero = substring(s,0,pos);
   string decimal = substring(s,pos+1);
   int e = stringToInt(entero);
   double d = stringToInt(decimal);
   int p = intPow(10,digitCount(d));
   double r = e+(d/p);

   return r;
}

string stringToString(string s)
{
   return s;
}

bool isEmpty(string s)
{
   bool empty = false;
   if( s[0]=='\0' )
   {
      empty = true;
   }
   return empty;
}

bool contains(string s, char c)
{
   return lastIndexOf(s,c)==-1?false:true;
}

string replace(string s, char oldChar, char newChar)
{
   while( contains(s,oldChar) )
   {
      s[lastIndexOf(s,oldChar)] = newChar;
   }
   return s;
}

string insertAt(string s, int pos, char c)
{
   string sub1 = substring(s,0,pos);
   string sub2 = substring(s,pos);
   s = sub1+c+sub2;
   return s;
}

string removeAt(string s, int pos)
{
   string sub1 = substring(s,0,pos);
   string sub2 = substring(s,pos+1);
   s = sub1+sub2;
   return s;
}

string ltrim(string s)
{
   while( s[0]==' ' )
   {
      s = removeAt(s,0);
   }
   return s;
}

string rtrim(string s)
{
   int l = length(s)-1;
   while( s[l]==' ' )
   {
      s = removeAt(s,l);
      l--;
   }
   return s;
}

string trim(string s)
{
   s = (rtrim(ltrim(s)));
   return s;
}

string replicate(char c, int n)
{
   string s = "";
   for( int i = 0; i<n; i++ )
   {
      s = s+c;
   }

   return s;
}

string spaces(int n)
{
   return replicate(' ',n);
}

string lpad(string s, int n, char c)
{
   string r;
   if( n>=length(s) )
   {
      r = replicate(c,n-length(s))+s;
   }
   else
   {
      r = substring(s,length(s)-n);
   }
   return r;
}

string rpad(string s, int n, char c)
{
   string r;
   if( n>=length(s) )
   {
      r = s+replicate(c,n-length(s));
   }
   else
   {
      r = substring(s,0,n);
   }
   return r;
}

string cpad(string s, int n, char c)
{

   if( n>=length(s) )
   {
      for( int i = 0; length(s)<n; i++ )
      {
         if( i%2==0 )
         {
            s = c+s;
         }
         else
         {
            s = s+c;
         }
      }
   }
   else
   {
      for( int i = 0; n<length(s); i++ )
      {
         if( i%2==0 )
         {
            s = removeAt(s,0);
         }
         else
         {
            s = removeAt(s,length(s)-1);
         }
      }
   }
   return s;
}

bool isDigit(char c)
{
   return (c>47)&&(c<58)?true:false;
}

bool isLetter(char c)
{
   return ((c>64)&&(c<91))||((c>96)&&(c<123))?true:false;
}

bool isUpperCase(char c)
{
   return ((c>64)&&(c<91))?true:false;
}

bool isLowerCase(char c)
{
   return ((c>96)&&(c<123))?true:false;
}

char toUpperCase(char c)
{
   if( isLowerCase(c) )
   {
      c = c-32;
   }
   return c;
}

char toLowerCase(char c)
{
   if( isUpperCase(c) )
   {
      c = c+32;
   }
   return c;
}

int cmpString(string a, string b)
{
   return a>b?1:a<b?-1:0;
}

bool endsWith(string a, string b){
   bool r = true;
   int largoA = length(a);
   int largoB = length(b);
   int j = largoA - 1;
   for(int i = largoB-1; i>=0; i--){
      if(b[i]!=a[j]){
         r = false;
      }
      j--;
   }
   return r;
}

#endif
