enum type {directory=0,regular,socket}; // enumeration for files

struct file_descriptor{
char file_name[100];
char file_path[100];
enum type file_type;
long int file_size;
};
