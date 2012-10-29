#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"




struct bstnode *bstroot=NULL;
struct bstnode *temp=NULL;
int rt=0;


struct bstnode* getbstnode()
{

	struct bstnode *newnode=(struct bstnode*)malloc(sizeof(struct bstnode));
	newnode->parent=NULL;
	newnode->left=NULL;
	newnode->right=NULL;
	return newnode;
}


int insert(struct file_descriptor newfdnode)
{


	char abspath[400];
	char file_pth[200];
	char file_nm[200];
	strcpy(file_pth,newfdnode.file_path);
	strcpy(file_nm,newfdnode.file_name);
	strcpy(abspath,strcat(file_pth,file_nm));


	// condition to check the equality (strcmp()==0) to be included

	if (bstroot==NULL) 
	{
		bstroot->fd_node=newfdnode;
		bstroot->left=NULL;
		bstroot->right=NULL;
		bstroot->parent=NULL;	
	}
	else if ((temp->right == NULL) && (strcmp(abspath, temp->fd_node.file_path) > 0))
	{
		temp->right = getbstnode();
		temp->right->fd_node=newfdnode;
		temp->right->parent=temp;
	}
	else if ((temp->right != NULL) && (strcmp(abspath, temp->fd_node.file_path) > 0))
	{
		temp=temp->right;
		insert(newfdnode);
	}


	if ((temp->left == NULL) && (strcmp(abspath, temp->fd_node.file_path) < 0))
	{
		temp->left = getbstnode();
		temp->left->fd_node=newfdnode;
		temp->left->parent=temp;
	}
	else if ((temp->left != NULL) && (strcmp(abspath, temp->fd_node.file_path) < 0))
	{
		temp=temp->left;
		insert(newfdnode);
	}


}




void displayinorder(struct bstnode *nd)
{
	printf("inside disp of bst\n");

	if(nd!=NULL)
	{
		displayinorder(nd->left);
		printf("\n%s %s\n",nd->fd_node.file_name,nd->fd_node.file_path);
		displayinorder(nd->right);
	}
}


void getBstRoot()
{
	bstroot=getbstnode();
	strcpy(bstroot->fd_node.file_name,"ROOT");
	strcpy(bstroot->fd_node.file_path,"/");

	temp=bstroot;
}



void insertToBst(struct file_descriptor fdnode){

	

	if(rt==0)
	{
		getBstRoot();
		insert(fdnode);
		rt++;
	}
	else
	{
		insert(fdnode);
	}
	displayinorder(bstroot);

}
