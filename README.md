# System monitoring application
This project aims to create a system monitoring application similar to the well-known *__htop__* application. With this project, you'll learn how to extract data about the computer's processes, CPU and memory usage, and display them in a well-organized and user-friendly interface.

Ncurses is a powerful programming library that provides a terminal-independent way to control the text-based terminal's display screen. It enables you to create interactive console applications that can be run on the command line interface, providing an intuitive graphical user interface (GUI) experience.

The functionality that can be added to the Linux System Monitor project is limited only by your creativity and the scope of the project. With the right features, this system monitor can become a valuable tool for system administrators, developers, and anyone who wants to monitor their computer's performance closely. 

## Features
1. __Real-time updates__: The monitor updates in real-time, displaying the most up-to-date information about system processes and statistics.
2. __User-friendly interface__: The user interface is be intuitive, easy to use, and visually appealing.
3. __Cross-platform compatibility__: The system monitor is able to run on various Linux distributions and architectures.
4. __Efficient resource usage__: The system monitor is designed to minimize resource usage, so it doesn't consume too much CPU or memory resources.
5. __Documentation__: The project is well-documented, including a clear explanation of the code and instructions on how to install and run the system monitor.

## Upcoming Features
1. __Process management__: Ability to kill or stop processes directly from the system monitor interface.
2. __Network monitoring__: A section that can displays network usage statistics, such as incoming and outgoing traffic, download and upload speeds, and more.
3. __Disk monitoring__: Section that shows disk usage statistics, including total and available disk space, file system type, and disk usage by different processes.
4. __CPU and memory usage alerts__: Ability to set CPU and memory usage alerts, which will notify the user when a particular threshold is crossed.
5. __History tracking__: Keeps track of historical data, such as CPU and memory usage over time, allowing the user to analyze trends and patterns.
6. __User-defined filters__: Allow users to define custom filters to view specific processes, services, or system statistics that match their search criteria.

## Requirements 
1. Linux based OS with Linux >= 2.6
2. cmake >= 3.11.3
3. make >= 4.1 (Linux)
4. gcc/g++ >= 7.4.0
5. install ncurses library   `sudo apt install libncurses5-dev libncursesw5-dev` 

## Build and Run
1. Make sure you meet the requirements.
2. Clone the repository
3. Build and compile using `make all`
4. Run using `./build/monitor`

## Demo
<a href="{demo.mo4}" title="Link Title"><img src="{demp.png}" alt="Demo" /></a>
