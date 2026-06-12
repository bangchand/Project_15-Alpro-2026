#include <iostream>
#include <string>

using namespace std;

enum Role {
    ADMIN,
    KASIR
};

enum TransactionType {
    SETOR,
    TARIK,
    PENJUALAN
}; 

struct User {
    string id;
    string username;
    string password;
    Role role;
};

struct Product {
    string id;
    string name;
    double price;
    int stock;
};

struct CartItem {
    string productId;
    string productName;
    double price;
    int quantity;
    double subtotal;
};

// need pivot model
struct Transaction {
    string id;
    string cashierId;
    string date;
    double total;
    double payment;
    double change;
};

struct Cash {
    double balance;
};

struct CashHistory {
    string id;
    TransactionType type;
    double amount;
    string description;
    string date;
};