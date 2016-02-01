#ifndef SES_WORLD_HPP
#define SES_WORLD_HPP

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <Box2D/Common/b2Draw.h>
#include <Box2D/Dynamics/b2World.h>

#include "../Helper/PhysicConverter.hpp"
#include "../Helper/pugixml.hpp"
#include "../Helper/Compression.hpp"

#include "Entity.hpp"
#include "System.hpp"

namespace ses
{

class World : public b2Draw
{
    public:
        World();
        ~World();

        // Entities
        Entity::Ptr getEntity(std::string const& id);
        Entity::Ptr instantiate(std::string const& id);
        bool isInstantiated(std::string const& id);
        void removeEntity(std::string const& id);
        void onEntityUpdate(std::string const& id);
        EntityVector getEntities() const;
        EntityVector getEntities(ComponentFilter const& filter) const;
        std::size_t getEntitiesCount() const;
        void removeEntities();

        // Systems
        template<typename T, typename ... Args>
        T& addSystem(Args&& ... args);
        template<typename T>
        bool hasSystem();
        bool hasSystem(std::string const& systemId);
        template<typename T>
        T& getSystem();
        template<typename T>
        void removeSystem();
        void removeSystem(std::string const& systemId);
        void removeSystems();
        std::size_t getSystemsCount() const;
        void handleMessage(sf::Packet& packet);

        // Common
        void update();
        void update(float dt);
        void reset();

        // Prefab
        void setPrefab(std::string const& id, std::function<Entity::Ptr()> prefab);
        void loadPrefab(std::string const& filename);
        void savePrefab(std::string const& filename, std::string const& prefabId, Entity::Ptr entity);
        Entity::Ptr execPrefab(std::string const& id);
        std::size_t getPrefabInstanceCount(std::string const& id);

        // Physic
        void setGravity(b2Vec2 gravity);
        b2Vec2 getGravity() const;
        void render(sf::RenderTarget& target);
        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);

        // Saving/Loading
        bool load(std::string const& filename);
        void save(std::string const& filename);

        void setCompression(bool compressedFile);
        bool isCompressed() const;

    protected:
        b2World mWorld;
        EntityVector mEntities;
        std::map<std::string,System::Ptr> mSystems;
        std::map<std::string,std::function<Entity::Ptr()>> mPrefabs;
        std::map<std::string,std::size_t> mPrefabInstanceCounter;
        sf::RenderTarget* mRenderTarget;
        bool mCompressedFile;
};

template<typename T, typename ... Args>
T& World::addSystem(Args&& ... args)
{
    mSystems[lp::type<T>()] = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    mSystems[lp::type<T>()]->mWorld = this;
    return getSystem<T>();
}

template<typename T>
bool World::hasSystem()
{
    return hasSystem(lp::type<T>());
}

template<typename T>
T& World::getSystem()
{
    assert(hasSystem<T>());
    return static_cast<T&>(*mSystems.at(lp::type<T>()));
}

template<typename T>
void World::removeSystem()
{
    removeSystem(lp::type<T>());
}

} // namespace ses

#endif // SES_WORLD_HPP
