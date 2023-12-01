#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Link.h"
#include "Point.h"
using namespace std;

pair<int, int> addPoints (pair<int, int> a, pair<int, int> b){
    return {a.first + b.first, a.second + b.second};
}

Player::Player(int id) : id{id}, downloadCount{0}, virusCount{0}
{
    if (id == 1) {
        botLeft = {0, 0};
        right = Point{0, 1};
        up = Point{1, 0};
        linkIDs = "abcdefg";
    } else if (id == 2) {
        botLeft = {0, 0};
        right = {0, -1};
        up = {-1, 0};
        linkIDs = "ABCDEFG";
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
        Point tmp = botLeft + right;
        if (i == 3 || i == 4) {
            tmp = botLeft + up;
        }
        Link * newLink = new Link(linkIDs[i], tmp, type, strength);
        // Board.notify(newLink); <- notify the board that the link exists? (TO DO)
        links.push_back(newLink);
    }
}

void Player::init(){
    vector<string> layout = {"V1", "V2", "V3", "V4", "D1", "D2", "D3", "D4"};
    random_shuffle(layout.begin(), layout.end());
    for (int i=0; i<8; i++) {
        string link;
        link = layout[i];
        // handle error checking on link (TO DO)
        char type = link[0];
        int strength = link[1] - '0';
        // calculate coordinate of link
        Point tmp = botLeft + right;
        if (i == 3 || i == 4) {
            tmp = botLeft + up;
        }
        Link * newLink = new Link(linkIDs[i], tmp, type, strength);
        // Board.notify(newLink); <- notify the board that the link exists? (TO DO)
        links.push_back(newLink);
    }
}

void Player::moveLink(Link * l, Point dir) {
    l->move(dir);
    // Board.notify(l); <- notify the board that the link moved to update it?? (TO DO)
}

Player::~Player()
{

}

ostream &operator<<(ostream &out, const Player &l)
{
    
    return out;
}
