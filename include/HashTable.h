struct node{
	struct file_descriptor f_desc;
	char fname[10];
	struct node* next;
	struct node * previous;
};

int findIndex(char fname[]);
void  insertFile(struct file_descriptor f_desc);
void displayHash();

