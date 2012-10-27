struct freelist{
long int block_number;
int isFree;
struct freelist *next;
};

struct freelist free_list[1024];
