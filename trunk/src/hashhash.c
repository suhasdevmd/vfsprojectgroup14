#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct file_descriptor{
	char file_name[100];
	char file_path[100];
	char file_type[10];
	long int file_size;
}f_desc[20];
struct node{
	struct file_descriptor f_desc;
	char fname[10];
	struct node* next;
	struct node * previous;
};

int findIndex(char fname[]);
struct node **  insertFile(char fname[],struct file_descriptor f_desc,struct node *hashTable[],int hashTableIndex);
void displayFile(struct node *hashTable[]);

int main()
{	struct node *hashTable[52];
	struct node **hashTablePointer=&hashTable;
	int q;
	for(q=0;q<52;q++)
	hashTable[q]=NULL;
	int j,k;
	char fname[10];
	int choice,hashTableIndex;
	int z=1;
	int i,n;
	while(z){
		printf("enter 1 for insertion and 2 to display the file\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 
				printf("enter the no of files to enter");
				scanf("%d",&n);
				for(i=0;i<n;i++)
				{ 	printf("enter the name of the %d file",i);
                	          	scanf("%s",fname);
				  	strcpy(f_desc[i].file_name,fname);
					strcpy(f_desc[i].file_path,"/home/hello");
					strcpy(f_desc[i].file_type,"regular");
					f_desc[i].file_size=1024;
				}
				for(i=0;i<n;i++)
				{	
					strcpy(fname,f_desc[i].file_name);			
					hashTableIndex=findIndex(fname);
					hashTablePointer=insertFile(fname,f_desc[i],hashTable,hashTableIndex);
				}
				break;

			case 2: 
				displayFile(hashTable);
				z=0;
				break;

			default : 
				printf("wrong choice\n");
		}
	}
	return 0;
}

int findIndex(char fname[])
{
	int firstAlphabetASCII=fname[0];
	int hashTableIndex;
	//printf("firstAlphabetASCII=%d\n",firstAlphabetASCII);
	if(firstAlphabetASCII>=65&&firstAlphabetASCII<=90)
		hashTableIndex=firstAlphabetASCII-65;
	else 
		hashTableIndex=firstAlphabetASCII-71;
	//printf("hashTableIndex=%d\n",hashTableIndex);
	return hashTableIndex;

}

struct node **  insertFile(char fname[],struct file_descriptor f_desc,struct node *hashTable[],int hashTableIndex)
{
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	int z;
	for(z=0;z<10;z++)
	temp->fname[z]=fname[z];
	temp->f_desc=f_desc;
	temp->next=NULL;
	temp->previous=NULL;
	
		if(hashTable[hashTableIndex]==NULL)
		hashTable[hashTableIndex]=temp;
	else{
	 	struct node *ptr,*ptrp;
   		ptr=hashTable[hashTableIndex];
  		 ptrp=hashTable[hashTableIndex];
 		  while(ptr->next != NULL){
    			ptrp=ptr;
      			ptr=ptr->next;
      			ptr->previous=ptrp;   
  		}
   	ptrp=ptr;
   	ptr->next=temp;
   	temp->previous=ptrp;
  	}
printf("inserted\n");
return &hashTable;
}

void displayFile(struct node *hashTable[]){
	printf("HashTable :\n");	
	struct node *ptr;
	int i=0;
	while(i<52){	
		ptr=hashTable[i];
		printf("%d\t",i);
		if(ptr!=NULL){

			while(ptr->next!=NULL){
				printf("%s and path : %s",ptr->fname,ptr->f_desc.file_path);
				printf("--->");
				ptr=ptr->next;
			}
//	while(ptr->previous!=NULL)
//	{
//		printf("%s\n",ptr->fname);
//		printf("--->\n");
//		ptr=ptr->previous;
//	}
		printf("%s and path : %s",ptr->fname,ptr->f_desc.file_path);
		}
		printf("\n");
		i++;
		}
	printf("\n");	
}
