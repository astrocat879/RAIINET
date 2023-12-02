#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Player.h"
using namespace std;

pair<int, int> addPoints (pair<int, int> a, pair<int, int> b){
    return {a.first + b.first, a.second + b.second};
}

Player::Player(int id) : id{id}, downloadCount{0}, virusCount{0}
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
        Link * newLink = new Link(linkIDs[i], tmp, type, strength);
        // Board.notify(newLink); <- notify the board that the link exists? (TO DO)
        links.push_back(newLink);
    }
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
        Link * newLink = new Link(linkIDs[i], tmp, type, strength);
        // Board.notify(newLink); <- notify the board that the link exists? (TO DO)
        links.push_back(newLink);
    }
}

vector<Link*>::iterator Player::getLinkBeginIterator() {
    return links.begin();
}

vector<Link*>::iterator Player::getLinkEndIterator() {
    return links.end();
}



void Player::moveLink(Link * l, Point dir) {
    Point newPos = l->getNewPos(dir);
    if (newPos.outOfBounds(up, right, botLeft)) { //if out of bounds, throw an exception
        throw std::invalid_argument("End position (" + std::to_string(newPos.y) + "," + std::to_string(newPos.x) + ") is out of bounds");
    }
    else if (newPos.inDownloadZone(up, right, botLeft)) { //if it reached the end of the board, download to its player
        l->getPlayer()->downloadLink(l);
        return;
    }
    l->move(dir);
    // board.moveLink
    // Board.notify(l); <- notify the board that the link moved to update it?? (TO DO)
}

// called by anything that forces player to download
//     for example:
//         - player moves to end of board
//             - board calls download link on that Link
//         - board handles battle between link
void Player::downloadLink(Link * l) {
    if (l->getType() == 'V') {
        virusCount ++;
    } else if (l->getType() == 'D') {
        downloadCount ++;
    }
    downloaded.push_back(l);
    l->getPlayer()->removeLink(l);
}

void Player::removeLink(Link * l) {
    links.erase(find(links.begin(), links.end(), l));
}

Link * Player::getLinkById(char id) {
    for (Link * l : links) {
        if (id == l->getId()) {
            return l;
        }
    }
}

int Player::getAbilityCnt(){
    return abilities.size();
}

int Player::getId(){
    return id;
}

Player::~Player()
{

}



ostream &operator<<(ostream &out, const Player &p)
{
    // TO DO: make player have an observer so text display can do this
    out << "Player 1:\n";
    out << "Downloaded: ";
    for (int i=0; i<p.downloaded.size(); i++) {
        if (i == 0) {
            out << ' ';
        } else {
            out << ", ";
        }
        out << p.downloaded[i]->getType() << p.downloaded[i]->getStrength();
    }
    out << "\n";
    out << "Abilities: " << p.abilities.size() << "\n";
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
