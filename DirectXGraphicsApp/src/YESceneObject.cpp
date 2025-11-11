#include "YESceneObject.h"

YESceneObject::YESceneObject()
{
}

YESceneObject::~YESceneObject()
{
}

void YESceneObject::Draw(IUnknown* context)
{
	for (size_t i = 0; i < _meshesToRender.size(); ++i)
	{
		_meshesToRender[i].Draw(context);
	}
}