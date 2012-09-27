#include<stdio.h>

struct node{
struct file_descriptor f_desc;
char fname[10];
struct node* next;
struct node * previous;
};
struct file_descriptor{
char file_name[100];
char file_path[100];
char file_type[10];
long int file_size;
}f_desc[20];

int findIndex(char fname[]);
struct node **  insertFile(char fname[],struct file_descriptor f_desc,struct node *hashTable[],int hashTableIndex)
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
int i=0;


while(z){
	printf("enter 1 to create a new file and 2 to display the file\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: printf("enter the name of the file\n");
			scanf("%s",fname);
			strcpy(f_desc[i].file_name,fname);
			strcpy(f_desc[i].file_path,"/home/hello");
			strcpy(f_desc[i].file_type,"regular");
			f_desc[i].file_size=1024;					
			hashTableIndex=findIndex(fname);
			hashTablePointer=insertFile(fname,f_desc[i],hashTable,hashTableIndex);
			i++;
			break;
		case 2: displayFile(hashTable);
			z=0;
			break;
		default : printf("wrong choice\n");
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

	if(hashTable[hashTableIndex]==NULL){printf("1st node");
		hashTable[hashTableIndex]=temp;}
	else{
	 	struct node *ptr,*ptrp;
   		ptr=hashTable[hashTableIndex];
  		 ptrp=hashTable[hashTableIndex];
		if(fname[1]<ptr->fname[1]){
			printf("in front");
			temp->next=ptr;
			ptr->previous=temp;	
			hashTable[hashTableIndex]=temp;			
		}else{
 		 while(ptr->next!= NULL && ptr->fname[1]<fname[1]) {  // while(ptr->next != NULL){
    			ptrp=ptr;
      			ptr=ptr->next;
			printf("\nkeeping pointer to the required pos\n");
      			//ptr->previous=ptrp;
 			//ptrp->next=ptr;   
  		}
		if(ptr->next==NULL && ptr->fname[1]<fname[1]){
			printf("\n as it needs to b inserted on the last position,i m in\n");
   			ptrp=ptr;
   			ptr->next=temp;
   			temp->previous=ptrp;
		}
		else {//if (ptr->next==NULL&&ptr->fname[1]<fname[1]){//{printf("hello");ptr->previous=temp;}
			printf("\ninserting btw 2\n");
			ptrp->next=temp;
			temp->next=ptr;
			ptr->previous=temp;
			temp->previous=ptrp;
		}
		}
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
