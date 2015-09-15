#include "Renderer.hpp"
#include "../../Aharos/Application/Application.hpp"

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
    mInstance.mRenderables.erase(std::remove_if(mInstance.mRenderables.begin(),mInstance.mRenderables.end(),
    [&](rd::Renderable* r){ return r == renderable || r == nullptr ;}),mInstance.mRenderables.end());
}

void Renderer::clear()
{
    mInstance.mRenderables.clear();
}

void Renderer::render(sf::RenderTarget& target)
{
    mInstance.mRenderables.erase(std::remove_if(mInstance.mRenderables.begin(),mInstance.mRenderables.end(),
    [](rd::Renderable* r){ return r == nullptr ;}),mInstance.mRenderables.end());

    std::sort(mInstance.mRenderables.begin(), mInstance.mRenderables.end(),
    [](Renderable* a, Renderable* b) -> bool
    {
        if (a != nullptr && b != nullptr)
        {
            if (a->getZ() == b->getZ())
            {
               return a->getPosition().y < b->getPosition().y;
            }
            else
            {
                return a->getZ() < b->getZ();
            }
        }
        return true;
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
