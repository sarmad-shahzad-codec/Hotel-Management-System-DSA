# Hotel Management System Using Data Structures in C++

A console-based **Hotel Management System** developed in **C++** as a Data Structures and Algorithms (DSA) project.

The project demonstrates how different data structures such as **Binary Search Trees, Queues, Stacks, and Vectors** can be applied to solve a practical hotel room and booking management problem.

## Overview

The Hotel Management System allows users to create a hotel with multiple floors and rooms, view room information, add customer booking requests, prioritize urgent bookings, assign available rooms, cancel the most recent booking, and view booking history.

The main purpose of this project is to demonstrate the practical implementation of important **Data Structures and Algorithms concepts in C++**.

## Features

- Create a hotel with a custom number of floors and rooms.
- Automatically generate Single, Double, and Suite rooms.
- Display all hotel floors and room information.
- Add regular booking requests.
- Add high-priority booking requests.
- Process high-priority bookings before regular bookings.
- Automatically search for an available room of the requested type.
- Update room status from `Ready` to `Booked`.
- Maintain booking history.
- Cancel the most recently processed booking.
- Automatically change the canceled room back to `Ready`.
- Validate basic user input.
- Support customer names containing spaces.
- Menu-driven console interface.

## Data Structures Used

### 1. Binary Search Tree

A **Binary Search Tree (BST)** is used to represent the floors of the hotel.

Each tree node represents one floor and contains:

- Floor number
- Collection of rooms
- Pointer to the left child
- Pointer to the right child

An in-order traversal is used to display the floors and their rooms in order.

### 2. Vector

A `vector<Room>` is stored inside every floor node.

The vector allows each floor to contain multiple rooms dynamically.

Each room contains:

- Room ID
- Room type
- Room status

### 3. Queue

Queues are used for booking requests.

Two queues are maintained:

- `regularQueue`
- `highPriorityQueue`

The system processes high-priority booking requests before regular booking requests.

Because a queue follows the **First In, First Out (FIFO)** principle, requests within the same priority level are processed in the order in which they were received.

### 4. Stack

A stack is used to maintain successfully processed bookings.

The stack follows the **Last In, First Out (LIFO)** principle.

This makes it suitable for the cancellation feature because the most recently processed booking can be accessed and canceled first.

### 5. Recursion

Recursion is used for several tree operations, including:

- Inserting hotel floors
- Traversing the Binary Search Tree
- Searching for an available room
- Finding a room during cancellation
- Deleting dynamically allocated tree nodes

## Object-Oriented Programming Concepts

The project also uses Object-Oriented Programming principles.

The main functionality of the system is organized inside the:

`HotelManagementSystem`

class.

The class handles:

- Hotel initialization
- Floor management
- Room management
- Booking requests
- Booking processing
- Booking history
- Booking cancellation

The internal data structures are kept private and accessed through public member functions.

## Project Structures

### Room

Stores information about an individual hotel room.

```cpp
struct Room {
    int id;
    string type;
    string status;
};
```

### TreeNode

Represents a hotel floor inside the Binary Search Tree.

```cpp
struct TreeNode {
    int floorNumber;
    vector<Room> rooms;
    TreeNode* left;
    TreeNode* right;
};
```

### BookingRequest

Stores an incoming customer booking request.

```cpp
struct BookingRequest {
    string customerName;
    string roomType;
    int nights;
    bool highPriority;
};
```

### BookingRecord

Stores information about a successfully processed booking.

```cpp
struct BookingRecord {
    string customerName;
    string roomType;
    int nights;
    int roomId;
};
```

## How the System Works

When the program starts, the user enters the number of hotel floors and the number of rooms per floor.

The program then creates the hotel structure using a Binary Search Tree.

Rooms are automatically assigned one of the following types:

- Single
- Double
- Suite

All rooms initially have the status:

`Ready`

When a customer submits a booking request, the request is stored in either the regular booking queue or the high-priority booking queue.

When booking requests are processed, the system first checks the high-priority queue.

The Binary Search Tree is then searched for an available room matching the requested room type.

When a room is found, its status changes from:

`Ready`

to:

`Booked`

The successful booking is then stored in the booking-history stack.

If the user cancels the most recent booking, the latest booking is removed from the stack and its room status is changed back to:

`Ready`

## Menu Options

The program provides the following menu:

```text
1. Display Rooms
2. Add Booking Request
3. Process Booking Requests
4. Cancel Most Recent Booking
5. Display Booking History
6. Exit
```

## Technologies Used

- C++
- Standard Template Library (STL)
- Binary Search Tree
- Queue
- Stack
- Vector
- Recursion
- Object-Oriented Programming
- Dynamic Memory Management

## Requirements

To run this project, you need:

- A C++ compiler supporting C++11 or later
- Visual Studio Code, Code::Blocks, Dev-C++, Visual Studio, or another C++ IDE/compiler

The project has also been tested using the **C++17** standard.

## How to Run

Clone the repository:

```bash
git clone https://github.com/your-username/Hotel-Management-System-DSA.git
```

Move into the project directory:

```bash
cd Hotel-Management-System-DSA
```

Compile the program using g++:

```bash
g++ -std=c++17 main.cpp -o hotel
```

Run the program:

### Windows

```bash
hotel.exe
```

### Linux/macOS

```bash
./hotel
```

## Example Workflow

A typical workflow is:

```text
Enter the number of floors: 3
Enter the number of rooms per floor: 6

Menu:
1. Display Rooms
2. Add Booking Request
3. Process Booking Requests
4. Cancel Most Recent Booking
5. Display Booking History
6. Exit
```

A customer can submit a request such as:

```text
Customer Name: Ali Khan
Room Type: Single
Number of Nights: 3
High Priority: yes
```

After processing, the system assigns an available Single room and changes its status to `Booked`.

## Learning Outcomes

This project helped demonstrate the practical application of several fundamental Computer Science concepts, particularly:

- Selecting appropriate data structures for different problems
- Tree creation and traversal
- FIFO processing using queues
- LIFO processing using stacks
- Dynamic data storage using vectors
- Recursive algorithms
- Dynamic memory management
- Structuring a program using Object-Oriented Programming
- Building a menu-driven C++ console application

## Possible Future Improvements

The project can be extended by adding:

- Customer login and registration
- Check-in and check-out functionality
- Booking dates
- Room pricing
- Total bill calculation
- Customer records
- File-based or database storage
- Search booking functionality
- Room availability filters
- Admin authentication
- Graphical User Interface
- More advanced priority management
- Balanced Binary Search Tree implementation

## Project Purpose

This project was developed as a **Data Structures and Algorithms academic project** to demonstrate how theoretical DSA concepts can be applied to a real-world management system.

## Author

Developed as part of a **Data Structures and Algorithms (DSA)** project using C++.

---

If you found this project useful, consider giving the repository a ⭐.
