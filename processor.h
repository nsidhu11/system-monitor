#ifndef processor_h
#define processor_h

class processor {
public:
  float utilization();

private:
  long int prev_user = -1;
  long int prev_nice = -1;
  long int prev_system = -1;
  long int prev_idle = -1;
  long int prev_iowait = 1;
  long int prev_irq = -1;
  long int prev_softirq = -1;
  long int prev_steal = -1;
};

#endif