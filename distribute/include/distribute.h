enum {
    MAX_PATH = 1024,
    MAX_STRING = 1024,
    MAX_FILENAME = 256,
    MAX_NUM_FILE = 300000,
    MAX_CHILD = 100
};

typedef struct {
    char *src_path;
    char *filename;
    long long size;
} FileSource;
//typedef FileSourceDesc *FileSource;
typedef FileSource *FileSrc1D;
typedef FileSource **FileSrc2D;
typedef struct {
    int count;
    long long sum_size;
} FileSourceProperties;
typedef FileSourceProperties FileDesc;
typedef FileSourceProperties *FileDesc1D;
//typedef FileSourcePropertiesDesc *FileSourceProperties;

typedef struct {
    FileSource *in;
    FileSourceProperties *in_count;
    FileSource **out;
    FileSourceProperties *out_count;
    FileSource *outsame;
    FileSourceProperties *outsame_count;
} CompactSource;
//typedef CompactSourceDesc *CompactSource;

//function split file
//extern void split_file_mode_a(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount);

//extern void split_file_mode_b(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount);

//announce global function
void list_file(char *absolute_path, char *relative_path, FileSource *Parent, FileSourceProperties *ParentCount);
void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild, char *source_path);
void check_nfs_child(int MaxChild);
//int rsync_copy(char *src_list, char *src, char *dst);
void rsync_copy(char cmd[][MAX_STRING], int n);
//void distribute(char *path, int n_child, int n_same, void (*split_file)(int, int, FileSource*, FileSourceProperties*, FileSource**, FileSourceProperties*, FileSource*, FileSourceProperties*));

char* strbuff(char *text, int len);

