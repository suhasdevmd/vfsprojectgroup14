//enum {directory=0,regular,socket} type; // enumeration for files

struct file_descriptor{
char file_name[100];
char file_path[100];
char file_type[10];
long int file_size;
};
