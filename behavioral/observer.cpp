#include <vector>
#include <iostream>
#include <algorithm>
class Observer {
    public:
     virtual ~Observer(){};
     virtual void update(float tempreture) = 0;
   };
   
   class Subject {
    public:
     virtual ~Subject(){};
     virtual void addObserver(Observer *observer) = 0;
     virtual void removeObserver(Observer *observer) = 0;
     virtual void NotifyObservers() = 0;
   };

   class PhoneDisplay : public Observer {
    public:   
        void update(float tempreture) override{
            std::cout << "Updated tempreture on the phone is " << tempreture << std::endl;
        }
   };

   class LEDDisplay : public Observer {
    public:   
        void update(float tempreture) override{
           std::cout << "Updated tempreture on LED is " << tempreture << std::endl;
       }
  };

  class ConcreteWeatherStation : public Subject{
    private:
        std::vector<Observer*> observers;
        float _tempreture;
    public:
        void addObserver(Observer *observer) override{
            observers.push_back(observer);
        }
        void removeObserver(Observer *observer) override{
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }
        void NotifyObservers() override{
            for(auto* obs: observers) {
                obs->update(_tempreture);
            }
        }
        void changeTempreture(float tempreture) {
            _tempreture = tempreture;
            NotifyObservers();
        }
  };

  int main() {
    ConcreteWeatherStation station;
    PhoneDisplay phone;
    LEDDisplay led;
    station.addObserver(&phone);
    station.addObserver(&led);
    station.changeTempreture(40);
    station.removeObserver(&led);
    station.changeTempreture(35);

}
