/*
  rec11-part-one.cpp
 */
#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() = 0;
private:
};

class Brass : public Instrument {
public:
    Brass(unsigned);

    void makeSound();
private:
    unsigned mouthPiece;
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned);
};

class Trombone : public Brass {
public:
    Trombone(unsigned);
};


class String : public Instrument {
public:
    String(unsigned);

    void makeSound();
private:
    unsigned stringPitch;
};

class Violin : public String {
public:
    Violin(unsigned);
};

class Cello : public String {
public:
    Cello(unsigned);
};


class Percussion : public Instrument {
public:
    void makeSound();
};

class Drum : public Percussion {
public:
};

class Cymbal : public Percussion {
public:
};


class MILL {
public:
    void dailyTestPlay();
    void receiveInstr(Instrument&);
    Instrument* loanOut();
private:
    vector<Instrument*> inventory;
};


class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};


// PART ONE
int main() {

    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;

    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    cout << "Daily test -------------------------------------------------\n"
        << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << endl << endl;

    groucho.testPlay();
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());


    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << endl;
}


void MILL::dailyTestPlay() {
    for (Instrument* instrument : inventory) {
        if (instrument) instrument->makeSound();
    }
}

void MILL::receiveInstr(Instrument& instr) {
    for (size_t cubby = 0; cubby < inventory.size(); ++cubby) {
        if (inventory[cubby] == nullptr) {
            inventory[cubby] = &instr;
            return;
        }
    }
    inventory.push_back(&instr);
}

Instrument* MILL::loanOut() {
    for (size_t cubby = 0; cubby < inventory.size(); ++cubby) {
        if (inventory[cubby]) {
            Instrument* instrAddress = inventory[cubby];
            inventory[cubby] = nullptr;
            return instrAddress;
        }
    }
    return nullptr;
}

void Instrument::makeSound() {
    cout << "To make a sound... ";
}


Brass::Brass(unsigned size) : mouthPiece(size) {}

void Brass::makeSound() {
    Instrument::makeSound();
    cout << "blow on a mouthpiece of size "
        << mouthPiece << endl;
}


Trumpet::Trumpet(unsigned size) : Brass(size) {}


Trombone::Trombone(unsigned size) : Brass(size) {}


String::String(unsigned pitch) : stringPitch(pitch) {}

void String::makeSound() {
    Instrument::makeSound();
    cout << "bow a string with pitch "
        << stringPitch << endl;
}


Violin::Violin(unsigned pitch) : String(pitch) {}


Cello::Cello(unsigned pitch) : String(pitch) {}


void Percussion::makeSound() {
    Instrument::makeSound();
    cout << "hit me!" << endl;
}

