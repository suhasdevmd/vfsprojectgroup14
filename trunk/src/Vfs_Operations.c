#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./../include/allheaders.h"


void create_vfs(char filelabel[],long int size)
{
FILE *fp;
char a[10]={""};
int i;

// declared mainheader structure in the .h file


//creating the large binary file 
char path[100]="/home/suhasdev/Desktop/VfsProject/";
strcat(path,filelabel);


fp=fopen(path,"wb");

if(fp==NULL)
{
printf("File doesnot exist.\n");
}
else
{
//allocating memory 
fseek(fp,size,SEEK_SET);
fwrite(a,1,1,fp);
}


//initializing the main header structure

strcpy(mheader.file_sys_label,filelabel);
mheader.used_file_desc=0;
mheader.max_file_desc=MAX_FILE_DESC;
struct file_descriptor fd;
struct freelist fl;
mheader.file_desc=fd;
mheader.free_list=fl;




//writing the mainheader structure into the memory

fseek(fp,0,SEEK_SET);
fwrite(&mheader,sizeof(struct mainheader),1,fp);





//creating the array of file descriptors and storing it in memory
//more number of file descriptors than the number of blocks

// declared file descriptor array in the header file


for(i=0;i<mheader.max_file_desc;i++)
{
f_desc[i].location_block_number=i;

//setting the block number and isFree to 0 to indicate its free
free_list[i].block_number=i;
free_list[i].isFree=0;
}



// *** initializing the first file descriptor for checking

strcpy(f_desc[0].file_name,"SuhasDev");
strcpy(f_desc[0].file_path,"ROOT/suhas/dev");
strcpy(f_desc[0].file_type,"directory");
free_list[0].isFree=1;


strcpy(f_desc[1].file_name,"Rupali");
strcpy(f_desc[1].file_path,"ROOT/suhas/rupali");
strcpy(f_desc[1].file_type,"directory");
free_list[1].isFree=1;


// *** end initializing




naryRoot();// create root for narry


fseek(fp,sizeof(struct mainheader),SEEK_SET);
fwrite(&f_desc,(sizeof(struct file_descriptor))*(mheader.max_file_desc),1,fp);

fwrite(&free_list,(sizeof(struct freelist))*(mheader.max_file_desc),1,fp);



// written for testing purpose----------->

printf("\nReading the VFS name ---------> \n");
//reading the contents of the file
struct block b;
char m[100];

struct mainheader mh;
FILE *fp1=fopen(path,"rb");
fread(&mh,sizeof(struct mainheader),1,fp1);
printf("\n%s\n",mh.file_sys_label);



}


// function for mounting the VFS

void mount_vfs(char filelabel[]){

char path[50]="/home/suhasdev/Desktop/VfsProject/";
strcat(path,filelabel);
int i;


FILE *fp=fopen(path,"rb");

if(fp==NULL){
printf("File doesnot exist.");
return;
}


fread(&mheader,sizeof(struct mainheader),1,fp);
fread(&f_desc,(sizeof(struct file_descriptor))*(mheader.max_file_desc),1,fp);
fread(&free_list,(sizeof(struct freelist))*(mheader.max_file_desc),1,fp);


printf("Inside mount0.\n");

for(i=0;i<mheader.max_file_desc;i++){
if(free_list[i].isFree!=0){
struct file_descriptor fd;
fd=f_desc[i];
printf("Inside mount1.\n");
insertToNarry(fd);
//insertToHash(fd);
//insertToBst(&fd);
}
}


printf("Inside mount.\n");
}




// function for unmounting the VFS


void unmount_vfs(char filelabel[]){

char path[50]="/home/suhasdev/Desktop/VfsProject/";
strcat(path,filelabel);
FILE *fp;

fp=fopen(path,"wb");

if(fp==NULL)
{
printf("File doesnot exist.\n");
}
else
{
fseek(fp,0,SEEK_SET);
fwrite(&mheader,sizeof(struct mainheader),1,fp);
fwrite(&f_desc,(sizeof(struct file_descriptor))*(mheader.max_file_desc),1,fp);
fwrite(&free_list,(sizeof(struct freelist))*(mheader.max_file_desc),1,fp);
}

fclose(fp);
}


            











