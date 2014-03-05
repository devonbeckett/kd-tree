#include "kdtree.h"
#include <stdio.h>

/* This function will return the first exact match for the color input
and NULL if there is none. */
KDTreeNode* find(int C[], KDTreeNode* T){
	if(T != NULL){
		if(colorMatch(C, T)){
			return T;
		} else {
			if(C[0] < T->color[0]){
				return find2(C, T->left);
			} else {
				return find2(C, T->right);
			}
		}
	}
	return NULL;
}

KDTreeNode* find2(int C[], KDTreeNode* T){
	if(T != NULL){
		if(colorMatch(C, T)){
			return T;
		} else {
			if(C[1] < T->color[1]){
				return find3(C, T->left);
			} else {
				return find3(C, T->right);
			}
		}
	}
	return NULL;
}

KDTreeNode* find3(int C[], KDTreeNode* T){
	if(T != NULL){
		if(colorMatch(C, T)){
			return T;
		} else {
			if(C[2] < T->color[2]){
				return find(C, T->left);
			} else {
				return find(C, T->right);
			}
		}
	}
	return NULL;
}

/* This function compares a node's color with a color argument and
returns true if it is a match and false if not. */
int colorMatch(int C[], KDTreeNode* N){
	if(N->color[0] == C[0]){
		if(N->color[1] == C[1]){
			if(N->color[2] == C[2]){
				return 1;
			}
		}
	}
	return 0;
}

/* This function will return the first nearest match for the color input
and NULL if the tree is empty. */
KDTreeNode* findNearest(int C[], KDTreeNode* T, KDTreeNode* N){
	if(T != NULL){
		if(!eval(C, T)){
			return T;
		} else {
			if(C[0] < T->color[0]){
				return findNearest2(C, T->left, T);
			} else {
				return findNearest2(C, T->right, T);
			}
		}
	}
	return N;
}

KDTreeNode* findNearest2(int C[], KDTreeNode* T, KDTreeNode* N){
	if(T != NULL){
		if(colorMatch(C, T)){
			return T;
		} else {
			if(C[1] < T->color[1]){
				return findNearest3(C, T->left, T);
			} else {
				return findNearest3(C, T->right, T);
			}
		}
	}
	return N;
}

KDTreeNode* findNearest3(int C[], KDTreeNode* T, KDTreeNode* N){
	if(T != NULL){
		if(colorMatch(C, T)){
			return T;
		} else {
			if(C[2] < T->color[2]){
				return findNearest(C, T->left, T);
			} else {
				return findNearest(C, T->right, T);
			}
		}
	}
	return N;
}

int eval(int C[], KDTreeNode* N){
	int r, g, b;
	r = abs(C[0] - N->color[0]);
	g = abs(C[1] - N->color[1]);
	b = abs(C[2] - N->color[2]);
	return r + g + b;
}

int abs(int n){
	if(n < 0){
		n = n * (-1);
	}
	return n;
}

/* This function will delete a node from the tree. The return value will
be true if the node was deleted and false if the node was not found. */
int delete(int C[], KDTreeNode* T){
	if(T != NULL){
		if(colorMatch(C, T)){
			return 1;
		} else {
			if(C[0] < T->color[0]){
				return delete2(C, T->left);
			} else {
				return delete2(C, T->right);
			}
		}
	}
	return 0;
}

int delete2(int C[], KDTreeNode* T){
	KDTreeNode N;
	if(T != NULL){
		if(colorMatch(C, T)){
			return 1;
		} else {
		if(C[1] < T->color[1]){
				return delete3(C, T->left);
			} else {
				return delete3(C, T->right);
			}
		}
	}
	return 0;
}

int delete3(int C[], KDTreeNode* T){
	KDTreeNode N;
	if(T != NULL){
		if(colorMatch(C, T)){
			return 1;
		} else {
			if(C[2] < T->color[2]){
				return delete(C, T->left);
			} else {
				return delete(C, T->right);
			}
		}
	}
	return 0;
}

/* This will insert a new node in the tree. If T is a NULL it will 
return a pointer to the new node. */
KDTreeNode* insert(KDTreeNode* N, KDTreeNode* T){
	if(N != NULL){
		if(T == NULL){
			T = N;
		} else {
			if(T->color[0] > N->color[0]){
				T->left = insert2(N, T->left);
			} else {
				T->right = insert2(N, T->right);
			}
		}
	}
	return T;
}

KDTreeNode* insert2(KDTreeNode* N, KDTreeNode* T){
	if(T == NULL){
		T = N;
	} else {
		if(T->color[1] > N->color[1]){
			T->left = insert3(N, T->left);
		} else {
			T->right = insert3(N, T->right);
		}
	}
	return T;
}

KDTreeNode* insert3(KDTreeNode* N, KDTreeNode* T){
	if(T == NULL){
		T = N;
	} else {
		if(T->color[2] > N->color[2]){
			T->left = insert(N, T->left);
		} else {
			T->right = insert(N, T->right);
		}
	}
	return T;
}

/* This function will return a pointer to a new KDTreeNode */
KDTreeNode create_a(int C[], char* img){
	KDTreeNode N = {(N.color)[0] = C[0], (N.color)[1] = C[1], (N.color)[2] = C[2], img, NULL, NULL};
	return N;
}

KDTreeNode* create_i(int C0, int C1, int C2, char* img){
	KDTreeNode* N = (KDTreeNode*)malloc(sizeof(KDTreeNode));
	N->color[0] = C0;
	N->color[1] = C1;
	N->color[2] = C2;
	N->img = img;
	N->left = NULL;
	N->right = NULL;
	return N;
}

/* This function will print the tree to the console */
void printTree(KDTreeNode* T){
	if(T != NULL){
		printNode(T);
		printf(" left->");
		printNode(T->left);
		printf(" right->");
		printNode(T->right);
		printf("\n");
		printTree(T->left);
		printTree(T->right);
	}
}

void printNode(KDTreeNode* N){
	if(N != NULL){
		printf("(%d,%d,%d)%s", N->color[0], N->color[1], N->color[2], N->img);
	} else {
		printf("NULL");
	}
}