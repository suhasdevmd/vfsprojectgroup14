enum type {directory=0,regular,socket}; // written for testing

struct file_descriptor{
char *file_name;
char *file_path;
enum type file_type;
long int file_size;
};
