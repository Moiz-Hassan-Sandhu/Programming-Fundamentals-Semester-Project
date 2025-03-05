#include "headerFiles\\customer.h"
#include "headerFiles\\common.h"
void customer()
{
    //Customer login/signin
    char pathext[] = "\\customer_users";        //jab generic functions ko customer ke liye call karna ho tab use hoga
    int choice;
    cout << endl;

    cout << "--------------Welcome Dear customer--------------" << endl<<endl;
    cout << "For Signup Press 1" << endl<<endl
         << "For Login Press 2" << endl<<endl
         << "To Main Menu press 3" << endl<<endl
         << "To Exit Press 4" << endl<<endl;

    do {
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice < 1 || choice > 4)
        {
            cout << endl
                 << "Invalid Input!" << endl
                 << endl;
        }
    } while (choice < 1 || choice > 4);

    switch (choice)
    {
        case 1:
        {
            //Registering new customer
            if (Signin(pathext))    //bool signin ture return kare ga to customer signin ho jy ga
            {
                cout<<"Inside";
                customerMenu();
            }
            else                    // false kare ga toh fail
            {
                customer();
            }
            break;
        }
        case 2:
        {
            if (login(pathext))     //bool login ture return kare ga to customer login ho jy ga
            {
                cout << "Sucessfully Login" << endl;
                customerMenu();
            }
            else                    //false return kare ga to failed login attemtp hogi
            {
                cout << "Unsuccessfull Login" << endl;
                customer();
            }
            break;
        }
        case 3:
        {
            mainMenu();     //Program ko abrptly band na karne ke liye mainMenu call kia hai 
            break;
        }
        case 4:
        {
            cout << "---Exited---" << endl;     //program execution khatam ho jaye gi
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
void customerMenu()
{
    //Customer main menu
    char choice;
    cout << endl;
    cout<<"\\\\--------------Annoncemments------------//"<<endl;
    char announcement;
    ifstream announce;
    announce.open("textfiles\\announcements.txt");
    while(announce.get(announcement))
    {
        cout<<announcement;
    }
    announce.close();
    cout<<"-------------------------------------------"<<endl;
    cout<<"---------------Customer Menu------------------"<<endl<<endl
         << "Press 1 to see catalogue" << endl<<endl
         << "Press 2 to see Wishlist" << endl<<endl
         << "Press 3 to See Order History" << endl<<endl
         << "Press 4 for Incquires" << endl<<endl
         << "Press 5 for Main Menu" << endl<<endl;

    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    //input validation
    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5')
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
        Catalogue();    //catalogue ko call kia
        break;
    }
    case '2':
    {
        Wishlist();     //Wishlist dekhne ke liye
        break;
    }
    case '3':
    {
        orderHistory(); //Order History Check karne ke liye
        break;
    }
    case '4':
    {
        // c_Inquiries();   //Inquiries place karne ke liye
        customerMenu();
        break;
    }
    case '5':
    {
        mainMenu();     //Program ko abrptly band na karne ke liye mainMenu call kia hai
        break;
    }
    default:
    {
        cout << "System Error!!!" << endl;  //kuch bhi galti honay par wapis mainmenu pe jai ga
        mainMenu();
        break;
    }
    }
}
void Catalogue()
{
    int i = 0;  //index
    int c = 0;  //counter
    int f_choice = 0;   //filter choice ke liye

    //catalog ko read karne wali arrays
    int id[200];
    char name[200][40];
    char catagory[200][40];
    int price[200];
    int quantity[200];
    fstream catalog;    //catalogue ko read write karne ke liye object bnaya
    catalog.open("textfiles\\catalog.txt", ios::in);    //file read mode main open
    //file ko read karra hai by loop
    while (catalog >> id[i])
    {
        catalog.ignore(1);
        catalog.getline(name[i], 50, '[');
        catalog >> price[i];
        catalog.ignore(1);
        catalog.getline(catagory[i], 15, ',');
        catalog >> quantity[i];
        i++;
        c++;    //total products counter
    }

    //catalogue ka head print hoga
    printHeader();

    //Catalogue print hogi
    i = 0;
    while (i < c)
    {
        cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
        i++;
    }
    cout << endl
         << endl;
    //Filter options for Customer
    cout << "Do you want to filter Products?" << endl
         << endl
         << "Press 1 for filter by Catagory" << endl
         << endl
         << "Press 2 for filter by Price Range" << endl
         << endl
         << "Press 3 for filter by Availbility" << endl
         << endl
         << "Press 4 for Full catalog" << endl;
    cout << "Enter your choice: ";
    cin >> f_choice;
    cin.ignore();
    //Input validation
    while (f_choice != 1 && f_choice != 2 && f_choice != 3 && f_choice != 4)
    {
        cout << endl
             << "Invalid Choice!" << endl;
        cout << "Enter your choice again: ";
        cin >> f_choice;
        cin.ignore();
    }

    switch (f_choice)
    {
        case 1:
        {
            char f_category[20] = "";
            cout << "Enter the catagory You want: ";
            cin.getline(f_category, 20, '\n');
            i = 0;
            printHeader();
            while (i < c)
            {
                if (isArraySame(f_category, catagory[i]))
                {
                    cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                }
                i++;
            }
            break;
        }
        case 2:
        {
            int min;
            int max;
            cout << "Enter the min price: ";
            cin >> min;
            cin.ignore();
            while (min < 0)
            {
                cout << "Enter positive number: " << endl;
                cout << "Enter the min price: ";
                cin >> min;
                cin.ignore();
            }
            cout << "Enter the max price: ";
            cin >> max;
            cin.ignore();
            while (max < 0)
            {
                cout << "Enter positive number and enter value greater than the minimum price: " << endl;
                cout << "Enter the max price: ";
                cin >> max;
                cin.ignore();
            }
            i = 0;
            printHeader();
            while (i < c)
            {
                if (price[i] >= min && price[i] <= max)
                {
                    cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                }
                i++;
            }
            break;
        }
        case 3:
        {
            i = 0;
            printHeader();
            while (i < c)
            {
                if (quantity[i] != 0)
                {
                    cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                }
                i++;
            }
            break;
        }
        case 4:
        {
            i = 0;
            printHeader();
            while (i < c)
            {
                cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
                i++;
            }
            break;
        }
    }
    cout << endl
         << endl
         << endl;
    int choice;
    fstream create; // creating the usercart
    create.open("textfiles\\usercart.txt", ios::out);
    create.close();

    int c_c = 0;     // to count the poducts stored in the cart
    int p_index = 0; // to store the returned index from the match id function
    int c_index;     // to store the returned cart index form the match id function
    int pid;         // Product id entered by the customer

    //cart read karne ke liye
    int c_id[100] = {0};
    char c_name[100][100] = {'\0'};
    int c_price[100] = {0};
    char c_catagory[100][100] = {'\0'};
    int c_quantity[100] = {0};
    
    //Add to Cart
    do{
        int choice;

        //file objects
        ifstream cartin;    //read ke liye
        ofstream cartout;   //write ke liye
        cartin.open("textfiles\\usercart.txt");     //cart in mode main open kia read ke liye
        i = 0;

        while (cartin >> c_id[i])
        {
            c_c++;
            cartin.ignore(1);
            cartin.getline(c_name[i], 50, '[');
            cartin >> c_price[i];
            cartin.ignore(1);
            cartin.getline(c_catagory[i], 15, ',');
            cartin >> c_quantity[i];
            i++;
        }

        cartin.close();     //cart close kia
        cout << endl
             << endl
             << endl;

        cout << "Enter the Id you want to add to cart: ";   //jo id add karni woh input kia
        cin >> pid;
        cin.ignore();

        p_index = matchId(pid, c, id);      //jis index pe id match hogi woh index return aye ga // agar nai hoga match to -1 return karega

        if (p_index == -1) // if p_index=-1 means the product is not in the catalogue
        {
            cout << "No match found, Enter the correct Product" << endl
                 << endl;
        }

        else if (quantity[p_index] == 0) // if quantity [p_index]=0 means the product exist in the catalog but with 0 quantitity available
        {
            cout << "Product is out od stock!, We will refill soon" << endl
                 << endl;
        }

        else if (quantity[p_index] > 0)         //agar quantity 0 se ziada ho toh following body execute hoga
        {
            quantity[p_index]--;                 //catalog main se aik minus hoga jo product main cart main add karu ga

            cout << "Product added to your cart:    ";      //jo product add kia hoga usko print kia
            cout << setw(5) << "ID:   " << id[p_index] << setw(15) << "Name:   " << name[p_index] << setw(10) << "Price:    " << price[p_index] << endl
                 << endl;

            c_index = matchId(pid, c_c, c_id);  //jo product cart main pe hoga uske liye index return karega    //agar nai hoga toh  -1 return aye ga

            if (c_index != -1)                  // if c_index = -1, it means the product is already in cart in certain quantity
            {
                c_quantity[c_index]++;
                c_price[c_index] = price[p_index] * c_quantity[c_index];
            }
            else
            {
                // agar product pehly se exist nai karrta toh jo user ne jo product id enter ki ho gi woh id wala product cart wali arrays ke last index (c_c) pe ajye ga.
                c_id[c_c] = id[p_index];
                copyarray(c_name[c_c], name[p_index]);
                c_price[c_c] = price[p_index];
                copyarray(c_catagory[c_c], catagory[p_index]);
                c_quantity[c_c] = 1;
                c_c++; // c_C main 1 increment kia ta ke isko as max product count ke taur pe istemal kar saken.
            }
        }
        do{
            cout << "Press 1 to continue shopping" << endl<<endl
                 << "Press 2 to checkout" << endl<<endl;

            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            if (choice != 1 && choice != 2)
            {
                cout << "Invalid Choice! Enter again" << endl
                     << endl;
            }
            
        } while (choice != 1 && choice != 2);       //input validation
        
        if (choice == 2)
        {
            break;
        }

    } while (choice != 2);  //agar choice 2 hoga toh loop break ho jaye ga

    cout << endl << endl;

    //customer ka cart display hoga
    cout << "Your cart: " << endl << endl;
    printHeader();

    for (i = 0; i < c_c; i++)
    {
        cout << "  " << c_id[i] << "       " << c_name[i] << "  " << setw(5) << c_price[i] << "        " << setw(15) << c_catagory[i] << setw(14) << c_quantity[i] << endl;
    }

    cout << endl << endl;
    cout << "Press 1 to remove any product form the cart" << endl
         << "Press 2 to Checkout" << endl;
    cout << "Enter choice: ";
    int r_choice; // remove choice
    cin >> r_choice;
    cin.ignore();

    if (r_choice == 1)
    {
        do
        {
            cout << "Enter the Id you want to remove from cart: ";      //jo id remove karwana hai woh input lia
            cin >> pid;
            cin.ignore();

            p_index = matchId(pid, c, id);          
            c_index = matchId(pid, c_c, c_id);

            if (c_index == -1)      // if c_index=-1 means the product is not in the cart
            {
                cout << "No match found, Enter the correct Product" << endl
                     << endl;
            }
            else if (c_index != -1)     //agar c_index -1 nai toh product cart main hoga
            {
                quantity[p_index]++;        //jo product customer remove kare ga cart se woh catalog main wapis jaye ga
                cout << "Product removed from your cart:    ";
                cout << setw(5) << "ID:   " << id[p_index] << setw(15) << "Name:   " << name[p_index] << setw(10) << "Price:    " << price[p_index] << endl << endl;
                c_index = matchId(pid, c_c, c_id);

                if (c_quantity[c_index] > 1)    // agar cart main quantity aik se ziada hogi toh following code chale ga
                {
                    c_quantity[c_index]--;
                    c_price[c_index] = price[p_index] * c_quantity[c_index];
                }
                else    //agar 1 ho gi toh following code chale ga
                {
                    // agar product pehly se exist nai karrta toh jo user ne jo product id enter ki ho gi woh automatically remove ho jaye gi
                    // Explained:
                    // jo id match kare gi uske index se loop start ho ho urr us index se agge jo bhi products hongi woh aik indexx pichy a jaye gi
                    // jo product matched product ke bilkul agle index pe ho gi woh matched product ke index pe ajey gi and so on next products bhi.
                    // end main jo counter hoga woh 1 se decrement ho jy ga.

                    for (int j = c_index; j < c_c - 1; j++) // loop condition main se -1 isliye kia ke jab aik position pichy anna sab indexes ne toh last wala index empty reh jana.
                    {
                        c_id[j] = c_id[j + 1];
                        copyarray(c_name[j], c_name[j + 1]);
                        c_price[j] = c_price[j + 1];
                        copyarray(c_catagory[j], c_catagory[j + 1]);
                        c_quantity[j] = c_quantity[j + 1];
                    }
                    c_c--; // c_c main 1 decrement kia ta ke isko as max product count ke taur pe istemal kar saken.
                }
            }
            do{
                cout << "Press 1 to Remove More" << endl
                     << "Press 2 to checkout" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice != 1 && choice != 2)
                {
                    cout<< endl << "Invalid Choice! Enter again" << endl << endl;
                }
            } while (choice != 1 && choice != 2);   //input validation

            if (choice == 2)
            {
                break;
            }

        } while (choice != 2);      //agar choice 2 hogi toh loop break ho jaye ga
    }

    //catalog ko re write kare ga to update the quantities
    catalog.open("textfiles\\catalog.txt", ios::out); // sari catalog file ko out mode main open kar ke dobara write karwa dia
    for (i = 0; i < c; i++) {
        catalog << id[i] << "|" << name[i] << "[" << price[i] << "]" << catagory[i] << "," << quantity[i] << endl; // ussi format main wite kia ta ke read karne main assani ho urr standard maintain ho
    }
    catalog.close();

    //customer_cart main write kar dia to checkout
    ofstream cartout("textfiles\\usercart.txt", ios::out); // sari usercart file ko out mode main open kar ke dobara write karwa dia
    for (i = 0; i < c_c; i++) {
        cartout << c_id[i] << "|" << c_name[i] << "[" << c_price[i] << "]" << c_catagory[i] << "," << c_quantity[i] << endl; // ussi format main wite kia ta ke read karne main assani ho urr standard maintain ho
    }
    cartout.close();

    order();
}
void order()
{
    //checkout urr order place ke liye
    int total = 0;  //total price
    int p_code;     //promocode
    
    //file ko read karne ke liye
    int c_c = 0;
    int c_id[100] = {0};
    char c_name[100][100] = {'\0'};
    int c_price[100] = {0};
    char c_catagory[100][100] = {'\0'};
    int c_quantity[100] = {0};

    //objects file handling
    ifstream cartin;    //cart read kare ga
    ofstream database;  //order.txt main record ke liye

    //cart read kare ga
    cartin.open("textfiles\\usercart.txt");
    int i = 0;

    while (cartin >> c_id[i])
    {
        c_c++;
        cartin.ignore(1);
        cartin.getline(c_name[i], 50, '[');
        cartin >> c_price[i];
        cartin.ignore(1);
        cartin.getline(c_catagory[i], 15, ',');
        cartin >> c_quantity[i];
        i++;
    }
    cartin.close();
    
    //cart print kare ga
    cout << "Your cart: " << endl
         << endl;
    printHeader();
    for (i = 0; i < c_c; i++)
    {
        cout << "  " << c_id[i] << "       " << c_name[i] << "  " << setw(5) << c_price[i] << "        " << setw(15) << c_catagory[i] << setw(14) << c_quantity[i] << endl;
    }

    cout << endl << endl;
    
    //total price calculate kare ga
    i = 0;
    while (i < c_c)
    {
        total += c_price[i];
        i++;
    }
    int temp = total;
    char promos[50][20]={'\0'};
    ifstream promoin;
    promoin.open("textfiles\\promocode.txt");
    int c=0;
    while (promoin.getline(promos[i], 20, '\n'))
    {
        c++;
    }
    promoin.close();
    cout<<"available promo codes"<<endl;
    i=0;
    while (i < c)
    {
        cout<<i+1<<": "<<promos[i]<<endl;
        i++;
    }
    bool valid;
    cout<<"Enter the promode code number: ";
    char inpromo[20]="";
    cin.getline(inpromo, 20, '\n');
    while(i<c)      //input validation
    {
        if(isArraySame(inpromo, promos[i]))
        {
            valid=true;
            break;
        }
        else
        {   
            valid=false;
        }
        i++;
    }
    if(valid)
    {
        double per=0;
        per= 10 * (promos[i][9] - '0');     //extracts the 2nd last charachter which would probably be the first digit of the discount and stores int the int per.
        per= per + (promos[i][10] - '0');   //extract the last charachter which would probably be the second digit of the discount and stores it int the in per.
        total = total - (total * per / 100);
    }
    double tax = 0;
    tax = (double)total * 0.05;
    cout << endl << endl;
    cout << "-------------Recipt---------------" << endl;
    cout << "Total before discount: " << temp << endl<<endl;
    cout <<"Total After Promocode"<<promos[i]<<": "<<total<<endl<<endl;
    cout << "Total tax applied: " << tax << endl<<endl;
    cout << "Total after tax: " << total + tax << endl<<endl;
    cout << "----------------------------------" << endl<<endl;
    cout<<"Your order have been placed to your address, Will reach you in 2-3 working days"<<endl
        <<"Thanks for Visiting our store"<<endl<<endl;
    time_t now = time(nullptr);     //for storing the record wtih time 

    //order.txt main write kar dia record cart ka with user name
    database.open("textfiles\\order.txt", ios::app);
    for (i = 0; i < c_c; i++)
    {
        database << username << "|" << c_id[i] << "|" << c_name[i] << "[" << c_price[i] << "]" << c_catagory[i] << "," << c_quantity[i] << "|" << ctime(&now); // ussi format main wite kia ta ke read karne main assani ho urr standard maintain ho
    }
    database.close();

    remove("textfiles\\usercart.txt");  //usercart ko remove kar dega
    customerMenu();     //to continue customerMenu mian wapis bhaij dia
}
void Wishlist()
{
    char choice;

    // catalog variables and arrays
    int c = 0, i = 0;
    int id[200] = {0};
    char name[200][200] = {'\0'};
    char catagory[200][200] = {'\0'};
    int price[200] = {0};
    int quantity[200] = {0};

    // wishlist variables and arrays
    int w_c = 0, w_i = 0;
    char id_name[100][100] = {'\0'};
    int w_id[100] = {0};
    char w_name[100][100] = {'\0'};
    int w_price[100] = {0};
    char w_catagory[100][100] = {'\0'};
    int w_quantity[100] = {0};

    //object for filehandling
    fstream catalog;
    catalog.open("textfiles\\catalog.txt", ios::in);       //catalog ko read karwaya
    while (catalog >> id[i])
    {
        catalog.ignore(1);
        catalog.getline(name[i], 50, '[');
        catalog >> price[i];
        catalog.ignore(1);
        catalog.getline(catagory[i], 15, ',');
        catalog >> quantity[i];
        i++;
        c++;
    }

    //object for filehandling
    fstream seewish;    //wishlist read karwane ke liye
    seewish.open("textfiles\\wishlist.txt", ios::in);

    i = 0;
    while (seewish.getline(id_name[i], 50, '|'))
    {
        seewish >> w_id[i];
        seewish.ignore(1);
        seewish.getline(w_name[i], 100, '[');
        seewish >> w_price[i];
        seewish.ignore(1);
        seewish.getline(w_catagory[i], 50, ',');
        seewish >> w_quantity[i];
        seewish.ignore(1);
        w_c++;      //wish count kare ga
        i++;
    }

    if (w_c == 0)   //agar wishlist empty hogi 
    {
        cout << "No items in wishlist" << endl;
    }
    else    //empty nahi hoga
    {
        //exisiting wishlist print hoga
        cout << "Your Wishlist: " << endl
             << endl;
        printHeader();
        for (i = 0; i < w_c; i++)
        {
            if (isArraySame(username, id_name[i]))
            {
                cout << "  " << w_id[i] << "       " << w_name[i] << "  " << setw(5) << w_price[i] << "        " << setw(15) << w_catagory[i] << setw(14) << w_quantity[i] << endl;
            }
        }
    }
    cout << endl
         << endl;
    cout << "Press 1 to add products to Wishlist" << endl
         << endl;
    cout << "Press 2 to remove products from Wishlist" << endl
         << endl;
    cout << "Press 3 to Exit" << endl
         << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    while (choice != '1' && choice != '2' && choice != '3')
    {
        cout << endl
             << "Invalid Input!" << endl
             << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
    }
    if (choice == '1')
    {
        cout << "--------------------------------------Catalogue----------------------------------" << endl;
        i = 0;
        printHeader();
        while (i < c)
        {
            cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
            i++;
        }

        char a_choice; // ask user to add more to cart or checkout
        int pid;
        int p_index;
        int w_index;
        do
        {
            ifstream wishin;
            ofstream wishout;
            wishin.open("textfiles\\wishlist.txt", ios::in);
            w_c = 0;
            i = 0;
            while (seewish.getline(id_name[i], 50, '|'))
            {
                wishin >> w_id[i];
                wishin.ignore(1);
                wishin.getline(w_name[i], 100, '[');
                wishin >> w_price[i];
                wishin.ignore(1);
                wishin.getline(w_catagory[i], 50, ',');
                wishin >> w_quantity[i];
                w_c++;
                i++;
            }

            wishin.close();
            cout << endl
                 << endl
                 << endl;
            cout << "Enter the Id you want to add to Wishlist: ";
            cin >> pid;
            cin.ignore();
            w_index = matchId(pid, w_c, w_id);
            if (w_index == -1) // agar  product wishlist main nai toh -1 return aye ga
            {
                // agar nai hai tabhi add hosakta
                // agar pehle se hai toh add nai karna
                p_index = matchId(pid, c, id);
                if (p_index == -1) // agar product catalog main nai hai to -1 return aye ga
                {
                    cout << "No match found, Enter the correct Product" << endl
                         << endl;
                }
                else
                {
                    //wishlist main by id last main product add kardega
                    wishout.open("textfiles\\wishlist.txt", ios::app);
                    wishout << username << "|" << id[p_index] << "|" << name[p_index] << "[" << price[p_index] << "]" << catagory[p_index] << "," << 1 << endl;
                    cout << "Product added to your Wishlist:    ";
                    cout << setw(5) << "ID:   " << id[p_index] << setw(15) << "Name:   " << name[p_index] << setw(10) << "Price:    " << price[p_index] << endl
                         << endl;
                    wishout.close();
                }
            }
            else // agar product pehly se hai toh uska index return aye ga
            {
                // uski quanitity ko modify karne ki zarurat nai kiun ke ye wishlist hai
                cout << "Product already in your Wishlist";
            }
            do {
                cout << "Press 1 to Add more in your Wishlist" << endl<<endl
                     << "Press 2 to Remove from your Wishlist" << endl<<endl
                     << "Press 3 to Checkout" << endl<<endl;

                cout << "Enter your choice: ";
                cin >> a_choice;
                cin.ignore();

                if (a_choice != '1' && a_choice != '2' && a_choice != '3')
                {
                    cout << "Invalid Choice! Enter again" << endl
                         << endl;
                }
            } while (a_choice != '1' && a_choice != '2' && a_choice != '3');    //input validation
            if (a_choice == '2')    
            {
                choice = '2';
                break;
            }
            else if (a_choice == '3')
            {
                choice = '3';
                break;
            }
        } while (a_choice != '2' && a_choice != '3');   //loop terminate ho jaya agar 2 ya 3 ho a_choice
    }
    if (choice == '2')
    {
        //remove from wishlist
        char rem_choice;
        int pid;
        int p_index;
        int w_index;

        //objects for filehandling
        ifstream wishin;    //read wishlist
        ofstream wishout;   //remove wishlist

        //wishlist read kare ga
        wishin.open("textfiles\\wishlist.txt", ios::in);
        w_c = 0;

        i = 0;
        while (wishin.getline(id_name[i], 50, '|'))
        {
            wishin >> w_id[i];
            wishin.ignore(1);
            wishin.getline(w_name[i], 100, '[');
            wishin >> w_price[i];
            wishin.ignore(1);
            wishin.getline(w_catagory[i], 50, ',');
            wishin >> w_quantity[i];
            wishin.ignore(1);
            w_c++;
            i++;
        }
        wishin.close();
        cout << endl << endl;

        //wishlist print kare ga
        cout << "Your Wishlist: " << endl
             << endl;
        printHeader();
        for (i = 0; i < w_c; i++)
        {
            if (isArraySame(username, id_name[i]))
            {
                cout << "  " << w_id[i] << "       " << w_name[i] << "  " << setw(5) << w_price[i] << "        " << setw(15) << w_catagory[i] << setw(14) << w_quantity[i] << endl;
            }
        }
        cout << endl << endl;

        cout << "Press 1 to remove any product form the cart" << endl<<endl
             << "Press 2 to Exit" << endl<<endl;

        cout << "Enter choice: ";
        int r_choice; // remove choice
        cin >> r_choice;
        cin.ignore();

        if (r_choice == 1)
        {   //remove karna hai
            do {
                cout << "Enter the Id you want to remove from cart: ";  //remove by id ke liye
                cin >> pid;
                cin.ignore();

                cout << endl;

                p_index = matchId(pid, c, id);
                w_index = matchId(pid, w_c, w_id);
                
                if (w_index == -1) // if c_index=-1 means the product is not in the cart
                {
                    cout << "No match found, Enter the correct Product" << endl
                         << endl;
                }
                else if (w_index != -1)     //agar -1 nai hai toh product wihslist main hoga usko remove karna hai
                {
                    cout << "Product removed from your cart:    ";      //jo product remove karna hoga karwye ga
                    cout << setw(5) << "ID:   " << id[p_index] << setw(15) << "Name:   " << name[p_index] << setw(10) << "Price:    " << price[p_index] << endl<< endl;
                    // jo id match kare gi uske index se loop start ho ho urr us index se agge jo bhi products hongi woh aik indexx pichy a jaye gi
                    // jo product matched product ke bilkul agle index pe ho gi woh matched product ke index pe ajey gi and so on next products bhi.
                    // end main jo counter hoga woh 1 se decrement ho jy ga.

                    for (int j = w_index; j < w_c - 1; j++)
                    {
                        w_id[j] = w_id[j + 1];
                        copyarray(w_name[j], w_name[j + 1]);
                        w_price[j] = w_price[j + 1];
                        copyarray(w_catagory[j], w_catagory[j + 1]);
                    }
                    w_c--; // w_c main 1 decrement kia ta ke isko as max product count ke taur pe istemal kar saken.
                }
                do{
                    cout << "Press 1 to Remove More" << endl
                         << endl
                         << "Press 2 to checkout" << endl
                         << endl;

                    cout << "Enter your choice: ";
                    cin >> rem_choice;
                    cin.ignore();

                    if (rem_choice != '1' && rem_choice != '2')
                    {
                        cout << endl
                             << "Invalid Choice! Enter again" << endl
                             << endl;
                        cout << endl
                             << endl;
                    }

                } while (rem_choice != '1' && rem_choice != '2');       //input validation

                if (rem_choice == '2')
                {
                    break;
                }
            } while (rem_choice != '2');
        }

        //wishlist ko write kar dega //out mode main previous data remove ho jaye ga
        wishout.open("textfiles\\wishlist.txt", ios::out); // sari usercart file ko out mode main open kar ke dobara write karwa dia
        for (i = 0; i < w_c; i++)
        {
            wishout << id_name[i] << "|" << w_id[i] << "|" << w_name[i] << "[" << w_price[i] << "]" << w_catagory[i] << "," << 1 << endl;
        }
        wishout.close();

    }
    if (choice == '3')
    {
        customerMenu();
    }
    customerMenu();     //customer Menu main wapis bhaij de ga
}
void orderHistory()
{
    //order history ko read karne ke liye arrays
    char c_name[100][100] = {'\0'};
    int id[100] = {0};
    char name[100][100] = {'\0'};
    int price[100] = {0};
    char catagory[100][100] = {'\0'};
    int quantity[100] = {0};
    char timing[100][30] = {"\0"};

    //object to read data base
    fstream database;
    int i = 0;
    int c = 0;

    //database read kare ga in mode main opne kia
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

    i = 0;

    //order history print kare ga
    printHeader();
    while (i < c)
    {
        if (isArraySame(username, c_name[i]))
        {
            cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
        }
        i++;
    }

    cout << endl << endl;

    char choice;
    cout << "Do You want to add feedback/review? Press 1" << endl;
    cout << "Or Press 2 to Exit: ";
    cin >> choice;
    cin.ignore();

    while (choice != '1' && choice != '2')  //input validation
    {
        cout << "Invalid Input!" << endl;
        cout << "Enter again: ";
        cin >> choice;
        cin.ignore();
    }

    if (choice == '1')  //feeback input urr store kare ga
    {
        int count = 0;
        char feedback[1000] = "";
        cout << "Enter Your Feedback";
        cin.getline(feedback, 1000, '\n');

        //customer ka feedback ko name ke sath write kare ga
        fstream storefeed;
        storefeed.open("textfiles\\feedback.txt", ios::app);
        storefeed << username << '|' << feedback <<"|"<<username<<endl;
        storefeed.close();
    }
    else
    {
        customerMenu();     //customer menu main wapis bhej dega
    }
}