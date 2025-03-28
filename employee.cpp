#include"headerFiles\\employee.h"
#include"headerFiles\\common.h"

int points;
void employee()
{
    char pathext[]="\\employee_users";
    int choice;
    cout<<endl;
    cout<<"\\\\\\\\\\-----Welcome Dear Employee-----/////"<<endl<<endl
        <<"Please SignIn to continue"<<endl<<endl;

    cout<<"For Signup Press 1"<<endl<<endl
        <<"For Login Press 2"<<endl<<endl
        <<"To Return to Main Menu press 3"<<endl<<endl
        <<"To Exit Press 4"<<endl<<endl;

    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            if(Signin(pathext))
            {
                employeeMenu();
            }
            else
            {
                employee();
            }
            break;
        }
        case 2:
        {
            if(login(pathext))
            {
                cout<<"Sucessfully Login"<<endl;
                employeeMenu();
            }
            else
            {
                cout<<"Unsuccessfull Login"<<endl;
                employee();
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
            cout<<"---Exited---"<<endl;
            break;
        }
        default:
        {
            cout<<"Invalid Choice!"<<endl
                <<"Input again"<<endl;
            break;
        }
    }
}
void employeeMenu()
{
    //Employee main menu
    char choice;
    cout << endl;
    cout<<"---------------Employee Menu------------------"<<endl<<endl

         << "Press 1 to see Customer Queries" << endl<<endl
         << "Press 2 to see To Edit Catalogue" << endl<<endl
         << "Press 3 to See Stock Alerts" << endl<<endl
         << "Press 4 for See your Contribution" << endl<<endl
         << "Press 5 for Customer Feedback" << endl<<endl
         << "Press 6 for Main Menu"<<endl<<endl
         <<"---------------------------------------------"<<endl<<endl;

    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    //input validation
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
        customerQueries();    //catalogue ko call kia
        break;
    }
    case '2':
    {
        editCatalogue();     //Wishlist dekhne ke liye
        break;
    }
    case '3':
    {
        stockAlerts(); //Order History Check karne ke liye
        break;
    }
    case '4':
    {
        contribution();   //Inquiries place karne ke liye
        break;
    }
    case '5':
    {
        feedbackResponse();     //Program ko abrptly band na karne ke liye mainMenu call kia hai
        break;
    }
    case '6': 
    {
        mainMenu();
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
void customerQueries()
{

}
void editCatalogue()
{
    int choice1;
    int pid;
    int i=0, c=0;
    //arrays to read catalog
    int id[200]={0};
    int quantity[200]={0};
    int price[200]={0};
    char name[200][200]={'\0'};
    char catagory[200][200]={'\0'};

    //object to read and write catalogue
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
        c++;    //total products counter
    }
    cout<<"Press 1 to Add more product"<<endl<<endl
        <<"Press 2 to Delete Product"<<endl<<endl
        <<"Press 3 to edit specific Product"<<endl<<endl
        <<"Press 4 to Exit"<<endl<<endl;

    cout<<"Enter your choice: ";
    cin>>choice1;
    cin.ignore();

    while (choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4)    //input validation kia
    {
        cout << endl << "Invalid Choice!" << endl<<endl;
        cout << "Enter choice again: ";
        cin >> choice1;
        cin.ignore();
    }
    if(choice1==1)
    {
        cout<<"Enter Product ID (must be 3 digits +ve): ";
        cin>>id[c];
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
        cout<<"Enter Product ID (must be 3 digits +ve): ";
        cin>>id[c];
        cin.ignore();
    }
    cout<<endl;
    cout<<"Enter Product Name: ";
    cin.getline(name[c], 50, '\n');
        
    //name validation
    int namelen=0;
    for(int i=0; name[c][i]!='\0'; i++)     //calculates the name lenght
    {
        namelen++;
    }
    if(namelen<26)  //agar name 26 se chota hua to end main spaces lagye ga to main the file reading and  writing format
    {
        for(i=namelen; i<26; i++)
        {
            name[c][i]=' ';
        }
        name[c][26]='\0';
    }


    cout<<"Enter Product Price: ";
    cin>>price[c];
    cin.ignore();
    while(price[c]<0)   //agar price 0 se kam ho gi toh re-input
    {
        cout<<"Invalid Price!"<<endl;
        cout<<"Enter Product Price: ";
        cin>>price[c];
        cin.ignore();
    }

        cout<<"Enter Product Catagory: ";
        cin.getline(catagory[c], 15, '\n');

        cout<<"Enter Product Quantity: ";
        cin>>quantity[c];
        cin.ignore();
        while(quantity[c]<0)   //agar quantity 0 se kam ho gi toh re-input
        {
            cout<<"Invalid Quantity!"<<endl;
            cout<<"Enter Product Quantity: ";
            cin>>quantity[c];
            cin.ignore();
        }
        c++;
        ofstream announce;
        announce.open("textfiles\\announcements.txt", ios::app);
        announce<<"New product added!"<<endl;
        announce<<id[c]<<"["<<name[c]<<"]"<<price[c]<<" "<<catagory[c]<<","<<quantity[c]<<endl<<endl;
        announce.close();
    }
    else if(choice1==2)
    {
        printHeader();

        //Catalogue print hogi
        i = 0;
        while (i < c)
        {
            cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
            i++;
        }
        cout << endl<< endl;

        cout<<"Enter Product ID which you want to delete: ";
        cin>>pid;
        cin.ignore();

        if(matchId(pid, c, id)==-1)
        {
            cout<<"No match Found!, Product is not in the catalogue"<<endl;
        }
        else
        {
            //agar exist karta hai to uss index se loop intitialze kar ke toh last tak chale gi, har aik index peechy aye ga urr last wala empty bach jaye ga, product auto remove ho je gi
            int p_index;
            p_index=matchId(pid, c, id);
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
    else if(choice1==3)
    {
        int p_index;
        int pid;
        cout<<"Enter the ID you want to edit: "<<endl;
        cin>>pid;
        cin.ignore();
        if(matchId(pid, c, id)==-1)
        {
            cout<<"Sorry, No match found!"<<endl<<endl;
        }
        else
        {
            p_index=matchId(pid, c, id);
            cout<<endl;

            cout<<"Enter Product Name: ";
            cin.getline(name[p_index], 50, '\n');
        
            //name validation
            int namelen=0;
            for(int i=0; name[p_index][i]!='\0'; i++)     //calculates the name lenght
            {
                namelen++;
            }
            if(namelen<26)  //agar name 26 se chota hua to end main spaces lagye ga to main the file reading and  writing format
            {
                for(i=namelen; i<26; i++)
                {
                    name[p_index][i]=' ';
                }
                name[p_index][26]='\0';
            }

            cout<<"Enter Product Price: ";
            cin>>price[p_index];
            cin.ignore();
            while(price[p_index]<0)   //agar price 0 se kam ho gi toh re-input
            {
                cout<<"Invalid Price!"<<endl;
                cout<<"Enter Product Price: ";
                cin>>price[p_index];
                cin.ignore();
            }

            cout<<"Enter Product Catagory: ";
            cin.getline(catagory[p_index], 15, '\n');

            cout<<"Enter Product Quantity: ";
            cin>>quantity[p_index];
            cin.ignore();
            while(quantity[p_index]<0)   //agar quantity 0 se kam ho gi toh re-input
            {
                cout<<"Invalid Quantity!"<<endl;
                cout<<"Enter Product Quantity: ";
                cin>>quantity[p_index];
                cin.ignore();
            }
        }
    }
    ofstream catalogout;
    catalogout.open("textfiles\\catalog.txt", ios::out);    //file write mode main open

    //file ko write karra hai by loop
    for (int i = 0; i < c; i++) 
    {
        catalogout << id[i] << "|" << name[i] << " [" << price[i] << "]" << catagory[i] << "," << quantity[i] << endl;

    }
    catalogout.close();
    employeeMenu();
}
void stockAlerts()
{
    int choice1;
    int pid;
    int i=0, c=0;
    int p_index;
    //arrays to read catalog
    int id[200]={0};
    int quantity[200]={0};
    int price[200]={0};
    char name[200][200]={'\0'};
    char catagory[200][200]={'\0'};

    //object to read and write catalogue
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
        c++;    //total products counter
    }
    cout << setw(4) << "ID" << setw(12) << "Name" << setw(27) << "Price" << setw(24) << "Catagory" << setw(15) << "Quantity" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    //Catalogue print hogi
    i = 0;
    while (i < c)
        {
            if(quantity[i]<5)
            {
                cout << "  " << id[i] << "       " << name[i] << "  " << setw(5) << price[i] << "        " << setw(15) << catagory[i] << setw(14) << quantity[i] << endl;
            }
                i++;
        }
    cout<<"Enter the ID of the product you want to restock: "<<endl;
    cin>>pid;
    cin.ignore();
    
    p_index= matchId(pid, c, id);
    if(p_index==-1)
    {
        cout<<"Sorry, No match found!"<<endl<<endl;
    }
    else
    {
        quantity[p_index]+=10;
        cout<<"Product Restocked!"<<endl<<endl;
    }
    ofstream catalogout;
    catalogout.open("textfiles\\catalog.txt", ios::out);    //file write mode main open

    //file ko write karra hai by loop
    for (int i = 0; i < c; i++) 
    {
        catalogout << id[i] << "|" << name[i] << " [" << price[i] << "]" << catagory[i] << "," << quantity[i] << endl;

    }
    catalogout.close();

    employeeMenu();
}
void contribution()
{
    char eid_name[100][100]={'\0'};
    int e_points[100]={0};
    int sumpoints=0;
    ifstream contriin;
    contriin.open("textfiles\\contribution.txt", ios::in);
    int i=0;
    int c=0;
    while(contriin.getline(eid_name[i], 100, '|'))
    {
        contriin>>e_points[i];
        contriin.ignore(1);
        i++;
        c++;
    }
    contriin.close();
    i=0;
    while(i<c)
    {
        if(isArraySame(username, eid_name[i]))
        {
            sumpoints+=5;
        }
        i++;
    }
    cout<<"Your contribution points are: "<<sumpoints<<endl;
    employeeMenu();
}
void feedbackResponse()
{
    char cid_name[100][100]={'\0'};
    char input_name[100]={'\0'};
    char c_feedback[1000][100];
    char e_feedback[1000]={'\0'};
    ifstream feedbackin;
    feedbackin.open("textfiles\\feedback.txt", ios::in);
    int i=0;
    int c=0;
    while(feedbackin.getline(cid_name[i], 100, '|'))
    {
        feedbackin.getline(c_feedback[i], 1000, '\n');
        i++;
        c++;
    }
    feedbackin.close();

    for(i=0; i<c; i++)
    {
        cout<<"Customer name :"<<cid_name[i]<<endl;
        cout<<"Feedback :"<<c_feedback[i]<<endl<<endl;
    }

    cout<<"Enter Customer ID which you want to respond: ";
    cin.getline(input_name, 50, '\n');

    cout<<"Enter your response: ";
    cin.getline(e_feedback, 1000, '\n');

    ofstream feedbackout;
    feedbackout.open("textfiles\\feedbackemployee.txt", ios::app);
    feedbackout<<username<<"|"<<e_feedback<<"|"<<input_name<<endl;
    feedbackout.close();

    points+=5;

    ofstream contriout;
    contriout.open("textfiles\\contribution.txt", ios::app);
    contriout<<username<<"|"<<points<<endl;
    contriout.close();
    employeeMenu();
}


