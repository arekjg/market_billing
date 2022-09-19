#include <iostream>
#include <fstream>
using namespace std;

// Basen on tutorial from: https://youtu.be/m2xt5KIEHvc

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
};

void shopping::menu()
{
    m:      // jump here

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
    cout << "\t\t|_____________3) Exit_________________________|\n";
    cout << "\n\t\t Please select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Please login \n";
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

    case 3:
        exit(0);

    default:
        cout << "\nPlease select from the given options\n\n";
    }
    goto m;     // jump statement
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

    cout << "\n\n\t Please enter your choise: ";
    cin >> choice;

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

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();

    default:
        cout << "\nInvalid choice\n\n";
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
            goto jump_add;      // jump statement
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
        cout << "\n\n\t\t Record inserted!";
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

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Enter the product code:";
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
                cout << "\n\t\t New product code: ";
                cin >> c;
                cout << "\n\t\t Name of the product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited";
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
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n Record not found sorry!";
        }
    }

}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Enter the product code:";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;

        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "\n\n\t Product deleted succesfully";
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
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n Record not found";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|________________________________________________\n";
    cout << "#\t\tName\t\tPrice\n";
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
            jump_rec:      // jump here
            cout << "\n\n Enter product code:";
            cin >> arrc[c];
            cout << "\n\n Enter the product quantity:";
            cin >> arrq[c];
            for (int i = 0; i < c ; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\n Duplicate product code. Please try again";
                    goto jump_rec;          // jump statement
                }
            }
            c++;
            cout << "\n\n Do you want to buy another prouct? (y/n)";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t\t_________________RECEIPT____________________\n";
        cout << "\n #\tProduct name\tProduct quantity\tPrice\tAmount\tAmount with discount\n";

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
                    cout << "\n" << "\t\t" << pcode << "\t\t" << pname << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << dis;
                }
                data >> pcode >> pname >> price >> dis;
            }
        }
        data.close();
    }
    cout << "\n\n____________________________________________________";
    cout << "\n Total amount: " << total;
}

int main()
{
    shopping s;
    s.menu();
}


// TODO
// receipt function - does not add products and their prices correctly
// change repeated lines of code with new functions if possible
// improve the design
// correct the misspelings
// add comments