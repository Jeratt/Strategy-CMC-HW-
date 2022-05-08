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
    Country(string name = "Untitled",unsigned int pop = 1000, unsigned int power = 50, unsigned int army = 50, unsigned int area = 500) :
        name(name), population(pop), power(power), army(army), area(area) {}
    virtual void year_upd() = 0;
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
    unsigned int to_elections;
    string country_type,name,king_name,president_name,inh_name;
    cout << "Strategy simulator by Georgy Sazonov\nNumber of players: ";
    cin >> number;
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
        }
        catch (char) {
            cout << "WRONG COUNTRY TYPE! TRY AGAIN!" << endl;
            continue;
        }
        catch (int) {
            cout << "WRONG PARAMETERS! TRY AGAIN!" << endl;
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
