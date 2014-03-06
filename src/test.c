#include <stdio.h>
#include "kdtree.h"

int main(int argc, char *argv[]){
	int i;
	int c[3];
	KDTreeNode* T;
	//KDTreeNode N;
	KDTreeNode* P;

	/*for(i=0;i<50;i++){
		c[0] = i*(i%3);
		c[1] = i*(i%3);
		c[2] = i*(i%3);
		KDTreeNode n = {(n.color)[0] = c[0], (n.color)[1] = c[1], (n.color)[2] = c[2],
			.img = "path", .left = NULL, .right = NULL};
		T = insert(&n, T);
	}
	int I[3] = {50,50,50};
	N = find(I, T);
	if(N == NULL){
		
		N = findNearest(I, T, NULL);
	}
	if(N == NULL){
		printf("FAILURE!");
	} else {
		printf("R%d, G%d, B%d, %s", (N->color)[0], (N->color)[1], (N->color)[2], N->img);
	}
	*/
	int I[3] = {50,50,50};
	KDTreeNode N = {(N.color)[0] = I[0], (N.color)[1] = I[1], (N.color)[2] = I[2], "test", NULL, NULL};
	T = insert(&N, T);
	I[0]++;
	I[1]++;
	I[2]++;
	P = find(I, T);
	if(P == NULL){
		printf("Could not find (%d,%d,%d). Now searching for nearest result.\n", I[0], I[1], I[2]);
		P = findNearest(I, T, NULL);
	}
	if(P == NULL){
		printf("FAILURE!\n");
	} else {
		printf("(%d,%d,%d) found.\n", (P->color)[0], (P->color)[1], (P->color)[2]);
	}
	exit(0);
}