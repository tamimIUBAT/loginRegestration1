#include<iostream>
#include<fstream>
#include<chrono>
#include<ctime>
using namespace std;


class VariableClass
{
protected:
    string Full_Name,UserName,UserID,UserPass,RegID,RegName,RegPass,RegUserName,RegBirthDate,RegEmail,RegPhone;

};

class Functional : public VariableClass
{
public:

    void registration()
    {
        system("cls");

        cout<<"Welcome to the registration page.\n";
        cout<<"Please do the following steps carefully\n";
        cout<<endl;
        cout<<"<*************************************>\n";
        cout<<"<*************************************>\n\n";
        string RegName,RegEmail,RegPhone,RegBirthDate,RegPass,conf_pass;

start:
        cout<<"Enter a valid user name: ";

        cin>>RegName;

        int c=0;

        for(int i=0; i<RegName.size(); i++)
        {
            if(RegName[i]>='a'|| 'A' && RegName[i]<='z'||'Z')
            {
                c++;
            }
        }
        if(c!=RegName.size())
        {
            cout<<"Invalid username. The user name must not contain any space or capital letter or any symbols.\n";
            cout<<"Please enter a valid username again.\n";

            goto start;
        }

        cout<<"Enter the email address: ";
        cin>>RegEmail;
        cout<<"Enter the phone number: ";
        cin>>RegPhone;
        cout<<"Enter your date of birth: ";
        cin>>RegBirthDate;
confirm:
        cout<<"Enter your password: ";
        cin>>RegPass;
        cout<<"Confirm your password: ";
        cin>>conf_pass;

        if(RegPass==conf_pass)
        {
            ofstream RegInfo("userinfo.txt",ios::app);

            ofstream Email("allEmail.txt",ios::app);
            ofstream Phone("allPhone.txt",ios::app);
            RegInfo<<RegName<<" "<<RegPass<<" "<<RegEmail<<" "<<RegPhone<<" "<<RegBirthDate<<endl;
            Email<<RegEmail<<endl;
            Phone<<RegPhone<<endl;
            cout<<"\t\t<------Registration Successful------\n";

            cout<<"Do you want to go to the login page?\n";
            cout<<"\t\t<----------->\n";
            cout<<"\t\t<----------->\n";
            cout<<"\t\t 1.YES\n";
            cout<<"\t\t 2.NO\n";
            cout<<"\t\t<----------->\n";
            cout<<"Please enter your option: ";

            int option;
            cin>>option;

            if(option==1)
            {
                login();
            }
            else
            {
                cout<<"Thank you\n";
            }
        }
        else
        {
            cout<<"<------------------------------------->\n";
            cout<<"<  --------------------------------->\n";
            cout<<"<    ----------------------------->\n";
            cout<<"Invalid Input.Confirm Password Again>\n";
            cout<<"<    ----------------------------->\n";
            cout<<"<  --------------------------------->\n";
            cout<<"<------------------------------------->\n";

            goto confirm;
        }

    }
    void login()
    {
        system("cls");

        cout<<"<---------Welcome to the login page----------->.\n";

Login:

        cout<<"Please enter the username and password carefully\n\n";

        cout<<"<*************************************>\n";
        cout<<"<*************************************>\n\n";
        string Username,Pass,tmp_name,tmp_pass,tmp_email,tmp_phone,tmp_birth;

        cout<<"Enter the username: ";
        cin>>Username;
        cout<<"Enter the password : ";
        cin>>Pass;

        //cout<<tempname<<" "<<temppass<<"\n";

        ifstream RegInfo("userinfo.txt",ios::app);

        bool loginSuccess = false;

        while(RegInfo>>tmp_name>>tmp_pass>>tmp_email>>tmp_phone>>tmp_birth)
        {

            //cout<<username<<" "<<pass<<"\n";
            if(Username==tmp_name && Pass==tmp_pass)
            {
                loginSuccess=true;
                break;
            }
        }
        if(loginSuccess)
        {
            cout<<"<***************************************************>\n";
            cout<<"<***************************************************>\n";
            cout<<"\t\tLogin Successful\n";
            cout<<"\t\tThank you\n";
            cout<<"<--------------------------------------------------->\n";
        }

        else
        {

            cout<<"Login failed.\n";
            ofstream Time("TimeSlot.txt",ios::app);

            auto now = chrono::system_clock::now();
            time_t current_time = chrono::system_clock::to_time_t(now);
            Time<<"Failed attempt at : "<<ctime(&current_time)<<endl;

            cout<<"<-------------------------------------->\n";
            cout<<"<-------------------------------------->\n";

            cout<<"\t\t 1. Try again?\n";
            cout<<"\t\t 2. Forget password?\n";
            cout<<"\t\t 3. Haven't registered yet?. Register now.\n";
            cout<<endl;
            cout<<"Enter your choice: ";
            int choice;
            cin>>choice;

            switch (choice)
            {
            case 1:
                login();
            case 2:
                forgetPass();
                break;
            case 3:
                registration();
                break;
            default:
                cout << "Invalid choice. Exiting...\n";
                break;
            }

            Time.close();
        }
        RegInfo.close();
    }

    void forgetPass()
    {
        system("cls");
        cout<<"Welcome to the password recovery page.\n";
        cout<<"<************************************>\n";
        cout<<"<************************************>\n\n";

        cout<<"You have two options: \n";
        cout<<"\t\t 1. Get your password using phone number.\n";
        cout<<"\t\t 2. Get your password using your email address.\n\n";
first:
        cout<<"Enter your choice: ";
        int n;
        cin>>n;
        if(n==1)
        {
start:
            ifstream Phone("allPhone.txt",ios::app);
            string phone,readphone;
            cout<<"Enter your Phone number: ";
            cin>>phone;
            bool forget= false;
            while(Phone>>readphone)
            {
                if(phone==readphone)
                {
                    forget=true;
                    break;
                }
            }
            if(forget)
            {
                ifstream RegInfo("userinfo.txt",ios::app);

                string tmp_name,tmp_pass,tmp_email,tmp_phone,tmp_birth;
                string ac_username,ac_pass;

                while(RegInfo>>tmp_name>>tmp_pass>>tmp_email>>tmp_phone>>tmp_birth)
                {
                    if(phone==tmp_phone)
                    {
                        ac_username=tmp_name;
                        ac_pass=tmp_pass;
                        break;
                    }
                }
                cout<<"Bingoooooo....!!You got your password back.\n";
                cout<<"<------------------------------------------->\n";
                cout<<"<------------------------------------------->\n";

                cout<<"Your username is : "<<ac_username<<endl;
                cout<<"Your password is : "<<ac_pass<<endl;

                cout<<"Do you want to login now?\n";


                cout<<"<------------------------>\n";
                cout<<"\t\t1.YES\n";
                cout<<"\t\t2.NO\n";

                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;

                if(choice==1) login();
                else
                {
                    cout<<"Happy to help you.\n";
                    cout<<"----Good Luck----\n";
                }


            }
            else
            {
                cout<<"Your input phone number doesn't match with your registered phone number.\n";
                cout<<"Please try again by entering the valid phone number.\n";

                goto start;

            }

        }
        else if(n==2)
        {
            ifstream Email("allEmail.txt",ios::app);
            string email,reademail;
            cout<<"Enter your email address: ";
            cin>>email;
            bool forget = false;
            while(Email>>reademail)
            {
                if(reademail==email)
                {
                    forget=true;
                    break;
                }
            }
            if(forget)
            {
                ifstream RegInfo("userinfo.txt",ios::app);

                string tmp_name,tmp_pass,tmp_email,tmp_phone,tmp_birth;
                string ac_username,ac_pass;

                while(RegInfo>>tmp_name>>tmp_pass>>tmp_email>>tmp_phone>>tmp_birth)
                {
                    if(email==tmp_email)
                    {
                        ac_username=tmp_name;
                        ac_pass=tmp_pass;
                        break;
                    }
                }

                cout<<"Hurrraayyyyy.....!!. You have found your password.\n";

                cout<<"Your username is : "<<ac_username<<endl;
                cout<<"Your password is : "<<ac_pass<<endl;

                cout<<"Do you want to login now?\n";


                cout<<"<------------------------>\n";
                cout<<"\t\t 1.YES\n";
                cout<<"\t\t 2.NO\n";

                int choice;
                cout<<"Enter your choice: ";
                cin>>choice;

                if(choice==1) login();
                else
                {
                    cout<<"Happy to help you.\n";
                    cout<<"----Good Luck----\n";
                }

            }
            else
            {
                cout<<"Your input email address doesn't match with the registered email address.\n";
                cout<<"Please enter the email address that you have registered with\n";
            }
        }
        else
        {
            cout<<"Wrong input. Please select the correct one.\n";
            goto first;
        }
    }
};



int main()
{

    Functional obj;


    cout<<"<-----Welcome to the server-----\n>";
    cout<<"--------------------------------\n";
    cout<<"--------------------------------\n";
label:
    cout<<"\t\t 1. Login\n";
    cout<<"\t\t 2. Registration\n";
    cout<<"\t\t 3. Forget Password\n";
    cout<<"--------------------------------\n";
    cout<<"--------------------------------\n";

    cout<<"Enter your choice: ";
    int n;
    cin>>n;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a valid number (1-3).\n";
        goto label;
    }
    switch (n)
    {
    case 1:
        obj.login();
        break;
    case 2:
        obj.registration();
        break;
    case 3:
        obj.forgetPass();
        break;
    default:
        cout << "Invalid Input. Enter again.\n";
        goto label;
        break;
    }


    return 0;
}
