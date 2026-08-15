#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Stores information about a hotel room
struct Room {
    int id;
    string type;
    string status;
};

// Node used to represent each hotel floor in a Binary Search Tree
struct TreeNode {
    int floorNumber;
    vector<Room> rooms;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int floor)
        : floorNumber(floor), left(nullptr), right(nullptr) {}
};

// Stores a customer's booking request
struct BookingRequest {
    string customerName;
    string roomType;
    int nights;
    bool highPriority;
};

// Stores information about a successfully processed booking
struct BookingRecord {
    string customerName;
    string roomType;
    int nights;
    int roomId;
};

class HotelManagementSystem {
private:
    TreeNode* root;

    // Queue for normal booking requests
    queue<BookingRequest> regularQueue;

    // Queue for priority booking requests
    queue<BookingRequest> highPriorityQueue;

    // Stack stores booking history
    stack<BookingRecord> bookingHistory;

public:
    // Constructor
    HotelManagementSystem(int floors, int roomsPerFloor)
        : root(nullptr) {
        initializeHotel(floors, roomsPerFloor);
    }

    // Destructor
    ~HotelManagementSystem() {
        deleteTree(root);
    }

    // Creates hotel floors and rooms
    void initializeHotel(int floors, int roomsPerFloor) {
        for (int i = 1; i <= floors; i++) {
            root = insertFloor(root, i, roomsPerFloor);
        }
    }

    // Inserts a floor into the Binary Search Tree
    TreeNode* insertFloor(
        TreeNode* node,
        int floor,
        int roomsPerFloor
    ) {
        if (!node) {
            TreeNode* newFloor = new TreeNode(floor);

            for (int j = 1; j <= roomsPerFloor; j++) {

                string type =
                    (j % 3 == 0) ? "Single" :
                    (j % 3 == 1) ? "Double" :
                                   "Suite";

                int roomId =
                    (floor - 1) * roomsPerFloor + j;

                newFloor->rooms.push_back(
                    {roomId, type, "Ready"}
                );
            }

            return newFloor;
        }

        if (floor < node->floorNumber) {
            node->left =
                insertFloor(
                    node->left,
                    floor,
                    roomsPerFloor
                );
        }
        else {
            node->right =
                insertFloor(
                    node->right,
                    floor,
                    roomsPerFloor
                );
        }

        return node;
    }

    // Displays all hotel rooms
    void displayRooms() const {
        cout << "\nHotel Room Details:\n";
        inOrderTraversal(root);
    }

    // Adds a booking request
    void addBookingRequest(
        const string& customerName,
        const string& roomType,
        int nights,
        bool highPriority
    ) {

        BookingRequest request = {
            customerName,
            roomType,
            nights,
            highPriority
        };

        if (highPriority) {
            highPriorityQueue.push(request);
        }
        else {
            regularQueue.push(request);
        }

        cout << "Booking request added.\n";
    }

    // Processes booking requests
    void processBookingRequests() {
        int processedRequests = 0;

        // Process priority bookings first
        while (
            !highPriorityQueue.empty()
            && processedRequests < 10
        ) {
            processRequest(
                highPriorityQueue.front()
            );

            highPriorityQueue.pop();
            processedRequests++;
        }

        // Process normal bookings afterwards
        while (
            !regularQueue.empty()
            && processedRequests < 10
        ) {
            processRequest(
                regularQueue.front()
            );

            regularQueue.pop();
            processedRequests++;
        }

        if (processedRequests == 0) {
            cout
                << "No booking requests to process.\n";
        }
    }

    // Cancels the latest booking
    void cancelMostRecentBooking() {

        if (bookingHistory.empty()) {
            cout << "No bookings to cancel.\n";
            return;
        }

        BookingRecord latest =
            bookingHistory.top();

        if (markRoomReady(
                root,
                latest.roomId
            )) {

            cout
                << "Canceled booking for "
                << latest.customerName
                << " (Room "
                << latest.roomId
                << ").\n";

            bookingHistory.pop();
        }
        else {
            cout
                << "Unable to find the booked room.\n";
        }
    }

    // Displays booking history
    void displayBookingHistory() const {

        stack<BookingRecord> temp =
            bookingHistory;

        cout << "\nBooking History:\n";

        if (temp.empty()) {
            cout
                << "No bookings made yet.\n";
            return;
        }

        while (!temp.empty()) {

            const BookingRecord& record =
                temp.top();

            cout
                << "Customer: "
                << record.customerName
                << ", Room ID: "
                << record.roomId
                << ", Room Type: "
                << record.roomType
                << ", Nights: "
                << record.nights
                << '\n';

            temp.pop();
        }
    }

private:

    // In-order traversal of hotel floors
    void inOrderTraversal(
        TreeNode* node
    ) const {

        if (!node)
            return;

        inOrderTraversal(node->left);

        cout
            << "Floor "
            << node->floorNumber
            << ":\n";

        for (const auto& room :
             node->rooms) {

            cout
                << "  Room ID: "
                << room.id
                << ", Type: "
                << room.type
                << ", Status: "
                << room.status
                << '\n';
        }

        inOrderTraversal(node->right);
    }

    // Processes one booking request
    void processRequest(
        const BookingRequest& request
    ) {

        int assignedRoomId =
            assignRoom(root, request);

        if (assignedRoomId != -1) {

            BookingRecord record = {
                request.customerName,
                request.roomType,
                request.nights,
                assignedRoomId
            };

            bookingHistory.push(record);

            cout
                << "Processed: Customer: "
                << request.customerName
                << ", Room ID: "
                << assignedRoomId
                << ", Room Type: "
                << request.roomType
                << ", Nights: "
                << request.nights
                << '\n';
        }
        else {
            cout
                << "No available "
                << request.roomType
                << " room for "
                << request.customerName
                << ".\n";
        }
    }

    // Searches for an available room
    int assignRoom(
        TreeNode* node,
        const BookingRequest& request
    ) {

        if (!node)
            return -1;

        for (auto& room :
             node->rooms) {

            if (
                room.type ==
                    request.roomType
                &&
                room.status ==
                    "Ready"
            ) {

                room.status = "Booked";

                return room.id;
            }
        }

        int roomId =
            assignRoom(
                node->left,
                request
            );

        if (roomId != -1)
            return roomId;

        return assignRoom(
            node->right,
            request
        );
    }

    // Changes a canceled room back to Ready
    bool markRoomReady(
        TreeNode* node,
        int roomId
    ) {

        if (!node)
            return false;

        for (auto& room :
             node->rooms) {

            if (room.id == roomId) {
                room.status = "Ready";
                return true;
            }
        }

        return
            markRoomReady(
                node->left,
                roomId
            )
            ||
            markRoomReady(
                node->right,
                roomId
            );
    }

    // Deletes dynamically created tree nodes
    void deleteTree(
        TreeNode* node
    ) {

        if (!node)
            return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }
};

int main() {

    cout
        << "Welcome to the "
        << "Hotel Management System!\n";

    int floors;
    int roomsPerFloor;

    cout
        << "Enter the number of floors: ";

    cin >> floors;

    cout
        << "Enter the number of "
        << "rooms per floor: ";

    cin >> roomsPerFloor;

    if (
        floors <= 0
        ||
        roomsPerFloor <= 0
    ) {
        cout
            << "Floors and rooms per floor "
            << "must be greater than 0.\n";

        return 0;
    }

    HotelManagementSystem hotel(
        floors,
        roomsPerFloor
    );

    while (true) {

        cout << "\nMenu:\n";
        cout << "1. Display Rooms\n";
        cout << "2. Add Booking Request\n";
        cout << "3. Process Booking Requests\n";
        cout << "4. Cancel Most Recent Booking\n";
        cout << "5. Display Booking History\n";
        cout << "6. Exit\n";

        int choice;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {

            hotel.displayRooms();
        }

        else if (choice == 2) {

            string name;
            string roomType;
            string priorityInput;
            int nights;

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout
                << "Enter customer name: ";

            getline(cin, name);

            cout
                << "Enter room type "
                << "(Single, Double, Suite): ";

            getline(cin, roomType);

            cout
                << "Enter number of nights: ";

            cin >> nights;

            if (nights <= 0) {

                cout
                    << "Number of nights must "
                    << "be greater than 0.\n";

                continue;
            }

            cout
                << "Is this a high-priority "
                << "booking? (yes/no): ";

            cin >> priorityInput;

            bool highPriority =
                (
                    priorityInput == "yes"
                    ||
                    priorityInput == "Yes"
                    ||
                    priorityInput == "YES"
                );

            hotel.addBookingRequest(
                name,
                roomType,
                nights,
                highPriority
            );
        }

        else if (choice == 3) {

            cout
                << "\nProcessing "
                << "Booking Requests...\n";

            hotel.processBookingRequests();
        }

        else if (choice == 4) {

            hotel.cancelMostRecentBooking();
        }

        else if (choice == 5) {

            hotel.displayBookingHistory();
        }

        else if (choice == 6) {

            cout
                << "Exiting the system. "
                << "Goodbye!\n";

            break;
        }

        else {

            cout
                << "Invalid choice. "
                << "Please try again.\n";
        }
    }

    return 0;
}
