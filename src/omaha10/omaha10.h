#ifndef OMAHA10_H
#define OMAHA10_H

#include <stdio.h>

int repl(char* json);
int ccnt(const int* cards, const int cnt);
int init(int deck[52]);
int kick(int deck[52], int decksz, const int* dead, const int deadsz);
int push(int deck[52], int decksz, const int card);
int eror(char* json, char* info);
int eval_OT(const int b1, const int b2, const int b3, const int b4, const int b5, const int h1, const int h2, const int h3, const int h4, const int h5);
int calc_OT(const int hands[][5], const int hsz, const int* board, const int bsz, const int* deads, const int dsz, char* json);
int calc_OT2(const int h1[5], const int h2[5], const int deck[52], const int ftrsz[5], char* json);
int calc_OT3(const int h1[5], const int h2[5], const int h3[5], const int deck[52], const int ftrsz[5], char* json);
int calc_OT4(const int h1[5], const int h2[5], const int h3[5], const int h4[5], const int deck[52], const int ftrsz[5], char* json);
int calc_OT5(const int h1[5], const int h2[5], const int h3[5], const int h4[5], const int h5[5], const int deck[52], const int ftrsz[5], char* json);
int calc_OT6(const int h1[5], const int h2[5], const int h3[5], const int h4[5], const int h5[5], const int h6[5], const int deck[52], const int ftrsz[5], char* json);

#endif // OMAHA10_H
