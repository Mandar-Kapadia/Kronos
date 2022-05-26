/*Copyright 2022  Mandar Kapadia */
#include "boost/regex.hpp" //NOLINT
#include <iostream> //NOLINT
#include <fstream> //NOLINT
#include <string> //NOLINT
#include "boost/date_time/gregorian/gregorian.hpp" //NOLINT
#include "boost/date_time/posix_time/posix_time.hpp"//NOLINT
#include <exception>//NOLINT

void testingArc(bool(*func)(int argc), int argc);
int main(int argc, char* argv[]) {
    testingArc(([](int argc){ return (argc != 2);}) , argc);

    std::string fileName = argv[1];
    std::string output = fileName + ".rpt";

    boost::posix_time::ptime begining;
    boost::posix_time::ptime ending;

    boost::gregorian::date FirstDate;
    boost::gregorian::date SecondDate;

    boost::posix_time::time_duration time;

    std::string startingString = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}): \\(log.c.166\\) server started";//NOLINT
    std::string endingString = "([0-9]{4})-([0-9]{2})-([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}).([0-9]{3}):INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080";//NOLINT

    boost::regex startingRegex(startingString, boost::regex::perl);
    boost::regex endRegex(endingString);
    boost::smatch smash;

    std::ifstream file(fileName.c_str());
    std::ofstream outputFile(output);
    std::string lines;
    bool checking = false;


    int linesCounter = 1;
    std::string boots = "";

    std::string startTime = "";
    std::string endTime = "";

    unsigned int hours = 0;
    unsigned int minutes = 0;
    unsigned int seconds = 0;
    if (!file.is_open()) {
        std::runtime_error("cannot open file");
    }
    while (std::getline(file, lines)) {
        startTime.clear();
        endTime.clear();
        if (boost::regex_search(lines, smash, startingRegex)) {
            startTime = smash[1] + "-" + smash[2] + "-" + smash[3] + " " + smash[4] + ":" + smash[5] + ":" + smash[6];//NOLINT
            FirstDate =  boost::gregorian::date(boost::gregorian::from_simple_string(smash[1] + "-" + smash[2] + "-" + smash[3])); //NOLINT
            hours = std::stoi(smash[4]);
            minutes = std::stoi(smash[5]);
            seconds = std::stoi(smash[6]);

            begining = boost::posix_time::ptime(FirstDate, boost::posix_time::time_duration(hours, minutes, seconds));//NOLINT

            if (checking == true) {
                boots += "**** Incomplete boot **** \n\n";
            }

            boots += ("=== Device boot ===\n" + std::to_string(linesCounter) + "(" + fileName + "): " + startTime + " Boot Start\n"); //NOLINT

            checking = true;
        }
        if (boost::regex_search(lines, smash, endRegex)) {
            endTime = smash[1] + "-" + smash[2] + "-" + smash[3] + " " + smash[4] + ":" + smash[5] + ":" + smash[6];//NOLINT
            SecondDate =  boost::gregorian::date(boost::gregorian::from_simple_string(smash[1] + "-" + smash[2] + "-" + smash[3])); //NOLINT

            hours = std::stoi(smash[4]);
            minutes = std::stoi(smash[5]);
            seconds = std::stoi(smash[6]);

            ending = boost::posix_time::ptime(SecondDate, boost::posix_time::time_duration(hours, minutes, seconds));//NOLINT

            boots += (std::to_string(linesCounter) + "(" + fileName + "): " + endTime + " Boot Completed\n"); //NOLINT

            time = ending - begining;

            boots += "\tBoot Time: " + std::to_string(time.total_milliseconds()) + "ms \n";//NOLINT

            checking = false;
        }
        linesCounter++;
    }
    file.close();

    outputFile << boots;
    outputFile.close();
}
void testingArc(bool(*func)(int argc), int argc) {
    if (func(argc)) {
         std::runtime_error("need 2 arguments");
    }
}
