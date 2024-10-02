#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <sstream>
#include <curl/curl.h> // You'll need to install libcurl for this

using namespace std;

// ... [Previous code remains the same] ...

// New struct for receipts
struct Receipt {
    int id;
    string itemName;
    string condition;
    float price;
    int payment;
    int change;
    time_t timestamp;
};

// Vector to store receipts
vector<Receipt> receipts;

// Function to generate ASCII art receipt
string generateASCIIReceipt(const Receipt& receipt) {
    stringstream ss;
    ss << "+-----------------------------------------+\n";
    ss << "|    T.I.P. Recycle and Repair Shop       |\n";
    ss << "|              RECEIPT                    |\n";
    ss << "+-----------------------------------------+\n";
    ss << "| Receipt ID: " << setw(28) << receipt.id << " |\n";
    ss << "| Date: " << setw(35) << ctime(&receipt.timestamp);
    ss << "+-----------------------------------------+\n";
    ss << "| Item: " << setw(35) << receipt.itemName << " |\n";
    ss << "| Condition: " << setw(30) << receipt.condition << " |\n";
    ss << "| Price: " << setw(34) << receipt.price << " |\n";
    ss << "| Payment: " << setw(32) << receipt.payment << " |\n";
    ss << "| Change: " << setw(33) << receipt.change << " |\n";
    ss << "+-----------------------------------------+\n";
    ss << "|        Thank you for your purchase!     |\n";
    ss << "+-----------------------------------------+\n";
    return ss.str();
}

// Function to simulate sending email (replace with actual Mailgun API call)
void sendEmailReceipt(const string& email, const string& receiptContent) {
    cout << "Simulating email sent to: " << email << endl;
    cout << "Email content:\n" << receiptContent << endl;
    
    // In a real implementation, you would use libcurl to send an HTTP POST request to Mailgun's API
    // Here's a basic example of how you might do that:
    /*
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.mailgun.net/v3/your-domain.com/messages");
        curl_easy_setopt(curl, CURLOPT_USERPWD, "api:YOUR_API_KEY");
        
        string post_fields = "from=TIP Shop <mailgun@your-domain.com>&to=" + email + 
                             "&subject=Your Receipt&text=" + receiptContent;
        
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        
        curl_easy_cleanup(curl);
    }
    */
}

// Function to handle a purchase (updated)
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

            // Create and store receipt
            Receipt newReceipt = {
                static_cast<int>(receipts.size() + 1),
                items[choice - 1].name,
                items[choice - 1].condition,
                price,
                payment,
                change,
                time(nullptr)
            };
            receipts.push_back(newReceipt);

            // Print receipt
            string receiptContent = generateASCIIReceipt(newReceipt);
            cout << receiptContent << endl;

            // Ask if user wants to receive receipt via email
            string wantEmail;
            cout << "Would you like to receive a copy of the receipt via email? (yes/no): ";
            cin >> wantEmail;
            
            if (wantEmail == "yes" || wantEmail == "Yes" || wantEmail == "YES") {
                string email;
                cout << "Please enter your email address: ";
                cin >> email;
                sendEmailReceipt(email, receiptContent);
            }

        } else {
            cout << "Insufficient payment. Transaction canceled." << endl;
        }
    } else if (choice != 0) {
        cout << "Invalid choice or out of stock!" << endl;
    }
    pause();
}

// Function to view receipts
void viewReceipts() {
    clearScreen();
    if (receipts.empty()) {
        cout << "No receipts available." << endl;
    } else {
        cout << "--- Receipts ---" << endl;
        for (const auto& receipt : receipts) {
            cout << "Receipt ID: " << receipt.id << " | Item: " << receipt.itemName 
                 << " | Date: " << ctime(&receipt.timestamp);
        }
        
        int choice;
        cout << "Enter receipt ID to view details (0 to exit): ";
        cin >> choice;
        
        if (choice > 0 && choice <= static_cast<int>(receipts.size())) {
            string receiptContent = generateASCIIReceipt(receipts[choice - 1]);
            cout << receiptContent << endl;
            
            string wantEmail;
            cout << "Would you like to receive a copy of this receipt via email? (yes/no): ";
            cin >> wantEmail;
            
            if (wantEmail == "yes" || wantEmail == "Yes" || wantEmail == "YES") {
                string email;
                cout << "Please enter your email address: ";
                cin >> email;
                sendEmailReceipt(email, receiptContent);
            }
        }
    }
    pause();
}

// Updated main menu
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
            cout << "4. Submit Repair Request" << endl;
            cout << "5. View Repair Requests" << endl;
            cout << "6. View Receipts" << endl;
            if (isAdmin) {
                cout << "7. Add Stock (Admin Only)" << endl;
                cout << "8. Update Repair Status (Admin Only)" << endl;
                cout << "9. View Sales Report (Admin Only)" << endl;
            }
            cout << "0. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> categoryChoice;

            switch (categoryChoice) {
                case 1:
                    buyItem(electronics, isStudent);
                    break;
                case 2:
                    buyItem(furniture, isStudent);
                    break;
                case 3:
                    buyItem(gadgets, isStudent);
                    break;
                case 4:
                    submitRepairRequest();
                    break;
                case 5:
                    viewRepairRequests();
                    break;
                case 6:
                    viewReceipts();
                    break;
                case 7:
                    if (isAdmin) {
                        int stockChoice;
                        cout << "Choose category to add stock:\n1. Electronics\n2. Furniture\n3. Gadgets\nEnter choice: ";
                        cin >> stockChoice;
                        switch (stockChoice) {
                            case 1: adminAddStock(electronics); break;
                            case 2: adminAddStock(furniture); break;
                            case 3: adminAddStock(gadgets); break;
                            default: cout << "Invalid choice!" << endl;
                        }
                    } else {
                        cout << "Access denied. Admin only." << endl;
                        pause();
                    }
                    break;
                case 8:
                    if (isAdmin) {
                        updateRepairStatus();
                    } else {
                        cout << "Access denied. Admin only." << endl;
                        pause();
                    }
                    break;
                case 9:
                    if (isAdmin) {
                        displaySalesReport();
                    } else {
                        cout << "Access denied. Admin only." << endl;
                        pause();
                    }
                    break;
                case 0:
                    running = false;
                    saveDataToFile(); // Save data before exiting
                    cout << "Thank you for using the T.I.P. Recycle and Repair Shop Transaction System!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice, please try again." << endl;
                    pause();
                    break;
            }
        }
    }

    return 0;
}
