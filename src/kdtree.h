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
#ifndef KDTREE_H_
#define KDTREE_H_

#include <string.h>
#include <stdlib.h>
#include "cv.h"
#include "highgui.h"

typedef struct KDTreeNode KDTreeNode;
struct KDTreeNode{
	int color[3];
	IplImage* img;
	KDTreeNode* left;
	KDTreeNode* right;
	KDTreeNode* parent;
};

/* This function will return the first exact match for the color input
and NULL if there is none. */
KDTreeNode* find(int C[], KDTreeNode* T);
KDTreeNode* find2(int C[], KDTreeNode* T);
KDTreeNode* find3(int C[], KDTreeNode* T);

/* This function compares a node's color with a color argument and
returns true if it is a match and false if not. */
int colorMatch(int C[], KDTreeNode* N);

/* This function will return the first nearest match for the color input
and NULL if the tree is empty. */
KDTreeNode* findNearest(int C[], KDTreeNode* T, KDTreeNode* NN);
KDTreeNode* findNearest2(int C[], KDTreeNode* T, KDTreeNode* NN);
KDTreeNode* findNearest3(int C[], KDTreeNode* T, KDTreeNode* NN);
int eval(int C[], KDTreeNode* N);

/* This function will delete a node from the tree. The return value is a
pointer to the root node of the tree. The deleted node is freed from memory. 
Warning if the node does not exist in the tree it will Seg Fault.*/
KDTreeNode* delete(KDTreeNode* N, KDTreeNode* T);

/* This will insert a new node in the tree. If T is a NULL it will 
construct a new node and return a pointer to it*/
KDTreeNode* insert(KDTreeNode* N, KDTreeNode* T);
KDTreeNode* insert2(KDTreeNode* N, KDTreeNode* T);
KDTreeNode* insert3(KDTreeNode* N, KDTreeNode* T);

/* This function will return a pointer to a new KDTreeNode created from 
an IplImage. */
KDTreeNode* create(IplImage* img);

/* This function will return a pointer to a new KDTreeNode created from 
an array. */
KDTreeNode* create_a(int C[], IplImage* img);

/* This function will return a pointer to a new KDTreeNode created from 
three integers. */
KDTreeNode* create_i(int C0, int C1, int C2, IplImage* img);

/* This function will print the tree to the console */
void printTree(KDTreeNode* T);
void printNode(KDTreeNode* N);
#endif