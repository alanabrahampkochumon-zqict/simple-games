#include "IDGen.h"
#include "Registry.h"

// TODO: Only for testing. Remove after use

struct MoveComponent
{
    float velocity, acceleration;
};

struct PositionComponent
{
    float x, y, z;
};

struct PhysicsComponent
{
    float gravity, friction;
};

int main()
{
    const u_ecs::Registry registry;
    const u_ecs::Entity car = 12;

    registry.add(car, PhysicsComponent{ .gravity = 9.2f, .friction = 1.2f });
    auto physicsComps = registry.get<PhysicsComponent>(car);
    auto pc           = registry.getAll<PhysicsComponent>();

    const auto id = u_ecs::IDGen::generate<Component>();
}
