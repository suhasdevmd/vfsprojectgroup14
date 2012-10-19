#include<stdio.h>
#include<string.h>
#include "./../include/block.h"
#include "./../include/file_descriptor.h"
#include "./../include/freelist.h"
#include "./../include/mainheader.h" 


int main()
{

printf("\n Mounting the vfs. \n");
//reading the contents of the file
struct block b[100];
struct file_descriptor fd[20];
int i;
char m[100];


FILE *fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
fread(m,1,12,fp1);
printf("\nFile System name : %s\n",m);


// reading the file descriptors

printf("\nReading the file descriptor ---------> \n");
fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
//fseek(fp1,1000,SEEK_SET);
fseek(fp1,sizeof(struct mainheader),SEEK_SET);
fread(&fd,sizeof(struct file_descriptor),20,fp1);

for(i=0;i<20;i++)
{
printf("\n%s\n",fd[i].file_path);
}
printf("\nFinished reading the file descriptor \n");



printf("\nInitializing the data structures. \n");
printf("\nInitializing N-arry tree. \n");
printf("\nInitializing Hash Table. \n");

// reading the blocks

printf("\nReading the block ---------> \n");
fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
//fseek(fp1,1000,SEEK_SET);
fseek(fp1,sizeof(struct mainheader)+(sizeof(struct file_descriptor)*20),SEEK_SET);
fread(&b,sizeof(struct block),100,fp1);
//fread(b,1,10000000,fp1);


for(i=0;i<100;i++)
{
//printf("\n%d\n",b[i].address);
}
printf("\nFinished reading 100 blocks \n");

return 0;
}
