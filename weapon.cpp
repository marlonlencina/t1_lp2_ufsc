#include "weapon.hpp"

WEAPON::WEAPON(string name, weapon_type type, float attribute_value){
    c_name = name;
    c_type = type;
    c_attribute = type == SWORD ? ATTACK : DEFENSE;
    c_attribute_value = attribute_value;
}

WEAPON::~WEAPON(){}

string WEAPON::getWeaponName(){
    return c_name;
}

weapon_type WEAPON::getWeaponType(){
    return c_type;
}

float WEAPON::getWeaponAttributeValue(){
    return c_attribute_value;
}

attribute WEAPON::getWeaponAttribute(){
    return c_attribute;
};
