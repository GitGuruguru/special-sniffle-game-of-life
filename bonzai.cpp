#include <ncurses.h>
#include <unistd.h> // for usleep()
#include <vector>
#include <string>

void drawTree(int stage) {
    clear();
    
    // Bonsai stages - each stage adds more growth
    std::vector<std::string> bonsai = {
        "   (.)  ", 
        "   | |  ", 
        "   | |  ", 
        "  ===== "
    };
    
    if (stage > 1) bonsai.insert(bonsai.begin(), "   * *   ");
    if (stage > 2) bonsai.insert(bonsai.begin(), "  *** ***  ");
    if (stage > 3) bonsai.insert(bonsai.begin(), " ***** ***** ");
    if (stage > 4) bonsai.insert(bonsai.begin(), "*************");
    
    // Print bonsai at the center of the screen
    int y, x;
    getmaxyx(stdscr, y, x);
    int startY = y / 2 - bonsai.size() / 2;
    int startX = x / 2 - bonsai[0].size() / 2;
    
    for (size_t i = 0; i < bonsai.size(); i++) {
        mvprintw(startY + i, startX, "%s", bonsai[i].c_str());
    }
    
    refresh();
}

int main() {
    initscr();            // Start ncurses
    noecho();             // Don't show typed input
    curs_set(0);          // Hide cursor
    
    for (int i = 1; i <= 5; i++) {  // Grow tree in 5 stages
        drawTree(i);
        usleep(800000);   // Pause (800ms) before growing further
    }
    
    getch(); // Wait for user input before exiting
    endwin(); // Close ncurses
    
    return 0;
}
