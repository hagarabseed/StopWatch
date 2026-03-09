#include <graphics.h>
#include <conio.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int hVal=0, mVal=0, sVal=0, msVal=0;
bool running=false;
steady_clock::time_point startTime;
milliseconds elapsed(0);

void drawButton(int x,int y,int w,int h,const char* label,int color){
    setfillstyle(SOLID_FILL,color);
    bar(x,y,x+w,y+h);
    setcolor(WHITE);
    rectangle(x,y,x+w,y+h);
    settextstyle(2,0,4);
    outtextxy(x+w/2-textwidth((char*)label)/2,
              y+h/2-textheight((char*)label)/2,
              (char*)label);
}

void updateTimeDisplay(){
    setfillstyle(SOLID_FILL,BLACK);
    bar(50,60,450,180);

    int totalSeconds = elapsed.count()/1000;
    hVal=totalSeconds/3600;
    mVal=(totalSeconds/60)%60;
    sVal=totalSeconds%60;
    msVal=elapsed.count()%1000;

    char buffer[50];
    sprintf(buffer,"%02d   %02d   %02d   %03d",hVal,mVal,sVal,msVal);

    setcolor(YELLOW);
    settextstyle(3,0,4);
    outtextxy(80,120,buffer);

    settextstyle(0,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(90,90,"hr");
    outtextxy(150,90,"min");
    outtextxy(220,90,"sec");
    outtextxy(300,90,"ms");

    settextstyle(3,0,2);
    setcolor(LIGHTGREEN);
    outtextxy(130,30,"<<< Stopwatch >>>");
}

int main(){
    initwindow(500,400,"Stopwatch");

    drawButton(80,320,100,40,"Start",LIGHTGREEN);
    drawButton(200,320,100,40,"Stop",LIGHTRED);
    drawButton(320,320,100,40,"Reset",LIGHTBLUE);

    while(true){
        if(running){
            elapsed=duration_cast<milliseconds>(steady_clock::now()-startTime);
        }

        updateTimeDisplay();
        delay(20);

        if(ismouseclick(WM_LBUTTONDOWN)){
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);

            if(x>=80 && x<=180 && y>=320 && y<=360){
                running=true;
                startTime=steady_clock::now()-elapsed;
            }
          
            else if(x>=200 && x<=300 && y>=320 && y<=360){
                running=false;
            }
            
            else if(x>=320 && x<=420 && y>=320 && y<=360){
                running=false;
                elapsed=milliseconds(0);
                hVal=mVal=sVal=msVal=0;
            }
        }

        if(kbhit() && getch()==27) break; 
    }

    closegraph();
    return 0;
}
