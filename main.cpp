#include <iostream>
#include "windows.h"
#include "conio.h"
#include <fstream>
#include "string.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
void setcur(int x, int y)//????????? ??????? ?? ???????  x y 
{ 
COORD coord; 
coord.X = x; 
coord.Y = y; 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
};
void savehwnd(HWND handle)
{
	ofstream myfile;
  	myfile.open ("save.txt", std::ios::app);
  	myfile << handle<<endl;
  	myfile.close();
}
void clear_file()
{
	std::ofstream ofs;
	ofs.open("save.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();	
}

int loadhwnd(HWND handle[10000])
{
	ifstream myfile;
	string str;
  	myfile.open ("save.txt");
  	int i=0;
  	while(getline(myfile,str))
  	{
  	
  	char * p;
  	handle[i]=(HWND)strtoul(str.c_str(),& p, 16);
  	i++;
  }
 
	  myfile.close();
	   return i;
	   
  	
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
int main(int argc, char* argv[])
{
	
	
	POINT p, oldp;
	char ch;
	int i=0,n;
	HWND arrHwnd[10000];
	HWND oldHwnd, hwnd;
	n=loadhwnd(arrHwnd);
	
	cout<<"Skrytye ranee okna: \n";
	for (int i=0;i<n;i++)
		{
			cout<<arrHwnd[i]<<endl;
		}
	cout<<"Sdelat' ranee skrytye okna vidimymi? y/n"<<endl;
	
	ch=getch();
	if(ch=='y'||ch=='Y'||ch=='s'||ch=='S'){
		for (int i=0;i<n;i++)
		ShowWindow(arrHwnd[i],1);	
	}
	clear_file();
	system("cls");
	hidecursor();
	while(true){
if (GetCursorPos(&p))
{
	

	setcur(0, 0);
	hwnd=WindowFromPoint(p);
	cout<<hwnd<<endl;
	if(kbhit()){
		ch=getch();
	
	if(ch=='s'||ch=='S')
		{
			ShowWindow(hwnd,0);
			//oldHwnd=hwnd;
			savehwnd( hwnd);
			
			arrHwnd[i]=hwnd	;
			i++;	
			
		}
	if((ch=='d'||ch=='D')&&i>0)
		{
			i--;
			ShowWindow(arrHwnd[i],1);
			
			
			cout<<"i=="<<i<<endl;		
		}
   }
}
}
	   
	    return 0;
}
