#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <conio.h>
#include <bits/stdc++.h>

using namespace std;

map<int, pair<string, int>>accNo_and_name;
map<int , char>accNo_type;
map<int, bool>index;

int generate_accNo()
{
    int i =0;
    for( i= 0; i<1000; i++)
        if(index[1000+i] == 0)
            break;

    return (1000+i);

}

class account
{
    int accNo;
    char name[50];
    int deposit;
    char type;

public :
    void createAccount();
    void showAccount();
    void depositeMoney(int);
    void withdrawMoney(int);
    void report();
    void storeData();
    int retAccNo();
    int retAvailableBalance();
    void changeDetails(int);
    string retName();
    int retBalance();
    char retType();
    void removeAccount();

} ;

void account :: removeAccount()
{
    auto it = accNo_and_name.find(accNo);
    accNo_and_name.erase(it);
    auto it1 = accNo_type.find(accNo);
    accNo_type.erase(it1);
}

int account :: retBalance()
{
    return deposit;
}

char account :: retType()
{
    return type;
}

string account :: retName()
{
    return name;
}

void account :: changeDetails(int n)
{
    int option;
    cout << "Press 1 to Change the Name\n";
    cout << "Press 2 to Change the Types\n";
    cin >> option;

    do{
    switch(option)
    {
    case 1 :

        cout << "Please Enter the New Name : ";
        cin.ignore();
        cin.getline(name, 50);
        accNo_and_name[accNo].first = name;
        cout << "Name has been successfully changed !!!";
        break;

    case 2:
        char type1;
        cout << "Please Enter the New Type";
        cin >> type;
        accNo_type[accNo]= type;
        cout << "Type has been successfully changed !!!";
        break;

    default :
        cout << "Invalid Input !!! \n Try Again";

    }

    }while(option != 1 && option != 2);
}

int account :: retAvailableBalance()
{
    return deposit;
}
void account :: createAccount()
{
    system("cls");
    cout << "\n\t\t===================================\n";
    cout << "\t              Creating an Account       \n";
    cout << "\t\t=====================================\n";


    accNo = generate_accNo();
    cout << "\n\n\t\tEnter the Name of the Account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\n\t\tEnter the Type of the Account(C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\n\t\tEnter the Initial Amount : ";
    cin >> deposit;
    cout << "\n\n\t\tThe Account is Created.";
    cin.ignore();
    cin.get();

    int n = accNo;
    int bal = deposit;
    string str = name;
    char c = type;
    pair<string, int>pr;
    pr = make_pair(str, bal);
    accNo_and_name.insert(make_pair(n, pr));
    accNo_type.insert(make_pair(n, c));
    index[n] = 1;




}

void account :: storeData()
{
    ofstream myfile;
    myfile.open("acc.txt", ios :: app|ios :: binary);
    myfile.write((char *)this, sizeof(account));
    myfile.close();
}

void account :: report()
{
    cout <<setw(5) <<accNo << setw(20) << name << setw(5) << type <<setw(15) << deposit << endl;
}

void account :: depositeMoney(int amnt)
{
    deposit += amnt;
    int n = accNo;
    accNo_and_name[n].second = deposit;
}

void account :: showAccount()
{
    cout << "Account Number : " << accNo << endl;
    cout << "Account Holder's Name : " << name << endl;
    cout << "Type of Account : " << type << endl;
    cout << "Balance : " << deposit << endl;
}

int account :: retAccNo()
{
    return this->accNo;
}

void account :: withdrawMoney(int n)
{
    deposit -= n;
    int k = accNo;
    accNo_and_name[k].second = deposit;
}

void create_account();
void display_all_accounts();
void deposite_withdraw(int, int);
void show_balance(int);
void closeAccount(int);
void Change_details(int);
void remove_all_records();
void arrange_data_in_map();

int main()
{

    arrange_data_in_map();
    int ch;
    int num;
    do{
        system("CLS");
        cout<<"\n\n\t\t\t\t======================\n";
        cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM\n";
        cout<<"\t\t\t\tCreated By Rahul Kumar";
        cout<<"\n\t\t\t\t======================\n";

        // Displaying all options
        cout<<"\t\t\t\t    ::MAIN MENU::\n";
		cout<<"\n\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout<<"\n\t\t\t\t8. Remove All Records";
		cout<<"\n\t\t\t\t9. EXIT";
		cout<<"\n\n\t\t\t\tSelect Your Option (1-8): ";
		cin>>ch;

		switch(ch)
		{
            case 1 :
                create_account();
                break;

            case 2 :
                system("cls");
                cout << "Please Enter the Account Number : ";
                cin >> num;
                deposite_withdraw(num, 1);
                break;

            case 3 :
                system("cls");
                cout << "Please Enter the Account Number : ";
                cin >> num;
                deposite_withdraw(num, 0);
                break;

            case 4 :
                system("cls");
                cout << "Please Enter Your Account Number : ";
                cin >> num;
                show_balance(num);
                break;

            case 5 :
                display_all_accounts();

                break;



            case 6 :
                system("cls");
                cout << "Please Enter Your Account Number : ";
                cin >> num;
                closeAccount(num);
                break;

            case 7 :
                system("cls");
                cout << "Enter the Account Number";
                cin >> num;
                Change_details(num);
                break;

            case 8 :
                remove_all_records();
                break;



        }
        cin.ignore();
		cin.get();
    }while(ch != 9);

}

void arrange_data_in_map()
{
    account acc;
    ifstream myfile("acc.txt", ios :: binary);
    if(!myfile)
        return;

    for(int i=0; i<1000; i++)
        index[1000+i] = 0;


    while(myfile.read((char*)(&acc), sizeof(acc))){
        int n = acc.retAccNo();
        string NAME = acc.retName();
        int bal = acc.retBalance();
        char TYPE = acc.retType();
        index[n] = 1;
        pair<string, int>pr;
        pr = make_pair(NAME, bal);
        accNo_and_name.insert(make_pair(n,pr));
        accNo_type.insert(make_pair(n, TYPE));
    }
    myfile.close();

}

void remove_all_records()
{
    system("cls");
                cout <<"\n\t=================================\n";
                cout << "\t\tRemoving All Records";
                cout <<"\n\t=================================\n";
                cout << "\n\tTo Proceed Press Any Number";
                cout << "\n\tTo Return Press 0";

                int n;
                cout << "\n\n\tYour Response : ";
                cin >> n;

                if(n == 0)
                return;

                else{
                    system("cls");
                    cout << "\n\t=====================================\n";
                    cout << "\t      Erasing All the Stored Data.\n";
                    cout << "\t=====================================\n";
                    cout << "\nNote :- If you type a wrong password then you will be redirected to homepage!!!\n\n\n";

                    cout << "\t      Type Password : ";
                    char ch[10];

                    for(int i = 0; i<10; i++)
                    {
                        char a = getch();
                        if(a == 13)
                            break;

                        ch[i] = a;
                        cout <<'*';
                    }
                    if(strcmp("1234", ch) != 0){
                        cout <<"\n\t  Wrong Password!!!!!";
                        return;
                    }

                    else{
                        remove("acc.txt");
                        accNo_and_name.clear();
                        accNo_type.clear();
                        for(int i=0; i<1000; i++)
                            index[1000+i] = 0;
                        cout << "\n\n\t All data has been erased";

                    }
                }


}

void Change_details(int n)
{
    account acc;
    fstream myfile("acc.txt", ios :: in | ios :: out | ios :: binary);
    int flag = 0;

    while(myfile.read((char*)&acc, sizeof(acc)) && flag == 0){
        if(acc.retAccNo() == n){

            acc.changeDetails(n);

            int pos = (-1)*(sizeof(acc));
            myfile.seekp(pos, ios :: cur);
            myfile.write((char*)&acc, sizeof(acc));
            flag = 1;
        }
    }
    myfile.close();

}

void show_balance(int n)
{
    account acc;
    ifstream myfile("acc.txt", ios :: binary);
    if(!myfile){
        cout << "File Can't be opened !!! Press Any Key to Continue";
        return;
    }
    int flag = 0;

    while(myfile.read((char*)&acc, sizeof(acc)) && flag == 0){
        if(acc.retAccNo() == n){
            acc.showAccount();
            flag = 1;
        }
    }

    if(flag == 0)
        {cout << "Account Not Find";
        return;}
}

void closeAccount(int n)
{
    account acc;
    ifstream infile("acc.txt", ios :: binary);
    ofstream outfile("temp.txt", ios :: app);
    if(!infile)
    {
        cout << "File can't be opened";
        return;
    }
    int flag = 0;
    while(infile.read((char*)&acc, sizeof(acc))){
        if(acc.retAccNo() != n)
            outfile.write((char*)&acc, sizeof(acc));

            else{
                flag = 1;
                acc.removeAccount();
                index[acc.retAccNo()] = 0;
            }

    }
    infile.close();
    outfile.close();
    remove("acc.txt");
    rename("temp.txt", "acc.txt");
    if(flag == 0)
        cout << "Account Not Found !!!";
    else
        cout << "Account is Deleted !!!";

}


void create_account()
{
    account acc;
    acc.createAccount();
    acc.storeData();

}
void display_all_accounts()
{
    system("cls");
    account acc;
    ifstream file("acc.txt", ios :: binary);
    if(!file){
        cout << "\n\t\tCan't be Opened!!! Press Any Key.";
        return;
    }
    cout << "\n\t\tDetails of All Account Holders.\n\n";;
    cout << "====================================================\n";
    cout << "A/c no.\t\tNAME\t     Type\t\tBalance\n";
    cout << "====================================================\n";

   // while(file.read((char*)(&acc), sizeof(acc)))
     //   acc.report();

     for(auto it : accNo_and_name)
    cout <<setw(5) << it.first << setw(20) << it.second.first<<setw(5)<<accNo_type[it.first] <<setw(15)<< it.second.second<<endl;
    file.close();
}

void deposite_withdraw(int accno, int opt)
{
    //opt 1 to deposit
    // opt 2 to withdraw

    int amnt;

    int flag = 0;
    account acc;
    fstream file("acc.txt", ios :: in | ios :: out | ios :: binary);
    if( !file)
    {
        cout << "There is No File !!! Press Any Key to Continue.";
        return;
    }

    while(file.read((char*)(&acc), sizeof(acc)) && flag == 0){
            if(acc.retAccNo() == accno){
                acc.showAccount();

                if(opt == 1){
                    cout << "\nEnter the Amount to Be Deposited : ";
                    cin >> amnt;
                    acc.depositeMoney(amnt);
                }

                else{
                        cout << "Please Enter the Amount to Withdraw : ";
                        cin  >> amnt;
                        if(acc.retAvailableBalance() < amnt)
                        {
                            cout << "Balance in your Account is not Sufficient !!! \nCurrent Balance is : ";
                            cout << acc.retAvailableBalance();
                            return;

                        }
                        else
                        {
                            acc.withdrawMoney(amnt);
                            cout << "Now Available Balance : \n";
                            cout << acc.retAvailableBalance();
                        }


                }
                        int pos = (-1)*(sizeof(acc));
                        file.seekp(pos, ios :: cur);
                        file.write((char*)(&acc), sizeof(acc));
                        flag = 1;
            }
    }
    file.close();
            if(flag == 0)
                cout << "Record not Found\n";

}





