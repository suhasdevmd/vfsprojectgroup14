#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void update_file(char file_path[],char data[]){

FILE *fp=NULL;
fp=fopen(file_path,"a+");

if(fp!=NULL){
fseek(fp,0,SEEK_END);
fwrite(data,sizeof(data),1,fp);
}


}





int main(int argc,char *argv[]){

char file_path[20];
char data[20];

strcpy(file_path,argv[1]);
strcpy(data,argv[2]);

printf("%s , %s\n",file_path,data);

update_file(file_path,data);

return 0;
}
