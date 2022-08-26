#include <bits/stdc++.h>
#include <string>
#include <iostream>
using namespace std;

enum PlayerType { BATSMAN, BOWLER, ALLROUNDER, WICKET_KEEPER };

class Player {
    private:
        string name;
        bool isNotout;
        int runsScored;
        int ballsPlayed;
        int ballsBowled;
        int maidenOvers; 
        int dotBalls;
        int fours, sixes;
        string playerType;
        int wicketsTaken;
        int runsConceded;

    public:
        Player();
        void setOut();
        void addBall();
        void scoredSix();
        void setNotout();
        void scoredFour();
        void tookWicket();
        void addDotBalls();
        double getEconomy(); 
        void setName(string);
        int getSixes() const;
        int getFours() const;
        int getMaidenOvers();
        void addMaidenOver();
        void addBallsBowled(); 
        void addRuns(int runs);
        double getStrikeRate();
        bool getNotoutStatus();
        void bowledMaidenOver();
        string getName() const;
        int getDotBalls() const;
        int getRunsScored() const;
        int getBallsPlayed() const;
        int getBallsBowled() const; 
        int getWicketsTaken() const;
        int getRunsConceded() const;
        void addRunsConceded(int runs);
};

Player::Player() {
    this->name = "";
    this->isNotout = false;
    this->runsScored = 0;
    this->ballsPlayed = 0;
    this->ballsBowled = 0;
    this->fours = 0;
    this->sixes = 0;
    this->wicketsTaken = 0;
    this->runsConceded = 0;
    this->dotBalls = 0;
    this->maidenOvers = 0;
    this->playerType = PlayerType::BATSMAN;
}
void Player::setName(string name) { 
    this->name = name; 
}
string Player::getName() const { 
    return this->name; 
}
void Player::addRuns(int runs) { 
    this->runsScored += runs;
}
int Player::getRunsScored() const { 
    return this->runsScored; 
}
void Player::scoredFour() {
    this->fours += 1;
    this->runsScored += 4;
}
int Player::getFours() const { 
    return this->fours; 
}
void Player::scoredSix() {
    this->sixes += 1;
    this->runsScored += 6;
}
int Player::getSixes() const { 
    return this->sixes; 
}
int Player::getBallsPlayed() const { 
    return this->ballsPlayed; 
}
int Player::getBallsBowled() const { 
    return this->ballsBowled; 
}
void Player::tookWicket() { 
    this->wicketsTaken += 1; 
}
int Player::getWicketsTaken() const { 
    return this->wicketsTaken; 
}
void Player::addRunsConceded(int runs) { 
    this->runsConceded += runs; 
}
int Player::getRunsConceded() const { 
    return this->runsConceded; 
}
void Player::setNotout() { 
    this->isNotout = true; 
}
void Player::setOut() { 
    this->isNotout = false;
}
void Player::addBall() { 
    this->ballsPlayed += 1;
}
void Player::addMaidenOver(){
    this->maidenOvers += 1;
};
int Player::getMaidenOvers(){
    return maidenOvers;
};
bool Player::getNotoutStatus() {
    return this->isNotout; 
}
double Player::getStrikeRate(){
    if(ballsPlayed == 0) return 0;
    return ((double)runsScored/(double)ballsPlayed)*100;
}
double Player::getEconomy(){
    if(ballsBowled == 0) return 0;
    double overs = (double)ballsBowled/6.0;
    return ((double)runsConceded/overs);
}
void Player::addDotBalls(){
    this->dotBalls += 1;
}
int Player::getDotBalls() const{
    return dotBalls;
}
void Player::addBallsBowled(){
    ballsBowled += 1;
} 
void Player::bowledMaidenOver(){
    maidenOvers += 1;
}





class Team {
    private:
        int score;
        int extras;
        string name;
        int wickets;
        int ballsPlayed;
        int battingIndex;
        int currentBowler;
        vector<Player> players;
        int currBowlerLastOverRuns;
        int strikePlayer, nonStrikePlayer;

    public:
        void swapStrike();
        void startBatting();
        void startBowling();
        void setName(string);
        int getScore() const;
        int getExtras() const;
        string getName() const;
        int getWickets() const;
        int getBallsPlayed() const;
        int getCurrentBowler() const;
        void printBattingScorecard();
        void playBall(string action);
        void printBowlingScorecard();
        void throwBall(string action);
        bool setBowler(string bowlerName);
        void setPlayers(vector<Player> players);
};

void Team::setName(string name) { 
    this->name = name; 
}
string Team::getName() const { 
    return this->name; 
}
int Team::getScore() const { 
    return this->score;
}
int Team::getWickets() const { 
    return this->wickets; 
}
int Team::getExtras() const { 
    return this->extras; 
}
int Team::getBallsPlayed() const { 
    return this->ballsPlayed; 
}
void Team::swapStrike() {
    int temp;
    temp = strikePlayer;
    strikePlayer = nonStrikePlayer;
    nonStrikePlayer = temp;
}
void Team::setPlayers(vector<Player> players) { 
    this->players = players; 
}
void Team::startBatting() {
    this->score = this->wickets = this->ballsPlayed = this->extras = 0;
    this->strikePlayer = 0;
    this->nonStrikePlayer = 1;
    this->battingIndex = 1;
    this->players[strikePlayer].setNotout();
    this->players[nonStrikePlayer].setNotout();
}
void Team::startBowling(){
    currentBowler = -1;
}
int Team::getCurrentBowler() const{
    return currentBowler;
}
bool Team::setBowler(string bowlerName){
    int newBowler = -1;

    for(int i=0; i<players.size(); ++i){
        if(players[i].getName() == bowlerName){
            newBowler = i;
        }
    }
    if(newBowler == -1){
        cout << "Bowler not found!!" << endl;
        return false;
    }
    if(newBowler == currentBowler){
        cout << "Can not give over to same bowler!!" << endl;
        return false;
    }

    currentBowler = newBowler;

    return true;
}
void Team::playBall(string action) {

    transform(action.begin(), action.end(), action.begin(), ::toupper);

    if (action == "W") {
        ++wickets;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].setOut();
        ++battingIndex;
        if (this->wickets < players.size()-1) {
            strikePlayer = battingIndex;
            players[strikePlayer].setNotout();
        }
    } else if (action == "WD") {
        ++extras;
        ++score;
    } else if (action == "0") {
        ++ballsPlayed;
        players[strikePlayer].addBall();
    } else if (action == "1") {
        ++score;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].addRuns(1);
        swapStrike();
    } else if (action == "2") {
        score += 2;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].addRuns(2);
    } else if (action == "3") {
        score += 3;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].addRuns(3);
        swapStrike();
    } else if (action == "4") {
        score += 4;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].scoredFour();
    } else if (action == "5") {
        score += 5;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].addRuns(5);
        swapStrike();
    } else if (action == "6") {
        score += 6;
        ++ballsPlayed;
        players[strikePlayer].addBall();
        players[strikePlayer].scoredSix();
    }

    if (action != "WD" && ballsPlayed % 6 == 0) {
        swapStrike();
    }
}
void Team::throwBall(string action){
  
    transform(action.begin(), action.end(), action.begin(), ::toupper);

    if (ballsPlayed % 6 == 0) {
        currBowlerLastOverRuns = players[currentBowler].getRunsConceded();
    }
    
    if (action == "W") {
        ++ballsPlayed;
        players[currentBowler].addDotBalls();
        players[currentBowler].addBallsBowled();
        players[currentBowler].tookWicket();
    } 
    else if (action == "WD") {
        players[currentBowler].addRunsConceded(1);
    } 
    else if (action == "0") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addDotBalls();
    } 
    else if (action == "1") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addRunsConceded(1);
    } 
    else if (action == "2") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addRunsConceded(2);
    } 
    else if (action == "3") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addRunsConceded(3);
    } 
    else if (action == "4") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addRunsConceded(4);
    } 
    else if (action == "5") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addRunsConceded(5);
    } 
    else if (action == "6") {
        ++ballsPlayed;
        players[currentBowler].addBallsBowled();
        players[currentBowler].addRunsConceded(6);
    }

    if (action != "WD" && ballsPlayed % 6 == 0) {
        int currBowlerThisOverRuns = players[currentBowler].getRunsConceded();
        if(currBowlerLastOverRuns == currBowlerThisOverRuns)
            players[currentBowler].bowledMaidenOver();
    }

}
void Team::printBattingScorecard() {

    cout << endl;
    cout << " ------------------ " << endl;
    cout << "Batting Scorecard for " << name << endl;

    for (Player p : players) {
        cout << p.getName();
        if (p.getNotoutStatus() == true) {
        cout << "*";
        }
        cout << " ";
        cout << p.getRunsScored() << " ";
        cout << p.getFours() << " ";
        cout << p.getSixes() << " ";
        cout << p.getBallsPlayed() << " ";
        cout << std::fixed;
        cout << std::setprecision(2);
        cout << p.getStrikeRate()  << " ";
        cout << endl;
    }

    cout << "Total : ";
    cout << score << "/" << wickets << endl;
    cout << "Overs : ";
    cout << ballsPlayed / 6 << "." << ballsPlayed % 6 << endl;
    cout << "Extras : ";
    cout << extras << endl;

    cout << " ------------------ " << endl;
    cout << endl;
}
void Team::printBowlingScorecard(){
    cout << endl;
    cout << " ------------------ " << endl;
    cout << "Bowling Scorecard for " << name << endl;
    for (Player p : players) {
        cout << p.getName();

        cout << " ";
        cout << p.getRunsConceded() << " ";
        cout << p.getDotBalls() << " ";
        cout << p.getMaidenOvers() << " ";
        cout << p.getWicketsTaken() << " ";
        cout << p.getBallsBowled()/6 << "." << p.getBallsBowled()%6 << " ";
        cout << std::fixed;
        cout << std::setprecision(2);
        cout << p.getEconomy()  << " ";
        cout << endl;
    }


    cout << " ------------------ " << endl;
    cout << endl;
}





  
class Match {
    private:
        Team battingTeam, bowlingTeam;
        int totalOvers, players;
        int currentInning;
    public:
        void startGame();
        void setBattingTeam(Team team);
        void setBowlingTeam(Team team);
        void setTotalOvers(int overs);
        void setPlayers(int players);
};

void Match::setBattingTeam(Team team){
    this->battingTeam = team;
}
void Match::setBowlingTeam(Team team){
    this->bowlingTeam = team;
}
void Match::setTotalOvers(int overs){
    this->totalOvers = overs;
}
void Match::setPlayers(int players){
    this->players = players;
}
void Match::startGame(){
  
    vector<Player> battingOrder;
    
    cout << "Batting Order for " << battingTeam.getName() << " : " << endl;
    for(int i=0; i<players; ++i){
        string name; cin >> name;
        Player p;
        p.setName(name);
        battingOrder.push_back(p);
    }
    battingTeam.setPlayers(battingOrder);
    battingTeam.startBatting();

    battingOrder.clear();

    cout << "Batting Order for " << bowlingTeam.getName() << " : " << endl;
    for(int i=0; i<players; ++i){
        string name; cin >> name;
        Player p;
        p.setName(name);
        battingOrder.push_back(p);
    }
    bowlingTeam.setPlayers(battingOrder);
    bowlingTeam.startBowling();

    string lastAction;
  
    while(battingTeam.getBallsPlayed() < totalOvers*6){
 
        if(lastAction != "wd" && battingTeam.getBallsPlayed() % 6 == 0){
            bool flag = false;
            while(!flag){
                cout << "Bowler Name : ";
                string name; cin >> name;
                flag = bowlingTeam.setBowler(name);
            }
            cout << "Over " << (battingTeam.getBallsPlayed() / 6) + 1 << endl;
        }
        
        string action; cin >> action;
        battingTeam.playBall(action);
        bowlingTeam.throwBall(action);

        lastAction = action;

        if(battingTeam.getWickets() == players-1){
            battingTeam.printBattingScorecard();
            break;
        } 
        
        if(action != "wd" && battingTeam.getBallsPlayed() % 6 == 0){
            battingTeam.printBattingScorecard();
            bowlingTeam.printBowlingScorecard();
        }
    }

    bowlingTeam.startBatting();
    battingTeam.startBowling();

    lastAction = "";

    while(bowlingTeam.getBallsPlayed() < totalOvers*6){

        if(lastAction != "wd" && bowlingTeam.getBallsPlayed() % 6 == 0){
            bool flag = false;
            while(!flag){
                cout << "Bowler Name : ";
                string name; cin >> name;
                flag = battingTeam.setBowler(name);
            }
            cout << "Over " << (bowlingTeam.getBallsPlayed() / 6) + 1 << endl;
        }
        
        string action; cin >> action;
        bowlingTeam.playBall(action);
        battingTeam.throwBall(action);

        lastAction = action;
        
        if(bowlingTeam.getWickets() == players-1){
            bowlingTeam.printBattingScorecard();
            battingTeam.printBowlingScorecard();
            break;
        } 

        if(bowlingTeam.getScore() > battingTeam.getScore()){
            bowlingTeam.printBattingScorecard();
            battingTeam.printBowlingScorecard();
            break;
        }
        
        if(action != "wd" && bowlingTeam.getBallsPlayed() % 6 == 0){
            bowlingTeam.printBattingScorecard();
            battingTeam.printBowlingScorecard();
        }
    }

    cout << "Result ";

    if(bowlingTeam.getScore() > battingTeam.getScore()){
        cout << bowlingTeam.getName() << " won by ";
        cout << (players - bowlingTeam.getWickets()) << " Wickets";
    }
    else if(battingTeam.getScore() > bowlingTeam.getScore()){
        cout << battingTeam.getName() << " won by ";
        cout << (battingTeam.getScore() - bowlingTeam.getScore()) << " Runs";
    }
    else{
        cout << "Match Tied";
    }
    
    cout << endl;
}

int main() { 
    Match m = Match();

    int players, overs;

    cout << "No. of players for each team:";
    cin >> players;
    cout << "No. of overs:";
    cin >> overs;

    m.setPlayers(players);
    m.setTotalOvers(overs);

    Team t1,t2;
    t1.setName("Team 1");
    t2.setName("Team 2");

    m.setBattingTeam(t1);
    m.setBowlingTeam(t2);

    m.startGame();

    return 0;
}