#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
//both the child and parent processes share the same file using file pointer
//both the child and parent has the same offset, that is both child and parent can alter the offset
int main(){
	FILE *fp = fopen("filename.txt","r");
	pid_t id = fork();

	if(id != 0) 
	{
		char str[100] = "parent";
		//fprintf(fp,"%s\n",str);
		char str1[100];
		fscanf(fp,"%s",str1);
		printf("from the parent process with id : %d\n",getpid());
		printf("%s\n",str1);
	}
	else 
	{
		char str[100] = "child\n";
		//fprintf(fp,"%s\n",str);
		char str1[100];
		fscanf(fp,"%s",str1);
		printf("from the child process with id : %d\n",getpid());
		printf("%s\n",str1);
	}
}