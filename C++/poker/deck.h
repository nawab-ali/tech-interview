// This class models a deck of cards.

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include<vector>
#include<random>
#include<algorithm>

const int SUIT_SIZE = 13;
const int DECK_SIZE = 52;

class Deck {
private:
    vector <Card> container;

public:
    Deck(void);
    Card deal(void);
    void shuffle_deck(void);
    bool return_to_deck(const Card c);

    // Overload the << operator
    friend ostream &operator<<(ostream &out, const Deck &d) {
        for_each(d.container.begin(), d.container.end(), [&out](const Card c) { out << c << endl; });
        return (out);
    }
};

// Constructor
Deck::Deck(void) {
    vector <Suit> v = {Suit::SPADE, Suit::HEART, Suit::DIAMOND, Suit::CLUB};

    for_each(v.begin(), v.end(), [this](const Suit s) {
        for (int i = 1; i <= SUIT_SIZE; i++) {
            this->container.push_back(Card(s, i));
        }
    });
}

// Return the card on top of the deck
Card Deck::deal(void) {
    assert(container.size() >= 1 && container.size() <= DECK_SIZE);

    Card c = container[0];
    container.erase(container.begin());

    return (c);
}

// Shuffle the deck
void Deck::shuffle_deck(void) {
    random_device rd;
    mt19937 g(rd());
    shuffle(container.begin(), container.end(), g);
}

// Return card to deck
bool Deck::return_to_deck(const Card c) {
    Suit s = c.get_suit();
    int pips = c.get_pips();

    assert(pips >= 1 && pips <= 13);
    assert(container.size() >= 0 && container.size() <= DECK_SIZE - 1);
    assert(s == Suit::SPADE || s == Suit::HEART || s == Suit::DIAMOND ||
           s == Suit::CLUB);

    // Ignore duplicate cards
    auto it = find_if(container.begin(), container.end(), [&c](const Card &c1) {
        return ((c.get_pips() == c1.get_pips()) &&
                (c.get_suit() == c1.get_suit()));
    });

    if (it == container.end()) {
        container.push_back(c);
        return (true);
    } else {
        return (false);
    }
}

#endif //DECK_H
