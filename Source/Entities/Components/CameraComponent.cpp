#include "CameraComponent.hpp"
#include "../Entity.hpp"
#include "../../Application/Application.hpp"

namespace ses
{

CameraComponent::CameraComponent() : Component()
{
    mView = ah::Application::getWindow().getDefaultView();
}

void CameraComponent::setView(sf::View const& view)
{
    mView = view;
    update();
}

sf::View& CameraComponent::getView()
{
    update();
    return mView;
}

void CameraComponent::update()
{
    if (mEntity != nullptr)
    {
        mView.setCenter(mEntity->getPosition());
    }
}

sf::FloatRect CameraComponent::getViewRect() const
{
    return sf::FloatRect(mView.getCenter() - mView.getSize() * 0.5f,mView.getSize());
}

void CameraComponent::load(pugi::xml_node& component)
{
    mView.setSize(sf::Vector2f(component.attribute("size-x").as_float(),component.attribute("size-y").as_float()));
}

void CameraComponent::save(pugi::xml_node& component)
{
    component.append_attribute("size-x") = mView.getSize().x;
    component.append_attribute("size-y") = mView.getSize().y;
}

} // namespace ses
