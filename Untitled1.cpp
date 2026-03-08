#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <string>
using namespace std;

struct Box {
    int x, y, w, h;
    string label;
    int color;
};

void drawBox(Box b, string value) {
    setcolor(b.color);
    rectangle(b.x, b.y, b.x + b.w, b.y + b.h);
    settextstyle(3, 0, 2);
    setcolor(WHITE);
    outtextxy(b.x + 10, b.y + 10, const_cast<char*>(b.label.c_str()));
    outtextxy(b.x + 10, b.y + 40, const_cast<char*>(value.c_str()));
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    Box msBox = {50, 50, 80, 80, "MS", RED};
    Box secBox = {150, 50, 80, 80, "SEC", GREEN};
    Box minBox = {250, 50, 80, 80, "MIN", BLUE};
    Box hrBox  = {350, 50, 80, 80, "HR", YELLOW};

    Box start = {100, 180, 100, 50, "START", CYAN};
    Box stop  = {220, 180, 100, 50, "STOP", MAGENTA};
    Box reset = {340, 180, 100, 50, "RESET", LIGHTGRAY};

    bool running = false;
    clock_t startTime = 0;
    double elapsed = 0;

    while (true) {
        cleardevice();

        if (running) {
            elapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        }

        int totalSeconds = (int)elapsed;
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds / 60) % 60;
        int seconds = totalSeconds % 60;
        int milliseconds = (int)((elapsed - totalSeconds) * 1000);

        drawBox(msBox, to_string(milliseconds));
        drawBox(secBox, to_string(seconds));
        drawBox(minBox, to_string(minutes));
        drawBox(hrBox, to_string(hours));

        drawBox(start, "");
        drawBox(stop, "");
        drawBox(reset, "");

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);

            if (mx >= start.x && mx <= start.x + start.w && my >= start.y && my <= start.y + start.h) {
                running = true;
                startTime = clock();
            }
            if (mx >= stop.x && mx <= stop.x + stop.w && my >= stop.y && my <= stop.y + stop.h) {
                running = false;
            }
            if (mx >= reset.x && mx <= reset.x + reset.w && my >= reset.y && my <= reset.y + reset.h) {
                running = false;
                elapsed = 0;
                startTime = clock();
            }
        }

        delay(50);

        if (kbhit() && getch() == 27) break;
    }

    closegraph();
    return 0;
}


