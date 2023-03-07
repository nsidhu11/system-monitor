#include "system.h"
#include "linux.h"
#include "process.h"
#include "processor.h"
#include <algorithm>
#include <cstddef>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

processor &System::cpu() { return cpu_; }

vector<Process> &System::processes() {
  processes_.clear();
  vector<int> pids = linux_interpreter::pids();
  for (unsigned int i = 0; i < pids.size(); i++) {
    Process p = Process(pids[i]);
    processes_.push_back(p);
  }
  std::sort(processes_.begin(), processes_.end());
  std::reverse(processes_.begin(), processes_.end());
  return processes_;
}

std::string System::kernel() { return linux_interpreter::kernel(); }

float System::memory_Utilization() {
  return linux_interpreter::memory_Utilization();
}

string System::operating_system() {
  return linux_interpreter::operating_System();
}

int System::running_processes() {
  return linux_interpreter::running_Processes();
}

int System::totaol_processes() { return linux_interpreter::total_Processes(); }

long int System::up_time() { return linux_interpreter::up_Time(); }