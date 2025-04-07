#include "../src/WorkerDb.hpp"
#include <iostream>

using namespace std;

//4.3 helper functions
void print_db(WorkerDb& db) {
    cout << "===== WORKER DATABASE =====" << endl;
    cout << "Total workers: " << db.size() << endl;
    
    for (auto it = db.begin(); it != db.end(); ++it) {
        cout << "Surname: " << it.key() 
             << ", Name: " << it->name
             << ", Age: " << it->age
             << ", Salary: $" << it->salary
             << endl;
    }
    cout << "==========================" << endl;
}

double get_avg_age(WorkerDb& db) {
    if (db.size() == 0) {
        return 0.0;
    }
    
    int total_age = 0;
    int count = 0;
    
    for (auto it = db.begin(); it != db.end(); ++it) {
        total_age += it->age;
        count++;
    }
    
    return static_cast<double>(total_age) / count;
}

int main() {
    WorkerDb db;
    
    db["Ivanov"] = WorkerData("Ivan", 34, 50000);
    db["Petrov"] = WorkerData("Petr", 43, 60000);
    
    //access
    cout << "Ivanov's name = " << db["Ivanov"].name << "\n";
    cout << "Petrov's age = " << db["Petrov"].age << "\n";
    
    db["Ivanov"].salary = 55000;
    cout << "Ivanov's new salary = $" << db["Ivanov"].salary << "\n";
    
    //create a new worker implicitly
    db["Sidorov"].name = "Sidor";
    db["Sidorov"].age = 28;
    db["Sidorov"].salary = 45000;
    
    //add more workers
    db["Smith"] = WorkerData("John", 39, 65000);
    db["Johnson"] = WorkerData("Mike", 52, 80000);
    db["Brown"] = WorkerData("Anna", 29, 48000);
    
    cout << "\nNumber of workers: " << db.size() << "\n";
    
    //test the iterator
    cout << "\n=== Using Iterator ===\n";
    for (auto it = db.begin(); it != db.end(); ++it) {
        cout << "Surname: " << it.key() 
             << ", Name: " << it->name
             << ", Age: " << it->age
             << ", Salary: $" << it->salary
             << endl;
    }
    
    //test copy construction and assignment
    cout << "\n=== Testing Copy Construction ===\n";
    WorkerDb db_copy(db);
    cout << "Copy contains " << db_copy.size() << " workers\n";
    
    cout << "\n=== Testing Assignment ===\n";
    WorkerDb db_assign;
    db_assign = db;
    cout << "Assigned copy contains " << db_assign.size() << " workers\n";
    
    //task 4.3 helper functions
    cout << "\n=== Using Helper Functions ===\n";
    print_db(db);
    
    double avg_age = get_avg_age(db);
    cout << "Average age of workers: " << avg_age << " years\n";
    
    return 0;
}