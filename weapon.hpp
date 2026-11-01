#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
using namespace std;

enum weapon_type {
    NONE,
    SWORD,
    SHIELD
};

enum attribute {
    ATTACK,
    DEFENSE
};

class WEAPON {
    private:
    string c_name;
    weapon_type c_type;
    attribute c_attribute;
    float c_attribute_value;

    public:
    WEAPON(string name = "Sem arma", weapon_type type = NONE, float attribute_value = 0);
    ~WEAPON();

    string getWeaponName();
    weapon_type getWeaponType();
    attribute getWeaponAttribute();
    float getWeaponAttributeValue();
};

#endif