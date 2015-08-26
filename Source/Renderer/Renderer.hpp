#ifndef RD_RENDERER_HPP
#define RD_RENDERER_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Renderable.hpp"

namespace rd
{

class Renderer
{
    public:
        static void add(Renderable* renderable);
        static void remove(Renderable* renderable);
        static void clear();

        static void render(sf::RenderTarget& target);

        static void setView(sf::View const& view);
        static sf::View& getView();

    private:
        Renderer();

        static Renderer mInstance;

        std::vector<Renderable*> mRenderables;
        sf::View mView;
};

} // namespace rd

#endif // RD_RENDERER_HPP
