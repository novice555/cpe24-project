enum {
    MAX_PATH = 1024,
    MAX_COMMAND = 1024,
    MAX_FILENAME = 256,
    MAX_NUM_FILE = 300000,
    MAX_CHILD = 100
};

struct FileSource {
    char *src_path;
    char *filename;
    long long size;
    struct FileSource *next;
    struct FileSource *back;
};
//typedef struct FileSource FileSrc;
typedef struct FileSource *FileSrc;
//typedef FileSource *FileSrc1D;
//typedef FileSource **FileSrc2D;
struct FileSourceProperties {
    int count;
    long long sum_size;
    FileSrc head;
    FileSrc tail;
};
//typedef FileSourceProperties FileDesc;
//typedef FileSourceProperties *FileDesc1D;
typedef struct FileSourceProperties *FileDesc;

struct CompactSource {
    FileDesc in;
    FileDesc *out;
    FileDesc same;
    FileDesc queue;
};
typedef struct CompactSource CompactSrc;

struct stringtype {
    char *str;
    struct stringtype *next;
};
typedef struct stringtype *strtype;

//typedef CompactSourceDesc *CompactSource;

//function split file
extern void split_file_mode_c(int ChildNum, int percent, void *src);
//extern void split_file_mode_a(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount);

//extern void split_file_mode_b(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount);

//announce global function
/*void list_file(char *absolute_path, char *relative_path, FileSource *Parent, FileSourceProperties *ParentCount);
void copy_to_child(FileSource **Child, FileSourceProperties *ChildCount, int MaxChild, char *source_path);
void check_nfs_child(int MaxChild);
//int rsync_copy(char *src_list, char *src, char *dst);
void rsync_copy(char cmd[][MAX_STRING], int n);
//void distribute(char *path, int n_child, int n_same, void (*split_file)(int, int, FileSource*, FileSourceProperties*, FileSource**, FileSourceProperties*, FileSource*, FileSourceProperties*));
*/
char* strbuff(char *text, int len);
void enqueue(FileDesc desc, struct FileSource src);
struct FileSource dequeue(FileDesc desc);


