/*
 * File: vfsdriver.c
 *
 * Description: This is a driver program for testing your VFS system using an interaction script as input
 * You need to make additional calls to your respective functions as noted in the comments below
 * Make sure the output you display is exactly as per the given specifications for you. Do NOT print
 * any extra output (like debug messages) in the final version of your driver program. You can use this driver program
 * in a in incremental manner as you keep implementing one operator after another. For operators not yet implemented,
 * you can leave the output as given ("TO_BE_DONE"). So you can use this program as your "main" program for testing purposes.
 *
 * DO NOT write the full code for operators in the driver program! You must only CALL your functions from here.
 *
 * Usage: vfsdriver <scriptfilename>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "./../include/allheaders.h"

#define BUFSIZE 200
#define CMDSIZE 30
#define PARSIZE 100

void createvfs ( char *P1, int P2 );
void mountvfs ( char *P1 );
void unmountvfs ( char *P1 );
void makedir ( char *P1, char *P2 );
void deletedir ( char *P1 );
void movedir ( char *P1, char *P2 );
void listdir ( char *P1, int P2, char *P3 );
void addfile ( char *P1, char *P2, char *P3 );
void listfile ( char *P1, char *P2 );
void updatefile ( char *P1, char *P2 );
void removefile ( char *P1 );
void movefile ( char *P1, char *P2 );
void copyfile ( char *P1, char *P2 );
void exportfile ( char *P1, char *P2 );
void searchfile ( char *P1, char *P2 );

void processcommand( char *command, char *P1, char *P2, char *P3 );

int main( int argc, char *argv[] )
{
	FILE *scriptfp;
	char linebuffer[BUFSIZE];
	char command[CMDSIZE], par1[PARSIZE], par2[PARSIZE], par3[PARSIZE];
	char *token;

	if( argc != 2 ){
		fprintf(stderr,"Usage: vfsdriver <scriptfile>\n");
		return(1);
	}

	if( (scriptfp=fopen(argv[1],"r")) == NULL ){
		fprintf(stderr,"Unable to open script file: %s\n", argv[1]);
		return(2);
	}

	while( fgets(linebuffer, sizeof(linebuffer), scriptfp) != NULL ){
		/* This output is for debugging... do not uncomment in final version */
		/*
		printf("==================================================\n");
		printf("Processing: %s", linebuffer);
		printf("==================================================\n");
		*/

		/* Remove the extra newline character in the end of line */
		linebuffer[ strlen(linebuffer)-1 ] = '\0';
		
		/* Get the command and the parameters using tokenizer */
		strcpy( command, (token = strtok(linebuffer, " ")) == NULL ? "" : token );
		
		strcpy( par1, (token = strtok(NULL, " ")) == NULL ? "" : token );
		strcpy( par2, (token = strtok(NULL, " ")) == NULL ? "" : token );
		strcpy( par3, (token = strtok(NULL, " ")) == NULL ? "" : token );
		/* printf("Command:%s:p1:%s:p2:%s:p3:%s\n",command, par1, par2, par3); */

		processcommand( command, par1, par2, par3 );
	}
}

void processcommand( char *command, char *P1, char *P2, char *P3 )
{
	if( strcmp(command, "createvfs") == 0 ){
		int size = atoi(P2);
		createvfs (P1,size);
	}
	else if( strcmp(command, "mountvfs") == 0 )
		mountvfs (P1);
	else if( strcmp(command, "unmountvfs") == 0 )
		unmountvfs (P1);
	else if( strcmp(command, "makedir") == 0 )
		makedir (P1,P2);
	else if( strcmp(command, "deletedir") == 0 )
		deletedir (P1);
	else if( strcmp(command, "movedir") == 0 )
		movedir (P1,P2);
	else if( strcmp(command, "listdir") == 0 ){
		int flag = atoi(P2);
		listdir (P1,flag,P3);
	}
	else if( strcmp(command, "addfile") == 0 )
		addfile (P1,P2,P3);
	else if( strcmp(command, "listfile") == 0 )
		listfile (P1,P2);
	else if( strcmp(command, "updatefile") == 0 )
		updatefile (P1,P2);
	else if( strcmp(command, "removefile") == 0 )
		removefile (P1);
	else if( strcmp(command, "movefile") == 0 )
		movefile (P1,P2);
	else if( strcmp(command, "copyfile") == 0 )
		copyfile (P1,P2);
	else if( strcmp(command, "exportfile") == 0 )
		exportfile (P1,P2);
	else if( strcmp(command, "searchfile") == 0 )
		searchfile (P1,P2);
	else
		printf("Ignoring invalid command %s\n", command);
}

void createvfs ( char *P1, int P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling create_vfs **************\n");
	create_vfs(P1,P2);
}

void mountvfs ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling mount_vfs.. **************\n");
	mount_vfs(P1);
}

void unmountvfs ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling unmountvfs **************\n");
	unmount_vfs(P1);
}

void makedir ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling makedir ***********************\n");
	make_dir(P1,P2);
}

void deletedir ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling deletedir ^^^^^^^^^^^^^^^^^^^^^^^^ ---------------> > > > \n");
	delete_dir(P1);
}

void movedir ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling movedir **************************\n");
	move_dir(P1,P2);
}

void listdir ( char *P1, int P2, char *P3 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling listdir >>>>>>>>>>>>>>>>>>>>>>>>>\n");
	list_dir(P1,P2,P3);
}

void addfile ( char *P1, char *P2, char *P3 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("addfile_TO_BE_DONE\n");
	add_file(P1,P2,P3);
}

void listfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("\ncalling listfile *********************\n");
	list_file(P1,P2);
}

void updatefile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling updatefile *********************\n");
	update_file(P1,P2);
}

void removefile ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling removefile ^^^^^^^^^^^^^^^^^^^^^^ --------------> > > \n");
	remove_file(P1);
}

void movefile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling movefile *************************************\n");
	move_file(P1,P2);
}

void copyfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling copyfile *************************\n");
	copy_file(P1,P2);
}

void exportfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("calling exportfile ************************\n");
	export_file(P1,P2);
}

void searchfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	printf("\ncalling searchfile ***************************************************\n");
	search_file(P1,P2);

}


