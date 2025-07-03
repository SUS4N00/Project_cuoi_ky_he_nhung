#ifndef CONTAINERENTITY_HPP
#define CONTAINERENTITY_HPP

#include <gui_generated/containers/ContainerEntityBase.hpp>
#include <game/Entity.hpp>

class ContainerEntity : public ContainerEntityBase
{
public:
    ContainerEntity();
    virtual ~ContainerEntity() {}

    virtual void initialize();
    void setHPText(int hp);
    void setAvatar(game::Entity::Type type);
    void setVisible(bool visible);
    // Getter cho logic di chuyển UI
    game::Entity::Type getAvatarType() const { return avatarType; }
    int getHP() const { return hp; }
    int getSpeed() const { return speed; } // Thêm getter cho speed
    void setSpeed(int s) { speed = s; }   // Thêm setter cho speed
    int getAttack() const { return attack; }
    void setAttack(int a) { attack = a; }
    void showDamageTaken(int damage);
    void fadeInAvatar(uint8_t duration = 20); // Thêm hàm public để fade avatar

private:
    Unicode::UnicodeChar hpBuffer[10];
    Unicode::UnicodeChar damageTakenBuffer[10];
    game::Entity::Type avatarType = game::Entity::NONE;
    int hp = 0;
    int speed = 1; // Thêm thuộc tính speed, mặc định 1
    int attack = 0; // Thêm thuộc tính attack
    // Thêm textDamageTaken để hiển thị hiệu ứng fade
    TextArea textDamageTaken;
};

#endif // CONTAINERENTITY_HPP
