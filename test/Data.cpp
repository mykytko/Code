#include "PriorityQueue.hpp"
#include <cstdlib>
#define COMPARE damage //hp/damage/skill

Data::Data(){
    hp = rand()%100+1;
    damage = rand()%100+1;
    skill = rand()/1000.0;
}

bool Data::operator< (const Data& e) const{
    return COMPARE < e.COMPARE;
}
bool Data::operator> (const Data& e) const{
    return e<(*this); //A const member function can be called by any type of object. Non-const functions can be called by non-const objects only.
}
bool Data::operator== (const Data& e) const{
    return COMPARE == e.COMPARE;
}
bool Data::operator<= (const Data& e) const{
    return (*this) < e ? true : (*this) == e;
}
bool Data::operator>= (const Data& e) const{
    return (*this) > e ? true : (*this) == e;
}
