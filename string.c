#include "types.h"
#include "x86.h"

void*
memset(void *dst, int c, uint n)
{
  if ((int)dst%4 == 0 && n%4 == 0){
    c &= 0xFF;
    stosl(dst, (c<<24)|(c<<16)|(c<<8)|c, n/4);
  } else
    stosb(dst, c, n);
  return dst;
}

int
memcmp(const void *v1, const void *v2, uint n)
{
  const uchar *s1, *s2;

  s1 = v1;
  s2 = v2;
  while(n-- > 0){
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }

  return 0;
}

void*
memmove(void *dst, const void *src, uint n)
{
  const char *s;
  char *d;

  s = src;
  d = dst;
  if(s < d && s + n > d){
    s += n;
    d += n;
    while(n-- > 0)
      *--d = *--s;
  } else
    while(n-- > 0)
      *d++ = *s++;

  return dst;
}

// memcpy exists to placate GCC.  Use memmove.
void*
memcpy(void *dst, const void *src, uint n)
{
  return memmove(dst, src, n);
}

int
strncmp(const char *p, const char *q, uint n)
{
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

char*
strncpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  while(n-- > 0 && (*s++ = *t++) != 0)
    ;
  while(n-- > 0)
    *s++ = 0;
  return os;
}

// Like strncpy but guaranteed to NUL-terminate.
char*
safestrcpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  if(n <= 0)
    return os;
  while(--n > 0 && (*s++ = *t++) != 0)
    ;
  *s = 0;
  return os;
}

int
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}
////////////////customized functions by woohyuk yang///////////////////////////

char* cStrcat(char* first, char* second){

  int i = strlen(first);
  int j = 0;

  while(second[j] != '\0')
    first[i++] = second[j++];

  return first;
}

char* cStrtok(char* str, char* deli){


  int i = 0;
  for(; str[i]!=0; i++){
      if(str[i] == *deli){
          str[i] = '\0';
          return str;
      }
  }
  return '\0';
}

char* cStrToUpper(char* str){

  while(*str != '\0'){
    if(*str>=97 && *str<=122)
      *str -= 32;
    str++;
  }

  return str;
}

char* cStrToLower(char* str){

  while(*str != '\0'){
    if(*str>=65 && *str<=90)
      *str += 32;
    str++;
  }

  return str;
}



char* cRevString(char* str){

  int len;
  int i;
  char temp;

  len = strlen(str);
  for(i = 0; i < len / 2; i++){

    temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;

  }

  return str;
}
//Hexadecimal to integer
int hexStringToInt(char* str){

  int reValue = 0;
  int i;
  for(; str[i] != '\0'; i++){
      reValue *= 16;
      if(('A' <= str[i]) && (str[i] <= 'Z'))
        reValue += (str[i] - 'A') + 10;
      else if(('a' <= str[i]) && (str[i] <= 'z'))
        reValue += (str[i] - 'a') + 10;
      else
        reValue += str[i] - '0'; 
  }

  return reValue;
}

//decimal to integer
int decStringToInt(char* str){

  int reValue = 0;
  int i;

  if(str[0] == '-')
    i = 1;
  else
    i = 0;

  for(; str[i] != '\0'; i++){
    reValue *= 10;
    reValue += str[i] - '\0';
  }

  if(str[0] == '-')
    reValue = -reValue;

  return reValue;
}


//customized atoi; I implemented this without knowing atoi exists already. but I just did not delete it 
//woohyuk yang
int cAtoi(char* str, int base){

  int reValue = 0;
  switch(base){

  case 16:
      reValue = hexStringToInt(str);
      break;
  case 10:
      reValue = decStringToInt(str);
      break;
  }

  return reValue;
}

int hexToString(int number, char* str){

  int i = 0; 
  int curValue = 0;

  if( number == 0){
    str[0] = '0';
    str[1] = '\0';
    return 1;
  }

  for(; curValue > 0; i++){

    curValue = number % 16;
    if( curValue >= 10)
      str[i] = 'A' + (curValue - 10);
    else
      str[i] = '0' + curValue;
    
    number = number / 16;
  }

  str[i] = '\0';

  cRevString(str);
  return i;
}


int decToString(int number, char* str){

  int i;

  if(number == 0){
    str[0] = '0';
    str[1] = '\0';
    return 1;
  }

  if(number < 0){
    i = 1;
    str[0] = '-';
    number = -number;
  }
  else
    i = 0;

  for(; number > 0; i++){

    str[i] = '0' + number % 10;
    number = number / 10;
  }

  str[i] = '\0';

  if( str[0] == '-')
    cRevString(&(str[1]));
  else
    cRevString(str);

  return i;
}


int cItoa(int number, char* str, int base){

  int reValue = 0;

  switch(base){

    case 16:
      reValue = hexToString(number, str);
      break;

    case 10:
      reValue = decToString(number, str);
      break;
  }

  return reValue;

}



