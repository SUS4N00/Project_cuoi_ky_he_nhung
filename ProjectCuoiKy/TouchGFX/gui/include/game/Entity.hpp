#pragma once
namespace game {

class Entity {
public:
    enum Type {
        PLAYER,
        DEATH_KNIGHT,
        GOBLIN,
        SMALL_SLIME,
        BIG_SLIME,
        SPELL_SCROLL,
        CHEST,
        DOOR,
        OPEN_DOOR,
        POTION,
        ROCK,
        NONE // Loại không xác định
    };
    Entity(Type type, int hp, int speed, bool canMove = false);
    virtual ~Entity() {}
    int getHP() const;
    int getSpeed() const;
    Type getType() const;
    void setHP(int hp);
    void setType(Type t) { type = t; }
    bool isMovable() const { return canMove; }
protected:
    Type type;
    int hp;
    int speed;
    bool canMove;
};

} // namespace game