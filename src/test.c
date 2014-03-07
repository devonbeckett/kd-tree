#include <stdio.h>
#include "kdtree.h"

int main(int argc, char *argv[]){
	int c[3];
	KDTreeNode* T = NULL;
	KDTreeNode* N;
	KDTreeNode* P = NULL;

	T = insert(create_i(50,50,50,"test1"), T);
	T = insert(create_i(150,50,50,"test2"), T);
	T = insert(create_i(50,150,50,"test3"), T);
	T = insert(create_i(50,0,50,"test4"), T);
	T = insert(create_i(210,50,50,"test5"), T);
	T = insert(create_i(50,50,0,"test6"), T);
	T = insert(create_i(50,5,0,"test7"), T);
	T = insert(create_i(50,50,50,"test8"), T);

	int I[3] = {50,50,50};
	P = find(I, T);
	if(P == NULL){
		printf("Could not find (%d,%d,%d). Now searching for nearest result.\n", I[0], I[1], I[2]);
		//P = findNearest(I, T, NULL);
	}
	if(P == NULL){
		printf("FAILURE!\n");
	} else {
		printf("(%d,%d,%d) found. \"%s\"\n\n", (P->color)[0], (P->color)[1], (P->color)[2], P->img);
	}
	
	printTree(T);

	exit(0);
}