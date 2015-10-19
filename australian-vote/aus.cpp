/*
 * aus.cpp
 * Anoop Iyer, 2015
 * C++ class assignment for Australian Voting
 */ 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <climits>

namespace aus {

class Ballot {
public:
    std::list<int> candidate;
    void push_back (int x) { candidate.push_back (x); }
    void print (void) {
        for (auto& c : candidate) std::cerr << c << ',';
        std::cerr << '\n';
    }
};

class Candidate {
public:
    std::string name;
    bool eliminated = false;
    int votes = 0;
    std::list<Ballot *> ballot;

    void print (void) { std::cerr << name << ": " << votes << '\n'; }
    void init (const std::string& s) { name = s; }
    void increment (void) { votes++; }
    void eliminate (void) { eliminated = true; }
};

class Case {
public:
    std::vector<Candidate> candidate;
    std::list<Ballot> ballot;

    void print (void);
    void count (void);
};

bool verbose = false;

void Case::print (void)
{
    for (auto& c : candidate) c.print();
    for (auto& b : ballot) b.print();
}

void Case::count (void)
{
    int min, max, winner;
    int threshold = ballot.size() / 2 + 1;

    // Initial count of all ballots
    for (auto& b : ballot) {
        int c = b.candidate.front();
        candidate[c-1].increment();
        // b.candidate.pop_front();
        candidate[c-1].ballot.push_back (&b);
    }

    for (int x = 0; x < 20; x++) {

        if (verbose) std::cerr << "Count round " << x << '\n';

        min = INT_MAX;
        max = INT_MIN;
        winner = INT_MAX;

        // Find the winner and the loser
        int i = 0;
        for (auto& c : candidate) {
            if (!c.eliminated) {
                if (c.votes < min) {
                    min = c.votes;
                }
                if (c.votes > max) {
                    winner = i;
                    max = c.votes;
                }
            }
            i++;
        }

        // If the highest has more than 50%, declare the winner.
        if (max >= threshold) {
            std::cout << candidate[winner].name << "\n";
            return;
        } else if (min == max) {
            // Tie
            for (auto& c : candidate) {
                if (c.eliminated == false) {
                    std::cout << c.name << '\n';
                }
            }
            return;
        } else {
            // Mark min candidates for elimination
            std::vector<Candidate *> elimination_list;
            for (auto& c : candidate) {
                if (c.votes == min && c.eliminated == false) {
                    if (verbose) std::cerr << "Eliminating " << c.name << '\n';
                    c.eliminated = true;
                    elimination_list.push_back (&c);
                }
            }

            // Reassign votes from min candidates
            for (Candidate * c : elimination_list) {
                for (Ballot * b : c->ballot) {
                    int c_new;
                    do {
                        b->candidate.pop_front();
                        c_new = b->candidate.front();
                    } while (candidate[c_new-1].eliminated == true);
                    candidate[c_new-1].increment();
                    candidate[c_new-1].ballot.push_back (b);
                    if (verbose) {
                        std::cerr << "Assigning from " << c->name << " to " <<
                            candidate[c_new-1].name << '\n';
                    }
                }
            }
            elimination_list.clear();
        }
    }
}

}; // namespace Aus

using namespace std;
using namespace aus;

int main (int argc, char * argv[])
{
    int num_cases = 0;
    string l;
    istringstream s;

    Case * mycase;

    // Read the number of cases
    getline (cin, l);
    s.str (l);
    s >> num_cases;
    if (verbose) cerr << num_cases << " cases\n";
    getline (cin, l); // blank
    mycase = new Case [num_cases];

    for (int c = 0; c < num_cases; c++) {
        Candidate * candidate;
        Ballot * ballot;
        int num_candidates = 0;
        int ballot_count = 0;

        // Read candidates
        getline (cin, l);
        s.clear(); s.str (l);
        s >> num_candidates;
        if (verbose) cerr << num_candidates << " candidates\n";
        candidate = new Candidate[num_candidates];
        for (int j = 0; j < num_candidates; j++) {
            getline (cin, l);
            candidate[j].init (l);
            mycase[c].candidate.push_back (candidate[j]);
        }
        if (verbose) 
            for (int q = 0; q < num_candidates; q++) 
                cerr << candidate[q].name << '\n';

        // Read ballots
        ballot = new Ballot[1000];
        ballot_count = 0;
        for (getline (cin, l); l.length() > 0; getline (cin, l), ballot_count++) {
            s.clear(); s.str (l);
            for (int j = 0; j < num_candidates; j++) {
                int k;
                s >> k;
                ballot[ballot_count].push_back (k);
            }
            if (verbose) ballot[ballot_count].print();
            mycase[c].ballot.push_back (ballot[ballot_count]);
        }
        if (verbose) cerr << ballot_count << " ballots\n";

        mycase[c].count();

        // delete[] ballot;
        // delete[] candidate;

        if (verbose) cerr << "End of case\n";
        if (c != num_cases - 1) std::cout << "\n";
    }

    return 0;
}
