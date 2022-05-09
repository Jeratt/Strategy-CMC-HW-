#include <iostream>
#include <cstdlib>
#include "windows.h"

using namespace std;

//ДОБАВИТЬ ПЕРЕГРУЗКУ ВВОДА ВЫВОДА, КОНСТРУКТОР КОПИРОВАНИЯ

class Leader {
public:
    Leader(string name = "Unnamed", unsigned int age = 75) : name(name), age(age) {}
    string get_name() {
        return name;
    }
    virtual void year_upd() = 0;
    virtual void show() {
        cout << name << " at age of " << age << endl;
    }
    virtual ~Leader() {}
protected:
    string name;
    unsigned int age;
};

class President_t : public Leader {
public:
    President_t(string name = "Unnamed",unsigned int year_upd = 4) : Leader(name), to_elections(year_upd), term(year_upd) {}
    void year_upd() {
        ++age;
        --to_elections;
        if (to_elections <= 0) {
            cout << "Elections! Previous President is: " << name << endl;
            cout << "The new President is: ";
            cin >> name;
            cout << "Next elections in: " << term << " years" <<  endl;
            to_elections = term;
        }
    }
    void show() {
        cout << "President: ";
        this->Leader::show();
        cout << "Elections in " << to_elections << " years" << endl;
    }
private:
    unsigned int to_elections;
    const unsigned int term;
};

class King_t : public Leader {
public:
    King_t(string k_name = "Unnamed", string inh = "Unnamed", unsigned int k_age = 75, unsigned int age = 18) :
        Leader(k_name, k_age), inheritor(inh), inh_age(age) {}
    void year_upd() {
        ++age;
        if (age >= 80) {
            cout << "The king " << name << " is dead!\nLong live the king " << inheritor << endl;
            name = inheritor;
            age = inh_age;
            cout << "New inheritor: ";
            cin >> inheritor;
            cout << "His age is ";
            cin >> inh_age;
        }
    }
    void show() {
        cout << "King: ";
        this->Leader::show();
        cout << "Inheritor: " << inheritor << " at age of " << inh_age << endl;
    }
private:
    string inheritor;
    unsigned int inh_age;
};

class Country {
public:
    Country(string name = "Untitled",unsigned int pop = 1000, unsigned int power = 100, unsigned int army = 20, unsigned int area = 500) :
        name(name), population(pop), power(power), army(army), area(area) {}
    virtual void year_upd() = 0;
    virtual void show() {
        cout << name << ":" << endl;
        cout << "Population: " << population << endl;
        cout << "Power: " << power << endl;
        cout << "Army: " << army << endl;
        cout << "Area: " << area << endl;
    }
    void attack(Country * opp) {
        population -= army;
        area += opp->defense(power);
    }
    int defense(unsigned int attack) {
        population -= army;
        if (attack > army) {
            area -= attack - army;
            return attack - army;
        }
        return 0;
    }
    string get_name() {
        return name;
    }
    bool in_game() {
        if (population <= 0 || area <= 0)
            return false;
        return true;
    }
    void operator*(Country* opp) {
        this->attack(opp);
    }
    virtual Country & operator++() {
        this->year_upd();
        return *this;
    }
    virtual Country& operator++(int) {
        this->year_upd();
        return *this;
    }
    friend ostream& operator<<(ostream& c, Country& a) {
        a.show();
        return c;
    }
    virtual ~Country() {}
protected:
    string name;
    unsigned int population;
    unsigned int power;
    unsigned int army;
    unsigned int area;
};

class Republic : public Country {
public:
    Republic(string name, string president_name, unsigned int to_elections) : Country(name),
        to_elections(to_elections), president(president_name,to_elections) {}
    void year_upd() {
        president.year_upd();
    }
    void show() {
        cout << "\nRepublic ";
        this->Country::show();
        president.show();
    }
    virtual Republic& operator++() {
        this->year_upd();
        return *this;
    }
    virtual Republic& operator++(int) {
        this->year_upd();
        return *this;
    }
private:
    President_t president;
    unsigned int to_elections;
};

class Kingdom : public Country {
public:
    Kingdom(string name,string king_name, string inh_name, unsigned int k_age = 75, unsigned int inh_age = 18) : Country(name) {
        king = King_t(king_name, inh_name, k_age, inh_age);
    }
    void year_upd() {
        king.year_upd();
    }
    void show() {
        cout << "\nKingdom ";
        this->Country::show();
        king.show();
    }
    virtual Kingdom& operator++() {
        this->year_upd();
        return *this;
    }
    virtual Kingdom& operator++(int) {
        this->year_upd();
        return *this;
    }
private:
    King_t king;
};

class Community : public Country {
public:
    Community(string name, unsigned int elders_amount, string *elders, unsigned int to_elections) : Country(name),
        to_elections(to_elections), term(to_elections), elders_amount(elders_amount)
    {
        this->elders = new string[elders_amount];
        for (int i = 0; i < elders_amount; ++i) {
            this->elders[i] = elders[i];
        }
    }
    void year_upd() {
        --to_elections;
        if (to_elections <= 0) {
            cout << "Elections in community " << name << "!\n";
            cout << "New " << elders_amount << " elders are: ";
            for (int k = 0; k < elders_amount; ++k) {
                cin >> elders[k];
            }
        }
        to_elections = term;
    }
    void show() {
        cout << "\nCommunity ";
        this->Country::show();
        cout << "Elders are: ";
        for (int k = 0; k < elders_amount; ++k) {
            cout << elders[k] << endl;
        }
    }
    virtual Community& operator++() {
        this->year_upd();
        return *this;
    }
    virtual Community& operator++(int) {
        this->year_upd();
        return *this;
    }
    ~Community() { delete[] elders; }
private:
    string* elders;
    unsigned int elders_amount;
    unsigned int to_elections;
    const unsigned int term;
};

class Barbarians {
public:
    static void attack(Country* point) {
        point->defense(power);
    }
private:
    static unsigned int power;
};

void game() {
    //REGISTRATION
    int i = 0, number, live_players;
    unsigned int to_elections, elders_amount,barbarians_opp;
    string country_type,name,king_name,president_name,inh_name, *elders,opp;
    char action;
    cout << "Strategy simulator by Georgy Sazonov\nNumber of players: ";
    cin >> number;
    live_players = number;
    Country** players;
    players = new Country * [number];
    while(i < number) {
        try {
            cout << "Country type: ";
            cin >> country_type;
            if (country_type != "Kingdom" && country_type != "Republic" && country_type != "Community")
                throw 'x';
            else if (country_type == "Kingdom") {
                cout << "The kingdom is: ";
                cin >> name;
                cout << "The king is: ";
                cin >> king_name;
                cout << "The inheritor is: ";
                cin >> inh_name;
                players[i] = new Kingdom(name, king_name, inh_name);
            }
            else if (country_type == "Republic") {
                cout << "The republic is: ";
                cin >> name;
                cout << "The president is: ";
                cin >> president_name;
                cout << "Elections every(years): ";
                cin >> to_elections;
                if (to_elections <= 0)
                    throw 1;
                players[i] = new Republic(name, president_name, to_elections);
            }
            else if (country_type == "Community") {
                cout << "The community is: ";
                cin >> name;
                cout << "Elders amount: ";
                cin >> elders_amount;
                if (elders_amount <= 0)
                    throw 1;
                elders = new string[elders_amount];
                for (int j = 0; j < elders_amount; ++j) {
                    cin >> elders[j];
                }
                cout << "Elections every(years): ";
                cin >> to_elections;
                players[i] = new Community(name, elders_amount, elders, to_elections);
                delete[] elders;
            }
        }
        catch (char) {
            cout << "WRONG COUNTRY TYPE! TRY AGAIN!" << endl;
            continue;
        }
        catch (int) {
            cout << "WRONG PARAMETERS! TRY AGAIN!" << endl;
            continue;
        }
        cout<<(*players[i]);
        ++i;
    }
    //THE GAME ITSELF
    i = 0;
    while (true) {
        system("cls"); //DIFFERENT ON LINUX
        live_players = 0;
        for (int j = 0; j < number; ++j) {
            if (players[j]->in_game())
                live_players++;
        }
        if (live_players == 1) {
            cout << "GAME OVER!" << endl;
            break;
        }
        else if (live_players == 0) {
            cout << "BARBARIANS WON!" << endl;
            break;
        }
        if (i != number) {
            cout<<(*players[i]);
            try {
                cout << "TURN: ";
                cin >> action >> opp;
                if (action != '*')
                    throw 'x';
                for (int j = 0; j < number; ++j) {
                    if (j == i)
                        continue;
                    if (players[j]->get_name() == opp) {
                        if (players[j]->in_game()) {
                            (*players[i])* players[j];
                            break;
                        }
                        else {
                            throw 1.5;
                        }
                    }
                    if (j + 1 == number)
                        throw 1;
                }
                ++(*players[i]);
            }
            catch (char) {
                cout << "WRONG ACTION! TRY AGAIN!" << endl;
                continue;
            }
            catch (int) {
                cout << "OPPONENT DOES NOT EXIST! TRY AGAIN!" << endl;
                continue;
            }
            catch (double) {
                cout << "OPPONENT HAS BEEN ELIMINATED! TRY AGAIN!" << endl;
            }
        }
        else {
            cout << "BARBARIANS!" << endl;
            while (true) {
                barbarians_opp = rand() % number;
                if (players[barbarians_opp]->in_game()) {
                    cout << "Barbarians attack country: " << players[barbarians_opp]->get_name() << endl;
                    Barbarians::attack(players[barbarians_opp]);
                    Sleep(1000);
                    break;
                }
                else
                    continue;
            }
        }
        ++i;
        i = i % (number + 1);
    }
    //DELETING
    for (int i = 0; i < number; ++i) {
        delete players[i];
    }
    delete[] players;

}

unsigned int Barbarians::power = 100;

int main()
{
    game();
    return 0;
}
