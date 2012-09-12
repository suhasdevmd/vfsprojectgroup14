struct mainheader{
char file_sys_label[100];
int used_file_desc;
int max_file_desc;
struct file_descriptor file_desc;
struct freelist free_list;
};
