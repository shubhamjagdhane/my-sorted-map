#include<stdio.h>
#include<stdlib.h>

typedef enum {red,black} Color;

typedef struct TestTree {
	int data;
	struct TestTree *left,*right,*parent;
	Color color;
}T;

static int a=0;

T *insert(T *root,int data);
void inorder(T *root);
void deleteTree(T **root);
T *newNode(int data);
int isPropertySatisfied(T *root);
Color givesParentSiblingColor(T *root,int data);
/*T *identifyWhichRotationAndRotate(T *root,int data);
T *rightRotate(T *X);
T *leftRotate(T *Y);*/
Color whichColor(T *node);
int printData(T *node);

// This is new implementation

void identifyWhichRotationAndRotate(T **root,int data);
void rightRotate(T ***X);
void leftRotate(T ***Y);

int main(void) {
	int data,ch;
	T *root=NULL;
	while(1) {
		printf("\n__________________________________________________");
		printf("\n1: Insert\n2: Inorder\n3: DeleteTree\n4: Exit");
		printf("\n__________________________________________________");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		
		if(ch==4)
			break;

		switch(ch) {
			case 1:
				printf("\nEnter data for a node: ");
				scanf("%d",&data);
				root = insert(root,data);
				break;
			case 2:
				if(root)
					inorder(root);
				else
					printf("\nTree is already NULL");
				break;
			case 3:
				a=0;
				deleteTree(&root);
				break;
		}
	}
	deleteTree(&root);
}

void deleteTree(T **root) {
	if(*root) {
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));

		free(*root);
	}
	*root=NULL;
}

T *newNode(int data) {
	T *node = (T *)malloc(sizeof(T));

	if(!node) {
		printf("\nMemory is not allocated...!");
		exit(1);
	}

	node->data = data;
	node->right=node->left=NULL;
	node->parent= NULL;
	if(a==0)
		node->color = black;
	else
		node->color = red;
	a+=1;
	return node;
}

void inorder(T *root) {
	if(root!=NULL) {
		inorder(root->left);
		printf("\n%d %d %d",printData(root),printData(root->left),printData(root->right));
		printf("\nRoot->right->left->data = %d",root->right->left->data);
		/*if(root->parent)
			printf("\n%d has %d parent with its color %d",root->data,root->parent->data,root->color);
		else
			printf("\n%d has NULL parent with its color %d",root->data,root->color);
		*/
		inorder(root->right);
	}
}

T *insert(T *root,int data) {
	if(root==NULL) {
		return (newNode(data));
	}
	else if(data > root->data) {
		root->right = insert(root->right,data);
		root->right->parent = root;
	}
	else if(data < root->data) {
		root->left = insert(root->left,data);
		root->left->parent = root;
	}

	if(!isPropertySatisfied(root)) {
		printf("\n\t\t***Property is not satisfied..!!***");
		if(givesParentSiblingColor(root,data) == black) {
			printf("\n\t\t*** BLACK ***");
			printf("\nPerform suitable rotation and recolor");
			
			//root = (identifyWhichRotationAndRotate((root->parent),data));
			(identifyWhichRotationAndRotate(&(root->parent),data));
			
			printf("\n\n\t\t*** Root Informations ***");
			printf("\nRoot->data = %d and parent = %d",printData(root),printData(root->parent));
			printf("\nRoot->left->data = %d and parent = %d",printData(root->left),printData(root->left->parent));
			printf("\nRoot->right->data = %d and parent = %d",printData(root->right),printData(root->right->parent));

		}
		else {
			printf("\n\t\t*** RED ***");
			printf("\nCheck parent's parent is not a root node, then recolor and recheck");
		}
	}
	
	return root;
}

int printData(T *node) {
	if(!node)
		return -1;
	return node->data;

}

Color givesParentSiblingColor(T *root,int data) {
	if(root) {
		if(root->left && root->left->data==data) {
			if(root->parent->left==root)
				return whichColor(root->parent->right);
			else
				return whichColor(root->parent->left);
		}
		else if(root->right && root->right->data==data) {
			if(root->parent->right==root)
				return whichColor(root->parent->left);
			else
				return whichColor(root->parent->right);
		}
	}
	return black;
}

Color whichColor(T *node) {
	if(!node)
		return black;
	return node->color;
}

int isPropertySatisfied(T *root) {
	if(root==NULL || root->parent==NULL)
		return 1;
	if(root && root->parent) {
		if(root->color==red && root->parent->color==red)
			return 0;
		else
			return (1 && isPropertySatisfied(root->left) && isPropertySatisfied(root->right));
	}
}
/*
T *identifyWhichRotationAndRotate(T *root,int data) {
	printf("\n\t\t***Working Processing...***");
	
	if(root) {
		if(root->left && data < root->left->data)
			return rightRotate(root);
		
		if(root->right && data > root->right->data)
			return leftRotate(root);

		if(root->left && data > root->left->data) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if(root->right && data < root->right->data) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	//return root;
}

T *leftRotate(T *W) {
	printf("\n\t\t*** Inside Left Rotation***");
	printf("\n\t\t*** Performing Rotation of %d node***",printData(W));
	
	T *X = W->right;
	T *Z;
	if(X->left)
		Z = X->left;
	else
		Z = NULL;
	X->left = W;
	W->right = Z;

	W->parent=X;
	Z->parent=W;
	X->parent=NULL;
	
	return X;
}

T *rightRotate(T *X) {
	printf("\n\t\t*** Inside Right Rotation***");
	printf("\n\t\t*** Performing Rotation of %d node***",X->data);
	T *W = X->left;
	T *Z;

	if(W->right)
		Z = W->right;
	else
		Z = NULL;

	W->right = X;
	X->left = Z;

	X->parent=W;
	Z->parent=X;
	W->parent=NULL;

	return W;
}
*/
// This is new trying...

void identifyWhichRotationAndRotate(T **root,int data) {
	printf("\n\t\t***Working Processing...***");
	
	if(*root) {
		if((*root)->left && data < (*root)->left->data)
			rightRotate(&(root));
		
		if((*root)->right && data > (*root)->right->data)
			leftRotate(&(root));

		if((*root)->left && data > (*root)->left->data) {
			leftRotate(&root->left);
			rightRotate(&(root));
		}

		if((*root)->right && data < (*root)->right->data) {
			rightRotate(&root->right);
			leftRotate(&(root));
		}
	}
	//return root;
}

void leftRotate(T ***W) {
	printf("\n\t\t*** Inside Left Rotation***");
	printf("\n\t\t*** Performing Rotation of %d node***",(*(*W))->data);
	
/*	T *X = W->right;
	T *Z;
	if(X->left)
		Z = X->left;
	else
		Z = NULL;
	X->left = W;
	W->right = Z;

	W->parent=X;
	Z->parent=W;
	X->parent=NULL;
	
	return X;*/
}

void rightRotate(T ***X) {
	printf("\n\t\t*** Inside Right Rotation***");
	printf("\n\t\t*** Performing Rotation of %d node***",printData((**X)));
	
	/*
	T *W = X->left;
	T *Z;

	if(W->right)
		Z = W->right;
	else
		Z = NULL;

	W->right = X;
	X->left = Z;

	X->parent=W;
	Z->parent=X;
	W->parent=NULL;

	return W;
	*/
}
