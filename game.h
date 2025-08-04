#pragma once
#include <bits/stdc++.h>
#include "piece.h"
using namespace std;

class player
{
private:
    stack<pair<piece,string>> moves;
    stack<pair<piece,string>> captured;
    pair<int,int> time; //minute:second
    int rating;
public:
    player(int initialRating, pair<int,int> gameTime);
    ~player();

};

player::player(int initialRating, pair<int,int> gameTime)
{
    rating = initialRating;
    time = gameTime;
}

player::~player()
{
}
