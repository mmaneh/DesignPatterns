#include <iostream>
class Device {
  
    public:
        virtual void isEnabled() = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual int getVolume() = 0;
        virtual void setVolume(int) = 0;
        virtual int getStatus() = 0;
        virtual void setStatus(int) = 0;
        virtual ~Device() {}

};

class TV : public Device {
    private:
        int volume = 0;
        int status = 0;
    public:
        int getStatus() override{
            return status;
        }
        void setStatus(int st) override{
            status = st;
        }
        void isEnabled() override {
            if(status) std::cout << "TV is enabled" << std::endl;
            else std::cout << "TV is not enabled" << std::endl;
        }
        void enable() override { status = 1;}
        void disable() override {status = 0;}
        int getVolume() override {
            return volume;
        }
        void setVolume(int vol) override {
                volume = vol;
        }
};
class Radio : public Device {
    private:
        int volume = 0;
        int status = 0;
    public:
        void isEnabled() override {
            if(status) std::cout << "TV is enabled" << std::endl;
            else std::cout << "TV is not enabled" << std::endl;
        }
        void enable() override { status = 1;}
        void disable() override {status = 0;}
        int getVolume() override {
            return volume;
        }
        void setVolume(int vol) override {
                volume = vol;
        }   
        int getStatus() override{
            return status;
        }
        void setStatus(int st) override{
            status = st;
        }
};

class RemoteControl {
    protected: 
        Device* device;
    public: 
        RemoteControl(Device* d) : device{d} {}
        virtual ~RemoteControl() {}
        virtual void togglePower() = 0;
        virtual void volumeUp() = 0;
        virtual void volumeDown() = 0;
        
};

class AdvancedRemoteControl : RemoteControl {

    public:

    AdvancedRemoteControl(Device * ctrl) : RemoteControl(ctrl) {}

    void togglePower() override {
        if(device->getStatus()) {
            std::cout << "The device is now turned off" << std::endl;
            device->setStatus(0);
        }else {
            std::cout << "The device is now turned on" << std::endl;
            device->setStatus(1);
        }
    }
    void volumeUp() override {
        int vol = device->getVolume() + 1;
        device->setVolume(vol);
        std::cout << device->getVolume() << std::endl;
    }
    void volumeDown() override {
        int vol = device->getVolume() - 1;
        device->setVolume(vol);
        std::cout << device->getVolume() << std::endl;
    }
    void mute() {
        device->setVolume(0);
        std::cout << "Volume is now " << device->getVolume() << "muted"<< std::endl;
    }

};

int main() {
    TV tel;
    Radio radio;
    tel.setVolume(12);
    radio.setVolume(10);
    AdvancedRemoteControl TVcontrol(&tel);
    AdvancedRemoteControl RadioControl(&radio);
    TVcontrol.togglePower();
    TVcontrol.volumeDown();
    TVcontrol.volumeDown();
    TVcontrol.mute();
    TVcontrol.togglePower();
    RadioControl.togglePower();
    RadioControl.volumeUp();
    RadioControl.volumeUp();
    RadioControl.mute();
    RadioControl.togglePower();
    
    

}
