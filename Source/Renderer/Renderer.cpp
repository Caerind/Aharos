#include "Renderer.hpp"

namespace rd
{

Renderer Renderer::mInstance;

Renderer::Renderer()
{
}

void Renderer::add(Renderable* renderable)
{
    mInstance.mRenderables.push_back(renderable);
}

void Renderer::remove(Renderable* renderable)
{
    for (std::size_t i = 0; i < mInstance.mRenderables.size(); i++)
    {
        if (mInstance.mRenderables[i] == renderable)
        {
            mInstance.mRenderables.erase(mInstance.mRenderables.begin() + i);
        }
    }
}

void Renderer::clear()
{
    mInstance.mRenderables.clear();
}

void Renderer::render(sf::RenderTarget& target)
{
    std::sort(mInstance.mRenderables.begin(), mInstance.mRenderables.end(),
    [](Renderable* a, Renderable* b) -> bool
    {
        if (a->getZ() == b->getZ())
        {
            return a->getPosition().y < b->getPosition().y;
        }
        else
        {
            return a->getZ() < b->getZ();
        }
    });

    sf::View oldView = target.getView();
    target.setView(mInstance.mView);
    sf::FloatRect viewRect = sf::FloatRect(mInstance.mView.getCenter() - 0.5f * mInstance.mView.getSize(), mInstance.mView.getSize());
    for (std::size_t i = 0; i < mInstance.mRenderables.size(); i++)
    {
        if (mInstance.mRenderables[i]->getBounds().intersects(viewRect))
        {
            mInstance.mRenderables[i]->render(target);
        }
    }

    target.setView(oldView);
}

void Renderer::setView(sf::View const& view)
{
    mInstance.mView = view;
}

sf::View& Renderer::getView()
{
    return mInstance.mView;
}

} // namespace rd
