#include "product.hpp"
#include "cart.hpp"
#include "utils.hpp"
#include "kas.hpp"

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
