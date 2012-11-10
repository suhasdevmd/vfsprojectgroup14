#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"


void add_file ( char *dest_dir_name, char *file_name, char *data )
{
	
	char dir_path[200];
	char file[200];
	char data_file_path[1024];
	int i,j;


	// path of the vfs file system ******************
	char vfs_path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(vfs_path,mheader.file_sys_label);



	struct file_descriptor fd_dir;


	strcpy(dir_path,dest_dir_name);
	strcpy(file,file_name);
	strcpy(data_file_path,data);



	strcpy(fd_dir.file_path,dir_path);
	strcpy(fd_dir.file_name,file);
	//strcpy(data_file_pth,data_file_path);

	
	strcpy(fd_dir.file_type,"file");


	i=get_file_descriptor_index();
	j=getFreeListIndex();


	fd_dir.location_block_number=j;
	fd_dir.file_descriptor_index=i;

	int bst=insertToBst(fd_dir);

	if(bst==0)
	{	
		

		fd_index[i]=1;
		f_desc[i]=fd_dir;
		free_list[f_desc[i].location_block_number]=1;
		printf("\nNOW GOING INTO NARRAY\n");
		insertToNarry(fd_dir);
		printf("i value in make directory : %d",i);
		struct block *blk=(struct block *)malloc(sizeof(struct block));
		block_ptr_array[fd_dir.location_block_number]=blk;
	
		
		//read from file and write into the block
		FILE *fp=fopen(data_file_path,"r");
		if(fp==NULL)
		{
			printf("Data File doesnot exist !!!\n");
		}
		else
		{
			fread(blk->buffer,1024,1,fp);
			printf(" \n Data read from the data file : %s \n",blk->buffer);

			blk->block_number=fd_dir.location_block_number;

			printf("\n The block number : %ld \n",blk->block_number);

			
			// writing the block value in the file system

			FILE *fptr;

			if((fptr=fopen(vfs_path,"rb+"))==NULL)
			{
				printf("VFS file system doesnot exist\n");
			}
			else
			{
				rewind(fptr);

				fseek(fptr,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(fd_dir.location_block_number*sizeof(struct block)),SEEK_SET);
        			fwrite(blk,sizeof(struct block),1,fptr);
        			
			}
			
			fclose(fptr);
				
		}

		fclose(fp);
		


		

	}else clearBst();




	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();

}




// function to check if the file name ends with .txt extension

//


int checkTxtFile(char fname[])
{
	int len = strlen(fname);
	int i;
	char* ext = ".txt";
	char* temp;
 
	for( i = 0; i < len; i++)
	{
		if(fname[i] == '.')
		{
			temp = fname+i;
			puts(temp);
			if(strcmp(ext,temp) == 0)
			{
				return 1;
			}
			else
				return 0;
		}
	}
}





void list_file ( char *file_path, char *output_file_name )
{


	char file_pth[200];
	char output_file[200];
	//char content[1024];
	struct block *content=(struct block *)malloc(sizeof(struct block));	


	char vfs_path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(vfs_path,mheader.file_sys_label);

	strcpy(file_pth,file_path);
	strcpy(output_file,output_file_name);




	// condition to check if the file is text file ?????? //

	//	 function for this should be written          //

	// ***************************************************//

	struct file_descriptor  *fdptr=searchAndGetFD(file_pth);



	int blk_no;

	if(fdptr==NULL)
	{
		printf("File doesnot exist \n");
	}
	else
	{


		int validtxtfile=checkTxtFile(fdptr->file_name);

		if(validtxtfile)
		{

			blk_no=fdptr->location_block_number;


			printf("\n\n The block number in list file : %d \n\n",blk_no);


			FILE *fp=fopen(vfs_path,"rb+");
			if(fp==NULL)
			{
				printf("File sys doesnot exist\n");
			}
			else
			{
				rewind(fp);
				fseek(fp,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(blk_no*sizeof(struct block)),SEEK_SET);
				fread(content,sizeof(struct block),1,fp); // reading the block structure from file system		
				



				FILE *fp1=fopen(output_file,"w+");

				printf("\n\nData to be written : %s \n",content->buffer);

				fwrite(content->buffer,strlen(content->buffer),1,fp1);
				printf("\nstrlen==%d",strlen(content->buffer));
				fclose(fp1);
							
			}
			
			fclose(fp);
		}
		else printf("Not a valid text file. \n"); // to be verified		
	}		




	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();
}



void update_file ( char *file_path, char *data )
{



	char file_pth[200];
	char data_file_path[200];

	char data_read[1024];


	char vfs_path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(vfs_path,mheader.file_sys_label);

	strcpy(file_pth,file_path);
	strcpy(data_file_path,data);

	struct block *blk=(struct block *)malloc(sizeof(struct block));


	struct file_descriptor  *fdptr=searchAndGetFD(file_pth);
	
	if(fdptr==NULL)
	{
		printf("File does not exist !!!\n");
	}
	else
	{
		
		FILE *fp=fopen(data_file_path,"r+");
		if(fp==NULL)
		{
			printf("Data file doesnot exist . \n");			
		}
		else
		{
			
			fseek(fp,0,SEEK_END);
			int number=ftell(fp);
			//rewind(fp);

			rewind(fp);

			//fseek(fp,0,SEEK_SET);

			printf("\nNumber of chars in the file : %d\n",number-1);

			
			fread(data_read,1,number-1,fp); // reading the data from the data file path
			data_read[number-1]='\0';
			
			// reading the data from the existing file and appending the read data

			int block_num=fdptr->location_block_number;
			FILE *fptr=fopen(vfs_path,"rb+");
			
			rewind(fptr);
			fseek(fptr,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(block_num*sizeof(struct block)),SEEK_SET);

			fread(blk,sizeof(struct block),1,fptr);


			printf(" Before updation dataread=%s*****************---------------------> %s",data_read,blk->buffer);

			strcat(blk->buffer,data_read);


			printf("Suhas data updated ***********------------length==%d--->>>>>>>>>> %s",strlen(blk->buffer),blk->buffer);

	
			// writing the back the updated file 

			
			rewind(fptr);
			fseek(fptr,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(block_num*sizeof(struct block)),SEEK_SET);

			fwrite(blk,sizeof(struct block),1,fptr);
			fclose(fptr);
		


		}
		fclose(fp);
		
	}




	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();
	
}



void remove_file ( char *file_path)
{
	char dir_path[200];
	strcpy(dir_path,file_path);
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



		}else printf("File doesnt exist");

	}
			for(i=0;i<fd_count;i++)
			{ 
				fd_index[i]=0;
				clearFD(i);
				free_list[Fdesc[i].location_block_number]=0;
				block_ptr_array[Fdesc[i].location_block_number]=NULL;
				printf("cleared %d index\n",i);
				deleteHash(Fdesc[i]);	
				deleteBST(Fdesc[i]);	
		
			}
		
		//fd_count=0;
	//	Fdesc=NULL;	
	

	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();

}



void move_file ( char *source_file_path, char *dest_file_path )
{
	char destPath[200];
	char sendpath[200];
	strcpy(destPath,dest_file_path);
	char sourcePath[200];
	int count=0;
	char prevpath[200];
	char path[200];
	char *tokens[200];
	strcpy(sourcePath,source_file_path);
	int i,j;


	if(strcmp(destPath,sourcePath)==0)
	{ printf("same source and destination path");}
	else{
		i=searchIfPathExists(sourcePath);
		if(i==0) printf("source path doesnt exist");
		j=searchIfPathExists(destPath);
		if(j==0) printf("destination path doesnt exist");


		if(i==1 &&j==1){

			printf("\n\n\n\n\n\n\n\n ######################## B4 deletion in file : \n\n\n\n\n\n\n\n");
			displayNaryMain();
	displayHash();
	displayBSTMain();


			strcpy(sendpath,sourcePath);
			del_dir_file(sendpath);
			deleteHashWithPath(sourcePath);	
			deleteB(sourcePath);

			printf("\n\n\n\n\n\n\n\n ######################## After deletion in file : \n\n\n\n\n\n\n\n");
			displayNaryMain();
	displayHash();
	displayBSTMain();



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


// added at 10:30 by rupali
void copy_file ( char *source_file_path, char *dest_file_path )
{	
	char sourcePath[200];
	strcpy(sourcePath,source_file_path);	
	char destPath[200];
	strcpy(destPath,dest_file_path);	
	struct file_descriptor * fdptr;
	struct file_descriptor FD;
	fdptr= searchAndGetFD(sourcePath);
	int i,j;

	
	char vfs_path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(vfs_path,mheader.file_sys_label);


	if(fdptr==NULL)
		printf("wrong source file path");
	else{	
			
		strcpy(FD.file_name,fdptr->file_name);
		strcpy(FD.file_path,destPath);
		strcpy(FD.file_type,fdptr->file_type);
		FD.file_size=fdptr->file_size;
		//FD.location_block_number=fdptr->location_block_number;
		//FD.file_descriptor_index=fdptr->file_descriptor_index;
		
		i=get_file_descriptor_index();
		j=getFreeListIndex();


		FD.location_block_number=j;
		FD.file_descriptor_index=i;
	
		int bst=insertToBst(FD);

		if(bst==0)
		{	
		

			fd_index[i]=1;
			f_desc[i]=FD;
			free_list[f_desc[i].location_block_number]=1;
			printf("\nNOW GOING INTO NARRAY\n");
			insertToNarry(FD);
			printf("i value in make directory : %d",i);
			struct block *blk=(struct block *)malloc(sizeof(struct block));
			struct block *blk_new=(struct block *)malloc(sizeof(struct block));
	
	
	
			FILE *fp=fopen(vfs_path,"rb+");
	
			if(fp==NULL)
			{
				printf("File system doesnot exist \n");
			}
			else
			{
				rewind(fp);
				fseek(fp,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(fdptr->location_block_number*sizeof(struct block)),SEEK_SET);

				fread(blk,sizeof(struct block),1,fp);

				strcpy(blk_new->buffer,blk->buffer);
				
				blk_new->block_number=FD.location_block_number;
		
				block_ptr_array[FD.location_block_number]=blk_new;

				// write into the file blk_new
		
				rewind(fp);
				fseek(fp,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(blk_new->block_number*sizeof(struct block)),SEEK_SET);

				fwrite(blk_new,sizeof(struct block),1,fp);
				


			}
			fclose(fp);
		
		}else clearBst();
	}



	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();

}



void export_file ( char *vfs_file_path, char *harddisk_path )
{

	char file_pth[200];
	char output_file[200];
	//char content[1024];
	
	struct block *content=(struct block *)malloc(sizeof(struct block));

	char vfs_path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(vfs_path,mheader.file_sys_label);

	strcpy(file_pth,vfs_file_path);
	strcpy(output_file,harddisk_path);




	struct file_descriptor  *fdptr=searchAndGetFD(file_pth);

	int blk_no;

	if(fdptr==NULL)
	{
		printf("File doesnot exist \n");
	}
	else
	{

		blk_no=fdptr->location_block_number;	
		FILE *fp=fopen(vfs_path,"rb+");
		if(fp==NULL)
		{
			printf("File sys doesnot exist\n");
		}
		else
		{
			rewind(fp);
			fseek(fp,sizeof(struct mainheader)+(sizeof(struct file_descriptor))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(sizeof(int))*(mheader.max_file_desc)+(blk_no*sizeof(struct block)),SEEK_SET);
			fread(content,1024,1,fp);			
			fclose(fp);



			FILE *fp1=fopen(output_file,"wb+");
			fwrite(content->buffer,strlen(content->	buffer),1,fp1);
			fclose(fp1);
					
		}

			
	}		

	free(content);	


	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();
	
}







//void searchSubstringFile(char substring[])
//void searchPaths(char fname[]);
//char *listPaths[100];  int listPathsIndex; char *listNames[100];  int listNamesIndex; add it to global 
void search_file ( char *file_name, char *output_File_name )
{	
	listPathsIndex=0;
	*listPaths=NULL;

	int i;
	char substring[200];
	strcpy(substring,file_name);
	searchSubstringFile(substring);



	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n ----------------> > > > > after search sustring \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");


	listPathsIndex=0;
	*listPaths=NULL;
	int j,k;
	if(listNamesIndex!=0)
		searchPaths(listNames[0]);
	for(i=1;i<listNamesIndex;i++)
	{	k=0;
		for(j=0;j<i;j++)
		{
			if(listNames[i]==listNames[j])
			k=1;
		}
		if(k==1)
		searchPaths(listNames[i]);	

	}

	printf("\n\n\n\n\n\n\n\n\n\n listPathsInde : %d \n\n\n\n\n\n\n",listPathsIndex);


	for(i=0;i<listPathsIndex;i++)
	printf("%s\n",listPaths[i]);
	//listPaths contains all the paths to be written in outputfile,listPathsIndex




	printf("\n Displaying the contents of Data structure . \n");
	displayNaryMain();
	displayHash();
	displayBSTMain();

}

