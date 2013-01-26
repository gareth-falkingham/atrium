// AtriumServer.cpp : Defines the entry point for the console application.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//#include <vld.h>

#include "Atrium.h"


int main()
{
	Atrium* _atriumServer = new Atrium();

	_atriumServer->process();

	delete _atriumServer;
	_atriumServer = 0;

	return 0;
}