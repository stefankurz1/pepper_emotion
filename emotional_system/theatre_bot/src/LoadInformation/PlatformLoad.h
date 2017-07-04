///////////////////////////////////////////////////////////
//  PlatformLoad.h
//  Implementation of the Class PlatformLoad
//  Created on:      04-dic-2014 04:42:19 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#if !defined(PLATFORMLOAD_H_)
#define PLATFORMLOAD_H_

#include "Load.h"

class PlatformLoad : public Load
{

public:
	PlatformLoad();
	virtual ~PlatformLoad();
	void LoadInformation();

};
#endif // !defined(PLATFORMLOAD_H_)
