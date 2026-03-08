#include <graphics.h>
#include <conio.h>
#include <chrono>
#include <string>
#include <cstring>
using namespace std;
using namespace std::chrono;

int hVal = 0, mVal = 0, sVal = 0, msVal = 0;
bool running = false;
steady_clock::time_point startTime;
milliseconds elapsed(0);

void drawButton(int x, int y, int w, int h, const char* label) {
    char temp[100];
    strcpy(temp, label);

    rectangle(x, y, x+w, y+h);
    settextstyle(2, 0, 4);
    outtextxy(x + w/2 - textwidth(temp)/2,
              y + h/2 - textheight(temp)/2,
              temp);
}

void updateTimeDisplay() {
    setfillstyle(SOLID_FILL, BLACK);
    bar(50, 60, 450, 180);

    int totalSeconds = elapsed.count() / 1000;
    hVal = totalSeconds / 3600;
    mVal = (totalSeconds / 60) % 60;
    sVal = totalSeconds % 60;
    msVal = elapsed.count() % 1000;

    char buffer[50];
    sprintf(buffer, "%02d   %02d   %02d   %03d", hVal, mVal, sVal, msVal);

    setcolor(WHITE);
    settextstyle(3, 0, 4);
    outtextxy(80, 120, buffer);

    settextstyle(0, 0, 2);
    outtextxy(90, 90, "hr");
    outtextxy(160, 90, "min");
    outtextxy(240, 90, "sec");
    outtextxy(330, 90, "ms");

    settextstyle(3, 0, 2);
    char title[] = "<<< Stopwatch >>>";
    outtextxy(130, 30, title);
}

int main() {
    initwindow(500, 300, "Stopwatch");

    drawButton(100, 220, 80, 40, "Start");
    drawButton(200, 220, 80, 40, "Stop");
    drawButton(300, 220, 80, 40, "Reset");

    while(true) {
        if(running) {
            elapsed = duration_cast<milliseconds>(steady_clock::now() - startTime);
        }

        updateTimeDisplay();
        delay(20);

        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(x >= 100 && x <= 180 && y >= 220 && y <= 260) {
                running = true;
                startTime = steady_clock::now() - elapsed;
            }
            else if(x >= 200 && x <= 280 && y >= 220 && y <= 260) {
                running = false;
            }
            else if(x >= 300 && x <= 380 && y >= 220 && y <= 260) {
                running = false;
                elapsed = milliseconds(0);
                hVal = mVal = sVal = msVal = 0;
            }
        }

        if(kbhit() && getch() == 27) break;
    }

    closegraph();
    return 0;
}
