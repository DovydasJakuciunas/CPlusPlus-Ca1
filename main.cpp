#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include "shipping_data_struct.h"

using namespace std;
void printMainMenuOptions();
void printLinkedListMenuOptions();
void printVectorMenuOptions();
void printMapMenuOptions();
void parseLine(const string& line,shipping_data &shippingEntry);
void load(const string& fileName, list<shipping_data> &data);
void display(const shipping_data &shippingEntry);
void LinkedListMenu(list<shipping_data> &shippingList);
void vectorMenu(list<shipping_data> &shippingList);
void displayLinkedList(list<shipping_data> &shippingList);

shipping_data &getShippingEntry(shipping_data &shippingEntry);

void displayVector(const vector<shipping_data>& vector1);

void setMenu(const list<shipping_data>& shippingList);

void checkForInvalidProductImportanceValues(const list<shipping_data>& list1, unordered_set<string> set);

void mapMenu(const list<shipping_data>& list1);

void displayHeader();

int main()
{
    list<shipping_data> shippingList;
    load("shipping-data-small.csv",shippingList);
    cout << "Welcome to the program \n Please enter your selection" << endl;
    bool quit = false;
    while (!quit)
    {
        printMainMenuOptions();
        int choice;
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        switch(choice)
        {
            case 1:
                LinkedListMenu(shippingList);
                break;
            case 2:
                vectorMenu(shippingList);
                break;
            case 3:
                setMenu(shippingList);
                break;
            case 4:
                mapMenu(shippingList);
                break;
            case 5:
                quit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }
    return 0;
}

void mapMenu(const list<shipping_data>& list1)
{
    unordered_map<int, shipping_data> map1;
    bool quit = false;
    while (!quit)
    {
        printMapMenuOptions();
        int choice;
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        switch(choice)
        {
            case 1://create a map from the list using id as the key and the rest of the data as the value
            {
                for (auto & it : list1)
                {
                    map1.insert({it.id, it});
                }
                break;
            }
            case 2://find a display a record given an id by the user
            {
                int id;
                cout << "Please enter the id of the record you want to find" << endl;
                cin >> id;
                while(!cin)
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Please enter a valid id" << endl;
                    cin >> id;
                }
                auto it = map1.find(id);
                if(it != map1.end())
                {
                    displayHeader();
                    display(it->second);
                }
                else
                {
                    cout << "Record not found" << endl;
                }
            }
                break;
            case 3:
                quit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }

}

void setMenu(const list<shipping_data>& shippingList)
{
    unordered_set<string> validProductImportanceValues = {"low","medium","high"};
    checkForInvalidProductImportanceValues(shippingList,validProductImportanceValues);
}

void checkForInvalidProductImportanceValues(const list<shipping_data>& list1, unordered_set<string> set)
{
    for (auto & it : list1)
    {
        if(set.find(it.product_importance) == set.end())
        {
            cout << "Invalid Product Importance Value: " << it.product_importance << " for ID: " << it.id << endl;
        }
    }
}

void printMainMenuOptions()
{
    cout << "Please enter your selection" << endl;
    cout << "\t 1. Linked List Features" << endl;
    cout << "\t 2. Vector Features" << endl;
    cout << "\t 3. Set Features" << endl;
    cout << "\t 4. Map Features" << endl;
}
void printLinkedListMenuOptions()
{
    cout << "Please enter your selection" << endl;
    cout << "\t 1. Display all elements" << endl;
    cout << "\t 2. Display front element" << endl;
    cout << "\t 3. Display last element" << endl;
    cout << "\t 4. Find element by ID" << endl;
    cout << "\t 5. Delete First Element" << endl;
    cout << "\t 6. Delete Last Element" << endl;
    cout << "\t 7. Delete Nth Element" << endl;
    cout << "\t 8. Insert an element at Nth position" << endl;
    cout << "\t 9. Count Customer Ratings that are less than 2" << endl;
    cout << "\t 10. Sort the Linked-List by customer Rating" << endl;
    cout << "\t 11. Return to Main Menu" << endl;
}
void printVectorMenuOptions()
{
    cout << "Please enter your selection" << endl;
    cout << "\t 1. Populate vector from Linked-List" << endl;
    cout << "\t 2. Display all elements" << endl;
    cout << "\t 3. Display element at position I" << endl;
    cout << "\t 4. Insert new record at position at 2" << endl;
    cout << "\t 5. Sort the vector by order of cost" << endl;
    cout << "\t 6. Sort in order by ID" << endl;
    cout << "\t 7. Display records where customer rating is less than 3" << endl;
    cout << "\t 8. Return to Main Menu" << endl;
}
void printMapMenuOptions()
{
    cout << "Please enter your selection" << endl;
    cout << "\t 1. Create a map from the contents of the linked list" << endl;
    cout << "\t 2. Search for a record by id " << endl;
    cout << "\t 3. Return to Main Menu" << endl;

}
void load(const string& fileName, list<shipping_data> &data)
{
    ifstream fin(fileName);

    if(fin)
    {
        string line;
        getline(fin, line); //Skip the first line
        while(getline(fin, line))
        {
            shipping_data shippingEntry;
            parseLine(line, shippingEntry);
            data.push_back(shippingEntry);
        }
        fin.close();
    }
    else
    {
        cout << "Error opening file." <<endl;
    }
}
void parseLine(const string& line,shipping_data &shippingEntry)
{

    string temp;
    stringstream ss(line);


    getline(ss, temp, ','); //temp = 1
    shippingEntry.id = stoi(temp);




    getline(ss, temp, ',');
    shippingEntry.warehouse_block = temp.at(0);

    getline(ss, shippingEntry.mode_of_shipment, ',');

    getline(ss, temp, ',');
    shippingEntry.customer_care_calls = stoi(temp);

    getline(ss, temp, ',');
    shippingEntry.customer_rating = stoi(temp);

    getline(ss, temp, ',');
    shippingEntry.cost_of_the_product = stoi(temp);

    getline(ss, temp, ',');
    shippingEntry.prior_purchases = stoi(temp);

    getline(ss,shippingEntry.product_importance,',');

    getline(ss, temp, ',');
    shippingEntry.gender = temp.at(0);

    getline(ss, temp, ',');
    shippingEntry.discount_offered = stoi(temp);

    getline(ss, temp, ',');
    shippingEntry.weight_in_gms = stoi(temp);

    getline(ss, temp, ',');
    if(temp!= "1")
    {
        shippingEntry.reached_on_time = false;
    }
    else
    {
        shippingEntry.reached_on_time = true;
    }

}
void display(const shipping_data &shippingEntry)
{
    cout << boolalpha;
    cout <<left
         << setw(6) << shippingEntry.id
         <<setw(4)  << shippingEntry.warehouse_block
         <<setw(8)  << shippingEntry.mode_of_shipment
         <<setw(4)  << shippingEntry.customer_care_calls
         <<setw(4)  << shippingEntry.customer_rating
         <<setw(5)  << shippingEntry.cost_of_the_product
         <<setw(3)  << shippingEntry.prior_purchases
         <<setw(8)  << shippingEntry.product_importance
         <<setw(3)  << shippingEntry.gender
         <<setw(5)  << shippingEntry.discount_offered
         <<setw(6)  << shippingEntry.weight_in_gms
         <<setw(5)  << shippingEntry.reached_on_time
         <<endl;
}
void displayLinkedList(list<shipping_data> &shippingList) {
    displayHeader();
    for(auto & iter : shippingList)
    {
        display(iter); //Dereference the iterator
    }
}

void displayHeader()
{
    cout <<left
         << setw(6) << "ID"
         <<setw(4)  << "WB"
         <<setw(8)  << "MOS"
         <<setw(4)  << "CCC"
         <<setw(4)  << "CR"
         <<setw(5)  << "COTP"
         <<setw(3)  << "PP"
         <<setw(8)  << "PI"
         <<setw(3)  << "G"
         <<setw(5)  << "DO%"
         <<setw(6)  << "WIG"
         <<setw(5)  << "ROT"
         <<endl;
}

void LinkedListMenu(list<shipping_data> &shippingList)
{
    bool quit = false;
    while(!quit)
    {
        printLinkedListMenuOptions();
        int choice;
        cin >> choice;
        switch(choice)
        {
            case 1:
                displayLinkedList(shippingList);
                break;
            case 2:
                displayHeader();
                display(shippingList.front());
                break;
            case 3:
                displayHeader();
                display(shippingList.back());
                break;
            case 4:
                cout << "Enter the ID to search for: " << endl;
                int id;
                cin >> id;
                for(auto & iter : shippingList)
                {
                    if(iter.id == id)
                    {
                        displayHeader();
                        display(iter);
                        break;
                    }
                }
                break;
            case 5:
                shippingList.pop_front();
                break;
            case 6:
                shippingList.pop_back();
                break;
            case 7:
                cout << "Enter the position to delete: " << endl;
                int pos;
                cin >> pos;
                if(pos < 0 || pos >= shippingList.size())
                {
                    cout << "Invalid position" << endl;
                }
                else
                {
                    auto iter = shippingList.begin();
                    for(int i = 0; i < pos; i++)
                    {
                        iter++;
                    }
                    shippingList.erase(iter);
                }
                break;
            case 8: {
                cout << "Enter the position to insert: " << endl;
                int position;
                cin >> position;
                shipping_data shippingEntry;
                shippingEntry = getShippingEntry(shippingEntry);
                if (position < 0 || position >= shippingList.size()) {
                    cout << "Invalid position" << endl;
                } else {
                    auto iter = shippingList.begin();
                    for (int i = 0; i < position; i++) {
                        iter++;
                    }
                    shippingList.insert(iter, shippingEntry);
                }
                break;
            }


            case 9:
            {
                int numberBelow2 = count_if(shippingList.begin(), shippingList.end(), [](shipping_data &s){return s.customer_rating < 2;}); // NOLINT(cppcoreguidelines-narrowing-conversions)
                cout << "Number of ratings below 2: " << numberBelow2 << endl;
                break;
            }

            case 10:
                shippingList.sort([](shipping_data &s1, shipping_data &s2){return s1.customer_rating < s2.customer_rating;});
                break;
            case 11:
                quit = true;
                break;
            default:
                cout << "Invalid choice" << endl;

        }
    }
}

shipping_data& getShippingEntry(shipping_data &shippingEntry) {
    cout << "Enter the following data: " << endl;
    cout << "ID: " << endl;
    cin >> shippingEntry.id;
    cout << "Warehouse Block: " << endl;
    cin >> shippingEntry.warehouse_block;
    cout << "Mode of Shipment: " << endl;
    cin >> shippingEntry.mode_of_shipment;
    cout << "Customer Care Calls: " << endl;
    cin >> shippingEntry.customer_care_calls;
    cout << "Customer Rating: " << endl;
    cin >> shippingEntry.customer_rating;
    cout << "Cost of the Product: " << endl;
    cin >> shippingEntry.cost_of_the_product;
    cout << "Prior Purchases: " << endl;
    cin >> shippingEntry.prior_purchases;
    cout << "Product Importance: " << endl;
    cin >> shippingEntry.product_importance;
    cout << "Gender: " << endl;
    cin >> shippingEntry.gender;
    cout << "Discount Offered: " << endl;
    cin >> shippingEntry.discount_offered;
    cout << "Weight in Gms: " << endl;
    cin >> shippingEntry.weight_in_gms;
    cout << "Reached on Time: " << endl;
    cin >> shippingEntry.reached_on_time;
    return shippingEntry;
}

void vectorMenu(list<shipping_data> &shippingList)
{
    vector<shipping_data> shippingVector;
    bool quit = false;
    while(!quit)
    {
        printVectorMenuOptions();
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                for(auto & iter : shippingList)
                {
                    shippingVector.push_back(iter);
                }
                break;
            case 2://Display
                displayHeader();
                displayVector(shippingVector);
                break;
            case 3:
                cout << "Enter the index position: " << endl;
                int index;
                cin >> index;
                if(index < 0 || index >= shippingVector.size())
                {
                    cout << "Invalid index" << endl;
                }
                else
                {
                    displayHeader();
                    display(shippingVector[index]);
                }
                break;
            case 4:
            {
                shipping_data shippingEntry;
                shippingVector.insert(shippingVector.begin() + 2, getShippingEntry(shippingEntry));
                break;
            }
            case 5:
                sort(shippingVector.begin(), shippingVector.end(), [](shipping_data &s1, shipping_data &s2){return s1.cost_of_the_product < s2.cost_of_the_product;});
                break;
            case 6://Sort the vector by id
                sort(shippingVector.begin(), shippingVector.end(), [](shipping_data &s1, shipping_data &s2){return s1.id < s2.id;});
                break;
            case 7 :
            {
                vector<shipping_data> shippingVector2;
                copy_if(shippingVector.begin(), shippingVector.end(), back_inserter(shippingVector2), [](shipping_data &s){return s.customer_rating < 3;});
                displayHeader();
                displayVector(shippingVector2);
                break;
            }
            case 8:
                quit = true;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

void displayVector(const vector<shipping_data>& vector1)
{
    for (const auto & i : vector1)
    {
        display(i);
    }

}
