#ifndef process_h
#define process_h

#include <string>
using namespace std;

class Process {
public:
  Process(int PID);
  int Pid() const;
  string user();
  string command();
  void update_cpu_utilization();
  float get_cpu_utilization() const;
  string ram();
  long int up_Time();
  bool operator<(Process const &a) const;

private:
  int pid;
  float cpu_utilization{0.0};
};

#endif