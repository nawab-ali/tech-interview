// This file models the game of Poker.

#ifndef POKER_H
#define POKER_H

#include "card.h"
#include "deck.h"

const int POKER_HAND_SIZE = 5;

// Do all the cards in the hand belong to the same suit?
bool is_flush(const vector <Card> &hand) {
    assert(hand.size() == POKER_HAND_SIZE);
    assert(hand[0].get_pips() >= 1 && hand[0].get_pips() <= SUIT_SIZE);

    Suit s = hand[0].get_suit();

    for (int i = 1; i < hand.size(); i++) {
        assert(hand[i].get_pips() >= 1 && hand[i].get_pips() <= SUIT_SIZE);

        if (hand[i].get_suit() != s) {
            return (false);
        }
    }

    return (true);
}

// Is the poker hand a straight?
bool is_straight(const vector <Card> &hand) {
    assert(hand.size() == POKER_HAND_SIZE);

    vector<int> pips;

    for_each(hand.begin(), hand.end(), [&pips](const Card c) {
        assert(c.get_pips() >= 1 && c.get_pips() <= SUIT_SIZE);
        pips.push_back(c.get_pips());
    });

    sort(pips.begin(), pips.end());

    if (pips[0] != 1) {
        // non-Aces
        return (pips[0] == pips[1] - 1 && pips[1] == pips[2] - 1 &&
                pips[2] == pips[3] - 1 && pips[3] == pips[4] - 1);
    } else {
        // Aces need special logic
        return ((pips[0] == pips[1] - 1 && pips[1] == pips[2] - 1 &&
                 pips[2] == pips[3] - 1 && pips[3] == pips[4] - 1) ||
                (pips[1] == 10 && pips[2] == 11 && pips[3] == 12 && pips[4] == 13));
    }
}

// Is the poker hand a straight flush?
bool is_straight_flush(const vector <Card> &hand) {
    return (is_straight(hand) && is_flush(hand));
}

// Print the hand
void print_hand(const vector <Card> &hand) {
    assert(hand.size() == POKER_HAND_SIZE);

    for (auto Card:hand) {
        cout << Card << endl;
    }
}

#endif //POKER_H
