#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

class NPC {
    private:
    string c_name;
    float c_life, c_attack, c_defense;
    bool c_is_alive, c_is_hero;

    public:
    NPC(string name, float life=20, float atk=20, float def=20, bool is_alive = true, bool is_hero = false){
        c_name = name;
        c_life = life;
        c_attack = atk;
        c_defense = def;
        c_is_alive = is_alive;
        c_is_hero = is_hero;
    };
    ~NPC(){};

    void attack(){};

    void buff(){
        cout << "efeito de buff temporário ativado. contamos com vc!" << endl;
        c_attack+=5;
    ;}

    void showNpcData(){
        cout << "Name: " << c_name << endl;
        cout << "Life: " << c_life << endl;
        cout << "ATK: " << c_attack << endl;
        cout << "DEF: " << c_defense << endl;
        cout << "status (is_alive): " << c_is_alive << endl;
        cout << "status (is_hero): " << c_is_hero << endl;
    };

    string getName(){
        return c_name;
    };
    float getLife(){
        return c_life;
    };
    float getDefense(){
        return c_defense;
    };
    float getAttack(){
        return c_attack;
    };
    bool getIsNpcAlive(){
        return c_is_alive;
    };

    void setName(string name){
        c_name = name;
    }
    void setLife(float life){
        c_life = life;
    };
    void setAttack(float attack){
        c_attack = attack;
    };
    void setDefense(float defense){
        c_defense = defense;
    };
    void setNpcIsAlive(bool is_alive){
        c_is_alive = is_alive;
    };

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

int quantityTeamMembersAlive(vector<NPC> v1){
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

void startMatch(vector<NPC>& v1, vector<NPC>& v2){

    int current_round = 0;
    int winner_team = 0;
    int current_team_on_attack = rand() % 2;
    int current_team_1_members_alive = quantityTeamMembersAlive(v1);
    int current_team_2_members_alive = quantityTeamMembersAlive(v2);

    while(current_team_1_members_alive > 0 && current_team_2_members_alive > 0){

        // índice sorteado em cada time (independente de quem ataca)
        int idx_team1 = getRandomAliveNPCIndex(v1);
        int idx_team2 = getRandomAliveNPCIndex(v2);

        cout << "O round atual é: " << current_round << endl;
        cout << "NPC sorteado do time 1: " << idx_team1 << endl;
        cout << "NPC sorteado do time 2: " << idx_team2 << endl;
        cout << "NPCS vivos team 1: " << current_team_1_members_alive << endl;
        cout << "NPCS vivos team 2: " << current_team_2_members_alive << endl;

        if(current_team_on_attack == 0){
            // TIME 1 ATACA -> TIME 2 DEFENDE
            float attack  = v1.at(idx_team1).getAttack();
            float defense = v2.at(idx_team2).getDefense();
            float damage  = attack - defense;

            if(damage < 0){
                cout << "seu ataque é fraco. nao surtiu efeito. você recebera o dano!" << endl;
                float reversed_damage = -damage;
                float attacker_life = v1.at(idx_team1).getLife() - reversed_damage;
                v1.at(idx_team1).setLife(attacker_life);

                if(attacker_life <= 0){
                    v1.at(idx_team1).setNpcIsAlive(false);
                }
            } else {
                if(damage == 0){
                    v1.at(idx_team1).buff();
                }
                cout << "seu ataque causou dano ao oponente: " << damage << endl;
                float target_life = v2.at(idx_team2).getLife() - damage;
                v2.at(idx_team2).setLife(target_life);

                if(target_life <= 0){
                    v2.at(idx_team2).setNpcIsAlive(false);
                }
            }

            current_team_on_attack = 1;

        } else {
            // TIME 2 ATACA -> TIME 1 DEFENDE
            float attack  = v2.at(idx_team2).getAttack();
            float defense = v1.at(idx_team1).getDefense();
            float damage  = attack - defense;

            if(damage < 0){
                cout << "seu ataque é fraco. nao surtiu efeito. você recebera o dano!" << endl;
                float reversed_damage = -damage;
                float attacker_life = v2.at(idx_team2).getLife() - reversed_damage;
                v2.at(idx_team2).setLife(attacker_life);

                if(attacker_life <= 0){
                    v2.at(idx_team2).setNpcIsAlive(false);
                }
            } else {
                if(damage == 0){
                    v2.at(idx_team2).buff();
                }
                cout << "seu ataque causou dano ao oponente: " << damage << endl;
                float target_life = v1.at(idx_team1).getLife() - damage;
                v1.at(idx_team1).setLife(target_life);

                if(target_life <= 0){
                    v1.at(idx_team1).setNpcIsAlive(false);
                }
            }

            current_team_on_attack = 0;
        }

        current_team_1_members_alive = quantityTeamMembersAlive(v1);
        current_team_2_members_alive = quantityTeamMembersAlive(v2);
        current_round++;

        winner_team = (current_team_1_members_alive > 0) ? 1 : 2;
    }

    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "o time vencedor é o: " << winner_team << endl;
    cout << "time 1: -----------------------------------" << endl;
    showAllNpcFromVector(v1);
    cout << "time 2: -----------------------------------" << endl;
    showAllNpcFromVector(v2);

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

    float random_life    = rand() % 100;
    float random_attack  = rand() % 100;
    float random_defense = rand() % 100;

    bool is_hero = (line.find("(H)") != string::npos);

    npcs.push_back(NPC(line, random_life, random_attack, random_defense, true, is_hero));
}

    if(npcs.size() < quantity){
        cout << "Aviso: o arquivo declara " << quantity << " NPCs, mas só tem " << npcs.size() << " nomes." << endl;
    }

    return npcs;
}

int main(){
    cout << "Iniciando..." << endl;

    string path_for_teams = "./teams";
    
    srand(time(NULL));

    vector<NPC> team_one = loadTeamFromTxt("./teams/t1.txt");
    vector<NPC> team_two = loadTeamFromTxt("./teams/ig.txt");
    showAllNpcFromVector(team_one);
    showAllNpcFromVector(team_two);

    startMatch(team_one, team_two);

    cout << "Fechando..." << endl;
    return 0;
}