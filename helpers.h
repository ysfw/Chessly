#pragma once
#include <bits/stdc++.h>
using namespace std;

string moveTOstring(pair<size_t,size_t> Position){
    string move="";
    move+=(static_cast<char>('a' + Position.second));
    move+= to_string(Position.first+1);
    return move;
}

pair<size_t,size_t> stringTOmove(string move){
    
    size_t firstCoord,SecondCoord;
    char first = move [0], second = move[1];
    firstCoord = static_cast<size_t>(first - 'a');
    SecondCoord = static_cast<size_t>(second - '0') -1;
    return {firstCoord,SecondCoord};
}