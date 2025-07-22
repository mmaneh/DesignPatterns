#include <iostream>
class DAtaProcessor {
    public:
        void execute() {
            readData();
            processData();
            saveData();
        }

        virtual void readData() = 0;
        virtual void processData() = 0;
        virtual void saveData() = 0;
        virtual ~DAtaProcessor() {}
};

class CSVProcessor : public DAtaProcessor {
    public:
    void readData() override {
        std::cout << "Reading data from CSV file" << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from CSV file" << std::endl;
    }
    void saveData() override {
        std::cout << "Saving data from CSV file" << std::endl;
    }
};

class JSONProcessor : public DAtaProcessor {
    public:
    void readData() override {
        std::cout << "Reading data from JSON file" << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from JSON file" << std::endl;
    }
    void saveData() override {
        std::cout << "Saving data from JSON file" << std::endl;
    }
};

int main() {
    CSVProcessor csv;
    JSONProcessor json;

    csv.execute();
    json.execute();
}
