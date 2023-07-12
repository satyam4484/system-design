#pragma once
#include<bits/stdc++.h>
using namespace std;


class LogProcessor{
public :
    static const int INFO = 1;
    static const int DEBUG = 2;
    static const int ERROR = 3;

    LogProcessor *nextLogProcessor;

    LogProcessor(LogProcessor *loggerProcessor) {
        // store the next logger pointer
        this->nextLogProcessor = loggerProcessor;
    }

    virtual void log(int logLevel,string message) {

        // if next logger exist then call it 
        // this function is virual means it will be overidden by child classes
        if(this->nextLogProcessor!=nullptr) {
            this->nextLogProcessor->log(logLevel,message);
        }
    }
};