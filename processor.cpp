#include "processor.h"
#include "linux.h"
#include <string>
#include <vector>

float processor::utilization()
{
    vector<string> cpu_usage = linux_interpreter::cpu_Utilization();
    const long int usertime = stol(cpu_usage[0]);
    const long int nicetime = stol(cpu_usage[1]);
    const long int systemtime = stol(cpu_usage[2]);
    const long int idletime = stol(cpu_usage[3]);
    const long int iowait = stol(cpu_usage[4]);
    const long int irq = stol(cpu_usage[5]);
    const long int softirq = stol(cpu_usage[6]);
    const long int steal = stol(cpu_usage[7]);

    const float IDLE = idletime + iowait;
    const float NON_IDLE = usertime + nicetime + systemtime + irq + softirq + steal;
    const float TOTAL = IDLE + NON_IDLE;

    if (prev_user == -1 || prev_nice == -1 || prev_system == -1 || prev_idle == -1 || prev_iowait == -1 || prev_irq == -1 || prev_softirq == -1 || prev_steal == -1)
    {
        prev_user = usertime;
        prev_nice = nicetime;
        prev_system = systemtime;
        prev_idle = idletime;
        prev_iowait = iowait;
        prev_irq = irq;
        prev_softirq = softirq;
        prev_steal = steal;

        if (TOTAL == 0.0)
        {
            return 0.0;
        }

        return (TOTAL - IDLE) / TOTAL;
    }
    else
    {
        const long int PREV_IDLE = prev_idle + prev_iowait;
        const long int PREV_NON_IDLE =
            prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
        const long int PREV_TOTAL = PREV_IDLE + PREV_NON_IDLE;

        const float TOTAL_DIF = TOTAL - PREV_TOTAL;
        const float IDLE_DIF = IDLE - PREV_IDLE;

        prev_user = usertime;
        prev_nice = nicetime;
        prev_system = systemtime;
        prev_idle = idletime;
        prev_iowait = iowait;
        prev_irq = irq;
        prev_softirq = softirq;
        prev_steal = steal;

        if (TOTAL_DIF == 0.0)
        {
            return 0.0;
        }
        return (TOTAL_DIF - IDLE_DIF) / TOTAL_DIF;
    }
    return 0.0;
}