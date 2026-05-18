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
