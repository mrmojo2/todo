#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seperator(char *input,char output[100][100]){
	int i=0,c=0;
	for(int row=0;row<100;row++){
		for(int col=0;col<100;col++){
			if(input[i]==' '){
				output[row][col]='\0';
				i++;c++;
				break;
			}else if(input[i]=='\0'||input[i]=='\n'){
				output[row][col]='\0';
				return c+1;
			}else{
				output[row][col]=input[i++];
			}

		}
	}
}


void help(){
	printf("\nthere are the list of commands:\n");
	printf("\t\"add [your task] [time]\"    : To add a task\n");
	printf("\t\"done [task index]\"         : To remove a task\n");
	printf("\t\"overdue\"                   : To ckeck over due tasks\n");
	printf("\t\"list\"                      : To ckeck over due tasks\n");
	
}

void add(FILE *file,char c[100][100],int a){
	if(a<3){ printf("\nIncomplete arguments");return;}
	

}

int main(){
	char inp[1024],inparr[100][100];
	int c;
	FILE *fd=fopen("./tasks","r");

	printf("\n\t\t\t\t\tWelcome to todo app\n\tThis application helps you to remember and plan all the stuffs you need to do make your day productive\n\nEnter \"help\" for help\n\n");

	while(1){
		printf(">");
		fgets(inp,sizeof(inp),stdin);
		c=seperator(inp,inparr);	
		
		if(strcmp(inparr[0],"help")==0){
			help();
		}else if(strcmp(inparr[0],"add")==0){
			add(fd,inparr,c)	
		}
	}
}
