#include "ncursesDisplay.h"
#include "system.h"

int main() {
  System system;
  NCursesDisplay::Display(system, 10);
  return 0;
}