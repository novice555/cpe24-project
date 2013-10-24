#include<libssh/libssh.h> 
#include<libssh/sftp.h> 
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

int verify_knownhost(ssh_session session)
{
    int state, hlen;
    unsigned char *hash = NULL;
    char *hexa;
    char buf[10];

    state = ssh_is_server_known(session);
    hlen = ssh_get_pubkey_hash(session, &hash);
    if(hlen < 0)
        return -1;
    switch(state)
    {
        case SSH_SERVER_KNOWN_OK:
            break;
        case SSH_SERVER_KNOWN_CHANGED:
            fprintf(stderr, "Host key for server changed: it is now:\n");
            ssh_print_hexa("Public key hash", hash, hlen);
            fprintf(stderr, "For security reasons, connection will be stopped\n");
            free(hash);
            return -1;
        case SSH_SERVER_FOUND_OTHER:
            fprintf(stderr, "The host key for this server was not found but an other type of key exists.\n");
            fprintf(stderr, "An attacker might change the default server key to confuse your client into thinking the key does not exist\n");
            free(hash);
        case SSH_SERVER_FILE_NOT_FOUND:
            fprintf(stderr, "Could not find known host file.\n");
            fprintf(stderr, "If you accept the host key here, the file will be automatically created.\n");
        
        case SSH_SERVER_NOT_KNOWN:
            hexa = ssh_get_hexa(hash,hlen);
            fprintf(stderr, "The server is unknown. Do you trust the host key?\n");
            fprintf(stderr, "Public key hash: %s\n", hexa);
            free(hexa);
            
            if(fgets(buf, sizeof(buf), stdin) == NULL)
            {
                free(hash);
                return -1;
            }
            buf[3] = '\0';
            if(strcmp(buf, "yes") != 0)
            {
                free(hash);
                return -1;
            }
            if(ssh_write_knownhost(session) < 0)
            {
                fprintf(stderr, "Error %s\n", strerror(errno));
                free(hash);
                return -1;
            }
            break;


        case SSH_SERVER_ERROR:
            fprintf(stderr, "Error %s", ssh_get_error(session));
            free(hash);
            return -1;
    }

    free(hash);
    return 0;
}


int sftp_testwrite(ssh_session session, sftp_session sftp)
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
    rc = sftp_mkdir(sftp, "3/4/5/6", S_IRWXU);
    if(rc != SSH_OK)
    {
        if(sftp_get_error(sftp) != SSH_FX_FILE_ALREADY_EXISTS)
        {
            fprintf(stderr, "Can,t create directory: %s", ssh_get_error(session));
        
        return rc;
        }
    }
    file = sftp_open(sftp, "1/2/3/1.tar.gz", access_type, S_IRWXU);
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

int sftp_opensession(ssh_session session)
{
    sftp_session sftp;
    int rc;

    sftp = sftp_new(session);
    if(sftp == NULL)
    {
        fprintf(stderr, "Error allocating SFTP session: %s\n", ssh_get_error(session));
        return SSH_ERROR;
    }

    rc = sftp_init(sftp);
    if(rc != SSH_OK)
    {
        fprintf(stderr, "Error initializing SFTP session: %d\n", sftp_get_error(sftp));
        sftp_free(sftp);
        return rc;
    }

    sftp_testwrite(session, sftp);

    sftp_free(sftp);
    return SSH_OK;
}


int main()
{
    ssh_session my_ssh_session;
    int verbosity = SSH_LOG_PROTOCOL;
    char *password;
    int port = 22;
    int rc;

    my_ssh_session = ssh_new();
    if(my_ssh_session == NULL)
        exit(-1);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "localhost");
    //ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, "root");

    rc = ssh_connect(my_ssh_session);
    if(rc != SSH_OK)
    {
        fprintf(stderr,"Error: %s\n", ssh_get_error(my_ssh_session));
        ssh_free(my_ssh_session);
        exit(-1);
    }
    
    if(verify_knownhost(my_ssh_session) < 0)
    {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }
    password = getpass("Password: ");
    rc = ssh_userauth_password(my_ssh_session, NULL, password);
    if(rc != SSH_AUTH_SUCCESS)
    {
        fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

 //   scp_write(my_ssh_session);
    sftp_opensession(my_ssh_session);
    ssh_disconnect(my_ssh_session);               
    ssh_free(my_ssh_session);
}

