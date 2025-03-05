#include "headerFiles\\admin.h"
#include "headerFiles\\common.h"
void admin()
{
    char pathext[] = "\\admin_users";
    int choice;
    cout << endl;
    cout << "\\\\\\\\\\-----Welcome Dear Admin-----/////" << endl
         << endl
         << "Please SignIn to continue" << endl
         << endl;

    cout << "For Signup Press 1" << endl
         << endl
         << "For Login Press 2" << endl
         << endl
         << "To Return to Main Menu press 3" << endl
         << endl
         << "To Exit Press 4" << endl
         << endl;

    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        if (Signin(pathext))
        {
            adminMenu();
        }
        else
        {
            admin();
        }
        break;
    }
    case 2:
    {
        if (login(pathext))
        {
            adminMenu();
        }
        else
        {
            admin();
        }
        break;
    }
    case 3:
    {
        mainMenu();
        break;
    }
    case 4:
    {
        cout << "---Exited---" << endl;
        break;
    }
    default:
    {
        cout << "Invalid Choice!" << endl
             << "Input again" << endl;
        break;
    }
    }
}
void adminMenu()
{
    // Employee main menu
    char choice;
    cout << endl;
    cout << "---------------ADMIN Menu------------------" << endl
         << endl

         << "Press 1 to see To modify Users" << endl
         << endl
         << "Press 2 to see To  Modify Invntory" << endl
         << endl
         << "Press 3 to See Generate Discounts" << endl
         << endl
         << "Press 4 for See your Activity Log" << endl
         << endl
         << "Press 5 for Customer Reports and Audits" << endl
         << endl
         << "Press 6 for Main Menu" << endl
         << endl
         << "---------------------------------------------" << endl
         << endl;

    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    // input validation
    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6')
    {
        cout << endl
             << "Invalid Choice!" << endl;
        cout << "Enter choice again: ";
        cin >> choice;
        cin.ignore();
    }

    switch (choice)
    {
    case '1':
    {
        modifyUsers(); // catalogue ko call kia
        break;
    }
    case '2':
    {
        Inventory(); // Wishlist dekhne ke liye
        break;
    }
    case '3':
    {
        Discounts(); // Order History Check karne ke liye
        break;
    }
    case '4':
    {
        Activitylog(); // Inquiries place karne ke liye
        break;
    }
    case '5':
    {
        ReportsandAudits(); // Program ko abrptly band na karne ke liye mainMenu call kia hai
        break;
    }
    case '6':
    {
        mainMenu();
        break;
    }
    default:
    {
        cout << "System Error!!!" << endl; // kuch bhi galti honay par wapis mainmenu pe jai ga
        mainMenu();
        break;
    }
    }
}
void modifyUsers()
{
    cout << "Feature Not added Yet" << endl;
    adminMenu();
}
void Inventory()
{
    int choice1;
    int pid;
    int i = 0, c = 0;
    // arrays to read catalog
    int id[200] = {0};
    int quantity[200] = {0};
    int price[200] = {0};
    char name[200][200] = {'\0'};
    char catagory[200][200] = {'\0'};

    // object to read and write catalogue
    ifstream catalogin;
    catalogin.open("textfiles\\catalog.txt", ios::in);
    while (catalogin >> id[i])
    {
        catalogin.ignore(1);
        catalogin.getline(name[i], 50, '[');
        catalogin >> price[i];
        catalogin.ignore(1);
        catalogin.getline(catagory[i], 15, ',');
        catalogin >> quantity[i];
        i++;
        c++; // total products counter
    }
    cout << "Press 1 to Add more product" << endl
         << endl
         << "Press 2 to Delete Product" << endl
         << endl
         << "Press 3 to edit specific Product" << endl
         << endl
         << "Press 4 to import BULK Quantity for product" << endl
         << endl;

    cout << "Enter your choice: ";
    cin >> choice1;
    cin.ignore();

    while (choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4) // input validation kia
    {
        cout << endl
             << "Invalid Choice!" << endl
             << endl;
        cout << "Enter choice again: ";
        cin >> choice1;
        cin.ignore();
    }
    if (choice1 == 1)
    {
        cout << "Enter Product ID (must be 3 digits +ve): ";
        cin >> id[c];
        cin.ignore();
        while (true)
        {
            if (id[c] < 100 || id[c] > 999)
            {
                cout << "Invalid ID! Must be a positive 3-digit number." << endl;
            }
            if (matchId(id[c], c, id) != -1)
            {
                cout << "ID already exists in the catalogue!" << endl;
            }
            else
            {
                break;
            }
            cout << "Enter Product ID (must be 3 digits +ve): ";
            cin >> id[c];
            cin.ignore();
        }
        cout << endl;
        cout << "Enter Product Name: ";
        cin.getline(name[c], 50, '\n');

        // name validation
        int namelen = 0;
        for (int i = 0; name[c][i] != '\0'; i++) // calculates the name lenght
        {
            namelen++;
        }
        if (namelen < 26) // agar name 26 se chota hua to end main spaces lagye ga to main the file reading and  writing format
        {
            for (i = namelen; i < 26; i++)
            {
                name[c][i] = ' ';
            }
            name[c][26] = '\0';
        }

        cout << "Enter Product Price: ";
        cin >> price[c];
        cin.ignore();
        while (price[c] < 0) // agar price 0 se kam ho gi toh re-input
        {
            cout << "Invalid Price!" << endl;
            cout << "Enter Product Price: ";
            cin >> price[c];
            cin.ignore();
        }

        cout << "Enter Product Catagory: ";
        cin.getline(catagory[c], 15, '\n');

        cout << "Enter Product Quantity: ";
        cin >> quantity[c];
        cin.ignore();
        while (quantity[c] < 0) // agar quantity 0 se kam ho gi toh re-input
        {
            cout << "Invalid Quantity!" << endl;
            cout << "Enter Product Quantity: ";
            cin >> quantity[c];
            cin.ignore();
        }
        c++;
        ofstream announce;
        announce.open("textfiles\\announcements.txt", ios::app);
        announce << "New product added!" << endl;
        announce << id[c] << "[" << name[c] << "]" << price[c] << " " << catagory[c] << "," << quantity[c] << endl
                 << endl;
        announce.close();
    }
    else if (choice1 == 2)
    {
        printHeader();

        // Catalogue print hogi
        i = 0;
        while (i < c)
        {
            cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
            i++;
        }
        cout << endl
             << endl;

        cout << "Enter Product ID which you want to delete: ";
        cin >> pid;
        cin.ignore();

        if (matchId(pid, c, id) == -1)
        {
            cout << "No match Found!, Product is not in the catalogue" << endl;
        }
        else
        {
            // agar exist karta hai to uss index se loop intitialze kar ke toh last tak chale gi, har aik index peechy aye ga urr last wala empty bach jaye ga, product auto remove ho je gi
            int p_index;
            p_index = matchId(pid, c, id);
            for (int j = p_index; j < c - 1; j++) // loop condition main se -1 isliye kia ke jab aik position pichy anna sab indexes ne toh last wala index empty reh jana.
            {
                id[j] = id[j + 1];
                copyarray(name[j], name[j + 1]);
                price[j] = price[j + 1];
                copyarray(catagory[j], catagory[j + 1]);
                quantity[j] = quantity[j + 1];
            }
            c--;
        }
    }
    else if (choice1 == 3)
    {
        int p_index;
        int pid;
        cout << "Enter the ID you want to edit: " << endl;
        cin >> pid;
        cin.ignore();
        if (matchId(pid, c, id) == -1)
        {
            cout << "Sorry, No match found!" << endl
                 << endl;
        }
        else
        {
            p_index = matchId(pid, c, id);
            cout << endl;

            cout << "Enter Product Name: ";
            cin.getline(name[p_index], 50, '\n');

            // name validation
            int namelen = 0;
            for (int i = 0; name[p_index][i] != '\0'; i++) // calculates the name lenght
            {
                namelen++;
            }
            if (namelen < 26) // agar name 26 se chota hua to end main spaces lagye ga to main the file reading and  writing format
            {
                for (i = namelen; i < 26; i++)
                {
                    name[p_index][i] = ' ';
                }
                name[p_index][26] = '\0';
            }

            cout << "Enter Product Price: ";
            cin >> price[p_index];
            cin.ignore();
            while (price[p_index] < 0) // agar price 0 se kam ho gi toh re-input
            {
                cout << "Invalid Price!" << endl;
                cout << "Enter Product Price: ";
                cin >> price[p_index];
                cin.ignore();
            }

            cout << "Enter Product Catagory: ";
            cin.getline(catagory[p_index], 15, '\n');

            cout << "Enter Product Quantity: ";
            cin >> quantity[p_index];
            cin.ignore();
            while (quantity[p_index] < 0) // agar quantity 0 se kam ho gi toh re-input
            {
                cout << "Invalid Quantity!" << endl;
                cout << "Enter Product Quantity: ";
                cin >> quantity[p_index];
                cin.ignore();
            }
        }
    }
    else if (choice1 == 4)
    {
        int choice1;
        int pid;
        int i = 0, c = 0;
        int p_index;
        // arrays to read catalog
        int id[200] = {0};
        int quantity[200] = {0};
        int price[200] = {0};
        char name[200][200] = {'\0'};
        char catagory[200][200] = {'\0'};

        // object to read and write catalogue
        ifstream catalogin;
        catalogin.open("textfiles\\catalog.txt", ios::in);
        while (catalogin >> id[i])
        {
            catalogin.ignore(1);
            catalogin.getline(name[i], 50, '[');
            catalogin >> price[i];
            catalogin.ignore(1);
            catalogin.getline(catagory[i], 15, ',');
            catalogin >> quantity[i];
            i++;
            c++; // total products counter
        }
        printHeader();

        // Catalogue print hogi
        i = 0;
        while (i < c)
        {
            cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
            i++;
        }
        cout << "Enter the ID of the product you want to BULK RE-STOCK: " << endl;
        cin >> pid;
        cin.ignore();

        p_index = matchId(pid, c, id);
        if (p_index == -1)
        {
            cout << "Sorry, No match found!" << endl
                 << endl;
        }
        else
        {
            quantity[p_index] += 100;
            cout << "Product Restocked!" << endl
                 << endl;
        }
        ofstream catalogout;
        catalogout.open("textfiles\\catalog.txt", ios::out); // file write mode main open

        // file ko write karra hai by loop
        for (int i = 0; i < c; i++)
        {
            catalogout << id[i] << "|" << name[i] << " [" << price[i] << "]" << catagory[i] << "," << quantity[i] << endl;
        }
        catalogout.close();

        adminMenu();
    }
    ofstream catalogout;
    catalogout.open("textfiles\\catalog.txt", ios::out); // file write mode main open

    // file ko write karra hai by loop
    for (int i = 0; i < c; i++)
    {
        catalogout << id[i] << "|" << name[i] << " [" << price[i] << "]" << catagory[i] << "," << quantity[i] << endl;
    }
    catalogout.close();
    adminMenu();
}
void Discounts()
{
    char per[3];
    char promocode[20] = "PROMODISC";
    cout << "\\\\\\------Discounts------/////" << endl;
    cout << "Enter the discount percentage: ";
    cin.getline(per, 3, '\n');
    cin.ignore();
    while (per[0] < 0 || per[1] < 0)
    { // percentage should be between 0 to 100
        cout << "Invalid Percentage!" << endl;
        cout << "Enter the discount percentage: ";
        cin.getline(per, 3, '\n');
        cin.ignore();
    }
    int i = 0, j = 0;
    while (promocode[i] != '\0')
    {
        i++;
    }
    while (per[j] != '\0')
    {
        promocode[i] = per[j];
        i++;
        j++;
    }
    cout << "Promocode: " << promocode << endl;
    ofstream announce;
    announce.open("textfiles\\announcements.txt", ios::app);
    announce << "Promocode added!" << endl;
    announce << promocode << endl;
    announce.close();
    ofstream promocodeout;
    promocodeout.open("textfiles\\promocode.txt", ios::app);
    promocodeout << promocode << endl;
    promocodeout.close();
    adminMenu();
}
void Activitylog()
{
    ifstream activityin;
    activityin.open("textfiles\\activitylog.txt", ios::in); // read and print the suspesious activies
    char ch[100];
    while (activityin.getline(ch, 100, '\n'))
    {
        cout << ch << endl;
    }
    activityin.close();
    adminMenu();
}
void ReportsandAudits()
{
    cout << "\\\\\\------Reports and Audits------/////" << endl
         << endl
         << "Press 1 to see Sales Report" << endl
         << endl
         << "Press 2 to see Revenue Report" << endl
         << endl
         << "Press 3 to see Stock Report" << endl
         << endl
         << "Press 4 to Security audit" << endl
         << endl
         << "Press 5 to make hourly graph" << endl
         << endl
         << "Press 6 to main menu" << endl
         << endl;

    char choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    // input validation
    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6')
    {
        cout << endl
             << "Invalid Choice!" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
    }
    if (choice == '1')
    {
        SalesReport();
    }
    else if (choice == '2')
    {
        RevenueReport();
    }
    else if (choice == '3')
    {
        StockReport();
    }
    else if (choice == '4')
    {
        SecurityAudit();
    }
    else if (choice == '5')
    {
        HourlyGraph();
    }
    else if (choice == '6')
    {
        adminMenu();
    }
    adminMenu();
}
void SalesReport()
{
    ifstream database;
    database.open("textfiles\\order.txt", ios::in);
    char ch[200];
    while (database.getline(ch, 100, '\n'))
    {
        cout << ch << endl;
    }
    database.close();
    adminMenu();
}
void RevenueReport()
{
    // order history ko read karne ke liye arrays
    char c_name[100][100] = {'\0'};
    int id[100] = {0};
    char name[100][100] = {'\0'};
    int price[100] = {0};
    char catagory[100][100] = {'\0'};
    int quantity[100] = {0};
    char timing[100][30] = {"\0"};

    fstream database;
    int i = 0;
    int c = 0;

    // database read kare ga in mode main opne kia
    database.open("textfiles\\order.txt", ios::in);

    while (database.getline(c_name[i], 50, '|'))
    {
        database >> id[i];
        database.ignore(1);
        database.getline(name[i], 100, '[');
        database >> price[i];
        database.ignore(1);
        database.getline(catagory[i], 50, ',');
        database >> quantity[i];
        database.getline(timing[i], 30, '\n');
        c++;
        i++;
    }

    database.close();

    int revenue = 0;
    i = 0;
    while (i < c)
    {
        revenue = revenue + price[i];
        i++;
    }

    cout << "-----------Total Revenue-----------" << endl;
    cout << endl
         << "Total Revenue: " << revenue << endl;
    cout << "------------------------------------" << endl;
    cout << endl
         << endl;
    adminMenu();
}
void StockReport()
{
    int id[200]; // catalogue ko read karne ke liye arrays
    char name[200][50];
    char catagory[200][50];
    int price[200];
    int quantity[200];
    ifstream catalogin;
    catalogin.open("textfiles\\catalog.txt", ios::in);
    int i = 0, c = 0;
    while (catalogin >> id[i])
    {
        catalogin.ignore(1);
        catalogin.getline(name[i], 50, '[');
        catalogin >> price[i];
        catalogin.ignore(1);
        catalogin.getline(catagory[i], 15, ',');
        catalogin >> quantity[i];
        i++;
        c++; // total products counter
    }

    // Catalogue print hogi
    i = 0;
    cout<<"------------------Stock Menu-----------------"<<endl<<endl;
    cout << "press 1 to see out of stock products" << endl
         << endl
         << "press 0 to see out of stock products" << endl
         << endl
         << "press 5 to see the low stock products" << endl
         << endl
         << "press 6 to go back to main menu" << endl
         << endl;
    cout<<"--------------------------------------------"<<endl;
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    while (choice != 1 && choice != 0 && choice != 5 && choice != 6)
    {
        cout << endl
             << "Invalid Choice!" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
    }
    // catalogue ka head print hoga

    if (choice == 1)
    {

        printHeader();
        i = 0;
        while (i < c)
        {
            if (quantity[i] >= choice)
            {
                cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                i++;
            }
        }
        cout << endl
             << endl;
    }
    if (choice == 0)
    {

        printHeader();
        i = 0;
        while (i < c)
        {
            if (quantity[i] == choice)
            {
                cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                i++;
            }
        }
        cout << endl
             << endl;
    }
    if (choice == 5)
    {

        printHeader();
        i = 0;
        while (i < c)
        {
            if (quantity[i] < choice)
            {
                cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                i++;
            }
        }
        cout << endl
             << endl;
    }
    if (choice == 6)
    {
        adminMenu();
    }
}
void SecurityAudit()
{
    cout << "-----------Security Audit-----------" << endl;
    ifstream activityin;
    activityin.open("textfiles\\activitylog.txt", ios::in); // suspesious activity read kare ga aur print kare ga
    char ch[100];
    while (activityin.getline(ch, 100, '\n'))
    {
        cout << ch << endl;
    }
    activityin.close();
    adminMenu();
}
void HourlyGraph()
{
    cout << "-----------Hourly Graph-----------" << endl;
    int i = 0;
    int hour[24] = {0};
    srand(time(0));
    for (i = 0; i < 24; i++)
    {
        hour[i] = rand() % 30;
    }
    int j = 0;
    for (i = 0; i < 24; i++)
    {
        cout << i + 1 << " |";
        for (j = 1; j <= hour[i]; j++)
        {
            cout << "-";
        }
        cout << endl;
    }
    cout << "  -----------------------------------------------------" << endl;
    adminMenu();
}