#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
class medical_management
{
private:
	int medicine_id;
	char medicine_name [30];
	int stock_no;   
    char company_name[30];
    float total_Balance;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void search_rec();
    void edit_rec();
    void delete_rec();
};
void medical_management::read_data()
{
    cout<<"\nENTER ID NUMBER::- ";
    cin>>medicine_id;
    cout<<"ENTER MEDICINE NAME::- ";
    cin>>medicine_name;
    cout<<"ENTER THE STOCK NO::-";
    cin>>stock_no;
    cout<<"ENTER COMPANY NAME::-";
    cin>>company_name;
    cout<<"ENTER TOTAL BALANCE::-";
    cin>>total_Balance;
    cout<<endl;
}
void medical_management::show_data()
{
    cout<<"ID NO::- "<<medicine_id<<endl;
    cout<<"MEDICINE_NAME::- "<<medicine_name<<endl;
    cout<<"STOCK_NO::-"<< stock_no<<endl;
    cout<<"COMPANY_NAME::-"<<company_name<<endl;
    cout<<" TOTAL_BALANCE::-"<<total_Balance<<endl;    
    cout<<"-------------------------------"<<endl;
}
void medical_management::write_rec()
{
    ofstream outfile;
    outfile.open("medicial.txt", ios::binary|ios::app);
    read_data();
    outfile.write((char*)this,sizeof(*this));
    outfile.close();
}
void medical_management::read_rec()
{
    ifstream infile;
    infile.open("medicial.txt", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read((char*)this,sizeof(*this)));
        {
            show_data();
        }
    }
    infile.close();
}
void medical_management::search_rec()
{
    int n;
    ifstream infile;
    infile.open("medicial.txt", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read((char*)this,sizeof(*this));
    show_data();
}
void medical_management::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("medicial.txt", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read((char*)this,sizeof(*this));
    cout<<" Medicial Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("medicial.txt", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write((char*)this,sizeof(*this));
}
void medical_management::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("medicial.txt", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("deleted.txt", ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0; i<count; i++)
    {
        infile.read((char*)this,sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write((char*)this,sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("medicial.txt");
    rename("deleted.txt", "medicial.txt");
}
int main()
{
    medical_management A;
    int choice;
    cout<<"******************************MEDICINE RECORD MANAGEMENT SYSTEM*******************************************"<<endl;
    
	while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}

