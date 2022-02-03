// Jakub Lukasiewicz

#include <iostream>

// Fix names {{{

#define  Arena      ARENA_CLASS
#define  Beast      BEAST_CLASS
#define  Berserker  BERSERKER_CLASS
#define  Caesar     CAESAR_CLASS
#define  Human      HUMAN_CLASS
#define  Player     PLAYER_CLASS
#define  Squad      SQUAD_CLASS

#define  judge  judgeDeathOfLife // "Of" ?
#define  getHP  getRemainingHealth

// Fix names }}}

typedef unsigned int uInt;

template<typename T>
class Vector {
    uInt N; // size
    uInt capacity;

  public:
    T* data;

    Vector(uInt n = 1) : N(0), capacity(n), data(new T[n]) {}
    ~Vector() { delete[] data; }

    void pushBack(T elem)
    {
        if (N == capacity) {
            resize(2 * N);
        }
        data[N] = elem;
        ++N;
    }

    void remove(uInt n)
    {
        for (uInt i = n; i < N - 1; ++i) {
            data[i] = data[i+1];
        }
        if (N > 0) {
            --N;
        }
    }

    void resize(uInt n)
    {
        if (n > capacity) {
            T* temp = new T[n];
            for (uInt i = 0; i < N; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity = n;
        }
    }

    uInt size()
    {
        return N;
    }

    T& operator [](uInt n)
    {
        return data[n];
    }
};

class Player {
  public:

    Player() {}

    Player(uInt maxHP_, uInt HP_, uInt damage_, uInt agility_) :
        maxHP(maxHP_), HP(HP_), damage(damage_), agility(agility_)
    {}

    virtual uInt getHP()
    {
        return (HP * 100) / maxHP;
    }

    virtual uInt getDamage()
    {
        return damage;
    }

    virtual uInt getAgility()
    {
        return agility;
    }

    virtual void takeDamage(uInt d)
    {
        if (d < HP) {
            HP -= d;
            if (getHP() < 0) {
                die();
            }
        }
        else {
            die();
        }
    }

    virtual void applyWinnerReward()
    {
        damage  += 2;
        agility += 2;
    }

    virtual void cure()
    {
        HP = maxHP;
    }

    virtual void printParams()
    {
        std::cout << maxHP << ":" << HP << ":" << getHP() << "%:"
            << getDamage() << ":" << getAgility();
        // Missing new line! Print in inheriting class!
    }

  private:

    void die()
    {
        HP = 0;
    }

  protected:
    uInt maxHP;
    uInt HP;
    uInt damage;
    uInt agility;

    friend class Caesar;
    friend class Squad;
};

class Human : public virtual Player {
    std::string id;
  protected:
    uInt defense;
  public:
    Human(std::string id_) : Player(200, 200, 30, 10), id(id_), defense(10) {}

    virtual void takeDamage(uInt d)
    {
        uInt D = defense + getAgility();
        if (d > D) {
            Player::takeDamage(d - D);
        }
    }

    virtual void printParams()
    {
        if (getHP() > 0) {
            std::cout << id << ":";
            Player::printParams();
            std::cout << ":" << defense;
        }
        else {
            std::cout << id << ":R.I.P.";
        }
        std::cout << std::endl;
    }

};

class Beast : public virtual Player {
    std::string id;
  public:
    Beast(std::string id_) : Player(150, 150, 40, 20), id(id_) {}

    virtual uInt getDamage()
    {
        return getHP() < 25 ? 2 * damage : damage;
    }

    virtual void takeDamage(uInt d)
    {
        uInt D = getAgility() / 2;
        if (d > D) {
            Player::takeDamage(d - D);
        }
    }

    virtual void printParams()
    {
        if (getHP() > 0) {
            std::cout << id << ":";
            Player::printParams();
        }
        else {
            std::cout << id << ":R.I.P.";
        }
        std::cout << std::endl;
    }

};

class Berserker : virtual public Human, virtual public Beast {
    std::string idHuman;
    std::string idBeast;
  public:

    Berserker(std::string idH, std::string idB) :
        Player(200, 200, 35, 5), Human(idH), Beast(idB)
    {
        defense = 15;
    }

    uInt getDamage()
    {
        uInt hp = getHP();
        if (hp > 0 && hp < 25) {
            return Beast::getDamage();
        }
        else {
            return Human::getDamage();
        }
    }

    uInt getAgility()
    {
        uInt hp = getHP();
        if (hp > 0 && hp < 25) {
            return Beast::getAgility();
        }
        else {
            return Human::getAgility();
        }
    }

    void takeDamage(uInt d)
    {
        uInt hp = getHP();
        if (hp > 0 && hp < 25) {
            Beast::takeDamage(d);
        }
        else {
            Human::takeDamage(d);
        }
    }

    void printParams()
    {
        uInt hp = getHP();
        if (hp > 0 && hp < 25) {
            Beast::printParams();
        }
        else {
            Human::printParams();
        }
    }

};

class Squad : public Player {
    std::string id;
    Vector<Player*> warriors;
  public:
    Squad(std::string id_) : id(id_) {}

    void addPlayer(Player* w)
    {
        if (w->getHP() > 0){
            for (uInt i = 0; i < warriors.size(); ++i) {
                if (w == warriors[i]) {
                    return;
                }
            }
            warriors.pushBack(w);
        }
    }

    uInt getHP()
    {
        uInt hp = 0;
        for (uInt i = 0; i < warriors.size(); ++i) {
            uInt h = warriors[i]->getHP();
            if (h > hp) {
                hp = h;
            }
        }
        return hp;
    }

    uInt getDamage()
    {
        uInt d = 0;
        for (uInt i = 0; i < warriors.size(); ++i) {
            d += warriors[i]->getDamage();
        }
        return d;
    }

    void takeDamage(uInt d)
    {
        uInt N = warriors.size();
        if (N > 0) {
            d = d / N;
            for (uInt i = 0; i < warriors.size(); ++i) {
                warriors[i]->takeDamage(d);
                if (warriors[i]->getHP() == 0) {
                    warriors.remove(i);
                    --i;
                }
            }
        }
    }

    void applyWinnerReward()
    {
        for (uInt i = 0; i < warriors.size(); ++i) {
            warriors[i]->applyWinnerReward();
        }
    }

    uInt getAgility()
    {
        uInt N = warriors.size();
        uInt A = 0;
        if (N > 0) {
            A = warriors[0]->getAgility();
            for (uInt i = 1; i < N; ++i) {
                uInt a = warriors[i]->getAgility();
                if (a < A) {
                    A = a;
                }
            }
        }
        return A;
    }

    void printParams()
    {
        uInt N = warriors.size();
        if (N > 0) {
            std::cout << id << ":" << N << ":" << getHP() << "%:"
                << getDamage() << ":" << getAgility() << std::endl;
            for (uInt i = 0; i < N; ++i) {
                warriors[i]->printParams();
            }
        }
        else {
            std::cout << id << ":nemo" << std::endl;
        }
    }

    void cure()
    {
        for (uInt i = 0; i < warriors.size(); ++i) {
            warriors[i]->cure();
        }
    }

    void die()
    {
        for (int i = warriors.size() - 1; i >= 0; --i) {
            warriors[i]->die();
        }
        warriors.resize(0);
    }

};

class Caesar {
    uInt attackCounter;
    uInt judgeCounter;
  public:
    Caesar() : attackCounter(0), judgeCounter(0) {}

    void judge(Player* g)
    {
        ++judgeCounter;
        if (judgeCounter % 3 == 0) {
            if (attackCounter % 2 == 0) {
                g->die();
            }
            judgeCounter = 0;
        }
    }

    void countAttack()
    {
        ++attackCounter;
    }

    void finish(Player* primus, Player* secundus)
    {
        if (primus->getHP() > 0) {
            judge(primus);
            primus->printParams();
            if (primus->getHP() > 0) {
                primus->cure();
                primus->applyWinnerReward();
            }
        }

        if (secundus->getHP() > 0) {
            judge(secundus);
            secundus->printParams();
            if (secundus->getHP() > 0) {
                secundus->cure();
                secundus->applyWinnerReward();
            }
        }

        primus->printParams();
        secundus->printParams();

        attackCounter = 0;
    }

};

class Arena {
    Caesar* ceasar;
  public:
    Arena(Caesar* ceasar) : ceasar(ceasar) {}

    void fight(Player* primus, Player* secundus)
    {
        if (primus->getHP() > 0 && secundus->getHP() > 0) {
            if (primus->getAgility() < secundus->getAgility()) {
                Player* temp = primus;
                primus = secundus;
                secundus = temp;
            }
            primus->printParams();
            secundus->printParams();

            for (uInt i = 0; i < 40; ++i) {
                if (primus->getHP() >= 10 && secundus->getHP() >= 10) {
                    secundus->takeDamage(primus->getDamage());
                    secundus->printParams();
                    ceasar->countAttack();
                    if (secundus->getHP() >= 10) {
                        primus->takeDamage(secundus->getDamage());
                        primus->printParams();
                        ceasar->countAttack();
                    }
                }
                else {
                    break;
                }
            }

            ceasar->finish(primus, secundus);
        }
    }

};

// vim: fen
