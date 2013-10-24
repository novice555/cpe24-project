#define MAX_PATH 2560   
#define MAX_NUM_FILE 100000
#define MAX_CHILD 100
typedef struct {
    char path[MAX_PATH];
    long size;
} FileSourceDesc;
typedef FileSourceDesc *FileSource;
extern FileSource SourceFile[];
extern int FileCount;
