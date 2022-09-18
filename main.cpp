#include <iostream>
#include <fstream>
using namespace std;

// Basen on tutorial from: https://youtu.be/m2xt5KIEHvc

class shopping
{
    private:
        int pcode;
        float price;
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
    m:      // where to jump

    int choice;
    string email;
    string password;

    cout << "\t\t\t\t________________________________\n";
    cout << "\t\t\t\t                                \n";
    cout << "\t\t\t\t_____Supermarket Main Menu______\n";
    cout << "\t\t\t\t                                \n";
    cout << "\t\t\t\t________________________________\n";
    cout << "\t\t\t\t|   1) Administrator    |\n";
    cout << "\t\t\t\t|                       |\n";
    cout << "\t\t\t\t|   2) Buyer            |\n";
    cout << "\t\t\t\t|                       |\n";
    cout << "\t\t\t\t|   3) Exit             |\n";
    cout << "\t\t\t\t Please select!";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t Please login \n";
        cout << "\t\t\t Enter Email: \n";
        cin >> email;
        cout << "\t\t\t Enter password: \n";
        cin >> password;

        if (email == "morty@gmail.com" && password == "rick")
        {
            administrator();
        }
        else
        {
            cout << "Invalid email/password";
        }
        break;


    case 2:
        buyer();

    case 3:
        exit(0);

    default:
        cout << "Please select from the given options";
    }
    goto m;     // jump statement
}

void shopping::administrator()
{
    m:      // where to jump
    int choice;

    cout << "\n\n\n\t\t\t  Administrator menu";
    cout << "\n\t\t\t|_______1) Add the product___________|";
    cout << "\n\t\t\t|                                    |";
    cout << "\n\t\t\t|_______2) Modify the product________|";
    cout << "\n\t\t\t|                                    |";
    cout << "\n\t\t\t|_______3) Delete the product________|";
    cout << "\n\t\t\t|                                    |";
    cout << "\n\t\t\t|_______4) Back to the manu__________|";

    cout << "\n\n\t Please enter your choise";
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
        cout << "Invalid choice!";
    }
    goto m;     // jump statement

}

void shopping::buyer()
{
    m:      // where to jump
    int choice;
    cout << "\t\t\t      Buyer      \n";
    cout << "\t\t\t_________________\n";
    cout << "                       \n";
    cout << "\t\t\t  1) Buy product \n";
    cout << "                       \n";
    cout << "\t\t\t  2) Go back     \n";
    cout << "\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();

    default:
        cout << "Invalid choice";
    }
    goto m;     // jump statement
}

void shopping::add()
{
    m:          // where to jump
    fstream data;
    int c;              // code
    int token = 0;
    float p;            // price
    float d;            // discount
    string n;           // name

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Code of the product";
    cin >> pcode;
    cout << "\n\n\t Name of the product";
    cin >> pname;
    cout << "\n\n\t Proce of the product";
    cin >> price;
    cout << "\n\n\t Discount on the product";
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
            goto m;
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
    char choice;
    int c = 0;                  // counter
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t RECEIPT";
    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "\n\n Empty database";
    }
    else
    {
        data.close();
        list();
        
        cout << "\n|__________________________________________________|\n";
        cout << "\n|                                                  |\n";
        cout << "\n|               Please place the order             |\n";
        cout << "\n|                                                  |\n";
        cout << "\n|__________________________________________________|\n";

        do
        {
            m:      // where to jump
            cout << "\n\n Enter product code:";
            cin >> arrc[c];
            cout << "\n\n Enter the product quantity:";
            cin >> arrq[c];
            for (int i = 0; i < c ; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\n Duplicate product code. Please try again";
                    goto m;
                }
            }
            c++;
            cout << "\n\n Do you want to buy another prouct? (y/n)";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t\t_________________RECEIPT____________________\n";
        cout << "\n #\tProuct name\tProduct quantity\tPrice\tAmount\tAmount with discount\n";

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