// main.cpp

#include "poker.h"
#include <string>

int main(int argc, char **argv) {

    // Check for number of simulations
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " #simulations" << endl;
        exit(1);
    }

    long long flush_count = 0;
    long long straight_count = 0;
    long long straight_flush_count = 0;
    long long sims = stoll(string(argv[1]));

    // Monte-Carlo simulations
    for (int i = 0; i < sims; i++) {
        Deck d;
        vector<Card> hand;

        // Shuffle the deck
        d.shuffle_deck();

        for (int j = 0; j < POKER_HAND_SIZE; j++) {
            hand.push_back(d.deal());
        }

        if (is_flush(hand)) {
            flush_count++;
        }
        if (is_straight(hand)) {
            straight_count++;
        }
        if (is_straight_flush(hand)) {
            straight_flush_count++;
        }
    }

    cout.precision(6);
    cout << "Probability of a Flush = " << fixed
         << (flush_count / static_cast<double>(sims)) << endl;
    cout << "Probability of a Straight = " << fixed
         << (straight_count / static_cast<double>(sims)) << endl;
    cout << "Probability of a Straight Flush = " << fixed
         << (straight_flush_count / static_cast<double>(sims)) << endl;

    return (0);
}
