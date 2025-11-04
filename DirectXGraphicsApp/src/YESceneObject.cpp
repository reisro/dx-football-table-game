#include "YESceneObject.h"

YESceneObject::YESceneObject()
{
}

YESceneObject::~YESceneObject()
{
}

//void YESceneObject::addMesh(std::vector<YEMesh> meshes)
//{
//	_meshes = meshes;
//}

void YESceneObject::Draw(IUnknown* context)
{
	for (size_t i = 0; i < _meshes.size(); ++i)
	{
		_meshes[i].Draw(context);
	}
}