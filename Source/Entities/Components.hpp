#ifndef SES_COMPONENTS_HPP
#define SES_COMPONENTS_HPP

#include "Entity.hpp"

#include "Components/SpriteComponent.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/AudioSourceComponent.hpp"
#include "Components/AudioListenerComponent.hpp"
#include "Components/TileLayerComponent.hpp"

namespace ses
{

void registerComponents();

} // namespace ses

#endif // SES_COMPONENTS_HPP
