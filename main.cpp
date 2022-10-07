#include <iostream>
#include <fstream>
using namespace std;

// Basen on tutorial from: https://youtu.be/m2xt5KIEHvc
// My changes:
//      added terminate() function, which checks if user's input is an int, if not it terminates the app

class shopping
{
    private:
        int pcode;      // product code
        float price;    // price
        float dis;      // discount
        string pname;   // product name

    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void rem();
        void list();
        void receipt();
        void terminate(int choice);
};

void shopping::menu()
{
    jump_menu:      // jump here

    int choice;
    string email;
    string password;

    cout << "\t\t _____________________________________________ \n";
    cout << "\t\t|                                             |\n";
    cout << "\t\t|            Supermarket Main Menu            |\n";
    cout << "\t\t|_____________________________________________|\n";
    cout << "\t\t|                                             |\n";
    cout << "\t\t|             1) Administrator                |\n";
    cout << "\t\t|                                             |\n";
    cout << "\t\t|             2) Buyer                        |\n";
    cout << "\t\t|                                             |\n";
    cout << "\t\t|             3) Exit                         |\n";
    cout << "\t\t|_____________________________________________|\n";
    cout << "\n\t\tPlease select: ";
    cin >> choice;
    
    terminate(choice);

    switch (choice)
    {
    case 1:
        cout << "Please login\n";
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

        if (email == "admin@gmail.com" && password == "admin")
        {
            administrator();
        }
        else
        {
            cout << "\nInvalid email/password\n\n";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);
        break;

    default:
        cout << "\nInvalid choice\n\n";
        break;
    }
    goto jump_menu;             // jump statement
}

void shopping::administrator()
{
    jump_adm:       // jump here

    int choice;     // administrator's choice

    cout << "\n\t\t _________Administrator menu_________";
    cout << "\n\t\t|                                    |";
    cout << "\n\t\t|       1) Add the product           |";
    cout << "\n\t\t|                                    |";
    cout << "\n\t\t|       2) Modify the product        |";
    cout << "\n\t\t|                                    |";
    cout << "\n\t\t|       3) Delete the product        |";
    cout << "\n\t\t|                                    |";
    cout << "\n\t\t|       4) Back to the manu          |";
    cout << "\n\t\t|____________________________________|";

    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    terminate(choice);

    switch (choice)
    {
    case 1:
        add();
        break;
    
    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "\nInvalid choice!\n\n";
        break;
    }
    goto jump_adm;     // jump statement
}

void shopping::buyer()
{
    jump_buy:      // jump here
    
    int choice;     // buyer's choice
    
    cout << "\n\t\t _________Buyer menu_________";
    cout << "\n\t\t|                            |";
    cout << "\n\t\t|       1) Buy product       |";
    cout << "\n\t\t|                            |";
    cout << "\n\t\t|       2) Go back           |";
    cout << "\n\t\t|____________________________|";
    cout << "\n\n\t\t    Enter your choice: ";
    cin >> choice;

    terminate(choice);

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "\nInvalid choice\n\n";
        break;
    }
    goto jump_buy;     // jump statement
}

void shopping::add()
{
    jump_add:           // jump here
    fstream data;
    int c;              // code
    int token = 0;
    float p;            // price
    float d;            // discount
    string n;           // name

    cout << "\n\n\tAdd new product";
    cout << "\n\n\tProduct code: ";
    cin >> pcode;
    cout << "\n\tName of the product: ";
    cin >> pname;
    cout << "\n\tPrice of the product: ";
    cin >> price;
    cout << "\n\tDiscount on the product: ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;

        while (!data.eof())
        {
            // if passed code is equal to existing code of the product, increment token
            if (c == pcode)
            {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        // if token is 1, go back to menu to pass different product code
        if (token == 1)
        {
            cout << "\n\nThis product code already exists, please pass different one.\n\n";
            goto jump_add;      // jump statement
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
        cout << "\n\n\tRecord inserted!\n\n";
    }
}

void shopping::edit()
{
    fstream data, data1;
    int pkey;       // code entered by administrator which he wants to edit
    int token = 0;
    int c;          // code
    float p;        // price
    float d;        // discount
    string n;       // name

    cout << "\n\tModify the record";
    cout << "\n\tEnter the product code:";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\nFile doesn't exist!";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;

        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\tNew product code: ";
                cin >> c;
                cout << "\n\tName of the product: ";
                cin >> n;
                cout << "\n\tPrice: ";
                cin >> p;
                cout << "\n\tDiscount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\tRecord edited\n";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        if (rename("database1.txt", "database.txt") != 0)
        {
            perror("Error renaming file");
        }

        if (token == 0)
        {
            cout << "\n\nRecord not found!\n\n";
        }
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\tDelete product";
    cout << "\n\n\tEnter the product code:";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n\tFile doesn't exist";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;

        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "\n\n\tProduct deleted succesfully\n";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        if (rename("database1.txt", "database.txt") != 0)
        {
            perror("Error renaming file");
        }

        if (token == 0)
        {
            cout << "\n\n\tRecord not found!\n";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|________________________________________________\n";
    cout << "Product #\t\tName\t\tPrice\n";
    cout << "\n\n|________________________________________________\n";
    data >> pcode >> pname >> price >> dis;

    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
    fstream data;
    int arrc[100];              // array of codes
    int arrq[100];              // array of quantities
    char choice;                // user's choice
    int c = 0;                  // counter
    float amount = 0;           // amount of bought product
    float dis = 0;              // discount
    float total = 0;            // total price

    // open database
    data.open("database.txt", ios::in);

    // if database does not exist, return to menu
    if (!data)
    {
        cout << "\n\nEmpty database\n\n";
        menu();
    }
    // if database exists, place the order
    else
    {
        data.close();
        list();
        
        cout << "\n ________________________________________ \n";
        cout << "\n|                                        |\n";
        cout << "\n|         Please place the order         |\n";
        cout << "\n|________________________________________|\n";

        do
        {
            jump_rec:                   // jump here
            cout << "\n\nEnter product code: ";
            cin >> arrc[c];
            cout << "\n\nEnter the product quantity: ";
            cin >> arrq[c];
            for (int i = 0; i < c ; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\nDuplicate product code. Please try again.";
                    goto jump_rec;          // jump statement
                }
            }
            c++;
            cout << "\n\nDo you want to buy another product? (y/n) ";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n________________________________RECEIPT_____________________________________\n";
        cout << "\nProduct #\t\tProduct name\t\tProduct quantity\t\tPrice\t\tAmount\t\tAmount with discount\n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    dis = amount - (amount * dis / 100);
                    total = total + dis;
                    cout << "\n" << pcode << "\t\t" << pname << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> pcode >> pname >> price >> dis;
            }
        }
        data.close();
    }
    cout << "\n\n____________________________________________________";
    cout << "\nTotal amount: " << total;
}

void shopping::terminate(int choice)
{
    // if user's choice is not an int, terminate app
    if (isdigit(choice) == 0)
    {
        cout << "\nInvalid choice - program will be terminated!\n\n";
        exit(0);
    }
}

int main()
{
    shopping s;
    s.menu();
}


// TODO
// receipt function - does not add products and their prices correctly
// improve the design
// add function - after 1st addition there is no message "record inserted"
// eliminate warnings
// change reapeted lines of code with new functions if possible