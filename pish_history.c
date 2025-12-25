#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "pish.h"

static char pish_history_path[1024] = {'\0'};



/*
 * Set history file path to ~/.pish_history.
 */
static void set_history_path()
{
    const char *home = getpwuid(getuid())->pw_dir;
    strncpy(pish_history_path, home, 1024);
    strcat(pish_history_path, "/.pish_history");
}

void add_history(const struct pish_arg *arg)
{
    // set history path if needed
    if (!(*pish_history_path)) {
        set_history_path();
    }
   if (arg->argc==0){
	   return;
   }
   FILE *fp= fopen(pish_history_path, "a");
   if(fp ==NULL){
	   perror("open");
	   return;
   }

 for (int i =0; i< arg->argc; i++) {
	 fputs(arg->argv[i], fp);
	 if(i < arg->argc -1){
		 fputc(' ', fp);
	 }
 }
 fputc('\n', fp);
  fclose(fp);
}




/* 
* - open (and create if needed) history file at pish_history_pat
* - write out the command stored in `arg`; argv values are separated
*   by a space.
*/


void print_history(){

    // set history path if needed
    if (!(*pish_history_path)) {
        set_history_path();
    }

  FILE *fp=fopen(pish_history_path, "r");
		  if (fp == NULL) {
		  return;
		  }
   char buffer[1000];
   int index =1;
   while (fgets(buffer, sizeof(buffer), fp)!=NULL){
	   printf("%d %s", index, buffer);
	   index++;
   }
 fclose(fp);



/*  read history file and print with index */
}
