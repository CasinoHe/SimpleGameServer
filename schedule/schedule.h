// Purpose: define schedule struct for save schedule data
// Date: 2019.2.25
// By: Casino
#pragma once
#ifndef SIMPLE_SERVER_SCHEDULE_SCHEDULE_H
#define SIMPLE_SERVER_SCHEDULE_SCHEDULE_H


#include <string>

struct SScheduleData {
    long long microseconds_when;  // microseconds for schedule timestamp
    std::string func_name;
};


#endif