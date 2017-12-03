#include "subject.h"
#include "observer.h"
#include "state.h"
#include <iostream>

Subject::~Subject() {
    delete state;
}

Subject &Subject::operator=(const Subject &other){
    delete state;
    observers.clear();
    for (int i = 0; i < other.observers.size(); i++) {
        observers.emplace_back(other.getObservers()[i]);
        //observers[i] = other.observers[i];
    }
    return *this;
}

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for (auto &ob: this->observers) ob->notify(*this);
}

void Subject::detach(Observer *o) {
    for (auto it=observers.begin(); it !=observers.end(); ++it) {
        if (*it==o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::setState(State *s) {
    delete state;
    this->state = s;
}

State *Subject::getState() {
    return this->state;
}

std::vector<Observer *> Subject::getObservers() const {
    return observers;
}

void Subject::setObservers(std::vector<Observer *> given) {
    observers = given;
}