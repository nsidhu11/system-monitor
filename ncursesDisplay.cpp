#include <chrono>
#include <curses.h>
#include <string>
#include <thread>
#include <vector>
#include "format.h"
#include "ncursesDisplay.h"
#include "system.h"

string NCursesDisplay::ProgressBar(float percent)
{
    string result{"0%"};
    int size{50};
    float bars{percent * size};

    for (int i{0}; i < size; ++i)
    {
        result += i <= bars ? '|' : ' ';
    }

    string display{to_string(percent * 100).substr(0, 4)};
    if (percent < 0.1 || percent == 1.0)
        display = " " + to_string(percent * 100).substr(0, 3);
    return result + " " + display + "/100%";
}

void NCursesDisplay::DisplaySystem(System &system, WINDOW *window)
{
    int row{0};
    mvwprintw(window, ++row, 2, ("OS: " + system.operating_system).c_str());
    mvwprintw(window, ++row, 2, ("Kernel: " + system.kernel()).c_str());
    mvwprintw(window, ++row, 2, "CPU: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(system.cpu().utilization()).c_str());
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, 2, "Memory: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(system.memory_Utilization()).c_str());
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, 2, ("Total Processes: " + to_string(system.totaol_processes())).c_str());
    mvwprintw(window, ++row, 2, ("Running Processes: " + to_string(system.running_processes())).c_str());
    mvwprintw(window, ++row, 2, ("Up Time: " + Format::elapsed_Time(system.up_time())).c_str());
    wrefresh(window);
}

void NCursesDisplay::DisplayProcesses(std::vector<Process> &processes, WINDOW *window, int n)
{
    int row{0};
    int const pid_column{2};
    int const user_column{9};
    int const cpu_column{16};
    int const ram_column{26};
    int const time_column{35};
    int const command_column{46};
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, ++row, pid_column, "PID");
    mvwprintw(window, row, user_column, "USER");
    mvwprintw(window, row, cpu_column, "CPU[%%]");
    mvwprintw(window, row, ram_column, "RAM[MB]");
    mvwprintw(window, row, time_column, "TIME+");
    mvwprintw(window, row, command_column, "COMMAND");
    wattroff(window, COLOR_PAIR(2));
    for (int i = 0; i < n; ++i)
    {
        mvwprintw(window, ++row, pid_column, to_string(processes[i].Pid()).c_str());
        mvwprintw(window, row, user_column, processes[i].user().c_str());
        float cpu = processes[i].get_cpu_utilization() * 100;
        mvwprintw(window, row, cpu_column, to_string(cpu).substr(0, 4).c_str());
        mvwprintw(window, row, ram_column, processes[i].ram().c_str());
        mvwprintw(window, row, time_column, Format::elapsed_Time(processes[i].up_Time()).c_str());
        mvwprintw(window, row, command_column, processes[i].command().substr(0, window->_maxx - 46).c_str());
    }
}

void NCursesDisplay::Display(System &system, int n)
{
    initscr();
    noecho();
    cbreak();
    start_color();

    int x_max{getmaxx(stdscr)};
    WINDOW *system_window = newwin(9, x_max - 1, 0, 0);
    WINDOW *process_window = newwin(3 + n, x_max - 1, system_window->_maxy + 1, 0);

    while (1)
    {
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        box(system_window, 0, 0);
        box(process_window, 0, 0);
        DisplaySystem(system, system_window);
        DisplayProcesses(system.Processes(), process_window, n);
        wrefresh(system_window);
        wrefresh(process_window);
        refresh();
        this_thread::sleep_for(chrono::seconds(1));
    }
    endwin();
}