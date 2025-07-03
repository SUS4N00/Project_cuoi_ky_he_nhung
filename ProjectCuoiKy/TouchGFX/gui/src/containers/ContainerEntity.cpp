#include <gui/containers/ContainerEntity.hpp>
#include <touchgfx/Unicode.hpp>
#include <images/BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/hal/HAL.hpp>

using namespace game;

ContainerEntity::ContainerEntity() {}

void ContainerEntity::initialize()
{
    ContainerEntityBase::initialize();
    textHP.setVisible(true);
    avatar.setVisible(true);
}

void ContainerEntity::setHPText(int hp_)
{
    hp = hp_;
    Unicode::snprintf(hpBuffer, 10, "%d", hp);
    textHP.setWildcard(hpBuffer);
    textHP.invalidate();
}

void ContainerEntity::setAvatar(Entity::Type type)
{
    avatarType = type;
    switch (type)
    {
    case Entity::BIG_SLIME:
        avatar.setBitmap(Bitmap(BITMAP_BIG_SLIME_ID));
        break;
    case Entity::SMALL_SLIME:
        avatar.setBitmap(Bitmap(BITMAP_SMALL_SLIME_ID));
        break;
    case Entity::GOBLIN:
        avatar.setBitmap(Bitmap(BITMAP_GOBLIN_ID));
        break;
    case Entity::DEATH_KNIGHT:
        avatar.setBitmap(Bitmap(BITMAP_DEATH_KNIGHT_ID));
        break;
    case Entity::PLAYER:
        avatar.setBitmap(Bitmap(BITMAP_PLAYER_ID));
        break;
    case Entity::ROCK:
        avatar.setBitmap(Bitmap(BITMAP_ROCK_ID));
        break;
    case Entity::DOOR:
        avatar.setBitmap(Bitmap(BITMAP_CLOSED_DOOR_ID));
        break;
    case Entity::OPEN_DOOR:
        avatar.setBitmap(Bitmap(BITMAP_OPENED_DOOR_ID));
        break;
    case Entity::SPELL_SCROLL:
        avatar.setBitmap(Bitmap(BITMAP_SPELL_ID));
        break;
    case Entity::CHEST:
        avatar.setBitmap(Bitmap(BITMAP_CHEST_ID));
        break;
    case Entity::POTION:
        avatar.setBitmap(Bitmap(BITMAP_POTION_ID));
        break;
    default:
        avatar.setBitmap(Bitmap());
        break;
    }
    avatar.invalidate();
}

void ContainerEntity::setVisible(bool visible)
{
    ContainerEntityBase::setVisible(visible);
}

void ContainerEntity::showDamageTaken(int damage)
{
    Unicode::snprintf(textDamTakenBuffer, TEXTDAMTAKEN_SIZE, "-%d", damage);
    textDamTaken.setWildcard(textDamTakenBuffer);
    textDamTaken.setVisible(true);
    textDamTaken.setAlpha(255);
    textDamTaken.invalidate();
    textDamTaken.startFadeAnimation(0, 20, touchgfx::EasingEquations::linearEaseNone);
}

void ContainerEntity::fadeInAvatar(uint8_t duration)
{
    avatar.setAlpha(0);
    avatar.invalidate();
    avatar.startFadeAnimation(255, duration, touchgfx::EasingEquations::linearEaseNone);
}
