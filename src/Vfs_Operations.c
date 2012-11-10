#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"



void create_vfs(char filelabel[],long int size)
{
	FILE *fp;
	char a[1000000]={'a'};
	//char (*suhas)[];
	int i,ss;
	//suhas=(char *)malloc(sizeof(char)*1000000);
	
	
	// declared mainheader structure in the .h file


	// ************* initializing the global variables ***********

	//fd_count=0; //count of files and folders to be deleted
	//Fdesc=(struct file_descriptor *)NULL;// files to be deleted

	// ************ initialization ends **************************

	//creating the large binary file


	char path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(path,filelabel);


	fp=fopen(path,"wb+");

	if(fp==NULL)
	{
		printf("File doesnot exist.\n");
	}
	else
	{
		//allocating memory 
		//fseek(fp,size,SEEK_SET);
		rewind(fp);
		//fwrite(suhas,sizeof(char)*1000000,1,fp);
		//fwrite(a,size,1,fp);




		fseek(fp, size*1024, SEEK_SET);
		fputc('\n', fp);
		//fclose(fp);

		//for(ss=0;ss<1000000;ss++)
		//{
		//	putc('a',fp);
		//}


	}


	//fp=fopen(path,"wb");

	//initializing the main header structure

	strcpy(mheader.file_sys_label,filelabel);
	mheader.used_file_desc=0;
	mheader.max_file_desc=MAX_FILE_DESC;
	//struct file_descriptor fd;
	//struct freelist fl;
	//mheader.file_desc=fd;
	//mheader.free_list=fl;




	//writing the mainheader structure into the memory

	fseek(fp,0,SEEK_SET);
	fwrite(&mheader,sizeof(struct mainheader),1,fp);




	// declared file descriptor array in the header file


	// ***************************** initializing fd_index and free_list array to 0  *********************************
	for(i=0;i<mheader.max_file_desc;i++)
	{
		//f_desc[i].location_block_number=i;

		//setting the block number and isFree to 0 to indicate its free
		//free_list[i].block_number=i;
		free_list[i]=0;
		fd_index[i]=0;
	}



	// *** initializing the first file descriptor for checking ************  to be removed ****************

	/* strcpy(f_desc[0].file_name,"Rupali");
	strcpy(f_desc[0].file_path,"ROOT/suhas/rupali");
	strcpy(f_desc[0].file_type,"directory");
	f_desc[0].file_descriptor_index=0;
	fd_index[0]=1;

	strcpy(f_desc[1].file_name,"rupali");
	strcpy(f_desc[1].file_path,"ROOT/suhas");
	strcpy(f_desc[1].file_type,"directory");
	f_desc[1].file_descriptor_index=1;
	fd_index[1]=1;
	
	strcpy(f_desc[2].file_name,"suhas");
	strcpy(f_desc[2].file_path,"ROOT");
	strcpy(f_desc[2].file_type,"directory");
	f_desc[2].file_descriptor_index=2;
	fd_index[2]=1;
	
	strcpy(f_desc[3].file_name,"Rupali");
	strcpy(f_desc[3].file_path,"ROOT/suhas/rupali");
	strcpy(f_desc[3].file_type,"directory");
	f_desc[3].file_descriptor_index=3;
	fd_index[3]=1;
	
	*/	
	// *** end initializing




	
	fseek(fp,sizeof(struct mainheader),SEEK_SET);
	fwrite(&f_desc,(sizeof(struct file_descriptor))*(mheader.max_file_desc),1,fp);
	fwrite(&free_list,(sizeof(int))*(mheader.max_file_desc),1,fp);
	fwrite(&fd_index,(sizeof(int))*(mheader.max_file_desc),1,fp);



	fclose(fp);

	// written for testing purpose -------------(to be removed)----------->

	printf("\nReading the VFS name ---------> \n");
	//reading the contents of the file
	struct block b;
	char m[100];

	struct mainheader mh;
	FILE *fp1=fopen(path,"rb+");
	fread(&mh,sizeof(struct mainheader),1,fp1);
	printf("\n%s\n",mh.file_sys_label);
	fclose(fp1);

	// ---------- to be removed -------------------------------



}


// function for mounting the VFS

void mount_vfs(char filelabel[]){

	char path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(path,filelabel);
	int i;
	FILE *fp;


	fp=fopen(path,"rb+");
	naryRoot();// create root for narry
	getBstRoot();// create root for bst

	if(fp==NULL)
	{
		printf("File doesnot exist.\n");
	}
	else
	{	//mounting array
		
		fread(&mheader,sizeof(struct mainheader),1,fp);
		fread(&f_desc,(sizeof(struct file_descriptor))*(mheader.max_file_desc),1,fp);
		fread(&free_list,(sizeof(int))*(mheader.max_file_desc),1,fp);
		fread(&fd_index,(sizeof(int))*(mheader.max_file_desc),1,fp);
	
		printf("Inside mount0.\n");
		

		int la;	
		for(la=0;la<25;la++) {printf("%d .. %s\n",la,f_desc[la].file_name);}
		for(la=0;la<25;la++) {printf(" - --------------> %d..%d\n",la,fd_index[la]);}

		for(i=1;i<mheader.max_file_desc;i++){
			if(fd_index[i]!=0)
			{
				struct file_descriptor fd;
				fd=f_desc[i];
				int bst=insertToBst(fd);
				if(bst==0){
					
					printf("\nNOW GOING INTO NARRAY\n");
					insertToNarry(fd);
				}else clearBst();
			}
		}


		fclose(fp);
	
		printf("Completed mounting.\n");
	}

	
}


// function for clearing the file descriptor

void clearFD(int index)
{
	fd_index[index]=0;
	strcpy(f_desc[index].file_path,"");
	strcpy(f_desc[index].file_name,"");
	strcpy(f_desc[index].file_type,"");
	f_desc[index].file_size=0;
	f_desc[index].location_block_number=0;
	f_desc[index].file_descriptor_index=0;

}



// function for unmounting the VFS


void unmount_vfs(char filelabel[]){

	char path[100]="/home/suhasdev/Desktop/VfsProject/";
	strcat(path,filelabel);
	FILE *fp;
	int i;
	
	fp=fopen(path,"rb+");

	if(fp==NULL)
	{
		printf("File doesnot exist.\n");
	}
	else
	{
		
		rewind(fp);
		int l;		
		                 printf("before unmounting\n");
		for(l=0;l<25;l++) printf("%d..%s",l,f_desc[l].file_name);
		// initializing the f_desc and fd_index to null values 

		for(i=0;i<1024;i++)
		{

			clearFD(i);
			//fd_index[i]=0;
			//strcpy(f_desc[i].file_path,"");
			//strcpy(f_desc[i].file_name,"");
			//strcpy(f_desc[i].file_type,"");
			//f_desc[i].file_size=0;
			//f_desc[i].location_block_number=0;
			//f_desc[i].file_descriptor_index=0;
		}
		
		printf("after  clearing the file descriptor array\n");		
		
		for(l=0;l<25;l++) printf("%d .. %s\n",l,f_desc[l].file_name);


		unmount_filesystem();
		

		printf("after unmounting the file descriptor array\n");
		
		for(l=0;l<25;l++) printf("%d .. %s",l,f_desc[l].file_name);
	
		fseek(fp,0,SEEK_SET);
		fwrite(&mheader,sizeof(struct mainheader),1,fp);
		fwrite(&f_desc,(sizeof(struct file_descriptor))*(mheader.max_file_desc),1,fp);
		fwrite(&free_list,(sizeof(int))*(mheader.max_file_desc),1,fp);
		fwrite(&fd_index,(sizeof(int))*(mheader.max_file_desc),1,fp);
	}
	unmountNaryRoot();
	unmountHash();
	unmountBSTRoot();
	fclose(fp);
}

