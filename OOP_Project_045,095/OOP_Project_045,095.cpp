#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
using namespace std;


class Vehicle;


class Person
{
protected:
    string name;
public:
    virtual void ViewDetails() const = 0;
    void setName(const string& name)
    {
       this-> name = name;
    }
    string getName() const 
    {
        return name;
    }
    virtual ~Person() 
    {}
};


class Student : public Person 
{
private:
    string feeStatus;
    char attendance[30];
    int attendanceCount = 0;
    Vehicle* vehiclePtr = nullptr;

public:
    void setFeeStatus(const string& status)
    {
        feeStatus = status;
    }
    string getFeeStatus() const 
    {
        return feeStatus;
    }

    void markAttendance() 
    {
        if (attendanceCount < 30) 
        {
            attendance[attendanceCount++] = 'P';
            cout << "Attendance marked!\n";
        }
        else 
        {
            cout << "Max attendance (30) reached!\n";
        }
    }

    void assignVehicle(Vehicle* v);
    void showVehicleDetail() const;

    void ViewDetails() const override
    {
        cout << "\n--- Student Details ---\n";
        cout << "Name: " << name << "\nFee Status: " << feeStatus << "\nAttendance: ";
        for (int i = 0; i < attendanceCount; i++)
        {
            cout << attendance[i] << " ";
        }
        cout << "\nVehicle: " << (vehiclePtr ? "Assigned" : "None") << "\n";
        if (vehiclePtr) showVehicleDetail();
    }

    Vehicle* getVehicle() const 
    {
        return vehiclePtr; 
    }
};

class Vehicle
{
private:
    string model;
    string route;
    char stops[5][50];
    Student* students[20];
    int studentCount = 0;

public:
    void setModel(const string& model)
    {
       this-> model = model; 
    }
    string getModel() const 
    {
        return model; 
    }

    void setRoute(const string& route)
    {
       this-> route = route; 
    }
    string getRoute() const
    {
        return route; 
    }

    void addStop(int i, const char* stop)
    {
        if (i >= 0 && i < 5)
        {
            strncpy(stops[i], stop, 49);
        }
    }

    const char* getStop(int i) const
    {
        return (i >= 0 && i < 5) ? stops[i] : "";
    }

    void registerStudent(Student* s) 
    {
        if (studentCount < 20) students[studentCount++] = s;
    }

    void displayStudents() const
    {
        cout << "\n--- Students in " << model << " ---\n";
        for (int i = 0; i < studentCount; i++)
            cout << i + 1 << ". " << students[i]->getName() << "\n";
    }

    void detail() const 
    {
        cout << left << setw(15) << model << setw(20) << route;
        for (int i = 0; i < 5; i++) cout << i + 1 << "." << stops[i] << " ";
        cout << "\n";
    }

    friend class Student;
};

void Student::assignVehicle(Vehicle* v) 
{
    vehiclePtr = v;
    v->registerStudent(this);
}

void Student::showVehicleDetail() const 
{
    cout << "\n--- Vehicle Details ---\n";
    vehiclePtr->detail();
}

class Manage 
{
private:
    Student* students[100];
    Vehicle* vehicles[100];
    int studentCount = 0;
    int vehicleCount = 0;

    void clearInputBuffer() 
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

public:
    ~Manage() 
    {
        for (int i = 0; i < studentCount; i++)
        {
            delete students[i];
        }
        for (int i = 0; i < vehicleCount; i++)
        {
            delete vehicles[i];
        }
    }

    void registerVehicle() {

        if (vehicleCount >= 100) 
        {
            cout << "Max vehicles (100) reached!\n";
            return;
        }

        vehicles[vehicleCount] = new Vehicle();
        string input;

        cout << "Enter Model: ";
        getline(cin, input);
        vehicles[vehicleCount]->setModel(input);

        cout << "Enter Route: ";
        getline(cin, input);
        vehicles[vehicleCount]->setRoute(input);

        for (int i = 0; i < 5; i++)
        {

            char stop[50];
            cout << "Enter Stop " << i + 1 << ": ";
            cin.getline(stop, 50);
            vehicles[vehicleCount]->addStop(i, stop);
        }

        vehicleCount++;
        cout << "Vehicle registered!\n";
    }

    void displayVehicles() const {
        cout << "\n--- All Vehicles ---\n";

        cout << left << setw(15) << "Model" << setw(20) << "Route" << "Stops\n";
        for (int i = 0; i < vehicleCount; i++)
        {
            vehicles[i]->detail();
        }
    }

    void registerStudent()
    {

        if (studentCount >= 100)
        {
            cout << "Max students (100) reached!\n";
            return;
        }

        students[studentCount] = new Student();
        string name, feeStatus;

        cout << "Enter Name: ";
        getline(cin, name);
        students[studentCount]->setName(name);

        cout << "Enter Fee Status (Paid/Unpaid): ";
        getline(cin, feeStatus);

        while (feeStatus != "Paid" && feeStatus != "Unpaid")
        {
            cout << "Invalid! Enter 'Paid' or 'Unpaid': ";
            getline(cin, feeStatus);
        }
        students[studentCount]->setFeeStatus(feeStatus);

        if (feeStatus == "Paid") 
        {
            cout << "Enter Desired Stop: ";
            string stop;
            getline(cin, stop);

            vector<int> matchedVehicles;

            for (int i = 0; i < vehicleCount; i++) 
            {
                for (int j = 0; j < 5; j++) 
                {
                    if (stop == vehicles[i]->getStop(j))
                    {
                        matchedVehicles.push_back(i);
                        break;
                    }

                }

            }

            if (matchedVehicles.empty())
            {
                cout << "No vehicle passes through " << stop << "!\n";
                delete students[studentCount];
                return;
            }

            cout << "\nAvailable Vehicles:\n";
            for (size_t i = 0; i < matchedVehicles.size(); i++)
            {
                int idx = matchedVehicles[i];
                cout << i + 1 << ". " << vehicles[idx]->getModel()
                    << " (Route: " << vehicles[idx]->getRoute() << ")\n";
            }


            cout << "Select Vehicle (1-" << matchedVehicles.size() << "): ";
            int choice;
            cin >> choice;

            clearInputBuffer();

            if (choice >= 1 && choice <= matchedVehicles.size())
            {
                students[studentCount]->assignVehicle(vehicles[matchedVehicles[choice - 1]]);
                studentCount++;
                cout << "Student registered!\n";
            }

            else
            {
                cout << "Invalid choice!\n";
                delete students[studentCount];
            }
        }
        else
        {
            cout << "Fee unpaid. Registration failed.\n";
            delete students[studentCount];
        }
    }

    void viewStudentDetails() const 
    {

        string name;
        cout << "Enter Student Name: ";
        getline(cin, name);

        for (int i = 0; i < studentCount; i++)
        {
            if (students[i]->getName() == name) 
            {
                students[i]->ViewDetails();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void markAttendance()
    {
        string name;
        cout << "Enter Student Name: ";
        getline(cin, name);

        for (int i = 0; i < studentCount; i++)
        {
            if (students[i]->getName() == name)
            {
                students[i]->markAttendance();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void vehicleRoster() const {
        cout << "\n--- Vehicle Rosters ---\n";
        for (int i = 0; i < vehicleCount; i++)
        {
            vehicles[i]->displayStudents();
        }
    }
};

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
}

int main() {

    Manage manager;
    int choice;

    do 
    {
        system("cls");

        cout << "=== VEHICLE MANAGEMENT SYSTEM ===\n";
        cout << "1. Register Vehicle\n";
        cout << "2. Display Vehicles\n";
        cout << "3. Register Student\n";
        cout << "4. View Student Details\n";
        cout << "5. Mark Attendance\n";
        cout << "6. Show Vehicle Rosters\n";
        cout << "0. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: manager.registerVehicle();
            break;
        case 2: manager.displayVehicles();
            break;
        case 3: manager.registerStudent();
            break;
        case 4: manager.viewStudentDetails();
            break;
        case 5: manager.markAttendance();
            break;
        case 6: manager.vehicleRoster();
            break;
        case 0: cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

        if (choice != 0) waitForEnter();
    } while (choice != 0);

    return 0;
}