#include "subject.h"
#include "observer.h"
#include "state.h"
#include <iostream>

Subject::~Subject() {
}

Subject &Subject::operator=(const Subject &other){
    observers.clear();
    for (int i = 0; i < other.observers.size(); i++) {
        observers.emplace_back(other.getObservers()[i]);
        //observers[i] = other.observers[i];
    }
    return *this;
}

void Subject::attach(shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for (auto &ob: this->observers) ob->notify(*this);
}

void Subject::detach(shared_ptr<Observer> o) {
    for (auto it=observers.begin(); it !=observers.end(); ++it) {
        if (*it==o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::setState(shared_ptr<State> s) {
    this->state = s;
}

shared_ptr<State> Subject::getState() {
    return this->state;
}

std::vector<shared_ptr<Observer>> Subject::getObservers() const {
    return observers;
}

void Subject::setObservers(std::vector<shared_ptr<Observer>> given) {
    observers = given;
}