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
extern const char CHILD_PATH[];
extern const char PARENT_PATH[];
extern const char TMP_PATH[];


//function split file
extern void split_file_mode_c(int ChildNum, int percent, void *src);
//extern void split_file_mode_a(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount);

//extern void split_file_mode_b(int ChildNum, int Same, FileSource *Parent, FileSourceProperties *ParentCount, FileSource **Child, FileSourceProperties *ChildCount);

//announce global function


void check_nfs_child(int MaxChild);
void copy_to_child(char *source_path, int ChildNum, int mode, void *src);
void distribute(char *path, int n_child, int n_same, void (*split_file)(int, int, void*));
void list_file(char *absolute_path, char *workpath, void *src);
void enqueue(FileDesc desc, struct FileSource src);
void insert_sort(FileDesc desc, struct FileSource src);
void rsync_copy(char cmd[][MAX_COMMAND], int n);
void string_init();
void string_deinit();
void write_file(int child, void *src);
void write_list(int child, void *src);
char* strbuff(char *text, int len);
struct FileSource dequeue(FileDesc desc);
