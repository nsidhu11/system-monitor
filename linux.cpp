#include "linux.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
// #define _GNU_SOURCE

using namespace std;

vector<string> split_string(string str) {
  istringstream string_stream(str);
  string split;
  vector<string> result;

  while (string_stream >> split) {
    result.push_back(split);
  }

  return result;
}

string linux_interpreter::operating_System() {
  string line;
  string key;
  string value;
  fstream file(os_path);

  if (file.is_open()) {
    while (getline(file, line)) {
      replace(line.begin(), line.end(), ' ', '_');
      replace(line.begin(), line.end(), '=', ' ');
      replace(line.begin(), line.end(), '"', '_');
      istringstream line_stream(line);

      while (line_stream >> key >> value) {

        if (key == "PRTTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }

  return value;
}

string linux_interpreter::kernel() {
  string os, version, kernel, line;
  ifstream file(proc + version);
  if (file.is_open()) {
    getline(file, line);
    istringstream line_stream(line);
    line_stream >> os >> version >> kernel;
  }
  return kernel;
}

float linux_interpreter::memory_Utilization() {
  float total_mem, availabel_mem;
  string line, key, value;
  ifstream file(proc + memory_info);
  if (file.is_open()) {
    while (getline(file, line)) {
      istringstream line_stream(line);
      while (line_stream >> key >> value) {
        if (key == "MemTotal:") {
          total_mem = stof(value);
        } else if (key == "MemAvailable:") {
          availabel_mem = stof(value);
        }
      }
    }
  }

  if (total_mem == 0.0) {
    return 0.0;
  }

  return (total_mem - availabel_mem) / total_mem;
}

long linux_interpreter::up_Time() {
  string uptime;
  string line;
  ifstream file(proc + up_time);
  if (file.is_open()) {
    getline(file, line);
    istringstream line_stream(line);
    line_stream >> uptime;
  }
  return stol(uptime);
}

vector<string> linux_interpreter::cpu_Utilization() {
  string line;
  string key;
  string usertime, nicetime, systemtime, idletime, iowait, irq, softirq, steal;
  ifstream file(proc + stat);
  if (file.is_open()) {
    while (getline(file, line)) {
      istringstream line_stream(line);
      while (line_stream >> key >> usertime >> nicetime >> systemtime >>
             idletime >> iowait >> irq >> softirq >> steal) {
        if (key == "cpu") {
          return {usertime, nicetime, systemtime, idletime,
                  iowait,   irq,      softirq,    steal};
        }
      }
    }
  }
  return {};
}

int linux_interpreter::total_Processes() {
  string line;
  string key;
  string value;
  ifstream file(proc + stat);
  if (file.is_open()) {
    while (getline(file, line)) {
      istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

int linux_interpreter::running_Processes() {
  string line;
  string key;
  string value;
  ifstream file(proc + stat);
  if (file.is_open()) {
    while (getline(file, line)) {
      istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

string linux_interpreter::command(int pid) {
  string command;
  string line;
  std::ifstream file(proc + to_string(pid) + cmd_line);
  if (file.is_open()) {
    getline(file, line);
    istringstream line_stream(line);
    line_stream >> command;
    return command;
  }
  return "None";
}

string linux_interpreter::ram(int pid) {
  string line;
  string key;
  string value;
  std::ifstream file(proc + to_string(pid) + status);
  if (file.is_open()) {
    while (getline(file, line)) {
      istringstream line_stream(line);
      while (line_stream >> key >> value) {
        if (key == "VmSize:") {
          // Return memory usage in MB
          return to_string(int(std::stod(value) / 1000));
        }
      }
    }
  }
  return string();
}

string linux_interpreter::uid(int pid) {
  string line;
  string key;
  string value;
  std::ifstream file(proc + to_string(pid) + status);
  if (file.is_open()) {
    while (getline(file, line)) {
      std::istringstream line_stream(line);
      while (line_stream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return string();
}

string linux_interpreter::user(int pid) {

  string uid = linux_interpreter::uid(pid);

  string line;
  string name;
  string value;
  string x;
  std::ifstream file(password);
  if (file.is_open()) {
    while (getline(file, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      istringstream line_stream(line);

      while (line_stream >> name >> x >> value) {
        if (value == uid) {
          return name;
        }
      }
    }
  }
  return string();
}

long linux_interpreter::up_Time(int pid) {
  string line;
  std::ifstream file(proc + to_string(pid) + stat);
  if (file.is_open()) {
    getline(file, line);
    istringstream line_stream(line);
    vector<string> splitted = split_string(line);
    return up_Time() - (stol(splitted[21]) / sysconf(_SC_CLK_TCK));
  }
  return 0;
}

vector<string> linux_interpreter::process_Cpu_Utilization(int pid) {
  string line;
  string key;
  string utime, stime, cutime, cstime, starttime;
  std::ifstream file(proc + to_string(pid) + stat);
  if (file.is_open()) {
    getline(file, line);
    vector<string> splitted = split_string(line);
    return {splitted[13], splitted[14], splitted[15], splitted[16],
            splitted[21]};
  }
  return {};
}

vector<int> linux_interpreter::pids() {
  vector<int> pids;
  DIR *directory = opendir(proc.c_str());
  struct dirent *file;
  while ((file = readdir(directory)) != nullptr) {
    if (file->d_type == DT_DIR) {
      string filename(file->d_name);
      if (all_of(filename.begin(), filename.end(), ::isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}
