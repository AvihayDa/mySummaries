#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

using namespace std;

void beep(){
    cout << '\a' << endl;
}

class Action{
public:
    virtual ~Action() = default;
    virtual void applyAction() = 0;
};

class PrintAction : public Action{
private:
    string msg;
public:
    PrintAction(const string& message): msg(message) {}

    void applyAction() override{
        cout << msg << endl;
    }
};

class BeepAction : public Action{
public:
    void applyAction() override{
        beep();
    }
};

class MacroAction : public Action{
private:
    vector<unique_ptr<Action>> actions;
public:
    MacroAction(vector<unique_ptr<Action>>& actions_arg){
        for (auto& action : actions_arg) {
            this->actions.push_back(std::move(action));
        }
    }

    void applyAction() override{
        for(auto& action : actions){
            action->applyAction();
        }
    }

};

class KeyboardManager{
private:
    map<string, unique_ptr<Action>> keysMap;


public:
    void bind(const string& key, unique_ptr<Action> action){
        keysMap[key] = std::move(action);
    }

    void press(const string& key){
        if(keysMap.count(key) == 0) return;
        keysMap[key]->applyAction();
    }

};


int main(){
    KeyboardManager manager;
    string key1 = "A";
    manager.bind(key1, make_unique<BeepAction>());
    string key2 = "B";
    manager.bind(key2, make_unique<PrintAction>("oopsy..."));
    manager.press(key1);
    manager.press(key2);


    string key3 = "C";
    vector<unique_ptr<Action>> actions;
    actions.push_back(make_unique<BeepAction>());
    actions.push_back(make_unique<PrintAction>("Hello World!"));
    actions.push_back(make_unique<BeepAction>());
    manager.bind(key3, make_unique<MacroAction>(actions));
    manager.press(key3);

    return 0;
}
