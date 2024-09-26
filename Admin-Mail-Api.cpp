#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
using namespace std;

// Sample Mailgun API function for sending emails
void sendEmail(const string& to, const string& subject, const string& body) {
    // Simulate an email sending function using Mailgun API
    cout << "Sending email to " << to << " with subject: " << subject << endl;
    cout << "Body: " << body << endl;
    // Use Mailgun's API in actual implementation
    // Example: Use cURL or HTTP library to call Mailgun API
}

// User struct
struct User {
    string username;
    string password;
    string role; // "admin" or "customer"
    vector<string> orderHistory;
};

// Discount struct
struct Discount {
    string code;
    double discountPercentage;
};

// Repair struct
struct RepairRequest {
    string itemName;
    string issue;
    string status;
    string customerEmail;
};

// Inventory struct
struct Item {
    string name;
    string condition;
    int price;
    int stock;
};

// Admin functions
void restockInventory(Item& item, int quantity) {
    item.stock += quantity;
    cout << item.name << " restocked to " << item.stock << " units." << endl;
}

void viewSalesReport(const vector<User>& users) {
    cout << "\n--- Sales Report ---" << endl;
    for (const auto& user : users) {
        if (user.role == "customer") {
            cout << user.username << " purchased: " << endl;
            for (const auto& order : user.orderHistory) {
                cout << "  " << order << endl;
            }
        }
    }
}

// Login system (basic example)
bool login(const unordered_map<string, User>& users, string& currentUsername) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        currentUsername = username;
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Invalid credentials!" << endl;
    return false;
}

// Apply discount system
double applyDiscount(double total, const vector<Discount>& discounts) {
    string code;
    cout << "Enter discount code (or 'none' to skip): ";
    cin >> code;
    if (code != "none") {
        for (const auto& discount : discounts) {
            if (discount.code == code) {
                total -= total * (discount.discountPercentage / 100);
                cout << "Discount applied: " << discount.discountPercentage << "%" << endl;
                return total;
            }
        }
        cout << "Invalid discount code." << endl;
    }
    return total;
}

// Repair tracking
void submitRepairRequest(vector<RepairRequest>& repairs, const string& username) {
    RepairRequest repair;
    cout << "Enter the item name for repair: ";
    cin.ignore();
    getline(cin, repair.itemName);
    cout << "Describe the issue: ";
    getline(cin, repair.issue);
    repair.status = "Under Review";
    repair.customerEmail = username + "@mail.com"; // For demo purposes
    repairs.push_back(repair);
    sendEmail(repair.customerEmail, "Repair Request Submitted", "Your repair request is under review.");
    cout << "Repair request submitted!" << endl;
}

// Main menu
int main() {
    unordered_map<string, User> users = {
        {"admin", {"admin", "admin123", "admin", {}}},
        {"customer", {"customer", "customer123", "customer", {}}}
    };

    vector<Discount> discounts = {
        {"SAVE10", 10.0}, {"STUDENT20", 20.0}
    };

    vector<Item> inventory = {
        {"Smartphone", "Fully Functional", 2000, 5},
        {"Laptop", "Fully Functional", 5000, 3}
    };

    vector<RepairRequest> repairRequests;
    vector<User> customerList;

    string currentUsername;
    bool loggedIn = false;

    while (true) {
        int choice;
        cout << "\n1. Login\n2. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            if (login(users, currentUsername)) {
                User& user = users[currentUsername];
                if (user.role == "customer") {
                    int customerChoice;
                    cout << "Welcome, " << user.username << "!" << endl;
                    cout << "1. Buy Item\n2. Submit Repair Request\n3. View Order History\n4. Logout" << endl;
                    cin >> customerChoice;

                    switch (customerChoice) {
                        case 1:
                            // Simulate buying an item
                            cout << "Buying Smartphone..." << endl;
                            user.orderHistory.push_back("Smartphone - P2000");
                            break;
                        case 2:
                            submitRepairRequest(repairRequests, user.username);
                            break;
                        case 3:
                            cout << "Order History: " << endl;
                            for (const auto& order : user.orderHistory) {
                                cout << order << endl;
                            }
                            break;
                        case 4:
                            loggedIn = false;
                            break;
                    }
                } else if (user.role == "admin") {
                    int adminChoice;
                    cout << "Welcome, Admin!" << endl;
                    cout << "1. Restock Inventory\n2. View Sales Report\n3. Logout" << endl;
                    cin >> adminChoice;

                    switch (adminChoice) {
                        case 1:
                            restockInventory(inventory[0], 10); // For demo, restocking Smartphone
                            break;
                        case 2:
                            viewSalesReport(customerList); // Show sales report
                            break;
                        case 3:
                            loggedIn = false;
                            break;
                    }
                }
            }
        } else if (choice == 2) {
            break;
        }
    }

    return 0;
}
