//
//  Atrium
//  Ben Maher
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   networkdata.h
//  Description :   Network data for the player, keep it up to date
//  Author      :   Ben Maher
//

#pragma once

#if !defined(__ATRIUM_GJ_NETWORKDATA_H__)
#define __ATRIUM_GJ_NETWORKDATA_H__

struct TNetworkData
{
	unsigned short playerID;
	char hairID;
	char headID;
	char bodyID;
	char heartID;
	float x;
	float y;
};

#endif // __ATRIUM_GJ_NETWORKDATA_H__
