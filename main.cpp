#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

#define map_dim 15
#define no_type_each 7
#define no_items 4

int noTotalAgents = 3 * no_type_each;

struct Punct
{
    int x, y;
};

class Agent
{
private:
    int damage;
    int health;
    int no;      //id unic
    int x, y;   //pozitia pe harta
    int type;  // nu a fost folosit
public:
    Agent();
    void setDamage(int d);
    void setHealth(int h);
    void setNo(int n);
    void setType(int t);
    void setXY(int a, int b);
    void setX(int a);
    void setY (int b);
    int getDamage();
    int getHealth();
    int getNo();
    int getType();
    int getX();
    int getY();
    virtual ~Agent()
    {

    }
    void attack(Agent &deAtacat);
    virtual Punct trajectory(string M[][map_dim]) = 0;  //returneaza pozitia unui agent de pe posibila traiectorie
    virtual Punct casual(string M[][map_dim]) = 0;      // daca nu gaseste un agent de atacat, se misca cu o pozitie intr-o directie random
};
    Agent::Agent()
    {
        damage = 20;
        health = 100;
    }
    void Agent::setDamage(int d)
    {
        damage = d;
    }
    void Agent::setHealth(int h)
    {
        health = h;
    }
    void Agent::setNo(int n)
    {
        no = n;
    }
    void Agent::setType(int t)
    {
        type = t;
    }
    void Agent::setXY(int a, int b)
    {
        x = a;
        y = b;
    }
    void Agent::setX(int a)
    {
        x = a;
    }
    void Agent::setY(int b)
    {
        y = b;
    }
    int Agent::getDamage()
    {
        return damage;
    }
    int Agent::getHealth()
    {
        return health;
    }
    int Agent::getNo()
    {
        return no;
    }
    int Agent::getType()
    {
        return type;
    }
    int Agent::getX()
    {
        return x;
    }
    int Agent::getY()
    {
        return y;
    }
    void Agent::attack(Agent &deAtacat)
    {
        deAtacat.setHealth(deAtacat.getHealth() - this->getDamage());
    }

class S : public Agent
{
  public:
    using Agent :: Agent;
    Punct trajectory(string M[][map_dim]);
    Punct casual(string M[][map_dim]);
};
    Punct S::trajectory(string M[][map_dim])
    {
        Punct p;
        for(int j = 0; j < map_dim; j++)
        {
            if(j == this->getY()) continue;
            if(M[this->getX()][j] == "S" || M[this->getX()][j] == "L" || M[this->getX()][j] == "W")
            {
                p.x = this->getX();
                p.y = j;
                return p;
            }
        }
        p.x = -1;
        p.y = -1;
        return p;
    }
    Punct S::casual(string M[][map_dim])
    {
        Punct p;
        p.x = this->getX();
        if(this->getY() + 1 > map_dim - 1)
        {
            p.y = this->getY() - 1;
            return p;
        }
        if(this->getY() - 1 < 0)
        {
            p.y = this->getY() + 1;
            return p;
        }
        srand((unsigned)time(0));
        int r = rand();
        if(r % 2 == 0)
        {
            p.y = this->getY() - 1;
            return p;

        }
        p.y = this->getY() + 1;
        return p;

    }
class L : public Agent
{
  public:
    using Agent :: Agent;
    Punct trajectory(string M[][map_dim]);
    Punct casual(string M[][map_dim]);
};
    Punct L::trajectory(string M[][map_dim])
    {
        Punct p;
        for(int i = 0; i < map_dim; i++)
        {
            if(i == this->getX()) continue;
            if(M[i][this->getY()] == "S" || M[i][this->getY()] == "L" || M[i][this->getY()] == "W")
            {
                p.x = i;
                p.y = this->getY();
                return p;
            }
        }
        p.x = -1;
        p.y = -1;
        return p;
    }
    Punct L::casual(string M[][map_dim])
    {
        Punct p;
        p.y = this->getY();
        if(this->getX() + 1 > map_dim - 1)
        {
            p.x = this->getX() - 1;
            return p;
        }
        if(this->getX() - 1 < 0)
        {
            p.x = this->getX() + 1;
            return p;
        }
        srand((unsigned)time(0));
        int r = rand();
        if(r % 2 == 0)
        {
            p.x = this->getX() - 1;
            return p;
        }
        p.x = this->getX() + 1;
        return p;
    }
class W : public Agent
{
  public:
    using Agent :: Agent;
    Punct trajectory(string M[][map_dim]);
    Punct casual(string M[][map_dim]);
};
    Punct W::trajectory(string M[][map_dim])
    {
        Punct p;

        int i = this->getX();
        int j = this->getY();
        while(i > 0 && j > 0)
        {
            i--;
            j--;
            if(M[i][j] == "S" || M[i][j] == "L" || M[i][j] == "W")
            {
                p.x = i;
                p.y = j;
                return p;
            }
        }
        i = this->getX();
        j = this->getY();
        while(i < map_dim - 1 && j < map_dim - 1)
        {
            i++;
            j++;
            if(M[i][j] == "S" || M[i][j] == "L" || M[i][j] == "W")
            {
                p.x = i;
                p.y = j;
                return p;
            }
        }
        p.x = -1;
        p.y = -1;
        return p;
    }
    Punct W::casual(string M[][map_dim])
    {
        Punct p;
        if(this->getX() == 0 || this->getY() == 0)
        {
            p.x = this->getX() + 1;
            p.y = this->getY() + 1;
            return p;
        }
        if(this->getX() == map_dim - 1 || this->getY() == map_dim - 1)
        {
            p.x = this->getX() - 1;
            p.y = this->getY() - 1;
            return p;
        }
        srand((unsigned)time(0));
        int r = rand();
        if(r % 2 == 0)
        {
            p.x = this->getX() - 1;
            p.y = this->getY() - 1;
            return p;
        }
        p.x = this->getX() + 1;
        p.y = this->getY() + 1;
        return p;
    }
class healthRestore
{
private:
    int bonus;
public:
    healthRestore();
    void setBonus(int b);
    int getBonus();
};
    healthRestore::healthRestore()
    {
        bonus = 100;
    }
    void healthRestore::setBonus(int b)
    {
        bonus = b;
    }
    int healthRestore::getBonus()
    {
        return bonus;
    }
class godsTree
{
private:
    int bonusHealth;
    int bonusDamage;
public:
    godsTree();
    void setBonusHealth(int b);
    int getBonusHealth();
    void setBonusDamage(int b);
    int getBonusDamage();
};
    godsTree::godsTree()
    {
        bonusHealth = 30;
        bonusDamage = 20;
    }
    void godsTree::setBonusHealth(int b)
    {
        bonusHealth = b;
    }
    int godsTree::getBonusHealth()
    {
        return bonusHealth;
    }
    void godsTree::setBonusDamage(int b)
    {
        bonusDamage = b;
    }
    int godsTree::getBonusDamage()
    {
        return bonusDamage;
    }
class gold
{
private:
    int bonusHealth;
    int bonusDamage;
public:
    gold();
    void setBonusHealth(int b);
    int getBonusHealth();
    void setBonusDamage(int b);
    int getBonusDamage();
};
    gold::gold()
    {
        bonusHealth = 30;
        bonusDamage = 20;
    }
    void gold::setBonusHealth(int b)
    {
        bonusHealth = b;
    }
    int gold::getBonusHealth()
    {
        return bonusHealth;
    }
    void gold::setBonusDamage(int b)
    {
        bonusDamage = b;
    }
    int gold::getBonusDamage()
    {
        return bonusDamage;
    }
class iceSword
{
private:
    int bonusHealth;
    int bonusDamage;
public:
    iceSword();
    void setBonusHealth(int b);
    int getBonusHealth();
    void setBonusDamage(int b);
    int getBonusDamage();
};
    iceSword::iceSword()
    {
        bonusHealth = 30;
        bonusDamage = 20;
    }
    void iceSword::setBonusHealth(int b)
    {
        bonusHealth = b;
    }
    int iceSword::getBonusHealth()
    {
        return bonusHealth;
    }
    void iceSword::setBonusDamage(int b)
    {
        bonusDamage = b;
    }
    int iceSword::getBonusDamage()
    {
        return bonusDamage;
    }

class Map
{
private:
    string M[map_dim][map_dim];

public:
    Map();
    void spawn();
    void printMap();
    void roundS(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers, int n);
    void roundL(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers, int n);
    void roundW(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers, int n);
    void command(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers);
};
    Map::Map()
    {
        for(int i = 0; i < map_dim; i++)
        for(int j = 0; j < map_dim; j++)
        M[i][j] = "~";
    }


    void Map::command(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers)
    {
        cout<<"BINE AI VENIT IN JOCUL GAME OF THRONES - SURVIVAL!"<<endl;
        cout<<"Aceasta este harta:"<<endl<<endl;
        printMap();
        cout<<endl<<"S -> Starks se pot misca pe orizontala -"<<endl<<"  -> t = GOD's TREE ii ofera 30 bonus health si 20 bonus damage"<<endl<<endl;
        cout<<"L -> Lannisters se pot misca pe verticala |"<<endl<<"  -> g = GOLD ii ofera 30 bonus health si 20 bonus damage"<<endl<<endl;
        cout<<"W -> White Walkers se pot misca pe diagonala backslash"<<endl<<"  -> i = ICE SWORD ii ofera 30 bonus health si 20 bonus damage"<<endl<<endl;
        cout<<"h -> Health Restore"<<endl<<endl;
        cout<<"Comenzile sunt urmatoarele: "<<endl<<"next -> urmatoarea runda"<<endl<<"map -> vezi harta"<<endl<<"end -> fast forward sfarsitul jocului"<<endl;
        string c;
        while(noTotalAgents > 0)
        {
            cout<<endl<<"Introduceti comanda: ";
            cin>>c;
            if(c == "map")
            {
                cout<<endl;
                printMap();
            }
            else if(c == "next")
            {
                cout<<endl;
                for(int i = 0; i < no_type_each; i++)
                {
                    if(starks[i].getX() >= 0)
                    {
                        roundS(M, starks, lannisters, white_walkers, i);
                    }
                    if(lannisters[i].getX() >= 0)
                    {
                        roundL(M, starks, lannisters, white_walkers, i);
                    }
                    if(white_walkers[i].getX() >= 0)
                    {
                        roundW(M, starks, lannisters, white_walkers, i);
                    }
                }
                if(noTotalAgents == 1)
                {
                    for(int i = 0; i < no_type_each; i++)
                    {
                        if(starks[i].getX() >= 0)
                        {
                            cout<<"S"<<starks[i].getNo()<<" ("<<starks[i].getX()<<", "<<starks[i].getY()<<") a castigat!";
                            break;
                        }
                        if(lannisters[i].getX() >= 0)
                        {
                            cout<<"L"<<lannisters[i].getNo()<<" ("<<lannisters[i].getX()<<", "<<lannisters[i].getY()<<") a castigat!";
                            break;
                        }
                        if(white_walkers[i].getX() >= 0)
                        {
                            cout<<"W"<<white_walkers[i].getNo()<<" ("<<white_walkers[i].getX()<<", "<<white_walkers[i].getY()<<") a castigat!";
                            break;
                        }
                    }
                    cout<<endl;
                    printMap();
                    cout<<endl<<"    ~~ THE END ~~"<<endl;
                    break;
                }
            }
            else if(c == "end")
            {
                int j = 1000;
                while(j > 0 && noTotalAgents > 1)
                {
                    for(int i = 0; i < no_type_each; i++)
                    {
                        if(starks[i].getX() >= 0)
                        {
                            roundS(M, starks, lannisters, white_walkers, i);
                        }
                        if(lannisters[i].getX() >= 0)
                        {
                            roundL(M, starks, lannisters, white_walkers, i);
                        }
                        if(white_walkers[i].getX() >= 0)
                        {
                            roundW(M, starks, lannisters, white_walkers, i);
                        }
                    }
                    j--;
                }
                if(j == 0)
                {
                    cout<<"Fiecare jucator a actionat de 1000 de ori. JOC OPRIT. Au mai ramas "<<noTotalAgents<<" in viata."<<endl;
                    cout<<endl;
                    printMap();
                    cout<<"Datorita modului de miscare si pozitiei, cei "<<noTotalAgents<<" nu se pot intalni."<<endl;
                    cout<<endl<<"    ~~ THE (peaceful) END ~~"<<endl;
                    break;
                }
                else
                {
                    for(int i = 0; i < no_type_each; i++)
                    {
                        if(starks[i].getX() >= 0)
                        {
                            cout<<"S"<<starks[i].getNo()<<" ("<<starks[i].getX()<<", "<<starks[i].getY()<<") a castigat!";
                            break;
                        }
                        if(lannisters[i].getX() >= 0)
                        {
                            cout<<"L"<<lannisters[i].getNo()<<" ("<<lannisters[i].getX()<<", "<<lannisters[i].getY()<<") a castigat!";
                            break;
                        }
                        if(white_walkers[i].getX() >= 0)
                        {
                            cout<<"W"<<white_walkers[i].getNo()<<" ("<<white_walkers[i].getX()<<", "<<white_walkers[i].getY()<<") a castigat!";
                            break;
                        }
                    }
                    cout<<endl;
                    printMap();
                    cout<<endl<<"    ~~ THE END ~~"<<endl;
                    break;
                }
            }
            else cout<<endl<<"Comanda Invalida";

        }

    }


    void Map::spawn()
    {
        int i, j, k = 0;
        vector <int> numbers;

        for(i = 0; i < map_dim * map_dim; i++)
            numbers.push_back(i);

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

        vector <S> starks;
        vector <L> lannisters;
        vector <W> white_walkers;
        S a;
        L b;
        W c;
        for(j = 0; j < no_type_each; j++)    //Spawn starks
        {
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "S";
            a.setXY(numbers[k] / map_dim, numbers[k] % map_dim);
            a.setType(1);
            a.setNo(k);
            starks.push_back(a);
            k++;
        }
        for(j = 0; j < no_type_each; j++)    //Spawn lannisters
        {
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "L";
            b.setXY(numbers[k] / map_dim, numbers[k] % map_dim);
            b.setType(2);
            b.setNo(k);
            lannisters.push_back(b);
            k++;
        }
        for(j = 0; j < no_type_each; j++)       //Spawn white walkers
        {
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "W";
            c.setXY(numbers[k] / map_dim, numbers[k] % map_dim);
            c.setType(3);
            c.setNo(k);
            white_walkers.push_back(c);
            k++;
        }
        for(j = 0; j < no_items; j++)           //Spawn items
        {
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "h";
            k++;
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "t";
            k++;
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "g";
            k++;
            M[numbers[k] / map_dim][numbers[k] % map_dim] = "i";
            k++;
        }
        command(M, starks, lannisters, white_walkers);
    }
    void Map::printMap()
    {
        for(int i = 0; i < map_dim; i++)
        {
            for(int j = 0; j < map_dim; j++)
                cout<<M[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
    void Map::roundS(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers, int n)
    {
        Punct p;
        p = starks[n].trajectory(M);
        if(p.x == -1)
        {
            p = starks[n].casual(M);
            M[starks[n].getX()][starks[n].getY()] = "~";
            cout<<"S"<<starks[n].getNo()<<" ("<<starks[n].getX()<<", "<<starks[n].getY()<<") s-a mutat pe pozitia ("<<p.x<<", "<<p.y<<") ";
            if(M[p.x][p.y] == "h")
            {
                healthRestore h;
                starks[n].setHealth(h.getBonus());
                cout<<"si a gasit un HEALTH RESTORE. Acum are health 100."<<endl;
            }
            else if(M[p.x][p.y] == "t")
            {
                godsTree t;
                starks[n].setHealth(starks[n].getHealth() + t.getBonusHealth());
                starks[n].setDamage(starks[n].getDamage() + t.getBonusDamage());
                cout<<"si a gasit un GOD'S TREE. Acum are health +30 si damage +20."<<endl;
            }
            cout<<endl<<endl;
            M[p.x][p.y] = "S";
            starks[n].setX(p.x);
            starks[n].setY(p.y);
        }
        else
        {
            int noAtacat, attacker = 0, attacked = 0;

            // Stark ataca Stark

            if(M[p.x][p.y] == "S")
            {
                cout<<endl<<"Un Stark ataca un alt Stark!"<<endl;
                for(int i = 0; i < starks.size(); i++)
                {
                    if(starks[i].getX() == p.x && starks[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"S"<<starks[n].getNo()<<" ("<<starks[n].getX()<<", "<<starks[n].getY()<<") il ataca pe S"<<starks[noAtacat].getNo()<<" ("<<starks[noAtacat].getX()<<", "<<starks[noAtacat].getY()<<")"<<endl;

                while(starks[n].getHealth() > 0 && starks[noAtacat].getHealth() > 0)
                {
                    starks[n].attack(starks[noAtacat]);
                    if(starks[noAtacat].getHealth() > 0)
                        starks[noAtacat].attack(starks[n]);
                    else attacker = 1;
                    if(starks[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[starks[noAtacat].getX()][starks[noAtacat].getY()] = "S";
                    M[starks[n].getX()][starks[n].getY()] = "~";
                    starks[n].setX(p.x);
                    starks[n].setY(p.y);
                    starks[noAtacat].setX(-2);
                    starks[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[starks[n].getX()][starks[n].getY()] = "~";
                    starks[n].setX(-2);
                    starks[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }

            // Stark ataca Lannister

            else if(M[p.x][p.y] == "L")
            {
                cout<<endl<<"Un Stark ataca un Lannister!"<<endl;
                for(int i = 0; i < lannisters.size(); i++)
                {
                    if(lannisters[i].getX() == p.x && lannisters[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"S"<<starks[n].getNo()<<" ("<<starks[n].getX()<<", "<<starks[n].getY()<<") il ataca pe L"<<lannisters[noAtacat].getNo()<<" ("<<lannisters[noAtacat].getX()<<", "<<lannisters[noAtacat].getY()<<")"<<endl;

                while(starks[n].getHealth() > 0 && lannisters[noAtacat].getHealth() > 0)
                {
                    starks[n].attack(lannisters[noAtacat]);
                    if(lannisters[noAtacat].getHealth() > 0)
                        lannisters[noAtacat].attack(starks[n]);
                    else attacker = 1;
                    if(starks[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[lannisters[noAtacat].getX()][lannisters[noAtacat].getY()] = "S";
                    M[starks[n].getX()][starks[n].getY()] = "~";
                    starks[n].setX(p.x);
                    starks[n].setY(p.y);
                    lannisters[noAtacat].setX(-2);
                    lannisters[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[starks[n].getX()][starks[n].getY()] = "~";
                    starks[n].setX(-2);
                    starks[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }

            //Stark ataca White Walker

            else if(M[p.x][p.y] == "W")
            {
                cout<<endl<<"Un Stark ataca un White Walker!"<<endl;
                for(int i = 0; i < white_walkers.size(); i++)
                {
                    if(white_walkers[i].getX() == p.x && white_walkers[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"S"<<starks[n].getNo()<<" ("<<starks[n].getX()<<", "<<starks[n].getY()<<") il ataca pe W"<<white_walkers[noAtacat].getNo()<<" ("<<white_walkers[noAtacat].getX()<<", "<<white_walkers[noAtacat].getY()<<")"<<endl;

                while(starks[n].getHealth() > 0 && white_walkers[noAtacat].getHealth() > 0)
                {
                    starks[n].attack(white_walkers[noAtacat]);
                    if(white_walkers[noAtacat].getHealth() > 0)
                        white_walkers[noAtacat].attack(starks[n]);
                    else attacker = 1;
                    if(starks[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[white_walkers[noAtacat].getX()][white_walkers[noAtacat].getY()] = "S";
                    M[starks[n].getX()][starks[n].getY()] = "~";
                    starks[n].setX(p.x);
                    starks[n].setY(p.y);
                    white_walkers[noAtacat].setX(-2);
                    white_walkers[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[starks[n].getX()][starks[n].getY()] = "~";
                    starks[n].setX(-2);
                    starks[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }
        }
    }

    void Map::roundL(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers, int n)
    {
        Punct p;
        p = lannisters[n].trajectory(M);
        if(p.x == -1)
        {
            p = lannisters[n].casual(M);
            M[lannisters[n].getX()][lannisters[n].getY()] = "~";
            cout<<"L"<<lannisters[n].getNo()<<" ("<<lannisters[n].getX()<<", "<<lannisters[n].getY()<<") s-a mutat pe pozitia ("<<p.x<<", "<<p.y<<") ";
            if(M[p.x][p.y] == "h")
            {
                healthRestore h;
                lannisters[n].setHealth(h.getBonus());
                cout<<"si a gasit un HEALTH RESTORE. Acum are health 100."<<endl;
            }
            else if(M[p.x][p.y] == "g")
            {
                gold g;
                lannisters[n].setHealth(lannisters[n].getHealth() + g.getBonusHealth());
                lannisters[n].setDamage(lannisters[n].getDamage() + g.getBonusDamage());
                cout<<"si a gasit GOLD. Acum are health +30 si damage +20."<<endl;
            }
            cout<<endl;
            cout<<endl;
            M[p.x][p.y] = "L";
            lannisters[n].setX(p.x);
            lannisters[n].setY(p.y);
        }
        else
        {
            int noAtacat, attacker = 0, attacked = 0;

            // Lannister ataca Stark

            if(M[p.x][p.y] == "S")
            {
                cout<<endl<<"Un Lannister ataca un Stark!"<<endl;
                for(int i = 0; i < starks.size(); i++)
                {
                    if(starks[i].getX() == p.x && starks[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"L"<<lannisters[n].getNo()<<" ("<<lannisters[n].getX()<<", "<<lannisters[n].getY()<<") il ataca pe S"<<starks[noAtacat].getNo()<<" ("<<starks[noAtacat].getX()<<", "<<starks[noAtacat].getY()<<")"<<endl;

                while(lannisters[n].getHealth() > 0 && starks[noAtacat].getHealth() > 0)
                {
                    lannisters[n].attack(starks[noAtacat]);
                    if(starks[noAtacat].getHealth() > 0)
                        starks[noAtacat].attack(lannisters[n]);
                    else attacker = 1;
                    if(lannisters[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[starks[noAtacat].getX()][starks[noAtacat].getY()] = "L";
                    M[lannisters[n].getX()][lannisters[n].getY()] = "~";
                    lannisters[n].setX(p.x);
                    lannisters[n].setY(p.y);
                    starks[noAtacat].setX(-2);
                    starks[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[lannisters[n].getX()][lannisters[n].getY()] = "~";
                    lannisters[n].setX(-2);
                    lannisters[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }

            // Lannister ataca Lannister

            else if(M[p.x][p.y] == "L")
            {
                cout<<endl<<"Un Lannister ataca un alt Lannister!"<<endl;
                for(int i = 0; i < lannisters.size(); i++)
                {
                    if(lannisters[i].getX() == p.x && lannisters[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"L"<<lannisters[n].getNo()<<" ("<<lannisters[n].getX()<<", "<<lannisters[n].getY()<<") il ataca pe L"<<lannisters[noAtacat].getNo()<<" ("<<lannisters[noAtacat].getX()<<", "<<lannisters[noAtacat].getY()<<")"<<endl;

                while(lannisters[n].getHealth() > 0 && lannisters[noAtacat].getHealth() > 0)
                {
                    lannisters[n].attack(lannisters[noAtacat]);
                    if(lannisters[noAtacat].getHealth() > 0)
                        lannisters[noAtacat].attack(lannisters[n]);
                    else attacker = 1;
                    if(lannisters[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[lannisters[noAtacat].getX()][lannisters[noAtacat].getY()] = "L";
                    M[lannisters[n].getX()][lannisters[n].getY()] = "~";
                    lannisters[n].setX(p.x);
                    lannisters[n].setY(p.y);
                    lannisters[noAtacat].setX(-2);
                    lannisters[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[lannisters[n].getX()][lannisters[n].getY()] = "~";
                    lannisters[n].setX(-2);
                    lannisters[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }

            //Lannister ataca White Walker

            else if(M[p.x][p.y] == "W")
            {
                cout<<endl<<"Un Lannister ataca un White Walker!"<<endl;
                for(int i = 0; i < white_walkers.size(); i++)
                {
                    if(white_walkers[i].getX() == p.x && white_walkers[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"L"<<lannisters[n].getNo()<<" ("<<lannisters[n].getX()<<", "<<lannisters[n].getY()<<") il ataca pe W"<<white_walkers[noAtacat].getNo()<<" ("<<white_walkers[noAtacat].getX()<<", "<<white_walkers[noAtacat].getY()<<")"<<endl;

                while(lannisters[n].getHealth() > 0 && white_walkers[noAtacat].getHealth() > 0)
                {
                    lannisters[n].attack(white_walkers[noAtacat]);
                    if(white_walkers[noAtacat].getHealth() > 0)
                        white_walkers[noAtacat].attack(lannisters[n]);
                    else attacker = 1;
                    if(lannisters[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[white_walkers[noAtacat].getX()][white_walkers[noAtacat].getY()] = "L";
                    M[lannisters[n].getX()][lannisters[n].getY()] = "~";
                    lannisters[n].setX(p.x);
                    lannisters[n].setY(p.y);
                    white_walkers[noAtacat].setX(-2);
                    white_walkers[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[lannisters[n].getX()][lannisters[n].getY()] = "~";
                    lannisters[n].setX(-2);
                    lannisters[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }
        }
    }




    void Map::roundW(string (&M)[map_dim][map_dim], vector <S> &starks, vector <L> &lannisters, vector <W> &white_walkers, int n)
    {
        Punct p;
        p = white_walkers[n].trajectory(M);
        if(p.x == -1)
        {
            p = white_walkers[n].casual(M);
            M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
            cout<<"W"<<white_walkers[n].getNo()<<" ("<<white_walkers[n].getX()<<", "<<white_walkers[n].getY()<<") s-a mutat pe pozitia ("<<p.x<<", "<<p.y<<") ";
            if(M[p.x][p.y] == "h")
            {
                healthRestore h;
                white_walkers[n].setHealth(h.getBonus());
                cout<<"si a gasit un HEALTH RESTORE. Acum are health 100."<<endl;
            }
            else if(M[p.x][p.y] == "g")
            {
                iceSword ice;
                white_walkers[n].setHealth(white_walkers[n].getHealth() + ice.getBonusHealth());
                white_walkers[n].setDamage(white_walkers[n].getDamage() + ice.getBonusDamage());
                cout<<"si a gasit ICE SWORD. Acum are health +30 si damage +20."<<endl;
            }
            cout<<endl;
            cout<<endl;
            M[p.x][p.y] = "W";
            white_walkers[n].setX(p.x);
            white_walkers[n].setY(p.y);
        }
        else
        {
            int noAtacat, attacker = 0, attacked = 0;

            // White Walker ataca Stark

            if(M[p.x][p.y] == "S")
            {
                cout<<endl<<"Un White Walker ataca un Stark!"<<endl;
                for(int i = 0; i < starks.size(); i++)
                {
                    if(starks[i].getX() == p.x && starks[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"W"<<white_walkers[n].getNo()<<" ("<<white_walkers[n].getX()<<", "<<white_walkers[n].getY()<<") il ataca pe S"<<starks[noAtacat].getNo()<<" ("<<starks[noAtacat].getX()<<", "<<starks[noAtacat].getY()<<")"<<endl;

                while(white_walkers[n].getHealth() > 0 && starks[noAtacat].getHealth() > 0)
                {
                    white_walkers[n].attack(starks[noAtacat]);
                    if(starks[noAtacat].getHealth() > 0)
                        starks[noAtacat].attack(white_walkers[n]);
                    else attacker = 1;
                    if(white_walkers[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[starks[noAtacat].getX()][starks[noAtacat].getY()] = "W";
                    M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
                    white_walkers[n].setX(p.x);
                    white_walkers[n].setY(p.y);
                    starks[noAtacat].setX(-2);
                    starks[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
                    white_walkers[n].setX(-2);
                    white_walkers[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }

            // White Walker ataca Lannister

            else if(M[p.x][p.y] == "L")
            {
                cout<<endl<<"Un White Walker ataca un Lannister!"<<endl;
                for(int i = 0; i < lannisters.size(); i++)
                {
                    if(lannisters[i].getX() == p.x && lannisters[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"W"<<white_walkers[n].getNo()<<" ("<<white_walkers[n].getX()<<", "<<white_walkers[n].getY()<<") il ataca pe L"<<lannisters[noAtacat].getNo()<<" ("<<lannisters[noAtacat].getX()<<", "<<lannisters[noAtacat].getY()<<")"<<endl;

                while(white_walkers[n].getHealth() > 0 && lannisters[noAtacat].getHealth() > 0)
                {
                    white_walkers[n].attack(lannisters[noAtacat]);
                    if(lannisters[noAtacat].getHealth() > 0)
                        lannisters[noAtacat].attack(white_walkers[n]);
                    else attacker = 1;
                    if(white_walkers[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[lannisters[noAtacat].getX()][lannisters[noAtacat].getY()] = "W";
                    M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
                    white_walkers[n].setX(p.x);
                    white_walkers[n].setY(p.y);
                    lannisters[noAtacat].setX(-2);
                    lannisters[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
                    white_walkers[n].setX(-2);
                    white_walkers[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }

            //White Walker ataca White Walker

            else if(M[p.x][p.y] == "W")
            {
                cout<<endl<<"Un White Walker ataca un alt White Walker!"<<endl;
                for(int i = 0; i < white_walkers.size(); i++)
                {
                    if(white_walkers[i].getX() == p.x && white_walkers[i].getY() == p.y)
                        noAtacat = i;
                }

                cout<<"W"<<white_walkers[n].getNo()<<" ("<<white_walkers[n].getX()<<", "<<white_walkers[n].getY()<<") il ataca pe W"<<white_walkers[noAtacat].getNo()<<" ("<<white_walkers[noAtacat].getX()<<", "<<white_walkers[noAtacat].getY()<<")"<<endl;

                while(white_walkers[n].getHealth() > 0 && white_walkers[noAtacat].getHealth() > 0)
                {
                    white_walkers[n].attack(white_walkers[noAtacat]);
                    if(white_walkers[noAtacat].getHealth() > 0)
                        white_walkers[noAtacat].attack(white_walkers[n]);
                    else attacker = 1;
                    if(white_walkers[n].getHealth() <= 0) attacked = 1;
                }
                if(attacker == 1)
                {
                    cout<<"Atacatorul a castigat!"<<endl;
                    M[white_walkers[noAtacat].getX()][white_walkers[noAtacat].getY()] = "W";
                    M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
                    white_walkers[n].setX(p.x);
                    white_walkers[n].setY(p.y);
                    white_walkers[noAtacat].setX(-2);
                    white_walkers[noAtacat].setY(-2);
                    noTotalAgents--;
                }
                else if(attacked == 1)
                {
                    cout<<"Atacatorul a pierdut!"<<endl;

                    M[white_walkers[n].getX()][white_walkers[n].getY()] = "~";
                    white_walkers[n].setX(-2);
                    white_walkers[n].setY(-2);
                    noTotalAgents--;
                }
                cout<<"Au mai ramas "<<noTotalAgents<<" jucatori."<<endl;
                cout<<endl;
            }
        }
    }

int main()
{
    Map m;
    m.spawn();
    return 0;
}
