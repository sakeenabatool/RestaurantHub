# 🍴 RestaurantHub

**RestaurantHub** is a C++ console-based application that simulates a restaurant management system.  
It allows **Customers, Employees, Drivers, and an Admin** to interact with the system through login/sign-up processes.  
The project demonstrates **data structures, OOP concepts, and algorithms** in a practical restaurant/order-management environment.

---

## 🚀 Features

### 👤 Customers
- Sign Up with validation (email & strong password).
- Log In with password masking (characters hidden as `*`).
- Browse restaurant menus and place orders.
- Enjoy promotions (discounts on special offers).

### 👨‍🍳 Employees & 🚗 Drivers
- Employees can log in to view/manage orders.
- Drivers can log in and handle deliveries.
- Unique IDs are generated for each employee/driver.

### 👑 Admin
- Secure login with username/password (`admin/admin123` by default).
- Access to system management functions (restaurants, promotions, reviews, etc.).

### 🍕 Restaurants
- Preloaded restaurants (e.g., *Italian Bistro*, *Cheezious*, *Sushi Haven*).
- Each restaurant has a menu with multiple dishes.
- Orders are placed with different priority levels (Premium, Express, Normal).

### 🎁 Promotions
- Preloaded discounts such as:
  - Winter Sale (20%)
  - Holiday Discount (10%)
  - Lunch Special (15%)

### ⭐ Reviews
- Customers can leave reviews for restaurants.
- Example:  
  - `"Great sushi and service!"`  
  - `"Bad Italian dishes. Never gonna try again!"`

---

## 🛠️ Technical Details

- **Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Data Structures Used:**
  - `HashMap` → Customers, Employees, Drivers
  - `Queue` → Orders
  - `Stack` → Promotions
  - `Graph` → Restaurant locations & delivery routes
- **Extra Features:**
  - Password masking (using `_getch()`).
  - Colorful console output for a better user experience.
  - Decorative console banners/messages.

---

## 📂 Project Structure

