#include "process.h"
#include "linux.h"
#include <cctype>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

Process::Process(int PID) {
  this->pid = PID;
  update_cpu_utilization();
}

int Process::Pid() const { return this->pid; }

float Process::get_cpu_utilization() const { return cpu_utilization; }

void Process::update_cpu_utilization() {
  vector<string> cpu_usage =
      linux_interpreter::process_Cpu_Utilization(this->pid);
  const long int u_time = stol(cpu_usage[0]);
  const long int s_time = stol(cpu_usage[1]);
  const long int cu_time = stol(cpu_usage[2]);
  const long int cs_time = stol(cpu_usage[3]);
  const long int start_time = stol(cpu_usage[4]);
  const long int sys_time = linux_interpreter::up_Time();

  const float TOTAL_TIME =
      (u_time + s_time + cu_time + cs_time) / sysconf(_SC_CLK_TCK);
  const float ELAPSED_TIME = sys_time - (start_time / sysconf(_SC_CLK_TCK));
  if (ELAPSED_TIME == 0.0) {
    cpu_utilization = 0.0;
  } else {
    cpu_utilization = TOTAL_TIME / ELAPSED_TIME;
  }
}

string Process::command() { return linux_interpreter::command(this->pid); }

string Process::ram() { return linux_interpreter::ram(this->pid); }

string Process::user() { return linux_interpreter::user(this->pid); }

long int Process::up_Time() { return linux_interpreter::up_Time(this->pid); }

bool Process::operator<(Process const &a) const {
  return get_cpu_utilization() < a.get_cpu_utilization();
}