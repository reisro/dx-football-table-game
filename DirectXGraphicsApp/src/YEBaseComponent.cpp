#include "YEBaseComponent.h"
#include "YEGameObject.h"

YETransformComponent* YEBaseComponent::getTransformComponent()
{
    return _gameObject->_transform;
}
