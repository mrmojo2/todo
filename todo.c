#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seperator(char *input,char output[100][100],char k){
	int i=0,c=0;
	for(int row=0;row<100;row++){
		for(int col=0;col<100;col++){
			if(input[i]==k){
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
	printf("\t\"list\"                      : To ckeck all tasks\n");
	printf("\t\"exit\"                      : To exit program\n");
}

void add(char c[100][100],char *t,int a){
		
	FILE *file=fopen("tasks.txt","a+");
	if(file==NULL) {
		FILE *file=fopen("tasks.txt","w+");
	}
		
	fseek(file,0L,SEEK_END);
	char nl='\n',space=' ';
	for(int j=1;j<a;j++){
		int size;
		for(size=0;c[j][size]!='\0';size++);
		fwrite(c[j],size,1,file);
		fwrite(&space,1,1,file);
	}
	int tsize;
	for(tsize=0;t[tsize]!='\0';tsize++);
	fwrite(t,tsize,1,file);
	fwrite(&nl,1,1,file);
	
	fclose(file);
}

void list(){
	char readbuff[2048],tasks[100][100];
	int taskno;
	FILE *file=fopen("tasks.txt","r");
	if(file==NULL){
		printf("No task added\n");
		return;
	}
	
	fseek(file,0l,SEEK_END);
	int filesize=ftell(file);
	fseek(file,0l,SEEK_SET);
	
	fread(readbuff,1,filesize,file);
	taskno=seperator(readbuff,tasks,'\n');
	for(int j=0;j<taskno-1;j++){
		printf("\n%d. %s",j+1,tasks[j]);
	}
	printf("\n\n");
	fclose(file);
}

void done(char i[100][100],int a){
	if(a<2){ printf("invalid arguments\n");return;}
	if(atoi(i[1])==0){ printf("invalid index value\n");return;}
	
	int index=atoi(i[1]),l=0;
	char c;
	char line[100];
	FILE *temp=fopen("temp.txt","w+");
	FILE *orig=fopen("tasks.txt","r");
	if(temp==NULL) printf("temp not creatd\n");
	
	while(1){
		if((fgets(line,100,orig))==NULL) break;
		if(l==index-1){
			//do nothing
		}else{
			fputs(line,temp);
		}
		l++;
	}
	
	fclose(orig);
	fclose(temp);
	remove("tasks.txt");
	rename("temp.txt","tasks.txt");
}

int main(){
	char inp[1024],inparr[100][100];
	int c;

	printf("\n\t\t\t\t\t\tWelcome to todo app\n\tThis application helps you to remember and plan all the stuffs you need to do make your day productive\n\nEnter \"help\" for help\n\n");

	while(1){
		printf(">");
		fgets(inp,sizeof(inp),stdin);
		c=seperator(inp,inparr,' ');
		
		if(strcmp(inparr[0],"help")==0){
			help();
		}else if(strcmp(inparr[0],"add")==0){
			char time[20];
			printf("Enter Due Time [hour:minute]:");
			fread(time,1,5,stdin);
			if(strcmp(time,"\n")==0){ continue; };
			add(inparr,time,c);
		}else if(strcmp(inparr[0],"done")==0){
			done(inparr,c);
		}else if(strcmp(inparr[0],"list")==0){
			list();
		}else if(strcmp(inparr[0],"exit")==0){
			exit(1);
		}else if(strcmp(inp,"\n")==0){
		}else{
			printf("invalid command...enter help to see the commands\n");
		}
	}
	
}
