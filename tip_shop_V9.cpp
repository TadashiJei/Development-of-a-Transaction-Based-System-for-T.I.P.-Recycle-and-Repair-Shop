#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <sstream>
#include <random>
#include <chrono>
#include <thread>
#include <queue>
#include <cmath>

using namespace std;

// Constants
const float STUDENT_DISCOUNT = 0.20;
const int POINTS_PER_PURCHASE = 10;
const int REPAIR_QUEUE_SIZE = 5;

// Struct definitions
struct Item {
    string name;
    string condition;
    int price;
    int stock;
    string category;
    vector<string> components;
};

struct RepairRequest {
    string itemName;
    string issue;
    string status;
    time_t submissionTime;
    int complexity;
    string assignedTechnician;
};

struct Transaction {
    string itemName;
    int price;
    time_t timestamp;
};

struct User {
    string username;
    string password;
    bool isStudent;
    int loyaltyPoints;
    vector<string> purchaseHistory;
    int repairExpertise;
};

struct PrintJob {
    string modelName;
    string material;
    int volume;
    string status;
};

struct RecyclingRecord {
    string itemName;
    float weight;
    time_t timestamp;
};

// Global variables
vector<Item> inventory;
vector<RepairRequest> repairRequests;
vector<Transaction> transactions;
map<string, User> users;
queue<RepairRequest> repairQueue;
vector<PrintJob> printJobs;
vector<RecyclingRecord> recyclingRecords;

// Function prototypes
void clearScreen();
void pause();
bool verifyStudentID();
void displayItems(const vector<Item>& items);
void adminAddNewItem();
void adminAddStock();
void buyItem(User& currentUser);
void submitRepairRequest();
void viewRepairRequests();
void updateRepairStatus();
void displaySalesReport();
void displayInventoryStatus();
void displayPopularItems();
void searchItems();
void redeemLoyaltyPoints(User& currentUser);
void saveDataToFile();
void loadDataFromFile();
void registerUser();
User* loginUser();
void initializeInventory();
void displayRepairQueue();
void assignRepairTechnician();
void performAutoDiagnostics(const string& itemName);
void submit3DPrintJob();
void update3DPrintStatus();
void recycleItem();
void displayRecyclingStats();
void offerTradeIn(User& currentUser);
void conductVirtualRepairSession();
void schedulePickupDelivery();
void displayUserDashboard(const User& user);
void generateQRCode(const string& data);
void simulateIoTDeviceRepair();
void applyAugmentedRealityRepair();
void offerSubscriptionService();
void provideRepairEstimate();
void manageInventoryAlerts();
void implementBlockchainWarranty();
void offerRemoteDiagnostics();
void gamifyLoyaltyProgram(User& currentUser);

// Function implementations
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool verifyStudentID() {
    int studentID;
    cout << "Enter your 7-digit school ID (starting from 2000000): ";
    cin >> studentID;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        return false;
    }

    if (studentID >= 2000000 && studentID <= 2999999) {
        cout << "Student ID verified successfully. You are eligible for the student discount.\n";
        return true;
    } else {
        cout << "Invalid ID! You are not eligible for the student discount.\n";
        return false;
    }
}

void displayItems(const vector<Item>& items) {
    cout << setw(5) << "No." << setw(25) << "Name" << setw(25) << "Condition" 
         << setw(10) << "Price" << setw(10) << "Stock" << setw(15) << "Category" << endl;
    cout << string(90, '-') << endl;
    
    for (size_t i = 0; i < items.size(); i++) {
        cout << setw(5) << i + 1 
             << setw(25) << items[i].name 
             << setw(25) << items[i].condition 
             << setw(10) << items[i].price 
             << setw(10) << items[i].stock
             << setw(15) << items[i].category << endl;
    }
}

void adminAddNewItem() {
    Item newItem;
    clearScreen();
    cout << "\n--- Admin: Add New Item ---" << endl;
    cout << "Enter item name: ";
    cin.ignore();
    getline(cin, newItem.name);
    cout << "Enter item condition: ";
    getline(cin, newItem.condition);
    cout << "Enter item price: ";
    cin >> newItem.price;
    cout << "Enter initial stock: ";
    cin >> newItem.stock;
    cout << "Enter category (Electronics/Furniture/Gadgets): ";
    cin.ignore();
    getline(cin, newItem.category);

    inventory.push_back(newItem);
    cout << "New item added successfully!" << endl;
    pause();
}

void adminAddStock() {
    int choice, additionalStock;
    clearScreen();
    cout << "\n--- Admin: Add Stock ---" << endl;
    displayItems(inventory);
    cout << "Enter the item number to add stock (0 to cancel): ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        pause();
        return;
    }

    if (choice > 0 && choice <= static_cast<int>(inventory.size())) {
        cout << "Enter the amount of stock to add: ";
        cin >> additionalStock;

        if (cin.fail() || additionalStock < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive number.\n";
        } else {
            inventory[choice - 1].stock += additionalStock;
            cout << "Stock updated. New stock for " << inventory[choice - 1].name << ": " << inventory[choice - 1].stock << endl;
        }
    } else if (choice != 0) {
        cout << "Invalid choice!" << endl;
    }
    pause();
}

void buyItem(User& currentUser) {
    int choice;
    clearScreen();
    cout << "Select an item to buy: " << endl;
    displayItems(inventory);
    cout << "Enter your choice (0 to cancel): ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
        pause();
        return;
    }

    if (choice > 0 && choice <= static_cast<int>(inventory.size()) && inventory[choice - 1].stock > 0) {
        int payment;
        float price = inventory[choice - 1].price;

        if (currentUser.isStudent && verifyStudentID()) {
            price -= price * STUDENT_DISCOUNT;
            cout << "Discounted Price: P" << price << endl;
        } else {
            cout << "Total Price: P" << price << endl;
        }

        cout << "Enter payment amount: P";
        cin >> payment;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            pause();
            return;
        }

        if (payment >= price) {
            int change = payment - price;
            cout << "Payment successful. Change: P" << change << endl;

            inventory[choice - 1].stock--;

            transactions.push_back({inventory[choice - 1].name, static_cast<int>(price), time(nullptr)});

            currentUser.loyaltyPoints += POINTS_PER_PURCHASE;
            cout << "You earned " << POINTS_PER_PURCHASE << " loyalty points!" << endl;

            cout << "\n--- Receipt ---" << endl;
            cout << "Item: " << inventory[choice - 1].name << endl;
            cout << "Condition: " << inventory[choice - 1].condition << endl;
            cout << "Price: P" << price << endl;
            cout << "Payment: P" << payment << endl;
            cout << "Change: P" << change << endl;
            cout << "Loyalty Points Earned: " << POINTS_PER_PURCHASE << endl;
            cout << "Total Loyalty Points: " << currentUser.loyaltyPoints << endl;
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

void submitRepairRequest() {
    RepairRequest request;
    clearScreen();
    cout << "\n--- Submit a Repair Request ---" << endl;
    cout << "Enter the name of the item: ";
    cin.ignore();
    getline(cin, request.itemName);
    cout << "Describe the issue: ";
    getline(cin, request.issue);

    request.status = "Pending";
    request.submissionTime = time(nullptr);

    repairRequests.push_back(request);
    cout << "Your repair request has been submitted successfully!\n" << endl;
    pause();
}

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
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            pause();
            return;
        }
        
        if (choice > 0 && choice <= static_cast<int>(repairRequests.size())) {
            cout << "Enter new status (Pending/In Progress/Completed): ";
            cin >> newStatus;
            
            transform(newStatus.begin(), newStatus.end(), newStatus.begin(), ::tolower);
            if (newStatus == "pending" || newStatus == "in progress" || newStatus == "completed") {
                repairRequests[choice - 1].status = newStatus;
                cout << "Status updated successfully!" << endl;
            } else {
                cout << "Invalid status. Please enter Pending, In Progress, or Completed." << endl;
            }
        } else if (choice != 0) {
            cout << "Invalid choice!" << endl;
        }
    }
    pause();
}

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

void displayInventoryStatus() {
    clearScreen();
    cout << "\n--- Inventory Status ---" << endl;
    displayItems(inventory);
    
    int totalItems = 0;
    int totalValue = 0;
    for (const auto& item : inventory) {
        totalItems += item.stock;
        totalValue += item.price * item.stock;
    }
    
    cout << "\nTotal number of items in inventory: " << totalItems << endl;
    cout << "Total value of inventory: P" << totalValue << endl;
    pause();
}

void displayPopularItems() {
    clearScreen();
    cout << "\n--- Popular Items ---" << endl;
    
    map<string, int> itemSales;
    for (const auto& transaction : transactions) {
        itemSales[transaction.itemName]++;
    }
    
    vector<pair<string, int>> sortedSales(itemSales.begin(), itemSales.end());
    sort(sortedSales.begin(), sortedSales.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    cout << setw(5) << "Rank" << setw(25) << "Item" << setw(10) << "Sales" << endl;
    cout << string(40, '-') << endl;
    
    for (size_t i = 0; i < min(sortedSales.size(), size_t(10)); 

 i++) {
        cout << setw(5) << i + 1 
             << setw(25) << sortedSales[i].first 
             << setw(10) << sortedSales[i].second << endl;
    }
    pause();
}

void searchItems() {
    string searchTerm;
    clearScreen();
    cout << "\n--- Search Items ---" << endl;
    cout << "Enter search term: ";
    cin.ignore();
    getline(cin, searchTerm);
    
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
    
    vector<Item> searchResults;
    for (const auto& item : inventory) {
        string lowerName = item.name;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        if (lowerName.find(searchTerm) != string::npos) {
            searchResults.push_back(item);
        }
    }
    
    if (searchResults.empty()) {
        cout << "No items found matching your search term." << endl;
    } else {
        cout << "\nSearch Results:" << endl;
        displayItems(searchResults);
    }
    pause();
}

void redeemLoyaltyPoints(User& currentUser) {
    clearScreen();
    cout << "\n--- Redeem Loyalty Points ---" << endl;
    cout << "You have " << currentUser.loyaltyPoints << " loyalty points." << endl;
    
    int pointsToRedeem;
    cout << "Enter the number of points to redeem (100 points = P10 discount): ";
    cin >> pointsToRedeem;
    
    if (cin.fail() || pointsToRedeem < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive number.\n";
        pause();
        return;
    }
    
    if (pointsToRedeem > currentUser.loyaltyPoints) {
        cout << "You don't have enough points to redeem." << endl;
    } else {
        int discount = pointsToRedeem / 10;
        currentUser.loyaltyPoints -= pointsToRedeem;
        cout << "You've redeemed " << pointsToRedeem << " points for a P" << discount << " discount on your next purchase." << endl;
        cout << "Remaining loyalty points: " << currentUser.loyaltyPoints << endl;
    }
    pause();
}

void saveDataToFile() {
    ofstream outFile("shop_data.txt");
    if (outFile.is_open()) {
        // Save inventory
        outFile << inventory.size() << endl;
        for (const auto& item : inventory) {
            outFile << item.name << "|" << item.condition << "|" << item.price << "|" << item.stock << "|" << item.category << endl;
        }
        
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
        
        // Save user accounts
        outFile << users.size() << endl;
        for (const auto& user : users) {
            outFile << user.first << "|" << user.second.password << "|" << user.second.isStudent << "|" << user.second.loyaltyPoints << endl;
        }
        
        outFile.close();
        cout << "Data saved successfully!" << endl;
    } else {
        cout << "Unable to save data to file." << endl;
    }
}

void loadDataFromFile() {
    ifstream inFile("shop_data.txt");
    if (inFile.is_open()) {
        string line;
        int count;
        
        // Load inventory
        inFile >> count;
        inFile.ignore();
        inventory.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            istringstream iss(line);
            string name, condition, category;
            int price, stock;
            getline(iss, name, '|');
            getline(iss, condition, '|');
            iss >> price;
            iss.ignore();
            iss >> stock;
            iss.ignore();
            getline(iss, category);
            inventory.push_back({name, condition, price, stock, category});
        }
        
        // Load transactions
        inFile >> count;
        inFile.ignore();
        transactions.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            istringstream iss(line);
            string itemName;
            int price;
            time_t timestamp;
            getline(iss, itemName, '|');
            iss >> price;
            iss.ignore();
            iss >> timestamp;
            transactions.push_back({itemName, price, timestamp});
        }
        
        // Load repair requests
        inFile >> count;
        inFile.ignore();
        repairRequests.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            istringstream iss(line);
            string itemName, issue, status;
            time_t submissionTime;
            getline(iss, itemName, '|');
            getline(iss, issue, '|');
            getline(iss, status, '|');
            iss >> submissionTime;
            repairRequests.push_back({itemName, issue, status, submissionTime});
        }
        
        // Load user accounts
        inFile >> count;
        inFile.ignore();
        users.clear();
        for (int i = 0; i < count; i++) {
            getline(inFile, line);
            istringstream iss(line);
            string username, password;
            bool isStudent;
            int loyaltyPoints;
            getline(iss, username, '|');
            getline(iss, password, '|');
            iss >> isStudent;
            iss.ignore();
            iss >> loyaltyPoints;
            users[username] = {username, password, isStudent, loyaltyPoints};
        }
        
        inFile.close();
        cout << "Data loaded successfully!" << endl;
    } else {
        cout << "No saved data found. Starting with empty inventory and user base." << endl;
    }
}

void registerUser() {
    string username, password;
    bool isStudent;
    
    clearScreen();
    cout << "\n--- User Registration ---" << endl;
    cout << "Enter username: ";
    cin >> username;
    
    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please choose a different username." << endl;
        pause();
        return;
    }
    
    cout << "Enter password: ";
    cin >> password;
    cout << "Are you a student? (1 for Yes, 0 for No): ";
    cin >> isStudent;
    
    users[username] = {username, password, isStudent, 0};
    cout << "User registered successfully!" << endl;
    pause();
}

User* loginUser() {
    string username, password;
    
    clearScreen();
    cout << "\n--- User Login ---" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    
    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        cout << "Login successful!" << endl;
        return &(it->second);
    } else {
        cout << "Invalid username or password." << endl;
        pause();
        return nullptr;
    }
}

// Main function
int main() {
    int choice;
    bool running = true;
    User* currentUser = nullptr;

    loadDataFromFile(); // Load saved data at the start

    while (running) {
        clearScreen();
        cout << "Welcome to the Advanced T.I.P. Recycle and Repair Shop System!" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                currentUser = loginUser();
                if (currentUser) {
                    bool loggedIn = true;
                    while (loggedIn) {
                        clearScreen();
                        cout << "Welcome, " << currentUser->username << "!" << endl;
                        cout << "1. Buy Items" << endl;
                        cout << "2. Submit Repair Request" << endl;
                        cout << "3. View Repair Requests" << endl;
                        cout << "4. Search Items" << endl;
                        cout << "5. Redeem Loyalty Points" << endl;
                        cout << "6. Trade-In Device" << endl;
                        cout << "7. Virtual Repair Session" << endl;
                        cout << "8. Schedule Pickup/Delivery" << endl;
                        cout << "9. View Dashboard" << endl;
                        cout << "10. Generate QR Code for Item" << endl;
                        cout << "11. IoT Device Repair" << endl;
                        cout << "12. Use AR Repair Guide" << endl;
                        cout << "13. Repair Subscription Service" << endl;
                        cout << "14. Get Repair Estimate" << endl;
                        cout << "15. Remote Diagnostics" << endl;
                        cout << "16. Participate in Loyalty Game" << endl;
                        if (currentUser->username == "admin") {
                            cout << "17. Add New Item" << endl;
                            cout << "18. Add Stock" << endl;
                            cout << "19. Update Repair Status" << endl;
                            cout << "20. View Sales Report" << endl;
                            cout << "21. View Inventory Status" << endl;
                            cout << "22. View Popular Items" << endl;
                            cout << "23. Manage Repair Queue" << endl;
                            cout << "24. Manage 3D Print Jobs" << endl;
                            cout << "25. View Recycling Stats" << endl;
                            cout << "26. Manage Inventory Alerts" << endl;
                            cout << "27. Blockchain Warranty Management" << endl;
                        }
                        cout << "0. Logout" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1: buyItem(*currentUser); break;
                            case 2: submitRepairRequest(); break;
                            case 3: viewRepairRequests(); break;
                            case 4: searchItems(); break;
                            case 5: redeemLoyaltyPoints(*currentUser); break;
                            case 6: offerTradeIn(*currentUser); break;
                            case 7: conductVirtualRepairSession(); break;
                            case 8: schedulePickupDelivery(); break;
                            case 9: displayUserDashboard(*currentUser); break;
                            case 10: 
                                cout << "Enter item name for QR code: ";
                                {
                                    string itemName;
                                    cin.ignore();
                                    getline(cin, itemName);
                                    generateQRCode(itemName);
                                }
                                break;
                            case 11: simulateIoTDeviceRepair(); break;
                            case 12: applyAugmentedRealityRepair(); break;
                            case 13: offerSubscriptionService(); break;
                            case 14: provideRepairEstimate(); break;
                            case 15: offerRemoteDiagnostics(); break;
                            case 16: gamifyLoyaltyProgram(*currentUser); break;
                            case 17: if (currentUser->username == "admin") adminAddNewItem(); break;
                            case 18: if (currentUser->username == "admin") adminAddStock(); break;
                            case 19: if (currentUser->username == "admin") updateRepairStatus(); break;
                            case 20: if (currentUser->username == "admin") displaySalesReport(); break;
                            case 21: if (currentUser->username == "admin") displayInventoryStatus(); break;
                            case 22: if (currentUser->username == "admin") displayPopularItems(); break;
                            case 23: 
                                if (currentUser->username == "admin") {
                                    displayRepairQueue();
                                    assignRepairTechnician();
                                }
                                break;
                            case 24:
                                if (currentUser->username == "admin") {
                                    submit3DPrintJob();
                                    update3DPrintStatus();
                                }
                                break;
                            case 25: if (currentUser->username == "admin") displayRecyclingStats(); break;
                            case 26: if (currentUser->username == "admin") manageInventoryAlerts(); break;
                            case 27: if (currentUser->username == "admin") implementBlockchainWarranty(); break;
                            case 0: loggedIn = false; break;
                            default: cout << "Invalid choice!" << endl; pause();
                        }
                    }
                }
                break;
            case 3:
                running = false;
                break;
            default:
                cout << "Invalid choice!" << endl;
                pause();
        }
    }

    saveDataToFile(); // Save data before exiting
    cout << "Thank you for using the Advanced T.I.P. Recycle and Repair Shop System!" << endl;
    return 0;
}
