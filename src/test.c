#include <stdio.h>
#include "kdtree.h"


/* This program was just used to test out the functionality of the 3d-tree. */
int main(int argc, char *argv[]){
	int c[3];
	KDTreeNode* T = NULL;
	KDTreeNode* T2 = NULL;
	KDTreeNode* N;
	KDTreeNode* P = NULL;

	T = insert(create_i(50,50,50,"test1"), T);
	T = insert(create_i(150,50,50,"test2"), T);
	T = insert(create_i(50,150,50,"test3"), T);
	T = insert(create_i(50,0,50,"test4"), T);
	T = insert(create_i(210,50,50,"test5"), T);
	T = insert(create_i(50,50,0,"test6"), T);
	T = insert(create_i(50,5,0,"test7"), T);
	T = insert(create_i(50,72,50,"test8"), T);
	T = insert(create_i(50,243,50,"test9"), T);
	T = insert(create_i(50,2,5,"test10"), T);
	T = insert(create_i(7,84,0,"test11"), T);
	T = insert(create_i(23,97,150,"test12"), T);
	T = insert(create_i(0,123,20,"test13"), T);
	T = insert(create_i(9,57,30,"test14"), T);
	T = insert(create_i(253,9,57,"test15"), T);
	T = insert(create_i(92,0,59,"test16"), T);
	T = insert(create_i(67,0,250,"test17"), T);
	T = insert(create_i(12,0,180,"test18"), T);
	T = insert(create_i(16,0,72,"test19"), T);
	T = insert(create_i(28,40,89,"test20"), T);
	T = insert(create_i(198,60,163,"test21"), T);
	T = insert(create_i(32,70,50,"test22"), T);
	T = insert(create_i(219,210,55,"test23"), T);
	T = insert(create_i(128,64,5,"test24"), T);
	T = insert(create_i(87,15,2,"test25"), T);
	T = insert(create_i(52,12,8,"test26"), T);
	T = insert(create_i(23,255,6,"test27"), T);
	T = insert(create_i(0,60,0,"test28"), T);
	T = insert(create_i(50,10,50,"test29"), T);
	T = insert(create_i(40,11,50,"test30"), T);
	T = insert(create_i(213,111,50,"test31"), T);
	T = insert(create_i(12,222,50,"test32"), T);

	int I[3] = {50,50,50};
	P = find(I, T);
	if(P == NULL){
		printf("Could not find (%d,%d,%d). Now searching for nearest result.\n", I[0], I[1], I[2]);
		P = findNearest(I, T, NULL);
	}
	if(P == NULL){
		printf("FAILURE!\n");
	} else {
		printf("(%d,%d,%d) found. \"%s\"\n\n", (P->color)[0], (P->color)[1], (P->color)[2], P->img);
	}
	
	printTree(T);

	exit(0);
}