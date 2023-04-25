#include <iostream>
#include <vector>

using namespace std;

const int MAX = 4;
enum Receiver{ CUT, COPY, PASTE, NONE };

class Command{ public: virtual void execute() = 0; };
class NullCommand: public Command{ public: virtual void execute(){ 
    cout << "\nNull Command: Nothing happened.";
}; };


class Cut: public Command{ public: virtual void execute(){ 
    cout << "\nCutting...";
}; };
class Copy: public Command{ public: virtual void execute(){ 
    cout << "\nCopying...";
}; };
class Paste: public Command{ public: virtual void execute(){ 
    cout << "\nPasting...";
}; };


class Order{
    private:
        vector<Command*> orders;
    public:
        Order(): orders(MAX){
            Command *nullCmd = new NullCommand;
            for(int i = 0; i < MAX; i++){
                orders[i] = nullCmd;
            }
        }
        
        void setOrder(Receiver id, Command *cmd){
            orders[id] = cmd;
        }
        void executeOrder(Receiver id){
            orders[id]->execute();
        }
};

int main() {
    Cut *cut = new Cut;
    Copy *copy = new Copy;
    Paste *paste = new Paste;
    NullCommand *nullcmd = new NullCommand;
    
    Order *control = new Order;
    control->setOrder(CUT, cut);
    control->executeOrder(CUT);
    
    control->setOrder(COPY, copy);
    control->executeOrder(COPY);
    
    control->setOrder(PASTE, paste);
    control->executeOrder(PASTE);
    
    control->setOrder(NONE, nullcmd);
    control->executeOrder(NONE);
    
    delete cut, copy, paste;
    delete control, nullcmd;
    return 0;
}
