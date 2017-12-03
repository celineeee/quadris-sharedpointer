#ifndef subject_h
#define subject_h
#include <vector>

struct State;
class Observer;
class Subject {
    std::vector<shared_ptr<Observer>> observers;
    State *state = nullptr;
protected:
	Subject &operator=(const Subject &other);
public:
	virtual ~Subject() = 0;
    void attach(shared_ptr<Observer>shared_ptr<Observer>); //board should also set cell.ob
    void detach(shared_ptr<Observer>);
    void notifyObservers();
    void setState(shared_ptr<State> s);
    shared_ptr<State> getState();
    std::vector<shared_ptr<Observer>> getObservers() const;
    void setObservers(std::vector<shared_ptr<Observer>> given);
};

#endif /* subject_hpp */
