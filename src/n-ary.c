#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"


struct dirNode *root=NULL;

struct dirNode * getnode()//function to create a node of narytree
{	printf("getting node\n");
   struct dirNode* temp;
   temp=(struct dirNode*)malloc(sizeof(struct dirNode));
   temp->firstChild==NULL;
   temp->rightSibling==NULL;
	printf("got narry node\n");
   return temp;
	
}



void naryRoot()
{	printf("inside nary root\n");
	//struct dirNode *root;
	root=getnode();
	strcpy(root->fileDesc.file_name,"ROOT");
	strcpy(root->fileDesc.file_path,"");
	strcpy(root->fileDesc.file_type,"");
	root->fileDesc.file_size=0;
	root->fileDesc.location_block_number=-1;
	printf("passed narry root step.\n");
}

void displayNAry(struct dirNode *d)//function to display the filedescriptor names stored in the nodes of narytree in preorder manner
{

if(d!=NULL)
{
printf("%s\n",d->fileDesc.file_name);
printf("inside display\n");
displayNAry(d->rightSibling);
displayNAry(d->firstChild);
}
}          


void insertToNarry(struct file_descriptor fd)//function to insert the nodes other than root node
{
	printf("insetion process started\n");
	
 	struct dirNode *temp=NULL,*start=NULL;
  	int j,status=0,count=0,i=1,match=0,match1=0;
  	char s[100]="";	
   	char path[100];
   	char *tokens[100];
   	temp=getnode();
	temp->fileDesc=fd;
	insertToHash(fd);
   	strcpy(path,fd.file_path);//copy the filedescriptor path in the path char array
   	tokens[count]=strtok(path,"/");//breaking the path into tokens
    	start=root;

	printf("passed allocation Step\n");

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
                 
                
               }
             else//if the first child of the root is not null,traverse through right siblings and store if a right sibling is null
            {
             start=start->firstChild;
             while(status==0){
             if(start->rightSibling==NULL){
              
              start->rightSibling=temp;
               status=1;
               }
              else{
                start=start->rightSibling;
                }
               
              }
             
          }
               
    }

    else //when path contains ROOT/... ie it doesnot contain only the ROOT
      { 
	if(start->firstChild!=NULL){
        start=start->firstChild;
         while(i<count)//checking from token[i=1] as token[i=0] contains root and its checking done in IF statement b4.
          {
             while((strcmp(tokens[i],start->fileDesc.file_name)!=0)){//compare d present token with d firstchild,traverse thru right
                  if(start->rightSibling==NULL){
                     match=1;match1=1;
                     break;
                     }
                    start=start->rightSibling;
                   
              }
                 if(match==1)
                  break;
                   //to go to the next token
                   if(start->firstChild!=NULL)//after the match is found go to the first child 
                  { start=start->firstChild;}
                   else if(start->firstChild==NULL && (i==count-1)){
                    start->firstChild=temp;
                    status=1;
                    break;
                    }
                   else if(start->firstChild==NULL && (i<count-1)){
                   match1=1;
                   i++;
                  break;
                  }
                   
               
                  i++;
          }
       
  	}else
	{
	match1=1;
	}

       if(match1==1){
		if(match==1){
		start->rightSibling=getnode();
		start=start->rightSibling;
		}
		else{
		start->firstChild=getnode();
		start=start->firstChild;
		}
		strcpy(start->fileDesc.file_type,"");
        	start->fileDesc.file_size=0;
        	start->fileDesc.location_block_number=-1;
         	strcpy(start->fileDesc.file_name,tokens[i]);
		for(j=0;j<i-1;j++){
			strcat(s,tokens[j]);
			strcat(s,"/");
		}
		strcat(s,tokens[i-1]);
         	strcpy(start->fileDesc.file_path,s);
		insertToHash(start->fileDesc);//
          	i++;
        	while(i<count){
           		start->firstChild=getnode();
           		start=start->firstChild;
			strcpy(start->fileDesc.file_type,"");
        		start->fileDesc.file_size=0;
        		start->fileDesc.location_block_number=-1;
         		strcpy(start->fileDesc.file_name,tokens[i]);
			strcpy(s,"");	
			for(j=0;j<i-1;j++){
				strcat(s,tokens[j]);
				strcat(s,"/");
			}
			strcat(s,tokens[i-1]);
         		strcpy(start->fileDesc.file_path,s);
			insertToHash(start->fileDesc);//
          		i++;
        	} 
	}
       
        if(status==0){
         while(start->rightSibling!=NULL)
         start=start->rightSibling;
         start->rightSibling=temp;//when all the tokens are matched we insert our new folder
     }
       }
    printf("insertion complete \n");
displayNAry(root); 
displayHash();  
}            
   



