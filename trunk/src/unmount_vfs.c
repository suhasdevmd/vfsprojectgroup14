#include<stdio.h>
#include<string.h>
#include "./../include/block.h"
#include "./../include/file_descriptor.h"
#include "./../include/freelist.h"
#include "./../include/mainheader.h" 


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




int main(int argc, char *argv[])
{
 char label[20];

 printf("\n Mounting the vfs. \n");

 strcpy(label,argv[1]);

 unmount_vfs(label);

 return 0;
}
