#include <iostream>
#include <vector>

using namespace std;
const int MAX = 5;

enum Receiver{ LIGHT = 0, FAN, DOOR, OVEN, NONE};

class Command{ public: virtual void execute() = 0; };
class Light{ public: void on(){ cout << "\nLights on!"; }; void off(){ cout << "\nLights off!"; } };
class Fan{ public: void on(){ cout << "\nFan on!"; }; void off(){ cout << "\nFan off!"; } };


class NullCommand : public Command{ public: void execute() { cout << "Null command: does nothing\n"; }; };
        

class LightOn : public Command{ private: Light *lightOn;
    public: LightOn(Light *lightOn): lightOn(lightOn){}; 
        void execute() { lightOn->on(); }; };
class LightOff : public Command{ private: Light *lightOff;
    public: LightOff(Light *lightOff): lightOff(lightOff){}; 
        void execute() { lightOff->off(); }; };
class FanOn : public Command{ private: Fan *fanOn;
    public: FanOn(Fan *fanOn): fanOn(fanOn){}; 
        void execute() { fanOn->on(); }; };
class FanOff : public Command{ private: Fan *fanOff;
    public: FanOff(Fan *fanOff): fanOff(fanOff){}; 
        void execute() { fanOff->off(); }; };


class Remote{
    private: vector<Command*> onCommands, offCommands;
    public:
        Remote(): onCommands(MAX), offCommands(MAX){
            Command *nullcmd = new NullCommand;
            for(int i = 0; i < MAX; i++){
                onCommands[i] = nullcmd;
                offCommands[i] = nullcmd;
            }
        };
        
        void setCommand(Receiver id, Command *on, Command *off){
            onCommands[id] = on;
            offCommands[id] = off;
        }
        
        void onButton(Receiver id){ onCommands[id]->execute(); }
        void offButton(Receiver id){ offCommands[id]->execute(); }
};


int main()
{
    Light *light = new Light;
    Fan *fan = new Fan;
    
    LightOn *lonCmd = new LightOn(light);
        LightOff *loffCmd = new LightOff(light);
            FanOn *fonCmd = new FanOn(fan);
                FanOff *foffCmd = new FanOff(fan);
                    NullCommand *nullOnCmd = new NullCommand();
                    NullCommand *nullOffCmd = new NullCommand();
                    
    Remote *remote = new Remote;
    
    remote->setCommand(LIGHT, lonCmd, loffCmd);
    remote->onButton(LIGHT);
    remote->offButton(LIGHT);
    
    remote->setCommand(FAN, fonCmd, foffCmd);
    remote->onButton(FAN);
    remote->offButton(FAN);
    
    
    delete light, lonCmd, loffCmd;
	delete fan, fonCmd, foffCmd;
	delete remote;
    
    return 0;
}
