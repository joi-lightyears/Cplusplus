#include<iostream>
#include<string.h>
using namespace std;
class Nhan_su
{
protected:
    int ma;
    string name;
public:
    Nhan_su(int ma, string name)
    {
        this->ma=ma;
        this->name=name;
    }
    void Input()
    {
        cout<<"Ma: ";
        cin>>ma;
        cout<<"\nTen: ";
        cin>>name;
    }
    void Output()
    {
        cout<<"Ma: "<<ma;
        cout<<"\nTen: "<<name;
    }
};
class Giang_vien : virtual public Nhan_su
{
protected:
    string subject;
public:
    Giang_vien(int ma, string name, string subject): Nhan_su(ma, name)
    {
        this->subject=subject;
    }
    void Input()
    {
        Nhan_su::Input();
        cout<<"\nNhap mon giang day: ";
        cin>>subject;
    }
    void Output()
    {
        Nhan_su::Output();
        cout<<"\nMon giang day: "<<subject;
    }
};
class Sinh_vien : virtual public Nhan_su
{
protected:
    int gpa;
public:
    Sinh_vien(int ma, string name, int gpa): Nhan_su(ma, name)
    {
        this->gpa=gpa;
    }
    void Input()
    {
        Nhan_su::Input();
        cout<<"\nNhap GPA: ";
        cin>>gpa;
    }
    void Output()
    {
        Nhan_su::Output();
        cout<<"\nGPA: "<<gpa;
    }
};
class Tro_giang : public Giang_vien, public Sinh_vien
{
private:
    int hour;
public:
    Tro_giang(int ma, string name, int hour, int gpa, string subject):
    Nhan_su(ma,name),
    Giang_vien(1, "JK", subject),
    Sinh_vien(2, "KJ", gpa) // recall constructors
    {
        this->hour=hour;
    }
    void Output()
    {
        cout<<"Tro giang\n";
        cout<<"Ma: "<<ma<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Hour: "<<hour<<endl;
        cout<<"GPA: "<<gpa<<endl;
        cout<<"Subject: "<<subject;
        
    }
};
int main()
{
    Tro_giang *p = new Tro_giang(201, "J K", 10, 4, "Math");
    p->Output();
    return 0;
}