#include "YEPhysX.h"

YEPhysX* YEPhysX::_instance = nullptr;
PxFoundation* YEPhysX::_foundation = nullptr;
PxDefaultAllocator YEPhysX::_allocator;
PxDefaultErrorCallback YEPhysX::_errorCallback;

YEPhysX::YEPhysX()
{
	YELog("\nCreated Physics instance....");
}

YEPhysX::~YEPhysX()
{
}

void YEPhysX::Setup()
{
}

bool YEPhysX::Init()
{
	_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, _allocator, _errorCallback);

	return false;
}

void YEPhysX::PostInit()
{
}

void YEPhysX::Clean()
{
}
