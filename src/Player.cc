#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Ability.h"
#include "LinkBoost.h"
#include "FirewallAbility.h"
#include "Download.h"
#include "Polarize.h"
#include "Scan.h"
#include "Recycle.h"
#include "Exchange.h"
#include "Immobilize.h"

#include "Board.h"
using namespace std;

pair<int, int> addPoints (pair<int, int> a, pair<int, int> b){
    return {a.first + b.first, a.second + b.second};
}

Player::Player(int id, Board * board) : id{id}, downloadCount{0}, virusCount{0}, abilityCount{5}, board{board}
{
    if (id == 0) {
        botLeft = {0, 0};
        right = {0, 1};
        up = {1, 0};
        linkIDs = "abcdefgh";
    } else if (id == 1) {
        botLeft = {7, 7};
        right = {0, -1};
        up = {-1, 0};
        linkIDs = "ABCDEFGH";
    }
}

void Player::init(string layout){
    istringstream iss{layout};
    for (int i=0; i<8; i++) {
        string link;
        iss >> link;
        // handle error checking on link (TO DO)
        char type = link[0];
        int strength = link[1] - '0';
        // calculate coordinate of link
        Point tmp = botLeft + right * i;
        if (i == 3 || i == 4) {
            tmp = tmp + up;
        }
        Link * newLink = new Link(linkIDs[i], tmp, up, right, type, strength, this);
        // Board.notify(newLink); <- notify the board that the link exists? (TO DO)
        links.push_back(newLink);
    }
    notifyObservers();
}

void Player::init(){
    cout << "DEBUG: start player default init" << '\n';
    vector<string> layout = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};
    random_shuffle(layout.begin(), layout.end());
    cout << "DEBUG: shuffled" << '\n';
    for (int i=0; i<8; i++) {
        string link;
        link = layout[i];
        // handle error checking on link (TO DO)
        char type = link[0];
        int strength = link[1] - '0';
        cout << "DEBUG: got link " << link << '\n';
        // calculate coordinate of link
        cerr << "DEBUG: botLeft, right " << botLeft << ' ' << right << '\n';
        Point tmp = botLeft + right * i;
        cout << "DEBUG: " << tmp.y << ", "<< tmp.x << '\n';
        if (i == 3 || i == 4) {
            tmp = tmp + up;
        }
        cout << "DEBUG: make new link" << '\n';
        Link * newLink = new Link(linkIDs[i], tmp, up, right, type, strength, this);
        // Board.notify(newLink); <- notify the board that the link exists? (TO DO)
        links.push_back(newLink);
    }
    notifyObservers();
}

void Player::initAbility(string abilityList) {
    int freq[26];
    for (int i = 0; i < 26; ++i) {
        freq[i] = 0; // set all values to 0
    }
    for (int i = 0; i < abilityList.length(); ++i) {
        ++freq[abilityList[i] - 'A'];
        if (freq[abilityList[i] - 'A'] > 2) {
            throw logic_error{"Error: Cannot have more than 2 of the same ability in one hand."};
        }
        if (abilityList[i] == 'L') {
            abilities.push_back(new LinkBoost(i+1, this));
        } else if (abilityList[i] == 'F') {
            abilities.push_back(new FirewallAbility(i+1, this));
        } else if (abilityList[i] == 'D') {
            abilities.push_back(new Download(i+1, this));
        } else if (abilityList[i] == 'P') {
            abilities.push_back(new Polarize(i+1, this));
        } else if (abilityList[i] == 'S') {
            abilities.push_back(new Scan(i+1, this));
        } else if (abilityList[i] == 'R') {
            abilities.push_back(new Recycle{i+1, this});
        } else if (abilityList[i] == 'E') {
            abilities.push_back(new Exchange(i+1, this));
        } else if (abilityList[i] == 'I') {
            abilities.push_back(new Immobilize(i+1, this));
        } else {
            throw logic_error{"Error: Not a valid ability"};
        }
    }
}

void Player::initAbilityParams(int id, char c, Player *other) {
    if (c == 'R') {
        int a;
        cin >> a;
        Recycle* r = dynamic_cast<Recycle*>(abilities[id - 1]);
        r->setAbility(abilities[a - 1]);
    } else if (c == 'F') {
        int y, x;
        cin >> y >> x;
        FirewallAbility* f = dynamic_cast<FirewallAbility*>(abilities[id - 1]);
        f->setCell(y, x, board);
    } else if (c == 'E'){
        int a, b;
        cin >> a >> b;
        Link *link1 = getLinkById(a), *link2 = getLinkById(b);
        Exchange* e = dynamic_cast<Exchange*>(abilities[id - 1]);
        e->setLinks(link1, link2, board);
    } else if (c == 'P') {
        char linkID;
        cin >> linkID;
        Link *curLink = getLinkById(linkID);
        Polarize* e = dynamic_cast<Polarize*>(abilities[id - 1]);
        e->setLink(curLink);
    } else if (c == 'L') {
        char linkID;
        cin >> linkID;
        Link *curLink = getLinkById(linkID);
        LinkBoost* e = dynamic_cast<LinkBoost*>(abilities[id - 1]);
        e->setLink(curLink);
    }
    else {
        char linkID;
        cin >> linkID;
        Link* curLink = other->getLinkById(linkID);
        if (c == 'D') {
            Download* e = dynamic_cast<Download*>(abilities[id - 1]);
            e->setLink(curLink, board);
        } else if (c == 'S') {
            Scan* e = dynamic_cast<Scan*>(abilities[id - 1]);
            e->setLink(curLink);
        } else if (c == 'I') {
            Immobilize* e = dynamic_cast<Immobilize*>(abilities[id - 1]);
            e->setLink(curLink);
        }
    }
}

vector<Link*>::iterator Player::getLinkBeginIterator() {
    return links.begin();
}

vector<Link*>::iterator Player::getLinkEndIterator() {
    return links.end();
}

vector<Ability*>::iterator Player::getAbilityBeginIterator() {
    cout << "DEBUG: ability vector size: " << abilities.size() << endl;
    return abilities.begin();
}

vector<Ability*>::iterator Player::getAbilityEndIterator() {
    return abilities.end();
}

void Player::makeMove(Link * l, Point dir) {
    Point oldPos = l->getPoint();
    Point newPos = l->getNewPos(dir, up, right);
    cerr << "DEBUG: new pos obtained " << newPos << '\n';
    if (newPos.outOfBounds(up, right, botLeft)) { //if out of bounds, throw an exception
        throw std::logic_error("Invalid move: Target position (" + std::to_string(newPos.y) + "," + std::to_string(newPos.x) + ") is out of bounds");
    }
    else if (newPos.inDownloadZone(up, right, botLeft)) { //if it reached the end of the board, download to its player
        l->getPlayer()->downloadLink(l);
        return;
    }
    board->getCell(newPos)->attachLink(l);
    board->getCell(oldPos)->detachLink();

    l->move(dir, up, right);
    // board.moveLink
    // Board.notify(l); <- notify the board that the link moved to update it?? (TO DO)
    notifyObservers();
}

// called by anything that forces player to download
//     for example:
//         - player moves to end of board
//             - board calls download link on that Link
//         - board handles battle between link
void Player::downloadLink(Link * l) {
    cerr << "DEBUG: download link\n";
    cerr << "DEBUG: " << l->getType() << '\n';
    if (l->getType() == 'V') {
        virusCount ++;
    } else if (l->getType() == 'D') {
        downloadCount ++;
    }
    downloaded.push_back(l);
    // l->getPlayer()->removeLink(l);
    cerr << "DEBUG: set dead\n"; 
    l->setDead();
    notifyObservers();
    cerr << "DEBUG: Finished downloading link\n";
}

void Player::removeLink(Link * l) {
    // TO DO: fix this
    cerr << "DEBUG: Removing link\n"; 
    l->setDead();
    notifyObservers();
    cerr << "DEBUG: Finished removing link\n";
}

void Player::useAbility(int abilityId) {
    abilities[abilityId - 1]->useAbility();
    --abilityCount;
    notifyObservers();
}

Link * Player::getLinkById(char id) {
    for (Link * l : links) {
        if (id == l->getId()) {
            return l;
        }
    }
}

Ability * Player::getAbility(int id) {
    return abilities[id - 1];
}

int Player::getAbilityCount() const{
    return abilityCount;
}

int Player::getDownloadCount(){
    return downloadCount;
}

int Player::getVirusCount(){
    return virusCount;
}

int Player::getId(){
    return id;
}

Player::~Player()
{

}

vector<Link*>::iterator Player::getDownloadBeginIterator() {
    return downloaded.begin();
}

vector<Link*>::iterator Player::getDownloadEndIterator() {
    return downloaded.end();
}

void Player::addObserver(Observer * o) {
    observers.push_back(o);
}

void Player::notifyObservers(){
  for (Observer * o: observers) {
    o->notify(*this);
  }
}

ostream &operator<<(ostream &out, const Player &p)
{
    // TO DO: make player have an observer so text display can do this
    out << "Player 1:\n";
    out << "Downloaded:";
    for (int i=0; i<p.downloaded.size(); i++) {
        if (i == 0) {
            out << ' ';
        } else {
            out << ", ";
        }
        out << p.downloaded[i]->getType() << p.downloaded[i]->getStrength();
    }
    out << "\n";
    out << "Abilities: " << p.getAbilityCount() << "\n";
    for (int i=0; i<4; i++) {
        out << *(p.links[i]) << ' ';
    }
    out << '\n';
    for (int i=4; i<8; i++) {
        out << *(p.links[i]) << ' ';
    }
    out << '\n';
    return out;
}
