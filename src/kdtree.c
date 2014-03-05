#include "kdtree.h"

/* This function will return the first exact match for the color input
and NULL if there is none. */
KDTreeNode* find(int * C[], KDTreeNode* T){

	return NULL;
}

/* This function compares a node's color with a color argument and
returns true if it is a match and false if not. */
bool colorMatch(int * C[], KDTreeNode* N){
	if(N->color[0] == C[0]){
		if(N->color[1] == C[1]){
			if(N->color[2] == C[2]){
				return true;
			}
		}
	}
	return false;
}

/* This function will return the first nearest match for the color input
and NULL if the tree is empty. */
KDTreeNode* findNearest(int * C[], KDTreeNode* T){
	return NULL;
}

/* This function will delete a node from the tree. The return value will
be true if the node was deleted and false if the node was not found. */
bool delete(int * C[], KDTreeNode* T){
	if(T != NULL){
		if(colorMatch(C, T)){
			// delete
		} else {
			delete1(C, T);
		}
	}
	return false;
}

KDTreeNode* delete1(int * C[], KDTreeNode* T){
	if(T != NULL){
		if(colorMatch(C, T)){
			//delete
		} else {
			if(C[0] < T->color[0]){
				return delete2(C, T->left);
			} else {
				return delete2(C, T->right);
			}
		}
	}
	return NULL;
}

KDTreeNode* delete2(int * C[], KDTreeNode* T){
	KDTreeNode N;
	if(T != NULL){
		if(colorMatch(C, T)){
			//delete
		} else {
		if(C[1] < T->color[1]){
				return delete3(C, T->left);
			} else {
				return delete3(C, T->right);
			}
		}
	}
	return NULL;
}

KDTreeNode* delete3(int * C[], KDTreeNode* T){
	KDTreeNode N;
	if(T != NULL){
		if(colorMatch(C, T)){
			//delete
		} else {
			if(C[2] < T->color[2]){
				return delete1(C, T->left);
			} else {
				return delete1(C, T->right);
			}
		}
	}
	return NULL;
}

/* This will insert a new node in the tree. If T is a NULL it will 
construct a new node and return a pointer to it*/
KDTreeNode* insert(KDTreeNode* N, KDTreeNode* T){
	if(N != NULL ){
		if(T == NULL){
			T = N;
		} else {
			T = insert1(N,T);
		}
		return T;
	}
	return NULL;
}

KDTreeNode* insert1(KDTreeNode* N, KDTreeNode* T){
	if(T == NULL){
		T = N;
	} else {
		if(T->color[0] > N->color[0]){
			T = insert2(N, T->left);
		} else (T->color[0] <= N->color[0]){
			T = insert2(N, T->right);
		}
	}
	return T;
}

KDTreeNode* insert2(KDTreeNode* N, KDTreeNode* T){
	if(T == NULL){
		T = N;
	} else {
		if(T->color[0] > N->color[0]){
			T = insert3(N, T->left);
		} else (T->color[0] <= N->color[0]){
			T = insert3(N, T->right);
		}
	}
	return T;
}

KDTreeNode* insert3(KDTreeNode* N, KDTreeNode* T){
	if(T == NULL){
		T = N;
	} else {
		if(T->color[0] > N->color[0]){
			T = insert1(N, T->left);
		} else (T->color[0] <= N->color[0]){
			T = insert1(N, T->right);
		}
	}
	return T;
}
