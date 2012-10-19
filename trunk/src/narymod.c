#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0

/*First we are creating a root node that has to be created during vfs-mount.here i have created a root node in a separate program that is root.c .Run it first where a file nary.dat(in our project it should be the vfs.dat) is getting created with the root node.In this program we are reading the .dat file geting the root node and adding a folder in the root node and then writing it back to the .dat file and this happens everytime we are providing a path under which we are storing the folder.I havenot given any validation checks,but following checks we'll have to give here.a) under a folder files or folders with same names cant exist.b)distinction between files and folders.here we r considering dat we r storing folders.*/


/*This program will run only if u enter a valid path or path should contain the folders u hav written in the .dat file,else it will show a segmentation fault*/

struct fileDescriptor
{
	char fileName[100];
	char fullPath[100];//increase size
	char fileType[50];
	int fileSize;
	int locationBlockNo;
};

struct dirNode{
struct fileDescriptor fileDesc;
struct dirNode *firstChild;
struct dirNode *rightSibling;
};


struct dirNode *root=NULL;
struct dirNode * getnode()//function to create a node of narytree
{
   struct dirNode* temp;
   temp=(struct dirNode*)malloc(sizeof(struct dirNode));
   temp->firstChild=NULL;
   temp->rightSibling=NULL;
   return temp;
}



void insert_root(struct fileDescriptor *fd)//function to insert the root node only
{
  root=getnode();
  strcpy(root->fileDesc.fileName,fd->fileName);
   strcpy(root->fileDesc.fullPath,fd->fullPath);
   strcpy(root->fileDesc.fileType,fd->fileType);
   root->fileDesc.fileSize=fd->fileSize;
   root->fileDesc.locationBlockNo=fd->locationBlockNo;
  
}

void displayNAry(struct dirNode *d)//function to display the filedescriptor names stored in the nodes of narytree in preorder manner
{
if(d!=NULL)
{
puts(d->fileDesc.fileName);
displayNAry(d->rightSibling);
displayNAry(d->firstChild);
}
}          


void insert_node(struct fileDescriptor *fd)//function to insert the nodes other than root node
{
  struct dirNode *temp=NULL,*start=NULL;
  int status=0,count=0,i=1;
   char path[100];
   char *tokens[100];
   temp=getnode();
   strcpy(temp->fileDesc.fileName,fd->fileName);//copy the filedescriptor contents in the nary node
   strcpy(temp->fileDesc.fullPath,fd->fullPath);
   strcpy(temp->fileDesc.fileType,fd->fileType);
   temp->fileDesc.fileSize=fd->fileSize;
   temp->fileDesc.locationBlockNo=fd->locationBlockNo;
   strcpy(path,fd->fullPath);//copy the filedescriptor path in the path char array
	printf("path: %s\n",path);
   // char * result=NULL;
	//char str2[]="/";
   tokens[count]=strtok(path,"/");//breaking the path into tokens
    start=root;
    while(tokens[count]!=NULL)
     { 
           count++;
           tokens[count]=strtok(NULL,"/");//storing the tokens in the array of char pointers pointing to each token
		
      }
    
    if(tokens[i]==NULL)//when path contains only ROOT
    {
      
    	   
       		if(start->firstChild==NULL)//checking and storing in the first child of the root if its null
               {
                 start->firstChild=temp;
                 status=1;
               }
             else//if the first child of the root is not null,traverse through right siblings and store if a right sibling is null
            {
             start=start->firstChild;
             while(status!=1){
             if(start->rightSibling==NULL){
              start->rightSibling=temp;
               status=1;
               }
              else
                start=start->rightSibling;
              }
             
          }
               
    }

    else //when path contains ROOT/... ie it doesnot contain only the ROOT
      { 
        start=start->firstChild;
         while(i<count)//checking from token[i=1] as token[i=0] contains root and its checking done in IF statement b4.
          {
             if(strcmp(tokens[i],start->fileDesc.fileName))//compare d present token with d firstchild,traverse thru rightsibling til a match
                  start=start->rightSibling;
              else
                  { 
                   if(start->firstChild!=NULL)//after the match is found go to the first child 
                   start=start->firstChild;
                   i++;//to go to the next token
                  }
          }
        if(start->firstChild==NULL)
           start->firstChild=temp;
        else
        { 
        while(start->rightSibling!=NULL)
         start=start->rightSibling;
         start->rightSibling=temp;//when all the tokens are matched we insert our new folder
        }
 }   
   
}            
   

void saveToFile(struct dirNode *d,FILE *fp)//function to store the nodes in preorder manner
{
if(d!=NULL)
{
 
fwrite(&(d->fileDesc),sizeof(struct fileDescriptor),1,fp);
saveToFile(d->rightSibling,fp);
saveToFile(d->firstChild,fp);
}
}       





int main(int argc,char*argv[])//provide the file path and the folder name which u want to create under that path
{
struct dirNode *d=NULL;  
struct fileDescriptor *fd=NULL ,*fd1=NULL;
FILE *fp,*fp1;
  int k=0;//flag to insert only the root node everytime in our tree
  fp=fopen("nary.dat","rb+");//open the file in append mode
  fd=(struct fileDescriptor*)malloc(sizeof(struct fileDescriptor));//create a storage for filedescriptor
  if(fp==NULL)
  printf("File Doesnot exist..");
  else
   {
    rewind(fp);//to reading from the beginning since u r opening in the apend mode where file pointer should be in d position u want to apend






     while(fread(fd,sizeof(struct fileDescriptor),1,fp))//read the first content in a filedescriptor
       {
          if(k==0)
          {  
          insert_root(fd);//create the root node.separately done bcoz it doesnt contain any right siblings.
           k++;
          }
       else
      {
       insert_node(fd);//insert the other nodes(if any) from the .dat file
     }
      }
    k=0;
     d=root;
     strcpy(fd->fileName,argv[2]);//copying the folder name in the filedescriptor
     strcpy(fd->fullPath,argv[1]);//copying the path in the filedescriptor
     strcpy(fd->fileType,"");//filetype is not given,we'll include it later
     fd->fileSize=0;//filesize for folders should be 0
     fd->locationBlockNo=-1;//folders dont have location blocks so a -ve number
     insert_node(fd);//we insert the new node in the nary tree we created by reading from the .dat file
     displayNAry(root);//display the entire tree in preorder traversal with the new node
     rewind(fp);//do this to bring the file pointer back to the beginning
     



saveToFile(d,fp);//then we save the entire nary tree into the .dat file(so prev data in getting overwritten)
    fclose(fp);
  }

free(fd);

return 0;
}
 
          


          
  
