#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "menu.cpp"

using namespace std;

#define max_data 100

struct Transact {
    string nama_menu;
    float jumlah_menu;
    float harga_menu;
    string jenis_menu;
    float total_menu;
};

struct RincianTotal {
    string tanggal;
    float total;
    float bayar;
    float sisa;
};

struct Queue {
    int head;
    int tail;
    Transact transaksi[max_data];
};

struct StackData {
    int top = -1;
    Transact Rdata[max_data];
};

struct StackTotal {
    int top = -1;
    RincianTotal Rtotal[max_data];
};

class Transaksi {
    private:
        daftarMenu Dmenu;
        const string file_riwayat_data = "./data/riwayat_data.txt";
        const string file_riwayat_total = "./data/riwayat_total.txt";

        // Inisialisasi queue
        void init(Queue &que) {
            que.head = 0;
            que.tail = 0;
        }

        // Inisialisasi stack riwayat data
        void initStackData(StackData &sData) {
            sData.top = -1;
        }

        // Inisialisasi stack riwayat total
        void initStackTotal(StackTotal &sTotal) {
            sTotal.top = -1;
        }

        // Cek que kosong
        bool isEmpty(Queue &que) {
            if(que.head == que.tail) {
                return true;
            } else {
                return false;
            }
        }

        // Cek stack data kosong
        bool isDataEmpty(StackData &sData) {
            if(sData.top == -1) {
                return true;
            } else {
                return false;
            }
        }

        // Cek stack total kosong
        bool isTotalEmpty(StackTotal &sTotal) {
            if(sTotal.top == -1) {
                return true;
            } else { 
                return false;

            }
        }

        // Cek que penuh
        bool isFull(Queue &que) {
            if(que.tail == max_data) {
                return true;
            } else {
                return false;
            }
        }

        // Cek stack data kosong
        bool isDataFull(StackData &sData) {
            if(sData.top == max_data - 1) {
                return true;
            } else {
                return false;
            }
        }

        // Cek stack total kosong
        bool isTotalFull(StackTotal &sTotal) {
            if(sTotal.top == max_data - 1) {
                return true;
            } else {
                return false;
            }
        }

        // Get date and time automatic
        string getDateTime() {
            string date;
            time_t now = time(0);
            tm *ltm = localtime(&now);

            char buffer[20];
            strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", ltm);    
            date = buffer;

            return date;
        }

        // Insert data to stack data
        void insertTransaksiData(StackData &sData, string nama, float jumlah, float harga, string jenis, float total) {
            Transact newData;
            newData.nama_menu = nama;
            newData.jumlah_menu = jumlah;
            newData.harga_menu = harga;
            newData.jenis_menu = jenis;
            newData.total_menu = total;

            if(sData.top < max_data - 1) {
                sData.Rdata[++sData.top] = newData;
            } else {
                cout << "Data tidak berhasil ditambahkan.\n";
            }
        }

        // Insert data total to stack total
        void insertTransaksiTotal(StackTotal &sTotal, string tanggal, float total, float bayar, float sisa) {
            RincianTotal newData;
            newData.tanggal = tanggal;
            newData.total = total;
            newData.bayar = bayar;
            newData.sisa = sisa;

            if(sTotal.top < max_data - 1) {
                sTotal.Rtotal[++sTotal.top] = newData;
            } else {
                cout << "Data tidak berhasil ditambahkan.\n";
            }
        }

        // Load data from riwayat_data.txt
        void loadTransaksiData(StackData &sData) {
            initStackData(sData);

            ifstream file(file_riwayat_data);
            if(!file.is_open()) {
                cout << "Gagal membuka file!\n";
                return;
            }

            string nama, jumlahStr, hargaStr, jenis, totalStr, line;
            float jumlah, harga, total;

            while(getline(file, line)) {
                if(line.empty()) continue;

                stringstream ss(line);
                getline(ss, nama, ',');
                getline(ss, jumlahStr, ',');
                getline(ss, hargaStr, ',');
                getline(ss, jenis, ',');
                getline(ss, totalStr, ',');

                // Validasi data
                try {
                    jumlah = stof(jumlahStr);
                    harga = stof(hargaStr);
                    total = stof(totalStr);
                } catch(...) {
                    cout << "Data tidak valid! \n";
                    continue;
                }

                // Insert data to stack data
                insertTransaksiData(sData, nama, jumlah, harga, jenis, total);
            }
            file.close();
        }
        // Load data from riwayat_total.txt
        void loadTransaksiTotal(StackTotal &sTotal) {
            initStackTotal(sTotal);

            ifstream file(file_riwayat_total);
            if(!file.is_open()) {
                cout << "Gagal membuka file!\n";
                return;
            }

            string date, totalStr, bayarStr, kembalianStr, line;
            float total, bayar, kembalian;

            while(getline(file, line)) {
                if(line.empty()) continue;

                stringstream ss(line);
                getline(ss, date, ',');
                getline(ss, totalStr, ',');
                getline(ss, bayarStr, ',');
                getline(ss, kembalianStr, ',');

                // Validasi data
                try {
                    total = stof(totalStr);
                    bayar = stof(bayarStr);
                    kembalian = stof(kembalianStr);
                } catch(...) {
                    cout << "Data tidak valid! \n";
                    continue;
                }

                // Insert data to stack data
                insertTransaksiTotal(sTotal, date, total, bayar, kembalian);
            }
            file.close();
        }

        // Input data transaksi per barang
        void inputDataQue(Queue &que, Transact &data) {
            if(isFull(que) == true) {
                cout << "Maaf, pesanan sudah melebihi batas.\n";
                return;
            } else {
                que.transaksi[que.tail] = data;
                que.tail++;
            }
        }

        // Print data transaksi berdasarkan jenis menu pesanan
        void printDataQue(Queue &q) {
            if(isEmpty(q) == true) {
                cout << "Data kosong.\n";
            } else {
                bool adaMakanan = false;
                cout << "Makanan : \n";
                for(int i=q.head; i<q.tail; i++) {
                    if(q.transaksi[i].jenis_menu == "Makanan") {
                        cout << "- " << q.transaksi[i].nama_menu
                        << "\t" << q.transaksi[i].jumlah_menu << "\t"
                        << q.transaksi[i].harga_menu << "\t" 
                        << q.transaksi[i].total_menu << endl;
                        adaMakanan = true;
                    }
                }

                // Tampilan jika tidak ada makanan yang dipesan
                if(!adaMakanan) {
                    cout << "Tidak ada menu makanan yang dipesan.\n";
                }

                bool adaMinuman = false;
                int i=0;
                cout << "Minuman : \n";
                for(i=q.head; i<q.tail; i++) {
                    if(q.transaksi[i].jenis_menu == "Minuman") {
                        cout << "- " << q.transaksi[i].nama_menu
                        << "\t" << q.transaksi[i].jumlah_menu << "\t"
                        << q.transaksi[i].harga_menu << "\t" 
                        << q.transaksi[i].total_menu << endl;
                        adaMinuman = true;
                    }
                }

                // Tampilan jika tidak ada minuman yang dipesan
                if(!adaMinuman) {
                    cout << "Tidak ada menu minuman yang dipesan.\n";
                }
            }
        }

        // Print data riwayat transaksi berdasarkan total belanja
        void printDataRiwayat() {
            StackData sData;
            StackTotal sTotal;

            // Load data
            loadTransaksiData(sData);
            loadTransaksiTotal(sTotal);

            if (isDataEmpty(sData) && isTotalEmpty(sTotal)) {
                cout << "Data transaksi kosong.\n";
            } else {
                int index = sData.top;

                for (int i = sTotal.top; i >= 0; i--) {
                    float akumulasi = 0;
                    int batasAwal = index;

                    // Langkah 1: Telusuri mundur dan kumpulkan data sampai total per nota tercapai
                    while (index >= 0 && akumulasi < sTotal.Rtotal[i].total) {
                        akumulasi += sData.Rdata[index].total_menu;
                        index--;
                    }

                    int batasAkhir = index + 1; // Posisi pertama item dalam nota ini

                    // Langkah 2: Cetak informasi nota
                    cout << "\n+===================================+\n";
                    cout << "              Nota ke-" << (i + 1) << endl;
                    cout << "+===================================+\n";
                    cout << "Tanggal : " << sTotal.Rtotal[i].tanggal << endl;

                    // Langkah 3: Tampilkan makanan
                    bool adaMakanan = false;
                    cout << "Makanan :\n";
                    for (int j = batasAwal; j >= batasAkhir; j--) {
                        if (sData.Rdata[j].jenis_menu == "Makanan") {
                            cout << "- " << sData.Rdata[j].nama_menu
                                << "\t" << sData.Rdata[j].jumlah_menu
                                << "\t" << sData.Rdata[j].harga_menu
                                << "\t" << sData.Rdata[j].total_menu << endl;
                            adaMakanan = true;
                        }
                    }

                    // Tampilan jika tidak ada makanan yang dipesan
                    if(!adaMakanan) {
                        cout << "Tidak ada menu makanan yang dipesan.\n";
                    }

                    // Langkah 4: Tampilkan minuman
                    bool adaMinuman = false;
                    cout << "Minuman :\n";
                    for (int j = batasAwal; j >= batasAkhir; j--) {
                        if (sData.Rdata[j].jenis_menu == "Minuman") {
                            cout << "- " << sData.Rdata[j].nama_menu
                                << "\t" << sData.Rdata[j].jumlah_menu
                                << "\t" << sData.Rdata[j].harga_menu
                                << "\t" << sData.Rdata[j].total_menu << endl;
                                adaMinuman = true;
                        }
                    }

                    // Tampilan jika tidak ada minuman yang dipesan
                    if(!adaMinuman) {
                        cout << "Tidak ada menu minuman yang dipesan.\n";
                    }
                    
                    cout << "\n-------------------------------------\n";
                    // Langkah 5: Total dan kembalian
                    cout << "\nTotal Harga : Rp. " << sTotal.Rtotal[i].total << endl;
                    cout << "Pembayaran  : Rp. " << sTotal.Rtotal[i].bayar << endl;
                    cout << "Kembalian   : Rp. " << sTotal.Rtotal[i].sisa << endl;
                    cout << "\n-------------------------------------\n\n";
                }
            }
        }


        // Save data rincian pembelian per menu ke file riwayat_data.txt
        void saveToFileData(Queue &q) {
            ofstream file(file_riwayat_data, ios::app);
            if(!file.is_open()) {
                cout << "Gagal membuka file!\n";
                return;
            }
            for(int i=q.head; i<q.tail;i++) {
                file << q.transaksi[i].nama_menu << "," << q.transaksi[i].jumlah_menu 
                     << "," << q.transaksi[i].harga_menu << "," << q.transaksi[i].jenis_menu
                     << "," << q.transaksi[i].total_menu << endl;
            }
            file.close();
        }

        // Save totalHarga dan tanggal pembelian ke file riwayat_total.txt
        void saveToFileTotal(string date, float totalHarga, float pembayaran, float sisa) {
            ofstream file(file_riwayat_total, ios::app);
            if(!file.is_open()) {
                cout << "Gagal membuka file!\n";
                return;
            }

            file << date << "," << totalHarga << "," 
                 << pembayaran << "," << sisa << endl;
            file.close();
        }
    public:
        void transaksiPenjualan() {
            char ulang;
            string tanggal;
            float bayar, sisa, totalHarga = 0;

            Queue q;
            Transact t;

            init(q);

            do {
                system("cls");
                Dmenu.printDaftarMenu();
                cout << "Masukkan nama menu   : "; getline(cin, t.nama_menu);
                cout << "Masukkan jumlah menu : "; cin >> t.jumlah_menu;
                t.harga_menu = Dmenu.getHargaMenu(t.nama_menu);
                t.jenis_menu = Dmenu.getJenisMenu(t.nama_menu);
                t.total_menu = (t.jumlah_menu * t.harga_menu);
                totalHarga += t.total_menu;
                inputDataQue(q, t);
                cout << "Apakah anda masih ingin memesan ? (y/n) : ";
                cin >> ulang;
                cin.ignore();
            } while(ulang == 'y');

            tanggal = getDateTime();

            system("cls");
            do {
                cout << "+=======================================+\n";
                cout << "|             MENU BELANJA              |\n";
                cout << "+=======================================+\n";
                cout << "Tanggal : " << tanggal << endl;
                printDataQue(q);
                cout << endl;
                cout << "Total Harga Belanja : Rp. " << totalHarga << endl;
                cout << "Masukkan pembayaran : Rp. "; cin >> bayar;
                if(bayar > totalHarga) {
                    sisa = bayar - totalHarga;
                    cout << "Sisa kembalian      : Rp. " << sisa << endl;
                } else {
                    cout << "Nominal pembayaran kurang.\n\n";
                    system("cls");
                }
            } while(bayar < totalHarga);

            // saveData to file
            saveToFileData(q);
            saveToFileTotal(tanggal, totalHarga, bayar, sisa);
            cout << endl;
            system("pause");

            system("cls");
            cout << "+=======================================+\n";
            cout << "|             NOTA BELANJA              |\n";
            cout << "+=======================================+\n";
            cout << "Tanggal : " << tanggal << endl;
            printDataQue(q);
            cout << endl;
            cout << "Total Harga : Rp. " << totalHarga << endl;
            cout << "Pembayaran  : Rp. " << bayar << endl;
            cout << "Kembalian   : Rp. " << sisa << endl << endl;
        }

        void riwayatTransaksi(){
            cout << "+===================================+\n";
            cout << "|         RIWAYAT TRANSAKSI         |\n";
            cout << "+===================================+\n";
            printDataRiwayat();
        }

};