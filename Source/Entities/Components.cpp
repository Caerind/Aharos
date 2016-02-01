#include "Components.hpp"

namespace ses
{

void registerComponents()
{
    ses::Entity::registerComponent<SpriteComponent>();
    ses::Entity::registerComponent<CameraComponent>();
    ses::Entity::registerComponent<AudioSourceComponent>();
    ses::Entity::registerComponent<AudioListenerComponent>();
    ses::Entity::registerComponent<TileLayerComponent>();
}

} // namespace ses
