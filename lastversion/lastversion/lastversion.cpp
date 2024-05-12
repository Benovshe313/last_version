#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;



class Ingredient {
public:
    string name;
    int count;

    int price;
    

    Ingredient() {
    }

    Ingredient(string name, int count, int price) : name(name), count(count), price(price) {
    }
};

class Food {
public:
    string name;
    Ingredient* ingredients;
    int ingredientCount;

    Food() {
        name = "";
        ingredients = nullptr;
        ingredientCount = 0;
    }

    Food(string name, Ingredient* ingredients, int ingredientCount) {
        this->name = name;
        this->ingredientCount = ingredientCount;
        this->ingredients = new Ingredient[ingredientCount];
        for (int i = 0; i < ingredientCount; i++) {
            this->ingredients[i] = ingredients[i];
        }
    }

    void addIngredients(Ingredient* newIngredients, int count) {
        Ingredient* temp = new Ingredient[ingredientCount + count];
        for (int i = 0; i < ingredientCount; i++) {
            temp[i] = ingredients[i];
        }
        for (int i = 0; i < count; i++) {
            temp[ingredientCount + i] = newIngredients[i];
        }
        delete[] ingredients;
        ingredients = temp;
        ingredientCount += count;
    }

    /*~Food() {
        delete[] ingredients;
    }*/
};


class Admin {
public:
    string adminName;
    string adminsName;
    int mobNum;
    string passWord;
    Ingredient* ingredients;
    int ingredientCount;
    Food* foods;
    int foodCount;
    double budget;
    bool loginn;
    double moneyEarn;
    double moneySpend;

public:

    Admin() {
        ingredientCount = 6;
        ingredients = new Ingredient[ingredientCount];
        ingredients[0] = Ingredient("Yumurta", 25, 2);
        ingredients[1] = Ingredient("Kartof", 25, 1);
        ingredients[2] = Ingredient("Sogan", 25, 1);
        ingredients[3] = Ingredient("Pomidor", 25, 3);
        ingredients[4] = Ingredient("Yerkoku", 25, 2);
        ingredients[5] = Ingredient("Biber", 25, 1);

        foods = nullptr;
        foodCount = 0;
        budget = 1000;
    }

    void signup() {
        cout << "Sign up" << endl;
        cout << "Enter name: ";
        getline(cin, adminName);
        cout << "Enter surname: ";
        getline(cin, adminsName);
        cout << "Enter mobile number: ";
        cin >> mobNum;
        cin.ignore();
        cout << "Enter password: ";
        getline(cin, passWord);
    }

    bool login() {
        if (!loginn) {
            cout << "Login" << endl;
            cout << "Enter mobile number: ";
            int mobileNum;
            cin >> mobileNum;
            cin.ignore();
            cout << "Enter password: ";
            string inputPasswr;
            getline(cin, inputPasswr);

            if (mobNum == mobileNum && passWord == inputPasswr) {
                cout << "Login successful" << endl;
                loginn = true;
                return true;
            }
            else {
                cout << "Incorrect mobile number or password" << endl;
                Sleep(2000);
                system("cls");
                return false;
            }
        }
    }

    void addIngredient(Ingredient ingredient) {

        cout << "Budget before: $" << budget << endl;
        budget -= ingredient.price;
        moneySpend += ingredient.price;
        cout << "Budget after: $" << budget << endl;

        bool found = false;

        if (!found) {
            Ingredient* temp = new Ingredient[ingredientCount + 1];
            for (int i = 0; i < ingredientCount; i++) {
                temp[i] = ingredients[i];
            }
            temp[ingredientCount] = ingredient;
            delete[] ingredients;
            ingredients = temp;
            ingredientCount++;
        }
    }
    
    void addFood(Food food) {
        for (int i = 0; i < food.ingredientCount; i++) {
            bool enoughIngredient = false;
            for (int j = 0; j < ingredientCount; j++) {
                if (food.ingredients[i].name == ingredients[j].name) {
                    if (food.ingredients[i].count <= ingredients[j].count) {
                        enoughIngredient = true;
                        break;
                    }
                }
            }
            if (!enoughIngredient) {
                cout << "Not enough ingredient in stock." << endl;
                return;
            }
        }

        Food* temp = new Food[foodCount + 1];
        for (int i = 0; i < foodCount; i++) {
            temp[i] = foods[i];
        }
        temp[foodCount] = food;
        foodCount++;
        delete[] foods;
        foods = temp;
        cout << "Food added" << endl;
    }


    void displayIngr() {
        for (int i = 0; i < ingredientCount; i++) {
            cout << "Name: " << ingredients[i].name << endl;
            cout << "Count: " << ingredients[i].count << endl;
            cout << "Price: " << ingredients[i].price << endl;
        }
    }

    void displayStatistics() {
        cout << "Budget: $" << budget << endl;
        cout << "Money Earned: $" << moneyEarn << endl;
        cout << "Money Spent: $" << moneySpend << endl;
    }

    //~Admin() {
    //    delete[] ingredients;
    //    //delete[] foods;
    //}
};


class User {
public:
    string userName;
    string userSurname;
    int userMobNum;
    string userPassword;
    string* foodNames; 
    int foodNamesSize;
    int foodNamesMax;

    User() {
        foodNamesMax = 10;
        foodNamesSize = 0;
        foodNames = new string[foodNamesMax];
    }

    User(string name, string surname, int mobNum, string password) :
        userName(name), userSurname(surname), userMobNum(mobNum), userPassword(password) {
    }

    void signup() {
        cout << "Sign up" << endl;
        cout << "Enter name: ";
        getline(cin, userName);
        cout << "Enter surname: ";
        getline(cin, userSurname);
        cout << "Enter mobile number: ";
        cin >> userMobNum;
        cin.ignore();
        cout << "Enter password: ";
        getline(cin, userPassword);
    }

    bool login() {
        cout << "Login" << endl;
        cout << "Enter mobile number: ";
        int mobileNum;
        cin >> mobileNum;
        cin.ignore();
        cout << "Enter password: ";
        string inputPasswr;
        getline(cin, inputPasswr);

        if (userMobNum == mobileNum && userPassword == inputPasswr) {
            cout << "Login successful" << endl;
            return true;
        }
        else {
            cout << "Incorrect mobile number or password" << endl;
            Sleep(2000);
            system("cls");
            return false;
        }
    }

    void addfoodNames(string foodName) {
        string* tempfoodNames = new string[foodNamesSize + 1];
        for (int i = 0; i < foodNamesSize; i++) {
            tempfoodNames[i] = foodNames[i];
        }
        tempfoodNames[foodNamesSize] = foodName;
        delete[] foodNames;
        foodNames = tempfoodNames;
        foodNamesSize++;
    }

    void orderFood(Admin& admin) {
        if (admin.foodCount == 0) {
            cout << "Add food first" << endl;
            Sleep(2000);
            system("cls");
            return;
        }
        cout << "Menu:" << endl;
        for (int i = 0; i < admin.foodCount; i++) {
            cout << i + 1 << ". " << admin.foods[i].name << endl;
            cout << "Ingredients:" << endl;
            for (int j = 0; j < admin.foods[i].ingredientCount; j++) {
                cout << admin.foods[i].ingredients[j].name  << endl;
            }
            int totalPrice = 0;
            for (int j = 0; j < admin.foods[i].ingredientCount; j++) {
                totalPrice += (admin.foods[i].ingredients[j].count * admin.foods[i].ingredients[j].price)+10;
            }
            cout << "Total Price: $" << totalPrice  << endl; 
        }

        int numItems;
        cout << "Enter total number of food add to basket: ";
        cin >> numItems;
        cin.ignore();

        for (int i = 0; i < numItems; i++) {
            int foodChoice;
            cout << "Enter row number of " <<i+1<< " food: ";
            cin >> foodChoice;
            cin.ignore();

            if (foodChoice >= 1 && foodChoice <= admin.foodCount) {
                addfoodNames(admin.foods[foodChoice - 1].name);
            }
            cout << "Food added to basket" << endl;
            Sleep(2000);
            system("cls");
        }
    }

    void displayfoodNames() {
        for (int i = 0; i < foodNamesSize; i++) {
            cout << i + 1 << ". " << foodNames[i] << endl;
        }
    }

    void removefoodNames(int index) {
        if (index >= 0 && index < foodNamesSize) {
            for (int i = index; i < foodNamesSize - 1; i++) {
                foodNames[i] = foodNames[i + 1];
            }
            foodNamesSize--;
        }
    }

    void confirmOrder(Admin& admin, User& user) {
        vector<string> removeFood;

        double totalPrice = 0; 

        for (int i = 0; i < user.foodNamesSize; i++) {
            for (int j = 0; j < admin.foodCount; j++) {
                if (user.foodNames[i] == admin.foods[j].name) {
                    bool enoughIngredients = true;
                    for (int k = 0; k < admin.foods[j].ingredientCount; k++) {
                        for (int m = 0; m < admin.ingredientCount; m++) {
                            if (admin.foods[j].ingredients[k].name == admin.ingredients[m].name) {
                                if (admin.foods[j].ingredients[k].count > admin.ingredients[m].count) {
                                    enoughIngredients = false;
                                    removeFood.push_back(admin.foods[j].name);
                                    break;
                                }
                            }
                        }
                        if (!enoughIngredients) {
                            break; 
                        }
                    }

                    if (!enoughIngredients) {
                        break;
                    }

                    for (int k = 0; k < admin.foods[j].ingredientCount; k++) {
                        totalPrice += (admin.foods[j].ingredients[k].count * admin.foods[j].ingredients[k].price)+10;
                        for (int m = 0; m < admin.ingredientCount; m++) {
                            if (admin.foods[j].ingredients[k].name == admin.ingredients[m].name) {
                                admin.ingredients[m].count -= admin.foods[j].ingredients[k].count;
                                break;
                            }
                        }
                    }
                    break; 
                }
            }
        }

        for (size_t r = 0; r < removeFood.size(); r++) {
            string& dish = removeFood[r];
            for (int i = 0; i < admin.foodCount; i++) {
                if (admin.foods[i].name == dish) {
                    for (int j = i; j < admin.foodCount - 1; j++) {
                        admin.foods[j] = admin.foods[j + 1];
                    }
                    admin.foodCount--;
                    break;
                }
            }
        }

        cout << "Total amount: $" << totalPrice << endl;
        double amountPaid;
        cout << "Enter the amount you pay: $";
        cin >> amountPaid;
        cin.ignore();

        if (amountPaid < totalPrice) {
            cout << "Less amount entered" << endl;
        }
        else if (amountPaid > totalPrice) {
            cout << "Change: $" << amountPaid - totalPrice << endl;
            admin.moneyEarn += totalPrice; 
        }
        else {
            cout << "Thank you for payment" << endl;
            
            user.foodNamesSize = 0;
            admin.budget += amountPaid;
            admin.moneyEarn += totalPrice;
            cout << "Restaurant budget: $" << admin.budget << endl;
            Sleep(2000);
            system("cls");
        }
    }

    void displayRemove(Admin& admin, User& user) {
        if (foodNamesSize == 0) {
            cout << "Basket is empty" << endl;
            Sleep(2000);
            system("cls");
            return;
        }

        cout << "Basket Contents:" << endl;
        displayfoodNames();
        cout << "Enter row number of food to remove (else 0): ";
        int index;
        cin >> index;
        cin.ignore();
        if (index == 0) {
            string remove;
            cout << "Confirm order? 1.yes 2.no: ";
            getline(cin, remove);
            if (remove == "1") {
                confirmOrder(admin, user);
            }
        }
        else {
            removefoodNames(index - 1);
            cout << "Removed from basket" << endl;
            Sleep(2000);
            system("cls");
        }
        Sleep(2000);
        system("cls");
    }
};


int main() {
    Admin admin;
    User user;
    bool exit = false;
    bool adminLogin = false;
    bool userLogin = false;
    bool adminChoice = false;

    while (!exit) {
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "Make choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        Sleep(200);
        system("cls");
        if (choice == 1) {
            while (true) {
                if (!adminLogin) {
                    cout << "1.Sign up" << endl;
                    cout << "2.Login" << endl;
                    cout << "Enter choice: ";
                    int option;
                    cin >> option;
                    cin.ignore();
                    Sleep(200);
                    system("cls");
                    if (option == 1) {
                        admin.signup();
                        Sleep(200);
                        system("cls");
                        if (!admin.login()) {
                            continue;
                        }
                        adminLogin = true;
                        Sleep(2000);
                        system("cls");
                    }
                    else if (option == 2) {
                        if (!admin.login()) {
                            continue;
                        }
                        adminLogin = true;
                    }
                }

                cout << "1. Add food" << endl;
                cout << "2. Ingredients" << endl;
                cout << "3. Add ingredients" << endl;
                cout << "4. Statistics" << endl;
                cout << "5. Main menu" << endl;
                cout << "6. Logout" << endl;
                cout << "Enter your choice: ";
                int adminOption;
                cin >> adminOption;
                cin.ignore();

                bool ingrNotFound = false;
                if (adminOption == 1) {
                    string foodName;
                    Sleep(200);
                    system("cls");
                    cout << "Enter food name: ";
                    getline(cin, foodName);
                    cout << "Ingredients:" << endl;
                    admin.displayIngr();
                    cout << "Enter number of ingredients want to add: ";
                    int numIng;
                    cin >> numIng;
                    cin.ignore();

                    if (numIng > admin.ingredientCount) {
                        cout << "Not enough ingredients in stock" << endl;
                    }
                    else {
                        Ingredient* food = new Ingredient[numIng];
                        bool enoughIngredient = true;
                        for (int i = 0; i < numIng; i++) {
                            string ingrName;
                            cout << "Enter name of " << i + 1 << " ingredient: ";
                            getline(cin, ingrName);
                            bool found = false;
                            for (int j = 0; j < admin.ingredientCount; j++) {
                                if (admin.ingredients[j].name == ingrName) {
                                    found = true;
                                    food[i] = admin.ingredients[j];
                                    cout << "Enter count: ";
                                    cin >> food[i].count;
                                    cin.ignore();
                                    if (food[i].count > admin.ingredients[j].count) {
                                        enoughIngredient = false;
                                        break;
                                    }
                                }
                            }
                            if (!found) {
                                ingrNotFound = true;
                            }
                        }
                        if (enoughIngredient && !ingrNotFound) {
                            Food newFood(foodName, food, numIng);
                            admin.addFood(newFood);
                            //cout << "Food added" << endl;
                        }
                        else {
                            cout << "Not enough ingredients in stock";
                        }
                    }
                    Sleep(2000);
                    system("cls");
                }
                        else if (adminOption == 2) {
                            Sleep(200);
                            system("cls");
                            cout << "Ingredients:" << endl;
                            admin.displayIngr();
                        }
                        else if (adminOption == 3) {
                            string name;
                            int count;
                            int price;
                            Sleep(200);
                            system("cls");
                            cout << "Ingredient name: ";
                            getline(cin, name);
                            bool found = false;
                            for (int i = 0; i < admin.ingredientCount; i++) {
                                if (admin.ingredients[i].name == name) {
                                    found = true;
                                    cout << "Count: " << admin.ingredients[i].count << endl;
                                    cout << "Price: " << admin.ingredients[i].price << endl;
                                    cout << "Want to increase count? 1. Yes 2. No: ";
                                    string choice;
                                    getline(cin, choice);
                                    if (choice == "1") {
                                        cout << "Enter additional number: ";
                                        cin >> count;
                                        admin.ingredients[i].count += count;
                                        cout << "Final count " << admin.ingredients[i].count << endl;
                                    }
                                    else {
                                        break;
                                    }

                                }
                            }
                            if (!found) {
                                cout << "Enter count: ";
                                cin >> count;
                                cout << "Enter price: ";
                                cin >> price;
                                Ingredient ing(name, count, price);
                                admin.addIngredient(ing);
                                cout << "Ingredient added" << endl;
                                Sleep(2000);
                                system("cls");
                            }
                        }
                        else if (adminOption == 4) {
                            admin.displayStatistics();
                            Sleep(2000);
                            system("cls");
                        }
                        else if (adminOption == 5) {
                            Sleep(200);
                            system("cls");
                            break;
                        }
                        else if (adminOption == 6) {
                            adminLogin = false;
                            exit = true;
                            break;
                        }
                    }
                }

                else if (choice == 2) {
                    Sleep(300);
                    system("cls");
                    if (!userLogin) {
                        cout << "1.Sign up" << endl;
                        cout << "2.Login" << endl;
                        cout << "Enter choice: ";
                        int option;
                        cin >> option;
                        cin.ignore();

                        if (option == 1) {
                            Sleep(200);
                            system("cls");
                            user.signup();
                            Sleep(200);
                            system("cls");
                            if (!user.login()) {
                                continue;
                            }
                        }
                        else if (option == 2) {

                            if (!user.login()) {
                                continue;
                            }
                        }
                        userLogin = true;
                        Sleep(2000);
                        system("cls");
                    }
                    if (userLogin) {
                        while (true) {
                            cout << "1. Order food" << endl;
                            cout << "2. Main menu" << endl;
                            cout << "3. Basket" << endl;
                            cout << "4. Logout" << endl;
                            cout << "Enter your choice: ";

                            int userChoice;
                            cin >> userChoice;
                            cin.ignore();

                            if (userChoice == 1) {
                                Sleep(200);
                                system("cls");
                                user.orderFood(admin);
                            }
                            else if (userChoice == 2) {
                                if (!adminChoice) {
                                    Sleep(2000);
                                    system("cls");
                                    cout << "1. Admin" << endl;
                                    cout << "2. User" << endl;
                                    adminChoice = true;
                                }
                                cout << "Enter choice: ";
                                int adminOrUser;
                                cin >> adminOrUser;
                                cin.ignore();
                                Sleep(2000);
                                system("cls");

                                if (adminOrUser == 1) {
                                    userLogin = false;
                                    break;
                                }
                                else if (adminOrUser == 2) {
                                    continue;
                                }
                            }
                            else if (userChoice == 3) {
                                user.displayRemove(admin, user);
                            }

                            else if (userChoice == 4) {
                                userLogin = false; 
                                exit = true;
                                break;
                            }
                        }
                    }
                }
                else if (choice == 5) {
                    adminLogin = false;
                    userLogin = false; 
                    continue; 
                }
            }
        }
    
