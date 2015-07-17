#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int Mx,My,MinX,MinY,MaxX,MaxY;
int Mass[500][500];
int SMass[500][500];
char ch[500][500];
void recog();
void Recognize();
void print();
void check();
void Sprint();
void CentrFind();
void PBMWrite();
void RectangleCreator();
FILE *file;

int main(int argc, char *argv[]) {
	if (argc>3) {
		printf("Слишком много аргументов\n");
		exit(0);
	}
	file=fopen(argv[1], "r");
	if (file==NULL) {
		printf("Введите в аргументах путь к изображению\n");
		exit(1);
	}
	Recognize();
	recog();
	//print();
	//printf("\n");
	check();
	RectangleCreator();
	CentrFind();
	if (argc==3)
	Sprint();
	//printf("\n");
	//printf("%d\n", Mass[4][2]);
	if (argc==2) 
	PBMWrite();
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

void check() {
	int i,j,a;
	for(j=1;j<My;j++) {
		for(i=1;i<Mx;i++) {
			if (Mass[j+1][i-1]==1) a++;
			if (Mass[j+1][i]==1) a++;
			if (Mass[j+1][i+1]==1) a++;
			if (Mass[j][i-1]==1) a++;
			if (Mass[j][i+1]==1) a++;
			if (Mass[j-1][i-1]==1) a++;
			if (Mass[j-1][i]==1) a++;
			if (Mass[j-1][i+1]==1) a++;
			if (a>=2) SMass[j][i] = Mass[j][i];
			if (SMass[j][i]==1) {
				if (i>MaxX) MaxX=i;
				if (j>MaxY) MaxY=j;
				if (MinX==0) MinX=i;
				if (MinY==0) MinY=j;
				}			
			a=0;
		}
	}
}

void CentrFind() {
	int i,j;
	j=(MaxY+MinY)/2;
	i=(MaxX+MinX)/2;
	//printf("\n%d,%d\n",i,j);
	SMass[j][i]=2;
}

void Sprint() {
	int i,j;
	for(i=0;i<My;i++) {
		for(j=0;j<Mx;j++) {
			if (SMass[i][j]==1) printf("#");
			else if (SMass[i][j]==2) printf("*");
			else if (SMass[i][j]==3) printf("!");		
			else printf(".");
		}
		printf("\n");
	}
	printf("\nMx=%d\nMy=%d\n",MaxX-MinX+1,MaxY-MinY+1);
}

void PBMWrite() {
	int i,j;
	printf("P3\n");
	printf("%d %d\n",Mx,My);
	printf("255\n");
	for(i=0;i<My;i++) {
		for(j=0;j<Mx;j++) {
			if (SMass[i][j]==1) printf("0 0 0 ");
			else if (SMass[i][j]==2) printf("255 0 0 ");
			else if (SMass[i][j]==3) printf("0 255 0 ");		
			else printf("255 255 255 ");
		}
		printf("\n");
	}
}

void RectangleCreator() {
	int i;
	for(i=MinX-1;i<=MaxX+1;i++) {
		SMass[MinY-1][i]=3;
		SMass[MaxY+1][i]=3;
	}
	for(i=MinY-1;i<=MaxY+1;i++) {
		SMass[i][MinX-1]=3;
		SMass[i][MaxX+1]=3;
	}
}
