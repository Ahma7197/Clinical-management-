#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

int ID[100];
string NAME[100];
int AGE[100];
int QUEUE_NUMBER[100];
int APPOINTMENT_DATE[100];
int APPOINTMENT_TIME[100];

int mycount = 0;

// Save Data
void SaveData() {
    ofstream file("Clinic.txt");

    for (int i = 0; i < mycount; i++) {
        file << ID[i] << endl;
        file << NAME[i] << endl;
        file << AGE[i] << endl;
        file << APPOINTMENT_DATE[i] << endl;
        file << APPOINTMENT_TIME[i] << endl;
        file << QUEUE_NUMBER[i] << endl;
    }

    file.close();
}

// Load Data
void LoadData() {
    ifstream file("Clinic.txt");

    if (!file) {
        return;
            }
    mycount = 0;
    while (mycount < 100 && file >> ID[mycount]) {

        file.ignore();

        getline(file, NAME[mycount]);
        file >> AGE[mycount];
        file >> APPOINTMENT_DATE[mycount];
        file >> APPOINTMENT_TIME[mycount];
        file >> QUEUE_NUMBER[mycount];
        
        mycount++;
    }
    file.close();
}

   int main() {
     int choice;
    LoadData();
  
     do {

        cout << "\n========================================\n";
        cout << "     CLINIC MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Register New Patient\n";
        cout << "2. View Appointments\n";
        cout << "3. Search for Patient\n";
        cout << "4. Cancel Patient Registration\n";
        cout << "5. Update Patient Information\n";
        cout << "6. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        // إضافة مريض وبياناته
        case 1: {
            int newID;
            int appointmentsToday = 0;
            int year, month, day;
            bool duplicate;

            if (mycount >= 100) {
                cout << "Maximum capacity reached!\n";
                break;
            }
            do {
            duplicate = false;
            cout << "Enter Patient ID: ";
            cin >> newID;
              for (int i = 0; i < mycount; i++) {
                 if (ID[i] == newID) {
                   duplicate = true;
           cout << "This ID already exists!\n";
            break;
                    }
                }
            } while (duplicate);
            ID[mycount] = newID;
            cout << "Enter Patient Name: ";
            getline(cin >> ws, NAME[mycount]);
            cout << "Enter Patient Age: ";
            cin >> AGE[mycount];
            cout << "Enter Day: ";
            cin >> day;
            cout << "Enter Month: ";
            cin >> month;
            cout << "Enter Year: ";
            cin >> year;
            APPOINTMENT_DATE[mycount] =
                year * 10000 + month * 100 + day;
            for (int i = 0; i < mycount; i++) {
                if (APPOINTMENT_DATE[i] ==
                    APPOINTMENT_DATE[mycount]) {
                    appointmentsToday++;
                }
            }
            APPOINTMENT_TIME[mycount] =
                9 * 60 + appointmentsToday * 30;
            QUEUE_NUMBER[mycount] = appointmentsToday + 1;
            mycount++;

            cout << "Patient registered successfully!\n";
            cout << "Your Queue Number is: "
                 << QUEUE_NUMBER[mycount - 1] << endl;
            SaveData();
            
            break;
        }

        // عرض المواعيد
        case 2: {
          if (mycount == 0) {
          cout << "No patients are registered!\n";
            }
          else {
            for (int i = 0; i < mycount; i++) {
            cout << "Patient ID: " << ID[i] << endl;
            cout << "Patient Name: " << NAME[i] << endl;
            cout << "Patient Age: " << AGE[i] << endl;
            cout << "Appointment Time: " << setw(2) << setfill('0') << APPOINTMENT_TIME[i] / 60 << ":" << setw(2) << setfill('0') << APPOINTMENT_TIME[i] % 60 << endl;
            cout << "Appointment Date: "<< APPOINTMENT_DATE[i] % 100 << "/"<< APPOINTMENT_DATE[i] / 100 % 100 << "/"<< APPOINTMENT_DATE[i] / 10000 << endl;
            cout << "Queue Number: " << QUEUE_NUMBER[i] << endl;
            cout << "----------------------\n";
                }
            }
            break;
        }
        // بحث عن مريض
        case 3: {
           int SEARCH_ID;
           bool found = false;
            cout << "Enter Patient ID: ";
            cin >> SEARCH_ID;
            for (int i = 0; i < mycount; i++) {
                if (SEARCH_ID == ID[i]) {
                  found = true;
           cout << "Patient Name: " << NAME[i] << endl;
           cout << "Patient Age: " << AGE[i] << endl;
           cout << "Appointment Time: " << setw(2)<< setfill('0')<< APPOINTMENT_TIME[i] / 60 << ":"<< setw(2) << setfill('0')<< APPOINTMENT_TIME[i] % 60 << endl;
           cout << "Appointment Date: "<< APPOINTMENT_DATE[i] % 100 << "/" << APPOINTMENT_DATE[i] / 100 % 100 << "/"<< APPOINTMENT_DATE[i] / 10000 << endl;
           cout << "Queue Number: "<< QUEUE_NUMBER[i] << endl;
                break;
                }
            }
            if (found == false) {
                cout << "Patient ID not found!\n";
            }
            break;
        }

        // حذف مريض
        case 4: {
            int CANCEL_ID;
            bool found = false;

            cout << "Enter Patient ID to cancel: ";
            cin >> CANCEL_ID;
            for (int i = 0; i < mycount; i++) {
                if (CANCEL_ID == ID[i]) {
                    found = true;
            for (int j = i; j < mycount - 1; j++) {
                ID[j] = ID[j + 1];
                NAME[j] = NAME[j + 1];
                AGE[j] = AGE[j + 1];
                APPOINTMENT_DATE[j] = APPOINTMENT_DATE[j + 1];
                APPOINTMENT_TIME[j] = APPOINTMENT_TIME[j + 1];
                QUEUE_NUMBER[j] = QUEUE_NUMBER[j + 1];
                    }
                    mycount--;

                    // إعادة حساب المواعيد
            for (int j = 0; j < mycount; j++) {
                 int appointmentsToday = 0;
            for (int k = 0; k < j; k++) {
                if (APPOINTMENT_DATE[k] == APPOINTMENT_DATE[j]) {
                                appointmentsToday++;
                            }
                        }
            APPOINTMENT_TIME[j] = 9 * 60 + appointmentsToday * 30;
            QUEUE_NUMBER[j] = appointmentsToday + 1;
                    }
            cout << "Patient cancelled successfully!\n";
                    SaveData();
                 break;
                }
            }
            if (found == false) {
                cout << "Patient ID not found!\n";
            }
            break;
        }

        // تحديث معلومات مريض
        case 5: {
            int UPDATE_ID;
            bool found = false;
        cout << "Enter Patient ID: ";
        cin >> UPDATE_ID;
            for (int i = 0; i < mycount; i++) {
                if (UPDATE_ID == ID[i]) {
                    found = true;
        cout << "Enter New Name: ";
        getline(cin >> ws, NAME[i]);
        cout << "Enter New Age: ";
        cin >> AGE[i];
        cout << "Patient Information Updated Successfully!\n";
               SaveData();

          break;
                }
            }
            if (found == false) {
        cout << "Patient ID not found!\n";
            }
            break;
        }
        // الخروج
        case 6:
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}