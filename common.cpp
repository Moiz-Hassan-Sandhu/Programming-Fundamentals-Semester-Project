#include "headerFiles\\common.h"
#include "headerFiles\\customer.h"
#include "headerFiles\\employee.h"
#include "headerFiles\\admin.h"

char username[100] = "\0";
void mainMenu()
{
    int choice;
    cout << "----------------------Main Menu----------------------" << endl
         << endl;
    cout << "Press 1 for Customer" << endl
         << endl
         << "Press 2 for Employee" << endl
         << endl
         << "Press 3 for Admins" << endl
         << endl
         << "Press 4 to EXIT" << endl
         << endl
         << "-----------------------------------------------------" << endl
         << endl;

    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        customer();
        break;
    }
    case 2:
    {
        employee();
        break;
    }
    case 3:
    {
        admin();
        break;
    }
    case 4:
    {
        cout << "--Exited--" << endl;
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
bool passStrength(char pass[])
{
    if (isValidLenght(pass) && hasUpperCase(pass) && hasDigit(pass)) // call all the fuctions and checks the return values
    {
        return true; // if all true then return true
    }
    return false; // if any of these is false return false
}
bool isValidLenght(char pass[]) // function checks length of the password
{
    int c = 0;                            // counter for the number of digits in password
    for (int i = 0; pass[i] != '\0'; i++) // loop runs till the null charachter
    {
        c++; // increment for every digit
    }
    return (c >= 8); // condition return true if length greater or equal 8
}
bool hasUpperCase(char pass[]) // function checks if password has uppercase letter
{
    for (int i = 1; pass[i] != '\0'; i++) // loop runs untill null charachter
    {
        if (pass[i] >= 65 && pass[i] <= 90) // condtion checks the assci range of uppercase letters
        {
            return true; // if true has uppercase then return true
        }
    }
    return false; // if false ! has uppercase then return false
}
bool hasDigit(char pass[]) // function checks if password has a digit
{
    for (int i = 1; pass[i] != '\0'; i++) // loop runs untill null charachter
    {
        if (pass[i] >= 48 && pass[i] <= 57) // condtion checks the assci range of 0 to 9 charachters
        {
            return true; // if true has a digit then return true
        }
    }
    return false; // if false ! has a digit then return false
}
bool userexist(char uname[], char pathext[])
{

    int i = 0, j = 0;
    bool userexist;
    char t_uname[20] = "";
    char t_pass[20] = "";
    char path[100] = "textfiles";
    while (path[i] != '\0')
    {
        i++;
    }
    while (pathext[j] != '\0')
    {
        path[i] = pathext[j];
        i++;
        j++;
    }
    fstream inout;
    inout.open(path);
    while (inout.getline(t_uname, 20, '|'))
    {
        inout.getline(t_pass, 20, '\n');
        for (i = 0; uname[i] != '\0' || t_uname[i] != '\0'; i++)
        {
            if (uname[i] == t_uname[i])
            {
                userexist = true;
            }
            else
            {
                userexist = false;
                break;
            }
        }
        if (userexist)
        {
            break;
        }
    }
    return userexist;
    inout.close();
    return 0;
}
bool Signin(char pathext[])
{
    char uname[50] = "";
    char path[100] = "textfiles";
    int size = 50;
    int j = 0;
    int i = 0;
    char *pass = new char[size];
    cin.ignore();
    cout << endl;
    cout << "Enter username: ";
    cin.getline(uname, 50, '\n');
    cout << "Create Password: ";
    cin.getline(pass, 50, '\n');
    while (path[i] != '\0')
    {
        i++;
    }
    while (pathext[j] != '\0')
    {
        path[i] = pathext[j];
        i++;
        j++;
    }
    while (!passStrength(pass))
    {
        cout << "Your Password is not strong enough" << endl
             << "Please enter the password again: ";
        cin.getline(pass, 50, '\n');
    }
    if (userexist(uname, pathext))
    {
        cout << "User already exists, Please Login" << endl;
        delete[] pass;
        return false;
    }
    else
    {
        encrypt(pass);
        copyarray(username, uname);
        fstream inout;
        inout.open(path, ios::app);
        inout << uname << "|" << pass << "\n";
        cout << "Sucessfully Signed In" << endl;
        delete[] pass;
        return true;
    }
    delete[] pass;
    return 0;
}
bool login(char pathext[])
{
    char uname[50] = "";
    int size = 50;
    int i = 0, j = 0;
    char *pass = new char[size]; // dynamic memory alocation
    cin.ignore();
    cout << endl;
    cout << "Enter username: ";
    cin.getline(uname, 50, '\n');
    if (userexist(uname, pathext))
    {
        int attempts = 0;
        while (1)
        {
            attempts++;
            if (attempts > 3)
            {
                cout << "Too many incorrect attempts!" << endl;
                return false;
            }
            if (attempts < 1)
            {
                cout << "Please Try again" << endl;
            }
            cout << "Enter the Password: ";
            cin.getline(pass, 50, '\n');
            if (validatePass(uname, pass, pathext))
            {
                int OTP = generateOTP();
                cout << "Enter OTP: ";
                int enteredOPT = 0;
                cin >> enteredOPT;
                cin.ignore();
                if (verifyOTP(enteredOPT, OTP))
                {
                    copyarray(username, uname);
                    remove("textfiles\\otp.txt");
                    return true;
                }
                else
                {
                    cout << "Incorrect OTP" << endl;
                    cout << "Login Failed" << endl;
                    char usertype;
                    if (pathext == "\\customer_users")
                    {
                        usertype = 'C'; // C for customer
                    }
                    else if (pathext == "\\employee_users")
                    {
                        usertype = 'E'; // E for employee
                    }
                    else if (pathext == "\\admin_users")
                    {
                        usertype = 'A'; // A for admin
                    }
                    time_t now = time(nullptr);
                    ofstream sus;
                    sus.open("textfiles\\activitylog.txt", ios::app);
                    sus << "Failed Login Attempt by: " << uname << "User Type: " << usertype << " " << ctime(&now);
                    sus.close();
                    remove("textfiles\\otp.txt");

                    return false;
                }
            }
            else
            {
                char usertype;
                if (pathext == "\\customer_users")
                {
                    usertype = 'C'; // C for customer
                }
                else if (pathext == "\\employee_users")
                {
                    usertype = 'E'; // E for employee
                }
                else if (pathext == "\\admin_users")
                {
                    usertype = 'A'; // A for admin
                }
                else
                {
                    usertype = 'U';     //Unknown
                }
                time_t now = time(nullptr);
                ofstream sus;
                sus.open("textfiles\\activitylog.txt", ios::app);
                sus << "Failed Login Attempt by: " << uname << " User Type: " << usertype << " " << ctime(&now);
                sus.close();
                cout << "Incorrect Password" << endl;
                return false;
            }
        }
    }
    else
    {
        cout << "User Doesn't Exist Please Signin" << endl;
        return false;
    }
    delete[] pass;
    return false;
}
bool validatePass(char uname[], char pass[], char pathext[])
{
    int i = 0;
    int j = 0;
    char t_uname[20] = "";
    char t_pass[20] = "";
    char path[100] = "textfiles";
    while (path[i] != '\0')
    {
        i++;
    }
    while (pathext[j] != '\0')
    {
        path[i] = pathext[j];
        i++;
        j++;
    }
    fstream inout;
    inout.open(path, ios::in);
    int attempts = 0;
    while (inout.getline(t_uname, 20, '|'))
    {
        inout.getline(t_pass, 20, '\n');
        decrypt(t_pass);
        if (isArraySame(uname, t_uname) && isArraySame(pass, t_pass))
        {
            return true;
        }
    }
    inout.close();
    return false;
}
bool isArraySame(char a[], char b[])
{
    int i;
    bool same;
    for (i = 0; a[i] != '\0' || b[i]; i++)
    {
        if (a[i] == b[i])
        {
            same = true;
        }
        else
        {
            same = false;
            break;
        }
    }
    return same;
}
void copyarray(char arr1[], const char arr2[])
{
    int i = 0;
    while (arr2[i] != '\0') // ye loop tab tak chale gi jab rak arr2 main null na reach ho jaye
    {
        arr1[i] = arr2[i]; // arr1 ka [i] pe jo value ho gi woh arr2 ki [i] se change ho jaye gi
        i++;
    }
    arr1[i] = '\0'; // arr1 ke end main null charachter add karne ke liye
}
int matchId(int pId, int c, int id[110]) // product id ko match kare ga
{
    int i = 0;
    while (i < c) // loop, number of products tak chale ga
    {
        if (pId == id[i]) // agar kisi bhi index pe id match hogi
        {
            return i; // woh single index return kar dega
        }
        i++;
    }
    return -1; // agar match nai hoga toh -1 return ho jaye ga
}
char *encrypt(char *pass)
{
    int i = 0; // password ko encrypt kar ke store karne ke liye
    while (pass[i] != '\0')
    {
        pass[i] = pass[i] + 2;
        i++;
    }
    return pass;
}
char *decrypt(char *pass)
{
    int i = 0; // password ko dencrypt kar ke read karne ke liye
    while (pass[i] != '\0')
    {
        pass[i] = pass[i] - 2;
        i++;
    }
    return pass;
}
int generateOTP() // fucntion  generate random OTP
{
    srand(time(0)); // set seed for random number : cpu current time
    int generatedOTP = 0;
    int temp = 0;
    for (int i = 0; i <= 5; i++) // generating 6 digit randome number
    {
        temp = (rand() % 10);
        generatedOTP = generatedOTP * 10 + temp;
    }
    cout << endl;
    ofstream otpout;
    otpout.open("textfiles\\otp.txt", ios::out); // storing otp in otp.txt file
    otpout << "Your OTP: " << generatedOTP << endl;
    otpout.close();
    cout << "OTP has been sent to your registered device." << endl;
    return generatedOTP;
}
bool verifyOTP(int enteredOTP, int generatedOTP) // function validates OTP
{
    bool otp;
    if (enteredOTP == generatedOTP) // check if the user entered correct OTP
    {
        otp = true; // if true then return ture
    }
    else
    {
        otp = false; // if false then return false
    }
    return otp;
}

void printHeader()
{
    // catalogue ka head print hoga
    cout << setw(4) << "ID" << setw(12) << "Name" << setw(36) << "Price" << setw(23) << "Catagory" << setw(15) << "Quantity" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
}