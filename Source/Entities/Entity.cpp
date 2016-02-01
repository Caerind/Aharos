#include "Entity.hpp"
#include "World.hpp"

namespace ses
{

std::map<std::string,std::function<Component::Ptr()>> Entity::mComponentFactories;

Entity::Entity(std::string const& id) : mId(id)
{
    mBody = nullptr;
    mWorld = nullptr;
    mZ = 0.f;
    mMarkedForRemoval = false;
}

Entity::~Entity()
{
    mWorld = nullptr;
}

const std::string& Entity::getId() const
{
    return mId;
}

void Entity::setPosition(sf::Vector2f const& position)
{
    if (mBody != nullptr)
    {
        mBody->SetTransform(Physic::toBox2D(position),mBody->GetAngle());
    }
}

sf::Vector2f Entity::getPosition() const
{
    if (mBody != nullptr)
    {
        return Physic::toSfml(mBody->GetPosition());
    }
    return sf::Vector2f();
}

void Entity::setRotation(float rotation)
{
    if (mBody != nullptr)
    {
        mBody->SetTransform(mBody->GetPosition(),Physic::degToRad(rotation));
    }
}

float Entity::getRotation() const
{
    if (mBody != nullptr)
    {
        return Physic::radToDeg(mBody->GetAngle());
    }
    return 0.f;
}

void Entity::setPositionZ(float z)
{
    mZ = z;
}

float Entity::getPositionZ() const
{
    return mZ;
}

bool Entity::hasComponent(std::string const& componentId)
{
    return (mComponents.find(componentId) != mComponents.end());
}

bool Entity::hasComponents(ComponentFilter const& filter)
{
    return filter.passFilter(this);
}

void Entity::removeComponent(std::string const& componentId)
{
    auto itr = mComponents.find(componentId);
    if (itr != mComponents.end())
    {
        itr->second->mEntity = this;
        mComponents.erase(itr);
    }
    update();
}

void Entity::removeComponents()
{
    for (auto itr = mComponents.begin(); itr != mComponents.end(); itr++)
    {
        itr->second->mEntity = this;
        mComponents.erase(itr);
    }
    update();
}

std::size_t Entity::getComponentsCount() const
{
    return mComponents.size();
}

void Entity::remove()
{
    mMarkedForRemoval = true;
}

bool Entity::isMarkedForRemoval() const
{
    return mMarkedForRemoval;
}

void Entity::update()
{
    if (mWorld != nullptr)
    {
        mWorld->onEntityUpdate(mId);
    }
}

b2Body* Entity::getBody()
{
    return mBody;
}

void Entity::addFixture(b2FixtureDef fDef)
{
    if (mBody != nullptr)
    {
        mBody->CreateFixture(&fDef);
    }
}

bool Entity::hasFixture(std::string fName)
{
    // TODO : Has fixture
    return false;
}

void Entity::removeFixture(std::string fName)
{
    if (mBody != nullptr)
    {
        // TODO : Remove fixture
    }
}

void Entity::removeAllFixtures()
{
    if (mBody != nullptr)
    {
        // TODO : Remove all fixtures
    }
}

void Entity::load(pugi::xml_node& entity)
{
    if (mBody != nullptr)
    {
        // Load Body
        pugi::xml_node body = entity.child("Body");
        if (body)
        {
            mBody->SetType((b2BodyType)body.attribute("type").as_int());
            mBody->SetTransform(b2Vec2(body.attribute("pos-x").as_float(),body.attribute("pos-y").as_float()),body.attribute("angle").as_float());
            setPositionZ(body.attribute("pos-z").as_float());
            mBody->SetLinearVelocity(b2Vec2(body.attribute("vel-x").as_float(),body.attribute("vel-y").as_float()));
            mBody->SetAngularVelocity(body.attribute("vel-a").as_float());
            mBody->SetLinearDamping(body.attribute("damp").as_float());
            mBody->SetAngularDamping(body.attribute("adamp").as_float());
            mBody->SetSleepingAllowed(body.attribute("canSleep").as_bool());
            mBody->SetAwake(body.attribute("awake").as_bool());
            mBody->SetFixedRotation(body.attribute("fixedRot").as_bool());
            mBody->SetBullet(body.attribute("bullet").as_bool());
            mBody->SetActive(body.attribute("active").as_bool());
            mBody->SetGravityScale(body.attribute("gScale").as_float());
        }

        // Load Fixtures
        for (pugi::xml_node fixture = entity.child("Fixture"); fixture; fixture = fixture.next_sibling("Fixture"))
        {
            b2FixtureDef fd;
            // TODO : Fixture user data
			fd.friction = fixture.attribute("friction").as_float();
			fd.restitution = fixture.attribute("restitution").as_float();
			fd.density = fixture.attribute("density").as_float();
			fd.isSensor = fixture.attribute("isSensor").as_bool();
			fd.filter.categoryBits = fixture.attribute("f-cBits").as_uint();
			fd.filter.maskBits = fixture.attribute("f-mBits").as_uint();
			fd.filter.groupIndex = fixture.attribute("f-gIndex").as_int();

            switch ((b2Shape::Type)fixture.attribute("type").as_uint())
            {
                case b2Shape::e_circle:
                {
                    b2CircleShape s;
                    s.m_p.x = fixture.attribute("pos-x").as_float();
                    s.m_p.y = fixture.attribute("pos-y").as_float();
                    s.m_radius = fixture.attribute("radius").as_float();
                    fd.shape = &s;
                    mBody->CreateFixture(&fd);
                } break;
                case b2Shape::e_edge:
                {
                    b2EdgeShape s;
                    s.m_hasVertex0 = fixture.attribute("has0").as_bool();
                    s.m_hasVertex3 = fixture.attribute("has3").as_bool();
                    s.m_vertex0.x = fixture.attribute("x0").as_float();
                    s.m_vertex0.y = fixture.attribute("y0").as_float();
                    s.m_vertex1.x = fixture.attribute("x1").as_float();
                    s.m_vertex1.y = fixture.attribute("y1").as_float();
                    s.m_vertex2.x = fixture.attribute("x2").as_float();
                    s.m_vertex2.y = fixture.attribute("y2").as_float();
                    s.m_vertex3.x = fixture.attribute("x3").as_float();
                    s.m_vertex3.y = fixture.attribute("y3").as_float();
                    fd.shape = &s;
                    mBody->CreateFixture(&fd);
                } break;
                case b2Shape::e_polygon:
                {
                    b2Vec2 vertices[b2_maxPolygonVertices];
                    int numVertices = fixture.attribute("count").as_int();
                    for (int i = 0; i < numVertices; i++)
                    {
                        std::string x = "x" + std::to_string(i), y = "y" + std::to_string(i);
                        vertices[i].x = fixture.attribute(x.c_str()).as_float();
                        vertices[i].y = fixture.attribute(y.c_str()).as_float();
                    }
                    b2PolygonShape s;
                    s.Set(vertices,numVertices);
                    fd.shape = &s;
                    mBody->CreateFixture(&fd);
                } break;
                case b2Shape::e_chain:
                {
                    b2Vec2 vertices[b2_maxPolygonVertices];
                    int numVertices = fixture.attribute("count").as_int();
                    for (int i = 0; i < numVertices; i++)
                    {
                        std::string x = "x" + std::to_string(i), y = "y" + std::to_string(i);
                        vertices[i].x = fixture.attribute(x.c_str()).as_float();
                        vertices[i].y = fixture.attribute(y.c_str()).as_float();
                    }
                    b2ChainShape s;
                    s.CreateChain(vertices,numVertices);
                    if (fixture.attribute("hasPrev").as_bool())
                    {
                        s.SetPrevVertex(b2Vec2(fixture.attribute("prev-x").as_float(),fixture.attribute("prev-y").as_float()));
                    }
                    if (fixture.attribute("hasNext").as_bool())
                    {
                        s.SetPrevVertex(b2Vec2(fixture.attribute("next-x").as_float(),fixture.attribute("next-y").as_float()));
                    }
                    fd.shape = &s;
                    mBody->CreateFixture(&fd);
                } break;
                default: break;
            }
        }
    }

    // Load Components
    for (pugi::xml_node component = entity.child("Component"); component; component = component.next_sibling("Component"))
    {
        std::string id = component.attribute("id").value();

        auto found = mComponentFactories.find(id);
        if (found != mComponentFactories.end())
        {
            mComponents[id] = found->second();
            mComponents[id]->mEntity = this;
            mComponents[id]->load(component);
        }
        else
        {
            std::cerr << "Component type (" << id << ") hasn't been registered !" << std::endl;
        }
    }
    update();
}

void Entity::save(pugi::xml_node& entity)
{
    if (mBody != nullptr)
    {
        // Save Body
        pugi::xml_node body = entity.append_child("Body");
        body.append_attribute("type") = mBody->GetType();
        body.append_attribute("pos-x") = mBody->GetPosition().x;
        body.append_attribute("pos-y") = mBody->GetPosition().y;
        body.append_attribute("pos-z") = getPositionZ();
        body.append_attribute("angle") = mBody->GetAngle();
        body.append_attribute("vel-x") = mBody->GetLinearVelocity().x;
        body.append_attribute("vel-y") = mBody->GetLinearVelocity().y;
        body.append_attribute("vel-a") = mBody->GetAngularVelocity();
        body.append_attribute("damp") = mBody->GetLinearDamping();
        body.append_attribute("adamp") = mBody->GetAngularDamping();
        body.append_attribute("canSleep") = mBody->IsSleepingAllowed();
        body.append_attribute("awake") = mBody->IsAwake();
        body.append_attribute("fixedRot") = mBody->IsFixedRotation();
        body.append_attribute("bullet") = mBody->IsBullet();
        body.append_attribute("active") = mBody->IsActive();
        body.append_attribute("gScale") = mBody->GetGravityScale();
        // Save Fixtures
        for (b2Fixture* f = mBody->GetFixtureList(); f; f = f->GetNext())
        {
            pugi::xml_node fixture = entity.append_child("Fixture");
            // TODO : Fixture user data
            fixture.append_attribute("friction") = f->GetFriction();
            fixture.append_attribute("restitution") = f->GetRestitution();
            fixture.append_attribute("density") = f->GetDensity();
            fixture.append_attribute("isSensor") = f->IsSensor();
            fixture.append_attribute("f-cBits") = f->GetFilterData().categoryBits;
            fixture.append_attribute("f-mBits") = f->GetFilterData().maskBits;
            fixture.append_attribute("f-gIndex") = f->GetFilterData().groupIndex;

            if (f->GetShape() != nullptr)
            {
                fixture.append_attribute("type") = f->GetShape()->GetType();
                switch (f->GetShape()->GetType())
                {
                    case b2Shape::e_circle:
                    {
                        b2CircleShape* s = (b2CircleShape*)f->GetShape();
                        fixture.append_attribute("pos-x") = s->m_p.x;
                        fixture.append_attribute("pos-y") = s->m_p.y;
                        fixture.append_attribute("radius") = s->m_radius;
                    } break;
                    case b2Shape::e_edge:
                    {
                        b2EdgeShape* s = (b2EdgeShape*)f->GetShape();
                        fixture.append_attribute("has0") = s->m_hasVertex0;
                        fixture.append_attribute("has3") = s->m_hasVertex3;
                        fixture.append_attribute("x0") = s->m_vertex0.x;
                        fixture.append_attribute("y0") = s->m_vertex0.y;
                        fixture.append_attribute("x1") = s->m_vertex1.x;
                        fixture.append_attribute("y1") = s->m_vertex1.y;
                        fixture.append_attribute("x2") = s->m_vertex2.x;
                        fixture.append_attribute("y2") = s->m_vertex2.y;
                        fixture.append_attribute("x3") = s->m_vertex3.x;
                        fixture.append_attribute("y3") = s->m_vertex3.y;
                    } break;
                    case b2Shape::e_polygon:
                    {
                        b2PolygonShape* s = (b2PolygonShape*)f->GetShape();
                        fixture.append_attribute("count") = s->m_count;
                        for (int i = 0; i < s->m_count; i++)
                        {
                            std::string x = "x" + std::to_string(i), y = "y" + std::to_string(i);
                            fixture.append_attribute(x.c_str()) = s->m_vertices[i].x;
                            fixture.append_attribute(y.c_str()) = s->m_vertices[i].y;
                        }
                    } break;
                    case b2Shape::e_chain:
                    {
                        b2ChainShape* s = (b2ChainShape*)f->GetShape();
                        fixture.append_attribute("count") = s->m_count;
                        for (int i = 0; i < s->m_count; i++)
                        {
                            std::string x = "x" + std::to_string(i), y = "y" + std::to_string(i);
                            fixture.append_attribute(x.c_str()) = s->m_vertices[i].x;
                            fixture.append_attribute(y.c_str()) = s->m_vertices[i].y;
                        }
                        fixture.append_attribute("prev-x") = s->m_prevVertex.x;
                        fixture.append_attribute("prev-y") = s->m_prevVertex.y;
                        fixture.append_attribute("next-x") = s->m_nextVertex.x;
                        fixture.append_attribute("next-y") = s->m_nextVertex.y;
                        fixture.append_attribute("hasPrev") = s->m_hasPrevVertex;
                        fixture.append_attribute("hasNext") = s->m_hasNextVertex;
                    }
                    break;
                    default: break;
                }
            }
        }
    }

    // Save Components
    for (auto itr = mComponents.begin(); itr != mComponents.end(); itr++)
    {
        if (itr->second != nullptr)
        {
            pugi::xml_node component = entity.append_child("Component");
            component.append_attribute("id") = itr->first.c_str();
            itr->second->save(component);
        }
    }
}

} // namespace ses
