#ifndef NPC_HPP
#define NPC_HPP

#include <vector>
#include <string>
#include "weapon.hpp"

using namespace std;

class NPC {
    private:
    string c_name;
    float c_life, c_attack, c_defense;
    bool c_is_alive;
    int c_id_unique_hero_power;
    WEAPON c_equipped_weapon;
    

    public:
    NPC(string name, float life=20, float atk=20, float def=20, int id_unique_hero_power = -1, WEAPON equipped_weapon = WEAPON());
    ~NPC();

    void buff();

    void showNpcData();

    string getName();
    float getLife();
    float getDefense();
    float getAttack();
    bool getIsNpcAlive();
    bool getIsHero();
    int getHeroIdAttributes();

    bool getHasEquippedWeapon();
    weapon_type getEquippedWeaponType();
    float getEquippedWeaponValue();
    attribute getEquippedWeaponAttribute();


    void setName(string name);
    void setLife(float life);
    void setAttack(float attack);
    void setDefense(float defense);
    void setNpcIsAlive(bool is_alive);
};

#endif