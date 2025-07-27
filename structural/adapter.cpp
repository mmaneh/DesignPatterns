#include <iostream>
#include <vector>

class TempretureSensor {
    public: 
       virtual void getTempretureCelsius() = 0;
       virtual ~TempretureSensor() {}
};
class OldFahrenheitSencor {
    public:
        OldFahrenheitSencor(float tmp) :_tempreture{tmp} {}

        float getTempreture() {
            return _tempreture;
        }
       
    private:
        float _tempreture;
};
class FahrenheitTOCelsiusAdapter : public TempretureSensor{
    private:
        OldFahrenheitSencor* _ptr;

    public:
        FahrenheitTOCelsiusAdapter(OldFahrenheitSencor* ptr) : _ptr{ptr} {}
        void getTempretureCelsius() override{
            float cels = (_ptr->getTempreture() - 32) *5/9;
            std::cout << "The adapted tempreture is " << cels << std::endl;
        }
};

class ModernCelciusSensor : public TempretureSensor {
    public:
        ModernCelciusSensor(float tmp) : _tempreture{tmp} {} 
        void getTempretureCelsius() override {
            std::cout << "The tempreture is: " << _tempreture << std::endl;
        }
    private:
        float _tempreture;
};

int main() {
    std::vector<TempretureSensor*> vec;
    OldFahrenheitSencor* fahr = new OldFahrenheitSencor(75.5);
    ModernCelciusSensor* mod = new ModernCelciusSensor(22);
    FahrenheitTOCelsiusAdapter * adapter = new FahrenheitTOCelsiusAdapter(fahr);
    vec.push_back(adapter);
    vec.push_back(mod);
    for(auto& pt : vec) {
        pt->getTempretureCelsius();
    }
    delete adapter;
    delete fahr;
    delete mod;
}
