#include "DefaultCube.h"
#include "bgfx/bgfx.h"

Rendering::DefaultCube::DefaultCube()
{
}

Rendering::DefaultCube::~DefaultCube()
{
}

void Rendering::DefaultCube::DescribeMesh()
{
	bgfx::Init init;
	/*init.type = bgfx::RendererType::Direct3D11;
	init.platformData.nwh = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
	init.platformData.ndt = entry::getNativeDisplayHandle();
	init.platformData.type = entry::getNativeWindowHandleType();
	init.resolution.width = m_width;
	init.resolution.height = m_height;
	init.resolution.reset = m_reset;*/
	bgfx::init(init);
}
