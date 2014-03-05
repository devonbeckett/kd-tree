#include <string.h>
#include <stdlib.h>

typedef struct KDTreeNode KDTreeNode;
struct KDTreeNode{
	int color[3];
	char* img;
	KDTreeNode* left;
	KDTreeNode* right;
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
KDTreeNode* findNearest(int C[], KDTreeNode* T, KDTreeNode* N);
KDTreeNode* findNearest2(int C[], KDTreeNode* T, KDTreeNode* N);
KDTreeNode* findNearest3(int C[], KDTreeNode* T, KDTreeNode* N);

/* This function will delete a node from the tree. The return value will
be true if the node was deleted and false if the node was not found. */
int delete(int C[], KDTreeNode* T);
int delete2(int C[], KDTreeNode* T);
int delete3(int C[], KDTreeNode* T);

/* This will insert a new node in the tree. If T is a NULL it will 
construct a new node and return a pointer to it*/
KDTreeNode* insert(KDTreeNode* N, KDTreeNode* T);
KDTreeNode* insert2(KDTreeNode* N, KDTreeNode* T);
KDTreeNode* insert3(KDTreeNode* N, KDTreeNode* T);