/*
	Written by Devon Beckett & Priyal Patel
	Year of 2014
	This code provides the implementation of a three dimensional binary 
	search tree. 
	Use:
		KDTreeNode* insert(KDTreeNode* N, KDTreeNode* T)
			Inserts node N into tree T. The return value is a pointer to T.

		KDTreeNode* find(int C[], KDTreeNode* T)
			Finds the node matching the key of C. Will return NULL if the
			node cannot be found.
		
		KDTreeNode* findNearest(int C[], KDTreeNode* T, KDTreeNode* NN)
			Finds the closest match to C in the tree. NN should always
			equall NULL when first called. The code uses it for 
			recurssive calls.

		KDTreeNode* delete(KDTreeNode* N, KDTreeNode* T)
			Will remove a node from a tree. Returns a pointer to the 
			root of the tree. WARNING: If the node does not exist in
			the tree the program will Seg fault.

		KDTreeNode* create_a(int C[], char* img)
			This will create a new node from an array and return the
			pointer to it.

		KDTreeNode* create_i(int C0, int C1, int C2, char* img)
			This will create a new node from three integers and return
			the pointer to it.
		
		void printTree(KDTreeNode* T)
			Will print the entire tree to STDOUT.

		void printNode(KDTreeNode* N)
			Will print a single node to STDOUT.
*/

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
KDTreeNode* findNearest(int C[], KDTreeNode* T, KDTreeNode* NN){
	if(T != NULL){
		// set the first NN to the first leaf found
		if(NN == NULL){
			if(T->left == NULL && T->right == NULL){
				return T;
			}
		}
		
		if(C[0] < T->color[0]){
			NN = findNearest2(C, T->left, NN);
			if(eval(C,T) < eval(C,NN)){
				NN = T;
			}
			NN = findNearest2(C, T->right, NN);
		} else {
			NN = findNearest2(C, T->right, NN);
			if(eval(C,T) < eval(C,NN)){
				NN = T;
			}
			NN = findNearest2(C, T->left, NN);
		}		
	}
	return NN;
}

KDTreeNode* findNearest2(int C[], KDTreeNode* T, KDTreeNode* NN){
	if(T != NULL){
		// set the first NN to the first leaf found
		if(NN == NULL){
			if(T->left == NULL && T->right == NULL){
				return T;
			}
		}

		if(C[1] < T->color[1]){
			NN = findNearest3(C, T->left, NN);
			if(eval(C,T) < eval(C,NN)){
				NN = T;
			}
			//NN = findNearest3(C, T->right, NN);
		} else {
			NN = findNearest3(C, T->right, NN);
			if(eval(C,T) < eval(C,NN)){
				NN = T;
			}
			NN = findNearest3(C, T->left, NN);
		}	
	}
	return NN;
}

KDTreeNode* findNearest3(int C[], KDTreeNode* T, KDTreeNode* NN){
	if(T != NULL){
		// set the first NN to the first leaf found
		if(NN == NULL){
			if(T->left == NULL && T->right == NULL){
				return T;
			}
		}

		if(C[2] < T->color[2]){
			NN = findNearest(C, T->left, NN);
			if(eval(C,T) < eval(C,NN)){
				NN = T;
			}
			NN = findNearest(C, T->right, NN);
		} else {
			NN = findNearest(C, T->right, NN);
			if(eval(C,T) < eval(C,NN)){
				NN = T;
			}
			NN = findNearest(C, T->left, NN);
		}	
	}
	return NN;
}

int eval(int C[], KDTreeNode* N){
	int r, g, b;
	r = (C[0] - N->color[0]);
	g = (C[1] - N->color[1]);
	b = (C[2] - N->color[2]);
	r = (r*r);
	g = (g*g);
	b = (b*b);
	return r + g + b;
}

/* This function will delete a node from the tree. The return value is a
pointer to the root node of the tree. The deleted node is freed from memory. 
Warning if the node does not exist in the tree it will Seg Fault.*/
KDTreeNode* delete(KDTreeNode* N, KDTreeNode* T){
	if(N != NULL){
		if(N == T){
			if(N->left == NULL && N->right != NULL){
				T = T->right;
			} else if(N->left != NULL && N->right == NULL){
				T = T->left;
			} else if(N->left == NULL && N->right == NULL){
				T == NULL;
			} else{
				T = T->left;
				insert(N->right, T);
			}
		} else {
			// N has one child on the right
			if(N->left == NULL && N->right != NULL){
				if(N->parent->left == N){
					N->parent->left = N->right;
				} else {
					N->parent->right = N->right;
				}
			// N has one child on the left
			} else if(N->left != NULL && N->right == NULL){
				if(N->parent->left == N){
					N->parent->left = N->left;
				} else {
					N->parent->right = N->left;
				}
			// N has no children
			} else if(N->left == NULL && N->right == NULL){
				if(N->parent->left == N){
					N->parent->left = NULL;
				} else {
					N->parent->right = NULL;
				}
			// N has two children
			} else{
				if(N->parent->left == N){
					N->parent->left = NULL;
				} else {
					N->parent->right = NULL;
				}
				insert(N->left, T);
				insert(N->right, T);
			}
		}
		free(N);
	}
	return T;
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
				if(T->left == N){
					N->parent = T;
				}
			} else {
				T->right = insert2(N, T->right);
				if(T->right == N){
					N->parent = T;
				}
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
			if(T->left == N){
				N->parent = T;
			}
		} else {
			T->right = insert3(N, T->right);
			if(T->right == N){
				N->parent = T;
			}
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
			if(T->left == N){
				N->parent = T;
			}
		} else {
			T->right = insert(N, T->right);
			if(T->right == N){
				N->parent = T;
			}
		}
	}
	return T;
}

/* This function will return a pointer to a new KDTreeNode created from 
an array. */
KDTreeNode* create_a(int C[], char* img){
	KDTreeNode* N = (KDTreeNode*)malloc(sizeof(KDTreeNode));
	N->color[0] = C[0];
	N->color[1] = C[1];
	N->color[2] = C[2];
	N->img = img;
	N->left = NULL;
	N->right = NULL;
	N->parent = NULL;
	return N;
}

/* This function will return a pointer to a new KDTreeNode created from 
three integers. */
KDTreeNode* create_i(int C0, int C1, int C2, char* img){
	KDTreeNode* N = (KDTreeNode*)malloc(sizeof(KDTreeNode));
	N->color[0] = C0;
	N->color[1] = C1;
	N->color[2] = C2;
	N->img = img;
	N->left = NULL;
	N->right = NULL;
	N->parent = NULL;
	return N;
}

/* This function will print the tree to the console */
void printTree(KDTreeNode* T){
	if(T != NULL){
		printNode(T);
		printf("\n\tleft->");
		printNode(T->left);
		printf("\n\tright->");
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
