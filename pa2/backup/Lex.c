//Mythili Karra
//////mmkarra
//////CS101
//////04/18/2019
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define MAX_LEN 255
	int  main (int argc, char* argv[]) {
		FILE* in;
		FILE* out;
		if(argc != 3) {
			printf("Usage: FileIO in out");
			exit(1);
		}
		int w = 0;
		int l = 0;
		char x[MAX_LEN];
		in = fopen(argv[1], "r");
		out = fopen(argv[2], "w");
		if(in == NULL) {
			printf("File %s does not exist", argv[1]);
			exit(1);
		}
		if(out == NULL) {
			printf("File %s does not exist", argv[2]);
			exit(1);
		}
		while(fgets(x, MAX_LEN, in) != NULL) {
			l++;
		}
		char array[l][MAX_LEN];
		rewind(in);
		while(fgets(x,MAX_LEN, in)) {
			strcpy(array[w], x);
			w++;
		}
		List list = newList();
		int i, j;
		char* temp;
		append(list,0);
		moveFront(list);
		for(j = 1; j < l; j++) {
			temp = array[j];
			while(index(list) >= 0 && strncmp(temp,array[get(list)],MAX_LEN) < 0) {
				movePrev(list);
			}
			if(index(list) < 0) {
				prepend(list, j);
			}
			else {
				if(index(list) != length(list)-1) {
					insertAfter(list,j);
				}
				else {
					append(list,j);
				}
			}
			moveBack(list);
		}
		moveFront(list);
		while(index(list) > -1) {
			fprintf(out, "%s", array[get(list)]);
			moveNext(list);
		}
		fclose(in);
		fclose(out);
		freeList(&list);
}


