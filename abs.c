#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

void searchUtil(char path[1000],char name[1000],int flag);
void search(char name[1000],int flag);

void psearchUtil(char path[1000],char name[1000],int flag);
void psearch(char name[1000],int flag);



int main(){
	int flag;
	char name[1000];
	printf("What do you want to search for?\n");
	printf("\t1.File\n");
	printf("\t2.Directory\n");
	printf("\t3.Both\n");
	printf("Enter 1, 2 or 3: ");

	scanf("%d",&flag);
	if(flag==1){
		printf("Enter the name of file: ");
		scanf("%s",name);
	}
	else if(flag==2){
		printf("Enter the name of directory: ");
		scanf("%s",name);
	}
	else if(flag==3){
		printf("Enter the name: ");
		scanf("%s",name);
	}

	printf("\n\nSearching for exact matches...\n");
	printf("TYPE\t\t\t\tLOCATION");
	search(name,flag);

	printf("\n\nSearching for similar names...\n");
	printf("TYPE\t\t\t\tLOCATION");
	psearch(name,flag);
    printf("\n");
	return 0;
}

void searchUtil(char path[1000],char name[1000],int flag){
	DIR *dp;
	struct dirent *ep;
	dp = opendir(path);

	if(dp != NULL){
		while(ep = readdir(dp)){
            if(strcmp(ep->d_name,".")==0 || strcmp(ep->d_name,"..")==0)
                continue;

            char newpath[10000]="\0";
            if(ep->d_type == 8 && flag == 1 && strcmp(ep->d_name,name)==0)
                printf("\nFile:\t\t\t\t%s%s",path,ep->d_name);
            else if(ep->d_type == 4 && flag == 2 && strcmp(ep->d_name,name)==0)
                printf("\nFolder:\t\t\t\t%s%s",path,ep->d_name);
            else if(flag == 3 && strcmp(ep->d_name,name)==0)
                if(ep->d_type == 4)
                    printf("\nFolder\t\t\t\t%s%s",path,ep->d_name);
                else
                    printf("\nFile:\t\t\t\t%s%s",path,ep->d_name);
			strcat(newpath,path);
			strcat(newpath,ep->d_name);
			strcat(newpath,"/");

			if(ep->d_type == 4)
                searchUtil(newpath,name,flag);
        }
	}
}

void search(char name[1000],int flag){
	searchUtil("./",name,flag);
}

void psearchUtil(char path[1000],char name[1000],int flag){
	DIR *dp;
	struct dirent *ep;
	dp = opendir(path);

	if(dp != NULL){
		while(ep = readdir(dp)){
            if(strcmp(ep->d_name,".")==0 || strcmp(ep->d_name,"..")==0)
                continue;
            //printf("\nPath\t\t\t\t%s %s",path,ep->d_name);
            char newpath[10000]="\0";
            if(ep->d_type == 8 && flag == 1 && strstr(ep->d_name,name))
                printf("\nFile:\t\t\t\t%s%s",path,ep->d_name);
            else if(ep->d_type == 4 && flag == 2 && strstr(ep->d_name,name))
                printf("\nFolder:\t\t\t\t%s%s",path,ep->d_name);
            else if(flag == 3 && strstr(ep->d_name,name))
                if(ep->d_type == 4)
                    printf("\nFolder\t\t\t\t%s%s",path,ep->d_name);
                else
                    printf("\nFile:\t\t\t\t%s%s",path,ep->d_name);
			strcat(newpath,path);
			strcat(newpath,ep->d_name);
			strcat(newpath,"/");

			if(ep->d_type == 4)
                psearchUtil(newpath,name,flag);
        }
	}
}

void psearch(char name[1000],int flag){
	psearchUtil("./",name,flag);
}
