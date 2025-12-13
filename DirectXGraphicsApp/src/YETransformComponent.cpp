#include "YETransformComponent.h"
#include "YERenderer.h"
#include "YEGameObject.h"

YETransformComponent::YETransformComponent():
	x{ 0.0f }, y{ 0.0f }, z {0.0f },
	roll{ 0.0f }, yaw{ 0.0f }, pitch { 0.0f },
	sx{ 1.0f }, sy{ 1.0f }, sz{ 1.0f }
{
	_mWorld = XMFLOAT4X4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x,    y,    z,    1.0f
	};

	_mView = XMFLOAT4X4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	_mProj = XMFLOAT4X4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	YELog("\nCreated Transform Component...");
}

YETransformComponent::~YETransformComponent()
{
}

void YETransformComponent::start()
{
	//DXLog("\nStarted Transform Component...");
}

void YETransformComponent::shutdown()
{
	YELog("\nShutdown Transform Component...");
}

void YETransformComponent::update(float _deltaTime)
{
	//DXLog("\nUpdating Transform Component...");
}

void YETransformComponent::Attach(IYETransformComponentListener* observer)
{
	_list_observer.push_back(observer);
}

void YETransformComponent::Detach(IYETransformComponentListener* observer)
{
	_list_observer.remove(observer);
}

void YETransformComponent::Notify()
{
	if (_gameObject->hasMultipleMeshes)
	{
		for (size_t i =_gameObject->_id; i < _gameObject->_id + _gameObject->GetNumberOfChildren(); i++)
		{
            for (auto it = _list_observer.begin(); it != _list_observer.end(); ++it)
            {
                (*it)->Update(i, DirectX::XMLoadFloat4x4(&_mWorld));
            }
		}
	}
	else
	{
		std::list<IYETransformComponentListener*>::iterator it = _list_observer.begin();

		while (it != _list_observer.end())
		{
			(*it)->Update(_gameObject->_id, DirectX::XMLoadFloat4x4(&_mWorld));
			++it;
		}
	}
}

void YETransformComponent::setPosition(yeFloat _x, yeFloat _y, yeFloat _z)
{
	x = _x;
	y = _y;
	z = _z;

	_mWorld = XMFLOAT4X4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x,    y,    z,    1.0f
	};

	Notify();
}

void YETransformComponent::setPosition(YEVector3* position)
{
	_position.SetValue(position);

	x = position->_x;
	y = position->_y;
	z = position->_z;

	_mWorld = XMFLOAT4X4{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x,    y,    z,    1.0f
	};

	Notify();
}

void YETransformComponent::setTransformMatrix(const DirectX::CXMMATRIX& mWorld)
{
	XMStoreFloat4x4(&_mWorld, mWorld);

	Notify(); 
}

void YETransformComponent::setRotation(yeFloat x, yeFloat y, yeFloat z)
{
	roll = x;
	yaw = y;
	pitch = z;
}

void YETransformComponent::setScale(yeFloat x, yeFloat y, yeFloat z)
{
	sx = x;
	sy = y;
	sz = z;
}

YEVector3* YETransformComponent::getPosition()
{
	return &_position;
}

yeFloat* YETransformComponent::getRotation()
{
	return &roll;
}

yeFloat* YETransformComponent::getScale()
{
	return &sx;
}