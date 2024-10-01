#include <iostream>
#include <string>
#include <vector>
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
};

// Arrays for different categories
Item electronics[] = {
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

Item furniture[] = {
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

Item gadgets[] = {
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
void displayItems(Item items[], int size) {
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << items[i].name << " (" << items[i].condition << ") - P" << items[i].price << " [Stock: " << items[i].stock << "]" << endl;
    }
}

// Function for admin to add stock
void adminAddStock(Item items[], int size) {
    int choice, additionalStock;
    cout << "\n--- Admin: Add Stock ---" << endl;
    displayItems(items, size);
    cout << "Enter the item number to add stock: ";
    cin >> choice;

    if (choice > 0 && choice <= size) {
        cout << "Enter the amount of stock to add: ";
        cin >> additionalStock;
        items[choice - 1].stock += additionalStock;
        cout << "Stock updated. New stock: " << items[choice - 1].stock << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }
}

// Function to handle a purchase
void buyItem(Item items[], int size, bool isStudent) {
    int choice;
    cout << "Select an item to buy: " << endl;
    displayItems(items, size);
    cout << "Enter your choice (1-" << size << "): ";
    cin >> choice;

    if (choice > 0 && choice <= size && items[choice - 1].stock > 0) {
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

            // Decrease stock
            items[choice - 1].stock--;

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
    } else {
        cout << "Invalid choice or out of stock!" << endl;
    }
}

// Function to handle repair requests
void submitRepairRequest() {
    RepairRequest request;
    cout << "\n--- Submit a Repair Request ---" << endl;
    cout << "Enter the name of the item: ";
    cin.ignore(); // Ignore leftover newline from previous input
    getline(cin, request.itemName);
    cout << "Describe the issue: ";
    getline(cin, request.issue);

    // Add request to the vector
    repairRequests.push_back(request);
    cout << "Your repair request has been submitted successfully!\n" << endl;
}

// Function to display repair requests
void viewRepairRequests() {
    if (repairRequests.empty()) {
        cout << "\nNo repair requests at the moment.\n" << endl;
    } else {
        cout << "\n--- Repair Requests ---" << endl;
        for (size_t i = 0; i < repairRequests.size(); i++) {
            cout << i + 1 << ". Item: " << repairRequests[i].itemName << " | Issue: " << repairRequests[i].issue << endl;
        }
        cout << "------------------------\n" << endl;
    }
}

// Main menu
int main() {
    int categoryChoice, userType;
    bool running = true;

    cout << "Are you a: \n1. Normal Customer\n2. Student\n3. Admin\nEnter your choice: ";
    cin >> userType;

    bool isStudent = (userType == 2);
    bool isAdmin = (userType == 3);

    while (running) {
        cout << "\nWelcome to the T.I.P. Recycle and Repair Shop Transaction System!" << endl;
        cout << "1. Buy Electronics" << endl;
        cout << "2. Buy Furniture" << endl;
        cout << "3. Buy Gadgets" << endl;
        cout << "4. Submit Repair Request" << endl;
        cout << "5. View Repair Requests" << endl;
        if (isAdmin) {
            cout << "6. Add Stock (Admin Only)" << endl;
        }
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> categoryChoice;

        switch (categoryChoice) {
            case 1:
                buyItem(electronics, 9, isStudent);
                break;
            case 2:
                buyItem(furniture, 9, isStudent);
                break;
            case 3:
                buyItem(gadgets, 9, isStudent);
                break;
            case 4:
                submitRepairRequest();
                break;
            case 5:
                viewRepairRequests();
                break;
            case 6:
                if (isAdmin) {
                    adminAddStock(electronics, 9);
                    adminAddStock(furniture, 9);
                    adminAddStock(gadgets, 9);
                } else {
                    cout << "Invalid choice, please try again." << endl;
                }
                break;
            case 7:
                running = false;
                cout << "Thank you for using the T.I.P. Recycle and Repair Shop Transaction System!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }

    return 0;
}
