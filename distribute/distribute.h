#define MAX_PATH 2560   
#define MAX_NUM_FILE 100000
#define MAX_CHILD 100
typedef struct {
    char path[MAX_PATH];
    long size;
} FileSourceDesc;
typedef FileSourceDesc *FileSource;
typedef struct {
    int count;
    long sum_size;
} FileSourcePropertiesDesc;
typedef FileSourcePropertiesDesc *FileSourceProperties;
//extern FileSource SourceFile[];
//extern int FileCount;
extern void split_file_mode_a(FileSource *Parent, FileSourceProperties ParentCount, FileSource **Child, FileSourceProperties *ChildCount, int ChildNum);

