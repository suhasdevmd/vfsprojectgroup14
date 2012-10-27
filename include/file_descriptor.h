//enum {directory=0,regular,socket} type; // enumeration for files
#define MAX_FILE_DESC 1024

struct file_descriptor{
char file_name[100];
char file_path[100];
char file_type[10];
long int file_size;
long int location_block_number;
};

struct file_descriptor f_desc[1024];
