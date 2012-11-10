#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"




struct bstnode *bstroot=NULL;
struct bstnode *temp=NULL;
int bst=0;


struct bstnode* successor(struct bstnode *bstnode1);
struct bstnode* minimum(struct bstnode *bstnode1);
struct bstnode* search(char file_path[]);



struct bstnode* getbstnode()
{

	struct bstnode *newnode=(struct bstnode*)malloc(sizeof(struct bstnode));
	newnode->parent=NULL;
	newnode->left=NULL;
	newnode->right=NULL;
	return newnode;
}

void clearBst()
{
	bst=0;
} 


void unmountBSTRoot()
{
	bstroot=NULL;
}



int insert(struct file_descriptor newfdnode)
{

	if (bstroot==NULL) 
	{
		bstroot->fd_node=newfdnode;
		bstroot->left=NULL;
		bstroot->right=NULL;
		bstroot->parent=NULL;	
	}
	else if(strcmp(newfdnode.file_path, temp->fd_node.file_path)==0)
	{
	printf("File already exists");
	bst=1;
	}
	else if ((temp->right == NULL) && (strcmp(newfdnode.file_path, temp->fd_node.file_path) > 0))
	{
		temp->right = getbstnode();
		temp->right->fd_node=newfdnode;
		temp->right->parent=temp;
		

	}
	else if ((temp->right != NULL) && (strcmp(newfdnode.file_path, temp->fd_node.file_path) > 0))
	{
		temp=temp->right;
		insert(newfdnode);
	}
	
	else if ((temp->left == NULL) && (strcmp(newfdnode.file_path, temp->fd_node.file_path) < 0))
	{
		temp->left = getbstnode();
			temp->left->fd_node=newfdnode;
		temp->left->parent=temp;
		
	}
	else if ((temp->left != NULL) && (strcmp(newfdnode.file_path, temp->fd_node.file_path) < 0))
	{
		temp=temp->left;
		insert(newfdnode);
	}	
return bst;

}




void displayinorder(struct bstnode *nd)
{

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
	strcpy(bstroot->fd_node.file_path,"");

	temp=bstroot;
}



int insertToBst(struct file_descriptor fdnode){

	

	char abspath[400];
	char file_pth[200];
	char file_nm[200];

	temp=bstroot;
	strcpy(file_pth,fdnode.file_path);
	strcpy(file_nm,fdnode.file_name);
	strcat(file_pth,"/");
	strcpy(abspath,strcat(file_pth,file_nm));
	strcpy(fdnode.file_path,abspath);

	bst=insert(fdnode);


	printf("displaying BST");
//	displayinorder(bstroot);
	return bst;
}







int searchIfPathExists(char file_path[])
{
    printf("BST SEARCH for existance of path");
    if(bstroot==NULL)
    {
        printf("\nbst doesnt exist\n");
        return 0;
    }
    struct bstnode *temp1=bstroot;
    char abspath[200];
    strcpy(abspath,file_path);
    if(abspath=="")
    {
        printf("\npath=empty\n");
        return 0;
    }
    else
    {

        do
        {
            if(strcmp(temp1->fd_node.file_path,abspath)<0)
            {
                temp1=temp1->right;
                continue;
            }   


            if(strcmp(temp1->fd_node.file_path,abspath)>0)
            {
                temp1=temp1->left;
                continue;
            }


        if(strcmp(temp1->fd_node.file_path,abspath)==0)
        {
            return 1;
        }

        }while(temp1!=NULL);

    }
    return 0;

}





struct file_descriptor* searchAndGetFD(char file_path[])//return type : struct file_descriptor *
{

	if(bstroot==NULL) return NULL;
	
	struct bstnode *temp1=bstroot;
	char abspath[200];
	strcpy(abspath,file_path);
	if(abspath=="")return NULL;
	else
	{

		do
		{
			if(strcmp(temp1->fd_node.file_path,abspath)<0)
			{
				temp1=temp1->right;continue;
			}


			if(strcmp(temp1->fd_node.file_path,abspath)>0)
			{
				temp1=temp1->left;continue;
			}


			if(strcmp(temp1->fd_node.file_path,abspath)==0)
			{
				return &temp1->fd_node;
			}

		}while(temp1!=NULL);

	}
	
	return NULL;
}


struct bstnode* minimum(struct bstnode *bstnode1)
{

	struct bstnode *temp1;
	temp1=bstnode1;


	if(bstnode1==NULL)
	return NULL;
	else
	{
		while(temp1->left!=NULL)
   		{
			temp1=temp1->left;
		}
	return temp1;
	}
}





struct bstnode* successor(struct bstnode *bstnode1)
{

	struct bstnode *pp=bstnode1->parent;

	if(bstnode1->right!=NULL)
	{
		return(minimum(bstnode1->right));
	}
	else
	{


		while(pp!=NULL && bstnode1==pp->right)
		{
			bstnode1=pp;
			pp=pp->parent;
		}
	return pp;

	}
}






struct bstnode* search(char file_path[])
{

	if(bstroot==NULL) return NULL;

	struct bstnode *temp1=bstroot;
	char abspath[200];
	strcpy(abspath,file_path);
	if(abspath=="")return NULL;
	else
	{
	
		do
		{
			if(strcmp(temp1->fd_node.file_path,abspath)<0) 
			{
				temp1=temp1->right;
				continue;
			}


			if(strcmp(temp1->fd_node.file_path,abspath)>0) 
			{
				temp1=temp1->left;
				continue;
			}


			if(strcmp(temp1->fd_node.file_path,abspath)==0) 
			{
				return temp1;
			}

		}while(temp1!=NULL);

	}
	return NULL;
}







int deleteB(char tmfp[]){


	//bstroot is null

	if(bstroot==NULL) {puts("bstroot is null");return 0;}

	else
	{

	struct bstnode *ispresent;
	//char  tmfp[50];
	//strcat(file_path,"/");
	//strcpy(tmfp,strcat(file_path,file_name));
	ispresent=search(tmfp);

	if(ispresent==NULL) {puts("ispresent is null");return 0;}//bstnode is not in bst


	//if control reaches here it means bstnode to be deleted is present in bst.
	printf("\nispresent->fd_node.file_name = %s\n",ispresent->fd_node.file_name);
	
	if(ispresent->right==NULL && ispresent->left==NULL)
	{ 
		puts("ispresents right and left are null");

		if(ispresent->parent->right==ispresent)
			{puts("ispresents right and left are null ispresent is right child of its parent");
			ispresent->parent->right=NULL;}
		else 
			
			{puts("ispresents right and left are null  AND ispresent is left child of its parent");ispresent->parent->left=NULL;}

		ispresent=NULL;

		free(ispresent);

		return 0;
	}//no children



	struct bstnode *replacingnode;

	replacingnode=successor(ispresent);

	if(replacingnode==NULL){
		printf("\nreplacinnode=NULL\n"); //incase successor of ispresent is null
		if(ispresent->right==NULL){
			puts("ispresent->rightCD =NULL");
			printf("\nispresent->parent->fd_node.file_name = %s\n",ispresent->parent->fd_node.file_name);
			ispresent->left->parent=ispresent->parent;ispresent->parent->left=ispresent->left;
			printf("\nispresent->left->parent->fd_node.file_name = %s\n",ispresent->left->parent->fd_node.file_name);
			ispresent=NULL;
			}
		else if(ispresent->left==NULL){
			puts("ispresent->left==NULL");
			printf("\nispresent->parent->fd_node.file_name = %s\n",ispresent->parent->fd_node.file_name);			
			ispresent->right->parent=ispresent->parent;ispresent->parent->right=ispresent->right;
			printf("\nispresent->right->parent->fd_node.file_name = %s\n",ispresent->right->parent->fd_node.file_name);			
			ispresent=NULL;
			}
//		ispresent=NULL;
		free(ispresent);
		if(ispresent==NULL)puts("ispresent=null");
	return 0;}

	//if right subtree is present then what to do
	//puts(replacingnode->fd_node.file_name);

	if(ispresent->right!=NULL)
	{
		puts("ispresent->right is not null");

		if(ispresent->parent->right==ispresent){

			puts("ispresent->right is not null and ispresent is right child of its	parent");	
			ispresent->parent->right=replacingnode;
			printf("\nreplacingnode->fd_node.file_name = %s\n",replacingnode->fd_node.file_name);
			
			if(replacingnode==replacingnode->parent->right)replacingnode->parent->right=NULL;

			else replacingnode->parent->left=NULL;				
			
			replacingnode->parent=ispresent->parent;

			printf("\nreplacingnode->parent->fd_node.file_name = %s\n",replacingnode->parent->fd_node.file_name);

			//replacingnode->right=ispresent->right;

			printf("\nreplacingnode->right->fd_node.file_name = %s\n",replacingnode->right->fd_node.file_name);
			
			

			//replacingnode->left=ispresent->left;

			printf("\nreplacingnode->left->fd_node.file_name = %s\n",replacingnode->left->fd_node.file_name);	

			ispresent=NULL;
			free(ispresent);
		}

		else if(ispresent->parent->left==ispresent){
	


			puts("ispresent->right is not null and ispresent is left child of its parent");	

			ispresent->parent->left=replacingnode;

			printf("\nreplacingnode->fd_node.file_name = %s\n",replacingnode->fd_node.file_name);
				
			if(replacingnode==replacingnode->parent->right)replacingnode->parent->right=NULL;

			else replacingnode->parent->left=NULL;



			replacingnode->parent=ispresent->parent;

			printf("\nreplacingnode->parent->fd_node.file_name = %s\n",replacingnode->parent->fd_node.file_name);	

			//replacingnode->right=ispresent->right;

			printf("\nreplacingnode->right->fd_node.file_name = %s\n",replacingnode->right->fd_node.file_name);	

			//replacingnode->left=ispresent->left;

			printf("\nreplacingnode->left->fd_node.file_name = %s\n",replacingnode->left->fd_node.file_name);	

			ispresent=NULL;

			free(ispresent);

			}

		}

	   else	if(ispresent->right==NULL)		//if right subtree is absent then what to do
		{
			puts("ispresent->right is null");
			//struct bstnode *temp_parent;
			replacingnode->parent->left=replacingnode->left;
			replacingnode->left->parent=replacingnode->parent;
			ispresent->parent->right=replacingnode;
			replacingnode->right=ispresent->right;
			replacingnode->parent=ispresent->parent;
			ispresent=NULL;	
			free(ispresent);
		}



		

	}
	
}





void deleteBST(struct file_descriptor fd)
{


	strcat(fd.file_path,"/");
	strcpy(fd.file_path,strcat(fd.file_path,fd.file_name));
	int i=deleteB(fd.file_path);

	if(i==0)
	{
		printf("\n Deletion in BST unsuccessful . \n");
	}

}


void displayBSTMain(){

	printf("\n************************  BST  ***************************\n");
	displayinorder(bstroot);
}




















