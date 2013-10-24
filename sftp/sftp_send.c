#include<libssh/libssh.h> 
#include<libssh/sftp.h> 
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

char *find_filename(char *filename, char *result)
{
    int len = strlen(filename);
    int i;
    int counter = 0;
    for (i = len - 1; i >= 0; i--)
    {
        if(filename[i] == '/')
            break;
        counter++;
    }
    strcpy(result, filename + (len - counter));
    return result;
}

int sftp_send(ssh_session session, sftp_session sftp, char *destination)
{
    int access_type = O_WRONLY | O_CREAT | O_TRUNC;
    sftp_file file;
    int length = 4096;
    char buf[length];
    int rc, nwritten;
    unsigned int size;

    FILE* source = fopen("1.tar.gz","rb");
    if(source == NULL)
    {
        return SSH_ERROR;
    }

    file = sftp_open(sftp, "1.tar.gz", access_type, S_IRWXU);
    if(file == NULL)
    {
        fprintf(stderr, "Can't open file for writing: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    while(size = fread(buf, 1, length, source))
    {
        printf("%d\n",size);
        nwritten = sftp_write(file, buf, size);
        if(nwritten != size)
        {
            fprintf(stderr, "Can't write data to file: %s\n", ssh_get_error(session));
            sftp_close(file);
            return SSH_ERROR;
        }
    }

    rc = sftp_close(file);
    if(rc != SSH_OK)
    {
        fprintf(stderr, "Can't close the written file: %s\n", ssh_get_error(session));
        return rc;
    }

    return SSH_OK;
}

int main()
{
    char aabbcc[200];
    char *str = "/root/project";
    printf("%s\n", find_filename(str, aabbcc));
}


