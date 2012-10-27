struct dirNode{
struct file_descriptor fileDesc;
struct dirNode *firstChild;
struct dirNode *rightSibling;
};

struct dirNode * getnode();
void naryRoot();
void insertToNarry(struct file_descriptor fd);
void displayNAry(struct dirNode *d);
