#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

class User;

class ChatMediator {
public:
    virtual void addUser(User* user) = 0;
    virtual void removeUser(User* user) = 0;
    virtual void sendMessage(const std::string& msg, User* sender) = 0;
    virtual void sendPrivate(const std::string& msg, User* sender, const std::string& recipient) = 0;
    virtual ~ChatMediator() {}
};

class User {
protected:
    std::string _name;
    ChatMediator* _mediator;

public:
    User(const std::string& name, ChatMediator* mediator) : _name{name}, _mediator{mediator} {}
    std::string getname() const { return _name; }
    void send(const std::string& msg) {
        _mediator->sendMessage(msg, this);
    }
    void sendPrivate(const std::string& msg, const std::string& name) {
        _mediator->sendPrivate(msg, this, name);
    }
    virtual void receive(const std::string& msg, const std::string& sender) = 0;
    virtual ~User() {}
};

class concreteUser : public User {
public:
    concreteUser(const std::string& name, ChatMediator* mediator) : User(name, mediator) {}
    void receive(const std::string& msg, const std::string& sender) override {
        std::cout << this->getname() << " received the message: " << msg << " from " << sender << std::endl;
    }
};

class concreteMediator : public ChatMediator {
    std::vector<User*> users;

public:
    void addUser(User* user) override {
        users.push_back(user);
        std::cout << user->getname() << " joined the chat" << std::endl;
    }

    void removeUser(User* user) override {
        users.erase(std::remove(users.begin(), users.end(), user), users.end());
        std::cout << user->getname() << " left the chat." << std::endl;
    }

    void sendMessage(const std::string& msg, User* sender) override {
        for (auto* user : users) {
            if (user != sender) {
                user->receive(msg, sender->getname());
            }
        }
    }

    void sendPrivate(const std::string& msg, User* sender, const std::string& recipient) override {
        int found = 0;
        for (auto* user : users) {
            if (user->getname() == recipient) {
                user->receive(msg, sender->getname());
                found = 1;
                break;
            }
        }
        if (!found) {
            std::cout << recipient << " not found" << std::endl;
        }
    }
};

int main() {
    concreteMediator chatroom;

    concreteUser Alice("Alice", &chatroom);
    concreteUser Bob("Bob", &chatroom);
    concreteUser Max("Max", &chatroom);

    chatroom.addUser(&Alice);
    chatroom.addUser(&Bob);
    chatroom.addUser(&Max);

    Bob.send("Hi everyone");
    Alice.sendPrivate("Did u do your homework Max?", "Max");

    chatroom.removeUser(&Max);



    return 0;
}

