#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
    // // Get current time
    // std::time_t now = std::time(nullptr);
    // std::tm *localTime = std::localtime(&now);

    // // Format time as hh:mm:ss string
    // std::stringstream ss;
    // ss << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
    //    << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
    //    << std::setfill('0') << std::setw(2) << localTime->tm_sec;
    // std::string timeString = ss.str();

    // // Output formatted time
    // std::cout << timeString << std::endl;
    std::stringstream stringstream("Navpreet Singh Sidhu");
    std::string split;

    while (stringstream >> split)
    {
        cout << "sstream: " << stringstream.peek() << endl;
        cout << "Split: " << split << endl;
    }

    return 0;
}

vector<string> splitString(string s)
{
    std::stringstream stringstream(s);
    std::string split;
    vector<string> result;

    while (stringstream >> split)
    {
        result.push_back(split);
    }
    return result;
}