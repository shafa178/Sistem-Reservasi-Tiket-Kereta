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

bool kembaliMenu()
{
    char pilih;
    do 
    {
        cout << "\nKembali ke menu utama? (y/n) : ";
        cin >> pilih;
        pilih = tolower(pilih);
    } while (pilih != 'y' && pilih != 'n');
    
    return (pilih == 'y');
}

void tambah()
{
    Node* baru = new Node;
    garis('=');
    cout << "           PESAN TIKET BARU\n";
    garis('=');

    cin.ignore();
    cout << "Nama Penumpang : "; 
    getline(cin, baru->nama);
    
    if (baru->nama.empty()) 
    { 
		cout << "Nama tidak boleh kosong!\n"; 
		delete baru; 
		return; 
	}

    cout << "Stasiun Asal   : "; 
    getline(cin, baru->asal);
    cout << "Stasiun Tujuan : "; 
    getline(cin, baru->tujuan);
    cout << "Tanggal (dd-mm-yyyy) : "; 
    getline(cin, baru->tanggal);
    if (!validasiTanggal(baru->tanggal)) 
    { 
		cout << "Format tanggal salah!\n"; 
		delete baru; 
		return; 
	}

    cout << "\nJenis Kereta\n1. Ekonomi   - Rp 150000\n2. Bisnis    - Rp 350000\n3. Eksekutif - Rp 600000\nPilih [1-3] : ";
    int pil; 
    cin >> pil; 
    cin.ignore();
    if (pil == 1) 
		baru->jenis = "Ekonomi";
    else if (pil == 2) 
		baru->jenis = "Bisnis";
    else if (pil == 3) 
		baru->jenis = "Eksekutif";
    else 
    { 
		cout << "Pilihan tidak valid!\n"; 
		delete baru; 
		return; 
	}

    cout << "Nomor Kursi : "; 
    getline(cin, baru->kursi);

    baru->harga = hitungHarga(baru->jenis);
    baru->kodeBooking = generateKode();
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

    garis('-');
    cout << "Tiket berhasil dipesan!\nKode Booking : " << baru->kodeBooking << "\nTotal Harga : Rp " << fixed << setprecision(0) << baru->harga << endl;
    garis('-');

    simpanFile();
    if (!kembaliMenu()) 
    { 
		system("cls"); 
		tambah(); 
	}
}

void tampil()
{
    if (head == NULL) 
    { 
		cout << "Belum ada data tiket.\n"; 
		return; 
	}
    Node* temp = head; 
    int no=1;
    
    while (temp != NULL)
    {
        cout << "\nNo. " << no++ << endl; 
        garis('-');
        cout << setw(18) << left << "Kode Booking" << ": " << temp->kodeBooking << endl;
        cout << setw(18) << "Nama" << ": " << temp->nama << endl;
        cout << setw(18) << "Asal" << ": " << temp->asal << endl;
        cout << setw(18) << "Tujuan" << ": " << temp->tujuan << endl;
        cout << setw(18) << "Tanggal" << ": " << temp->tanggal << endl;
        cout << setw(18) << "Jenis" << ": " << temp->jenis << endl;
        cout << setw(18) << "Nomor Kursi" << ": " << temp->kursi << endl;
        cout << setw(18) << "Harga" << ": Rp " << fixed << setprecision(0) << temp->harga << endl;
        garis('-');
        temp = temp->next;
    }
}

void cari()
{
    if (head == NULL) 
    { 
		cout << "Data tiket kosong!\n"; 
		return; 
	}

    garis('=');
    cout << "              CARI TIKET\n";
    garis('=');

    cout << "Cari berdasarkan:\n1. Nama Penumpang\n2. Kode Booking\nPilih : ";
    int pil; 
    cin >> pil; 
    cin.ignore();

    string kunci;
    if (pil == 1) 
		cout << "Masukkan Nama : ";
    else 
		cout << "Masukkan Kode Booking : ";
    getline(cin, kunci);

    Node* temp = head;
    bool ditemukan=false;

    while(temp!=NULL)
    {
        bool cocok = (pil==1) ? (toLowerCase(temp->nama)==toLowerCase(kunci)) : (temp->kodeBooking==kunci);
        if(cocok)
        {
            ditemukan=true;
            garis('-');
            cout<<"Kode Booking : " << temp->kodeBooking << endl;
            cout<<"Nama         : " << temp->nama << endl;
            cout<<"Asal         : " << temp->asal << endl;
            cout<<"Tujuan       : " << temp->tujuan << endl;
            cout<<"Tanggal      : " << temp->tanggal << endl;
            cout<<"Jenis        : " << temp->jenis << endl;
            cout<<"Kursi        : " << temp->kursi << endl;
            cout<<"Harga        : Rp " << fixed << setprecision(0) << temp->harga << endl;
            garis('-');
        }
        temp=temp->next;
    }
    if(!ditemukan) 
		cout << "Data tidak ditemukan!\n";
    if(!kembaliMenu()) 
    { 
		system("cls"); 
		cari(); 
	}
}

void edit()
{
    if (head == NULL) 
    { 
		cout << "Data tiket kosong!\n"; 
		return; 
	}
	
	bool keluar = false;
	while(!keluar) 
	{
		tampil();
		cout << "\nPilih nomor data yang ingin diedit : ";
		int index; 
		cin >> index;

		Node* temp = head; 
		int i=1;
		
		while(temp!=NULL && i<index)
		{ 
			temp=temp->next; 
			i++; 
		}
		if(temp==NULL)
		{
			cout << "Data tidak ditemukan!\n"; 
			return; 
		}

		cin.ignore(); 
		string input;
		
		cout << "Nama Baru [" << temp->nama << "] : "; 
		getline(cin,input); 
		if(!input.empty()) 
			temp->nama=input;
			
		cout << "Asal Baru [" << temp->asal << "] : "; 
		getline(cin,input); 
		if(!input.empty()) 
			temp->asal=input;
			
		cout << "Tujuan Baru [" << temp->tujuan << "] : "; 
		getline(cin,input); 
		if(!input.empty()) 
			temp->tujuan=input;
			
		cout << "Tanggal Baru [" << temp->tanggal << "] : "; 
		getline(cin,input);
		if(!input.empty())
		{ 
			if(validasiTanggal(input)) 
				temp->tanggal=input; 
			else 
				cout<<"Format salah, tidak diubah\n";
		}
		
		cout << "Kursi Baru [" << temp->kursi << "] : "; 
		getline(cin,input); 
		if(!input.empty()) 
			temp->kursi=input;

		cout<<"\nJenis Kereta [" << temp->jenis << "]\n1. Ekonomi\n2. Bisnis\n3. Eksekutif\nPilih Jenis Baru [0 = tidak diubah] : ";
		int pil; 
		cin >> pil; 
		cin.ignore();
		
		if(pil==1) 
			temp->jenis="Ekonomi"; 
		else if(pil==2) 
			temp->jenis="Bisnis"; 
		else if(pil==3) 
			temp->jenis="Eksekutif";
			
		temp->harga=hitungHarga(temp->jenis);

		cout << "\nData berhasil diubah!\n";
		simpanFile();

		if(kembaliMenu())
			keluar = true;
		else
			system("cls"); 
	}
}

void hapus()
{
    if(head==NULL)
    { 
		cout<<"Data tiket kosong!\n"; 
		return; 
	}
	
	bool keluar = false;
    while(!keluar)
    {
		tampil();
		
		cout << "\nPilih nomor tiket yang ingin dibatalkan : "; 
		int index; 
		cin >> index;

		Node* temp=head; 
		int i=1;
		
		while(temp!=NULL && i<index)
		{ 
			temp=temp->next; 
			i++; 
		}
		if(temp==NULL)
		{ 
			cout << "Data tidak ditemukan!\n"; 
			return; 
		}

		cout << "\nYakin ingin menghapus tiket? (y/n) : "; 
		char konfirm; 
		cin >> konfirm;
		
		if(konfirm=='y'||konfirm=='Y')
		{
			if(temp==head && temp==tail) 
				head=tail=NULL;
			else if(temp==head)
			{ 
				head=head->next; 
				head->prev=NULL; 
			}
			else if(temp==tail)
			{ 
				tail=tail->prev; 
				tail->next=NULL; 
			}
			else 
			{ 
				temp->prev->next=temp->next; 
				temp->next->prev=temp->prev; 
			}
			
			delete temp; 
			cout << "Tiket berhasil dibatalkan!\n";
			
			simpanFile();
		}
		else cout << "Pembatalan dibatalkan.\n";

		if(kembaliMenu())
			keluar = true;
		else
			system("cls"); 
	}
}
