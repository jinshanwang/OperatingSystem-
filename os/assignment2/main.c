// a1710974 Jinshan Wang
// a1701108 Jiarong Fan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include "page.h"

int main(int argc, char const *argv[]) {
// ./menmin input_file.tarce pagesize numspage algorithm
// It will be run using (see sec�on Running your code below for more details)

// get access to the arguements
FILE* fp;
int   PAGESIZE=atoi(argv[2]);
int   NUMPAGES=atoi(argv[3]);
char* ALGORITHM;
ALGORITHM=(char*)malloc(sizeof(char)*4);
strcpy(ALGORITHM,argv[4]);

int   INTERVAL;
if ((fp = fopen(argv[1],"r"))==NULL) {
  printf("cannot open file\n");
  exit(0);
}
if (argc==6) {
  INTERVAL=atoi(argv[5]);
}

if (strcmp(argv[4],"SC")==0) {
  SC(fp,PAGESIZE,NUMPAGES);
  // printf("%s\n", argv[4]);
}
else if (strcmp(argv[4],"ESC")==0) {
   ESC(fp,PAGESIZE,NUMPAGES);
  //printf("%s\n", argv[4]);
}
else if (strcmp(argv[4],"ARB")==0) {

  ARB(fp,PAGESIZE,NUMPAGES,INTERVAL);

}
else if (strcmp(argv[4],"EARB")==0) {
  EARB(fp,PAGESIZE,NUMPAGES,INTERVAL);

}


  return 0;
}
