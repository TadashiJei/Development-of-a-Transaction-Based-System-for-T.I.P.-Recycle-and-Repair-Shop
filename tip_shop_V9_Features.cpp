// ... (previous code remains unchanged)

void offerTradeIn(User& currentUser) {
    clearScreen();
    cout << "\n--- Trade-In Offer ---" << endl;
    
    if (currentUser.purchaseHistory.empty()) {
        cout << "You don't have any previous purchases eligible for trade-in." << endl;
        pause();
        return;
    }

    cout << "Your eligible items for trade-in:" << endl;
    for (size_t i = 0; i < currentUser.purchaseHistory.size(); ++i) {
        cout << i + 1 << ". " << currentUser.purchaseHistory[i] << endl;
    }

    int choice;
    cout << "Select an item to trade in (0 to cancel): ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(currentUser.purchaseHistory.size())) {
        string itemToTradeIn = currentUser.purchaseHistory[choice - 1];
        int tradeInValue = 0;

        // Find the item in the inventory to determine its value
        for (const auto& item : inventory) {
            if (item.name == itemToTradeIn) {
                tradeInValue = item.price * 0.4; // Offer 40% of the original price
                break;
            }
        }

        cout << "We can offer you P" << tradeInValue << " for your " << itemToTradeIn << "." << endl;
        cout << "Do you accept this offer? (1 for Yes, 0 for No): ";
        int accept;
        cin >> accept;

        if (accept) {
            currentUser.loyaltyPoints += tradeInValue; // Add trade-in value as loyalty points
            cout << "Trade-in successful! P" << tradeInValue << " has been added to your loyalty points." << endl;
            currentUser.purchaseHistory.erase(currentUser.purchaseHistory.begin() + choice - 1);
        } else {
            cout << "Trade-in offer declined." << endl;
        }
    } else if (choice != 0) {
        cout << "Invalid choice!" << endl;
    }
    pause();
}

void conductVirtualRepairSession() {
    clearScreen();
    cout << "\n--- Virtual Repair Session ---" << endl;
    cout << "Initiating virtual repair session..." << endl;
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Please describe the issue with your device: ";
    string issue;
    cin.ignore();
    getline(cin, issue);

    cout << "\nAnalyzing issue..." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    cout << "\nBased on your description, here are some troubleshooting steps:" << endl;
    cout << "1. Check all cable connections" << endl;
    cout << "2. Restart the device" << endl;
    cout << "3. Update device firmware" << endl;
    cout << "4. Perform a factory reset if issues persist" << endl;

    cout << "\nDid these steps help resolve your issue? (1 for Yes, 0 for No): ";
    int resolved;
    cin >> resolved;

    if (resolved) {
        cout << "Great! Glad we could help you resolve the issue virtually." << endl;
    } else {
        cout << "We're sorry the virtual session couldn't resolve your issue." << endl;
        cout << "Would you like to schedule an in-person repair? (1 for Yes, 0 for No): ";
        int schedule;
        cin >> schedule;
        if (schedule) {
            submitRepairRequest();
        }
    }
    pause();
}

void schedulePickupDelivery() {
    clearScreen();
    cout << "\n--- Schedule Pickup/Delivery ---" << endl;
    
    cout << "1. Schedule a pickup for repair" << endl;
    cout << "2. Schedule a delivery for repaired item" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    string address, date, timeSlot;
    cin.ignore();

    cout << "Enter your address: ";
    getline(cin, address);
    cout << "Enter preferred date (DD/MM/YYYY): ";
    getline(cin, date);
    cout << "Enter preferred time slot (e.g., 10AM-12PM): ";
    getline(cin, timeSlot);

    if (choice == 1) {
        cout << "Pickup scheduled for repair item." << endl;
    } else if (choice == 2) {
        cout << "Delivery scheduled for repaired item." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }

    cout << "Address: " << address << endl;
    cout << "Date: " << date << endl;
    cout << "Time Slot: " << timeSlot << endl;
    cout << "Thank you for using our pickup/delivery service!" << endl;
    pause();
}

void displayUserDashboard(const User& user) {
    clearScreen();
    cout << "\n--- User Dashboard: " << user.username << " ---" << endl;
    cout << "Loyalty Points: " << user.loyaltyPoints << endl;
    cout << "Student Status: " << (user.isStudent ? "Yes" : "No") << endl;
    
    if (user.repairExpertise > 0) {
        cout << "Repair Expertise Level: " << user.repairExpertise << endl;
    }

    cout << "\nPurchase History:" << endl;
    if (user.purchaseHistory.empty()) {
        cout << "No purchases yet." << endl;
    } else {
        for (const auto& purchase : user.purchaseHistory) {
            cout << "- " << purchase << endl;
        }
    }

    cout << "\nActive Repair Requests:" << endl;
    bool hasActiveRepairs = false;
    for (const auto& repair : repairRequests) {
        if (repair.assignedTechnician == user.username) {
            cout << "- " << repair.itemName << " (" << repair.status << ")" << endl;
            hasActiveRepairs = true;
        }
    }
    if (!hasActiveRepairs) {
        cout << "No active repair requests." << endl;
    }

    pause();
}

void generateQRCode(const string& data) {
    cout << "Generating QR Code for: " << data << endl;
    // Simplified QR Code representation
    cout << "┌─────────┐" << endl;
    cout << "│ █ █ █ █ │" << endl;
    cout << "│ █     █ │" << endl;
    cout << "│ █ █ █ █ │" << endl;
    cout << "└─────────┘" << endl;
    cout << "QR Code generated. Scan for details." << endl;
    pause();
}

void simulateIoTDeviceRepair() {
    clearScreen();
    cout << "\n--- IoT Device Repair Simulation ---" << endl;
    cout << "Connecting to IoT device..." << endl;
    this_thread::sleep_for(chrono::seconds(2));

    cout << "Device connected. Running diagnostics..." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);
    int issue = dis(gen);

    cout << "Diagnostic complete. Issue detected: ";
    switch (issue) {
        case 1:
            cout << "Firmware outdated" << endl;
            cout << "Updating firmware..." << endl;
            this_thread::sleep_for(chrono::seconds(5));
            cout << "Firmware updated successfully." << endl;
            break;
        case 2:
            cout << "Sensor malfunction" << endl;
            cout << "Recalibrating sensors..." << endl;
            this_thread::sleep_for(chrono::seconds(4));
            cout << "Sensors recalibrated." << endl;
            break;
        case 3:
            cout << "Network connectivity problem" << endl;
            cout << "Resetting network module..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            cout << "Network module reset. Please reconnect the device to your network." << endl;
            break;
    }

    cout << "IoT device repair simulation complete." << endl;
    pause();
}

void applyAugmentedRealityRepair() {
    clearScreen();
    cout << "\n--- Augmented Reality Repair Guide ---" << endl;
    cout << "Please put on your AR glasses and scan the QR code on your device." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    cout << "AR guide loaded. Follow these steps:" << endl;
    cout << "1. Locate the screws highlighted in red" << endl;
    cout << "2. Use the virtual screwdriver to remove them" << endl;
    cout << "3. Gently lift the panel as shown by the green arrows" << endl;
    cout << "4. Identify the component flashing in blue" << endl;
    cout << "5. Follow on-screen instructions to replace or repair the component" << endl;

    cout << "\nAR guide complete. Did this help you repair your device? (1 for Yes, 0 for No): ";
    int success;
    cin >> success;

    if (success) {
        cout << "Great! Your device should now be repaired." << endl;
    } else {
        cout << "We're sorry the AR guide couldn't fully assist you." << endl;
        cout << "Would you like to schedule an in-person repair? (1 for Yes, 0 for No): ";
        int schedule;
        cin >> schedule;
        if (schedule) {
            submitRepairRequest();
        }
    }
    pause();
}

void offerSubscriptionService() {
    clearScreen();
    cout << "\n--- Repair Subscription Service ---" << endl;
    cout << "Subscribe to our repair service and enjoy these benefits:" << endl;
    cout << "1. Priority repair queue" << endl;
    cout << "2. 20% discount on all repairs" << endl;
    cout << "3. Free pickup and delivery" << endl;
    cout << "4. Monthly device health check" << endl;

    cout << "\nSubscription plans:" << endl;
    cout << "1. Basic (1 device) - P500/month" << endl;
    cout << "2. Family (3 devices) - P1000/month" << endl;
    cout << "3. Premium (5 devices) - P1500/month" << endl;

    cout << "\nWould you like to subscribe? (1 for Yes, 0 for No): ";
    int subscribe;
    cin >> subscribe;

    if (subscribe) {
        cout << "Enter plan number: ";
        int plan;
        cin >> plan;
        if (plan >= 1 && plan <= 3) {
            cout << "Thank you for subscribing to our repair service!" << endl;
            cout << "Your subscription will be active from today." << endl;
        } else {
            cout << "Invalid plan selection." << endl;
        }
    } else {
        cout << "Thank you for your interest. Feel free to subscribe anytime!" << endl;
    }
    pause();
}

void provideRepairEstimate() {
    clearScreen();
    cout << "\n--- Repair Cost Estimator ---" << endl;
    
    string itemName;
    cout << "Enter the name of the item to repair: ";
    cin.ignore();
    getline(cin, itemName);

    cout << "Select the type of damage:" << endl;
    cout << "1. Minor (e.g., small cracks, loose parts)" << endl;
    cout << "2. Moderate (e.g., screen replacement, battery issues)" << endl;
    cout << "3. Major (e.g., motherboard repair, water damage)" << endl;
    int damageType;
    cin >> damageType;

    int baseCost;
    switch (damageType) {
        case 1: baseCost = 500; break;
        case 2: baseCost = 1500; break;
        case 3: baseCost = 3000; break;
        default: 
            cout << "Invalid selection. Unable to provide estimate." << endl;
            pause();
            return;
    }

    cout << "Is the item still under warranty? (1 for Yes, 0 for No): ";
    int underWarranty;
    cin >> underWarranty;

    float finalCost = baseCost;
    if (underWarranty) {
        finalCost *= 0.5; // 50% discount if under warranty
    }

    cout << "\nEstimated Repair Cost for " << itemName << ":" << endl;
    cout << "Base Cost: P" << baseCost << endl;
    if (underWarranty) {
        cout << "Warranty Discount: 50%" << endl;
    }
    cout << "Final Estimated Cost: P" << finalCost << endl;
    cout << "\nNote: This is an estimate. Actual cost may vary after inspection." << endl;

    pause();
}

void offerRemoteDiagnostics() {
    clearScreen();
    cout << "\n--- Remote Diagnostics Service ---" << endl;

    cout << "This service allows us to diagnose your device remotely." << endl;
    cout << "Please ensure your device is connected to the internet." << endl;
    cout << "\nEnter the type of device:" << endl;
    cout << "1. Smartphone" << endl;
    cout << "2. Laptop" << endl;
    cout << "3. Smart Home Device" << endl;
    cout << "4. Other" << endl;

    int deviceType;
    cin >> deviceType;

    cout << "Initiating remote connection..." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    cout << "Running system checks..." << endl;
    this_thread::sleep_for(chrono::seconds(5));

    // Simulate diagnostic results
    vector<string> issues;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 3);
    int issueCount = dis(gen);

    for (int i = 0; i < issueCount; ++i) {
        switch (dis(gen)) {
            case 0: issues.push_back("Software update required"); break;
            case 1: issues.push_back("Battery health degraded"); break;
            case 2: issues.push_back("Storage space low"); break;
            case 3: issues.push_back("Network connectivity issues"); break;
        }
    }

    cout << "\nDiagnostic Results:" << endl;
    if (issues.empty()) {
        cout << "No issues detected. Your device appears to be functioning normally." << endl;
    } else {
        for (const auto& issue : issues) {
            cout << "- " << issue << endl;
        }
        cout << "\nWould you like to schedule a repair for these issues? (1 for Yes, 0 for No): ";
        int scheduleRepair;
        cin >> scheduleRepair;
        if (scheduleRepair) {
            submitRepairRequest();
        }
    }

    pause();
}

void gamifyLoyaltyProgram(User& currentUser) {
    clearScreen();
    cout << "\n--- Gamified Loyalty Program ---" << endl;

    cout << "Welcome to our Repair Master Challenge!" << endl;
    cout << "Current Points: " << currentUser.loyaltyPoints << endl;

    cout << "\nDaily Repair Quiz:" 

 << endl;
    vector<pair<string, string>> questions = {
        {"What is the most common cause of smartphone screen damage?", "Dropping the device"},
        {"Which component is often responsible for a laptop not turning on?", "Power supply"},
        {"What's a quick fix for a device that won't charge?", "Clean the charging port"}
    };

    int correctAnswers = 0;
    for (const auto& q : questions) {
        cout << "\nQ: " << q.first << endl;
        string answer;
        cout << "Your answer: ";
        cin.ignore();
        getline(cin, answer);

        if (answer == q.second) {
            cout << "Correct! +10 points" << endl;
            currentUser.loyaltyPoints += 10;
            correctAnswers++;
        } else {
            cout << "Incorrect. The correct answer is: " << q.second << endl;
        }
    }

    cout << "\nQuiz Complete!" << endl;
    cout << "You got " << correctAnswers << " out of " << questions.size() << " correct." << endl;
    cout << "New Total Points: " << currentUser.loyaltyPoints << endl;

    // Check for level up
    int newLevel = currentUser.loyaltyPoints / 100; // Level up every 100 points
    cout << "\nYour Repair Master Level: " << newLevel << endl;

    if (newLevel > 0 && newLevel % 5 == 0) { // Special reward every 5 levels
        cout << "Congratulations! You've reached a milestone level!" << endl;
        cout << "You've earned a 20% discount on your next repair!" << endl;
    }

    pause();
}

void displayRepairQueue() {
    clearScreen();
    cout << "\n--- Current Repair Queue ---" << endl;
    if (repairQueue.empty()) {
        cout << "No repairs currently in the queue." << endl;
    } else {
        int count = 1;
        queue<RepairRequest> tempQueue = repairQueue;
        while (!tempQueue.empty()) {
            RepairRequest req = tempQueue.front();
            cout << count << ". " << req.itemName << " - " << req.issue << " (Complexity: " << req.complexity << ")" << endl;
            tempQueue.pop();
            count++;
        }
    }
    pause();
}

void assignRepairTechnician() {
    if (repairQueue.empty()) {
        cout << "No repairs in the queue to assign." << endl;
        return;
    }

    RepairRequest req = repairQueue.front();
    repairQueue.pop();

    vector<pair<string, int>> availableTechnicians;
    for (const auto& user : users) {
        if (user.second.repairExpertise > 0) {
            availableTechnicians.push_back({user.first, user.second.repairExpertise});
        }
    }

    if (availableTechnicians.empty()) {
        cout << "No technicians available. Repair request remains unassigned." << endl;
        repairQueue.push(req);
        return;
    }

    // Assign to the technician with the closest expertise level
    sort(availableTechnicians.begin(), availableTechnicians.end(),
         [&req](const pair<string, int>& a, const pair<string, int>& b) {
             return abs(a.second - req.complexity) < abs(b.second - req.complexity);
         });

    req.assignedTechnician = availableTechnicians[0].first;
    req.status = "Assigned";
    repairRequests.push_back(req);

    cout << "Repair for " << req.itemName << " assigned to " << req.assignedTechnician << endl;
}

void submit3DPrintJob() {
    PrintJob job;
    cout << "Enter 3D model name: ";
    cin.ignore();
    getline(cin, job.modelName);
    cout << "Enter material (PLA/ABS/PETG): ";
    cin >> job.material;
    cout << "Enter volume in cm³: ";
    cin >> job.volume;
    job.status = "Queued";

    printJobs.push_back(job);
    cout << "3D print job submitted successfully!" << endl;
    pause();
}

void update3DPrintStatus() {
    if (printJobs.empty()) {
        cout << "No active 3D print jobs." << endl;
        return;
    }

    cout << "Current 3D Print Jobs:" << endl;
    for (size_t i = 0; i < printJobs.size(); ++i) {
        cout << i + 1 << ". " << printJobs[i].modelName << " - " << printJobs[i].status << endl;
    }

    int choice;
    cout << "Enter job number to update (0 to cancel): ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(printJobs.size())) {
        string newStatus;
        cout << "Enter new status (Printing/Completed/Failed): ";
        cin >> newStatus;
        printJobs[choice - 1].status = newStatus;
        cout << "Status updated successfully!" << endl;
    } else if (choice != 0) {
        cout << "Invalid choice!" << endl;
    }
    pause();
}

void displayRecyclingStats() {
    clearScreen();
    cout << "\n--- Recycling Statistics ---" << endl;

    if (recyclingRecords.empty()) {
        cout << "No recycling records available." << endl;
    } else {
        float totalWeight = 0;
        map<string, float> itemWeights;

        for (const auto& record : recyclingRecords) {
            totalWeight += record.weight;
            itemWeights[record.itemName] += record.weight;
        }

        cout << "Total items recycled: " << recyclingRecords.size() << endl;
        cout << "Total weight recycled: " << totalWeight << " kg" << endl;
        cout << "\nBreakdown by item:" << endl;

        for (const auto& item : itemWeights) {
            cout << item.first << ": " << item.second << " kg" << endl;
        }
    }
    pause();
}

void manageInventoryAlerts() {
    clearScreen();
    cout << "\n--- Inventory Alerts Management ---" << endl;

    cout << "Current low stock alerts:" << endl;
    bool hasLowStock = false;
    for (const auto& item : inventory) {
        if (item.stock < 5) { // Assuming 5 is the threshold for low stock
            cout << "- " << item.name << " (Current stock: " << item.stock << ")" << endl;
            hasLowStock = true;
        }
    }

    if (!hasLowStock) {
        cout << "No items are currently low in stock." << endl;
    } else {
        cout << "\nWould you like to reorder low stock items? (1 for Yes, 0 for No): ";
        int reorder;
        cin >> reorder;

        if (reorder) {
            for (auto& item : inventory) {
                if (item.stock < 5) {
                    int reorderAmount = 10 - item.stock; // Reorder to bring stock up to 10
                    item.stock += reorderAmount;
                    cout << "Reordered " << reorderAmount << " units of " << item.name << endl;
                }
            }
            cout << "Reorder complete. Stock levels have been updated." << endl;
        }
    }

    pause();
}

void implementBlockchainWarranty() {
    clearScreen();
    cout << "\n--- Blockchain Warranty System ---" << endl;

    string itemSerial;
    cout << "Enter the item's serial number: ";
    cin.ignore();
    getline(cin, itemSerial);

    // Simulate blockchain verification
    cout << "Verifying warranty on the blockchain..." << endl;
    this_thread::sleep_for(chrono::seconds(3));

    // Generate a random warranty status for demonstration
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);
    int warrantyStatus = dis(gen);

    cout << "Blockchain verification complete." << endl;
    cout << "Warranty status for item " << itemSerial << ": ";

    switch (warrantyStatus) {
        case 1:
            cout << "Active - Valid until " << (time(nullptr) + 31536000) << endl; // 1 year from now
            break;
        case 2:
            cout << "Expired - Warranty ended on " << (time(nullptr) - 2592000) << endl; // 1 month ago
            break;
        case 3:
            cout << "Not found - Please register your product" << endl;
            break;
    }

    if (warrantyStatus == 3) {
        cout << "Would you like to register this product for warranty? (1 for Yes, 0 for No): ";
        int registerWarranty;
        cin >> registerWarranty;

        if (registerWarranty) {
            cout << "Registering warranty on the blockchain..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Warranty registered successfully. Valid for 1 year from today." << endl;
        }
    }

    pause();
}

// ... (rest of the code remains unchanged)
