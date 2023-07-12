#pragma once
#include "LogProcessor.cpp"
#include <bits/stdc++.h>
using namespace std;

class InfoLogProcessor:public LogProcessor{
    public:
    InfoLogProcessor(LogProcessor *nextLogProcessor):LogProcessor(nextLogProcessor) {
        // pass the next logger to log processor
    }

    // override the log class
    void log(int logLevel,string message) {
        if(logLevel == INFO) {
            // if log level matches then process
            cout<<"INFO :"<<message<<endl;
        }else{
            // tell the parent to move to next logger
            LogProcessor::log(logLevel,message);
        }
    }
};

class DebugLogProcessor:public LogProcessor{
    public:
    DebugLogProcessor(LogProcessor *nextLogProcessor):LogProcessor(nextLogProcessor) {
    }

    void log(int logLevel,string message) {
        if(logLevel == DEBUG) {
            cout<<"DEBUG :"<<message<<endl;
        }else{
            LogProcessor::log(logLevel,message);
        }
    }
};

class ErrorLogProcessor:public LogProcessor{
    public:
    ErrorLogProcessor(LogProcessor *nextLogProcessor):LogProcessor(nextLogProcessor) {
    }

    void log(int logLevel,string message) {
        if(logLevel == ERROR) {
            cout<<"ERROR :"<<message<<endl;
        }else{
            LogProcessor::log(logLevel,message);
        }
    }
};

