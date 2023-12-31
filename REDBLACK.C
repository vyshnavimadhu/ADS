#include<stdio.h>
#include<stdlib.h>
#define RED 'R'
#define BLACK 'B'
struct node
{
	int data;
	char color;
	struct node*left,*right,*parent;
};
struct node *root=NULL;
void leftrotate(struct node *x);
void rightrotate(struct node *y);
void color(struct node *z);
void insert(int val);
void insertfixup(struct node *z);
void printtree(struct node *root,int level,int space);
void leftrotate(struct node *x)
{
	struct node *y=x->right;
	x->right=y->left;
	if(y->left!=NULL)
	y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
	root=y;
	else if(x==x->parent->left)
	x->parent->left=y;
	else
	x->parent->right=y;
	y->left=x;
	x->parent=y;
}
void rightrotate(struct node *y)
{
	struct node *x=y->left;
	y->left=x->right;
	if(x->right!=NULL)
	x->right->parent=y;
	x->parent=y->parent;
	if(y->parent==NULL)
	root=x;
	else if(y==y->parent->left)
	y->parent->left=x;
	else
	y->parent->right=x;
	x->right=y;
	y->parent=x;
}
void color(struct node *z)
{
	while(z->parent!=NULL&&z->parent->color==RED)
	{
	   if(z->parent==z->parent->parent->left)
	   {
	       struct node *y=z->parent->parent->right;
	       if(y!=NULL&&y->color==RED)
	       {
		   z->parent->color=BLACK;
		   y->color=BLACK;
		   z->parent->parent->color=RED;
		   z=z->parent->parent;
	       }
	       else
	       {
		   if(z==z->parent->right)
		   {
		      z=z->parent;
		      leftrotate(z);
		   }
		   z->parent->color=BLACK;
		   z->parent->parent->color=RED;
		   rightrotate(z->parent->parent);
	       }
	   }
	   else
	   {
		struct node *y=z->parent->parent->left;
		if(y!=NULL&&y->color==RED)
		{
		    z->parent->color=BLACK;
		    y->color=BLACK;
		    z->parent->parent->color=RED;
		    z=z->parent->parent;
		}
		else
		{
		   if(z==z->parent->left)
		   {
		      z=z->parent;
		      rightrotate(z);
		   }
		   z->parent->color=BLACK;
		   z->parent->parent->color=RED;
		   leftrotate(z->parent->parent);
		}
	   }
	}
	root->color=BLACK;
}
void insert(int val)
{
  struct node *z=(struct node*)malloc(sizeof(struct node));
  struct node *y=NULL;
  struct node *x=root;
  z->data=val;
  z->left=z->right=z->parent=NULL;
  z->color=RED;
  while(x!=NULL)
  {
      y=x;
      if(z->data<x->data)
      x=x->left;
      else
      x=x->right;
  }
  z->parent=y;
  if(y==NULL)
  root=z;
  else if(z->data<y->data)
  y->left=z;
  else
  y->right=z;
  color(z);
}
void printspaces(int count)
{
	int i;
	for(i=0;i<count;i++)
	printf(" ");
}
void printtree(struct node *root,int level,int space)
{
	int i;
	if(root==NULL)
	return;
	space+=5;
	printtree(root->right,level+1,space);
	printf("\n");
	for(i=5;i<space;i++)
	printf(" ");
	printf("%d%c\n",root->data,root->color);
	printtree(root->left,level+1,space);
}
void main()
{
	int ch,val;
	clrscr();
	while(1)
	{
	    printf("\n1.Insert\n2.Display\n3.Exit\n Enter your choice:");
	    scanf("%d",&ch);
	    switch(ch)
	    {
	       case 1:
	       printf("Enter the element");
	       scanf("%d",&val);
	       insert(val);
	       break;
	       case 2:
	       printf("RED-BLACK Tree structure:\n");
	       printf("--------------------------\n");
	       printtree(root,1,0);
	       printf("---------------------------\n");
	       break;
	       case 3:
	       exit(0);
	    }
	}
}