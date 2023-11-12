#include <iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<iomanip>
using namespace std;



class  MobileApp {
private:
    string Name;
    string languageOfDev;
    int CoastOfDeveloping;
    string message;
public:

    MobileApp() : Name("UsualApp"), languageOfDev("Simple languageOfDev"), CoastOfDeveloping(1400) {};
    MobileApp(string Name, string languageOfDev, int CoastOfDeveloping) {
        this->Name = Name;
        this->languageOfDev = languageOfDev;
        this->CoastOfDeveloping = CoastOfDeveloping;
    }
    MobileApp(const MobileApp& obj) {
        Name = obj.Name;
        languageOfDev = obj.languageOfDev;
        CoastOfDeveloping = obj.CoastOfDeveloping;
    }
    virtual ~MobileApp() {
        cout << "�������� ���������� ������ MobileApp" << endl;
    }

    string GetName() {
        return Name;
    }

    string GetlanguageOfDev() {
        return languageOfDev;
    }

    int GetCoastOfDeveloping() {
        return CoastOfDeveloping;
    }

    void SetName(string Name) {
        this->Name = Name;
    }

    void SetlanguageOfDev(string languageOfDev) {
        this->languageOfDev = languageOfDev;
    }

    void SetCoastOfDeveloping(int coast) {
        CoastOfDeveloping = coast;
    }

    void SetMessage(string message) {
        this->message = message;
    }

    string Getmessage() {
        return message;
    }


};

class AndroidApp : public MobileApp {
private:
    string AndroidVersion;
public:

    AndroidApp() :MobileApp(), AndroidVersion("1.3.5") {};
    AndroidApp(string Name, string languageOfDev, int CoastOfDeveloping, string AndroidVersion) :
        MobileApp(Name, languageOfDev, CoastOfDeveloping) {
        this->AndroidVersion = AndroidVersion;
    }

    virtual ~AndroidApp() {
        cout << "�������� ��������� ������ AndroidApp" << endl;
    }

    string GetAndroidVersion() {
        return AndroidVersion;
    }

    void setAndriodVerasion(string AndriodVersion) {
        this->AndroidVersion = AndriodVersion;
    }
};

class IOSApp : public MobileApp {
private:
    string IOSVersion;
    long int AppleStoreID;
public:

    IOSApp() :MobileApp(), IOSVersion("1.3.5"), AppleStoreID(123453395) {};
    IOSApp(string Name, string languageOfDev, int CoastOfDeveloping, string IOSVersion, long int AppleStoreID) :
        MobileApp(Name, languageOfDev, CoastOfDeveloping) {
        this->IOSVersion = IOSVersion;
        this->AppleStoreID = AppleStoreID;
    }

    virtual ~IOSApp() {
        cout << "�������� ��������� ������ IOSApp" << endl;
    }

    string GetIOSVersion() {
        return IOSVersion;
    }

    void setAndriodVerasion(string AndriodVersion) {
        this->IOSVersion = AndriodVersion;
    }

    long int GetAppleStoreID() {
        return AppleStoreID;
    }

    void SetAppleStoreID(long int AppleStoreID) {
        this->AppleStoreID = AppleStoreID;
    }
};

template <class T>
struct Status {
    T* ptr;
    int counter;
};

template <class T>
class SmartPointer {
    Status<T>* smartPtr;
public:
    SmartPointer(T* ptr) {
        if (!ptr)
            smartPtr = NULL;
        else {
            smartPtr = new Status<T>();
            smartPtr->ptr = ptr;
        }
        smartPtr->counter = 1;
    }

    SmartPointer(const SmartPointer& obj) :smartPtr(obj.smartPtr) {
        if (smartPtr) smartPtr->counter++;
    }
    ~SmartPointer() {
        if (smartPtr) {
            smartPtr->counter--;
            if (smartPtr->counter == 0) {
                delete smartPtr->ptr;
                delete smartPtr;
            }
        }
    }

    SmartPointer& operator=(const SmartPointer& obj) {

        if (this == &obj) return *this;

        if (smartPtr) {
            smartPtr->counter--;
            if (smartPtr->counter == 0) {
                delete smartPtr->ptr;
                delete smartPtr;
            }
        }
        smartPtr = obj.smartPtr;
        if (smartPtr) smartPtr->counter++;
        return *this;
    }
    T* operator->() const {
        if (smartPtr) return smartPtr->ptr;
        else return NULL;
    }
    void showCounter() {
        cout << "�������� �������� ��� ������� "
            << smartPtr << " �����: " << smartPtr->counter << endl;
    }
};

bool isNumberNumeric()
{

    if (cin.get() == '\n')
    {
        return true;

    }
    else
    {
        cin.clear();
        cin.ignore(256, '\n');
        return false;
    }
}

bool check_on_digit(string str) {
    return str.find_first_of("0123456789") != string::npos;
}
enum State { begin, end };


template <class T>
class Transaction {
private:
    T* currentState;
    T* prevState;
    vector<SmartPointer<AndroidApp>> vectorAndroid;
    vector<SmartPointer<IOSApp>> vectorIOSapp;
public:
    Transaction() : prevState(NULL), currentState(new T) {
        currentState->SetMessage("������ ������ ����������");
    }
    Transaction(const Transaction& obj) : currentState(new T(*(obj.currentState))), prevState(NULL) {}
    ~Transaction() {
        delete currentState;
        delete prevState;
    }

    Transaction& operator=(const Transaction& obj) {
        if (this != &obj) {
            delete currentState;
            currentState = new T(*(obj.currentState));
        }
        return *this;
    }

    T* operator->() {
        return currentState;
    }


    bool beginTransactions(int NumberOfOperation)
    {
        delete prevState;
        prevState = currentState;
        currentState = new T(*prevState);
        string name, language;
        int CoastOfdeveloping;
        cout << "������� �������� ���������� : ";
        cin >> name;
        cout << "������� ����(�) ���������� : ";
        cin >> language;
        if (check_on_digit(language)) {
            deleteTransactions();
            currentState->SetMessage("���������� �� ������ �������");
            return false;
        };
        cout << "������� ��������� ���������� : ";
        cin >> CoastOfdeveloping;
        if (!isNumberNumeric()) {
            deleteTransactions();
            currentState->SetMessage("���������� �� ������ �������");
            return false;
        };

        if (NumberOfOperation == 1) {
            string version;
            cout << "������� ������ Android : ";
            cin >> version;
            SmartPointer<AndroidApp> ptr = new AndroidApp(name, language, CoastOfdeveloping, version);
            vectorAndroid.push_back(ptr);
        }
        else if (NumberOfOperation == 2) {
            string version;
            long int ID;
            cout << "������� ������ IOS : ";
            cin >> version;
            cout << "������� ID IOS ���������� (�����) : ";
            cin >> ID;
            if (!isNumberNumeric()) {
                deleteTransactions();
                currentState->SetMessage("���������� �� ������ �������");
                return false;
            }
            SmartPointer<IOSApp> ptr = new IOSApp(name, language, CoastOfdeveloping, version, ID);
            vectorIOSapp.push_back(ptr);
        }
        currentState->SetMessage("����������  ������ �������");
        return true;
    }

    void commit() {
        delete prevState;
        prevState = NULL;
    }

    void deleteTransactions() {
        cout << "�� ����������� ����� ������, ���������� ��������" << endl;
        if (prevState != NULL) {
            delete currentState;
            currentState = prevState;
            prevState = NULL;
        }
    }

    void showState(State state) {
        cout << "��������� ������� ";
        if (!state) cout << "�� ������ ���������� " << endl;
        else cout << "����� ���������� ���������� " << endl;
        if (prevState) cout << "prevState = " << prevState->Getmessage() << endl;
        else cout << "prevState = NULL" << endl;
        cout << "currentState = " << currentState->Getmessage() << endl;
    }

    vector<SmartPointer<AndroidApp>>& getVectorAndroid() {
        return vectorAndroid;
    }


    vector<SmartPointer<IOSApp>>& getVectorIOSapp() {
        return vectorIOSapp;
    }

    void setVectorAndroid(const vector<SmartPointer<AndroidApp>>& androidApps) {
        vectorAndroid = androidApps;
    }

    void setVectorIOSapp(const vector<SmartPointer<IOSApp>>& iosApps) {
        vectorIOSapp = iosApps;
    }


};

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    Transaction<MobileApp> transaction;

    while (1) {


        cout << "1. ������ ����� Android ����������" << endl;
        cout << "2. ������� ����� IOS ����������" << endl;
        cout << "3. ������� ��� ���������� � ���� �������" << endl;
        cout << "4. ����� �� ���������" << endl;

        cin >> choice;
        isNumberNumeric();

        switch (choice) {
        case 1:
            transaction.showState(State::begin);
            if (!transaction.beginTransactions(1))   transaction.commit();
            transaction.showState(State::end);
            break;
        case 2:
            transaction.showState(State::begin);
            if (!transaction.beginTransactions(2))   transaction.commit();
            transaction.showState(State::end);
            break;
        case 3:

            if (transaction.getVectorAndroid().empty()) cout << "��� Android ����������" << endl;
            else {
                cout << "������ Android ����������:" << endl;
                cout << "____________________________________________________________________________" << endl;
                cout << "| �������� ���������� | ���� ���������� | ���� ���������� | ������ Android |" << endl;
                cout << "|_____________________|_________________|_________________|________________|" << endl;
                for (const auto& ptr : transaction.getVectorAndroid()) {
                    cout << "|   " << setw(15) << ptr->GetName() << "   |   " << setw(10) << ptr->GetlanguageOfDev() << "    |   " << setw(10) <<
                        ptr->GetCoastOfDeveloping() << "    |   " << setw(10) << ptr->GetAndroidVersion() << "   |" << endl;
                    cout << "|_____________________|_________________|_________________|________________|" << endl;

                }

            }
            if (transaction.getVectorIOSapp().empty()) cout << "��� IOS ����������" << endl;
            else {
                cout << "������ IOS ����������:" << endl;
                cout << "______________________________________________________________________________________________" << endl;
                cout << "| �������� ���������� | ���� ���������� | ���� ���������� |   ������ IOS   | ID � AppleStore |" << endl;
                cout << "|_____________________|_________________|_________________|________________|_________________|" << endl;
                for (const auto& ptr : transaction.getVectorIOSapp()) {
                    cout << "|   " << setw(15) << ptr->GetName() << "   |   " << setw(10) << ptr->GetlanguageOfDev() << "    |   " << setw(10) <<
                        ptr->GetCoastOfDeveloping() << "    |   " << setw(10) << ptr->GetIOSVersion() << "   |   " << setw(10) << ptr->GetAppleStoreID() << "    |" << endl;
                    cout << "|_____________________|_________________|_________________|________________|_________________|" << endl;
                }
            }
            break;
        case 4: return 0;
        default:cout << "������� ���������� �������� ��������" << endl;
        }
    }
}

