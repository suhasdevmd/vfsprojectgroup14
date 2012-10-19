#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void create_file(char dest_dir_name[],char file_name[],char data[])
{

int a=0,b=0,c=0;

char file_loc[40];

//int i=strlen(dest_dir_name);

while(dest_dir_name[a]!='\0')
{
file_loc[b]=dest_dir_name[a];
a++;
b++;
}

file_loc[b]='/';
b++;

//i=strlen(dest_dir_name);

while(file_name[c]!='\0')
{
file_loc[b]=file_name[c];
b++;
c++;
}

file_loc[b]='\0';

printf("File location : %s\n",file_loc);

FILE *fp=fopen(file_loc,"wb");

if(fp!=NULL)
{
printf("File created");
fwrite(data,sizeof(char),strlen(data),fp);

}



}


int main(int argc,char *argv[]){

char dest_dir_name[20];
char file_name[20];
char data[20];

strcpy(dest_dir_name,argv[1]);
strcpy(file_name,argv[2]);
strcpy(data,argv[3]);

printf("%s , %s , %s\n",dest_dir_name,file_name,data);

create_file(dest_dir_name,file_name,data);

return 0;
}
