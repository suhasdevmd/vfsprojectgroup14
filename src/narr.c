
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define MAX_NAME 10
#define MAX_DIR 10

struct fileDescriptor
	{
		char fileName[100];
		char fullPath[100];
		char fileType[50];
		int fileSize;
		int locationBlockNo;
	};

struct dirNode{
	struct fileDescriptor fileDesc;
	struct dirNode *firstChild;
	struct dirNode *rightSibling;
	};

struct dirNode* getNode()
	{
		struct dirNode *p;
		p=(struct dirNode *)malloc(sizeof(struct dirNode));
		p->firstChild=NULL;
		p->rightSibling=NULL;
		return p;
	}
struct dirNode* insertNAry(struct fileDescriptor *fd,struct dirNode* root)
	{
		struct dirNode *p,*parent;
		char *ref;
		int exitStatus=FALSE;
		p=getNode();
		if(p==NULL)
			{
				printf("Sorry NO SUFFICIENT MEMORY");
				exit(0);
			}
		strcpy(p->fileDesc.fileName,fd->fileName);
		strcpy(p->fileDesc.fullPath,fd->fullPath);
		strcpy(p->fileDesc.fileType,fd->fileType);
		p->fileDesc.fileSize=fd->fileSize;
		p->fileDesc.locationBlockNo=fd->locationBlockNo;
		if(root==NULL)
			{
				root=p;
				exitStatus=TRUE;
			}
		else
			{
				parent=root;
				while(exitStatus==FALSE)
				{
					if(strstr(p->fileDesc.fullPath,(parent->fileDesc).fullPath)==NULL) // if i use this, its working 
						{
							if(parent->rightSibling==NULL)  // /c/example/root /c or /d/example/root /c
								{
									parent->rightSibling=p;
									exitStatus=TRUE;
								}
							else
								parent=parent->rightSibling;
						}
					else
						{
							if(parent->firstChild==NULL)
								{
									parent->firstChild=p;
									exitStatus=TRUE;
								}
						//	else
						//		{
						//		}
						}
						parent=parent->firstChild;
				}
			}
		return root;
	}
void displayNAry(struct dirNode *root)
	{
		if(root!=NULL)
			{
				puts(root->fileDesc.fullPath);
				displayNAry(root->rightSibling);
				displayNAry(root->firstChild);
			}
//Pre-order traversal
	}
void saveToFile(struct dirNode *root,FILE *fstore)
	{
		if(root!=NULL)
			{
				fwrite(&(root->fileDesc),sizeof(struct fileDescriptor),1,fstore);
				saveToFile(root->rightSibling,fstore);
				saveToFile(root->firstChild,fstore);
			}
	}
int main()
	{
		int i;
		char ch;
		FILE *fp,*fstore,*fp2;
		struct dirNode* root=NULL;
		struct fileDescriptor *fd;
		fstore=fopen("/Users/krishnachaitanya/desktop/nary_store.dat","wb");
		fd=(struct fileDescriptor*)malloc(sizeof(struct fileDescriptor));
		if((fp=fopen("/Users/krishnachaitanya/Desktop/inputfiledesc.txt","r"))==NULL)
				printf("Cannot open file");
		else
			{
				while(fscanf(fp,"%s",fd->fileName)!=EOF)
					{
						fscanf(fp,"%s",fd->fullPath);
						fscanf(fp,"%s",fd->fileType);
						fscanf(fp,"%d",&fd->fileSize);
						fscanf(fp,"%d",&fd->locationBlockNo);
						root=insertNAry(fd,root);
					}
			}
		fclose(fp);
//displayNAry(root);
		saveToFile(root,fstore);
		fclose(fstore);
		root=NULL;
		if((fp2=fopen("nary_store.dat","rb"))==NULL)
			printf("Cannot open file");
		else
			{
				while(fread(fd,sizeof(struct fileDescriptor),1,fp2))
					{
						root=insertNAry(fd,root);
					}
			}
		displayNAry(root);
		fclose(fp);
		return 0;
	}
