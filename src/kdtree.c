#include "kdtree.h"

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
			if(C[0] < T->color[0]){
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
			if(C[0] < T->color[0]){
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
		if(colorMatch(C, T)){
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
			if(C[0] < T->color[0]){
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
			if(C[0] < T->color[0]){
				return findNearest(C, T->left, T);
			} else {
				return findNearest(C, T->right, T);
			}
		}
	}
	return N;
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
	if(T == NULL){
		T = N;
	} else {
		if(T->color[0] > N->color[0]){
			T = insert2(N, T->left);
		} else {
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
		} else {
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
			T = insert(N, T->left);
		} else {
			T = insert(N, T->right);
		}
	}
	return T;
}
