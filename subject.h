#ifndef subject_h
#define subject_h
#include <vector>

struct State;
class Observer;
class Subject {
    std::vector<Observer *> observers;
    State *state = nullptr;
protected:
	Subject &operator=(const Subject &other);
public:
	virtual ~Subject() = 0;
    virtual void attach(Observer *); //board should also set cell.ob
    void detach(Observer *);
    void notifyObservers();
    void setState(State *s);
    State *getState();
    std::vector<Observer *> getObservers() const;
    void setObservers(std::vector<Observer *> given);
};

#endif /* subject_hpp */
