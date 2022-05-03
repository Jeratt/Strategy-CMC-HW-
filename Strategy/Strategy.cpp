#include <iostream>
#include <cstdlib>

using namespace std;

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
    President_t(unsigned int year_upd = 4) : to_elections(year_upd) {}
private:
    unsigned int to_elections;
};

class King_t : public Leader {
public:
    King_t(string k_name = "Unnamed", string inh = "Unnamed", unsigned int k_age = 75, unsigned int age = 18) :
        Leader(k_name, k_age), inheritor(inh), inh_age(age) {
        // добавить обработку исключения на возраст наследника
    }
    void year_upd() {
        ++age;
        if (age == 80) {
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
        cout << "King ";
        this->Leader::show();
        cout << "Inheritor: " << inheritor << " at age of " << inh_age << endl;
    }
private:
    string inheritor;
    unsigned int inh_age;
};

class Country {
public:
    Country(string name = "Untitled",unsigned int pop = 1000, unsigned int power = 50, unsigned int army = 50, unsigned int area = 500) :
        name(name), population(pop), power(power), army(army), area(area) {}
    virtual void elections() = 0;
    virtual void show() {
        cout << name << ":" << endl;
        cout << "Population: " << population << endl;
        cout << "Power: " << power << endl;
        cout << "Army: " << army << endl;
        cout << "Area: " << area << endl;
    }
    void attack(int country_id) {

    };
    void defense() {

    };
protected:
    string name;
    unsigned int population;
    unsigned int power;
    unsigned int army;
    unsigned int area;
};

class Republic : public Country {

};

class Kingdom : public Country {
public:
    Kingdom(string name,string king_name, string inh_name, unsigned int k_age = 75, unsigned int inh_age = 18) : Country(name) {
        king = King_t(king_name, inh_name, k_age, inh_age);
    }
    void elections() {
        string new_name, inheritor;
        int new_age, inh_age;
        cout << "The king " << king.get_name() <<" has murdered! A new king is: ";
        cin >> new_name;
        cout << "His age is ";
        cin >> new_age;
        cout << "New inheritor: ";
        cin >> inheritor;
        cout << "His age is ";
        cin >> inh_age;
        king = King_t(new_name,inheritor,new_age,inh_age);
    }
    void show() {
        cout << "Kingdom ";
        this->Country::show();
        king.show();
    }
private:
    King_t king;
};

class Community : public Country {

};

class Barbarians {
public:
    static void attack(Country& point) {

    }
private:
    static unsigned int power;
};

void game() {
    //REGISTRATION
    int i = 0,number;
    string country_type,name,king_name,inh_name;
    cout << "Strategy simulator by Georgy Sazonov\nNumber of players: ";
    cin >> number;
    Country** players;
    players = new Country * [number];
    while(i < number) {
        try {
            cin >> country_type;
            if (country_type != "Kingdom" && country_type != "Republic" && country_type != "Community")
                throw 'x';
            else if (country_type == "Kingdom") {
                cin >> name;
                cout << "The king is: ";
                cin >> king_name;
                cout << "The inheritor is: ";
                cin >> inh_name;
                players[i] = new Kingdom(name, king_name, inh_name);
            }
        }
        catch (char) {
            cout << "WRONG COUNTRY TYPE! TRY AGAIN!" << endl;
            continue;
        }
        players[i]->show();
        ++i;
    }
    //THE GAME ITSELF
    //DELETING
    for (int i = 0; i < number; ++i) {
        delete players[i];
    }
    delete[] players;

}

unsigned int Barbarians::power = 10;

int main()
{
    game();
    return 0;
}
