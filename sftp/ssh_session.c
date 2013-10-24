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

void ssh_open_session(session my_ssh_session, char *host, char *user, char *pass)
{
    //int verbosity = SSH_LOG_PROTOCOL;
    int port = 22;
    int rc;

    my_ssh_session = ssh_new();
    if(my_ssh_session == NULL)
        exit(-1);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host);
    //ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, user);

    rc = ssh_connect(my_ssh_session);
    if(rc != SSH_OK)
    {
        fprintf(stderr,"Error: %s\n", ssh_get_error(my_ssh_session));
        ssh_free(my_ssh_session);
        exit(-1);
    }
    
    //Checking Knownhost
    if(verify_knownhost(my_ssh_session) < 0)
    {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    rc = ssh_userauth_password(my_ssh_session, NULL, pass);
    if(rc != SSH_AUTH_SUCCESS)
    {
        fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

}

void ssh_close_session(session my_ssh_session)
{
    ssh_disconnect(my_ssh_session);               
    ssh_free(my_ssh_session);
}

