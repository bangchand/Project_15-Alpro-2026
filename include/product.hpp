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
