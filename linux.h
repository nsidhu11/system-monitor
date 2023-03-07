#ifndef linux_h
#define linux_h

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

namespace linux_interpreter {

const string proc = "/proc/";
const string cmd_line = "/cmdline";
const string cpu_info = "/cpuinfo";
const string status = "/status";
const string stat = "/stat";
const string up_time = "/uptime";
const string memory_info = "/meminfo";
const string version = "/version";
const string os_path = "/etc/os-release";
const string password = "/etc/passwd";

float memory_Utilization();
long up_Time();
vector<int> pids();
int total_Processes();
int running_Processes();
string operating_System();
string kernel();

enum cpu_states {
  users = 0,
  nice,
  system,
  idle,
  io_wait,
  irq,
  soft_irq,
  steal,
  guest,
  guest_nice
};
vector<string> cpu_Utilization();

string command(int pid);
string ram(int pid);
string uid(int pid);
string user(int pid);
long up_Time(int pid);
vector<string> process_Cpu_Utilization(int pid);

}; // namespace linux_interpreter

#endif