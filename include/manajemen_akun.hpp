#pragma once
#include <string>
#include "product.hpp"
#include "transaction.hpp"

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
void menuAdmin(Akun adminAktif, Product products[], int& productCount, Akun dataPengguna[], int& jumlahPengguna, Transaction transactions[], int transactionCount);
void menuManajemenAkun(Akun dataPengguna[], int &jumlahPengguna);
