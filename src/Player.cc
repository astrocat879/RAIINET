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

using namespace std;

pair<int, int> addPoints (pair<int, int> a, pair<int, int> b){
    return {a.first + b.first, a.second + b.second};
}

Player::Player(int id) : id{id}, downloadCount{0}, virusCount{0}, abilityCount{5}
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
        Link * newLink = new Link(linkIDs[i], tmp, type, strength, this);
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
        Link * newLink = new Link(linkIDs[i], tmp, type, strength, this);
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
            abilities.push_back(new LinkBoost{i+1, this});
        } else if (abilityList[i] == 'F') {
            
        } else if (abilityList[i] == 'D') {
            abilities.push_back(new Download{i+1, this});
        } else if (abilityList[i] == 'P') {
            abilities.push_back(new Polarize(i+1, this));
        } else if (abilityList[i] == 'S') {
            abilities.push_back(new Scan(i+1, this));
        } else if (abilityList[i] == 'R') {
            abilities.push_back(new Recycle{i+1, this});
        } else if (abilityList[i] == 'E') {
            
        } else if (abilityList[i] == 'I') {
            
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
        int x, y;
        cin >> x >> y;
        FirewallAbility* f = dynamic_cast<FirewallAbility*>(abilities[id - 1]);
        f->setCell(x, y);
    } else if (c == 'E'){
        int a, b;
        cin >> a >> b;
        Link *link1 = getLinkById(a), *link2 = getLinkById(b);
        Exchange* e = dynamic_cast<Exchange*>(abilities[id - 1]);
        e->setLinks(link1, link2);
    } else {
        char linkID;
        cin >> linkID;
        Link* curLink = other->getLinkById(linkID);
        if (c == 'L') {
            LinkBoost* e = dynamic_cast<LinkBoost*>(abilities[id - 1]);
            e->setLink(curLink);
        } else if (c == 'D') {
            Download* e = dynamic_cast<Download*>(abilities[id - 1]);
            e->setLink(curLink);
        } else if (c == 'P') {
            Polarize* e = dynamic_cast<Polarize*>(abilities[id - 1]);
            e->setLink(curLink);
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

void Player::moveLink(Link * l, Point dir) {
    Point newPos = l->getNewPos(dir, up, right);
    cerr << "DEBUG: new pos obtained " << '\n';
    if (newPos.outOfBounds(up, right, botLeft)) { //if out of bounds, throw an exception
        throw std::invalid_argument("End position (" + std::to_string(newPos.y) + "," + std::to_string(newPos.x) + ") is out of bounds");
    }
    else if (newPos.inDownloadZone(up, right, botLeft)) { //if it reached the end of the board, download to its player
        l->getPlayer()->downloadLink(l);
        return;
    }
    cerr << "DEBUG: pass bound checks " << '\n';
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
    l->getPlayer()->removeLink(l);
    notifyObservers();
}

void Player::removeLink(Link * l) {
    cerr << "DEBUG: Removing link\n"; 
    links.erase(find(links.begin(), links.end(), l));
    for (int i=0;i<links.size();i++) {
        if (links[i]->getId() == l->getId()) {
            links.erase(links.begin() + i);
            return;
        }
    }
    notifyObservers();
}

void Player::useAbility(int abilityId) {
    abilities[abilityId - 1]->useAbility();
    --abilityCount;
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
