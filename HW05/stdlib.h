#include <stdint.h>
#include <stdbool.h>
/*
#ifndef __MYSTDLIB_H__
#define __MYSTDLIB_H__
*/
#define     SUART0      0xC0000000
long        time();
long        insn();
char* malloc(int size);
void* memcpy(void* dest, const void* src, long n);
char* strcpy(char* dest, const char* src);
int         strcmp(const char* s1, const char* s2);
void        printf_c(int c);
void        printf_s(char* p);
void        printf_d(int val);
int         R_printf(const char* format, ...);
int  puts(const char* s);
//#endif