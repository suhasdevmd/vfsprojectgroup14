#include<stdio.h>
#include<string.h>
#include "./../include/block.h"
#include "./../include/file_descriptor.h"
#include "./../include/freelist.h"
#include "./../include/mainheader.h" 






void create_vfs(char filelabel[],long int size)
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
//allocating 1MB of memory 
fseek(fp,size,SEEK_SET);
fwrite(a,1,1,fp);
}




//initializing the main header structure

strcpy(mheader.file_sys_label,filelabel);
mheader.used_file_desc=0;
mheader.max_file_desc=100;
struct file_descriptor fd;
struct freelist fl;
mheader.file_desc=fd;
mheader.free_list=fl;




//writing the mainheader structure into the memory

fseek(fp,0,SEEK_SET);
fwrite(&mheader,sizeof(struct mainheader),1,fp);





//creating the array of file descriptors and storing it in memory
struct file_descriptor f_desc[20];
//memset ( f_desc, 0x00, sizeof(f_desc));// for initializing the array of fds' to 0


for(i=0;i<20;i++)
{
strcpy(f_desc[i].file_name,"Sample");
strcpy(f_desc[i].file_path,"/home/suhasdev/Desktop/VfsProject");
strcpy(f_desc[i].file_type,"regular");
f_desc[i].file_size=1024;
}


fseek(fp,sizeof(struct mainheader),SEEK_SET);
fwrite(&f_desc,sizeof(struct file_descriptor),20,fp);



/*long int remaining_size=size-(sizeof(struct mainheader)+(sizeof(struct file_descriptor))*20));

int no_of_blocks=remaining_size/(sizeof(struct block));

printf("Number of blocks : %d",no_of_blocks)
*/

//creating the blocks in the memory
struct block blk[100];
//memset ( blk, 0x00, sizeof(blk));// initializing the blocks to 0

for(i=0;i<100;i++)
{
blk[i].address=1000;
strcpy(blk[i].buffer,"Block1");
}


//fseek(fp,1000,SEEK_SET);
fseek(fp,sizeof(struct mainheader)+(sizeof(struct file_descriptor)*20),SEEK_SET);
fwrite(&blk,sizeof(struct block),100,fp);





printf("\nReading the VFS name ---------> \n");
//reading the contents of the file
struct block b;
char m[100];
FILE *fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
fread(m,1,20,fp1);
printf("\n%s\n",m);

printf("\nReading the block ---------> \n");
fp1=fopen("/home/suhasdev/Desktop/VfsProject/VFSystem","rb");
//fseek(fp1,1000,SEEK_SET);
fseek(fp1,sizeof(struct mainheader)+(sizeof(struct file_descriptor)*20),SEEK_SET);
fread(&b,sizeof(struct block),1,fp1);
//fread(b,1,10000000,fp1);

printf("\n%d\n",b.address);
printf("\nAfter reading block 1 \n");


}


int main(int argc, char *argv[])
{
  char label[20];
  long int size;


  if ( argc < 3 ) 
  {
       
	printf("Value of argc : %d",argc);
        printf( "usage: %s filename", argv[0] );
  }
  else 
  {

	strcpy(label,argv[1]);
	size=atol(argv[2]);

        create_vfs(label,size);
  }
return 0;
}


