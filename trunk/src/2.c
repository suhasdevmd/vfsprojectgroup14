#include<stdio.h>
#include<stdlib.h>
#define MAX_FILE_DESC 100

typedef struct block{//8
int address;
char *buffer;
}block;

typedef struct freelist {//8
int block_number;
struct freelist *next;
}f_l;

enum type {directory=0,regular,socket}; // written for testing

typedef struct file_descriptor{//20
char *file_name;
char *file_path;
enum type file_type;
long int file_size;
}f_d;

typedef struct mainheader{//100+4+20*10+8*10=100+4+200+80=384
char* file_sys_label;
int used_file_desc;
f_l file_desc[10];
f_l free_list[10];
}mh;

int main(){
FILE *f;
f=fopen("/home/apoorve/Desktop/a1.txt","wb");
//declare the mainheader struture
mh *p;
p=(mh*)(malloc(sizeof(mh)));
p->file_sys_label="vfs_ubuntu";
p->used_file_desc=0;
p->file_desc[10];
p->free_list[10];

//1.declare for loop
//2.loop it from 1 to 10
//3.declare structure in it.initialize structure values to zero.
fwrite(p,400,1000,f);
fclose(f);
return 0;
}
