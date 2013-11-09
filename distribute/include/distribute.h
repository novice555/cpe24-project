/*
#define MAX_PATH 2560   
#define MAX_FILENAME 256
#define MAX_NUM_FILE 100000
#define MAX_CHILD 100
*/
enum {
    MAX_PATH = 2560,
    MAX_FILENAME = 256,
    MAX_NUM_FILE = 100000,
    MAX_CHILD = 100
};

typedef struct {
    char src[MAX_PATH];
    char dst_path[MAX_PATH];
    char filename[MAX_FILENAME];
    long size;
} FileSource;
//typedef FileSourceDesc *FileSource;
typedef struct {
    int count;
    long sum_size;
} FileSourceProperties;
//typedef FileSourcePropertiesDesc *FileSourceProperties;

//function split file
extern void split_file_mode_a(FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount, int ChildNum);


//announce global function
FileSourceProperties init_filesourceproperties();
void list_file(char *absolute_path, char *relative_path, FileSource *Parent, FileSourceProperties *ParentCount);
void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild);
