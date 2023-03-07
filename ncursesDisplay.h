#ifndef ncursesDisplay_h
#define ncursesDisplay_h
#include "process.h"
#include "system.h"
#include <curses.h>

namespace NCursesDisplay
{
    void Display(System &system, int n = 10);
    void DisplaySystem(System &system, WINDOW *window);
    void DisplayProcesses(std::vector<Process> &processes, WINDOW *window, int n);
    std::string ProgressBar(float percent);
};

#endif