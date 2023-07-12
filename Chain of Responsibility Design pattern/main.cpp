#include<iostream>
#include<bits/stdc++.h>
#include "LogProcessor.cpp"
#include "loggerProcessors.cpp"

using namespace std;
int main() {
    // we are building a logger system
    //   info -> debug -> error -> nullptr;
    LogProcessor *logobject = new InfoLogProcessor(new DebugLogProcessor(new ErrorLogProcessor(nullptr)));
    logobject->log(LogProcessor::ERROR,"Just for ERROr");
    logobject->log(LogProcessor::DEBUG,"Just for debug");
    logobject->log(LogProcessor::INFO,"Just for Info");
    return 0;
}
