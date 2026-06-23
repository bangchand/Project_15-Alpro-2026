// =========================================
// --- utils.hpp ---
// =========================================
#pragma once
#include <string>
#include <vector>

using namespace std;

string getCurrentDate();
void clearScreen();
void pauseScreen();
void bersihkanLayar();
void jedaLayar();

int inputChoice(int min, int max);

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";

// =========================================
// --- manajemen_akun.hpp ---
// =========================================
#pragma once
#include <string>
// #include "product.hpp"

const int MAX_PENGGUNA = 100;

struct Akun {
    std::string username;
    std::string password;
    std::string role; 
    std::string nama;
};

void muatDataAkun(Akun dataPengguna[], int &jumlahPengguna);
void simpanDataAkun(Akun dataPengguna[], int jumlahPengguna);

void bersihkanLayar();
void jedaLayar();
bool tambahAkunKasir(Akun dataPengguna[], int &jumlahPengguna, std::string username, std::string password, std::string nama);
void lihatDaftarKasir(Akun dataPengguna[], int jumlahPengguna);
bool editAkunKasir(Akun dataPengguna[], int jumlahPengguna, std::string usernameTarget, std::string usernameBaru, std::string passwordBaru, std::string namaBaru);
bool hapusAkunKasir(Akun dataPengguna[], int &jumlahPengguna, std::string usernameTarget);

std::string prosesLogin(Akun &userAktif, Akun dataPengguna[], int jumlahPengguna);
void menuAdmin(Akun adminAktif, Product products[], int& productCount, Akun dataPengguna[], int& jumlahPengguna);
void menuManajemenAkun(Akun dataPengguna[], int &jumlahPengguna);


// =========================================
// --- product.hpp ---
// =========================================
#pragma once
#include <string>

const int MAX_PRODUCT = 100;

struct Product {
    std::string id;
    std::string name;
    double price;
    int stock;
};

void tambahProduk(Product daftarProduk[], int& jumlahProduk);
void editProduk(Product daftarProduk[], int jumlahProduk);
void hapusProduk(Product daftarProduk[], int& jumlahProduk);
void lihatProduk(Product daftarProduk[], int jumlahProduk);
void cariProduk(Product daftarProduk[], int jumlahProduk);
void menuProduk(Product daftarProduk[], int& jumlahProduk);

void muatDataProduk(Product daftarProduk[], int& jumlahProduk);
void simpanDataProduk(Product daftarProduk[], int jumlahProduk);


// =========================================
// --- cart.hpp ---
// =========================================
#pragma once
// #include "product.hpp"
#include <string>

using namespace std;

const int MAX_CART = 100;

struct CartItem {
    string productId;
    string productName;
    double price;
    int quantity;
    double subtotal;

    void setItem(Product* product, int qty);
    void addQuantity(int qty);
};

CartItem* findCartItem(CartItem cart[], int cartCount, string productId);
Product* findProduct(Product products[], int productCount, string productId);
double calculateTotal(CartItem cart[], int cartCount);
void addToCart(Product products[], int productCount, CartItem cart[], int &cartCount, string productId, int qty);
void showCart(CartItem cart[], int cartCount);


// =========================================
// --- transaction.hpp ---
// =========================================
// #include "product.hpp"
// #include "cart.hpp"
// #include "utils.hpp"
// #include "kas.hpp"

using namespace std;

const int MAX_TRANSACTION = 100;

struct Transaction {
    string id;
    string cashierId;
    string date;
    double total;
    double payment;
    double change;

    void setTransaction(string trxId, string userId, string trxDate, double trxTotal);
    bool pay(double money);
};

void checkout(
    Product products[],
    int productCount,
    CartItem cart[],
    int cartCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
);

void startTransaction(
    Product products[],
    int productCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
);

void muatDataTransaksi(Transaction transactions[], int &transactionCount);
void simpanDataTransaksi(Transaction transactions[], int transactionCount);
void tampilkanMenuLaporan(Transaction transactions[], int transactionCount);


// =========================================
// --- kas.hpp ---
// =========================================
#ifndef KAS_HPP
#define KAS_HPP

struct Kas {
    long long saldo;
};

void muatDataKas(Kas* dataKas);
void simpanDataKas(const Kas* dataKas);

void cekSaldoKas(const Kas* dataKas);
void setorKas(Kas* dataKas);
void tarikKas(Kas* dataKas);
void tampilkanMenuKas(Kas* dataKas);

#endif

// =========================================
// --- stocks.hpp ---
// =========================================
#pragma once
// #include "product.hpp"

void Stokmenu(Product products[], int productsCount);
void tambahStok(Product products[], int productsCount);
void kurangStok(Product products[], int productsCount);
void lihatStok(Product products[], int productsCount);

// =========================================
// --- core.hpp ---
// =========================================
#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

// #include "utils.hpp"

// #include "manajemen_akun.hpp"
// #include "product.hpp"
// #include "stocks.hpp"
// #include "cart.hpp"
// #include "kas.hpp"
// #include "transaction.hpp"

using namespace std;


// =========================================
// --- utils.cpp ---
// =========================================
// #include "core.hpp"
#include <limits>
#include <ctime>

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string date = to_string(ltm->tm_mday) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(1900 + ltm->tm_year);

    return date;
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void pauseScreen() {
    cout << "\nTekan [Enter] untuk melanjutkan...";
    if (cin.peek() == '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
}

void bersihkanLayar() {
    clearScreen();
}

void jedaLayar() {
    pauseScreen();
}

// Fungsi-fungsi kompleks berbasis vector dihapus agar sesuai dengan materi Alpro

int inputChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Pilih (" << min << "-" << max << "): ";
        cin >> choice;
        
        if (cin.fail()) {
            cout << RED << "Input tidak valid. Harap masukkan angka.\n" << RESET;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (choice >= min && choice <= max) {
            return choice;
        } else {
            cout << RED << "Pilihan di luar rentang. Silakan coba lagi.\n" << RESET;
        }
    }
}

// =========================================
// --- LOGIN.cpp ---
// =========================================
// #include "core.hpp"

void tampilkanMenuLoginUI();
void tampilkanMenuAdminUI(string nama);

// ================= FUNGSI SISTEM (LOGIN & MENU) =================

string prosesLogin(Akun &userAktif, Akun dataPengguna[], int jumlahPengguna) {
    bersihkanLayar();
    tampilkanMenuLoginUI();
    
    string uname, pwd;
    cout << "Username : "; cin >> uname;
    
    if (uname == "exit") {
        return "Exit"; 
    }

    cout << "Password : "; cin >> pwd;

    // Cek username, kecocokan password, lalu kembalikan rolenya
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == uname && dataPengguna[i].password == pwd) {
            userAktif = dataPengguna[i]; 
            
            if (dataPengguna[i].role == "Admin") {
                return "Admin";
            } else if (dataPengguna[i].role == "Kasir") {
                return "Kasir";
            }
        }
    }
    
    return "Gagal"; 
}

void menuAdmin(Akun adminAktif, Product products[], int& productCount, Akun dataPengguna[], int& jumlahPengguna) {
    bool sesiAktif = true;
    while (sesiAktif) {
        bersihkanLayar();
        tampilkanMenuAdminUI(adminAktif.nama);
        
        int pilihanInt = inputChoice(0, 3);
        string pilihan = to_string(pilihanInt);

        if (pilihan == "1") {
            menuManajemenAkun(dataPengguna, jumlahPengguna);
        } 
        else if (pilihan == "2") {
            menuProduk(products, productCount);
        }
        else if (pilihan == "3") {
            Stokmenu(products, productCount);
        }
        else if (pilihan == "0") {
            cout << GREEN << "\n[+] Anda berhasil logout dari Admin.\n" << RESET;
            jedaLayar();
            return; 
        }
    }
}

void tampilkanMenuLoginUI() {
    cout << CYAN << "=========================================\n";
    cout << "               MENU LOGIN                \n";
    cout << "=========================================\n" << RESET;
    cout << YELLOW << "Ketik 'exit' pada Username untuk keluar program.\n\n" << RESET;
}

void tampilkanMenuAdminUI(string nama) {
    cout << CYAN << "=========================================\n";
    cout << "               MENU ADMIN                \n";
    cout << "=========================================\n" << RESET;
    cout << BOLD << "Halo, " << nama << "!\n\n" << RESET;
    cout << "  [1] Manajemen Akun\n";
    cout << "  [2] Manajemen Produk\n";
    cout << "  [3] Manajemen Stok\n";
    cout << "  [0] Logout\n";
    cout << "-----------------------------------------\n";
}


// =========================================
// --- manajemen akun.cpp ---
// =========================================
// #include "core.hpp"

const string FILE_AKUN = "data_akun.txt";

void headerDaftarKasirUI();

void muatDataAkun(Akun dataPengguna[], int &jumlahPengguna) {
    ifstream file(FILE_AKUN);
    if (!file.is_open()) return;
    
    jumlahPengguna = 0;
    string u, p, r, n;
    while (file >> u >> p >> r) {
        file.ignore(); // space
        getline(file, n);
        dataPengguna[jumlahPengguna] = Akun{u, p, r, n};
        jumlahPengguna++;
    }
    file.close();
}

void simpanDataAkun(Akun dataPengguna[], int jumlahPengguna) {
    ofstream file(FILE_AKUN);
    if (!file.is_open()) return;
    for (int i = 0; i < jumlahPengguna; i++) {
        file << dataPengguna[i].username << " "
             << dataPengguna[i].password << " "
             << dataPengguna[i].role << " "
             << dataPengguna[i].nama << "\n";
    }
    file.close();
}

bool tambahAkunKasir(Akun dataPengguna[], int &jumlahPengguna, string username, string password, string nama) {
    if (jumlahPengguna >= MAX_PENGGUNA) {
        cout << RED << "\n[!] Gagal! Kapasitas data pengguna sudah penuh.\n" << RESET;
        return false;
    }

    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == username) {
            cout << RED << "\n[!] Gagal! Username \"" << username << "\" sudah digunakan.\n" << RESET;
            return false;
        }
    }
    
    dataPengguna[jumlahPengguna].username = username;
    dataPengguna[jumlahPengguna].password = password;
    dataPengguna[jumlahPengguna].role = "Kasir";
    dataPengguna[jumlahPengguna].nama = nama;
    
    jumlahPengguna++;
    simpanDataAkun(dataPengguna, jumlahPengguna);
    
    cout << GREEN << "\n[+] Sukses! Akun Kasir '" << nama << "' berhasil ditambahkan.\n" << RESET;
    return true;
}

void lihatDaftarKasir(Akun dataPengguna[], int jumlahPengguna) {
    headerDaftarKasirUI();
    
    bool adaKasir = false;
    int nomor = 1;
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].role == "Kasir") {
            cout << left << setw(5) << nomor 
                 << setw(15) << dataPengguna[i].nama 
                 << setw(15) << dataPengguna[i].username 
                 << dataPengguna[i].password << "\n";
            adaKasir = true;
            nomor++;
        }
    }
    
    if (!adaKasir) {
        cout << YELLOW << "       [-] Belum ada akun kasir.        \n" << RESET;
    }
    cout << CYAN << "==========================================================\n" << RESET;
}

bool editAkunKasir(Akun dataPengguna[], int jumlahPengguna, string usernameTarget, string usernameBaru, string passwordBaru, string namaBaru) {
    int indeksTarget = -1;
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == usernameTarget && dataPengguna[i].role == "Kasir") {
            indeksTarget = i;
            break;
        }
    }

    if (indeksTarget == -1) {
        cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << usernameTarget << "' tidak ditemukan.\n" << RESET;
        return false;
    }

    if (!usernameBaru.empty() && usernameBaru != "-" && usernameBaru != usernameTarget) {
        for (int i = 0; i < jumlahPengguna; i++) {
            if (dataPengguna[i].username == usernameBaru) {
                cout << RED << "\n[!] Gagal! Username baru '" << usernameBaru << "' sudah digunakan oleh akun lain.\n" << RESET;
                return false;
            }
        }
        dataPengguna[indeksTarget].username = usernameBaru;
    }

    if (!passwordBaru.empty() && passwordBaru != "-") dataPengguna[indeksTarget].password = passwordBaru;
    if (!namaBaru.empty() && namaBaru != "-") dataPengguna[indeksTarget].nama = namaBaru;
    
    simpanDataAkun(dataPengguna, jumlahPengguna);
    
    cout << GREEN << "\n[+] Sukses! Data akun berhasil diperbarui.\n" << RESET;
    return true;
}


bool hapusAkunKasir(Akun dataPengguna[], int &jumlahPengguna, string usernameTarget) {
    for (int i = 0; i < jumlahPengguna; i++) {
        if (dataPengguna[i].username == usernameTarget && dataPengguna[i].role == "Kasir") {
            
            // Geser elemen-elemen setelahnya ke kiri
            for (int j = i; j < jumlahPengguna - 1; j++) {
                dataPengguna[j] = dataPengguna[j + 1];
            }
            
            jumlahPengguna--;
            simpanDataAkun(dataPengguna, jumlahPengguna);
            cout << GREEN << "\n[+] Sukses! Akun Kasir '" << usernameTarget << "' telah dihapus.\n" << RESET;
            return true;
        }
    }
    cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << usernameTarget << "' tidak ditemukan.\n" << RESET;
    return false;
}

void headerDaftarKasirUI() {
    cout << CYAN << "==========================================================\n";
    cout << "                    DAFTAR AKUN KASIR                     \n";
    cout << "==========================================================\n" << RESET;
    cout << left << setw(5) << "NO" << setw(15) << "NAMA" << setw(15) << "USERNAME" << "PASSWORD\n";
    cout << "----------------------------------------------------------\n";
}

void tampilkanMenuManajemenAkunUI() {
    cout << CYAN << "=========================================\n";
    cout << "          MANAJEMEN AKUN KASIR           \n";
    cout << "=========================================\n" << RESET;
    cout << "  [1] Tambah Akun Kasir\n";
    cout << "  [2] Lihat Daftar Kasir\n";
    cout << "  [3] Edit Akun Kasir\n";
    cout << "  [4] Hapus Akun Kasir\n";
    cout << "  [0] Kembali\n";
    cout << "-----------------------------------------\n";
}

void menuManajemenAkun(Akun dataPengguna[], int &jumlahPengguna) {
    int pilihan;
    do {
        bersihkanLayar();
        tampilkanMenuManajemenAkunUI();
        pilihan = inputChoice(0, 4);

        if (pilihan == 1) {
            string u, p, n;
            cout << CYAN << "\n==========================================================\n";
            cout << "                       TAMBAH KASIR                       \n";
            cout << "==========================================================\n" << RESET;
            cout << "Username Baru : "; cin >> u;
            cout << "Password Baru : "; cin >> p;
            cout << "Nama Kasir    : "; 
            cin.ignore(); getline(cin, n);
            tambahAkunKasir(dataPengguna, jumlahPengguna, u, p, n);
            jedaLayar();
        } 
        else if (pilihan == 2) {
            bersihkanLayar();
            lihatDaftarKasir(dataPengguna, jumlahPengguna);
            jedaLayar();
        } 
        else if (pilihan == 3) {
            bersihkanLayar();
            lihatDaftarKasir(dataPengguna, jumlahPengguna);
            string target, u, p, n;
            cout << CYAN << "\n==========================================================\n";
            cout << "                        EDIT KASIR                        \n";
            cout << "==========================================================\n" << RESET;
            cout << "Masukkan Username yang ingin diedit: "; cin >> target;
            
            bool ketemu = false;
            for (int i = 0; i < jumlahPengguna; i++) {
                if (dataPengguna[i].username == target && dataPengguna[i].role == "Kasir") {
                    ketemu = true;
                    break;
                }
            }
            
            if (!ketemu) {
                cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << target << "' tidak ditemukan.\n" << RESET;
            } else {
                cout << "Username Baru (- jika tidak diubah): "; cin >> u;
                cout << "Password Baru (- jika tidak diubah): "; cin >> p;
                cout << "Nama Baru (- jika tidak diubah)    : "; 
                cin.ignore(); getline(cin, n);
                if(n.empty()) n = "-";
                editAkunKasir(dataPengguna, jumlahPengguna, target, u, p, n);
            }
            jedaLayar();
        } 
        else if (pilihan == 4) {
            bersihkanLayar();
            lihatDaftarKasir(dataPengguna, jumlahPengguna);
            string target;
            cout << CYAN << "\n==========================================================\n";
            cout << "                       HAPUS KASIR                        \n";
            cout << "==========================================================\n" << RESET;
            cout << "Masukkan Username yang ingin dihapus: "; cin >> target;
            
            bool ketemu = false;
            for (int i = 0; i < jumlahPengguna; i++) {
                if (dataPengguna[i].username == target && dataPengguna[i].role == "Kasir") {
                    ketemu = true;
                    break;
                }
            }
            
            if (!ketemu) {
                cout << RED << "\n[!] Gagal! Akun Kasir dengan username '" << target << "' tidak ditemukan.\n" << RESET;
            } else {
                hapusAkunKasir(dataPengguna, jumlahPengguna, target);
            }
            jedaLayar();
        }
    } while (pilihan != 0);
}

// =========================================
// --- product.cpp ---
// =========================================
// #include "core.hpp"

const string FILE_PRODUK = "data_produk.txt";

void muatDataProduk(Product daftarProduk[], int& jumlahProduk) {
    ifstream file(FILE_PRODUK);
    if (!file.is_open()) return;
    
    jumlahProduk = 0;
    string id, name;
    double price;
    int stock;
    while (file >> id >> price >> stock) {
        file.ignore();
        getline(file, name);
        daftarProduk[jumlahProduk] = Product{id, name, price, stock};
        jumlahProduk++;
    }
    file.close();
}

void simpanDataProduk(Product daftarProduk[], int jumlahProduk) {
    ofstream file(FILE_PRODUK);
    if (!file.is_open()) return;
    for (int i = 0; i < jumlahProduk; i++) {
        file << daftarProduk[i].id << " "
             << daftarProduk[i].price << " "
             << daftarProduk[i].stock << " "
             << daftarProduk[i].name << "\n";
    }
    file.close();
}

void headerDaftarProdukUI();
void tampilkanMenuProdukUI();

void tambahProduk(Product daftarProduk[], int& jumlahProduk) {
    cout << CYAN << "\n==========================================================\n";
    cout << "                      TAMBAH PRODUK                       \n";
    cout << "==========================================================\n" << RESET;

    string idBaru;
    cout << "ID Produk    : ";
    cin >> idBaru;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == idBaru) {
            cout << RED << "\n[!] Gagal! ID Produk \"" << idBaru << "\" sudah digunakan.\n" << RESET;
            return;
        }
    }

    daftarProduk[jumlahProduk].id = idBaru;
    cin.ignore();

    cout << "Nama Produk  : ";
    getline(cin, daftarProduk[jumlahProduk].name);

    cout << "Harga Produk : ";
    cin >> daftarProduk[jumlahProduk].price;

    cout << "Stok Produk  : ";
    cin >> daftarProduk[jumlahProduk].stock;

    jumlahProduk++;
    simpanDataProduk(daftarProduk, jumlahProduk);

    cout << GREEN << "\n[+] Sukses! Produk berhasil ditambahkan.\n" << RESET;
}

void lihatProduk(Product daftarProduk[], int jumlahProduk) {
    if (jumlahProduk == 0) {
        cout << YELLOW << "Belum ada produk.\n" << RESET;
        return;
    }

    headerDaftarProdukUI();

    for (int i = 0; i < jumlahProduk; i++) {
        cout << left << setw(10) << daftarProduk[i].id 
             << setw(20) << daftarProduk[i].name 
             << setw(15) << daftarProduk[i].price 
             << daftarProduk[i].stock << "\n";
    }
    
    cout << CYAN << "==========================================================\n" << RESET;
}

void cariProduk(Product daftarProduk[], int jumlahProduk) {
    string id;
    bool ditemukan = false;

    cout << CYAN << "\n==========================================================\n";
    cout << "                       CARI PRODUK                        \n";
    cout << "==========================================================\n" << RESET;
    cout << "Masukkan ID Produk: ";
    cin >> id;

    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            cout << GREEN << "\n[+] Produk ditemukan!\n" << RESET;
            cout << "ID     : " << daftarProduk[i].id << endl;
            cout << "Nama   : " << daftarProduk[i].name << endl;
            cout << "Harga  : Rp " << (long long)daftarProduk[i].price << endl;
            cout << "Stok   : " << daftarProduk[i].stock << endl;

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << RED << "\n[!] Produk tidak ditemukan.\n" << RESET;
    }
}

void editProduk(Product daftarProduk[], int jumlahProduk) {
    bersihkanLayar();
    lihatProduk(daftarProduk, jumlahProduk);
    
    string id;
    bool ditemukan = false;

    cout << CYAN << "\n==========================================================\n";
    cout << "                       EDIT PRODUK                        \n";
    cout << "==========================================================\n" << RESET;
    cout << "Masukkan ID Produk yang akan diedit: ";
    cin >> id;

    int indexEdit = -1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            indexEdit = i;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << RED << "Produk tidak ditemukan.\n" << RESET;
        jedaLayar();
        return;
    }

    cin.ignore();
    cout << "Nama Baru   : ";
    getline(cin, daftarProduk[indexEdit].name);

    cout << "Harga Baru  : ";
    cin >> daftarProduk[indexEdit].price;

    cout << "Stok Baru   : ";
    cin >> daftarProduk[indexEdit].stock;
    
    simpanDataProduk(daftarProduk, jumlahProduk);

    cout << GREEN << "\n[+] Sukses! Produk berhasil diperbarui.\n" << RESET;
    jedaLayar();
}

void hapusProduk(Product daftarProduk[], int& jumlahProduk) {
    bersihkanLayar();
    lihatProduk(daftarProduk, jumlahProduk);
    
    string id;
    bool ditemukan = false;

    cout << CYAN << "\n==========================================================\n";
    cout << "                      HAPUS PRODUK                        \n";
    cout << "==========================================================\n" << RESET;
    cout << "Masukkan ID Produk yang akan dihapus: ";
    cin >> id;

    int indexHapus = -1;
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) {
            indexHapus = i;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << RED << "Produk tidak ditemukan.\n" << RESET;
        jedaLayar();
        return;
    }

    for (int j = indexHapus; j < jumlahProduk - 1; j++) {
        daftarProduk[j] = daftarProduk[j + 1];
    }
    jumlahProduk--;
    
    simpanDataProduk(daftarProduk, jumlahProduk);

    cout << GREEN << "\n[+] Sukses! Produk berhasil dihapus.\n" << RESET;
    jedaLayar();
}

void menuProduk(Product daftarProduk[], int& jumlahProduk) {
    int pilihan;

    do {
        bersihkanLayar();
        tampilkanMenuProdukUI();
        pilihan = inputChoice(0, 5);

        switch (pilihan) {
            case 1:
                bersihkanLayar();
                tambahProduk(daftarProduk, jumlahProduk);
                jedaLayar();
                break;
            case 2:
                bersihkanLayar();
                lihatProduk(daftarProduk, jumlahProduk);
                jedaLayar();
                break;
            case 3:
                bersihkanLayar();
                cariProduk(daftarProduk, jumlahProduk);
                jedaLayar();
                break;
            case 4:
                editProduk(daftarProduk, jumlahProduk);
                break;
            case 5:
                hapusProduk(daftarProduk, jumlahProduk);
                break;
            case 0:
                cout << "Kembali ke menu utama..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);
}

void headerDaftarProdukUI() {
    cout << CYAN << "==========================================================\n";
    cout << "                      DAFTAR PRODUK                       \n";
    cout << "==========================================================\n" << RESET;
    cout << left << setw(10) << "ID" << setw(20) << "NAMA" << setw(15) << "HARGA" << "STOK\n";
    cout << "----------------------------------------------------------\n";
}

void tampilkanMenuProdukUI() {
    cout << CYAN << "=========================================\n";
    cout << "            MANAJEMEN PRODUK             \n";
    cout << "=========================================\n" << RESET;
    cout << "  [1] Tambah Produk\n";
    cout << "  [2] Lihat Daftar Produk\n";
    cout << "  [3] Cari Produk\n";
    cout << "  [4] Edit Produk\n";
    cout << "  [5] Hapus Produk\n";
    cout << "  [0] Kembali\n";
    cout << "-----------------------------------------\n";
}

// =========================================
// --- cart.cpp ---
// =========================================
// #include "core.hpp"

void headerKeranjangUI();

void CartItem::setItem(Product* product, int qty) {
    productId = product->id;
    productName = product->name;
    price = product->price;
    quantity = qty;
    subtotal = price * quantity;
}

void CartItem::addQuantity(int qty) {
    quantity += qty;
    subtotal = price * quantity;
}

CartItem* findCartItem(CartItem cart[], int cartCount, string productId) {
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].productId == productId) {
            return &cart[i];
        }
    }
    return nullptr;
}

Product* findProduct(Product products[], int productCount, string productId) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            return &products[i];
        }
    }
    return nullptr;
}

double calculateTotal(CartItem cart[], int cartCount) {
    double total = 0;
    for (int i = 0; i < cartCount; i++) {
        total += cart[i].subtotal;
    }
    return total;
}

void addToCart(
    Product products[],
    int productCount,
    CartItem cart[],
    int &cartCount,
    string productId,
    int qty
) {
    Product* product = findProduct(products, productCount, productId);

    if (product == nullptr) {
        cout << "Produk tidak ditemukan.\n";
        return;
    }

    CartItem* item = findCartItem(cart, cartCount, productId);

    int currentQty = 0;
    if (item != nullptr) {
        currentQty = item->quantity;
    }

    if (product->stock < currentQty + qty) {
        cout << "Stok tidak cukup.\n";
        return;
    }

    if (item != nullptr) {
        item->addQuantity(qty);
    } else {
        cart[cartCount].setItem(product, qty);
        cartCount++;
    }

    cout << "Produk berhasil ditambahkan.\n";
}

void showCart(CartItem cart[], int cartCount) {
    bersihkanLayar();

    if (cartCount == 0) {
        cout << YELLOW << "Keranjang kosong.\n" << RESET;
        return;
    }

    headerKeranjangUI();

    for (int i = 0; i < cartCount; i++) {
        cout << left << setw(20) << cart[i].productName
             << setw(10) << ("x" + to_string(cart[i].quantity))
             << "Rp " << static_cast<long long>(cart[i].subtotal) << endl;
    }

    cout << CYAN << "==================================================\n" << RESET;
}

void headerKeranjangUI() {
    cout << CYAN << "==================================================\n";
    cout << "                    KERANJANG                     \n";
    cout << "==================================================\n" << RESET;
    cout << left << setw(20) << "NAMA PRODUK" << setw(10) << "JUMLAH" << "SUBTOTAL\n";
    cout << "--------------------------------------------------\n";
}


// =========================================
// --- transaction.cpp ---
// =========================================
// #include "core.hpp"

const string FILE_TRANSAKSI = "data_transaksi.txt";

void muatDataTransaksi(Transaction transactions[], int &transactionCount) {
    ifstream file(FILE_TRANSAKSI);
    if (!file.is_open()) return;
    
    transactionCount = 0;
    string id, cid, d;
    double t, p, c;
    while (file >> id >> cid >> d >> t >> p >> c) {
        transactions[transactionCount].id = id;
        transactions[transactionCount].cashierId = cid;
        transactions[transactionCount].date = d;
        transactions[transactionCount].total = t;
        transactions[transactionCount].payment = p;
        transactions[transactionCount].change = c;
        transactionCount++;
    }
    file.close();
}

void simpanDataTransaksi(Transaction transactions[], int transactionCount) {
    ofstream file(FILE_TRANSAKSI);
    if (!file.is_open()) return;
    for (int i = 0; i < transactionCount; i++) {
        file << transactions[i].id << " "
             << transactions[i].cashierId << " "
             << transactions[i].date << " "
             << transactions[i].total << " "
             << transactions[i].payment << " "
             << transactions[i].change << "\n";
    }
    file.close();
}

void tampilkanPetunjukUI();
void headerRiwayatTransaksiUI();
void headerDaftarProdukTerjualUI();
void tampilkanMenuLaporanUI();

void Transaction::setTransaction(string trxId, string userId, string trxDate, double trxTotal) {
    id = trxId;
    cashierId = userId;
    date = trxDate;
    total = trxTotal;
    payment = 0;
    change = 0;
}

bool Transaction::pay(double money) {
    if (money < total) {
        return false;
    }

    payment = money;
    change = payment - total;
    return true;
}

void checkout(
    Product products[],
    int productCount,
    CartItem cart[],
    int cartCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
) {
    if (cartCount == 0) {
        cout << RED << "\n[!] Keranjang masih kosong. Tidak ada yang bisa dicheckout.\n" << RESET;
        return;
    }

    Transaction trx;
    trx.setTransaction(
        "TRX" + to_string(transactionCount + 1),
        cashierId,
        getCurrentDate(),
        calculateTotal(cart, cartCount)
    );

    double money;
    cout << CYAN << "\n=========================================\n";
    cout << "               CHECKOUT                  \n";
    cout << "=========================================\n" << RESET;
    cout << BOLD << "Total Tagihan : Rp " << (long long)trx.total << RESET << endl;
    cout << "Masukkan Uang : Rp ";
    cin >> money;

    while (!trx.pay(money)) {
        cout << RED << "[!] Uang tidak cukup. Masih kurang Rp " << (trx.total - money) << RESET << "\n";
        cout << "Masukkan Uang : Rp ";
        cin >> money;
    }

    // Update stok
    for (int i = 0; i < cartCount; i++) {
        Product* product = findProduct(products, productCount, cart[i].productId);
        if (product != nullptr) {
            product->stock -= cart[i].quantity;
        }
    }

    cash->saldo += trx.total;
    simpanDataKas(cash);
    transactions[transactionCount] = trx;
    transactionCount++;
    
    simpanDataTransaksi(transactions, transactionCount);
    simpanDataProduk(products, productCount);

    cout << GREEN << "\n[+] Transaksi berhasil!\n" << RESET;
    cout << "Kembalian Anda: Rp " << trx.change << "\n";
    cout << CYAN << "=========================================\n" << RESET;
}

void startTransaction(
    Product products[],
    int productCount,
    Transaction transactions[],
    int &transactionCount,
    Kas* cash,
    string cashierId
) {
    CartItem cart[MAX_CART];
    int cartCount = 0;

    string input;
    string lastProductId = "";

    while (true) {
        bersihkanLayar();
        cout << CYAN << "=========================================\n";
        cout << "             TRANSAKSI BARU              \n";
        cout << "=========================================\n" << RESET;
        
        showCart(cart, cartCount);

        tampilkanPetunjukUI();
        
        cout << "\n>> Input: ";
        cin >> input;

        if (input == "q") {
            if (lastProductId == "") {
                cout << RED << "[!] Belum ada barang yang dipilih sebelumnya.\n" << RESET;
                jedaLayar();
                continue;
            }
            
            CartItem* item = findCartItem(cart, cartCount, lastProductId);

            if (item != nullptr) {
                int qty;
                cout << "Masukkan jumlah baru untuk " << BOLD << item->productName << RESET << " : ";
                cin >> qty;
                
                item->quantity = 0;
                item->subtotal = 0;

                addToCart(products, productCount, cart, cartCount, lastProductId, qty);
            }
        }
        else if (input == "c") {
            checkout(
                products,
                productCount,
                cart,
                cartCount,
                transactions,
                transactionCount,
                cash,
                cashierId
            );
            jedaLayar();
            break;
        }
        else if (input == "x") {
            cout << YELLOW << "\n[!] Transaksi dibatalkan.\n" << RESET;
            jedaLayar();
            break;
        }
        else {
            addToCart(products, productCount, cart, cartCount, input, 1);
            lastProductId = input;
        }
    }
}

void transactionHistory(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << YELLOW << "\n[-] Belum ada transaksi yang tercatat.\n" << RESET;
        return;
    }

    headerRiwayatTransaksiUI();
    
    for (int i = 0; i < transactionCount; i++) {
        cout << left << setw(10) << transactions[i].id 
             << setw(10) << transactions[i].cashierId 
             << setw(15) << transactions[i].date 
             << setw(12) << transactions[i].total 
             << setw(12) << transactions[i].payment 
             << transactions[i].change << endl;
    }
    cout << "=================================================================\n";
}

void totalSales(Transaction transactions[], int transactionCount) {
    double total = 0;
    for (int i = 0; i < transactionCount; i++) {
        total += transactions[i].total;
    }
    cout << CYAN << "\n=========================================\n";
    cout << "            TOTAL PENJUALAN              \n";
    cout << "=========================================\n" << RESET;
    cout << "Keseluruhan Penjualan : " << GREEN << BOLD << "Rp " << (long long)total << RESET << endl;
    cout << "=========================================\n";
}

void soldProducts(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << YELLOW << "\n[-] Belum ada transaksi, belum ada produk terjual.\n" << RESET;
        return;
    }

    headerDaftarProdukTerjualUI();
    
    for (int i = 0; i < transactionCount; i++) {
        cout << left << setw(10) << transactions[i].id 
             << setw(12) << transactions[i].cashierId 
             << setw(15) << transactions[i].date 
             << "Rp " << transactions[i].total << endl;
    }
    cout << "==================================================\n";
}

void tampilkanMenuLaporan(Transaction transactions[], int transactionCount) {
    int pilihan;
    do {
        bersihkanLayar();
        tampilkanMenuLaporanUI();
        pilihan = inputChoice(0, 3);

        switch (pilihan) {
            case 1:
                transactionHistory(transactions, transactionCount);
                jedaLayar();
                break;
            case 2:
                totalSales(transactions, transactionCount);
                jedaLayar();
                break;
            case 3:
                soldProducts(transactions, transactionCount);
                jedaLayar();
                break;
            case 0:
                break;
        }
    } while (pilihan != 0);
}

void tampilkanPetunjukUI() {
    cout << CYAN << "=========================================\n";
    cout << "                PETUNJUK                 \n";
    cout << "=========================================\n" << RESET;
    cout << "- Ketik [Kode Barang] untuk menambah ke keranjang\n";
    cout << "- Ketik 'q' untuk mengubah jumlah (qty) barang terakhir\n";
    cout << "- Ketik 'c' untuk lanjut ke Checkout\n";
    cout << "- Ketik 'x' untuk membatalkan transaksi\n";
    cout << "-----------------------------------------\n";
}

void headerRiwayatTransaksiUI() {
    cout << CYAN << "=================================================================\n";
    cout << "                       RIWAYAT TRANSAKSI                         \n";
    cout << "=================================================================\n" << RESET;
    cout << left << setw(10) << "ID TRX" 
         << setw(10) << "KASIR" 
         << setw(15) << "TANGGAL" 
         << setw(12) << "TOTAL" 
         << setw(12) << "DIBAYAR" 
         << "KEMBALIAN\n";
    cout << "-----------------------------------------------------------------\n";
}

void headerDaftarProdukTerjualUI() {
    cout << CYAN << "==================================================\n";
    cout << "               DAFTAR PRODUK TERJUAL              \n";
    cout << "==================================================\n" << RESET;
    cout << left << setw(10) << "ID TRX" 
         << setw(12) << "KASIR" 
         << setw(15) << "TANGGAL" 
         << "TOTAL\n";
    cout << "--------------------------------------------------\n";
}

void tampilkanMenuLaporanUI() {
    cout << CYAN << "==================================================\n";
    cout << "               LAPORAN TRANSAKSI                  \n";
    cout << "==================================================\n" << RESET;
    cout << "  [1] List Transaksi                              \n";
    cout << "  [2] Total Penjualan                             \n";
    cout << "  [3] Produk Terjual                              \n";
    cout << "  [0] Kembali ke Menu Kasir                       \n";
    cout << "--------------------------------------------------\n";
}

// =========================================
// --- kas.cpp ---
// =========================================
// #include "core.hpp"

void tampilkanMenuSistemKasUI();

const string FILE_KAS = "data_kas.txt"; 

void muatDataKas(Kas* dataKas) {
    ifstream file(FILE_KAS);
    if (file.is_open()) {
        file >> dataKas->saldo;
        file.close();
    } else {
        dataKas->saldo = 0;
    }
}

void simpanDataKas(const Kas* dataKas) {
    ofstream file(FILE_KAS);
    if (file.is_open()) {
        file << dataKas->saldo;
        file.close();
    }
}

void cekSaldoKas(const Kas* dataKas) {
    cout << CYAN << "\n==================================================\n";
    cout << "                  CEK SALDO KAS                   \n";
    cout << "==================================================\n" << RESET;
    cout << "Total Saldo Kas Saat Ini : " << GREEN << BOLD << "Rp " << dataKas->saldo << RESET << "\n";
    cout << CYAN << "--------------------------------------------------\n" << RESET;
}

void setorKas(Kas* dataKas) {
    long long nominal;
    cout << CYAN << "\n==================================================\n";
    cout << "                    SETOR KAS                     \n";
    cout << "==================================================\n" << RESET;
    cout << "Masukkan nominal setor (Rp): ";
    cin >> nominal;
    if (nominal > 0) {
        dataKas->saldo += nominal;
        simpanDataKas(dataKas);
        cout << GREEN << ">> Sukses! Berhasil menyetor Rp " << nominal << " ke dalam kas.\n" << RESET;
        cout << ">> Total saldo kas saat ini: " << GREEN << BOLD << "Rp " << dataKas->saldo << RESET << "\n";
    } else {
        cout << RED << ">> Gagal! Nominal tidak valid.\n" << RESET;
    }
}

void tarikKas(Kas* dataKas) {
    long long nominal;
    cout << CYAN << "\n==================================================\n";
    cout << "                    TARIK KAS                     \n";
    cout << "==================================================\n" << RESET;
    cout << "Masukkan nominal tarik (Rp): ";
    cin >> nominal;

    if (nominal > 0) {
        if (dataKas->saldo >= nominal) {
            dataKas->saldo -= nominal; 
            simpanDataKas(dataKas);
            cout << GREEN << ">> Sukses! Berhasil menarik Rp " << nominal << " dari kas.\n" << RESET;
            cout << ">> Total saldo kas saat ini: " << GREEN << BOLD << "Rp " << dataKas->saldo << RESET << "\n";
        } else {
            cout << RED << ">> Gagal! Saldo kas tidak mencukupi untuk penarikan ini.\n" << RESET;
        }
    } else {
        cout << RED << ">> Gagal! Nominal tidak valid.\n" << RESET;
    }
}

void tampilkanMenuKas(Kas* dataKas) {
    int pilihan;
    bool selesai = false;
    muatDataKas(dataKas);
    while (!selesai) {
        bersihkanLayar();
        tampilkanMenuSistemKasUI();
        pilihan = inputChoice(0, 3);
        switch (pilihan) {
            case 1:
                cekSaldoKas(dataKas);
                jedaLayar();
                break;
            case 2:
                setorKas(dataKas);
                jedaLayar();
                break;
            case 3:
                tarikKas(dataKas);
                jedaLayar();
                break;
            case 0:
                selesai = true;
                cout << "\n>> Menyimpan data dan kembali ke Menu Kasir...\n";
                jedaLayar();
                break;
            default:
                cout << "\n>> [ERROR] Pilihan tidak valid! Silakan masukkan angka 0-3.\n";
                jedaLayar();
        }
    }
}

void tampilkanMenuSistemKasUI() {
    cout << CYAN << "==================================================\n";
    cout << "               SISTEM MANAJEMEN KAS               \n";
    cout << "==================================================\n" << RESET;
    cout << "  [1] Cek Saldo Kas                               \n";
    cout << "  [2] Setor Kas                                   \n";
    cout << "  [3] Tarik Kas                                   \n";
    cout << "  [0] Kembali ke Menu Kasir                       \n";
    cout << "--------------------------------------------------\n";
}

// =========================================
// --- stocks.cpp ---
// =========================================
// #include "core.hpp"

void tampilkanMenuStokUI();
void headerDaftarStokUI();

void Stokmenu(Product products[], int productCount){
	bersihkanLayar();
	int opsi;
	while(true){
	    bersihkanLayar();
        tampilkanMenuStokUI();
        opsi = inputChoice(0, 3);
	
        switch (opsi){
            case 0:
                return;
            case 1:
                bersihkanLayar();
                tambahStok(products, productCount);
                break;
            case 2:
                bersihkanLayar();
                kurangStok(products, productCount);
                break;
            case 3:
                bersihkanLayar();
                lihatStok(products, productCount);
                jedaLayar();
                break;
        }
	}
}

void tambahStok(Product products[], int productCount){
    lihatStok(products, productCount);
    
	string code;
	int jumlah;
	cout << CYAN << "\n==========================================================\n";
	cout << "                       TAMBAH STOK                        \n";
	cout << "==========================================================\n" << RESET;
	cout << ">> Masukkan KODE Produk : ";
	cin >> code;
	
	Product* prdt = findProduct(products, productCount, code);
	
	if (prdt == nullptr){
		cout << RED << ">> Produk Tidak Ditemukan!\n" << RESET;
		jedaLayar();
		return;
	}else{
		cout << "Nama Produk   : " << prdt->name << endl;
		cout << "Stok Tersedia : " << prdt->stock << endl;
	}
	
	cout << "\n>> Masukkan jumlah yang ingin ditambahkan: ";
	cin >> jumlah;
	if (jumlah <= 0){
		cout << RED << ">> Gagal! Jumlah harus lebih dari 0\n" << RESET;
		jedaLayar();
		return;
	}else{
	    prdt->stock += jumlah;
	    cout << CYAN << "----------------------------------------------------------\n" << RESET;	
	    cout << GREEN << ">> Sukses! Stok Berhasil ditambahkan.\n" << RESET;
	    cout << ">> Total Stok Saat Ini: " << GREEN << BOLD << prdt->stock << RESET << "\n\n";
	    simpanDataProduk(products, productCount);
	}
	jedaLayar();
}

void kurangStok(Product products[], int productCount){
    lihatStok(products, productCount);
    
	string code;
	int jumlah;
	cout << CYAN << "\n==========================================================\n";
	cout << "                       KURANGI STOK                       \n";
	cout << "==========================================================\n" << RESET;
	cout << ">> Masukkan KODE Produk : ";
	cin >> code;
	
	Product* prdt = findProduct(products, productCount, code);
	
	if (prdt == nullptr){
		cout << RED << ">> Produk Tidak Ditemukan!\n" << RESET;
		jedaLayar();
		return;
	}else{
		cout << "Nama Produk   : " << prdt->name << endl;
		cout << "Stok Tersedia : " << prdt->stock << endl;
	}
	
	cout << "\n>> Masukkan jumlah yang ingin dikurangi: ";
	cin >> jumlah;
	
	if(jumlah <= 0){
        cout << RED << ">> Gagal! Jumlah harus lebih dari 0!\n" << RESET;
	} else if (jumlah > prdt->stock){
        cout << RED << ">> Gagal! Stok tidak mencukupi!\n" << RESET;
	} else{
        prdt->stock -= jumlah;
        cout << CYAN << "----------------------------------------------------------\n" << RESET;
        cout << GREEN << ">> Sukses! Stok berhasil dikurangi.\n" << RESET;
	    cout << ">> Total Stok Saat Ini: " << GREEN << BOLD << prdt->stock << RESET << "\n\n";
	    simpanDataProduk(products, productCount);
	}
	jedaLayar();
}

void lihatStok(Product products[], int productCount) {
    headerDaftarStokUI();

    for(int i = 0; i < productCount; i++) {
        cout << left << setw(10) << products[i].id 
             << setw(20) << products[i].name 
             << setw(15) << products[i].price 
             << products[i].stock << "\n";
    }
    
    cout << CYAN << "==========================================================\n" << RESET;
}

void tampilkanMenuStokUI() {
    cout << CYAN << "=========================================\n";
    cout << "          MENU MANAJEMEN STOK            \n";
    cout << "=========================================\n" << RESET;
    cout << "  [1] Tambah Stok\n";
    cout << "  [2] Kurangi Stok\n";
    cout << "  [3] Lihat Semua Stok\n";
    cout << "  [0] Kembali\n";
    cout << "-----------------------------------------\n";
}

void headerDaftarStokUI() {
    cout << CYAN << "==========================================================\n";
    cout << "                  DAFTAR PRODUK (STOK)                    \n";
    cout << "==========================================================\n" << RESET;
    cout << left << setw(10) << "KODE" << setw(20) << "NAMA" << setw(15) << "HARGA" << "STOK\n";
    cout << "----------------------------------------------------------\n";
}

// =========================================
// --- main.cpp ---
// =========================================
// #include "core.hpp"

void tampilkanMenuKasirUI(string nama);

int main() {
    int jumlahPengguna = 0;
    Akun dataPengguna[MAX_PENGGUNA];
    muatDataAkun(dataPengguna, jumlahPengguna);

    int productCount = 0;
    Product products[MAX_PRODUCT];
    muatDataProduk(products, productCount);

    int transactionCount = 0;
    Transaction transactions[MAX_TRANSACTION];
    muatDataTransaksi(transactions, transactionCount);

    Kas cash;
    muatDataKas(&cash);

    Akun userAktif;

    while (true) {
        string role = prosesLogin(userAktif, dataPengguna, jumlahPengguna);
        
        if (role == "Exit") {
            break;
        } 
        else if (role == "Admin") {
            menuAdmin(userAktif, products, productCount, dataPengguna, jumlahPengguna);
        } 
        else if (role == "Kasir") {
            string cashierId = userAktif.username;
            int pilihan;

            do {
                bersihkanLayar();
                tampilkanMenuKasirUI(userAktif.nama);
                pilihan = inputChoice(0, 3);

                switch (pilihan) {
                    case 1:
                        startTransaction(
                            products,
                            productCount,
                            transactions,
                            transactionCount,
                            &cash,
                            cashierId
                        );
                        simpanDataKas(&cash);
                        break;

                    case 2:
                        tampilkanMenuKas(&cash);
                        break;

                    case 3:
                        Stokmenu(products, productCount);
                        break;

                    case 0:
                        simpanDataKas(&cash);
                        cout << GREEN << "\n[+] Anda berhasil logout dari Kasir.\n" << RESET;
                        jedaLayar();
                        break;

                    default:
                        cout << RED << "\n[!] Pilihan tidak valid.\n" << RESET;
                        jedaLayar();
                }

            } while (pilihan != 0);
        } 
        else {
            cout << RED << "\n[!] Login gagal! Username atau password salah.\n" << RESET;
            jedaLayar();
        }
    }

    simpanDataKas(&cash);
    simpanDataAkun(dataPengguna, jumlahPengguna);
    simpanDataProduk(products, productCount);
    simpanDataTransaksi(transactions, transactionCount);
    cout << GREEN << "\n[+] Program selesai. Terima kasih!\n" << RESET;
    return 0;
}

void tampilkanMenuKasirUI(string nama) {
    cout << CYAN << "=========================================\n";
    cout << "               MENU KASIR                \n";
    cout << "=========================================\n" << RESET;
    cout << BOLD << "Halo, " << nama << "!\n\n" << RESET;
    cout << "  [1] Transaksi Baru\n";
    cout << "  [2] Manajemen Kas\n";
    cout << "  [3] Manajemen Stok\n";
    cout << "  [0] Logout\n";
    cout << "-----------------------------------------\n";
}

