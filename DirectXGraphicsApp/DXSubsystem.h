#pragma once

#ifndef _DX_SUBSYSTEM_H
#define _DX_SUBSYSTEM_H

class DXSubsystem
{
public:

	// Starts up all procedures for a specific susbsystem
	virtual void Setup() = 0;

	// Required operations to start for this subsystem
	virtual bool Init() = 0;

	// Operations needed after initialization
	virtual void PostInit() = 0;
};

#endif _DX_SUBSYSTEM_H
