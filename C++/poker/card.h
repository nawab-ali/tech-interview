// This class models a playing card.

#ifndef CARD_H
#define CARD_H

#include<cassert>
#include<iostream>

using namespace std;

enum class Suit {
    SPADE, HEART, DIAMOND, CLUB
};

class Card {
private:
    Suit s;
    int pips;

public:
    Card(const Suit s, const int pips);
    Suit get_suit(void) const;
    int get_pips(void) const;

    // Overload the << operator
    friend ostream &operator<<(ostream &out, const Card &c) {
        assert(c.pips >= 1 && c.pips <= 13);

        // Print the pips of the card
        switch (c.pips) {
            case 1:
                out << "Ace of ";
                break;
            case 2:
                out << "2 of ";
                break;
            case 3:
                out << "3 of ";
                break;
            case 4:
                out << "4 of ";
                break;
            case 5:
                out << "5 of ";
                break;
            case 6:
                out << "6 of ";
                break;
            case 7:
                out << "7 of ";
                break;
            case 8:
                out << "8 of ";
                break;
            case 9:
                out << "9 of ";
                break;
            case 10:
                out << "10 of ";
                break;
            case 11:
                out << "Jack of ";
                break;
            case 12:
                out << "Queen of ";
                break;
            case 13:
                out << "King of ";
                break;
            default:
                break;
        }

        // Print the suit of the card
        switch (c.s) {
            case Suit::SPADE:
                out << "Spades";
                break;
            case Suit::HEART:
                out << "Hearts";
                break;
            case Suit::DIAMOND:
                out << "Diamonds";
                break;
            case Suit::CLUB:
                out << "Clubs";
                break;
            default:
                break;
        }

        return (out);
    }
};

// Constructor
Card::Card(const Suit s, const int pips) {
    //There are 13 cards in each suit
    assert(pips >= 1 && pips <= 13);

    this->s = s;
    this->pips = pips;
}

// Return the suit of the card
Suit Card::get_suit(void) const {
    return (s);
}

// Return the pips of the card
int Card::get_pips(void) const {
    return (pips);
}

#endif //CARD_H
