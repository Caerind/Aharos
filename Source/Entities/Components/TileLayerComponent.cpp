#include "TileLayerComponent.hpp"
#include "../../Application/Application.hpp"
#include "../Entity.hpp"
#include "../../Helper/Compression.hpp"

namespace ses
{

TileLayerComponent::TileLayerComponent()
: mTexture(nullptr)
, mFilename("")
{
    update();
}

TileLayerComponent::~TileLayerComponent()
{
    sf::Vector2i coords;
    for (coords.x = 0; coords.x < mSize.x; coords.x++)
    {
        for (coords.y = 0; coords.y < mSize.y; coords.y++)
        {
            removeFixture(coords);
        }
    }
}

void TileLayerComponent::setTexture(std::string const& id)
{
    mTextureId = id;
    mTexture = &ah::Application::getResources().getTexture(mTextureId);
}

void TileLayerComponent::setCollide(int id, bool collide)
{
    mCollisions[id] = collide;
}

bool TileLayerComponent::isCollide(int id)
{
    auto itr = mCollisions.find(id);
    if (itr != mCollisions.end())
    {
        return itr->second;
    }
    return false;
}

void TileLayerComponent::setId(int id, sf::Vector2i coords)
{
    if (coords.x >= 0 && coords.x < mSize.x && coords.y >= 0 && coords.y < mSize.y)
    {
        int exId = getId(coords);
        if ((!isCollide(exId) && isCollide(id)) || (id == exId && isCollide(id) && !hasCollisions(coords)))
        {
            addFixture(coords);
        }
        if (isCollide(exId) && !isCollide(id))
        {
            removeFixture(coords);
        }

        if (id != 0)
        {
            sf::Vertex* quad = &mArray[(coords.x + coords.y * mSize.x) * 4];
            sf::Vector2f tex = idToTex(id);
            quad[0].texCoords = sf::Vector2f(tex.x,tex.y);
            quad[1].texCoords = sf::Vector2f(tex.x + mTileSize.x, tex.y);
            quad[2].texCoords = sf::Vector2f(tex.x + mTileSize.x, tex.y + mTileSize.y);
            quad[3].texCoords = sf::Vector2f(tex.x, tex.y + mTileSize.y);
        }
    }
}

int TileLayerComponent::getId(sf::Vector2i coords)
{
    if (coords.x >= 0 && coords.x < mSize.x && coords.y >= 0 && coords.y < mSize.y)
    {
        sf::Vertex* quad = &mArray[(coords.x + coords.y * mSize.x) * 4];
        return texToId(quad[0].texCoords);
    }
    return 0;
}

bool TileLayerComponent::hasCollisions(sf::Vector2i coords)
{
    auto itr = mHasCollisions.find(std::to_string(coords.x) + "," + std::to_string(coords.y));
    if (itr != mHasCollisions.end())
    {
        return itr->second;
    }
    return false;
}

void TileLayerComponent::setSize(sf::Vector2i size)
{
    mSize = size;
    update();
}

sf::Vector2i TileLayerComponent::getSize()
{
    return mSize;
}

void TileLayerComponent::setTileSize(sf::Vector2i size)
{
    mTileSize = size;
    update();
}

sf::FloatRect TileLayerComponent::getBounds() const
{
    float x = 0;
    float y = 0;
    if (mEntity != nullptr)
    {
        x = mEntity->getPosition().x;
        y = mEntity->getPosition().y;
    }
    return sf::FloatRect(x,y,mTileSize.x * mSize.x,mTileSize.y * mSize.y);
}

void TileLayerComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mTexture != nullptr)
    {
        states.texture = mTexture;
        target.draw(mArray,states);
    }
}

void TileLayerComponent::load(pugi::xml_node& component)
{
    std::string filename = component.attribute("filename").value();
    if (filename != "")
    {
        loadFromTmx(filename);
    }
    else
    {
        setTexture(component.attribute("texture").value());
        setSize({component.attribute("size-x").as_int(),component.attribute("size-y").as_int()});
        setTileSize({component.attribute("tsize-x").as_int(),component.attribute("tsize-y").as_int()});

        loadData(component);
    }
}

void TileLayerComponent::save(pugi::xml_node& component)
{
    if (mFilename != "")
    {
        component.append_attribute("filename") = mFilename.c_str();
        saveToTmx(mFilename);
    }
    else
    {
        component.append_attribute("texture") = mTextureId.c_str();
        component.append_attribute("size-x") = mSize.x;
        component.append_attribute("size-y") = mSize.y;
        component.append_attribute("tsize-x") = mTileSize.x;
        component.append_attribute("tsize-y") = mTileSize.y;

        saveData(component);
    }
}

void TileLayerComponent::loadFromTmx(std::string filename)
{
    // TODO : Load From TMX
}

void TileLayerComponent::saveToTmx(std::string filename)
{
    // TODO : Save To TMX
}

void TileLayerComponent::loadData(pugi::xml_node& node)
{
    // Load Collisions
    std::string collisions = node.attribute("collisions").value();
    std::istringstream iss(collisions);
    std::string v;
    while (std::getline(iss,v,','))
    {
        mCollisions[std::stoi(v)] = true;
    }

    // TODO : Load Has Collisions

    // Load Data
    std::string data = node.attribute("data").value();
    sf::Vector2i coords;

    std::stringstream ss;
    ss << data;
    ss >> data;

    if (!lp::decompress(data))
        return;

    std::vector<unsigned char> byteVector;  // to hold decompressed data as bytes
    byteVector.reserve(mSize.x * mSize.y * 4); // number of tiles * 4 bytes = 32bits / tile

    for (std::string::iterator i = data.begin(); i != data.end(); ++i)
        byteVector.push_back(*i);

    for (std::size_t i = 0; i < byteVector.size() - 3 ; i += 4)
    {
        int id = byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24;
        setId(id,coords);

        coords.x = (coords.x + 1) % mSize.x;
        if (coords.x == 0) coords.y++;
    }
}

void TileLayerComponent::saveData(pugi::xml_node& node)
{
    std::string data;
    data.reserve(mSize.x * mSize.y * 4);
    sf::Vector2i coords;
    for (coords.y = 0; coords.y < mSize.y; coords.y++)
    {
        for (coords.x = 0; coords.x < mSize.x; coords.x++)
        {
            const int id = getId(coords);
            data.push_back((char)(id));
            data.push_back((char)(id >> 8));
            data.push_back((char)(id >> 16));
            data.push_back((char)(id >> 24));
        }
    }
    if(lp::compress(data))
    {
        node.append_attribute("data") = data.c_str();
    }

    std::string collisions;
    for (auto itr = mCollisions.begin(); itr != mCollisions.end(); itr++)
    {
        if (itr->second)
        {
            collisions += std::to_string(itr->first) + ",";
        }
    }
    node.append_attribute("collisions") = collisions.c_str();

    // TODO : Save Has Collisions
}

void TileLayerComponent::update()
{
    mArray.setPrimitiveType(sf::Quads);
    mArray.resize(mSize.x * mSize.y * 4);
    for (int i = 0; i < mSize.x; ++i)
    {
        for (int j = 0; j < mSize.y; ++j)
        {
            sf::Vertex* quad = &mArray[(i + j * mSize.x) * 4];
            quad[0].position = sf::Vector2f(i * mTileSize.x, j * mTileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * mTileSize.x, j * mTileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * mTileSize.x, (j + 1) * mTileSize.y);
            quad[3].position = sf::Vector2f(i * mTileSize.x, (j + 1) * mTileSize.y);
        }
    }
}

sf::Vector2f TileLayerComponent::idToTex(int id)
{
    id -= 1;
    if (mTexture != nullptr && id >= 0 && mTileSize.x != 0)
    {
        int tilePerLine = mTexture->getSize().x / mTileSize.x;
        int x = id%tilePerLine;
        int y = id/tilePerLine;
        return sf::Vector2f(x * mTileSize.x,y * mTileSize.y);
    }
    return sf::Vector2f(0,0);
}

int TileLayerComponent::texToId(sf::Vector2f texCoords)
{
    if (mTexture != nullptr && texCoords.x >= 0 && texCoords.y >= 0 && mTileSize.x != 0 && mTileSize.y != 0)
    {
        int x = texCoords.x / mTileSize.x;
        int y = texCoords.y / mTileSize.y;
        int tilePerLine = mTexture->getSize().x / mTileSize.x;
        return x + y * tilePerLine + 1;
    }
    return 0;
}

void TileLayerComponent::addFixture(sf::Vector2i coords)
{
    if (mEntity != nullptr)
    {
        b2FixtureDef fDef;
        b2PolygonShape s;
        b2Vec2 d = b2Vec2(Physic::pixelsToMeters((coords.x + 0.5f) * mTileSize.x),Physic::pixelsToMeters((coords.y + 0.5f) * mTileSize.y));
        s.SetAsBox(Physic::pixelsToMeters(mTileSize.x) / 2.f,Physic::pixelsToMeters(mTileSize.y) / 2.f,d,0);
        fDef.shape = &s;
        mHasCollisions[std::to_string(coords.x) + "," + std::to_string(coords.y)] = true;
        mEntity->addFixture(fDef);
    }
}

void TileLayerComponent::removeFixture(sf::Vector2i coords)
{
    if (mEntity != nullptr)
    {
        mHasCollisions[std::to_string(coords.x) + "," + std::to_string(coords.y)] = false;
        mEntity->removeFixture(std::to_string(coords.x) + "," + std::to_string(coords.y));
    }
}

} // namespace ses
