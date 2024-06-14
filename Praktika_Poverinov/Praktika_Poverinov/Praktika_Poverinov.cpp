#include "stdafx.h"  
#include <stdio.h>  
#include <stdlib.h>  
#include <conio.h>  
#include <string.h>  
#include <malloc.h>  
#include <clocale>  
#include <windows.h>  
  
using namespace std;  
using namespace System;  
using namespace System::IO;  
  
#define ENTER 13  
#define ESC 27  
#define UP 72  
#define DOWN 80  
#define HOME 71 
#define END 79
  
int menu(int);  
  
  
 
struct z {  
 char enemy[20];  
 char place[20];  
 int liv_score;  
 int en_score;  
 char tour[25];  
 char data[11];  
 };  
struct sp { 
 char team[20]; 
 int en_score; 
 struct sp* sled;
 struct sp* pred;
} ; 
int menu(int);  
void maxim(struct z*, int);  
void goals(struct z*, int);  
void vstavka(struct z*,char*, int, struct sp**); 
 void diagram(struct z*, int, struct sp**); 
 void alfalist(struct z*, int, struct sp**); 
 void same(struct z*, int);
  
int main(array<System::String ^> ^args)  
{  
 char dan[6][55]={  
  "Против какой команды Ливерпуль забил максимум голов?  ",  
  "Сколько Ливерпуль забил против <Введите команду>?     ",  
  "Алфавитный список противников и забитых ими мячей     ",  
  "Диаграмма: процент забитых голов                      ",  
  "Две ненулевые ничьи с одинаковым счетом               ",    
  "Выход                                                 "  
  };  
 char BlankLine[ ]="                                                        ";
 int NM;
 int i,n;  
 FILE *in;  
 struct z *match;  
 setlocale(LC_CTYPE,"Russian");  
 Console::CursorVisible::set(false);  
 Console::BufferHeight=Console::WindowHeight;  
 Console::BufferWidth=Console::WindowWidth;  
	if((in=fopen("table_data","r"))==NULL)  
		{  
		printf("\nФайл table_data.dat  не открыт !");  
		getch(); exit(1);  
		}  
 fscanf(in,"%d",&NM);  
match=(struct z*)malloc(NM*sizeof(struct z));  
  
	for(i=0;i<NM;i++)  
		fscanf(in,"%s%s%d%d%s%s",match[i].enemy,  
		match[i].place, &match[i].liv_score, &match[i].en_score, match[i].tour,  
		match[i].data);  
  
	for(i=0;i<NM;i++)  
		printf("\n%-20s %-7s %-5d %-5d %-15s %s",  
		match[i].enemy,  
		match[i].place, match[i].liv_score, match[i].en_score, match[i].tour,  
		match[i].data);  
getch();  
  
    while(1)  
  {  
  Console::ForegroundColor=ConsoleColor::White;  
  Console::BackgroundColor=ConsoleColor::Black;  
  Console::Clear();  
  
  Console::ForegroundColor=ConsoleColor::Red;  
  Console::BackgroundColor=ConsoleColor::White;  
  Console::CursorLeft=10;  
  Console::CursorTop=4;  
  printf(BlankLine);  
  for(i=0;i<6;i++)  
  {  
  Console::CursorLeft=10;  
  Console::CursorTop=i+5;  
  printf(" %s ",dan[i]);  
  }  
  Console::CursorLeft=10;  
  Console::CursorTop=11;  
  printf(BlankLine);  
  n = menu(6);  
  
  struct sp* spisok = 0;
  switch(n) {  
    case 1: maxim(match, NM);break;  
    case 2: goals(match, NM); break;  
    case 3: alfalist(match, NM, &spisok); break;  
    case 4: diagram(match, NM, &spisok); break;  
    case 5: same(match, NM); break;  
    case 6: ; exit(0);   
    }  
  }  
  return 0;  
}  
int menu(int n)  
{  
  char dan[6][55]={  
  "Против какой команды Ливерпуль забил максимум голов?  ",  
  "Сколько Ливерпуль забил против <Введите команду>?     ",  
  "Алфавитный список противников и забитых ими мячей     ",  
  "Диаграмма: процент забитых голов                      ",  
  "Две ненулевые ничьи с одинаковым счетом               ",    
  "Выход                                                 "  
  };  
 char BlankLine[ ]="                                                        ";
int y1=0,y2=n-1;  
char c=1;  
while (c!=ESC)  
{   
  switch(c) {  
   case DOWN: y2=y1; y1++; break;  
   case UP: y2=y1; y1--; break;  
   case ENTER: return y1+1;  
   case HOME: y2 = y1; y1 = 0; break;
   case END: y2 = y1; y1 = n - 1; break;
   }  
  if(y1>n-1){y2=n-1;y1=0;}  
  if(y1<0) {y2=0;y1=n-1;}  
  Console::ForegroundColor=ConsoleColor::Cyan;  
  Console::BackgroundColor=ConsoleColor::Red;  
  Console::CursorLeft=11;  
  Console::CursorTop=y1+5;  
  printf("%s",dan[y1]);  
  Console::ForegroundColor=ConsoleColor::Red;  
  Console::BackgroundColor=ConsoleColor::White;  
  Console::CursorLeft=11;  
  Console::CursorTop=y2+5;  
  printf("%s",dan[y2]);  
  c=getch();  
  }   
exit(0);  
}  

void maxim(struct z* match, int NM)  
{  
 int i=0; struct z best;  
 strcpy(best.enemy, match[0].enemy);  
 best.liv_score=match[0].liv_score;  
 for(i=1;i<NM;i++)  
  if (match[i].liv_score>best.liv_score)  
  {  
   strcpy(best.enemy,match[i].enemy);  
   best.liv_score=match[i].liv_score;  
  }  
Console::ForegroundColor=ConsoleColor::White;  
Console::BackgroundColor=ConsoleColor::Red;  
Console::CursorLeft=10;  
Console::CursorTop=17;  
printf("Максимальное кол-во голов %d   ",best.liv_score);  
Console::CursorLeft=10;  
Console::CursorTop=18;  
printf("против команды %s",best.enemy);  
getch();  
}  
void vstavka(struct z* match,char* team, int NM, struct sp**spisok) 
{ 
	int i; 
	struct sp *nov,*nt,*z=0; 
		for(nt=*spisok; nt!=0 && strcmp(nt->team,team)<0; z=nt, nt=nt->sled); 
			if(nt && strcmp(nt->team,team)==0) return; 
				nov=(struct sp *) malloc(sizeof(struct sp)); 
				strcpy(nov->team,team); 
				nov->sled=nt;
				nov->pred=z;
				nov->en_score=0; 
		for(i=0;i<NM;i++) 
			if(strcmp(match[i].enemy,team)==0) 
				nov->en_score+=match[i].en_score; 
				if(!z) *spisok=nov; 
				else z->sled=nov; 
			if(nt) nt->pred=nov;
			  nov->sled = nt;
	return; 
} 
void goals(struct z* match, int NM)  
{  
 int i = 0, g;   
 char team[20];  
 Console::CursorLeft=10;  
 Console::CursorTop=17;
 Console::ForegroundColor=ConsoleColor::White;  
Console::BackgroundColor=ConsoleColor::Red; 
 Console::WriteLine(L"Введите команду:");  
 SetConsoleCP(1251);  
 Console::CursorLeft=10;  
 Console::CursorTop=18;  
 scanf("%s", team);  
 SetConsoleCP(866);  
 for(i=1;i<NM;i++)  
	if (strcmp(team,match[i].enemy)==0)  
	   {  
		g = match[i].liv_score;  
	   }  
Console::ForegroundColor=ConsoleColor::White;  
Console::BackgroundColor=ConsoleColor::Red;  
Console::CursorLeft=30;  
Console::CursorTop=17;  
printf("Против команды %s",team);  
Console::CursorLeft=30;  
Console::CursorTop=18;  
printf("Ливерпуль забил %d голов",g);  
getch();  
} 
void diagram(struct z *match, int NM, struct sp**spisok) 
{ 
struct sp *nt; 
int len,i,NColor; 
long sum = 0 ; 
char str1[20]; 
char str2[20]; 
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::Black; 
Console::BackgroundColor=ConsoleColor::White; 
Console::Clear(); 
	for(i=0;i<NM;i++) sum = sum+match[i].en_score ; 
		if(!*spisok) 
			for(i=0;i<NM;i++) 
			vstavka(match,match[i].enemy, NM, spisok); 
			Color=ConsoleColor::Black; NColor=0; 
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++) 
		{ 
		sprintf(str1,"%s",nt->team); 
		sprintf(str2,"%3.1f%%",(nt->en_score*100./sum)); 
		Console::ForegroundColor=ConsoleColor::Black; 
		Console::BackgroundColor= ConsoleColor::White; 
		Console::CursorLeft=5; Console::CursorTop=i+1; 
		printf(str1); 
		Console::CursorLeft=20; 
		printf("%s",str2); 
		Console::BackgroundColor=++Color; NColor++; 
		Console::CursorLeft=30; 
			for(len=0; len<nt->en_score*100/sum; len++) printf(" "); 
				if(NColor==14) 
					{ Color=ConsoleColor::Black; NColor=0; } 
		} 
getch(); 
return ; 
} 
void alfalist(struct z* match, int NM, struct sp**spisok) 
{ 
int i, n=0; 
struct sp* nt; 
struct sp* z;
Console::ForegroundColor=ConsoleColor::Red; 
Console::BackgroundColor=ConsoleColor::White; 
Console::Clear(); 
	if(!*spisok) 
		for(i=0;i<NM;i++) 
			vstavka(match,match[i].enemy, NM, spisok); 
			Console::Clear(); 
			printf("\n\t\t Алфавитный список противников и обратный"); 
			printf("\n =======================================================================\n"); 
	for(nt=*spisok; nt!=0; nt=nt->sled) 
		printf("\n %-20s %ld",nt->team,nt->en_score); 
	for (nt = *spisok, z=0; nt != 0; z=nt, nt = nt->sled);
		for(nt=z; nt!=0; nt=nt->pred)
			{  
			Console::CursorLeft=48;
			Console::CursorTop=4+n;
				printf(" %-20s %ld", nt->team, nt->en_score);
			n+=1;
			}
    getch();
}
void same(struct z* match, int NM) {
    int g, s, flag = 0;
    char w[20], q[20];
    
    for(int i = 0; i < NM; i++) {
  if (match[i].en_score != 0)
   if (match[i].liv_score != 0)
        if (match[i].en_score == match[i].liv_score ) {
   g = match[i].en_score;
            strcpy(w, match[i].enemy);
            s = i;
            break;
        }
    }
    
    for(int j = s + 1; j < NM; j++) {
        if (match[j].en_score == match[j].liv_score) {
            if (match[j].en_score == g) {
				flag = 1;
                strcpy(q, match[j].enemy);
            }
        }
    }
	if (flag == 1){
 Console::CursorLeft=10;  
 Console::CursorTop=17;  
 printf("Против команд:");
    Console::CursorLeft=30;  
 Console::CursorTop=17;
    printf("%s\n", q);
 Console::CursorLeft=30;
Console::CursorTop=18; 
printf("%s\n", w); }
    getch();
if (flag == 0)
{  Console::CursorLeft=10;  
 Console::CursorTop=17;
 printf("В исходном файле нет двух матчей с одинаковыми ничьими");
 getch();
}
}
