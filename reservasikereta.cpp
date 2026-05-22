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

void cetakGarisTabel()
{
    cout << "+" << string(4,'-')  << "+"
         << string(8,'-')  << "+"
         << string(17,'-') << "+"
         << string(12,'-') << "+"
         << string(12,'-') << "+"
         << string(12,'-') << "+"
         << string(11,'-') << "+"
         << string(7,'-')  << "+"
         << string(13,'-') << "+"
         << endl;
}

void cetakHeaderTabel()
{
    cetakGarisTabel();
    cout << left
         << "| " << setw(3)  << "No"
         << "| " << setw(7)  << "Kode"
         << "| " << setw(16) << "Nama"
         << "| " << setw(11) << "Asal"
         << "| " << setw(11) << "Tujuan"
         << "| " << setw(11) << "Tanggal"
         << "| " << setw(10) << "Jenis"
         << "| " << setw(6)  << "Kursi"
         << "| " << setw(12) << "Harga"
         << "|" << endl;
    cetakGarisTabel();
}

void tampil()
{
    if (head == NULL) 
    { 
		cout << "Belum ada data tiket.\n"; 
		return; 
	}

	cetakHeaderTabel();
	
    Node* temp = head; 
    int no=1;
    
    while (temp != NULL)
    {
        cout << left
             << "| " << setw(3)  << no++
             << "| " << setw(7)  << temp->kodeBooking
             << "| " << setw(16) << temp->nama
             << "| " << setw(11) << temp->asal
             << "| " << setw(11) << temp->tujuan
             << "| " << setw(11) << temp->tanggal
             << "| " << setw(10) << temp->jenis
             << "| " << setw(6)  << temp->kursi
             << "| Rp " << setw(9) << fixed << setprecision(0) << temp->harga
             << "|" << endl;
        cetakGarisTabel();
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

void sorting()
{
    if(head==NULL)
    { 
		cout<<"Data kosong!\n"; 
		return; 
	}

    do{
        system("cls"); 
        garis('='); 
        cout<<"            SORTING TIKET\n"; 
        garis('=');
        cout << "1. Nama Penumpang (A-Z)\n2. Harga Tiket (Termahal ke Termurah)\nPilih : ";
        int pil; 
        cin >> pil;

        bool tukar; 
        Node* ptr;
        
        do 
        {
            tukar=false; 
            ptr=head;
            
            while(ptr->next!=NULL)
            {
                bool kondisi=false;
                if(pil==1 && ptr->nama>ptr->next->nama) 
					kondisi=true;
                else if(pil==2 && ptr->harga<ptr->next->harga) 
					kondisi=true;
                else if(pil!=1 && pil!=2)
                { 
					cout << "Pilihan tidak valid!\n"; 
					return; 
				}

                if(kondisi)
                {
                    swap(ptr->kodeBooking, ptr->next->kodeBooking);
                    swap(ptr->nama, ptr->next->nama);
                    swap(ptr->asal, ptr->next->asal);
                    swap(ptr->tujuan, ptr->next->tujuan);
                    swap(ptr->tanggal, ptr->next->tanggal);
                    swap(ptr->jenis, ptr->next->jenis);
                    swap(ptr->kursi, ptr->next->kursi);
                    swap(ptr->harga, ptr->next->harga);
                    tukar=true;
                }
                ptr=ptr->next;
            }
        } while(tukar);

        cout << "\nData berhasil diurutkan!\n";

        Node* temp=head; 
        int no=1;
        
        while(temp!=NULL)
        {
            cout << "\nNo. " << no++<<endl; 
            garis('-');
            cout << setw(18) << left << "Kode Booking" << ": " << temp->kodeBooking << endl;
            cout << setw(18) << "Nama" << ": " << temp->nama << endl;
            cout << setw(18) << "Asal" << ": " << temp->asal << endl;
            cout <<setw(18) << "Tujuan" << ": " << temp->tujuan << endl;
            cout << setw(18) << "Tanggal" << ": " << temp->tanggal << endl;
            cout << setw(18) << "Jenis" << ": " << temp->jenis << endl;
            cout << setw(18) << "Nomor Kursi" << ": " << temp->kursi << endl;
            cout << setw(18) << "Harga" << ": Rp " << fixed << setprecision(0) << temp->harga << endl;
            garis('-');
            
            temp=temp->next;
        }
        simpanFile();
        
        if(!kembaliMenu())
        { 
			system("cls"); 
			continue; 
		}
        else break;
    } while(true);
}

void statistik()
{
    if(head==NULL)
    { 
		cout<<"Belum ada data tiket.\n"; 
		return; 
	}

    int ekonomi=0, bisnis=0, eksekutif=0;
    double total=0;
    Node* temp=head;

    while(temp!=NULL)
    {
        if(temp->jenis=="Ekonomi") 
			ekonomi++;
        else if(temp->jenis=="Bisnis") 
			bisnis++;
        else if(temp->jenis=="Eksekutif") 
			eksekutif++;
        total+=temp->harga;
        temp=temp->next;
    }

    garis('='); 
    cout << "           STATISTIK TIKET\n"; 
    garis('=');
    cout << setw(20) << left << "Total Tiket" << ": " << ekonomi + bisnis + eksekutif << " tiket\n";
    cout << setw(20) << "Kelas Ekonomi" << ": " << ekonomi << " tiket\n";
    cout << setw(20) << "Kelas Bisnis" << ": " << bisnis << " tiket\n";
    cout << setw(20) << "Kelas Eksekutif" << ": " << eksekutif << " tiket\n";
    garis('-');
    cout << setw(20) << "Total Pendapatan" << ": Rp " << fixed << setprecision(0) << total << endl;
    garis('=');

    if(!kembaliMenu())
    { 
		system("cls"); 
		statistik(); 
	}
}

int main()
{
    if(!login()) 
        return 0;
    bacaFile();
    int pilih;
    
    do
    {
        system("cls");
        garis('='); 
        cout << " SISTEM MANAJEMEN RESERVASI TIKET KERETA API\n"; 
        garis('=');
        cout << "1. Pesan Tiket\n2. Lihat Daftar Tiket\n3. Cari Tiket\n4. Edit Data Tiket\n5. Batalkan Tiket\n6. Urutkan Tiket\n7. Statistik Tiket\n0. Keluar\n";
        garis('-'); 
        cout << "Pilih Menu : "; 
        cin >> pilih; 
        cout << endl;

        switch(pilih)
        {
            case 1: 
				system("cls"); 
				tambah(); 
				break;
            case 2: 
				system("cls"); 
				tampil(); 
				break;
            case 3: 
				system("cls"); 
				cari(); 
				break;
            case 4: 
				system("cls"); 
				edit(); 
				break;
            case 5: 
				system("cls"); 
				hapus(); 
				break;
            case 6: 
				system("cls"); 
				sorting(); 
				break;
            case 7: 
				system("cls"); 
				statistik(); 
				break;
            case 0: 
				system("cls"); 
				cout << "Terima kasih telah menggunakan sistem.\n"; 
				break;
            default: 
				system("cls"); 
				cout << "Menu tidak valid!\n";
        }
        
        system("pause");
        
    } while(pilih != 0);

    return 0;
}
