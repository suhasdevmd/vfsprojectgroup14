#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"




int get_file_descriptor_index(){

	int i=0;
	while(fd_index[i]!=0)
	{
		i++;
	}

	return i;
}



int getFreeListIndex(){
	int j=0;

	while(free_list[j]!=0)
	{
		j++;
	}

	return j;
}





void make_dir ( char *parent_path, char *dir_name)
{

// to check if the path and directory exists
// call insertTonarry();


char path[200];
char dirname[200];
int i,bst;
struct file_descriptor fd_dir;


// to check if the path and directory exists
	strcpy(path,parent_path);
	strcpy(dirname,dir_name);



	strcpy(fd_dir.file_path,path);
	strcpy(fd_dir.file_name,dirname);

	fd_dir.file_size=0;
	strcpy(fd_dir.file_type,"directory");
	fd_dir.location_block_number=-1;
	i=get_file_descriptor_index();
	fd_dir.file_descriptor_index=i;

	bst=insertToBst(fd_dir);

	if(bst==0)
	{
		fd_index[i]=1;
		f_desc[i]=fd_dir;
		printf("\nNOW GOING INTO NARRAY\n");
		insertToNarry(fd_dir);
		printf("i value in make directory : %d",i);
	}
	else clearBst();



	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();
	
}



void delete_dir ( char *path )
{
	char dir_path[200];
	strcpy(dir_path,path);
	int i;

	// whether it should be || in place of && in if clause ?????????? ---- Suhas



	if(strcmp(dir_path,"ROOT")==0 || strcmp(dir_path,"ROOT/")==0)
		del_root(dir_path);
	else 
	{	
		int a=searchIfPathExists(dir_path);
		printf("\naaaaaaaaaaaaaaa=============    %d\n",a);
		if(a==1){
			printf("\nyes path exists\n");
			del_dir_file(dir_path);//naray deletion
			printf("\n deleted from narray major achievement\n");
			for(i=0;i<fd_count;i++)
			printf("\n		name :%s   and path=%s \n",Fdesc[i].file_name,Fdesc[i].file_path);



		}else printf("directory doesnt exist doesnt exist");

	}
			for(i=0;i<fd_count;i++)
			{ 
				fd_index[i]=0;
				clearFD(i);
				//free_list[deleteHash(Fdesc[i].location_block_number)]=0;
				printf("cleared %d index\n",i);
				deleteHash(Fdesc[i]);	
				deleteBST(Fdesc[i]);	

				


		
			}



	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();


}




// char* getNewPath(int count,char oldPath[] ,char *apendPath) is to initialised globally

void move_dir ( char *source_dir_path, char *dest_dir_path )
{
	char destPath[200];
	char sendpath[200];
	strcpy(destPath,dest_dir_path);
	char sourcePath[200];
	int count=0;
	char prevpath[200];
	char path[200];
	char *tokens[200];


	strcpy(sourcePath,source_dir_path);


	if(strcmp(destPath,sourcePath)==0)
	{ 
		printf("same source and destination path");}
	else{
		int i=searchIfPathExists(sourcePath);
		if(i==0) printf("source path doesnt exist");
		int j=searchIfPathExists(destPath);
		if(j==0) printf("destination path doesnt exist");
		if(i==1 &&j==1){

			printf("\n before nary deletion .******************************");
			
			strcpy(sendpath,sourcePath);
			del_dir_file(sendpath);
			displayNaryMain();

			printf("\n\n\n\n \n\n\n\n\n deleted from Nary .******************************\n\n\n\n\n");

			deleteHashWithPath(sourcePath);	

			deleteB(sourcePath);
	
		
			strcpy(prevpath,Fdesc[0].file_path);
			strcpy(Fdesc[0].file_path,destPath);
			int bst1=insertToBst(Fdesc[0]);
			if(bst1==0)
			{
				printf("\nNOW GOING INTO NARRAY\n");
				insertToNarry(Fdesc[0]);// getting inserted into hash thru narray
			} clearBst();

				
		
			tokens[count]=strtok(prevpath,"/");
					
			
			while(tokens[count]!=NULL)
     			{ 
           			count++;
           			tokens[count]=strtok(NULL,"/");//storing the tokens in the array of char pointers pointing to each token
           
			      }
		

			for(i=1;i<fd_count;i++){
				deleteHash(Fdesc[i]);	
				deleteBST(Fdesc[i]);
			}
					
			for(i=1;i<fd_count;i++){
				strcpy(sendpath,destPath);
				strcpy(Fdesc[i].file_path,getNewPath(count,Fdesc[i].file_path,sendpath));
			
				int bst2=insertToBst(Fdesc[i]);

				if(bst2==0)
				{
					printf("\nNOW GOING INTO NARRAY\n");
					insertToNarry(Fdesc[i]);// getting inserted into hash thru narray
				}
				else clearBst();						
			}
		}

	}


	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();
	

}




void list_dir ( char *dir_name, int flag, char *output_file_name ){
	char dirname[200];
	strcpy(dirname,dir_name);
	int i;
	if(strcmp(dirname,"ROOT")==0)
		i=1;
		else i=searchIfPathExists(dirname);
	if(i==1)
	{
	if(flag==0)
		list_dir_normal(dirname);	
	else if (flag==1)
 		recursive_list(dirname);
	else printf("wrong value for flag");								
	}



	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();

}


//*********************************************         by rupali ,added a function in hash also : void searchPaths(char fname[]); 
/*
void list_dir ( char *dir_name, int flag, char *output_file_name )
{
	char *list[100]; // declare it globally
//	void searchPaths(char fname[]);       declaration globally
	char dirname[200];
	char flag[10];

	strcpy(dirname,dir_name);
		searchPaths(dirname);
	if(list==NULL)
		printf("directory doesnt exist");
	else{
		while(list[k]!=NULL){
		//	printf("%s",list[k]);

			


			k++;
		}		


	}
	// listdir();
}
*/

//void list_dir(char path[]);  void recursive_list(char path[]); global declaration
//  

