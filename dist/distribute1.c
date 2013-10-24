#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#define CHUNK 1024
#define NUMBEROFFILE 100000
/* Read the contents of a file into a buffer.  Return the size of the file 
 * and set buf to point to a buffer allocated with malloc that contains  
 * the file contents.
 */
void read1(char *);
int read_file1(char *);
int order[NUMBEROFFILE] ;
int distribute(char *);
void distri(int,char *);
void mkdirr(int,char *);
/*void namedir(int,char *);
static char * ret[2*CHUNK];*/
int t=0;
int read_file1(char *filename) 
{
   long length=0;
   FILE *fp;
   fp=fopen(filename,"rb");

   if(fp==NULL) {
      printf("\nfile not found!\n");
   }
   else {
      fseek(fp,0L,SEEK_END);
      length=ftell(fp);
      fclose(fp);
   }
   return length;
}
void read1(char *directory)
{
    DIR *dir;
    struct dirent *ent;
    struct stat st_buf;
    char nextfile[CHUNK];
    int dirlen = strlen(directory);

    dir = opendir(directory);
    while((ent = readdir(dir))!=NULL)
    {
        if(strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0)
        {
            continue;
        }
        if((dirlen + strlen(ent->d_name)) > CHUNK)
        {
            fprintf(stderr,"File name too large: %s/%s", directory, ent->d_name);
            return;
        }
        strcpy(nextfile, directory);
        strcat(nextfile, "/");
        strcat(nextfile, ent->d_name);
        stat(nextfile, &st_buf);
        if(S_ISDIR(st_buf.st_mode))
            read1(nextfile);
        else
        {   // printf("%s   ", nextfile);
	   // printf("size %d\n", read_file1(nextfile));
	   order[t] = read_file1(nextfile);  
           t++;
	}
    }
    closedir(dir);
}

char cp_command[] = "cp -vfR ";
int copy(char *src, char *dest)
{
    int sys;
    char strbuf[2048] = "";
    if(system(NULL)==0)
        exit(EXIT_FAILURE);
    strcat(strbuf, cp_command);
    strcat(strbuf, src);
    strcat(strbuf, " ");
    strcat(strbuf, dest);
    sys = system(strbuf);
    printf("%d\n", sys);
    return 0;
}

static __inline__ int sort(int * d){

    char j, i, imax;
    int tmp;
    for (j = 0 ; j < t-1 ; j++){
        imax = j;
        for (i = j + 1; i < t ; i++){
            if (d[i] > d[imax]){
                imax = i;
            }
        }
        tmp = d[j];
        d[j] = d[imax];
        d[imax] = tmp;
    }
}
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
            read1(nextfile);
        else
	{
		int si = read_file1(nextfile);
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
					
					char des[50];
					strcpy(des,"/koppae00/child/0");
					strcat(des,buf); 
					
					system(w);
					copy(ret, des);
					ii=n;
					jj=c[ii];
				}
			}
		}
	}
    }
    closedir(dir);
 
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
/*void namedir(int n ,char *sou)
{
	int i;
	for(i=0 ; i<CHUNK*2 ; i++)
	{
		ret[i] = NULL;
	}
	char buf[10];
	sprintf(buf,"%d",n);
	strcat(ret,sou);
	strcat(ret,"c");
	strcat(ret,buf);
	strcat(ret,"/");
}*/
int distribute(char *a)
{  
    printf("%s\n",a);
    int n=0;
    char *path = realpath(a, NULL);
    printf("Number of child : ");
    scanf("%d",&n);
    printf("\n");
    printf("%s\n\n", path);
    read1(path);
    sort(order);
    distri(n,a);
    return n;
}
int main(int argc, char *argv[])
{
   distribute(argv[1]);
}

