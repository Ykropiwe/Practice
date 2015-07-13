#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

int Mx,My;
int Mass[500][500];
char ch[500][500];
void recog();
void Recognize();
void print();
FILE *file;

int main(int argc, char *argv[]) {
	file=fopen(argv[1], "r");
	if (file==NULL) {
	printf("Введите в аргументах путь к изображению\n");
	exit(1);
	}
Recognize();
recog();
print();
//printf("%d\n", Mass[4][2]);
}

void recog(){
int x,d,i,o;
d=1;
char *buf;
buf=strtok(ch[1], " \n");
while (buf!=NULL){
	//printf("%s\n", buf);
	if (d==1){Mx=atoi(buf); d++;}
	else {My=atoi(buf); d=1; i++;}
	buf=strtok(NULL, " \n");
	}
buf=strtok(ch[2], " \n");
while (buf!=NULL){
	//printf("%s\n", buf);
	if (d==1){x=atoi(buf); d++;}
	else {o=atoi(buf); Mass[o][x]=1; d=1; i++;}
	buf=strtok(NULL, " \n");
	}
}
void Recognize() {
int h;
h=1;
while (fgets(ch[h], 500, file)) {
	h++;
	}
}
void print() {
int i,j;
for(i=0;i<My;i++) {
	for(j=0;j<Mx;j++) {
		if (Mass[i][j]==1) printf("#");
		else printf(".");
		}
	printf("\n");
	}
}
