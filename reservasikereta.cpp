#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Node 
{
    string kodeBooking;
    string nama;
    string asal;
    string tujuan;
    string tanggal;
    string jenis;
    string kursi;
    double harga;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* tail = NULL;
int totalTiket = 0;

void garis(char c = '-', int len = 50) 
{
    for (int i = 0; i < len; i++) cout << c;
    cout << endl;
}

string generateKode()
{
    totalTiket++;
    string kode = "KA";
    if (totalTiket < 10) 
		kode += "00" + to_string(totalTiket);
    else if (totalTiket < 100) 
		kode += "0" + to_string(totalTiket);
    else 
		kode += to_string(totalTiket);
    return kode;
}

string toLowerCase(string teks)
{
    transform(teks.begin(), teks.end(), teks.begin(), ::tolower);
    return teks;
}

double hitungHarga(string jenis)
{
    if (jenis == "Eksekutif") 
		return 600000;
    else if (jenis == "Bisnis") 
		return 350000;
    else 
		return 150000;
}

bool validasiTanggal(string tgl)
{
    if (tgl.length() != 10) 
		return false;
    if (tgl[2] != '-' || tgl[5] != '-') 
		return false;
    return true;
}

bool login()
{
    string user, pass;
    int attempt = 0;
    garis('=');
    cout << " SISTEM MANAJEMEN RESERVASI TIKET KERETA API\n";
    cout << "              LOGIN ADMIN\n";
    garis('=');
    while (attempt < 3)
    {
        cout << "\nPercobaan Login ke-" << attempt + 1 << "/3\n";
        cout << "Username : "; 
        cin >> user;
        cout << "Password : "; 
        cin >> pass;
        if (user == "admin" && pass == "kai124")
        {
            cout << "\nLogin berhasil!\nSelamat datang Admin Reservasi.\n";
            return true;
        }
        else 
        { 
			cout << "Username atau password salah!\n"; 
			attempt++; 
		}
    }
    cout << "\nAkun dikunci karena gagal login 3 kali.\n";
    return false;
}

void simpanFile()
{
    ofstream file("data_tiket.txt");
    Node* temp = head;
    while (temp != NULL)
    {
        file << temp->kodeBooking << "|" << temp->nama << "|" << temp->asal << "|"
             << temp->tujuan << "|" << temp->tanggal << "|" << temp->jenis << "|"
             << temp->kursi << "|" << temp->harga << endl;
        temp = temp->next;
    }
    file.close();
}

void bacaFile()
{
    ifstream file("data_tiket.txt");
    if (!file.is_open()) return;
    while (!file.eof())
    {
        Node* baru = new Node;
        getline(file, baru->kodeBooking, '|');
        getline(file, baru->nama, '|');
        getline(file, baru->asal, '|');
        getline(file, baru->tujuan, '|');
        getline(file, baru->tanggal, '|');
        getline(file, baru->jenis, '|');
        getline(file, baru->kursi, '|');
        string hargaStr; 
        getline(file, hargaStr);
        
        if (baru->kodeBooking.empty()) 
        { 
			delete baru; 
			break; 
		}
        
        baru->harga = stod(hargaStr);
        baru->next = NULL; 
        baru->prev = NULL;
        
        if (head == NULL) 
			head = tail = baru;
        else 
        { 
			tail->next = baru; 
			baru->prev = tail; 
			tail = baru; 
		}
        totalTiket++;
    }
    file.close();
}
