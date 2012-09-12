#include<stdio.h>
#include<string.h>
#include "./../include/block.h"
#include "./../include/file_descriptor.h"
#include "./../include/freelist.h"
#include "./../include/mainheader.h" 


int main()
{
FILE *fp;
char a[10]={""};
struct mainheader mheader;
int i;

//creating the large binary file 
fp=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","wb");

if(fp==NULL)
{
printf("File doesnot exist.\n");
}
else
{
//allocating 1MB of memory and initializing with 0
fwrite(a,1,10000000,fp);
}


//initializing the main header structure

strcpy(mheader.file_sys_label,"VfsProject");
mheader.used_file_desc=0;
mheader.max_file_desc=100;
struct file_descriptor fd={{0}};
struct freelist fl={{0}};
mheader.file_desc=fd;
mheader.free_list=fl;


//writing the mainheader structure into the memory

fseek(fp,0,SEEK_SET);
fwrite(&mheader,sizeof(struct mainheader),1,fp);



//creating the array of file descriptors and storing it in memory
struct file_descriptor f_desc[20];
memset ( f_desc, 0x00, sizeof(f_desc));// for initializing the array of fds' to 0

fseek(fp,sizeof(struct mainheader),SEEK_SET);
fwrite(&f_desc,sizeof(struct file_descriptor),20,fp);

//creating the blocks in the memory
struct block blk[100];
memset ( blk, 0x00, sizeof(blk));// initializing the blocks to 0

for(i=0;i<100;i++)
{
blk[i].address=1000;
strcpy(blk[i].buffer,"Block1");
}

fseek(fp,sizeof(struct mainheader)+(sizeof(struct file_descriptor)*20)+1000,SEEK_CUR);
fwrite(&blk,sizeof(struct block),100,fp);



printf("\nReading the VFS name ---------> \n");
//reading the contents of the file
char b[100];
FILE *fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
fread(b,1,12,fp1);
printf("\n%s\n",b);

printf("\nReading the block ---------> \n");
//fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
fseek(fp1,0,SEEK_SET);
fseek(fp1,sizeof(struct mainheader)+(sizeof(struct file_descriptor)*20)+1000,SEEK_SET);
fread(b,1,12,fp1);
//fread(b,1,10000000,fp1);

printf("\n%s\n",b);
printf("\nAfter reading block 1 \n");

return 0;
}
