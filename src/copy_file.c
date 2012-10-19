#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void copy_file(char source_path[],char dest_path[]){

FILE *source,*dest;

source=fopen(source_path,"rb");
dest=fopen(dest_path,"wb");
char buffer[10000];

if(source!=NULL){
if(fread(buffer,sizeof(buffer),1,source)!=0){
fwrite(buffer,sizeof(buffer),1,dest);
}
}



}





int main(int argc,char *argv[]){

char source_path[20];
char dest_path[20];

strcpy(source_path,argv[1]);
strcpy(dest_path,argv[2]);

printf("%s , %s\n",source_path,dest_path);

	copy_file(source_path,dest_path);

return 0;
}

