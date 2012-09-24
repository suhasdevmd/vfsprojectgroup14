#include <stdio.h>
#include <string.h>

struct nary{
	char file_name[10];
	int file;
	int children;
	struct nary *parent;
	struct nary *sibling;
	struct nary *child;
}

struct nary* found;

void create_dir_or_file(struct nary* root, char* filename, char* parent_name,int file_flag){ //create a directory
	int check = traverse_chk(struct nary* root, char* parent_name); //check whether the 'parent name' is present or not, and if present
	if (check == 0){												//check if its a file or a folder
		printf("\n *******Parent folder not found******* "); //if its not found
	}
	else if(check == 2){
		printf("\n *******Parent name is not a folder********"); // found and its a file
	}
	
	struct nary *temp;
	temp = found; //this points to the node containing
	if(temp->child != NULL){
		while(temp->child->sibling != NULL){
			temp->child = temp->child->sibling;
		}
	}
	struct nary *newnode = (struct nary *)malloc(sizeof(struct nary));
	
	strcpy(newnode->file_name,char* filename);
	temp->child->sibling = newnode;
	newnode->parent = found;
	newnode->child = NULL;
	newnode->sibling = NULL;
	newnode->file = file_flag;
	
	
	
	
	
	
	
} 

void delete_dir(){	//delete a directory
	
} 

void create_file(){} //create a file--not needed

void delete_file(struct nary* root, char* filename){	//delete a file, assuming the file name is unique
	int check = traverse_chk(struct nary* root, char* filename);
	if(check == 1){
		printf("\n********Given filename is of a directory*********");
	}
	else if(check == 0){
		printf("\n********Given filename is not present");
	}
	struct nary *temp;
	temp = found;
	struct nary *current,*previous;
	if(temp->sibling == NULL && temp->children > 1){
		temp = temp->parent->child;
		previous = temp;
		current = temp->sibling;
		while(current->sibling != NULL)
			previous = current;
			current = current->sibling;
	}
} 

int traverse_chk(struct* nary root, char* node){ //traversing the entire n-ary tree to find the given 'parent name' exists or not
	int child; 
	//struct nary* root_cpy = root; 
	if(root == null) 
		return 0;
	else if(!strcmp(root->file_name,char* node)) //if you have found 'parent name', then check whether its a file or a directory
			if(root->file == 0){ // check for directory and if true, return 1
				return 1;
				found = root;
			}
			else
				return 2; // if its a file, return 2
	else
		for( child = 0; child < root->children; child++) // for all the children
		traverse_chk(root->child,node); // use the same function for traversal
}

int main(){
	
	struct nary root;
	root->parent = NULL;
	root->child = NULL;
	
	do{
		printf("Press 1 to create a directory");
		printf("Press 2 to delete a directory");
		printf("Press 3 to create a file");
		printf("Press 4 to delete a file");
			
			switch(choice)
			{
				case 1:	create_dir();
				case 2: delete_dir();
				case 3: create_file();
				case 4: delete_file();
			
			}
	}
	
}