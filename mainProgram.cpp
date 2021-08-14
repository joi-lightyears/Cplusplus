/***************************************************************
*                 | STUDENT MANAGEMENT SYSTEM |                *
*______________________________________________________________*
*                            FEATURES                          *
*   1. OPEN FEATURES MENU                                      *
*   2. THEM SINH VIEN                                          *
*   3. HIEN THI DANH SACH                                      *
*   4. CHINH SUA SINH VIEN                                     *
*   5. TIM KIEM SINH VIEN                                      *
*       o Tim theo STT                                         *
*       o Tim theo ten                                         *
*       o Tim theo lop                                         *
*   6. XOA SINH VIEN                                           *
*   7. SAP XEP                                                 *
*       o Diem ren luyen                                       *
*       o Diem giua ky                                         *
*       o Diem cuoi ky                                         *
*   8. EXIT                                                    *
*                                                              *
***************************************************************/

#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<fstream> // for creating files/ writing/ read
#include<string>
#include <string.h> // for substr() and find()
#include<stdlib.h>
#include<iomanip>   // to use: setw
#include <algorithm> // to remove something in string | erase()
#include <stdio.h> // to use remove() rename() a file
using namespace std;
int stt2 = 0;
struct sinhVien
{
    int stt;
    string name, classID;
    float diemRenLuyen, diemGiuaKy, diemCuoiKy;

}a, bS[60];
typedef struct sinhVien sv;

void updateSTT();

void choose(int &choice);
void menu(int &choice);
void insert(int stt);
void display();
void action(int &choice);
void edit();
void searchSV();
void deleteSV();
//sort functions
void sort();
void sortInDe(int choiceS, int choiceS2);
void InsertionSort(int choiceS, int choiceS2, sv bS[], int n);
void chooseKey(int choiceS, int choiceS2, sv bS[], float &key, int i);

struct interface //giao dien
{
    void hangThuocTinh()
    {
        cout<<setw(17)<<right<<" "<<setfill('_');
        cout<<setw(101)<<"_"<<setfill(' ')<<endl;
        cout<<setw(17)<<right<<"|"<<setw(102)<<right<<"|"<<endl;
        cout<<setw(18)<<right<<" "<<setw(5)<<left<<"STT";
        cout<<setw(30)<<left<<"HO VA TEN";
        cout<<setw(15)<<left<<"LOP";
        cout<<setw(20)<<left<<"DIEM REN LUYEN";
        cout<<setw(17)<<left<<"DIEM GIUA KY";
        cout<<setw(12)<<left<<"DIEM CUOI KY"<<endl;
        cout<<setw(17)<<right<<" "<<setfill('-');
        cout<<setw(101)<<"-"<<setfill(' ')<<endl;
    }
    void vienDuoiBang()
    {
        cout<<setw(17)<<right<<"|"<<setfill('_');
        cout<<setw(102)<<right<<"|"<<setfill(' ')<<endl<<endl;
    }
    void vienKhungTieuDe()
    {
        cout<<setw(45)<<right<<" "<<setfill('-');
        cout<<setw(50)<<"-"<<setfill(' ')<<endl;
    }
    void printData(sv a)
    {
        cout<<setw(18)<<right<<" "<<setw(5)<<left<<a.stt;
        cout<<setw(30)<<left<<a.name;
        cout<<setw(15)<<left<<a.classID;
        cout<<setw(20)<<left<<a.diemRenLuyen;
        cout<<setw(17)<<left<<a.diemGiuaKy;
        cout<<setw(12)<<left<<a.diemCuoiKy<<endl;
    }
    void khungTangGiamDan()
    {
        cout<<setw(45)<<right<<" "<<setfill('_');
        cout<<setw(50)<<"_"<<setfill(' ')<<endl;
        cout<<setw(44)<<right<<" "<<setw(51)<<left<<"|"<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(14)<<left<<"|"<<"1. TANG DAN\t2. GIAM DAN"<<setw(13)<<right<<"|"<<endl;
        cout<<setw(45)<<right<<"|"<<setfill('_');
        cout<<setw(50)<<"_"<<"|"<<setfill(' ')<<endl<<endl;
    }
}iFace;

struct smallActions
{
    void inputSvData()
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"Ho va Ten: ";
        getline(cin, a.name);
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"Lop: ";
        getline(cin, a.classID);
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"Diem ren luyen: ";
        cin>>a.diemRenLuyen;
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"Diem giua ky: ";
        cin>>a.diemGiuaKy;
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"Diem cuoi ky: ";
        cin>>a.diemCuoiKy;
        cin.ignore();
    }
}sA;

void updateSTT() // cập nhật lại số stt trong file và gán vào biến stt2
{
    fstream file;
    file.open("QLSV.DAT", ios::in); //it opens a file for a read
    if (!file) // neu chua tao file
    {
        file.close();
    } else // da tao file
    {
        getline(file, a.name, '|');
        file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
        while(!file.eof())
        {
            getline(file, a.name, '|');
            file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
        }
    }
    if (a.stt != 0)
    {
        stt2 = a.stt;
    }
    file.close();
}

void choose(int &choice)
{
    cout<<">> HAY LUA CHON TAC VU (1 <<MENU>>, 2, 3,... 8 <<EXIT>>): ";
    cin>>choice;
    cin.ignore();
    action(choice);
}

void menu(int &choice)
{
    system("cls"); // xoa man hinh
    // title
    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(17)<<left<<"|"<<"QUAN LY SINH VIEN"<<setw(18)<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();
    // Display all Feature options
    cout<<setw(45)<<right<<" "<<setfill('_');
    cout<<setw(50)<<"_"<<setfill(' ')<<endl;
    cout<<setw(44)<<right<<" "<<setw(51)<<left<<"|"<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(19)<<left<<"|"<<"FEATURES MENU"<<setw(20)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"1. OPEN FEATURES MENU"<<setw(19)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"2. THEM SINH VIEN"<<setw(23)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"3. HIEN THI DANH SACH"<<setw(19)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"4. CHINH SUA SINH VIEN"<<setw(18)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"5. TIM KIEM SINH VIEN"<<setw(19)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"6. XOA SINH VIEN"<<setw(24)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"7. SAP XEP"<<setw(30)<<right<<"|"<<endl;
    cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"8. EXIT"<<setw(33)<<right<<"|"<<endl;
    cout<<setw(45)<<right<<"|"<<setfill('_');
    cout<<setw(50)<<"_"<<"|"<<setfill(' ')<<endl<<endl;
    choose(choice);
}

void insert()
{
    system("cls"); //xoa man hinh cmd
    fstream file; //creating files, reading and writing from files
    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(19)<<left<<"|"<<"THEM SINH VIEN"<<setw(19)<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();

    sA.inputSvData();
    stt2++;
    file.open("QLSV.DAT", ios::app | ios::out); // append and open the file for write
    file<<a.name<<"|"<<" "<<stt2<<" "<<a.classID<<" "<<a.diemRenLuyen<<" "<<a.diemGiuaKy<<" "<<a.diemCuoiKy<<"\n";
    file.close();
}

void display()
{
    system("cls"); // xoa man hinh cmd
    fstream file; //creating files, reading and writing from files
    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(17)<<left<<"|"<<"DANH SACH SINH VIEN"<<setw(16)<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();
    file.open("QLSV.DAT", ios::in); //it opens a file for a read
    if (!file) // neu chua tao file
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
        file.close();
    } else // da tao file
    {
        getline(file, a.name, '|');
        file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;

        iFace.hangThuocTinh();
        while(!file.eof())
        {
            iFace.printData(a);
            getline(file, a.name, '|');
            // loai bo \n dau dong cua hang thu 2 tro di trong data
            a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
            file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
            
        }
        if (a.stt == 0)
        {
            cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
        } else
        {
            iFace.vienDuoiBang();
        }
    }
    file.close();
}

void edit()
{
    system("cls");
    fstream file, fileTemp;
    int sttE, notFound = 1;

    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(17)<<left<<"|"<<"CHINH SUA SINH VIEN"<<setw(16 )<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();

    file.open("QLSV.DAT", ios::in);
    if (!file) // neu chua tao file
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
        file.close();
    } else // da tao file
    {
        fileTemp.open("QLSV_EDIT.DAT", ios::app | ios::out);
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"HAY NHAP SO THU TU (STT): ";
        cin>>sttE;
        cin.ignore();
        getline(file, a.name, '|');
        a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
        file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
        while (!file.eof())
        {
            if (a.stt != sttE)
            {
                fileTemp<<a.name<<"|"<<" "<<a.stt<<" "<<a.classID<<" "<<a.diemRenLuyen<<" "<<a.diemGiuaKy<<" "<<a.diemCuoiKy<<"\n";
            }else
            {
                sA.inputSvData();
                fileTemp<<a.name<<"|"<<" "<<sttE<<" "<<a.classID<<" "<<a.diemRenLuyen<<" "<<a.diemGiuaKy<<" "<<a.diemCuoiKy<<"\n";
                notFound++;
            }
            getline(file, a.name, '|');
            a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
            file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
        }
        if (notFound == 1)
        {
            cout<<setw(44)<<right<<" "<<setw(6)<<left<<"|"<<"(!) KHONG CO SINH VIEN CO SO THU TU NAY"<<setw(7)<<right<<"|"<<endl<<endl;
        }
        file.close();
        fileTemp.close();
        remove("QLSV.DAT");
        rename("QLSV_EDIT.DAT", "QLSV.DAT");
    }
}

void searchSV()
{
    system("cls");
    fstream file;
    int notFound = 1, choiceS;

    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(17)<<left<<"|"<<"TIM KIEM SINH VIEN"<<setw(17)<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();

    file.open("QLSV.DAT", ios::in);
    if (!file) // neu chua tao file
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
        file.close();
    } else // da tao file
    {
        cout<<setw(45)<<right<<" "<<setfill('_');
        cout<<setw(50)<<"_"<<setfill(' ')<<endl;
        cout<<setw(44)<<right<<" "<<setw(51)<<left<<"|"<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"HAY LUA CHON KIEU TIM KIEM"<<setw(14)<<right<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"1. TIM KIEM THEO SO THU TU (STT)"<<setw(8)<<right<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"2. TIM KIEM THEO TEN"<<setw(20)<<right<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(12)<<left<<"|"<<"3. TIM KIEM THEO LOP"<<setw(20)<<right<<"|"<<endl;
        cout<<setw(45)<<right<<"|"<<setfill('_');
        cout<<setw(50)<<"_"<<"|"<<setfill(' ')<<endl<<endl;
        againSearch:
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"HAY NHAP LUA CHON (1, 2, 3): ";
        cin>>choiceS;
        cin.ignore();
        switch(choiceS)
        {
            case 1:
            {
                int sttS;
                cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"HAY NHAP SO THU TU (STT): ";
                cin>>sttS;
                cin.ignore();

                iFace.hangThuocTinh();

                getline(file, a.name, '|');
                a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
                file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
                while (!file.eof())
                {
                    if (sttS == a.stt)
                    {
                        iFace.printData(a);
                        notFound++;
                    }
                    getline(file, a.name, '|');
                    // loai bo \n dau dong cua hang thu 2 tro di trong data
                    a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
                    file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
                }
                if (notFound == 1)
                {
                    cout<<endl;
                    cout<<setw(17)<<right<<"|"<<setw(71)<<right<<"(!) KHONG CO SINH VIEN CO SO THU TU NAY"<<setw(31)<<right<<"|"<<endl<<endl;
                }else
                {
                    iFace.vienDuoiBang();
                }
                file.close();
                break;
            }
            case 2:
            {
                string nameS, temp, classS;
                int notFound = 1;
                string::size_type idx;
                cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"HAY NHAP CHU BAT KY: ";
                getline(cin, classS);

                iFace.hangThuocTinh();

                getline(file, a.name, '|');
                a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
                file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
                while (!file.eof())
                {
                    idx = a.name.find(classS);
                    if (idx < a.name.length() && idx >= 0)
                    {
                        iFace.printData(a);
                        notFound++;
                    }
                    getline(file, a.name, '|');
                    a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
                    file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
                }
                if (notFound == 1)
                {
                    cout<<endl;
                    cout<<setw(17)<<right<<"|"<<setw(75)<<right<<"(!) KHONG CO SINH VIEN NAO CO CHU NAY TRONG TEN"<<setw(27)<<right<<"|"<<endl<<endl;
                }else
                {
                    iFace.vienDuoiBang();
                }
                file.close();
                break;
            }
            case 3:
            {
                string classS;
                cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"HAY NHAP LOP: ";
                cin>>classS;
                cin.ignore();

                iFace.hangThuocTinh();

                getline(file, a.name, '|');
                a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
                file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
                while (!file.eof())
                {
                    if (classS == a.classID)
                    {
                        iFace.printData(a);
                        notFound++;
                    }
                    getline(file, a.name, '|');
                    // loai bo \n dau dong cua hang thu 2 tro di trong data
                    a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
                    file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
                }
                if (notFound == 1)
                {
                    cout<<endl;
                    cout<<setw(17)<<right<<"|"<<setw(62)<<right<<"(!) KHONG CO LOP NAY"<<setw(40)<<right<<"|"<<endl<<endl;
                }else
                {
                    iFace.vienDuoiBang();
                }
                file.close();
                break;
            }
            default:
            {
                cout<<setw(99)<<right<<"(!) BAN DA NHAP KHONG DUNG SO THICH HOP | VUI LONG NHAP LAI"<<endl;
                goto againSearch;
                break;
            }
        }
    }
}

void deleteSV()
{
    system("cls");
    fstream file, fileTemp;
    int sttD, notFound = 1, sttTemp = 0;

    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(19)<<left<<"|"<<"XOA SINH VIEN"<<setw(20)<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();

    file.open("QLSV.DAT", ios::in);
    if (!file) // neu chua tao file
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
        file.close();
    } else // da tao file
    {
        fileTemp.open("QLSV_DELETE.DAT", ios::app | ios::out);
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<" "<<"HAY NHAP SO THU TU (STT): ";
        cin>>sttD;
        cin.ignore();
        getline(file, a.name, '|');
        a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
        file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
        while (!file.eof())
        {
            if (a.stt != sttD)
            {
                if (sttTemp != 0)
                {
                    a.stt--;
                }
                fileTemp<<a.name<<"|"<<" "<<a.stt<<" "<<a.classID<<" "<<a.diemRenLuyen<<" "<<a.diemGiuaKy<<" "<<a.diemCuoiKy<<"\n";
            }else
            {
                notFound++;
                sttTemp = a.stt;
                stt2--;
                cout<<endl;
                cout<<setw(44)<<right<<" "<<setw(14)<<left<<"|"<<"XOA SINH VIEN THANH CONG"<<setw(14)<<right<<"|"<<endl<<endl;
            }
            getline(file, a.name, '|');
            a.name.erase(remove(a.name.begin(), a.name.end(), '\n'), a.name.end());
            file >> a.stt >> a.classID >> a.diemRenLuyen >> a.diemGiuaKy >> a.diemCuoiKy;
        }
        if (notFound == 1)
        {
            cout<<endl;
            cout<<setw(44)<<right<<" "<<setw(6)<<left<<"|"<<"(!) KHONG CO SINH VIEN CO SO THU TU NAY"<<setw(7)<<right<<"|"<<endl<<endl;
        }
        file.close();
        fileTemp.close();
        remove("QLSV.DAT");
        rename("QLSV_DELETE.DAT", "QLSV.DAT");
    }
}
/****************(sort)****************************************************/
/*
bool selection(int choiceS, int choiceS2, sv bS[], int i, int j)
{
    if (choiceS == 1 && choiceS2 == 1) // diem ren luyen va tang dan
    {
        return bS[i].diemRenLuyen > bS[j].diemRenLuyen;
    }else if (choiceS == 1 && choiceS2 == 2) // diem ren luyen va giam dan
    {
        return bS[i].diemRenLuyen < bS[j].diemRenLuyen;
    }else if (choiceS == 2 && choiceS2 == 1) // diem giua ky va tang dan
    {
        return bS[i].diemGiuaKy > bS[j].diemGiuaKy;
    }else if (choiceS == 2 && choiceS2 == 2) // diem giua ky va giam dan
    {
        return bS[i].diemGiuaKy < bS[j].diemGiuaKy;
    }else if (choiceS == 3 && choiceS2 == 1) // diem cuoi ky va tang dan
    {
        return bS[i].diemCuoiKy > bS[j].diemCuoiKy;
    }else // diem cuoi ky va giam dan
    {
        return bS[i].diemCuoiKy < bS[j].diemCuoiKy;
    }
}*/
bool condition(int choiceS, int choiceS2, sv bS[], float key, int j)
{
    if (choiceS == 1 && choiceS2 == 1) // diem ren luyen va tang dan
    {
        return j >= 0 && bS[j].diemRenLuyen > key;
    }else if (choiceS == 1 && choiceS2 == 2) // diem ren luyen va giam dan
    {
        return j >= 0 && bS[j].diemRenLuyen < key;
    }else if (choiceS == 2 && choiceS2 == 1) // diem giua ky va tang dan
    {
        return j >= 0 && bS[j].diemGiuaKy > key;
    }else if (choiceS == 2 && choiceS2 == 2) // diem giua ky va giam dan
    {
        return j >= 0 && bS[j].diemGiuaKy < key;
    }else if (choiceS == 3 && choiceS2 == 1) // diem cuoi ky va tang dan
    {
        return j >= 0 && bS[j].diemCuoiKy > key;
    }else // diem cuoi ky va giam dan
    {
        return j >= 0 && bS[j].diemCuoiKy < key;
    }
}

void chooseKey(int choiceS, int choiceS2, sv bS[], float &key, int i)
{
    if (choiceS == 1)
    {
        key = bS[i].diemRenLuyen;
    }else if (choiceS == 2)
    {
        key = bS[i].diemGiuaKy;
    }else
    {
        key = bS[i].diemCuoiKy;
    }
}

void InsertionSort(int choiceS, int choiceS2, sv bS[], int n)
{
    sv temp;
    int i, j;
    float key;
    for (i = 1; i < n; i++)
    {
        j = i - 1;
        temp = bS[i];
        chooseKey(choiceS, choiceS2, bS, key, i);
        while (condition(choiceS, choiceS2, bS, key, j))
        {
            bS[j + 1] = bS[j];
            j = j - 1;
        }
        bS[j + 1] = temp;
    }
    /* selection sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (selection(choiceS, choiceS2, bS, i, j))
            {
                temp = bS[i];
                bS[i] = bS[j];
                bS[j] = temp;
            }
        }
    }*/
}

void sortInDe(int choiceS, int choiceS2)
{
    int i = 0, notFound = 1, n;
    sv bS[60];
    fstream file;
    file.open("QLSV.DAT", ios::in); //it opens a file for a read
    if (!file) // neu chua tao file
    {
        file.close();
    } else // da tao file
    {
        getline(file, bS[i].name, '|');
        file >> bS[i].stt >> bS[i].classID >> bS[i].diemRenLuyen >> bS[i].diemGiuaKy >> bS[i].diemCuoiKy;
        while(!file.eof())
        {
            i++;
            getline(file, bS[i].name, '|');
            bS[i].name.erase(remove(bS[i].name.begin(), bS[i].name.end(), '\n'), bS[i].name.end());
            file >> bS[i].stt >> bS[i].classID >> bS[i].diemRenLuyen >> bS[i].diemGiuaKy >> bS[i].diemCuoiKy;
            notFound++;
        }
    }
    if (notFound == 1)
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
    }
    file.close();
    n = i;
    InsertionSort(choiceS, choiceS2, bS, n);
    iFace.hangThuocTinh();

    for (int i = 0; i < n; i++)
    {
        iFace.printData(bS[i]); // print data from array
    }
    iFace.vienDuoiBang();
         
}

void sort()
{
    system("cls");
    fstream file;
    int notFound = 1, choiceS, choiceS2;

    iFace.vienKhungTieuDe();
    cout<<setw(44)<<right<<" "<<setw(18)<<left<<"|"<<"SAP XEP SINH VIEN"<<setw(17)<<right<<"|"<<endl;
    iFace.vienKhungTieuDe();

    file.open("QLSV.DAT", ios::in);
    if (!file) // neu chua tao file
    {
        cout<<setw(44)<<right<<" "<<setw(10)<<left<<"|"<<"(!) KHONG CO DU LIEU TRONG FILE"<<setw(11)<<right<<"|"<<endl;
        file.close();
    } else // da tao file
    {
        cout<<setw(45)<<right<<" "<<setfill('_');
        cout<<setw(50)<<"_"<<setfill(' ')<<endl;
        cout<<setw(44)<<right<<" "<<setw(51)<<left<<"|"<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(15)<<left<<"|"<<"HAY LUA CHON KIEU SAP XEP"<<setw(12)<<right<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(15)<<left<<"|"<<"1. DIEM REN LUYEN"<<setw(20)<<right<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(15)<<left<<"|"<<"2. DIEM GIUA KY"<<setw(22)<<right<<"|"<<endl;
        cout<<setw(44)<<right<<" "<<setw(15)<<left<<"|"<<"3. DIEM CUOI KY"<<setw(22)<<right<<"|"<<endl;
        cout<<setw(45)<<right<<"|"<<setfill('_');
        cout<<setw(50)<<"_"<<"|"<<setfill(' ')<<endl<<endl;
        againSort:
        cout<<setw(44)<<right<<" "<<setw(12)<<left<<" "<<"HAY NHAP LUA CHON (1, 2, 3): ";
        cin>>choiceS;
        cin.ignore();
        switch(choiceS)
        {
            case 1:
            {
                iFace.khungTangGiamDan();
                do
                {
                cout<<setw(44)<<right<<" "<<setw(12)<<left<<" "<<"HAY NHAP LUA CHON (1, 2): ";
                cin>>choiceS2;
                cin.ignore();
                }while( choiceS2 != 1 && choiceS2 != 2);
                sortInDe(choiceS, choiceS2);
                break;
            }
            case 2:
            {
                iFace.khungTangGiamDan();
                do
                {
                cout<<setw(44)<<right<<" "<<setw(12)<<left<<" "<<"HAY NHAP LUA CHON (1, 2): ";
                cin>>choiceS2;
                cin.ignore();
                }while( choiceS2 != 1 && choiceS2 != 2);
                sortInDe(choiceS, choiceS2);
                break;
            }
            case 3:
            {
                iFace.khungTangGiamDan();
                do
                {
                cout<<setw(44)<<right<<" "<<setw(12)<<left<<" "<<"HAY NHAP LUA CHON (1, 2): ";
                cin>>choiceS2;
                cin.ignore();
                }while( choiceS2 != 1 && choiceS2 != 2);
                sortInDe(choiceS, choiceS2);
                break;
            }
            default:
            {
                cout<<setw(99)<<right<<"(!) BAN DA NHAP KHONG DUNG SO THICH HOP | VUI LONG NHAP LAI"<<endl;
                goto againSort;
            }
        }
    }
}
//**************************************************************************************


void action(int &choice)
{
    int n;
    char x;
    switch(choice)
    {
        case 1: // open MENU
        {
            menu(choice);
            break;
        }
        case 2: // them sinh vien
        {
            do
            {
                insert();
                cout<<"BAN CO MUON NHAP THEM SINH VIEN KHONG? (Y/N): ";
                cin>>x;
                cin.ignore();
            } while(x == 'y' || x == 'Y');
            choose(choice);
            break;
        }
        case 3: // hien thi danh sach
        {
            display();
            choose(choice);
            break;
        }
        case 4: // chinh sua sinh vien
        {
            edit();
            choose(choice);
            break;
        }
        case 5: // tim kiem sinh vien
        {
            searchSV();
            choose(choice);
            break;
        }
        case 6: // xoa sinh vien
        {
            deleteSV();
            choose(choice);
            break;
        }
        case 7:
        {
            sort();
            choose(choice);
            break;
        }
        case 8: // thoat chuong trinh
        {
            exit(0);
        }
        default:
        {
            cout<<"(!) BAN DA NHAP KHONG DUNG SO THICH HOP | VUI LONG NHAP LAI"<<endl;
            choose(choice);
            break;
        }
    }
}


int main()
{
    char x;
    int choice;
    updateSTT();
    //BEGIN--------------
    menu(choice);
    return 0;
}