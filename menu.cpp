#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Menu {
    string nama_menu;
    float harga_menu;
    string jenis_menu;
    Menu *next;
};

class daftarMenu {
    private:
        Menu *head = NULL;
        const string file_menu = "./data/menu.txt";

        bool isMenuExist(string nama) {
            Menu *current = head;
            while(current != NULL) {
                if(current->nama_menu == nama) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        void clearNode() {
            while(head != NULL) {
                Menu *temp = head;
                head = head->next;
                delete temp;
            }
        }

        void sortMenuAscByNama() {
            if(head == NULL || head->next == NULL) {
                return;
            }

            bool swapped;
            Menu *ptr;
            Menu *lptr = NULL;

            do {
                swapped = false;
                ptr = head;

                while(ptr->next !=lptr) {
                    if(ptr->nama_menu > ptr->next->nama_menu) {
                        swap(ptr->nama_menu, ptr->next->nama_menu);
                        swap(ptr->harga_menu, ptr->next->harga_menu);
                        swap(ptr->jenis_menu, ptr->next->jenis_menu);
                        swapped = true;
                    }
                    ptr = ptr->next;
                }
                lptr = ptr;
            } while(swapped);
        }

        void insertMenuFileToNode(string nama, float harga, string jenis) {
            // deklarasi data menu
            Menu *newMenu = new Menu{nama, harga, jenis, NULL};

            if(head == NULL) {
                head = newMenu;
            } else {
                Menu *temp = head;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newMenu;
            }
        }

        void loadMenuFromFile(string filename) {
            // Menghapus isi node sebelum load data
            clearNode();

            ifstream file(filename);
            if(!file.is_open()) {
                cout << "Gagal membuka file!\n";
                return;
            }

            string nama, jenis, hargaStr, line;
            float harga;

            while(getline(file, line)) {
                if(line.empty()) continue;

                stringstream ss(line);
                getline(ss, nama, ',');
                getline(ss, hargaStr, ',');
                getline(ss, jenis, ',');

                // Validasi data
                try {
                    harga = stof(hargaStr);
                } catch (const invalid_argument &e) {
                    cout << "Data tidak valid! \n";
                    continue;
                }

                // insert data file to node
                insertMenuFileToNode(nama, harga, jenis);
            }
            file.close();
        }

        void saveToFile(string filename) {
            ofstream file(filename);
            if(!file.is_open()) {
                cout << "Gagal membuka file!\n";
                return;
            }

            Menu *current = head;
            while(current != NULL) {
                file << current->nama_menu << ","
                     << current->harga_menu << ","
                     << current->jenis_menu << "\n";
                current = current->next;
            }

            file.close();
        }
    public:
        void tambahMenuMakanan(string nama, float harga, string jenis) {
            // load data dari file
            loadMenuFromFile(file_menu);

            // Cek menu apakah sudah ada
            if(isMenuExist(nama)) {
                cout << "\nenu dengan nama \"" << nama << "\" sudah ada. Gagal ditambahkan!\n";
                return;
            }

            // declare newMenu
            Menu *newMenu = new Menu;
            newMenu->nama_menu = nama;
            newMenu->harga_menu = harga;
            newMenu->jenis_menu = jenis;
            newMenu->next = NULL;
            
            if(head == NULL) {
                head = newMenu;
            } else {
                Menu *temp = head;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newMenu;
            }

            saveToFile(file_menu);
            cout << "\nMenu makanan berhasil ditambahkan. \n\n";
        }

        void tambahMenuMinuman(string nama, float harga, string jenis) {
            // load data dari file
            loadMenuFromFile(file_menu);

            // Cek menu apakah sudah ada
            if(isMenuExist(nama)) {
                cout << "\nMenu dengan nama \"" << nama << "\" sudah ada. Gagal ditambahkan!\n";
                return;
            }

            // declare newMenu
            Menu *newMenu = new Menu;
            newMenu->nama_menu = nama;
            newMenu->harga_menu = harga;
            newMenu->jenis_menu = jenis;
            newMenu->next = NULL;
            
            if(head == NULL) {
                head = newMenu;
            } else {
                Menu *temp = head;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newMenu;
            }

            saveToFile(file_menu);
            cout << "\nMenu minuman berhasil ditambahkan. \n\n";
        }

        void printDaftarMenu() {
            // load data dari file
            loadMenuFromFile(file_menu);
            // Mengurutkan menu dari a-z
            sortMenuAscByNama();

            if(head == NULL) {
                cout << "Data Menu Kosong !!! \n\n";
                return;
            }

            // dekclare new variable to initialize first data menu
            Menu *current = head;
            int i = 1;
            bool adaMakanan = false;

            cout << "+=====================+\n";
            cout << "|     DAFTAR MENU     |\n";
            cout << "+=====================+\n";
            // Menu makanan
            cout << "Daftar Makanan : \n";
            while(current != NULL) {
                if(current->jenis_menu == "Makanan") {
                    cout << i++ << ". " << current->nama_menu
                    << "\tRp." << current->harga_menu << endl;
                    adaMakanan = true;
                }
                current = current->next;
            }
            if(!adaMakanan) {
                cout << "Tidak ada menu makanan.\n";
            }

            // Menu minuman
            cout << "\nDaftar Minuman : \n";
            current = head;
            i = 1;
            bool adaMinuman = false;

            while(current != NULL) {
                if(current->jenis_menu == "Minuman") {
                    cout << i++ << ". " << current->nama_menu
                    << "\tRp." << current->harga_menu << endl;
                    adaMinuman = true;
                }
                current = current->next;
            }
            if(!adaMinuman) {
                cout << "Tidak ada menu minuman.\n";
            }
            cout << endl;
        }

        void updateMenuMakanan(string target) {
            // load data dari file
            loadMenuFromFile(file_menu);

            Menu *temp = head;
            string nama, stok, harga, jenis;

            while(temp != NULL) {
                if(temp->nama_menu == target && temp->jenis_menu == "Makanan") {
                    cout << "\nData makanan ditemukan\n";
                    cout << "Nama menu \t: " << temp->nama_menu << endl;
                    cout << "Harga menu \t: Rp. " << temp->harga_menu << endl;
                    cout << "Jenis menu \t: " << temp->jenis_menu << endl;
                    
                    cin.ignore();
                    cout << "Masukkan data menu baru (beri - jika tidak ingin mengubah data)\n";
                    cout << "Nama menu baru  : "; getline(cin, nama); // Nama menu baru
                    if(nama != "-") {
                        temp->nama_menu = nama;
                    }
                    cout << "Harga menu baru : "; cin >> harga; // Harga menu baru
                    if(harga != "-") {
                        try {
                            temp->harga_menu = stof(harga);
                        } catch(...) {
                            cout << "Harga tidak valid!\n";
                        }
                    }
                    cout << "Jenis menu baru [Makanan/Minuman] : "; cin >> jenis; // Jenis menu baru
                    if(jenis != "-") {
                        temp->jenis_menu = jenis;
                    }
                    
                    saveToFile(file_menu);
                    cout << "\nMenu berhasil diupdate.\n";
                    return;
                } else if(temp->nama_menu == target && temp->jenis_menu != "Makanan") {
                    cout << "\nMenu dengan nama \"" << target << "\" ditemukan, akan tetapi bukan merupakan makanan.\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "\nMenu dengan nama \"" << target << "\" tidak ditemukan.\n";
        }

        void updateMenuMinuman(string target) {
            // load data dari file
            loadMenuFromFile(file_menu);

            Menu *temp = head;
            string nama, stok, harga, jenis;

            while(temp != NULL) {
                if(temp->nama_menu == target && temp->jenis_menu == "Minuman") {
                    cout << "\nData minuman ditemukan\n";
                    cout << "Nama menu \t: " << temp->nama_menu << endl;
                    cout << "Harga menu \t: Rp. " << temp->harga_menu << endl;
                    cout << "Jenis menu \t: " << temp->jenis_menu << endl;
                    
                    cin.ignore();
                    cout << "Masukkan data menu baru (beri - jika tidak ingin mengubah data)\n";
                    cout << "Nama menu baru  : "; getline(cin, nama); // Nama menu baru
                    if(nama != "-") {
                        temp->nama_menu = nama;
                    }
                    cout << "Harga menu baru : "; cin >> harga; // Harga menu baru
                    if(harga != "-") {
                        try {
                            temp->harga_menu = stof(harga);
                        } catch(...) {
                            cout << "Harga tidak valid!\n";
                        }
                    }
                    cout << "Jenis menu baru [Makanan/Minuman] : "; cin >> jenis; // Jenis menu baru
                    if(jenis != "-") {
                        temp->jenis_menu = jenis;
                    }
                    
                    saveToFile(file_menu);
                    cout << "\nMenu berhasil diupdate.\n";
                    return;
                } else if(temp->nama_menu == target && temp->jenis_menu != "Minuman") {
                    cout << "\nMenu dengan nama \"" << target << "\" ditemukan, akan tetapi bukan merupakan minuman.\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "\nMenu dengan nama \"" << target << "\" tidak ditemukan.\n";
        }

        void deleteMenu(string target) {
            // load data dari file
            loadMenuFromFile(file_menu);

            if(head == NULL) {
                cout << "Data menu kosong!!!\n";
                return;
            }

            Menu *current = head;
            Menu *prev = NULL;

            // Hapus data jika node pertama adalah yang dicari
            if(current != NULL && current->nama_menu == target) {
                head = current->next;
                delete current;
                saveToFile(file_menu);
                cout << "\nMenu dengan nama \"" << target << "\" berhasil dihapus.\n";
                return;
            }

            // Mencari node dengan nama target
            while(current != NULL && current->nama_menu != target) {
                prev = current;
                current = current->next;
            }

            // Menampilkan pesan apabila target tidak ditemukan.
            if(current == NULL) {
                cout << "\nMenu dengan nama \"" << target << "\" tidak ditemukan.\n";
                return;
            }

            // Menghapus node
            prev->next = current->next;
            delete current;
            saveToFile(file_menu);
            cout << "\nMenu dengan nama \"" << target << "\" berhasil dihapus.\n";
        }

        // Fungsi untuk mendapatkan harga menu
        float getHargaMenu(string nama) {
            Menu *current = head;
            while(current != NULL) {
                if(current->nama_menu == nama) {
                    return current->harga_menu;
                }
                current = current->next;
            }
            return 0;
        }

        // Fungsi untuk mendapatkan jenis menu
        string getJenisMenu(string nama) {
            Menu *current = head;
            while(current != NULL) {
                if(current->nama_menu == nama) {
                    return current->jenis_menu;
                }
                current = current->next;
            }
            return "";
        }
};
#endif