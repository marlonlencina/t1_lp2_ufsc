#include "npc.hpp"
#include "weapon.hpp"
#include <iostream>

NPC::NPC(
    string name, 
    float life, 
    float atk, 
    float def, 
    int id_unique_hero_power, 
    WEAPON equipped_weapon
){
    c_name = name;
    c_life = life >= 20 ? life : 20;
    c_attack = atk >= 20 ? atk : 20;
    c_defense = def >= 20 ? def : 20;
    c_is_alive = true;
    c_id_unique_hero_power = id_unique_hero_power;
    c_equipped_weapon = equipped_weapon;
}

NPC::~NPC(){};


void NPC::buff(){
    cout << "efeito de buff temporário ativado. contamos com vc!" << endl;
    c_attack += 5;
};

void NPC::showNpcData(){
    cout << "## Name: " << c_name << endl;
    cout << "## Life: " << c_life << endl; 
    cout << "## Attack: " << c_attack << endl; 
    cout << "## Defense: " << c_defense << endl; 
    cout << "## Alive: " << c_is_alive << endl; 
    cout << "## Hero: " << c_id_unique_hero_power << endl; 
    cout << "## Arma equipada: " << c_equipped_weapon.getWeaponName() << endl;
};

string NPC::getName(){
    return c_name;
};
float NPC::getLife(){
    return c_life;
};
float NPC::getDefense(){
    return c_defense;
};
float NPC::getAttack(){
    return c_attack;
};
bool NPC::getIsNpcAlive(){
    return c_is_alive;
};
bool NPC::getIsHero(){
    return c_id_unique_hero_power != -1;
};
int NPC::getHeroIdAttributes(){
    return c_id_unique_hero_power;
};

bool NPC::getHasEquippedWeapon(){
    return c_equipped_weapon.getWeaponType() != NONE;
};
weapon_type NPC::getEquippedWeaponType(){
    return c_equipped_weapon.getWeaponType();
};
float NPC::getEquippedWeaponValue(){
    return c_equipped_weapon.getWeaponAttributeValue();
};

attribute NPC::getEquippedWeaponAttribute(){
    return c_equipped_weapon.getWeaponAttribute();
};



void NPC::setName(string name){
    c_name = name;
};
void NPC::setLife(float life){
    c_life = life;
};
void NPC::setAttack(float attack){
    c_attack = attack;
};
void NPC::setDefense(float defense){
    c_defense = defense;
};
void NPC::setNpcIsAlive(bool is_alive){
    c_is_alive = is_alive;
};