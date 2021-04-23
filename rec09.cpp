//
//  main.cpp
//  Rec 9
//
//

#include <iostream>

using namespace std;

class Rational {
    friend ostream& operator<<(ostream&, const Rational&);
    friend istream& operator>>(istream&, Rational&);
    friend bool operator==(const Rational&, const Rational&);
    friend bool operator<(const Rational&, const Rational&);
    
private:
    int numerator, denominator;
    void normalize();
    
public:
    Rational (int num = 0, int denom = 1);

    Rational& operator+=(const Rational&);
    Rational& operator++();
    Rational operator++(int dummy);
    explicit operator bool() const;
};


Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& lhs);
Rational operator--(Rational& lhs, int dummy);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs) ;
bool operator>=(const Rational& lhs, const Rational& rhs);
int greatestCommonDivisor(int, int);


int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}


Rational::Rational (int num, int denom) : numerator(num), denominator(denom) {
    normalize();
}

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

void Rational::normalize() {
    int greatestCommDenom = greatestCommonDivisor(numerator, denominator);
    numerator /= greatestCommDenom;
    denominator /= greatestCommDenom;
    
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}

Rational& Rational::operator+=(const Rational& rhs) {
    numerator = (numerator * rhs.denominator) + (rhs.numerator * denominator);
    denominator *= rhs.denominator;
    this->normalize();
    return *this;
}

Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
}

Rational Rational::operator++(int dummy) {
    Rational orig(*this);
    numerator += denominator;
    return orig;
}

Rational::operator bool() const {
    return numerator != 0;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    int left = lhs.numerator * rhs.denominator;
    int right = rhs.numerator * lhs.denominator;
    return left < right;
}

ostream& operator<<(ostream& os, const Rational& rational) {
    os << rational.numerator << "/" << rational.denominator;
    return os;
}

istream& operator>>(istream& is, Rational& rational) {
    char skipSlash;
    int num, denom;
    is >> num >> skipSlash >> denom;
    rational.numerator = num;
    rational.denominator = denom;
    rational.normalize();
    return is;
}





Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational lcopy = lhs;
    lcopy += rhs;
    return lcopy;
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

Rational& operator--(Rational& lhs) {
    lhs += (-1);
    return lhs;
}

Rational operator--(Rational& lhs, int dummy) {
    Rational temp = lhs;
    lhs += (-1);
    return temp;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return (rhs < lhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (rhs < lhs) || (rhs == lhs);
}

