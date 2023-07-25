#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstddef>
#include <fstream>
#include <cstdlib>

using namespace std;

double calculateTotalAmount(double subtotal) {
    double discount = subtotal * 0.05;
    double vat = subtotal * 0.16;
    return subtotal - discount + vat;
}

void login();
void registration();
void forgot();
void adminMenu();

void saveOrderDetails(const string& username, const string& phoneNumber, const string& location, const string& orderDetails, double totalAmount) {
    ofstream outputFile("Used.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << "Username: " << username << endl;
        outputFile << "Phone number: " << phoneNumber << endl;
        outputFile << "Location: " << location << endl;
        outputFile << "Order Details: " << endl;
        outputFile << orderDetails << endl;
        outputFile << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        outputFile << "------------------------" << endl;
        outputFile.close();
    } else {
        cout << "Failed to save order details." << endl;
    }
}

int main() {
    login();

    cout << "\n\n\n\n\t\t\tWelcome to Fast Lane Hotel!" << endl << endl;

    string itemNames[] = {"Tea", "Rice", "Pizza", "Meat", "Sandwich", "Pilau", "Tea", "Soda", "Afya500ml", "Mineral water"};
    double itemPrices[] = {10.0, 5.0, 8.0, 10.0, 5.1, 3.0, 6.0, 9.8, 2.9, 5.0};

    int quantity;
    double subtotal = 0.0;
    string orderDetails;

    cout << "\nMenu:\n";
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ". " << itemNames[i] << " - $" << itemPrices[i] << endl;
    }

    cout << "\nEnter the item number and quantity (0 to exit):\n";

    int itemNumber;
    while (true) {
        cout << "Item number: ";
        cin >> itemNumber;

        if (itemNumber == 0) {
            break;
        }

        if (itemNumber < 1 || itemNumber > 10) {
            cout << "Invalid item number. Try again.\n";
            continue;
        }

        cout << "Quantity: ";
        cin >> quantity;

        if (quantity < 1) {
            cout << "Invalid quantity. Try again.\n";
            continue;
        }

        double itemPrice = itemPrices[itemNumber - 1];
        double itemTotal = itemPrice * quantity;
        subtotal += itemTotal;

        orderDetails += itemNames[itemNumber - 1] + " - Quantity: " + to_string(quantity) + ", Total: $" + to_string(itemTotal) + "\n";
    }

    double totalAmount = calculateTotalAmount(subtotal);

    time_t currentTime = time(NULL);
    string timeServiced = ctime(&currentTime);

    string paymentMode;
    cout << "Enter the mode of payment (Cash, M-Pesa, Credit Card): ";
    cin.ignore();
    getline(cin, paymentMode);

    string username, phoneNumber, location;

    if (paymentMode != "Cash") {
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your phone number: ";
        cin >> phoneNumber;
        cout << "Enter your location: ";
        cin.ignore();
        getline(cin, location);
    }

    // Print receipt
    cout << "\n\n---------- Receipt ----------\n";
    cout << "Title: Fast Lane Hotel!" << endl;
    cout << "Time serviced: " << timeServiced;
    cout << "------------------------------\n";
    cout << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    cout << "Discount (5%): $" << fixed << setprecision(2) << subtotal * 0.05 << endl;
    cout << "VAT (16%): $" << fixed << setprecision(2) << subtotal * 0.16 << endl;
    cout << "Total amount: $" << fixed << setprecision(2) << totalAmount << endl;
    cout << "Payment mode: " << paymentMode << endl;
    cout << "------------------------------\n";
    cout << "Thank you for visiting us" << endl;

    if (paymentMode != "Cash") {
        saveOrderDetails(username, phoneNumber, location, orderDetails, totalAmount);
    }

    return 0;
}

void login() {
    int c;
    cout << "\t\t\t..................................................\n\n\n";
    cout << "\t\t\t          WELCOME TO THE LOGIN PAGE               \n\n\n";
    cout << "\t\t\t.....................MENU..........................\n\n\n";
    cout << "                                                            \n\n";
    cout << "\t| Press 1 to LOGIN                           |\n";
    cout << "\t| Press 2 to REGISTER                        |\n";
    cout << "\t| Press 3 if you forgot your PASSWORD        |\n";
    cout << "\t| Press 4 to EXIT                            |\n";
    cout << "\n\t\t\t Press enter your choice    : ";
    cin >> c;
    cout << endl;

    switch (c) {
        case 1:
            // Perform login logic
            {
                string username, password;
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;

                if (username == "ADMIN" && (password == "Admin@234" || password == "Gilly123")) {
                    cout << "\nLogin successful! (Admin)\n";
                    adminMenu();
                } else {
                    ifstream input("records.txt");
                    string id, pass;
                    bool success = false;

                    while (input >> id >> pass) {
                        if (id == username && pass == password) {
                            success = true;
                            break;
                        }
                    }

                    input.close();

                    if (success) {
                        cout << "\nLogin successful!\n";
                    } else {
                        cout << "\nLogin failed. Invalid username or password.\n";
                        login();
                    }
                }
            }
            break;
        case 2:
            registration();
            break;
        case 3:
            forgot();
            break;
        case 4:
            cout << "\t\t\t THANK YOU!";
            exit(0);
        default:
            system("cls");
            cout << "\t\t\t please select from the options given above \n" << endl;
            login();
    }
}

void registration() {
    string ruserId, rpassword, phoneNumber, location;
    system("cls");
    cout << "\t\t\t Enter the username: ";
    cin >> ruserId;
    cout << "\t\t\t Enter the password: ";
    cin >> rpassword;
   
   
    ofstream f1("records.txt", ios::app);
    if (f1.is_open()) {
        f1 << ruserId << ' ' << rpassword << ' ' << phoneNumber << ' ' << location << endl;
        cout << "\n\t\t Registration is successful! \n";
        f1.close();
    }
}

void forgot() {
    int option;
    system("cls");
    cout << "\t\t\t You forgot the password? No worries \n";
    cout << "Press 1 to search your id by username" << endl;
    cout << "Press 2 to go back to the main menu" << endl;
    cout << "\t\t\t Enter your choice: ";
    cin >> option;
    switch (option) {
        case 1:
            {
                int count = 0;
                string suserId, sId, spass;
                cout << "\n\t\tEnter the username you remember: ";
                cin >> suserId;

                ifstream f2("records.txt");
                while (f2 >> sId >> spass) {
                    if (sId == suserId) {
                        count = 1;
                    }
                }
                f2.close();
                if (count == 1) {
                    cout << "\n\n Your account is found \n";
                    cout << "\n\n Your password is: " << spass;
                    login();
                } else {
                    cout << "\n\t Sorry! your account is not found! \n";
                    login();
                }
                break;
            }
        default:
            login();
    }
}

void adminMenu() {
    int choice;
    cout << "\n\n\n\n\t\t\tAdmin Menu\n";
    cout << "\t\t\t-----------\n\n";
    cout << "\t1. Add Product\n";
    cout << "\t2. Remove Product\n";
    cout << "\t3. Block Account\n";
    cout << "\t4. Exit\n";
    cout << "\n\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            {
                string itemName;
                double itemPrice;

                cout << "\n\tEnter the product name: ";
                cin.ignore();
                getline(cin, itemName);
                cout << "\n\tEnter the product price: $";
                cin >> itemPrice;

                ofstream f1("menu.txt", ios::app);
                if (f1.is_open()) {
                    f1 << itemName << ' ' << fixed << setprecision(2) << itemPrice << endl;
                    cout << "\n\tProduct added successfully!\n";
                    login();
                }
            }
            break;
        case 2:
            {
                string itemName;
                cout << "\n\tEnter the product name to remove: ";
                cin.ignore();
                getline(cin, itemName);

                ifstream f2("menu.txt");
                ofstream f3("temp.txt");

                string name;
                double price;
                bool found = false;

                while (f2 >> name >> price) {
                    if (name != itemName) {
                        f3 << name << ' ' << fixed << setprecision(2) << price << endl;
                    } else {
                        found = true;
                    }
                    
                }

                f2.close();
                f3.close();

                if (found) {
                    remove("menu.txt");
                    rename("temp.txt", "menu.txt");
                    cout << "\n\tProduct removed successfully!\n";
                } else {
                    remove("temp.txt");
                    cout << "\n\tProduct not found!\n";
                    login();
                }
            }
            break;
        case 3:
            {
                string username;
                cout << "\n\tEnter the username to block: ";
                cin.ignore();
                getline(cin, username);

                ifstream f4("records.txt");
                ofstream f5("temp.txt");

                string id, pass, phoneNumber, location;
                bool found = false;

                while (f4 >> id >> pass >> phoneNumber >> location) {
                    if (id != username) {
                        f5 << id << ' ' << pass << ' ' << phoneNumber << ' ' << location << endl;
                    } else {
                        found = true;
                    }
                }

                f4.close();
                f5.close();

                if (found) {
                    remove("records.txt");
                    rename("temp.txt", "records.txt");
                    cout << "\n\tAccount blocked successfully!\n";
                } else {
                    remove("temp.txt");
                    cout << "\n\tAccount not found!\n";
                    login();
                }
            }
            break;
        case 4:
            cout << "\n\tExiting admin menu...\n";
            break;
        default:
            cout << "\n\tInvalid choice!\n";
    }
}
