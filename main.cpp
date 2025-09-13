#include <iostream>
#include "component/menu.cpp"
#include "component/transaksi.cpp"
#include "component/laporanpenjualan.cpp"

using namespace std;

void manajemenMenu() {
    int menuChoice, updateChoice;
    string nama, jenis;
    float harga;

    daftarMenu dMenu;

    do {
        cout << "+===========================+\n";
        cout << "|       Manajemen Menu      |\n";
        cout << "+===========================+\n";
        cout << "1. Tambah menu makanan\n";
        cout << "2. Tambah menu minuman\n";
        cout << "3. Tampilkan semua menu\n";
        cout << "4. Update menu\n";
        cout << "5. Menghapus menu\n";
        cout << "6. Keluar\n";
        cout << "Silahkan pilih menu [1-6] : ";
        cin >> menuChoice;
        cin.ignore();

        switch(menuChoice) {
            case 1:
                system("cls");
                cout << "+=============================+\n";
                cout << "|      Tambah Menu Makanan    |\n";
                cout << "+=============================+\n\n";
                cout << "Masukkan nama makanan \t: ";
                getline(cin, nama);
                cout << "Masukkan harga makanan \t: ";
                cin >> harga;
                jenis = "Makanan";
                dMenu.tambahMenuMakanan(nama, harga, jenis);
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                cout << "+=============================+\n";
                cout << "|      Tambah Menu Minuman    |\n";
                cout << "+=============================+\n\n";
                cout << "Masukkan nama minuman \t: ";
                getline(cin, nama);
                cout << "Masukkan harga minuman \t: ";
                cin >> harga;
                jenis = "Minuman";
                dMenu.tambahMenuMinuman(nama, harga, jenis);
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                dMenu.printDaftarMenu();
                system("pause");
                system("cls");
                break;
            case 4:
                system("cls");
                cout << "+====================+\n";
                cout << "|     Menu Update    |\n";
                cout << "+====================+\n\n";
                cout << "1. Update menu makanan\n";
                cout << "2. Update menu minuman\n";
                cout << "Pilih menu : "; cin >> updateChoice;
                cin.ignore();
                if(updateChoice == 1) {
                    cout << "\nMasukkan nama makanan : "; 
                    getline(cin, nama);
                    dMenu.updateMenuMakanan(nama);
                } else if(updateChoice == 2) {
                    cout << "\nMasukkan nama minuman : "; 
                    getline(cin, nama);
                    dMenu.updateMenuMinuman(nama);
                } else {
                    cout << "Pilihan tidak ada.\n";
                }
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                cout << "+====================+\n";
                cout << "|     Menu Delete    |\n";
                cout << "+====================+\n\n";
                cout << "Masukkan nama menu yang ingin dihapus : ";
                getline(cin, nama);
                dMenu.deleteMenu(nama);
                system("pause");
                system("cls");
                break;
            case 6:
                system("cls");
                cout << "Kembali ke menu utama\n";
                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                cout << "Pilihan anda salah (tidak terdapat dalam daftar)\n";
                system("pause");
                system("cls");
                break;
        }
    } while(menuChoice != 6);
}

void pemesananMenu() {
    int buyOption;

    Transaksi transaksi;

    do {
        cout << "+===========================+\n";
        cout << "|       Pemesanan Menu      |\n";
        cout << "+===========================+\n";
        cout << "1. Transaksi penjualan\n";
        cout << "2. Riwayat transaksi\n";
        cout << "3. Keluar\n";
        cout << "Silahkan pilih menu [1-3] : ";
        cin >> buyOption;
        cin.ignore();

        switch (buyOption) {
            case 1:
                system("cls");
                transaksi.transaksiPenjualan();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                transaksi.riwayatTransaksi();
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                cout << "Kembali ke menu utama\n";
                system("pause");
                system("cls");
                break;
            default:
                break;
        }
    } while(buyOption != 3);
}

void tampilkanMenuLaporan() {
        int pilihan;

        LaporanPenjualan laporanpenjualan;

        do {
            system("cls");
            cout << "+======================================+\n";
            cout << "|           MENU LAPORAN               |\n";
            cout << "+======================================+\n";
            cout << "1. Tampilkan Laporan Penjualan (CSV)\n";
            cout << "2. Hapus Laporan\n";
            cout << "3. Kembali\n";
            cout << "Pilihan Anda: ";
            cin >> pilihan;
            cin.ignore();

            switch (pilihan) {
                case 1:
                    system("cls");
                    laporanpenjualan.tampilkanCSV();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    laporanpenjualan.hapusLaporan();
                    break;
                case 3:
                    cout << "Kembali ke menu utama...\n";
                    break;
                default:
                    system("cls");
                    cout << "Pilihan tidak valid.\n";
                    system("pause");
                    break;
            }
        } while (pilihan != 3);
    }

int main() {
    int mainChoice;

    do {
        cout << "+==================================+\n";
        cout << "|          SISTEM RESTORAN         |\n";
        cout << "+==================================+\n";
        cout << "1. Manajemen Menu\n";
        cout << "2. Pemesanan Menu\n";
        cout << "3. Laporan Penjualan\n";
        cout << "4. Keluar\n";
        cout << "Silahkan pilih menu [1-4] : "; 
        cin >> mainChoice;
        cin.ignore();

        switch(mainChoice) {
            case 1:
                system("cls");
                manajemenMenu();
                break;
            case 2:
                system("cls");
                pemesananMenu();
                break;
            case 3:
                system("cls");
                tampilkanMenuLaporan();
                break;
            case 4:
                system("cls");
                cout << "Terima kasih telah menggunakan aplikasi kami.\n";
                break;
            default:
                system("cls");
                cout << "Pilihan anda salah (tidak terdapat dalam daftar)\n";
                system("pause");
                system("cls");
                break;
        }

    } while(mainChoice != 4);

    return 0;
}