#ifndef system_h
#define system_h

#include "process.h"
#include "processor.h"
#include <string>
#include <vector>

class System {
public:
  processor &cpu();
  vector<Process> &processes();
  float memory_Utilization();
  long up_time();
  int totaol_processes();
  int running_processes();
  string kernel();
  string operating_system();

private:
  processor cpu_ = {};
  vector<Process> processes_ = {};
};

#endif