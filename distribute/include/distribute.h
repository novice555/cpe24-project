enum {
    MAX_PATH = 2560,
    MAX_FILENAME = 256,
    MAX_NUM_FILE = 100000,
    MAX_CHILD = 100
};

typedef struct {
    char *src_path;
    char *filename;
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

extern void split_file_mode_b(FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount, int ChildNum);

//announce global function
void list_file(char *absolute_path, char *relative_path, FileSource *Parent, FileSourceProperties *ParentCount);
void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild, char *source_path);
void check_nfs_child(int MaxChild);
int rsync_copy(char *src_list, char *src, char *dst);
void distribute(char *path, int n_child, void (*split_file)(FileSource*, FileSourceProperties*, FileSource**, FileSourceProperties*, int));
char* strbuff(char *text);

