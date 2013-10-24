#include<libssh/libssh.h> 
#include<libssh/sftp.h> 
#include<stdlib.h>
#include<stdio.h>


int sftp_open_session(ssh_session session, sftp_session sftp)
{
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

    return SSH_OK;
}

int sftp_close_session(sftp_session my_sftp)
{
    sftp_free(my_sftp);
    return SSH_OK;
}

