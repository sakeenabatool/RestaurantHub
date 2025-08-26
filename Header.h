#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <algorithm>
#include <queue>
using namespace std;

void setTextColor(const string& color)
{
    if (color == "black")
    {
        cout << "\033[30m"; // Black
    }
    else if (color == "red")
    {
        cout << "\033[31m"; // Red
    }
    else if (color == "green")
    {
        cout << "\033[32m"; // Green
    }
    else if (color == "yellow")
    {
        cout << "\033[33m"; // Yellow
    }
    else if (color == "blue")
    {
        cout << "\033[34m"; // Blue
    }
    else if (color == "magenta")
    {
        cout << "\033[35m"; // Magenta
    }
    else if (color == "cyan")
    {
        cout << "\033[36m"; // Cyan
    }
    else if (color == "white")
    {
        cout << "\033[37m"; // White
    }
    else if (color == "gray")
    {
        cout << "\033[90m"; // Gray (Bright Black)
    }
    else if (color == "bright_red")
    {
        cout << "\033[91m"; // Bright Red
    }
    else if (color == "bright_green")
    {
        cout << "\033[92m"; // Bright Green
    }
    else if (color == "bright_yellow")
    {
        cout << "\033[93m"; // Bright Yellow
    }
    else if (color == "bright_blue")
    {
        cout << "\033[94m"; // Bright Blue
    }
    else if (color == "bright_magenta")
    {
        cout << "\033[95m"; // Bright Magenta
    }
    else if (color == "bright_cyan")
    {
        cout << "\033[96m"; // Bright Cyan
    }
    else if (color == "bright_white")
    {
        cout << "\033[97m"; // Bright White
    }
    else if (color == "reset")
    {
        cout << "\033[0m"; // Reset to default color
    }
    else
    {
        cout << "\033[0m"; // Reset for unknown color
    }
}
void setBackgroundColor(const string& color)
{
    if (color == "black")
    {
        cout << "\033[40m"; // Black Background
    }
    else if (color == "red")
    {
        cout << "\033[41m"; // Red Background
    }
    else if (color == "green")
    {
        cout << "\033[42m"; // Green Background
    }
    else if (color == "yellow")
    {
        cout << "\033[43m"; // Yellow Background
    }
    else if (color == "blue")
    {
        cout << "\033[44m"; // Blue Background
    }
    else if (color == "magenta")
    {
        cout << "\033[45m"; // Magenta Background
    }
    else if (color == "cyan")
    {
        cout << "\033[46m"; // Cyan Background
    }
    else if (color == "white")
    {
        cout << "\033[47m"; // White Background
    }
    else if (color == "gray")
    {
        cout << "\033[48m"; // Gray (Bright Black) Background
    }
    else if (color == "bright_red")
    {
        cout << "\033[49m"; // Bright Red Background
    }
    else if (color == "bright_green")
    {
        cout << "\033[50m"; // Bright Green Background
    }
    else if (color == "bright_yellow")
    {
        cout << "\033[51m"; // Bright Yellow Background
    }
    else if (color == "bright_blue")
    {
        cout << "\033[52m"; // Bright Blue Background
    }
    else if (color == "bright_magenta")
    {
        cout << "\033[53m"; // Bright Magenta Background
    }
    else if (color == "bright_cyan")
    {
        cout << "\033[54m"; // Bright Cyan Background
    }
    else if (color == "bright_white")
    {
        cout << "\033[55m"; // Bright White Background
    }
    else
    {
        cout << "\033[0m"; // Reset for unknown color
    }
}
void resetTextColor()
{
    cout << "\033[0m"; // Reset to default
}


// === Utility for ID generation ===
int generateId() {
    static int currentId = 10000;
    return currentId++;
}

struct Promotion {
    int id;           // Unique 5-digit ID
    string name;      // Promotion name
    int discount;     // Discount percentage (0-100)
    int limit;        // Number of orders the promotion can be applied to

    Promotion(int id, const string& name, int discount, int limit)
        : id(id), name(name), discount(discount), limit(limit) {
    }
};

const int MAX_PROMOTIONS = 50;

class PromotionStack {
private:
    Promotion* stack[MAX_PROMOTIONS]; // Manual stack to store promotions
    int top;                          // Index of the top element in the stack

    int generatePromotionId() {
        static int currentId = 20000; // Start promotion IDs from 20000
        return currentId++;
    }

public:
    PromotionStack() : top(-1) {}

    // Add a promotion
    void addPromotion(const string& name, int discount, int limit) {
        if (top == MAX_PROMOTIONS - 1) {
            cout << "Promotion stack is full! Cannot add more promotions.\n";
            return;
        }
        stack[++top] = new Promotion(generatePromotionId(), name, discount, limit);
        cout << "Promotion added successfully: " << name << " with ID " << stack[top]->id << ".\n";
    }

    // Apply a promotion to an order
    void applyPromotion(double& orderCost) {
        if (top == -1) {
            cout << "No promotions available. Full cost applied.\n";
            return;
        }

        Promotion* currentPromotion = stack[top];

        // Apply the discount
        double discountAmount = (currentPromotion->discount / 100.0) * orderCost;
        orderCost -= discountAmount;
        cout << "Applied promotion: " << currentPromotion->name
            << " (" << currentPromotion->discount << "% discount).\n";

        // Decrease the limit and pop the promotion if limit is reached
        currentPromotion->limit--;
        if (currentPromotion->limit == 0) {
            cout << "Promotion " << currentPromotion->name << " expired and removed from the stack.\n";
            delete stack[top--]; // Remove from stack and free memory
        }
    }

    // Display all promotions
    void displayPromotions() {
        if (top == -1) {
            cout << "No promotions available.\n";
            return;
        }

        cout << "Available Promotions:\n";
        cout << "ID    | Name            | Discount | Remaining Limit\n";
        cout << "-----------------------------------------------\n";

        for (int i = top; i >= 0; --i) {
            cout << stack[i]->id << " | " << stack[i]->name << " | "
                << stack[i]->discount << "% | " << stack[i]->limit << endl;
        }
    }
};


void promotionMenu(PromotionStack& promotions) {
    int choice;
    do {
        cout << "\nPromotion Management:\n";
        cout << "1. Add Promotion\n";
        cout << "2. View Promotions\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int discount, limit;
            cin.ignore();
            cout << "Enter promotion name: ";
            getline(cin, name);
            cout << "Enter discount percentage: ";
            cin >> discount;
            cout << "Enter order limit: ";
            cin >> limit;
            promotions.addPromotion(name, discount, limit);
            break;
        }
        case 2:
            promotions.displayPromotions();
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 0);
}






struct Review {
    int id; // Unique 5-digit ID
    int rating; // Rating from 1 to 5 stars
    string description; // Review details
    void* target; // Pointer to Restaurant or Dish (can be cast dynamically)

    Review(int id, int rating, const string& description, void* target)
        : id(id), rating(rating), description(description), target(target) {
    }
};

class ReviewNode {
public:
    Review* review;
    ReviewNode* next;

    ReviewNode(Review* review) : review(review), next(nullptr) {}
};

class ReviewQueue {
private:
    ReviewNode* goodFront;  // Front of the good reviews list
    ReviewNode* goodRear;   // Rear of the good reviews list

    ReviewNode* badFront;   // Front of the bad reviews list
    ReviewNode* badRear;    // Rear of the bad reviews list

    int generateReviewId() {
        static int currentId = 90000;
        return currentId++;
    }

public:
    ReviewQueue() : goodFront(nullptr), goodRear(nullptr), badFront(nullptr), badRear(nullptr) {}

    // Add a review
    void addReview(int rating, const string& description, void* target) {
        Review* newReview = new Review(generateReviewId(), rating, description, target);
        ReviewNode* newNode = new ReviewNode(newReview);

        if (rating >= 4) {  // Good review
            if (goodRear == nullptr) {
                goodFront = goodRear = newNode;
            }
            else {
                goodRear->next = newNode;
                goodRear = newNode;
            }
            cout << "Good review added successfully: " << newReview->id << "\n";
        }
        else if (rating <= 2) {  // Bad review
            if (badRear == nullptr) {
                badFront = badRear = newNode;
            }
            else {
                badRear->next = newNode;
                badRear = newNode;
            }
            cout << "Bad review added successfully: " << newReview->id << "\n";
        }
        else {
            delete newReview;  // Neutral reviews are not handled in the current design
        }
    }

    // Edit a review by ID
    void editReview(int id, int newRating, const string& newDescription) {
        // Search and edit good reviews
        ReviewNode* current = goodFront;
        while (current != nullptr) {
            if (current->review->id == id) {
                current->review->rating = newRating;
                current->review->description = newDescription;
                cout << "Good review updated successfully.\n";
                return;
            }
            current = current->next;
        }

        // Search and edit bad reviews
        current = badFront;
        while (current != nullptr) {
            if (current->review->id == id) {
                current->review->rating = newRating;
                current->review->description = newDescription;
                cout << "Bad review updated successfully.\n";
                return;
            }
            current = current->next;
        }

        cout << "Review with ID " << id << " not found.\n";
    }

    // Delete a review by ID
    void deleteReview(int id) {
        // Search and delete from good reviews
        ReviewNode* current = goodFront;
        ReviewNode* prev = nullptr;
        while (current != nullptr) {
            if (current->review->id == id) {
                if (prev == nullptr) {
                    goodFront = current->next;
                    if (goodFront == nullptr) goodRear = nullptr;  // Handle empty list
                }
                else {
                    prev->next = current->next;
                    if (current == goodRear) goodRear = prev;  // Handle rear update
                }
                delete current->review;  // Delete the review object
                delete current;          // Delete the node
                cout << "Good review deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        // Search and delete from bad reviews
        current = badFront;
        prev = nullptr;
        while (current != nullptr) {
            if (current->review->id == id) {
                if (prev == nullptr) {
                    badFront = current->next;
                    if (badFront == nullptr) badRear = nullptr;  // Handle empty list
                }
                else {
                    prev->next = current->next;
                    if (current == badRear) badRear = prev;  // Handle rear update
                }
                delete current->review;  // Delete the review object
                delete current;          // Delete the node
                cout << "Bad review deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Review with ID " << id << " not found.\n";
    }

    // Display top 5 reviews (Good or Bad)
    void displayTopReviews(bool good = true) {
        ReviewNode* current = good ? goodFront : badFront;
        int count = 0;

        if (current == nullptr) {
            cout << (good ? "No good reviews available.\n" : "No bad reviews available.\n");
            return;
        }

        cout << (good ? "Top 5 Good Reviews:\n" : "Top 5 Bad Reviews:\n");
        cout << "ID    | Rating | Description\n";
        cout << "----------------------------\n";

        while (current != nullptr && count < 5) {
            cout << current->review->id << " | "
                << current->review->rating << " | "
                << current->review->description << endl;
            current = current->next;
            count++;
        }
    }

    // Destructor to delete all nodes
    ~ReviewQueue() {
        ReviewNode* current;

        // Delete all good reviews
        current = goodFront;
        while (current != nullptr) {
            ReviewNode* temp = current;
            current = current->next;
            delete temp->review;
            delete temp;
        }

        // Delete all bad reviews
        current = badFront;
        while (current != nullptr) {
            ReviewNode* temp = current;
            current = current->next;
            delete temp->review;
            delete temp;
        }
    }
};

ReviewQueue reviews;

void reviewMenu() {
    int choice;
    do {
        cout << "\nReview Management:\n";
        cout << "1. Add Review\n";
        cout << "2. Edit Review\n";
        cout << "3. Delete Review\n";
        cout << "4. Display Good Reviews\n";
        cout << "5. Display Bad Reviews\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int rating;
            string description;
            cout << "Enter rating (1-5): ";
            cin >> rating;
            cin.ignore();
            cout << "Enter description: ";
            getline(cin, description);

            reviews.addReview(rating, description, nullptr);
            break;
        }
        case 2: {
            int id, rating;
            string description;
            cout << "Enter review ID to edit: ";
            cin >> id;
            cout << "Enter new rating (1-5): ";
            cin >> rating;
            cin.ignore();
            cout << "Enter new description: ";
            getline(cin, description);
            reviews.editReview(id, rating, description);
            break;
        }
        case 3: {
            int id;
            cout << "Enter review ID to delete: ";
            cin >> id;
            reviews.deleteReview(id);
            break;
        }
        case 4:
            reviews.displayTopReviews(true);
            break;
        case 5:
            reviews.displayTopReviews(false);
            break;
        case 0:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 0);
}


// === Dish Node (Binary Tree) ===
struct Dish {
    int id;
    string name;
    string type;
    double price;
    Dish* left;
    Dish* right;

    Dish(string dishName, string dishType, double dishPrice)
        : id(generateId()), name(dishName), type(dishType), price(dishPrice), left(nullptr), right(nullptr) {
    }
};

// Binary Tree for Menu
// === Menu Tree (Binary Search Tree) ===
class MenuTree {
private:
    Dish* root;

    // Adding dish to the tree based on its name (this part works)
    Dish* addDish(Dish* node, string name, string type, double price) {
        if (!node) return new Dish(name, type, price); // Create a new dish node

        // Compare dish names to decide where to insert the new dish
        if (name < node->name) {
            node->left = addDish(node->left, name, type, price);
        }
        else if (name > node->name) {
            node->right = addDish(node->right, name, type, price);
        }
        // If name == node->name, we do not add a duplicate, but you can handle this case if needed.
        return node;
    }



    // Inorder traversal of the tree to display dishes
    void displayInOrder(Dish* node) {
        if (!node) return;
        displayInOrder(node->left); // Traverse left subtree
        cout << setw(5) << node->id << " | " << node->name << " | " << node->type << " | $" << node->price << endl;
        displayInOrder(node->right); // Traverse right subtree
    }

    // Searching for a dish by ID
    Dish* findDishById(Dish* node, int id) {
        if (!node) return nullptr;
        if (node->id == id) return node;
        if (id < node->id)
            return findDishById(node->left, id);
        else
            return findDishById(node->right, id);
    }

public:
    MenuTree() : root(nullptr) {}

    // Add dish to the menu (root of tree)
    void addDish(string name, string type, double price) {
        root = addDish(root, name, type, price);
    }

    //edit dish
    void editDish(int id, string newName, string newType, double newPrice) {
        Dish* dish = getDishById(id);
        if (dish) {
            dish->name = newName;
            dish->type = newType;
            dish->price = newPrice;
            cout << "Dish updated successfully.\n";
        }
        else {
            cout << "Dish with ID " << id << " not found.\n";
        }
    }

    Dish* deleteDish(Dish* node, int id) {
        if (!node) return nullptr;

        if (id < node->id) {
            node->left = deleteDish(node->left, id);
        }
        else if (id > node->id) {
            node->right = deleteDish(node->right, id);
        }
        else {
            // Node to be deleted found
            if (!node->left) {
                Dish* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Dish* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children
            Dish* temp = findMin(node->right); // Find minimum in the right subtree
            node->id = temp->id;
            node->name = temp->name;
            node->type = temp->type;
            node->price = temp->price;
            node->right = deleteDish(node->right, temp->id);
        }
        return node;
    }

    Dish* findMin(Dish* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void deleteDishById(int id) {
        root = deleteDish(root, id);
        cout << "Dish deleted successfully (if found).\n";
    }

    // Display the menu
    void displayMenu() {
        cout << "Menu:\n";
        cout << "ID    | Name          | Type        | Price\n";
        cout << "--------------------------------------------\n";
        displayInOrder(root);
    }

    // Retrieve a dish by its unique ID
    Dish* getDishById(int id) {
        return findDishById(root, id);
    }
};

// === Restaurant Node (Linked List) ===
struct Restaurant {
    int id;
    string name;
    string type;
    MenuTree menu;
    Restaurant* next;

    Restaurant(string restaurantName, string restaurantType)
        : id(generateId()), name(restaurantName), type(restaurantType), next(nullptr) {
    }
};

// Linked List for Restaurants
class RestaurantList {
private:
    Restaurant* head;

public:
    RestaurantList() : head(nullptr) {}

    void addRestaurant(string name, string type) {
        Restaurant* newRestaurant = new Restaurant(name, type);
        if (!head) {
            head = newRestaurant;
        }
        else {
            Restaurant* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newRestaurant;
        }
        cout << "Restaurant added successfully: " << name << endl;
    }


    // Edit an existing restaurant's name and type by ID
    void editRestaurant(int id, string newName, string newType) {
        Restaurant* temp = head;
        while (temp) {
            if (temp->id == id) {
                temp->name = newName;
                temp->type = newType;
                cout << "Restaurant updated successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Restaurant with ID " << id << " not found.\n";
    }

    // Delete a restaurant by its ID
    void deleteRestaurant(int id) {
        if (!head) {
            cout << "No restaurants available.\n";
            return;
        }

        if (head->id == id) {
            Restaurant* temp = head;
            head = head->next;
            delete temp;
            cout << "Restaurant deleted successfully.\n";
            return;
        }

        Restaurant* temp = head;
        while (temp->next) {
            if (temp->next->id == id) {
                Restaurant* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                cout << "Restaurant deleted successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Restaurant with ID " << id << " not found.\n";
    }



    void displayRestaurants() {
        if (!head) {
            cout << "No restaurants available.\n";
            return;
        }

        Restaurant* temp = head;
        cout << "Restaurants:\n";
        cout << "ID    | Name          | Type          \n";
        cout << "--------------------------------------\n";
        while (temp) {
            cout << setw(5) << temp->id << " | " << setw(13) << temp->name << " | " << setw(13) << temp->type << endl;
            temp = temp->next;
        }
    }

    Restaurant* findRestaurantById(int id) {
        Restaurant* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }
};




// === Orders (Queue with Priority) ===
struct Order {
    int id;
    string type; // Premium, Express, Normal
    double totalCost;
    string location;
    int status; //1.pending 2.processed 3.delivered
    Order* next;

    Order(string orderType, double orderCost, string loc)
        : id(generateId()), type(orderType), totalCost(orderCost), location(loc), status(1), next(nullptr) {
    }


};

class OrderQueue {
private:
    Order* front;
    Order* rear;

public:
    OrderQueue() : front(nullptr), rear(nullptr) {}

    Order* getFront() {
        return front;
    }

    void enqueue(string type, double cost, string location) {
        double finalCost = cost;
        if (type == "Premium") finalCost += 200;
        else if (type == "Express") finalCost += 100;

        if (type == "Premium") finalCost += 500;
        else if (type == "Express") finalCost += cost * 0.1;

        Order* newOrder = new Order(type, finalCost, location);

        if (!front || type == "Premium" || (type == "Express" && front->type == "Normal")) {
            newOrder->next = front;
            front = newOrder;
            if (!rear) rear = newOrder;
        }
        else {
            Order* temp = front;
            while (temp->next && !(type == "Express" && temp->next->type == "Normal"))
                temp = temp->next;
            newOrder->next = temp->next;
            temp->next = newOrder;
            if (!newOrder->next) rear = newOrder;
        }

        cout << "Order added: Type - " << type << ", Cost - $" << finalCost << ", Destination - " << location << endl;
    }

    void dequeue() {
        if (!front) {
            cout << "No orders to process.\n";
            return;
        }
        Order* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    void processOrder() {
        if (!front) {
            cout << "No orders to process.\n";
            return;
        }

        Order* temp = front;

        // Iterate until we find an unprocessed order or reach the end
        while (temp && temp->status != 1) {
            temp = temp->next;
        }

        if (!temp) {
            // No unprocessed orders found
            cout << "All orders have already been processed.\n";
            return;
        }

        // Process the found order
        temp->status = 2; // Change status to 'processed'
        cout << "Processing order ID: " << temp->id
            << " with total cost: $" << temp->totalCost
            << ", Destination: " << temp->location << endl;
    }

    void displayOrders() {
        if (!front) {
            cout << "No pending orders.\n";
            return;
        }
        Order* temp = front;
        cout << "Pending Orders:\n";
        cout << "ID    | Type    | Total Cost\n";
        cout << "----------------------------\n";
        while (temp) {
            cout << setw(5) << temp->id << " | " << temp->type << " | $" << temp->totalCost << endl;
            temp = temp->next;
        }
    }
};


class Graph {
private:
    int numVertices;
    int** adjacencyMatrix; // Adjacency matrix representation
    string* locationNames; // Array to store location names

public:
    // Constructor
    Graph(int vertices) : numVertices(vertices) {
        adjacencyMatrix = new int* [numVertices];
        locationNames = new string[numVertices];

        // Initialize adjacency matrix with 0 (no edges)
        for (int i = 0; i < numVertices; ++i) {
            adjacencyMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                adjacencyMatrix[i][j] = 0; // Initialize with no edge (0)
            }
        }

        // Initialize location names
        locationNames[0] = "H8";   locationNames[1] = "G5";   locationNames[2] = "F10";
        locationNames[3] = "F11";  locationNames[4] = "G10";  locationNames[5] = "F12";
        locationNames[6] = "G9";   locationNames[7] = "H9";   locationNames[8] = "F9";
        locationNames[9] = "F5";   locationNames[10] = "F6";  locationNames[11] = "I12";
        locationNames[12] = "I15"; locationNames[13] = "I14"; locationNames[14] = "G6";
        locationNames[15] = "G8";  locationNames[16] = "I8";  locationNames[17] = "I16";
        locationNames[18] = "H10"; locationNames[19] = "I11"; locationNames[20] = "I10";
        locationNames[21] = "G12"; locationNames[22] = "I9";  locationNames[23] = "F8";
        locationNames[24] = "H11"; locationNames[25] = "G7"; locationNames[26] = "G11";
        locationNames[27] = "G14";
        // Now you can add the edges based on the given data
        addEdge("H8", "G5", 11);
        addEdge("F10", "F11", 6);
        addEdge("G10", "F12", 5);
        addEdge("G9", "H11", 7);
        addEdge("H9", "F9", 11);
        addEdge("F12", "F5", 2);
        addEdge("F6", "I12", 9);
        addEdge("I15", "F12", 14);
        addEdge("G5", "I14", 12);
        addEdge("F9", "G6", 15);
        addEdge("I15", "F9", 7);
        addEdge("G8", "G7", 2);
        addEdge("F12", "F6", 14);
        addEdge("H9", "I8", 3);
        addEdge("G10", "F11", 1);
        addEdge("I8", "I15", 2);
        addEdge("F9", "I16", 9);
        addEdge("H9", "I10", 3);
        addEdge("H8", "G11", 6);
        addEdge("H11", "G12", 4);
        addEdge("I9", "G12", 7);
        addEdge("I8", "G8", 10);
        addEdge("H10", "I8", 5);
        addEdge("G12", "I11", 12);
        addEdge("I10", "F5", 15);
        addEdge("F10", "G10", 13);
        addEdge("F6", "F12", 1);
        addEdge("I14", "H11", 2);
        addEdge("G11", "F10", 5);
        addEdge("I10", "I16", 14);
        addEdge("F10", "F6", 3);
        addEdge("F12", "F8", 6);
        addEdge("F8", "F6", 7);
        addEdge("G9", "F11", 11);
        addEdge("F6", "H9", 12);
        addEdge("F8", "G9", 4);
        addEdge("F12", "H11", 3);
        addEdge("H11", "I15", 5);
        addEdge("I12", "G14", 8);
        addEdge("G6", "F9", 10);
        addEdge("I9", "G11", 9);
    }

    // Destructor
    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
        delete[] locationNames;
    }

    // Set the name of a location
    void setLocationName(int index, const string& name) {
        if (index >= 0 && index < numVertices) {
            locationNames[index] = name;
        }
    }

    // Get the index of a location by its name
    int getLocationIndex(const string& name) {
        for (int i = 0; i < numVertices; ++i) {
            if (locationNames[i] == name) {
                return i;
            }
        }
        return -1; // Return -1 if location is not found
    }

    // Add an edge between two locations with a specific weight
    void addEdge(const string& from, const string& to, int weight) {
        int fromIndex = getLocationIndex(from);
        int toIndex = getLocationIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Error: Invalid location names \"" << from << "\" or \"" << to << "\".\n";
            return;
        }

        adjacencyMatrix[fromIndex][toIndex] = weight;
        adjacencyMatrix[toIndex][fromIndex] = weight; // For undirected graph
    }

    bool validateLocation(const string& locationName) {
        int index = getLocationIndex(locationName);
        if (index == -1) {
            cout << "Error: Location \"" << locationName << "\" does not exist." << endl;
            return false;
        }
        return true;
    }

    // Display the locations
    void displayLocations() {
        if (numVertices == 0) {
            cout << "No locations available.\n";
            return;
        }

        cout << "List of Locations:\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << i + 1 << ". " << locationNames[i] << "\n"; // Print index and location name
        }
    }

    void shortestPath(const string& sourceName, OrderQueue& queue) {
        int sourceIndex = getLocationIndex(sourceName);
        if (sourceIndex == -1) {
            cout << "Location does not exist.\n";
            return;
        }

        // Initialize distance, visited, and previous arrays
        int* dist = new int[numVertices];
        bool* visited = new bool[numVertices];
        int* prev = new int[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            dist[i] = INT_MAX;
            visited[i] = false;
            prev[i] = -1;
        }
        dist[sourceIndex] = 0;

        priority_queue<pair<int, int>, deque<pair<int, int>>, greater<>> pq;
        pq.push({ 0, sourceIndex });

        // Dijkstra's algorithm
        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentIndex = pq.top().second;
            pq.pop();

            if (visited[currentIndex]) continue;
            visited[currentIndex] = true;

            for (int i = 0; i < numVertices; ++i) {
                if (adjacencyMatrix[currentIndex][i] != 0 && !visited[i]) {
                    int newDist = currentDist + adjacencyMatrix[currentIndex][i];
                    if (newDist < dist[i]) {
                        dist[i] = newDist;
                        prev[i] = currentIndex;
                        pq.push({ newDist, i });
                    }
                }
            }
        }

        // Process the order queue and calculate delivery paths
        cout << "Delivery Route: ";
        Order* temp = queue.getFront(); // Start with the first order in the queue
        string lastLocation = sourceName;

        // Ensure the queue is not empty
        if (!temp) {
            cout << "No orders to deliver.\n";
            delete[] dist;
            delete[] visited;
            delete[] prev;
            return;
        }

        while (temp) {
            // Skip orders that are not processed
            if (temp->status != 2) {
                temp = temp->next;
                continue;
            }

            string orderLocation = temp->location;
            int destIndex = getLocationIndex(orderLocation);

            // Validate if destination location exists
            if (destIndex == -1) {
                cout << "\nError: Location \"" << orderLocation << "\" does not exist for order ID: " << temp->id << "\n";
                temp = temp->next;
                continue;
            }

            // Build the path from source to destination
            int* path = new int[numVertices];
            int pathLength = 0;
            for (int at = destIndex; at != -1; at = prev[at]) {
                path[pathLength++] = at;
            }

            // Display the path
            for (int i = pathLength - 1; i >= 0; --i) {
                if (i == pathLength - 1 && lastLocation != locationNames[path[i]]) {
                    cout << locationNames[path[i]] << " (Restaurant) ==> ";
                }
                else {
                    cout << locationNames[path[i]];
                    if (i == 0) {
                        cout << " (Order->" << temp->id << ")";
                    }
                    cout << " ==> ";
                }
            }
            lastLocation = orderLocation;

            // Mark the order as delivered and dequeue
            temp->status = 3;
            queue.dequeue();

            // Move to the next order
            temp = queue.getFront();

            delete[] path;
        }

        cout << "End of Route\n";

        // Clean up dynamically allocated arrays
        delete[] dist;
        delete[] visited;
        delete[] prev;
    }

};



void AdminMenue(RestaurantList& restaurants, OrderQueue& orders, PromotionStack promotions) {


    int choice;
    do {
        setTextColor("cyan");
        cout << "\nRestaurantHub - Main Menu\n";
        cout << "1. Add Restaurant\n";
        cout << "2. Edit Restaurant\n";
        cout << "3. Delete Restaurant\n";
        cout << "4. Display Restaurants\n";
        cout << "5. Display Restaurant Menu\n";
        cout << "6. Display Reviews\n";
        cout << "7. Promotions\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        setTextColor("green");

        switch (choice) {

        case 1: {
            string name, type, location;
            cout << "Enter restaurant name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter restaurant type: ";
            getline(cin, type);
            restaurants.addRestaurant(name, type);
            break;
        }


        case 2: {
            int id;
            string name, type;
            cout << "Enter restaurant ID to edit: ";
            cin >> id;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new type: ";
            getline(cin, type);
            restaurants.editRestaurant(id, name, type);
            break;
        }

        case 3: {
            int id;
            cout << "Enter restaurant ID to delete: ";
            cin >> id;
            restaurants.deleteRestaurant(id);
            break;
        }

        case 4:
            restaurants.displayRestaurants();
            break;


        case 5: {
            int id;
            cout << "Enter restaurant ID to display menu: ";
            cin >> id;
            Restaurant* restaurant = restaurants.findRestaurantById(id);
            if (restaurant) {
                restaurant->menu.displayMenu();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 6:

            do {
                cout << "1. Display Good Reviews\n";
                cout << "2. Display Bad Reviews\n";
                cout << "0. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {

                case 1:
                    cout << endl << endl;
                    reviews.displayTopReviews(true);
                    cout << endl << endl;
                    break;
                case 2:
                    cout << endl << endl;
                    reviews.displayTopReviews(false);
                    cout << endl << endl;
                    break;
                case 0:
                    cout << "Returning to main menu.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
                    break;
                }
            } while (choice != 0);
            break;

        case 7:
            promotionMenu(promotions);
            break;

        case 0:
            setTextColor("red");
            cout << "Exiting the system.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
    resetTextColor();
}


void customerMenu(RestaurantList& restaurants, OrderQueue& orders, PromotionStack& promotions, Graph& graph) {

    int choice;
    do {
        setTextColor("cyan");
        cout << "\nRestaurantHub - Main Menu\n";

        cout << "1. Display Restaurants\n";
        cout << "2. Display Restaurant Menu\n";
        cout << "3. Place Order\n";
        cout << "4. Give Reviews\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        setTextColor("green");

        switch (choice) {

        case 1:
            restaurants.displayRestaurants();
            break;

        case 2: {
            int id;
            cout << "Enter restaurant ID to display menu: ";
            cin >> id;
            Restaurant* restaurant = restaurants.findRestaurantById(id);
            if (restaurant) {
                restaurant->menu.displayMenu();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 3: {
            int restaurantId;
            cout << "Enter restaurant ID to place order: ";
            cin >> restaurantId;
            Restaurant* restaurant = restaurants.findRestaurantById(restaurantId);
            if (restaurant) {
                restaurant->menu.displayMenu();
                double totalCost = 0.0;
                int dishId, dishCount;
                string dishChoice;
                do {
                    cout << "Enter dish ID to order (or 0 to finish): ";
                    cin >> dishId;
                    if (dishId == 0) break;
                    Dish* dish = restaurant->menu.getDishById(dishId);
                    if (dish) {
                        cout << "Enter quantity for " << dish->name << ": ";
                        cin >> dishCount;
                        totalCost += dish->price * dishCount;
                    }
                    else {
                        cout << "Dish not found.\n";
                    }
                    cout << "Would you like to add another dish? (yes/no): ";
                    cin >> dishChoice;
                } while (dishChoice == "yes" || dishChoice == "y");
                promotions.applyPromotion(totalCost);
                string orderType, location;
                cout << "Enter order type (Normal, Express, Premium): ";
                cin >> orderType;
                cout << "Enter location: ";
                cin >> location;
                if (!graph.validateLocation(location))
                    cin >> location;
                orders.enqueue(orderType, totalCost, location);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }


        case 4:
            reviewMenu();
            break;

        case 0:
            setTextColor("red");
            cout << "Exiting the system.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
    resetTextColor();
}


void employeeMenu(RestaurantList& restaurants, OrderQueue& orders) {

    int choice;
    do {
        setTextColor("cyan");
        cout << "\nRestaurantHub - Main Menu\n";
        cout << "1. Display Restaurants\n";
        cout << "2. Add Dish to Restaurant Menu\n";
        cout << "3. Display Restaurant Menu\n";
        cout << "4. Process Order\n";
        cout << "5. Display Orders\n";
        cout << "6. Edit Dish\n";
        cout << "7. Remove Dish\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        setTextColor("green");

        switch (choice) {


        case 1:
            restaurants.displayRestaurants();
            break;


        case 2: {
            int id;
            cout << "Enter restaurant ID to add dish: ";
            cin >> id;
            Restaurant* restaurant = restaurants.findRestaurantById(id);
            if (restaurant) {
                string name, type;
                double price;
                cout << "Enter dish name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter dish type: ";
                getline(cin, type);
                cout << "Enter dish price: ";
                cin >> price;
                restaurant->menu.addDish(name, type, price);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 3: {
            int id;
            cout << "Enter restaurant ID to display menu: ";
            cin >> id;
            Restaurant* restaurant = restaurants.findRestaurantById(id);
            if (restaurant) {
                restaurant->menu.displayMenu();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 4:
            orders.processOrder();
            break;

        case 5:
            orders.displayOrders();
            break;

        case 6: { // Edit Dish
            int restaurantId, dishId;
            cout << "Enter restaurant ID to edit a dish: ";
            cin >> restaurantId;
            Restaurant* restaurant = restaurants.findRestaurantById(restaurantId);
            if (restaurant) {
                restaurant->menu.displayMenu();
                cout << "Enter dish ID to edit: ";
                cin >> dishId;
                string newName, newType;
                double newPrice;
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter new type: ";
                getline(cin, newType);
                cout << "Enter new price: ";
                cin >> newPrice;
                restaurant->menu.editDish(dishId, newName, newType, newPrice);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 7: { // Delete Dish
            int restaurantId, dishId;
            cout << "Enter restaurant ID to delete a dish: ";
            cin >> restaurantId;
            Restaurant* restaurant = restaurants.findRestaurantById(restaurantId);
            if (restaurant) {
                restaurant->menu.displayMenu();
                cout << "Enter dish ID to delete: ";
                cin >> dishId;
                restaurant->menu.deleteDishById(dishId);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }
              setTextColor("red");

        case 0:
            cout << "Exiting the system.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
    resetTextColor();
}


void DriverMenu(RestaurantList& restaurants, OrderQueue& orders, Graph& graph, string mainHub) {

    int choice;
    do {
        setTextColor("cyan");
        cout << "\nRestaurantHub - Main Menu\n";
        cout << "1. Display Restaurants\n";
        cout << "2. Add Dish to Restaurant Menu\n";
        cout << "3. Display Restaurant Menu\n";
        cout << "4. Process Order\n";
        cout << "5. Display Orders\n";
        cout << "6. Deliver orders\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        setTextColor("green");

        switch (choice) {


        case 1:
            restaurants.displayRestaurants();
            break;


        case 2: {
            int id;
            cout << "Enter restaurant ID to add dish: ";
            cin >> id;
            Restaurant* restaurant = restaurants.findRestaurantById(id);
            if (restaurant) {
                string name, type;
                double price;
                cout << "Enter dish name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter dish type: ";
                getline(cin, type);
                cout << "Enter dish price: ";
                cin >> price;
                restaurant->menu.addDish(name, type, price);
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 3: {
            int id;
            cout << "Enter restaurant ID to display menu: ";
            cin >> id;
            Restaurant* restaurant = restaurants.findRestaurantById(id);
            if (restaurant) {
                restaurant->menu.displayMenu();
            }
            else {
                cout << "Restaurant not found.\n";
            }
            break;
        }

        case 4:
            orders.processOrder();
            break;

        case 5:
            orders.displayOrders();
            break;

        case 6: { // Edit Dish
            graph.shortestPath(mainHub, orders);
            break;
        }

        case 0:
            cout << "Exiting the system.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
    resetTextColor();
}




int generateCustId() {
    static int currentId = 50000; // Generates 5-digit IDs starting from 50000
    return currentId++;
}

int generateEmpId() {
    static int currentId = 60000;
    return currentId++;
}


struct Driver {
    int id;
    string name;
    string password;
    Driver* next; // For collision handling in the hashmap

    Driver(int _id, string _name, string _password)
        : id(_id), name(_name), password(_password), next(nullptr) {
    }
};


// === Customer Structure ===
struct Customer {
    int id;
    string name;
    string email;
    string password;
    Customer* next;  // For collision handling in the hashmap

    Customer(int _id, string _name, string _email, string _password)
        : id(_id), name(_name), email(_email), password(_password), next(nullptr) {
    }
};

// === Employee Structure ===
struct Employee {
    int id;
    string name;
    string password;
    Employee* next; // For collision handling in the hashmap

    Employee(int _id, string _name, string _password)
        : id(_id), name(_name), password(_password), next(nullptr) {
    }
};

// === Admin Structure ===
struct Admin {
    string username;
    string password;

    Admin(string _username, string _password)
        : username(_username), password(_password) {
    }
};

// === Custom HashMap for Customers ===
class CustomerHashMap {
private:
    static const int TABLE_SIZE = 100;  // Array size for the hashmap
    Customer* table[TABLE_SIZE];  // Array of linked lists for collision handling

    // Hash function for customers: Using Division method
    int hash(int id) {
        return id % TABLE_SIZE;  // Simple hash based on ID
    }

public:
    CustomerHashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;  // Initialize each bucket with null
        }
    }

    // Add a new customer to the hashmap
    void addCustomer(int id, string name, string email, string password) {
        int index = hash(id);  // Get the bucket index

        // Create a new customer and add it to the linked list at that index
        Customer* newCustomer = new Customer(id, name, email, password);

        if (!table[index]) {
            table[index] = newCustomer;  // If no collision, directly add
        }
        else {
            Customer* temp = table[index];
            while (temp->next) {
                temp = temp->next;  // Traverse to the last node
            }
            temp->next = newCustomer;  // Add new customer at the end
        }
    }

    // Find a customer by email
    Customer* findCustomerByEmail(string email) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Customer* temp = table[i];
            while (temp) {
                if (temp->email == email) {
                    return temp;  // Customer found
                }
                temp = temp->next;
            }
        }
        return nullptr;  // Customer not found
    }


};


// === Custom HashMap for Employees ===
class EmployeeHashMap {
private:
    static const int TABLE_SIZE = 100;  // Array size for the hashmap
    Employee* table[TABLE_SIZE];  // Array of linked lists for collision handling

    // Hash function for employees: Using Division method
    int hash(int id) {
        return id % TABLE_SIZE;  // Simple hash based on ID
    }

public:
    EmployeeHashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;  // Initialize each bucket with null
        }
    }

    // Add a new employee to the hashmap
    void addEmployee(int id, string name, string password) {
        int index = hash(id);  // Get the bucket index

        // Check if an employee already exists with the given ID
        Employee* temp = table[index];
        while (temp) {
            if (temp->id == id) {
                cout << "Employee ID already exists!" << endl;
                return;  // Exit if employee with the same ID is found
            }
            temp = temp->next;
        }

        Employee* newEmployee = new Employee(id, name, password);
        if (!table[index]) {
            table[index] = newEmployee;
        }
        else {
            temp = table[index];
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newEmployee;
        }

        // Debug: Print employee details after adding
        cout << "Added Employee: ID = " << newEmployee->id
            << ", Name = " << newEmployee->name
            << ", Password = " << newEmployee->password << endl;
    }




    // Find an employee by ID
    Employee* findEmployeeById(int id) {
        int index = hash(id);  // Get the bucket index
        Employee* temp = table[index];
        while (temp) {
            if (temp->id == id) {
                return temp;  // Employee found
            }
            temp = temp->next;
        }
        return nullptr;  // Employee not found
    }
};



class DriverHashMap {
private:
    static const int TABLE_SIZE = 100;  // Array size for the hashmap
    Driver* table[TABLE_SIZE];  // Array of linked lists for collision handling

    // Hash function for employees: Using Division method
    int hash(int id) {
        return id % TABLE_SIZE;  // Simple hash based on ID
    }

public:
    DriverHashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = nullptr;  // Initialize each bucket with null
        }
    }

    // Add a new employee to the hashmap
    void addDriver(int id, string name, string password) {
        int index = hash(id);  // Get the bucket index

        // Check if an employee already exists with the given ID
        Driver* temp = table[index];
        while (temp) {
            if (temp->id == id) {
                cout << "Employee ID already exists!" << endl;
                return;  // Exit if employee with the same ID is found
            }
            temp = temp->next;
        }

        Driver* newDriver = new Driver(id, name, password);
        if (!table[index]) {
            table[index] = newDriver;
        }
        else {
            temp = table[index];
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newDriver;
        }

        // Debug: Print employee details after adding
        cout << "Added Driver: ID = " << newDriver->id
            << ", Name = " << newDriver->name
            << ", Password = " << newDriver->password << endl;
    }




    // Find an employee by ID
    Driver* findDriverById(int id) {
        int index = hash(id);  // Get the bucket index
        Driver* temp = table[index];
        while (temp) {
            if (temp->id == id) {
                return temp;  // Employee found
            }
            temp = temp->next;
        }
        return nullptr;  // Employee not found
    }
};



bool isValidPassword(const string& password) {
    // Check the length constraint
    if (password.length() <= 8 || password.length() > 12) {
        return false;
    }

    // Flags for validation checks
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    // Iterate through each character in the password
    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (!isalnum(ch)) hasSpecial = true; // Special character check
    }

    // Return true only if all conditions are met
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool isValidEmail(const string& email) {
    // Define valid domains
    const string gmail = "@gmail.com";
    const string yahoo = "@yahoo.com";

    // Check if the email ends with either domain
    if (email.size() >= gmail.size() &&
        email.substr(email.size() - gmail.size()) == gmail) {
        return true;
    }
    if (email.size() >= yahoo.size() &&
        email.substr(email.size() - yahoo.size()) == yahoo) {
        return true;
    }

    return false;
}





