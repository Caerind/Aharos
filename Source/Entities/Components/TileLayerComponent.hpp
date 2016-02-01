#ifndef SES_TILELAYERCOMPONENT_HPP
#define SES_TILELAYERCOMPONENT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <map>
#include "../Component.hpp"

namespace ses
{

class TileLayerComponent : public Component, public sf::Drawable
{
    public:
        TileLayerComponent();
        ~TileLayerComponent();

        void setTexture(std::string const& id);

        void setCollide(int id, bool collide = true);
        bool isCollide(int id);

        void setId(int id, sf::Vector2i coords);
        int getId(sf::Vector2i coords);
        bool hasCollisions(sf::Vector2i coords);

        void setSize(sf::Vector2i size);
        sf::Vector2i getSize();

        void setTileSize(sf::Vector2i size);
        sf::Vector2i getTileSize();

        sf::FloatRect getBounds() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void load(pugi::xml_node& component);
        void save(pugi::xml_node& component);

        void loadFromTmx(std::string filename);
        void saveToTmx(std::string filename);

        void loadData(pugi::xml_node& node);
        void saveData(pugi::xml_node& node);

    protected:
        void update();
        sf::Vector2f idToTex(int id);
        int texToId(sf::Vector2f texCoords);
        void addFixture(sf::Vector2i coords);
        void removeFixture(sf::Vector2i coords);

    protected:
        sf::VertexArray mArray;
        sf::Texture* mTexture;
        std::string mTextureId;
        sf::Vector2i mSize;
        sf::Vector2i mTileSize;
        std::map<int,bool> mCollisions;
        std::map<std::string,bool> mHasCollisions;
        std::string mFilename;
};

} // namespace ses

#endif // TILELAYERCOMPONENT_HPP
