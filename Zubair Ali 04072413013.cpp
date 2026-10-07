#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <iomanip> 
using namespace std;
struct Patient {//patient detail
    string name;
    int age;
    string disease;
};
void user_Help() {
    cout << ".................................\n";
    cout << "Welcome to Hospital Queue Management System (QMS)\n";
    cout << "..................................\n\n";
    cout << "\nHelp for usage of (QMS)  :\n";
    cout << ".......................";
     cout << "\nProgram has given the instruction all time for input so read carefully \n";
    cout << " Firstly proceed with number of queues you want  ./qms <number_of_queues>\n\n";
    cout << "For instance:\n";
    cout << "  ./qms 3\\4\\5\n";
    cout << "  According to requirement Creates 3 queues (like, Checkup, Lab Test, Emergency etc)\n\n";
    cout << " System holds the menu which is :\n";
    cout << "  1. Add patient to any queue\n";
    cout << "  2. Remove (pop) patient from any queue\n";
    cout << "  3. Display all queues\n";
    cout << "  4. Exit the system will end the program\n\n";
    cout << "To display this help, at run time write:\n";
    cout << "  ./qms --help\n";
    cout << "  Hopefully this is helpful";
    cout << ".............................\n";
}


void display_data(queue<Patient>* queues, int total_Queues) {
    cout << "\n........ Welcome to queue display function  .......\n";
    
    for (int i = 1; i < total_Queues; ++i)
	 {
        cout << "\nQueue no " << i << " \n  ";
        if (queues[i].empty()) 
		{
            cout << "\nQueue is Empty\n";
        } else {
            queue<Patient> temporary = queues[i]; 
            while (!temporary.empty()) 
			{
                Patient patient = temporary.front();
                cout << "\nPatient name : " << patient.name << "\n";
                cout << " Patient  Age : " << patient.age << "\n";
                cout << "patient disease :  " << patient.disease << "\n";
                temporary.pop();
            }
        }
        cout << "\n";
    }
    cout << "..............End of function .............\n";
}

int main(int argc, char* argv[]) {
    if (argc == 2 && string(argv[1]) == "--help") {
        user_Help();
        return 0;
    }
    if (argc < 2) 
	{
        cout << "Please enter the number of queues to proceed in QMS \n";
        cout << "OR you can Run with --help for usage information.\n";
        return 1;
    }

    int total_Queues = atoi(argv[1]);
    if (total_Queues <= 0) 
	{
        cout << "\nNumber should be positive means greater than 0 thank you\n";
        cout<<"\nnow You can Enter seprately number of queues \n";
        cout<<"\nEnter total number of queues";
        cin>>total_Queues;
    }
    queue<Patient>* queues = new queue<Patient>[total_Queues];//TODO DEALOCATE

    int choice;
    do {
    	cout << "\n\n\n";

        cout << setw(60) << "------------------------------\n";
        cout << setw(70) << "Hospital Queue Management System\n";
        cout << setw(60) << "--------------------------------\n";

        cout << setw(55) << "1. Add Patient (Push)\n";
        cout << setw(55) << "2. Pop (Remove) Patient\n";
        cout << setw(55) << "3. Display Queues\n";
        cout << setw(55) << "4. Exit / Break\n";

        cout << setw(55) << "Enter your choice: ";
        cin >> choice;

        if (choice <= 0 || choice > 4)
		 {
            cout << "\nYou have Entered the wrong number \n";
            cout << "\n Choose number in between 1 to 4 \n";
            cout << "\nEnter again : ";
            cin >> choice;
        }

        switch (choice) {
            case 1: {
                int q_serial;
                cout <<setw(55)<< "\nEnter queue number (1-" << total_Queues << ") : ";
                cin >> q_serial;
                if (q_serial < 1 || q_serial > total_Queues) {
                    cout << "\nThis number does not exist number ERROR\n";
                    cout << " \nAgain Enter queue number (1-" << total_Queues << ") : ";
                    cin >> q_serial;
                }

                Patient p;
                cout << "\nEnter patient name : ";
                cin.ignore();
                getline(cin, p.name);
                cout << "\nEnter age : ";
                cin >> p.age;
                cout << "\nEnter disease : ";
                cin.ignore();
                getline(cin, p.disease);

                queues[q_serial - 1].push(p);
                cout << "\n Patient detail has been added to Queue no " << q_serial << " successfully!\n";
                break;
            }

            case 2: {
                int q_serial;
                cout << "\nEnter queue number (1 to " << total_Queues << "): ";
                cin >> q_serial;
                if (q_serial < 1 || q_serial > total_Queues)
				 {
                    cout << "\nThis number does not exist number ERROR\n";
                     cout << "\n Again Enter queue number (1 to " << total_Queues << "): ";
                     cin >> q_serial;
                }

                if (queues[q_serial - 1].empty()) 
				{
                    cout << "\n Queue no  " << q_serial << " is already empty ERROR\n";
                } else {
                    Patient p = queues[q_serial - 1].front();
                    queues[q_serial - 1].pop();
                    cout << "\npatient has been removed : " << p.name << "\n";
                }
                break;
            }

            case 3:
                display_data(queues, total_Queues);
                break;

            case 4:
                cout << "\nExiting the system... Allah hafiz\n";
                break;

            default:
                cout << "\nInvalid choice\n";
        }

    } while (choice != 4);

    delete[] queues; 
    return 0;
}
