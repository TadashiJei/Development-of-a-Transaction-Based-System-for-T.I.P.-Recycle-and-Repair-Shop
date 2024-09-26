# Development of a Transaction-Based System for T.I.P. Recycle and Repair Shop

The **T.I.P. Recycle and Repair Shop** is an eco-friendly service that allows students and staff to donate or repair used items like electronics, gadgets, and furniture. This transaction-based system will manage the inventory of donated items, repair services, and sales of refurbished items.

# Task Management System Using C++

**Course:** ITE-001  
**Program:** BS in Computer Science  
**Institution:** Technological Institute of the Philippines  
**Year Level:** First Year
**Group Name:** [@marsharctechnologies](https://github.com/marsharctechnologies)

## Overview
The **T.I.P. Recycle and Repair Shop Transaction System** is a console-based C++ application that simulates a basic retail and repair service shop. The program allows users to browse different categories of items, make purchases, and submit repair requests for damaged items. This project showcases fundamental inventory management, payment handling, and user interaction in C++.

## Features
1. **Browse and Buy Items**
   - Three categories of items:
     - **Electronics**: Smartphones, Laptops, and Tablets with conditions (Fully Functional, Minor Repairs Needed, Major Repairs Needed).
     - **Furniture**: Various types of chairs, tables, and shelves.
     - **Gadgets**: Different types of headphones, speakers, and power banks.
   - Each item displays its name, condition, price, and stock available.

2. **Purchase Process**
   - Users can select an item to buy.
   - Payment handling ensures sufficient funds are available, with change given if applicable.
   - A receipt is generated upon successful purchase.

3. **Submit Repair Requests**
   - Users can submit repair requests by entering the item name and describing the issue.
   - Requests are stored and can be viewed later.

4. **View Repair Requests**
   - Users can view all submitted repair requests, if any.

5. **User-Friendly Interface**
   - A clear console menu guides users through their options.

## Getting Started
### Prerequisites
- A C++ compiler (e.g., g++, clang++).
- An IDE or text editor (e.g., Visual Studio Code, Code::Blocks).

### Compilation
To compile the program, use the following command in your terminal:

```bash
g++ -o tip_shop tip_shop.cpp
```
### Execution
To run the program, execute the following command:
```bash
./tip_shop
```

### Usage
** Upon starting the program, a welcome message and main menu will be displayed. Choose an option by entering the corresponding number: **

- Buy Electronics
- Buy Furniture
- Buy Gadgets
- Submit Repair Request
- View Repair Requests
- Exit
- Follow the prompts to make purchases or submit requests.
