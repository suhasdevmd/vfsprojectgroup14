#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./../include/allheaders.h"


struct node *hashTable[27]={NULL};



int findIndex(char fname[])
{	
	char a=toupper(fname[0]);
	int firstAlphabetASCII=a;
	int hashTableIndex;
	if(firstAlphabetASCII>=65&&firstAlphabetASCII<=90)
		hashTableIndex=firstAlphabetASCII-65;
	else 
		hashTableIndex=26;

	return hashTableIndex;

}

void insertToHash(struct file_descriptor f_desc)
{			
	int hashTableIndex=findIndex(f_desc.file_name);
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->f_desc=f_desc;
	temp->next=NULL;
	temp->previous=NULL;
	
		if(hashTable[hashTableIndex]!=NULL)
	 		temp->next=hashTable[hashTableIndex];
		
		hashTable[hashTableIndex]=temp; 


 
  		
}

void displayHash(){
	printf("HashTable :\n");	
	struct node *ptr;
	int i=0;
	while(i<27){	
		ptr=hashTable[i];
		printf("%d\t",i);
		if(ptr!=NULL){

			while(ptr->next!=NULL){
				printf("%s and path : %s\t",ptr->f_desc.file_name,ptr->f_desc.file_path);
				printf("--->");
				ptr=ptr->next;
			}

		printf("%s and path : %s\t",ptr->f_desc.file_name,ptr->f_desc.file_path);
		}
		printf("\n");
		i++;
		}
	printf("\n");	
}
