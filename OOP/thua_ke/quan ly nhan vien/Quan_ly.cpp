#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Nhan_su
{
protected:
    string ma, ten;
public:
    //void Tinh_Luong();
    void Input()
    {
        cin.ignore();
        cout<<"Nhap ho va ten cua nhan su: ";
        getline(cin, ten);
        //cin.ignore();
        cout<<"Nhap ma so nhan su: ";
        getline(cin, ma);
    }
    void Output()
    {
        cout<<"\nMa so: "<<ma;
        cout<<"\nHo va Ten: "<<ten;
    }
};

class Nhan_vien : public Nhan_su
{
private:
    float heSoLuong;
public:
    void Input()
    {
        Nhan_su::Input();
        cout<<"Nhap he so luong: ";
        cin>>heSoLuong;
    }
    void Output()
    {
        Nhan_su::Output();
        cout<<"\nHe so luong: "<<heSoLuong;
    }
};

class Giang_vien : public Nhan_su
{
private:
    string hocVi;
public:
    void Input()
    {
        Nhan_su::Input();
        cout<<"Nhap hoc vi: ";
        getline(cin, hocVi);
    }
    void Output()
    {
        Nhan_su::Output();
        cout<<"\nHoc vi: "<<hocVi;
    }
};

class Tro_giang : public Nhan_su
{
private:
    float soGioCong;
public:
    void Input()
    {
        Nhan_su::Input();
        cout<<"Nhap so gio cong: ";
        cin>>soGioCong;
    }
    void Output()
    {
        Nhan_su::Output();
        cout<<"\nSo gio cong: "<<soGioCong;
    }
};

class System : public Nhan_su
{
private:
    vector<Nhan_vien> listNV;
    vector<Giang_vien> listGV;
    vector<Tro_giang> listTG;
public:
    void Menu();
    void Actions(int option);
};

int main()
{
    System *x = new System;
    x->Menu();
    return 0;
}
void System::Menu()
{
    system("cls");
    int option;
    cout<<"     THONG TIN NHAN SU";
    cout<<"\n>> 1. THEM NHAN VIEN";
    cout<<"\n>> 2. THEM GIANG VIEN";
    cout<<"\n>> 3. THEM TRO GIANG";
    cout<<"\n>> 4. HIEN THI";
    cout<<"\n>> 5. DELETE";
    cout<<"\n>> 0. EXIT";
    cout<<"\nNHAP LUA CHON: ";
    cin>>option;
    Actions(option);
}
void System::Actions(int option)
{
    switch(option)
    {
        case 1:
        {
            Nhan_vien a;
            cout<<"THEM NHAN VIEN\n";
            a.Input();
            listNV.push_back(a);
            system("pause");
            Menu();
            break;
        }
        case 2:
        {
            Giang_vien a;
            cout<<"THEM GIANG VIEN\n";
            a.Input();
            listGV.push_back(a);
            system("pause");
            Menu();
            break;
        }
        case 3:
        {
            Tro_giang a;
            cout<<"THEM TRO GIANG\n";
            a.Input();
            listTG.push_back(a);
            system("pause");
            Menu();
            break;
        }
        case 4:
        {
            cout<<"DANH SACH\n";
            for (int i = 0; i<listNV.size();i++)
            {
                listNV[i].Output();
            }
            for (int i = 0; i<listGV.size();i++)
            {
                listGV[i].Output();
            }
            for (int i = 0; i<listTG.size();i++)
            {
                listTG[i].Output();
            }
            cout<<endl;
            system("pause");
            Menu();
            break;
        }
        case 5:
        {
            string del;
            cout<<"\nNHAP MA SO NHAN SU CAN XOA: ";
            getline(cin, del);
            for (int i = 0; i<listNV.size();i++)
            {
                if (listNV[i].ma == del)
                {
                    listNV.erase(i);
                    goto end;
                }
            }
            for (int i = 0; i<listGV.size();i++)
            {
                if (listGV[i].ma == del)
                {
                    listGV.erase(i);
                    goto end;
                }
            }
            for (int i = 0; i<listTG.size();i++)
            {
                if (listTG[i].ma == del)
                {
                    listTG.erase(i);
                    goto end;
                }
            }
            end:
            cout<<"\nXOA THANH CONG\n";
            system("pause");
            Menu();
            break;
        }
        case 0:
            exit(0);
    }
}
