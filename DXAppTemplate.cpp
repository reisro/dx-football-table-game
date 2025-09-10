
#include "DXApplication.h"
#include "DXGame.h"
#include "GameEntry.h"

using namespace gamentry;

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static const uint16_t s_cubeTriStrip[] =
{
	0, 1, 2,
	3,
	7,
	1,
	5,
	0,
	4,
	2,
	6,
	7,
	4,
	5,
};

static const uint16_t s_cubeLineList[] =
{
	0, 1,
	0, 2,
	0, 4,
	1, 3,
	1, 5,
	2, 3,
	2, 6,
	3, 7,
	4, 5,
	4, 6,
	5, 7,
	6, 7,
};

static const uint16_t s_cubeLineStrip[] =
{
	0, 2, 3, 1, 5, 7, 6, 4,
	0, 2, 6, 4, 5, 7, 3, 1,
	0,
};

static const uint16_t s_cubePoints[] =
{
	0, 1, 2, 3, 4, 5, 6, 7
};

static const char* s_ptNames[]
{
	"Triangle List",
	"Triangle Strip",
	"Lines",
	"Line Strip",
	"Points",
};

static const uint64_t s_ptState[]
{
	UINT64_C(0),
	BGFX_STATE_PT_TRISTRIP,
	BGFX_STATE_PT_LINES,
	BGFX_STATE_PT_LINESTRIP,
	BGFX_STATE_PT_POINTS,
};

class Cube: public DXGame
{
public:
	Cube() : DXGame("Default Cube") 
	{
	}

	Cube(const char* _game_name) :
		DXGame(_game_name)
	{
	}

	void init(uint32_t _width, uint32_t _height) override
	{
		DXLog("----------------------------------------------");
		DXLog("\tYakira Engine v0.2");
		DXLog("----------------------------------------------");

		DXEngineConfig::DXConfig gameConfig;
		gameConfig.graphicsAPI = { DXEngineConfig::GraphicsAPI::DirectX11 };

		YE::DXApplication::Setup(gameConfig);

		// Create a window game application
		DXWindow* appWindow = new DXWindow();
		
		// Run the app
		if (YE::DXApplication::Init(appWindow))
		{
			DXLog("Initialized Game Window...");
		}
		
		DXLog("Initialized Cube Game...");

		// Create vertex stream declaration.
		PosColorVertex::init();

		//// Create static vertex buffer.
		//m_vbh = bgfx::createVertexBuffer(
		//	// Static data can be passed with bgfx::makeRef
		//	bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices))
		//	, PosColorVertex::ms_layout
		//);

		//// Create static index buffer for triangle list rendering.
		//m_ibh[0] = bgfx::createIndexBuffer(
		//	// Static data can be passed with bgfx::makeRef
		//	bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
		//);

		//// Create static index buffer for triangle strip rendering.
		//m_ibh[1] = bgfx::createIndexBuffer(
		//	// Static data can be passed with bgfx::makeRef
		//	bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip))
		//);

		//// Create static index buffer for line list rendering.
		//m_ibh[2] = bgfx::createIndexBuffer(
		//	// Static data can be passed with bgfx::makeRef
		//	bgfx::makeRef(s_cubeLineList, sizeof(s_cubeLineList))
		//);

		//// Create static index buffer for line strip rendering.
		//m_ibh[3] = bgfx::createIndexBuffer(
		//	// Static data can be passed with bgfx::makeRef
		//	bgfx::makeRef(s_cubeLineStrip, sizeof(s_cubeLineStrip))
		//);

		//// Create static index buffer for point list rendering.
		//m_ibh[4] = bgfx::createIndexBuffer(
		//	// Static data can be passed with bgfx::makeRef
		//	bgfx::makeRef(s_cubePoints, sizeof(s_cubePoints))
		//);
	}

	bool update(float _deltaTime) override
	{
		//const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
		//const bx::Vec3 eye = { 0.0f, 0.0f, -7.0f };

		return true;
	}

	virtual void shutdown() override
	{
		DXLog("Shutdown Cube Game...");
	}

private:
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh[5];
};

WINDOW_MAIN_ENTRY(Cube);