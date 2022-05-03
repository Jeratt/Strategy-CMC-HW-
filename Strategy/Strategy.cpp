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
    King_t(string k_name = "Unnamed", unsigned int k_age = 75, string inh = "Unnamed", unsigned int age = 18) :
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
private:
    string inheritor;
    unsigned int inh_age;
};

class Country {
public:
    Country(string name = "Untitled",unsigned int pop = 1000, unsigned int power = 50, unsigned int army = 50, unsigned int area = 500) :
        name(name), population(pop), power(power), army(army), area(area) {}
    virtual void elections() = 0;
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
        king = King_t(new_name, new_age, inheritor, inh_age);
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



unsigned int Barbarians::power = 10;

int main()
{
    std::cout << "Hello World!\n";
}
