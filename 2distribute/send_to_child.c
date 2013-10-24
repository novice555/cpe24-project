void distri (int n,char * sou)
{
    int c[n];// number of file for each child
    int m=0;
    while(m<n){c[m]=0; m++;}
    int a[NUMBEROFFILE][n];//size of files for each child
    int s=0;
    while(s<t)
    {
      int i,j,min,vmin;
      vmin=0;
      min=0;
      for(j=0;j<t;j++)
	{
	  vmin=vmin+a[j][min];
	}
      for(i=1;i<n;i++)
	{
	  int tmp=0;
	  for(j=0;j<t;j++)
           {
             tmp=tmp+a[j][i];
           }
	  if(tmp<vmin)
	   {
	     vmin=tmp;
             min=i;
	   }
	}
     // printf("\n%d %d\n",min,c[min]);
      a[c[min]][min] = order[s];
      c[min]=c[min]+1;
      s++;
    }
    int u=0;
    while(u<n)
    {
        int i;
        for( i=0 ; i<c[u] ; i++)
        {
          printf("%d\n",a[i][u]);

        }
        printf("\n\n");
        u++;
    }
   // begin to move file
    mkdirr(n,sou);
 
    DIR *dir;
    struct dirent *ent;
    struct stat st_buf;
    char nextfile[CHUNK];
    int dirlen = strlen(sou);

    dir = opendir(sou);
    while((ent = readdir(dir))!=NULL)
    {
        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > CHUNK)
        {
            fprintf(stderr,"File name too large: %s/%s", sou, ent->d_name);
            return;
        }
        strcpy(nextfile, sou);
        strcat(nextfile, "/");
        strcat(nextfile, ent->d_name);
        stat(nextfile, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
           // read1(nextfile);
	        printf("\nError : Not expect directory in this %s directory.\n",sou);
        else
	    {
    		int si = read_file1(nextfile);
    		//printf("\nsize : %d\n",si);
    		int ii, jj;
    		for(ii=0 ; ii<n ; ii++)
    		{
    			for(jj=0 ; jj<c[ii] ; jj++)
    			{
    				if(si==a[jj][ii])
    				{
    					a[jj][ii]=0;
    					char w[4000] ;
    					strcpy(w,"mv ");
    					strcat(w,nextfile);
    					strcat(w," ");
    
    					char ret[3000];
     	        		char buf[5];
       			     	sprintf(buf,"%d",ii+1);
                  		strcpy(ret,sou);
                        strcat(ret,"/c");
                  	  	strcat(ret,buf);
                    	strcat(ret,"/");
    					strcat(w,ret);
    					//printf("\n\n%s\n\n",w);
    					system(w);
    					ii=n;
    					jj=c[ii];
    				}
    			}
    		}
    	}
    }
    closedir(dir);
    int child  ; 
    for(child+1 ; child <= n ;child++)
    {
	char buf[5];
	char des[50];
	char ret[3000];
	sprintf(buf,"%d",child);
	strcpy(des,"/koppae00/child/0");
	strcat(des,buf);
	strcpy(ret,sou);
	strcat(ret,"/c");
	strcat(ret,buf);
	strcat(ret,"/");
	copy(ret,des);
    }
 
}
void mkdirr (int n,char *sou)
{
	int i=0;
	while(i<n)
	{
		char w[4000] ;
		strcpy(w,"mkdir ");
		char ret[3000];
		char buf[5];
	        sprintf(buf,"%d",i+1);
       		strcpy(ret,sou);
       		strcat(ret,"/c");
        	strcat(ret,buf);
        	strcat(ret,"/");

		strcat(w,ret);
		printf("\n\n%s\n\n",w);
		system(w);
		i++;
	}
}
