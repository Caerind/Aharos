#include "World.hpp"

namespace ses
{

World::World() : mWorld(b2Vec2(0,0))
{
    mCompressedFile = false;
    mRenderTarget = nullptr;
    mWorld.SetDebugDraw(this);
    SetFlags(b2Draw::e_shapeBit);
}

World::~World()
{
}

Entity::Ptr World::getEntity(std::string const& id)
{
    std::size_t s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (mEntities[i]->getId() == id)
            {
                return mEntities[i];
            }
        }
    }
    return nullptr;
}

Entity::Ptr World::instantiate(std::string const& id)
{
    if (!isInstantiated(id))
    {
        b2BodyDef myBodyDef;
        mEntities.push_back(std::make_shared<Entity>(id));
        Entity::Ptr e = mEntities.back();
        e->mWorld = this;
        e->mBody = mWorld.CreateBody(&myBodyDef);
        e->mBody->SetUserData(e.get());
        return mEntities.back();
    }
    return nullptr;
}

bool World::isInstantiated(std::string const& id)
{
    return getEntity(id) != nullptr;
}

void World::removeEntity(std::string const& id)
{
    Entity::Ptr e = getEntity(id);
    if (e != nullptr)
    {
        e->remove();
    }
}

void World::onEntityUpdate(std::string const& id)
{
    Entity::Ptr e = getEntity(id);
    if (e != nullptr)
    {
        for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
        {
            itr->second->onEntityUpdate(e);
        }
    }
}

EntityVector World::getEntities() const
{
    return mEntities;
}

EntityVector World::getEntities(ComponentFilter const& filter) const
{
    EntityVector entities;
    std::size_t s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (filter.passFilter(mEntities[i].get()))
            {
                entities.push_back(mEntities[i]);
            }
        }
    }
    return entities;
}

std::size_t World::getEntitiesCount() const
{
    return mEntities.size();
}

void World::removeEntities()
{
    std::size_t s = mEntities.size();
    for (std::size_t i = 0; i < s; i++)
    {
        if (mEntities[i] != nullptr)
        {
            mEntities[i]->remove();
        }
    }
    update();
}

bool World::hasSystem(std::string const& systemId)
{
    return (mSystems.find(systemId) != mSystems.end());
}

void World::removeSystem(std::string const& systemId)
{
    auto itr = mSystems.find(systemId);
    if (itr != mSystems.end())
    {
        itr->second->mWorld = nullptr;
        mSystems.erase(itr);
    }
}

void World::removeSystems()
{
    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
    {
        itr->second->mWorld = nullptr;
        mSystems.erase(itr);
    }
}

std::size_t World::getSystemsCount() const
{
    return mSystems.size();
}

void World::handleMessage(sf::Packet& packet)
{
    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
    {
        itr->second->handleMessage(packet);
    }
}

void World::update()
{
    // Remove entities
    for (std::size_t i = 0; i < mEntities.size();)
    {
        bool removed = false;
        if (mEntities[i] != nullptr)
        {
            if (mEntities[i]->isMarkedForRemoval())
            {
                if (mEntities[i]->getBody() != nullptr)
                {
                    mWorld.DestroyBody(mEntities[i]->mBody);
                }

                for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
                {
                    itr->second->removeEntity(mEntities[i]);
                }

                mEntities.erase(i + mEntities.begin());
                removed = true;
            }
        }
        if (!removed)
        {
            i++;
        }
    }
}

void World::update(float dt)
{
    // Update PhysicWorld
    mWorld.Step(dt,8,3);

    // Remove Entities
    update();
}

void World::reset()
{
    removeSystems();
    removeEntities();
}

void World::setPrefab(std::string const& id, std::function<Entity::Ptr()> prefab)
{
    mPrefabs[id] = prefab;
    mPrefabInstanceCounter[id] = 0;
}

void World::loadPrefab(std::string const& filename)
{
    // Load file
    pugi::xml_document doc;
    if (mCompressedFile)
    {
        lp::loadCompressedXml(filename,doc);
    }
    else
    {
        if (!doc.load_file(filename.c_str()))
        {
            std::cerr << filename << " doesn't exists" << std::endl;
            return;
        }
    }

    // Load Prefabs
    for (pugi::xml_node prefab = doc.child("Prefab"); prefab; prefab = prefab.next_sibling("Prefab"))
    {
        if (prefab)
        {
            std::string prefabId = prefab.attribute("id").value();
            // Create Prefab
            setPrefab(prefabId,[this,prefabId,filename]() -> Entity::Ptr {
                Entity::Ptr e = instantiate(prefabId + std::to_string(getPrefabInstanceCount(prefabId)));
                if (e != nullptr)
                {
                    pugi::xml_document doc;
                    if (doc.load_file(filename.c_str()))
                    {
                        for (pugi::xml_node prefab = doc.child("Prefab"); prefab; prefab = prefab.next_sibling("Prefab"))
                        {
                            if (prefab)
                            {
                                if (prefabId == prefab.attribute("id").as_string())
                                {
                                    e->load(prefab);
                                }
                            }
                        }
                    }
                }
                return e;
            });
        }
    }
}

void World::savePrefab(std::string const& filename, std::string const& prefabId, Entity::Ptr entity)
{
    // Prepare File
    pugi::xml_document doc;
    if (mCompressedFile)
    {
        lp::loadCompressedXml(filename,doc);
    }
    else
    {
        doc.load_file(filename.c_str());
    }

    // Remove Prefab with this id if already exist
    for (pugi::xml_node prefab = doc.child("Prefab"); prefab; prefab = prefab.next_sibling("Prefab"))
    {
        if (prefab.attribute("id").value() == prefabId)
        {
            doc.remove_child(prefab);
            break;
        }
    }

    // Save Prefab
    pugi::xml_node prefab = doc.append_child("Prefab");
    prefab.append_attribute("id") = prefabId.c_str();
    if (entity != nullptr)
    {
        entity->save(prefab);
    }

    // Save File
    if (mCompressedFile)
    {
        lp::saveCompressedXml(filename,doc);
    }
    else
    {
        doc.save_file(filename.c_str());
    }
}

Entity::Ptr World::execPrefab(std::string const& id)
{
    auto itr = mPrefabs.find(id);
    if (itr != mPrefabs.end())
    {
        if (itr->second)
        {
            Entity::Ptr e = itr->second();
            mPrefabInstanceCounter[id]++;
            return e;
        }
    }
    return nullptr;
}

std::size_t World::getPrefabInstanceCount(std::string const& id)
{
    return mPrefabInstanceCounter[id];
}

void World::setGravity(b2Vec2 gravity)
{
    mWorld.SetGravity(gravity);
}

b2Vec2 World::getGravity() const
{
    return mWorld.GetGravity();
}

void World::render(sf::RenderTarget& target)
{
    mRenderTarget = &target;
    mWorld.DrawDebugData();
}

void World::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    if (mRenderTarget != nullptr)
    {
        sf::ConvexShape shape;
        shape.setPointCount(vertexCount);
        for (int32 i = 0; i < vertexCount; i++)
        {
            shape.setPoint(i,Physic::toSfml(vertices[i]));
        }
        shape.setFillColor(Physic::toSfml(color));
        mRenderTarget->draw(shape);
    }
}

void World::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    if (mRenderTarget != nullptr)
    {
        sf::ConvexShape shape;
        shape.setPointCount(vertexCount);
        for (int32 i = 0; i < vertexCount; i++)
        {
            shape.setPoint(i,Physic::toSfml(vertices[i]));
        }
        shape.setFillColor(Physic::toSfml(color));
        mRenderTarget->draw(shape);
    }
}

void World::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    if (mRenderTarget != nullptr)
    {
        sf::CircleShape shape;
        shape.setPosition(Physic::toSfml(center));
        shape.setRadius(Physic::metersToPixels(radius));
        shape.setFillColor(Physic::toSfml(color));
        mRenderTarget->draw(shape);
    }
}

void World::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    if (mRenderTarget != nullptr)
    {
        sf::CircleShape shape;
        shape.setPosition(Physic::toSfml(center));
        shape.setRadius(Physic::metersToPixels(radius));
        shape.setFillColor(Physic::toSfml(color));
        mRenderTarget->draw(shape);
    }
}

void World::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    if (mRenderTarget != nullptr)
    {
        sf::VertexArray line(sf::Lines,2);
        line[0].position = Physic::toSfml(p1);
        line[1].position = Physic::toSfml(p2);
        line[0].color = Physic::toSfml(color);
        line[1].color = Physic::toSfml(color);
        mRenderTarget->draw(line);
    }
}

void World::DrawTransform(const b2Transform& xf)
{
    // TODO : Find how to represent a transform in Box2D
}

bool World::load(std::string const& filename)
{
    // Load file
    pugi::xml_document doc;
    if (mCompressedFile) // Compressed
    {
        lp::loadCompressedXml(filename,doc);
    }
    else
    {
        if (!doc.load_file(filename.c_str()))
        {
            return false;
        }
    }

    // Load World
    pugi::xml_node world = doc.child("World");
    if (!world)
    {
        return false;
    }
    mWorld.SetGravity(b2Vec2(world.attribute("gravity-x").as_float(),world.attribute("gravity-y").as_float()));

    // Load Entities
    pugi::xml_node entities = doc.child("Entities");
    if (!entities)
    {
        return false;
    }
    for (pugi::xml_node entity = entities.child("Entity"); entity; entity = entity.next_sibling("Entity"))
    {
        std::string id = entity.attribute("id").value();
        Entity::Ptr e = instantiate(id);
        if (e != nullptr)
        {
            e->load(entity);
        }
    }

    return true;
}

void World::save(std::string const& filename)
{
    // Prepare File
    pugi::xml_document doc;
    if (mCompressedFile)
    {
        lp::loadCompressedXml(filename,doc);
    }
    else
    {
        doc.load_file(filename.c_str());
    }

    if (doc.child("World"))
    {
        doc.remove_child("World");
    }
    if (doc.child("Entities"))
    {
        doc.remove_child("Entities");
    }

    // Save World
    pugi::xml_node world = doc.append_child("World");
    world.append_attribute("gravity-x") = mWorld.GetGravity().x;
    world.append_attribute("gravity-y") = mWorld.GetGravity().y;

    // Save Entities
    pugi::xml_node entities = doc.append_child("Entities");
    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (!mEntities[i]->isMarkedForRemoval())
            {
                pugi::xml_node entity = entities.append_child("Entity");
                entity.append_attribute("id") = mEntities[i]->getId().c_str();
                mEntities[i]->save(entity);
            }
        }
    }

    // Save File
    if (mCompressedFile)
    {
        lp::saveCompressedXml(filename,doc);
    }
    else
    {
        doc.save_file(filename.c_str());
    }
}

void World::setCompression(bool compressedFile)
{
    mCompressedFile = compressedFile;
}

bool World::isCompressed() const
{
    return mCompressedFile;
}

} // namespace ses
