#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

enum class POL { MALE, FEMALE };
enum class PPCLASS { NONE, UPPER, MIDDLE, LOWER };
enum class VST { NONE, CHERBOURG, QUEENSTOWN, SOUTHAMPTON };

struct Description {
    int id;
    bool survival;
    int ppclass;
    string name;
    POL pol;
    int age;
    int sibsp;
    int parch;
    string ticket;
    float fare;
    string cabin;
    VST vst;
};


int main()
{
    setlocale(LC_ALL, "rus");

    string file_path = "train.csv";
    string result_path = "result.txt";
    bool first_line = true;

    vector<Description> arr;

    ifstream data(file_path);
    ofstream answ(result_path);

    while (data.good()) {
        Description kim;
        string kimstr;

        if (first_line) {
            for (int i = 0; i < 11; i++)
                getline(data, kimstr, ',');
            getline(data, kimstr, '\r');
            first_line = false;
        }

        //// ID
        getline(data, kimstr, ',');
        kim.id = stoi(kimstr);
        //// Survival
        getline(data, kimstr, ',');
        kim.survival = stoi(kimstr);
        //// Ppclass
        getline(data, kimstr, ',');
        kim.ppclass = stoi(kimstr);

        //// Name
        {
            string kim1;
            getline(data, kimstr, ',');
            getline(data, kim1, ',');
            kim.name = kimstr + ',' + kim1;
        }

        //// Pol
        getline(data, kimstr, ',');
        if (kimstr == "male")
            kim.pol = POL::MALE;
        else
            kim.pol = POL::FEMALE;
        //// AGE
        getline(data, kimstr, ',');
        if (kimstr != "") kim.age = stoi(kimstr);
        else kim.age = -1;
        //// Sibsp
        getline(data, kimstr, ',');
        kim.sibsp = stoi(kimstr);
        //// Parch
        getline(data, kimstr, ',');
        kim.parch = stoi(kimstr);
        //// Ticket
        getline(data, kimstr, ',');
        kim.ticket = kimstr;
        //// Fare
        getline(data, kimstr, ',');
        kim.fare = stof(kimstr);
        //// Cabin
        getline(data, kimstr, ',');
        kim.cabin = kimstr;
        //// VST
        getline(data, kimstr, '\r');
        if (kimstr == "C")
            kim.vst = VST::CHERBOURG;
        else if (kimstr == "Q")
            kim.vst = VST::QUEENSTOWN;
        else if (kimstr == "S")
            kim.vst = VST::SOUTHAMPTON;
        arr.push_back(kim);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        int schetchik = 0;
        {
            float ag_p = 0;
            float ag_f = 0;
            float ag_m = 0;

            for (int i = 0; i < arr.size(); i++) {
                if (arr[i].survival) {
                    schetchik++; ag_p += arr[i].age;
                }
            }
            ag_p /= schetchik;
            cout << "Выжившие: " << schetchik << endl;
            answ << "Выжившие: " << schetchik << endl;
            schetchik = 0;

            for (int kim = 1; kim < 4; kim++) {
                for (int i = 0; i < arr.size(); i++) {
                    if (arr[i].ppclass == kim && arr[i].survival) schetchik++;
                }
                cout << "Выживший" << kim << " класса: " << schetchik << endl;
                answ << "Выживший" << kim << " класса: " << schetchik << endl;
                schetchik = 0;
            }

            for (int i = 0; i < arr.size(); i++) {
                if (arr[i].survival && arr[i].pol == POL::FEMALE) {
                    schetchik++; ag_f += arr[i].age;
                }
            }
            ag_f /= schetchik;
            cout << "Выжившие ж.р.: " << schetchik << endl;
            answ << "Выжившие ж.р.: " << schetchik << endl;
            schetchik = 0;

            for (int i = 0; i < arr.size(); i++) {
                if (arr[i].survival && arr[i].pol == POL::MALE) {
                    schetchik++; ag_m += arr[i].age;
                }
            }
            ag_m /= schetchik;
            cout << "Выжившие м.р.: " << schetchik << endl;
            answ << "Выжившие м.р.: " << schetchik << endl;
            schetchik = 0;

            cout << "Средний возраст всех пассажиров: " << ag_p << endl;
            answ << "Средний возраст всех пассажиров: " << ag_p << endl;
            cout << "Средний возраст всех пассажиров женского пола: " << ag_f << endl;
            answ << "Средний возраст всех пассажиров женского пола: " << ag_f << endl;
            cout << "Средний возраст всех пассажиров мужского пола: " << ag_m << endl;
            answ << "Средний возраст всех пассажиров мужского пола: " << ag_m << endl;
        }

        {
            int Cherbourg = 0;
            int Queenstown = 0;
            int Southampton = 0;

            for (int i = 0; i < arr.size(); i++) {
                switch (arr[i].vst) {
                case VST::CHERBOURG:
                    Cherbourg++;
                    break;
                case VST::QUEENSTOWN:
                    Queenstown++;
                    break;
                case VST::SOUTHAMPTON:
                    Southampton++;
                    break;
                }
            }

            if (Cherbourg > Queenstown) {
                if (Cherbourg > Southampton) {
                    cout << "Штат Cherbourg" << endl;
                    answ << "Штат Cherbourg" << endl;
                }
                else {
                    cout << "Штат Southampton" << endl;
                    answ << "Штат Southampton" << endl;
                }
            }
            else if (Queenstown > Southampton) {
                cout << "Штат Queenstown" << endl;
                answ << "Штат Queenstown" << endl;
            }
            else {
                cout << "Штат Southampton" << endl;
                answ << "Штат Southampton" << endl;
            }
        }

        cout << "Несовершеннолетние: ";
        answ << "Несовершеннолетние: ";
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i].age > 0 && arr[i].age < 18) {
                cout << arr[i].id << " ";
                answ << arr[i].id << " ";
            }
        }
        cout << endl;
    }
}