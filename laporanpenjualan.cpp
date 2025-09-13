#ifndef LAPORANPENJUALAN_H
#define LAPORANPENJUALAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

class LaporanPenjualan {
public:
    const string file_laporan_csv = "./data/laporan_penjualan.csv";

    LaporanPenjualan() {
        ifstream file(file_laporan_csv);
    if (!file.good()) {
        ofstream create(file_laporan_csv);
        create << "Tanggal,Item,Total\n";
        create.close();
    }

    // === Tambahkan bagian ini: proses otomatis isi dari riwayat ===
    ifstream riwayat("./data/riwayat_total.txt");
    if (riwayat.is_open()) {
        string line, tanggal, item, total;
        ofstream append(file_laporan_csv, ios::app);

        while (getline(riwayat, line)) {
            stringstream ss(line);
            getline(ss, tanggal, ',');
            getline(ss, item, ',');
            getline(ss, total, ',');

            if (!tanggal.empty() && !item.empty() && !total.empty()) {
                append << tanggal << "," << item << "," << total << "\n";
            }
        }

        riwayat.close();
        append.close();
    }
}

    void tampilkanCSV() {
        tampilkanCSV(file_laporan_csv);
    }

    void tampilkanCSV(const string &filename) {
        system("cls");
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Gagal membuka file: " << filename << endl;
            return;
        }

        string line;
        cout << "+==========================================+\n";
        cout << "|           LAPORAN PENJUALAN CSV          |\n";
        cout << "+==========================================+\n";
        cout << "| Tanggal       | Item                     | Total     |\n";
        cout << "+---------------+--------------------------+-----------+\n";

        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string tanggal, item, total;

            getline(ss, tanggal, ',');
            getline(ss, item, ',');
            getline(ss, total, ',');

            printf("| %-13s | %-24s | Rp %-7s |\n", tanggal.c_str(), item.c_str(), total.c_str());
        }

        cout << "+==========================================+\n";

        file.close();
        cout << "\nTekan ENTER untuk kembali...";
        cin.get(); 
    }

    void hapusLaporan() {
        char konfirmasi;
        cout << "\n+====================================+\n";
        cout << "|       HAPUS LAPORAN PENJUALAN      |\n";
        cout << "+====================================+\n";
        cout << "Apakah Anda yakin ingin menghapus laporan? (y/n): ";
        cin >> konfirmasi;
        cin.ignore();

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            ofstream(file_laporan_csv).close();
            ofstream out(file_laporan_csv);
            out << "Tanggal,Item,Total\n";
            out.close();
            cout << "\nLaporan berhasil dihapus!\n";
        } else {
            cout << "\nPenghapusan dibatalkan.\n";
        }
        system("pause");
    }

    void tambahLaporan(const string &tanggal, const string &item, const string &total) {
        ofstream file(file_laporan_csv, ios::app);
        if (file.is_open()) {
            file << tanggal << "," << item << "," << total << "\n";
            file.close();
        } else {
            cout << "Gagal membuka file laporan untuk penulisan." << endl;
        }
    }
};

#endif