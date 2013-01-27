#include "debug.hpp"

// ----------------------------------------------------------------------
// Log a simple message to the consol
// ----------------------------------------------------------------------

void Debug::log(LogLevel p_level, char* p_title, const char* p_messages, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, p_messages);
#if defined(HACKY_LINUX_HACK)
    // TODO: no vsprintf_s in gcc?
	vsprintf(buffer, p_messages, args);
#else
	vsprintf_s(buffer, p_messages, args);
#endif
	switch(p_level)
	{
		case LogLevel::INFO:
		{
			std::cout << "[INFO](" << p_title << "): "; 
			break;
		}
		case LogLevel::WARNING:
		{
			std::cout << "[WARNING](" << p_title << "): "; 
			break;
		}
		case LogLevel::EXCEPTION: 
		{
			std::cout << "[EXCEPTION](" << p_title << "): "; 
			break;
		}
	}
	std::cout << buffer << std::endl;
	va_end(args);
}
