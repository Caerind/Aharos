#include "SpriteComponent.hpp"
#include "../../Application/Application.hpp"

namespace ses
{

SpriteComponent::SpriteComponent()
{
}

void SpriteComponent::setTexture(std::string const& id)
{
    mTextureId = id;
    sf::Sprite::setTexture(ah::Application::getResources().getTexture(mTextureId));
}

bool SpriteComponent::contains(sf::Vector2f const& position) const
{
    return getGlobalBounds().contains(position);
}

sf::FloatRect SpriteComponent::getBounds() const
{
    return getGlobalBounds();
}

void SpriteComponent::load(pugi::xml_node& component)
{
    setOrigin({component.attribute("ori-x").as_float(),component.attribute("ori-y").as_float()});
    setPosition({component.attribute("pos-x").as_float(),component.attribute("pos-y").as_float()});
    setScale({component.attribute("sca-x").as_float(),component.attribute("sca-y").as_float()});
    setRotation(component.attribute("rot").as_float());
    setTexture(component.attribute("img").value());
    setTextureRect({component.attribute("tL").as_int(),component.attribute("tT").as_int(),component.attribute("tW").as_int(),component.attribute("tH").as_int()});
}

void SpriteComponent::save(pugi::xml_node& component)
{
    component.append_attribute("pos-x") = getPosition().x;
    component.append_attribute("pos-y") = getPosition().y;
    component.append_attribute("ori-x") = getOrigin().x;
    component.append_attribute("ori-y") = getOrigin().y;
    component.append_attribute("sca-x") = getScale().x;
    component.append_attribute("sca-y") = getScale().y;
    component.append_attribute("rot") = getRotation();
    component.append_attribute("img") = mTextureId.c_str();
    component.append_attribute("tL") = getTextureRect().left;
    component.append_attribute("tT") = getTextureRect().top;
    component.append_attribute("tW") = getTextureRect().width;
    component.append_attribute("tH") = getTextureRect().height;
}

} // namespace ses
