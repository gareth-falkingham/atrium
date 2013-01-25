#ifndef UTIL_DEBUG_H
#define UTIL_DEBUG_H

#pragma once

#include <iostream>
#include <stdarg.h>

enum LogLevel { INFO, WARNING, EXCEPTION };

class Debug
{
	public:
	
		static void log(LogLevel p_level, char* p_funcName, const char* p_logs, ...);
};

#endif