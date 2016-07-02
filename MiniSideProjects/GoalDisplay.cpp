//
//  main.cpp
//  ExpediaScoreDisplay
//
//  Created by Daven Gomes on 15/01/2016.
//  Copyright © 2016 Daven Gomes. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

class Goal{
    std::string p;
    std::string m;
    
public:
    Goal() {};
    Goal(const std::string &p_, const std::string &m_) : m(m_), p(p_){};
    std::string player() const { return p; }
    std::string minute() const { return m; }
    
    friend std::ostream & operator<<(std::ostream &out, const Goal &g){
        return out << " " << g.p << " " << g.m << "' ";
    }
};

class Team{
    std::string n;
    bool h;
    std::vector<Goal> gs;
    
public:
    Team(){};
    Team(const std::string &n_, const bool &home) : n(n_){};
    std::string name() const { return n; }
    std::vector<Goal> goals() const { return gs; }
    
    void addGoal(const std::string &player, const std::string &minute){
        gs.push_back(Goal(player, minute));
    }
    
    friend std::ostream & operator<<(std::ostream &out, const Team &t){
        
        out << t.n;
        
        if (t.gs.size() > 0){
            out << " (";
            for(auto const& goal: t.gs) {
                out << goal;
            }
            out << ")";
        }
        
        return out;
    }
};

class Helper {
    
public:
    std::vector<std::string> splitStringIntoVector(std::string &str){
        std::vector<std::string> strings;
        std::istringstream s ( str);
        strings.insert(strings.end(),
                       std::istream_iterator<std::string>(s),
                       std::istream_iterator<std::string>());
        return strings;
    }
};

class Game {
    Team t1;
    Team t2;
    bool started_;
    
public:
    Game(){};
    Game(const std::string &team1Name, const std::string &team2Name){
        t1 = Team(team1Name, true);
        t2 = Team(team2Name, false);
        started_ = true;
    }
    
    Team team1() const { return t1; }
    Team team2() const { return t2; }
    bool started() const { return started_; }
    
    void addGoal(std::string &goalStr){
        
        Helper helper;
        
        std::vector<std::string> strings = helper.splitStringIntoVector(goalStr);
        
        if (!strings[1].compare(t1.name())){
            t1.addGoal(strings[2], strings[0]);
        }else{
            t2.addGoal(strings[2], strings[0]);
        }
    }
    
    friend std::ostream & operator<<(std::ostream &out, const Game &g){
        return out << g.t1 << " vs. " << g.t2;
    }
};

int main(int argc, const char * argv[]) {
    
    Game game;
    Helper helper;
    
    bool gameIsOn = true;
    
    while (gameIsOn) {
        
        std::string input;
        
        std::cout << "Enter command: ";
        
        getline(std::cin, input);
        
        std::string startPrefix("Start:");
        
        if (!input.compare(0, startPrefix.size(), startPrefix)){
            std::vector<std::string> strings = helper.splitStringIntoVector(input);
            game = Game(strings[1], strings[3]);
        }else{
            
            if (game.started()){

                if (isdigit(input[0])){
                    game.addGoal(input);
                }
                else if (!input.compare("print")){
                    std::cout << game << std::endl;
                }
                else if (!input.compare("End")){
                    gameIsOn = false;
                }else{
                    std::cout << "input error - please type 'print' for game details" << std::endl;
                }
                
            }else{
                std::cout << "input error - please start a game through typing 'Start: '<Name of Home Team>' vs. '<Name of Away Team>" << std::endl;
            }
        }
    }
    
    return 0;
}

// Test data:
// Start: England vs. Portugal
// 11 England Haller
// 50 Portugal Daven