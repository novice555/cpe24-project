#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<libssh/libssh.h>
#include<libssh/sftp.h>
static char host[256];
static char username[256];
static char password[256];

void input(int num_argc, char *str_argv)
{
    char *pass, *ch;
    
    if(num_argc != 3)
    {
        fprintf(stderr,"usage: sftp <user@host> <file>\n");
        exit(-1);
    }
    ch = strchr(str_argv, 64);
    if(ch == NULL)
    {
        fprintf(stderr,"username and host is not valid\n\nusage: sftp <user@host> <file>\n\n");
        exit(-1);
    }
    
    strcpy(host, ch + 1);
    strncpy(username, str_argv, ch - str_argv);

    pass = getpass("Password: ");
    strcpy(password, pass);
}


int main(int argc, char *argv[])
{
    ssh_session upload_file;
    sftp_session upload_sftp;
    printf("\n");
    input(argc, argv[1]);
    printf("%s %s %s\n", host, username, password);
    ssh_open_session(upload_file, host, username, password);
    sftp_open_session(upload_file, upload_sftp);
    sftp_open_session(upload_sftp);
    ssh_close_session(upload_file);
    printf("\n\nEND :)\n");
    return 0;
}
