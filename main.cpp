// ALUNOS: Marlon Lencina Boeira (26104785), Joao Gabriel Ramos de Souza (26102524)

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "npc.hpp"
#include "weapon.hpp"

using namespace std;

struct special_unique_hero_power {
    int id;
    string name;
    string attribute;
    float value;
};

vector<special_unique_hero_power> hero_powers_catalog = {
        {0, "Fúria Divina", "attack", 15.0f},
        {1, "Escudo Arcano", "defense", 20.0f}
};

vector<WEAPON> weapon_catalog = {
        WEAPON("Espada de Ferro", SWORD, 8.0),
        WEAPON("Espada Longa",    SWORD, 12.0),
        WEAPON("Escudo de Madeira", SHIELD, 6.0),
        WEAPON("Escudo de Aço",     SHIELD, 10.0)
};

void generateRandomNPCs(int quantity, vector<NPC> &vector){
    for(int i = 0; i < quantity; i++){
        string random_name = "NPC ";
        string index_string = to_string(i+1);
        random_name.append(index_string);

        float random_life = rand() % 100;
        float random_attack = rand() % 100;
        float random_defense = rand() % 100;

        NPC New_random_npc(random_name, random_life, random_attack, random_defense);
        vector.push_back(New_random_npc);
    };
}

void showAllNpcFromVector(vector<NPC> &vector){
    for(int i = 0; i < vector.size(); i++){
        vector.at(i).showNpcData();
    };
}

int quantityTeamMembersAlive(vector<NPC> &v1){
    int quantity = 0;
    for(int i = 0; i < v1.size(); i++){
        if(v1.at(i).getIsNpcAlive()){
            quantity++;
        }
    }
    return quantity;
}

int getRandomAliveNPCIndex(vector<NPC>& v){
    vector<int> alive_idx;
    for(size_t i = 0; i < v.size(); i++){
        if(v.at(i).getIsNpcAlive()){
            alive_idx.push_back(i);
        }
    }

    if(alive_idx.empty()){
    return -1;
    }

    return alive_idx.at(rand() % alive_idx.size());
}

void attackDamageLogic(NPC &Attack, NPC &Target){
            cout << ">> Atacante: " << Attack.getName() << endl;
            cout << ">> Defensor: " << Target.getName() << endl;

            bool attack_is_a_hero = Attack.getIsHero();
            bool defense_is_a_hero = Target.getIsHero();

            float attack  = Attack.getAttack();
            float defense = Target.getDefense();

            if(Attack.getHasEquippedWeapon()){
                if(Attack.getEquippedWeaponAttribute() == ATTACK){
                    cout << ">> Ataque aumentado por arma equipada. " << endl;
                    attack += Attack.getEquippedWeaponValue();
                }
            }

            if(Target.getHasEquippedWeapon()){
                if(Target.getEquippedWeaponAttribute() == DEFENSE){
                    cout << ">> Defesa aumentada por arma equipada. " << endl;
                    defense += Target.getEquippedWeaponValue();
                }
            }

            if(attack_is_a_hero){
                string attribute = hero_powers_catalog.at(Attack.getHeroIdAttributes()).attribute;
                if(attribute == "attack"){
                    cout << ">> O atacante é um herói - Buff de ATK ativo: +" << hero_powers_catalog.at(Attack.getHeroIdAttributes()).value  << endl;

                    attack += hero_powers_catalog.at(Attack.getHeroIdAttributes()).value;
                }
            }

            if(defense_is_a_hero){
                string attribute = hero_powers_catalog.at(Target.getHeroIdAttributes()).attribute;
                if(attribute == "defense"){
                    cout << ">> O defensor é um herói - Buff de DEF ativo: +" << hero_powers_catalog.at(Target.getHeroIdAttributes()).value << endl;

                    defense += hero_powers_catalog.at(Target.getHeroIdAttributes()).value;
                }
            }

            float damage  = attack - defense;

            cout << ">> Dano calculado: " << damage << endl;

            if(damage < 0){
                float reversed_damage = -damage;
                float attacker_life = Attack.getLife() - reversed_damage;
                Attack.setLife(attacker_life);
                cout << ">> Atacante executou ataque falho. Seu stats de ATQ < DEF, por isso receberá dano reverso:  " << reversed_damage << endl;

                if(attacker_life <= 0){
                    cout << ">> Atacante " << Attack.getName() << " foi morto durante execução do ataque" << endl;
                    Attack.setNpcIsAlive(false);
                }
            } else {
                if(damage == 0){
                    cout << "## Atenção: Pela valentia em batalha o atacante recebeu um Buff temporário." << endl;
                    Attack.buff();
                }
                cout << ">> Atacante causou dano ao oponente: " << damage << endl;
                float target_life = Target.getLife() - damage;
                Target.setLife(target_life);

                if(target_life <= 0){
                    Target.setNpcIsAlive(false);
                    cout << ">> " << Target.getName() << " morreu durante batalha." << endl;
                }
            }
}

void attackDamageLogicCritical(NPC &Attack, vector<NPC>& v){
    cout << "## O ATAQUE CRITÍCO, ATINGIRÁ TODOS OPONENTES NO CAMPO DE BATALHA!" << endl; 
    cout << ">> " << Attack.getName() << " executará um ataque crítico a todos oponentes no campo de batalha." << endl; 

    int critical_additional = (rand() % 20) + 1;
    float attack  = Attack.getAttack() + critical_additional;

    if(Attack.getIsHero()){
                string attribute = hero_powers_catalog.at(Attack.getHeroIdAttributes()).attribute;
                if(attribute == "attack"){
                    attack += hero_powers_catalog.at(Attack.getHeroIdAttributes()).value;
                    cout << ">> O atacante é um herói - Buff de ATK ativo: +" << hero_powers_catalog.at(Attack.getHeroIdAttributes()).value  << endl;
                }
    }

    if(Attack.getHasEquippedWeapon()){
        if(Attack.getEquippedWeaponAttribute() == ATTACK){
            cout << ">> Ataque aumentado por arma equipada. " << endl;
            attack += Attack.getEquippedWeaponValue();
        }
    }

    cout << ">> Ataque total calculado: " << attack << endl; 


    for(size_t i = 0; i < v.size(); i++){
        if(v.at(i).getIsNpcAlive()){
            float defense_target = v.at(i).getDefense();
            if(v.at(i).getIsHero()){
                string attribute = hero_powers_catalog.at(v.at(i).getHeroIdAttributes()).attribute;
                if(attribute == "defense"){
                    defense_target += hero_powers_catalog.at(v.at(i).getHeroIdAttributes()).value;
                    cout << ">> O defensor é um herói - Buff de DEF ativo: +" << hero_powers_catalog.at(v.at(i).getHeroIdAttributes()).value << endl;

                }
            }

            if(v.at(i).getHasEquippedWeapon()){
                if(v.at(i).getEquippedWeaponAttribute() == DEFENSE){
                    cout << ">> Defesa aumentada por arma equipada. " << endl;
                    defense_target += v.at(i).getEquippedWeaponValue();
                }
            }

            float damage = attack - defense_target;
            cout << ">> Dano real: " << damage << " - aplicado a: " << v.at(i).getName() << endl; 


            if(damage < 0){
                cout << ">> Seu ataque é falho, mas você não receberá dano reverso. (Crítico BUFF)" << endl;
            } else {
                cout << ">> seu ataque causou dano ao oponente: " << damage << endl;
                float target_life = v.at(i).getLife() - damage;
                v.at(i).setLife(target_life);

                if(target_life <= 0){
                    v.at(i).setNpcIsAlive(false);
                    cout << ">> " << v.at(i).getName() << " morreu durante batalha." << endl;
                }
            }

        }
    }
}

void startMatch(vector<NPC>& v1, vector<NPC>& v2){

    int current_round = 1;
    int winner_team;
    int current_team_on_attack = rand() % 2;
    cout << ">> Time no modo ataque: " << current_team_on_attack << endl;

    int current_team_1_members_alive = quantityTeamMembersAlive(v1);
    int current_team_2_members_alive = quantityTeamMembersAlive(v2);

    while(current_team_1_members_alive > 0 && current_team_2_members_alive > 0){

        cout << ">> Turno iniciado: " << current_round << endl;

        int idx_team1 = getRandomAliveNPCIndex(v1);
        int idx_team2 = getRandomAliveNPCIndex(v2);
        int critical_odd = v1.at(idx_team1).getIsHero() ? (rand() % 100) + 1 : 0;

        if(critical_odd <= 10){
        cout << ">> Algo extraordinário aconteceu, um ataque crítico será disparado!" << endl;
        //critical-hit starts
            if(current_team_on_attack == 0){
                // TIME 1 ATACA CRÍTICO -> TIME 2 DEFENDE
                attackDamageLogicCritical(v1.at(idx_team1), v2);
                current_team_on_attack = 1;
            } else {
                // TIME 2 ATACA CRÍTICO -> TIME 1 DEFENDE
                attackDamageLogicCritical(v2.at(idx_team2), v1);
                current_team_on_attack = 0;
            }
        } else {
            if(current_team_on_attack == 0){
                // TIME 1 ATACA -> TIME 2 DEFENDE
                attackDamageLogic(v1.at(idx_team1), v2.at(idx_team2));
                current_team_on_attack = 1;
            } else {
                // TIME 2 ATACA -> TIME 1 DEFENDE
                attackDamageLogic(v2.at(idx_team2), v1.at(idx_team1));
                current_team_on_attack = 0;
            }
        }
        current_round++;

        current_team_1_members_alive = quantityTeamMembersAlive(v1);
        current_team_2_members_alive = quantityTeamMembersAlive(v2);

        cout << ">> NPCs do time 1 vivos: " << current_team_1_members_alive << endl;
        cout << ">> NPCs do time 2 vivos: " << current_team_2_members_alive << endl;
        cout << ">> Turno encerrado." << endl;
    }
    
    winner_team = (current_team_1_members_alive > 0) ? 1 : 2;

    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "A batalha foi encerrada." << endl << ">> TIME VENCEDOR: " << winner_team << " <<" <<  endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
}

vector<NPC> loadTeamFromTxt(string path){
    vector<NPC> npcs;
    ifstream file(path);

      if(!file.is_open()){
        cout << "Erro ao abrir o arquivo: " << path << endl;
        return npcs;
    }

    string line;

    if(!getline(file, line)){
        cout << "Arquivo vazio." << endl;
        return npcs;
    }

    int quantity = 0;
    try {
        quantity = stoi(line);
    } catch(...) {
        cout << "A primeira linha deve ser a quantidade de NPCs." << endl;
        return npcs;
    }

    while((int)npcs.size() < quantity && getline(file, line)){
    if(!line.empty() && line.back() == '\r'){
        line.pop_back();
    }
    if(line.empty()){
        continue;
    }

    bool is_hero = (line.find("(H)") != string::npos);

    int range_life = is_hero ? 999 : 100;
    int range_attack = is_hero ? 150 : 100;
    int range_defense = is_hero ? 150 : 100;

    float random_life    = rand() % range_life;
    float random_attack  = rand() % range_attack;
    float random_defense = rand() % range_defense;

    WEAPON equipped_weapon;
    int random_odd = (rand() % 100) + 1;
    int probability_to_have_a_weapon = 30;

    if(random_odd <= probability_to_have_a_weapon){
        int random_weapon_idx = rand() % weapon_catalog.size();
        equipped_weapon = weapon_catalog.at(random_weapon_idx);
    }

    npcs.push_back(
        NPC(
            line, 
            random_life, 
            random_attack,
            random_defense, 
            is_hero ? rand() % hero_powers_catalog.size() : -1,
            equipped_weapon
        )   
    );
}

    if(npcs.size() < quantity){
        cout << "Aviso: o arquivo declara " << quantity << " NPCs, mas só tem " << npcs.size() << " nomes." << endl;
    }

    return npcs;
}

int main(){
    cout << "Iniciando..." << endl;

    string path_for_teams = "./teams/";
    string path_extension = ".txt";

    string team_1_name = "";
    string team_2_name = "";

    cout << "Digite apenas o nome do time (Ex: humanos): " << endl;
    getline(cin, team_1_name);

    cout << "Digite apenas o nome do time (Ex: orcs): " << endl;
    getline(cin, team_2_name);

    string filepath_for_team_1 = "";
    string filepath_for_team_2 = "";
    filepath_for_team_1.append(path_for_teams).append(team_1_name).append(path_extension);
    filepath_for_team_2.append(path_for_teams).append(team_2_name).append(path_extension);

    srand(time(NULL));

    vector<NPC> team_one = loadTeamFromTxt(filepath_for_team_1);
    vector<NPC> team_two = loadTeamFromTxt(filepath_for_team_2);

    if(team_one.empty() || team_two.empty()){
        cout << "Um dos times está vazio;" << endl;
        exit(1);
    }

    showAllNpcFromVector(team_one);
    showAllNpcFromVector(team_two);

    startMatch(team_one, team_two);

    cout << "Fechando..." << endl;
    return 0;
}