#include <string>
#include <memory>
class Message {
    public:
        virtual std::string getText(const std::string& message) = 0;
        virtual ~Message() {}
};

class PlainMessage : public Message {
    public:
        std::string getText(const std::string& message) override {
            return message;
        }
};

class Decorator : public Message {
    protected:
        Message* ptr;
    public:
        virtual ~Decorator() {delete ptr;}
        Decorator(Message* msg) : ptr{msg} {}
        virtual std::string getText (const std::string& message) = 0;

};

class UpperCaseDecorator : public Decorator {
    public:
        UpperCaseDecorator(Message* msg) : Decorator(msg) {}
        std::string getText(const std::string& message) override {
            std::string messg = (ptr->getText(message));
            for (char& c : messg) {
                toupper(c);
            }   
            return messg;        
        }
};

class LowerCaseDecorator : public Decorator {
    public:
        LowerCaseDecorator(Message* msg) : Decorator(msg) {}
        std::string getText(const std::string& message) override {
            std::string messg = (ptr->getText(message));
            for (char&
                 c : messg) {
                tolower(c);
            }   
            return messg;        
        }
};

class EncryptedMessageDecorator : public Decorator {
    private:
        std::unordered_map<char,char> cipher;
    public:
    EncryptedMessageDecorator(Message* msg, const std::unordered_map<char,char>& map) : Decorator(msg), cipher{map} {}
    std::string getText(const std::string& message) override {
        std::string result = ptr->getText(message);   
        for (auto& c : result) {
            if(cipher.count(c)) {
                c = cipher.at(c);
            }
        }
        return result;
    }
};
