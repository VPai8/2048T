#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include<bits/stdc++.h>
using namespace std;

#define DELAY 300000
vector<vector<int>> tzfe(4,vector<int>(4,0));
int score=0;

void drawbox(int my,int mx){
	int i,j,numd,c;
	mvprintw(2,mx/2-1,"2048");
	for(i=-2;i<2;++i){
 		mvprintw(my/2+3*i,mx/2-16, "|");
 		mvprintw(my/2+3*i+1,mx/2-16, "|");
 		mvprintw(my/2+3*i+2,mx/2-16, "|"); 
 		mvprintw(my/2-7,mx/2+8*(i+1)-3, "_");
 		mvprintw(my/2-7,mx/2+8*(i+1)-4, "_");
 		mvprintw(my/2-7,mx/2+8*(i+1)-5, "_");
    }
 for(i=-2;i<2;++i)
 	for(j=-1;j<3;++j){
 		mvprintw(my/2+3*i,mx/2+8*j, "|");
 		mvprintw(my/2+3*i+1,mx/2+8*j, "|");
 		mvprintw(my/2+3*i+2,mx/2+8*j, "|"); 
 		mvprintw(my/2+3*i+2,mx/2+8*j-3, "_"); 
 		mvprintw(my/2+3*i+2,mx/2+8*j-4, "_"); 
 		mvprintw(my/2+3*i+2,mx/2+8*j-5, "_"); 
 		numd=ceil(log10(tzfe[i+2][j+1]));
 		switch(numd){
 			case 1: 
 			case 2: c=4; break;
 			case 3: c=5; break;
 			case 4: c=6; break;
 		}
 		if(tzfe[i+2][j+1])
 			mvprintw(my/2+3*i+1,mx/2+8*j-c,(to_string(tzfe[i+2][j+1])).c_str());
 	}
 	mvprintw(9,mx-21,"SCORE");
 	mvprintw(10,mx-20,(to_string(score)).c_str());
 	mvprintw(my-5,10,"- use a,w,s,d for movement");
 	mvprintw(my-4,10,"- game ends when no move is possible or grid is full and keypress didnt move any tile");
 	mvprintw(my-3,10,"- ctrl+c to exit");
}

int kbhit(){
    int ch = getch();
    if(ch != ERR){
        ungetch(ch);
        return 1;
    } 
    return 0;    
}

void random2start(){
 srand(int(time(0)));
 int pos1=rand()%16,pos2;
 tzfe[pos1/4][pos1%4]=2;
 do{
 	pos2=rand()%16;
 }while(pos2==pos1);
 tzfe[pos2/4][pos2%4]=2;
}

bool random2(bool mov){
	vector<int> empty;
	int i,j;
	for(i=0;i<4;++i)
		for(j=0;j<4;++j)
			if(tzfe[i][j]==0)
				empty.push_back(4*i+j);
	if(empty.size()==0)
		return true;
	if(mov){
		int pos=rand()%empty.size();
		tzfe[empty[pos]/4][empty[pos]%4]=2;
	}
	return false;
}

bool makemove(int key){
    int i,j,c;
    bool mov=false;
    vector<int> res(4,0);
switch(key){
        case 97: 
for(i=0;i<4;++i)
    for(j=0;j<4;++j){
        if(tzfe[i][j]==0){
            c=j+1;
            while(c!=4&&!tzfe[i][c])
                ++c;
            if(c!=4){
                mov=true;
                tzfe[i][j]=tzfe[i][c];
                tzfe[i][c]=0;
                if(j!=0){
                    if(!res[j-1]&&tzfe[i][j]==tzfe[i][j-1]){
                        tzfe[i][j-1]*=2;
                        score+=tzfe[i][j-1];
                        tzfe[i][j]=0;
                        res[j-1]=1;
                    }
                    else if(tzfe[i][j-1]==0){
                    tzfe[i][j-1]=tzfe[i][j];
                    tzfe[i][j]=0;
                    }
                }
            }
            else
                break;            
        }
        else{
            if(j!=3){
                if(tzfe[i][j]==tzfe[i][j+1]){
                    tzfe[i][j]*=2;
                    score+=tzfe[i][j];
                    tzfe[i][j+1]=0;
                    res[j]=1;
                    mov=true;
                }
            }
        }                
    }
    break;
        case 100:
for(i=0;i<4;++i)
    for(j=3;j>=0;--j){
        if(tzfe[i][j]==0){
            c=j-1;
            while(c!=-1&&!tzfe[i][c])
                --c;
            if(c!=-1){
                mov=true;
                tzfe[i][j]=tzfe[i][c];
                tzfe[i][c]=0;
                if(j!=3){
                    if(!res[j+1]&&tzfe[i][j]==tzfe[i][j+1]){
                        tzfe[i][j+1]*=2;
                        score+=tzfe[i][j+1];
                        tzfe[i][j]=0;
                        res[j+1]=1;
                    }
                    else if(tzfe[i][j+1]==0){
                    tzfe[i][j+1]=tzfe[i][j];
                    tzfe[i][j]=0;
                    }
                }                
            }
            else
                break;            
        }
        else{
            if(j!=0){
                if(tzfe[i][j]==tzfe[i][j-1]){
                    tzfe[i][j]*=2;
                    score+=tzfe[i][j];
                    tzfe[i][j-1]=0;
                    res[j]=1;
                    mov=true;
                }
            }                
        }
    }
    break;
    case 119:
for(i=0;i<4;++i)
    for(j=0;j<4;++j){
        if(tzfe[j][i]==0){
            c=j+1;
            while(c!=4&&!tzfe[c][i])
                ++c;
            if(c!=4){
                mov=true;
                tzfe[j][i]=tzfe[c][i];
                tzfe[c][i]=0;
                if(j!=0){
                    if(!res[j-1]&&tzfe[j][i]==tzfe[j-1][i]){
                        tzfe[j-1][i]*=2;
                        score+=tzfe[j-1][i];
                        tzfe[j][i]=0;
                        res[j-1]=1;
                    }
                    else if(tzfe[j-1][i]==0){
                            tzfe[j-1][i]=tzfe[j][i];
                            tzfe[j][i]=0;
                        }
                }
            }
            else
                break;            
        }
        else{
            if(j!=3){
                if(tzfe[j][i]==tzfe[j+1][i]){
                    tzfe[j][i]*=2;
                    score+=tzfe[j][i];
                    tzfe[j+1][i]=0;
                    res[j]=1;
                    mov=true;
                }
            }                
        }
    }
    break;
        case 115:
for(i=0;i<4;++i)
    for(j=3;j>=0;--j){
        if(tzfe[j][i]==0){
            c=j-1;
            while(c!=-1&&!tzfe[c][i])
                --c;
            if(c!=-1){
                mov=true;
                tzfe[j][i]=tzfe[c][i];
                tzfe[c][i]=0;
                if(j!=3){
                    if(!res[j+1]&&tzfe[j][i]==tzfe[j+1][i]){
                        tzfe[j+1][i]*=2;
                        score+=tzfe[j+1][i];
                        tzfe[j][i]=0;
                        res[j+1]=1;
                    }
                    else if(tzfe[j+1][i]==0){
                           tzfe[j+1][i]=tzfe[j][i];
                           tzfe[j][i]=0;
                        }
                }
            }
            else
                break;            
        }
        else{
            if(j!=0){
                if(tzfe[j][i]==tzfe[j-1][i]){
                    tzfe[j][i]*=2;
                    score+=tzfe[j][i];
                    tzfe[j-1][i]=0;
                    res[j]=1;
                    mov=true;
                }
            }                
        }
    }
} 
return mov;  
}

void gameover(int my,int mx){
	clear();
	mvprintw(my/2,mx/2-4, "game over");
	refresh();
	usleep(DELAY);
}

int main(){
 int i,j,my,mx,key;
 bool end=false,mov;
 initscr();
 noecho();
 nodelay(stdscr, TRUE);
 random2start();  //position two 2s ramdomly
 while(!end){
 	getmaxyx(stdscr, my, mx);
 	clear();
 	drawbox(my,mx);
 	refresh();
 	while(1){
   		if(kbhit()){
   			key=getch();
   			break;
   		}
 	}
 	mov=makemove(key);
 	end=random2(mov);  //position one 2 randomly
 	usleep(DELAY);
 }
 gameover(my,mx);
 endwin();
}