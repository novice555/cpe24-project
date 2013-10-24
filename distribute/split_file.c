void split_file(FileSource Parent, int *ParentCount, FileSource Child, int *ChildCount, void (*f)(FileSource, int*, FileSource, int*))
{
    (*f)(Parent, ParentCount, Child, ChildCount);    
}
