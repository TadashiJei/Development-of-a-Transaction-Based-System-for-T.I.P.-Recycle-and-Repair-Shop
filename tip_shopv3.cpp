#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <fstream>
#include <ctime>
using namespace std;

const float STUDENT_DISCOUNT = 0.20; // 20% student discount

// Struct for handling items
struct Item {
    string name;
    string condition;
    int price;
    int stock;
};

// Struct for repair requests
struct RepairRequest {
    string itemName;
    string issue;
    string status;
    time_t submissionTime;
};

// Struct for transactions
struct Transaction {
    string itemName;
    int price;
    time_t timestamp;
};

// Arrays for different categories
vector<Item> electronics = {
    {"Smartphone", "Fully Functional", 2000, 5},
    {"Smartphone", "Minor Repairs Needed", 1500, 3},
    {"Smartphone", "Major Repairs Needed", 1000, 2},
    {"Laptop", "Fully Functional", 5000, 4},
    {"Laptop", "Minor Repairs Needed", 3000, 3},
    {"Laptop", "Major Repairs Needed", 2000, 1},
    {"Tablet", "Fully Functional", 3000, 6},
    {"Tablet", "Minor Repairs Needed", 2000, 5},
    {"Tablet", "Major Repairs Needed", 1500, 2}
};

vector<Item> furniture = {
    {"Wooden Chair", "New", 300, 10},
    {"Office Chair", "New", 600, 5},
    {"Gaming Chair", "New", 1500, 3},
    {"Wooden Table", "New", 500, 4},
    {"Office Desk", "New", 1000, 2},
    {"Study Table", "New", 700, 6},
    {"Small Shelf", "New", 400, 7},
    {"Medium Shelf", "New", 600, 3},
    {"Large Shelf", "New", 800, 1}
};

vector<Item> gadgets = {
    {"Wired Headphones", "New", 150, 10},
    {"Wireless Headphones", "New", 400, 7},
    {"Noise-Cancelling Headphones", "New", 1000, 4},
    {"Portable Speaker", "New", 500, 8},
    {"Bluetooth Speaker", "New", 1000, 3},
    {"Home Theater System", "New", 2000, 2},
    {"5000mAh Power Bank", "New", 300, 15},
    {"10000mAh Power Bank", "New", 600, 5},
    {"20000mAh Power Bank", "New", 1000, 3}
};

// Vector to store repair requests
vector<RepairRequest> repairRequests;

// Vector to store transactions
vector<Transaction> transactions;

// Function to clear the console screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to pause the console
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Function to verify student ID
bool verifyStudentID() {
    int studentID;
    cout << "Enter your 7-digit school ID (starting from 2000000): ";
    cin >> studentID;

    // Check if the ID is within the valid range
    if (studentID >= 2000000 && studentID <= 2999999) {
        cout << "Student ID verified successfully. You are eligible for the student discount.\n";
        return true;
    } else {
        cout << "Invalid ID! You are not eligible for the student discount.\n";
        return false;
    }
}

// Function to display items with inventory
void displayItems(const vector<Item>& items) {
    cout << setw(5) << "No." << setw(25) << "Name" << setw(25) << "Condition" 
         << setw(10) << "Price" << setw(10) << "Stock" << endl;
    cout << string(75, '-') << endl;
    
    for (size_t i = 0; i < items.size(); i++) {
        cout << setw(5) << i + 1 
             << setw(25) << items[i].name 
             << setw(25) << items[i].condition 
             << setw(10) << items[i].price 
             << setw(10) << items[i].stock << endl;
    }
}

// Function for admin to add stock
void adminAddStock(vector<Item>& items) {
    int choice, additionalStock;
    clearScreen();
    cout << "\n--- Admin: Add Stock ---" << endl;
    displayItems(items);
    cout << "Enter the item number to add stock (0 to cancel): ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(items.size())) {
        cout << "Enter the amount of stock to add: ";
        cin >> additionalStock;
        items[choice - 1].stock += additionalStock;
        cout << "Stock updated. New stock for " << items[choice - 1].name << ": " << items[choice - 1].stock << endl;
    } else if (choice != 0) {
        cout << "Invalid choice!" << endl;
    }
    pause();
}

// Function to handle a purchase
void buyItem(vector<Item>& items, bool isStudent) {
    int choice;
    clearScreen();
    cout << "Select an item to buy: " << endl;
    displayItems(items);
    cout << "Enter your choice (0 to cancel): ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(items.size()) && items[choice - 1].stock > 0) {
        int payment;
        float price = items[choice - 1].price;

        // Check if the user is a student and verify the student ID
        if (isStudent && verifyStudentID()) {
            price -= price * STUDENT_DISCOUNT;
            cout << "Discounted Price: P" << price << endl;
        } else if (isStudent) {
            // If student ID verification fails, charge full price
            cout << "No discount applied. Full Price: P" << price << endl;
        } else {
            cout << "Total Price: P" << price << endl;
        }

        // Handle payment
        cout << "Enter payment amount: P";
        cin >> payment;
        if (payment >= price) {
            int change = payment - price;
            cout << "Payment successful. Change: P" << change << endl;

            // Decrease stocks
            items[choice - 1].stock--;

            // Record transaction
            transactions.push_back({items[choice - 1].name, static_cast<int>(price), time(nullptr)});

            // Print receipt
            cout << "\n--- Receipt ---" << endl;
            cout << "Item: " << items[choice - 1].name << endl;
            cout << "Condition: " << items[choice - 1].condition << endl;
            cout << "Price: P" << price << endl;
            cout << "Payment: P" << payment << endl;
            cout << "Change: P" << change << endl;
            cout << "Thank you for your purchase!" << endl;
            cout << "-----------------\n" << endl;
        } else {
            cout << "Insufficient payment. Transaction canceled." << endl;
        }
    } else if (choice != 0) {
        cout << "Invalid choice or out of stock!" << endl;
    }
    pause();
}

// Function to handle repair requests
void submitRepairRequest() {
    RepairRequest request;
    clearScreen();
    cout << "\n--- Submit a Repair Request ---" << endl;
    cout << "Enter the name of the item: ";
    cin.ignore(); // Ignore leftover newline from previous input
    getline(cin, request.itemName);
    cout << "Describe the issue: ";
    getline(cin, request.issue);

    // Set initial status and submission time
    request.status = "Pending";
    request.submissionTime = time(nullptr);

    // Add request to the vector
    repairRequests.push_back(request);
    cout << "Your repair request has been submitted successfully!\n" << endl;
    pause();
}

// Function to display repair requests
void viewRepairRequests() {
    clearScreen();
    if (repairRequests.empty()) {
        cout << "\nNo repair requests at the moment.\n" << endl;
    } else {
        cout << "\n--- Repair Requests ---" << endl;
        cout << setw(5) << "No." << setw(20) << "Item" << setw(30) << "Issue" 
             << setw(15) << "Status" << setw(25) << "Submission Time" << endl;
        cout << string(95, '-') << endl;
        
        for (size_t i = 0; i < repairRequests.size(); i++) {
            cout << setw(5) << i + 1 
                 << setw(20) << repairRequests[i].itemName 
                 << setw(30) << repairRequests[i].issue
                 << setw(15) << repairRequests[i].status
                 << setw(25) << ctime(&repairRequests[i].submissionTime);
        }
    }
    pause();
}

// Function to update repair request status (Admin only)
void updateRepairStatus() {
    clearScreen();
    if (repairRequests.empty()) {
        cout << "\nNo repair requests to update.\n" << endl;
    } else {
        int choice;
        string newStatus;
        
        cout << "\n--- Update Repair Request Status ---" << endl;
        viewRepairRequests();
        
        cout << "Enter the request number to update (0 to cancel): ";
        cin >> choice;
        
        if (choice > 0 && choice <= static_cast<int>(repairRequests.size())) {
            cout << "Enter new status (Pending/In Progress/Completed): ";
            cin >> newStatus;
            
            repairRequests[choice - 1].status = newStatus;
            cout << "Status updated successfully!" << endl;
        } else if (choice != 0) {
            cout << "Invalid choice!" << endl;
        }
    }
    pause();
}

// Function to display sales report
void displaySalesReport() {
    clearScreen();
    if (transactions.empty()) {
        cout << "\nNo transactions recorded yet.\n" << endl;
    } else {
        int totalRevenue = 0;
        cout << "\n--- Sales Report ---" << endl;
        cout << setw(5) << "No." << setw(25) << "Item" << setw(10) << "Price" 
             << setw(25) << "Timestamp" << endl;
        cout << string(65, '-') << endl;
        
        for (size_t i = 0; i < transactions.size(); i++) {
            cout << setw(5) << i + 1 
                 << setw(25) << transactions[i].itemName 
                 << setw(10) << transactions[i].price
                 << setw(25) << ctime(&transactions[i].timestamp);
            totalRevenue += transactions[i].price;
        }
        
        cout << "\nTotal Revenue: P" << totalRevenue << endl;
    }
    pause();
}

// Function to save data to file
void saveDataToFile() {
    ofstream outFile("shop_data.txt");
    if (outFile.is_open()) {
        // Save transactions
        outFile << transactions.size() << endl;
        for (const auto& trans : transactions) {
            outFile << trans.itemName << "|" << trans.price << "|" << trans.timestamp << endl;
        }
        
        // Save repair requests
        outFile << repairRequests.size() << endl;
        for (const auto& req : repairRequests) {
            outFile << req.itemName << "|" << req.issue << "|" << req.status << "|" << req.submissionTime << endl;
        }
        
        outFile.close();
        cout << "Data saved successfully!" << endl;
    } else {
        cout << "Unable to save data to file." << endl;
    }
}

// Function to load data from file
void loadDataFromFile() {
    ifstream inFile("shop_data.txt");
    if (inFile.is_open()) {
        string line;
        int count;
        
        // Load transactions
        inFile >> count;
        inFile.ignore(); // Ignore newline
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            if (pos1 != string::npos && pos2 != string::npos) {
                Transaction trans;
                trans.itemName = line.substr(0, pos1);
                trans.price = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                trans.timestamp = stoll(line.substr(pos2 + 1));
                transactions.push_back(trans);
            }
        }
        
        // Load repair requests
        inFile >> count;
        inFile.ignore(); // Ignore newline
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);
            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                RepairRequest req;
                req.itemName = line.substr(0, pos1);
                req.issue = line.substr(pos1 + 1, pos2 - pos1 - 1);
                req.status = line.substr(pos2 + 1, pos3 - pos2 - 1);
                req.submissionTime = stoll(line.substr(pos3 + 1));
                repairRequests.push_back(req);
            }
        }
        
        inFile.close();
        cout << "Data loaded successfully!" << endl;
    } else {
        cout << "No saved data found." << endl;
    }
}

// Main menu
int main() {
    int categoryChoice, userType;
    bool running = true;

    loadDataFromFile(); // Load saved data at the start

    while (running) {
        clearScreen();
        cout << "Are you a: \n1. Normal Customer\n2. Student\n3. Admin\nEnter your choice: ";
        cin >> userType;

        bool isStudent = (userType == 2);
        bool isAdmin = (userType == 3);

        while (true) {
            clearScreen();
            cout << "\nWelcome to the T.I.P. Recycle and Repair Shop Transaction System!" << endl;
            cout << "1. Buy Electronics" << endl;
            cout << "2. Buy Furniture" << endl;
            cout << "3. Buy Gadgets" << endl;
            cout << "4. Submit Repair Request
