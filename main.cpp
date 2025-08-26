#include "header.h"

const int MAXVERTICES = 28;  //set total number of vertices



// === Password Masking Function ===
void maskPassword(string& password) {
    setTextColor("red");
    password.clear();
    char ch;
    while ((ch = _getch()) != 13) {  // Loop until Enter key is pressed
        if (ch == 8) {  // If Backspace is pressed, delete last character
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b";  // Move cursor back, overwrite with space, and move back again
            }
        }
        else {
            password.push_back(ch);  // Add character to password
            cout << "*";  // Mask the input
        }
    }
    cout << endl;
    resetTextColor();
}


void populateData(RestaurantList& restaurants, OrderQueue& orders, PromotionStack& promotions, Graph& graph) {
    setTextColor("red");
    // Add Restaurants
    restaurants.addRestaurant("Italian Bistro", "Italian Cuisine");
    restaurants.addRestaurant("Cheezious", "Fast Food");
    restaurants.addRestaurant("sushi Haven", "Japanease Cuisine");
    // Add Dishes to Restaurants
    Restaurant* italianBistro = restaurants.findRestaurantById(10000);
    if (italianBistro) {
        italianBistro->menu.addDish("Spaghetti Carbonara", "Main Course", 12.99);
        italianBistro->menu.addDish("Tiramisu", "Dessert", 6.50);
        double dishPrice1 = 12.99;  // Spaghetti Carbonara
        double dishPrice2 = 6.50;   // Tiramisu

        // Order calculation with 15% discount (Lunch Special promotion)
        double discount = 0.15; // 15% discount
        double totalCost = (dishPrice1 * 4 + dishPrice2) * (1 - discount);  // 4 servings of Spaghetti Carbonara

        // Place the order with Premium type and location "F10"
        orders.enqueue("Premium", totalCost, "G10");

        cout << "Order placed at " << italianBistro->name << " (Restaurant ID: 10000) with a total cost of $" << totalCost << endl;

    }


    Restaurant* restaurant1 = restaurants.findRestaurantById(10001);
    if (restaurant1) {
        restaurant1->menu.addDish("Crown Crust Pizza", "Pizza", 12);
        restaurant1->menu.addDish("Calzone", "Pizza", 6);
        double dishPrice1 = 12.00;  // Crown Crust Pizza
        double dishPrice2 = 6.00;   // Calzone

        // Order calculation with 10% discount (Holiday Discount promotion)
        double discount = 0.10; // 10% discount
        double totalCost = (dishPrice1 * 2 + dishPrice2 * 3) * (1 - discount);  // 2 Crown Crust Pizzas and 3 Calzones

        // Place the order with Express type and location "B5"
        orders.enqueue("Express", totalCost, "H8");

        cout << "Order placed at " << restaurant1->name << " (Restaurant ID: 10001) with a total cost of $" << totalCost << endl;

    }


    Restaurant* sushiHaven = restaurants.findRestaurantById(10002);
    if (sushiHaven) {
        sushiHaven->menu.addDish("California Roll", "Main Course", 8.99);
        sushiHaven->menu.addDish("Miso Soup", "Starter", 3.50);
        double dishPrice1 = 8.99;  // California Roll
        double dishPrice2 = 3.50;  // Miso Soup

        // No discount applied
        double totalCost = (dishPrice1 * 3 + dishPrice2 * 2);  // 3 California Rolls and 2 Miso Soups

        // Place the order with Normal type and location "D12"
        orders.enqueue("Normal", totalCost, "F7");

        cout << "Order placed at " << sushiHaven->name << " (Restaurant ID: 10002) with a total cost of $" << totalCost << endl;
    }





    cout << "Orders populated successfully.\n";
    // Add Promotions
    promotions.addPromotion("winterSale", 0.2, 1);
    promotions.addPromotion("Holiday Discount", 20, 10);
    promotions.addPromotion("Lunch Special", 15, 5);

    // Add Reviews
    reviews.addReview(2, "bad Italian dishes.Never gonna try again!", italianBistro);
    reviews.addReview(4, "Great sushi and service!", sushiHaven);

    cout << "Data populated successfully.\n";
    resetTextColor();
}

void printMessage(const string& message) {

    const int width = 60;
    const char borderChar = '*';

    int padding = (width - message.length()) / 2;

    cout << setfill(borderChar) << setw(width) << "" << endl;

    cout << setfill(' ') << setw(padding + message.length()) << message << endl;

    // Print bottom border
    cout << setw(width) << setfill(borderChar) << "" << endl;
}




// === Main Application ===
int main() {
    int opt;
    string filename;
    string welcomeMessage = "Welcome to Restaurant Hub!!!!";
    cout << "\033[0;32m";
    // Print the fancy message
    printMessage(welcomeMessage);

    setTextColor("bright_magenta");
    cout << "  \n"
        "  S a v o u r i n g  \n"
        "      t h e      \n"
        "  F l a v o u r s \n"
        "     T h a t \n"
        "   I g n i t e \n";
    cout << "      M y \n"
        "  S e n s e s \n"
        "  "
        "  "
        " \n"
        "   \n";

    cout << "   E A T   G O O D ! ! ! \n"
        "       \n"
        "       F E E L    G O O D ! ! !\n"
        "  \n\n";
    setTextColor("bright_yellow");
    cout << "      W e l c o m e ! ! !~\n"
        "       sameer and sakeena\n";


    cout << "\033[0;32m";
    printMessage(welcomeMessage);

    CustomerHashMap customers;
    EmployeeHashMap employees;
    DriverHashMap drivers;

    Admin admin("admin", "admin123"); // Initialize the admin account

    int choice, role;
    string name, email, password;
    RestaurantList restaurants;
    OrderQueue orders;
    PromotionStack promotions;
    Graph graph(MAXVERTICES);
    string mainHub = "F10";
    if (graph.getLocationIndex(mainHub) != -1) {
        cout << "mainhub identified!" << endl;
    }
    populateData(restaurants, orders, promotions, graph);


    int id = 0;


    do {
        setTextColor("yellow");
        cout << "\n=========================================\n";
        cout << "             RestaurantHub               \n";
        cout << "=========================================\n";
        cout << "1.  Customer Sign Up / Log In\n";
        cout << "2.  Employee Sign Up / Log In\n";
        cout << "3.  Admin Log In\n";
        cout << "4.  Exit\n";
        cout << "=========================================\n";
        cout << " Enter your choice: ";
        resetTextColor();
        cin >> choice;
        cin.ignore();  // To clear the newline character left in the buffer

        switch (choice) {
        case 1: {  // Customer Sign Up / Log In
            int subChoice;
            cout << "\n=========================================\n";
            cout << "              Customer Menu              \n";
            cout << "=========================================\n";
            cout << "1.  Sign Up\n";
            cout << "2.  Log In\n";
            cout << "=========================================\n";
            cout << "Enter your choice: ";
            cin >> subChoice;
            cin.ignore();

            switch (subChoice) {
            case 1: {
                // Sign up process
                cout << "Enter your name: ";
                getline(cin, name);
                cout << " Enter your email: ";
                getline(cin, email);

                // Validate the email
                while (!isValidEmail(email)) {
                    cout << " Invalid email address. Please enter a valid email: ";
                    getline(cin, email);
                }
                // Check if email is already registered
                if (customers.findCustomerByEmail(email)) {
                    cout << " Email is already registered. Please use a different one.\n";
                    break;
                }

                id = generateCustId();

                cout << "Enter your password: ";
                maskPassword(password);  // Mask password input
                while (!isValidPassword(password)) {
                    cout << " Invalid Password. Please enter a valid password: ";
                    maskPassword(password);
                }
                // Add customer to the hashmap with a unique ID
                Customer customer(id, name, email, password);

                customers.addCustomer(id, name, email, password);
                cout << " Sign-up successful! Your ID is " << id << endl;
                customerMenu(restaurants, orders, promotions, graph);
                break;
            }
            case 2: {
                // Log in process
                cout << " Enter your email: ";
                getline(cin, email);

                // Validate the email
                while (!isValidEmail(email)) {
                    cout << " Invalid email address. Please enter a valid email: ";
                    getline(cin, email);
                }

                Customer* customer = customers.findCustomerByEmail(email); // Moved declaration here
                if (customer) {
                    cout << "Enter your password: ";
                    string enteredPassword;
                    maskPassword(enteredPassword);  // Mask password input

                    if (enteredPassword == customer->password) {
                        cout << " Login successful! Welcome " << customer->name << "\n";
                        customerMenu(restaurants, orders, promotions, graph);
                    }
                    else {
                        cout << " Incorrect password. Please try again.\n";
                    }
                }
                else {
                    cout << " Customer not found. Please sign up first.\n";
                }
                break;
            }
            default:
                cout << " Invalid choice. Returning to main menu.\n";
                break;
            }
            break;
        }

        case 2: {  // Employee Sign Up / Log In
            int subChoice;
            cout << "\n=========================================\n";
            cout << "              Employee Menu              \n";
            cout << "=========================================\n";
            cout << "1.  Sign Up\n";
            cout << "2.  Log In\n";
            cout << "=========================================\n";
            cout << " Enter your choice: ";
            cin >> subChoice;
            cin.ignore();

            switch (subChoice) {
            case 1: {
                // Employee sign up process
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter your role(1.Employee 2.Driver): ";
                cin >> role;
                while (role != 1 && role != 2) {
                    cin >> role;
                }
                id = generateEmpId();
                cout << "Enter your password: ";
                maskPassword(password);  // Mask password input
                while (!isValidPassword(password)) {
                    cout << " Invalid Password. Please enter a valid password: ";
                    maskPassword(password);
                }
                if (role == 1) {
                    // Add employee to the hashmap with a unique ID
                    employees.addEmployee(id, name, password);
                    cout << " Employee sign-up successful! Your ID is " << id << endl;
                    employeeMenu(restaurants, orders);
                }
                else if (role == 2) {
                    // Add employee to the hashmap with a unique ID
                    drivers.addDriver(id, name, password);
                    cout << " Employee sign-up successful! Your ID is " << id << endl;
                    DriverMenu(restaurants, orders, graph, mainHub);
                }

                break;
            }
            case 2: {
                // Employee log in process
                cout << "Enter your Employee ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter your role(1.Employee 2.Driver): ";
                cin >> role;

                while (role != 1 && role != 2) {
                    cin >> role;
                }
                if (role == 1) {
                    Employee* employee = employees.findEmployeeById(id); // Moved declaration here
                    if (employee) {
                        cout << "Enter your password: ";
                        string enteredPassword;
                        maskPassword(enteredPassword);  // Mask password input
                        if (role == 1) {}
                        if (enteredPassword == employee->password) {
                            cout << " Login successful! Welcome " << employee->name << " !!\n";

                            employeeMenu(restaurants, orders);
                        }
                        else {
                            cout << " Incorrect password. Please try again.\n";
                        }
                    }
                    else {
                        cout << " Employee/Driver not found. Please sign up first.\n";
                    }
                }
                else if (role == 2) {
                    Driver* employee = drivers.findDriverById(id); // Moved declaration here
                    if (employee) {
                        cout << "Enter your password: ";
                        string enteredPassword;
                        maskPassword(enteredPassword);  // Mask password input
                        if (role == 1) {}
                        if (enteredPassword == employee->password) {
                            cout << " Login successful! Welcome " << employee->name << " !!\n";

                            DriverMenu(restaurants, orders,graph,mainHub);
                        }
                        else {
                            cout << " Incorrect password. Please try again.\n";
                        }
                    }
                    else {
                        cout << " Employee/Driver not found. Please sign up first.\n";
                    }
                
                
                }
                

                
                break;
            }
            default:
                cout << " Invalid choice. Returning to main menu.\n";
                break;
            }
            break;
        }

        case 3: {  // Admin Log In
            string username, password;
            cout << "\n=========================================\n";
            cout << "               Admin Log In              \n";
            cout << "=========================================\n";
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            maskPassword(password);

            if (username == admin.username && password == admin.password) {
                cout << " Admin login successful! Welcome back.\n";
                AdminMenue(restaurants, orders, promotions);
            }
            else {
                cout << "Incorrect username or password.Please try again.\n";
            }
            break;
        }

        case 4:
            setTextColor("red");
            cout << "\n=========================================\n";
            cout << "          Exiting the system. Bye!       \n";
            cout << "=========================================\n";
            resetTextColor();
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}




