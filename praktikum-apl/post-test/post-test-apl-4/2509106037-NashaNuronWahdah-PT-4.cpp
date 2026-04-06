#include <iostream>
#include <string>
using namespace std;

struct Pengguna {
    string username;
    string password;
    string role; 
};

struct SlotMakam {
    int id;
    int harga;
    bool terisi;
    string namaJenazah;
    string namaOrtu;
    string tanggalWafat;
};

struct Wilayah {
    string nama;     
    int baris;
    int kolom;
    int totalSlot;    
    int hargaPerMakam;
    SlotMakam slot[100];
};

#define MAX_PENGGUNA 50
#define MAX_WILAYAH 50

Pengguna pengguna[MAX_PENGGUNA];
int jumlahPengguna = 0;

// AKUN ADMIN
Pengguna admin = {"Nuron", "037", "admin"};

Wilayah wilayah[MAX_WILAYAH];
int jumlahWilayah = 0;

void tambahJumlahPengguna(int &jumlah) {
    jumlah++;
    cout << "Jumlah pengguna bertambah, sekarang: " << jumlah << endl;
}

void tandaiSlotDenganPointer(SlotMakam *slot, string namaJenazah, string namaOrtu, string tanggalWafat) {
    if (slot->terisi) {
        cout << "Slot sudah terisi sebelumnya.\n";
    } else {
        slot->terisi = true;
        slot->namaJenazah = namaJenazah;
        slot->namaOrtu = namaOrtu;
        slot->tanggalWafat = tanggalWafat;
        cout << "Slot berhasil ditandai terisi dengan pointer.\n";
    }
}

bool masuk(const string &namaPenggunaInput, const string &kataSandiInput, string &peran) {
    if (namaPenggunaInput == admin.username && kataSandiInput == admin.password) {
        peran = admin.role;
        return true;
    }
    for (int i = 0; i < jumlahPengguna; i++) {
        if (pengguna[i].username == namaPenggunaInput && pengguna[i].password == kataSandiInput) {
            peran = pengguna[i].role;
            return true;
        }
    }
    return false;
}

void daftarPengguna() {
    if (jumlahPengguna < MAX_PENGGUNA) {
        cout << "Masukkan username: ";
        cin >> pengguna[jumlahPengguna].username;
        cout << "Masukkan password: ";
        cin >> pengguna[jumlahPengguna].password;
        pengguna[jumlahPengguna].role = "user";
        jumlahPengguna++;
        cout << "Registrasi berhasil! Akun role: user\n";

        tambahJumlahPengguna(jumlahPengguna);

    } else {
        cout << "Kapasitas user penuh!\n";
    }
}

string masukPengguna() {
    string namaPenggunaInput, kataSandiInput, peran;
    int percobaan = 0;
    while (percobaan < 3) {
        cout << "Masukkan username: ";
        cin >> namaPenggunaInput;
        cout << "Masukkan password: ";
        cin >> kataSandiInput;
        if (masuk(namaPenggunaInput, kataSandiInput, peran)) {
            cout << "Login berhasil! Selamat datang, " << namaPenggunaInput << " (role: " << peran << ").\n";
            return peran;
        } else {
            percobaan++;
            cout << "Login gagal! Kesempatan tersisa: " << (3 - percobaan) << endl;
        }
    }
    cout << "Anda sudah 3 kali salah login. Program berhenti.\n";
    return "";
}

string duaDigit(int x) {
    if (x < 10) return "0" + to_string(x);
    return to_string(x);
}

void tambahWilayah() {
    if (jumlahWilayah >= MAX_WILAYAH) {
        cout << "Kapasitas wilayah penuh!\n";
        return;
    }

    Wilayah w;
    cout << "Nama wilayah (tanpa spasi, hanya huruf): ";
    cin >> w.nama; 

    bool namaOk = true;
    for (int i = 0; i < (int)w.nama.length(); i++) {
        char c = w.nama[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            namaOk = false;
            break;
        }
    }
    if (!namaOk) {
        cout << "Nama wilayah hanya boleh huruf (tanpa spasi). Contoh: LoaJanan\n";
        return;
    }

    cout << "Masukkan jumlah baris (angka, >0). Contoh: 4\n";
    cout << "Catatan: baris * kolom maksimal 100.\n";
    cin >> w.baris;

    cout << "Masukkan jumlah kolom (angka, >0). Contoh: 5\n";
    cin >> w.kolom;

    if (w.baris <= 0 || w.kolom <= 0) {
        cout << "Baris dan kolom harus berupa angka lebih dari 0.\n";
        return;
    }
    int kapasitas = w.baris * w.kolom;
    if (kapasitas > 100) {
        cout << "Kapasitas baris*kolom maksimal 100. Kurangi baris atau kolom.\n";
        return;
    }
    w.totalSlot = kapasitas;

    cout << "Harga per makam (masukkan angka bulat, mis. 500000): ";
    cin >> w.hargaPerMakam;
    if (w.hargaPerMakam <= 0) {
        cout << "Harga harus berupa angka bulat lebih dari 0.\n";
        return;
    }

    for (int i = 0; i < w.totalSlot; i++) {
        w.slot[i].id = i + 1;
        w.slot[i].harga = w.hargaPerMakam;
        w.slot[i].terisi = false;
        w.slot[i].namaJenazah = "";
        w.slot[i].namaOrtu = "";
        w.slot[i].tanggalWafat = "";
    }

    wilayah[jumlahWilayah] = w;
    jumlahWilayah++;
    cout << "Wilayah berhasil ditambahkan! Total slot = " << w.totalSlot << "\n";
}

void tampilkanDenahWilayah(int indeks) {
    Wilayah &w = wilayah[indeks];
    int baris = w.baris;
    int kolom = w.kolom;

    int peta[100][100];
    for (int r = 0; r < baris; r++) {
        for (int c = 0; c < kolom; c++) {
            int pos = r * kolom + c + 1;
            if (pos <= w.totalSlot) peta[r][c] = pos;
            else peta[r][c] = 0;
        }
    }

    cout << "\nDenah wilayah " << w.nama << " (X = terisi)\n";
    for (int r = 0; r < baris; r++) {
        for (int c = 0; c < kolom; c++) cout << "+----";
        cout << "+\n";

        for (int c = 0; c < kolom; c++) {
            cout << "|";
            if (peta[r][c] == 0) {
                cout << "    ";
            } else {
                int num = peta[r][c];
                if (w.slot[num-1].terisi) {
                    cout << "  X ";
                } else {
                    if (num < 10) cout << "  " << num << " ";
                    else if (num < 100) cout << " " << num << " ";
                    else cout << num << " ";
                }
            }
        }
        cout << "|\n";
    }
    for (int c = 0; c < kolom; c++) cout << "+----";
    cout << "+\n";
}

void hapusWilayah() {
    if (jumlahWilayah == 0) {
        cout << "Belum ada wilayah untuk dihapus.\n";
        return;
    }
    string namaHapus;
    cout << "Masukkan nama wilayah yang akan dihapus: ";
    cin >> namaHapus;
    int indeks = -1;
    for (int i = 0; i < jumlahWilayah; i++) {
        if (wilayah[i].nama == namaHapus) {
            indeks = i;
            break;
        }
    }
    if (indeks == -1) {
        cout << "Wilayah tidak ditemukan.\n";
        return;
    }
    for (int i = indeks; i < jumlahWilayah - 1; i++) {
        wilayah[i] = wilayah[i+1];
    }
    jumlahWilayah--;
    cout << "Wilayah \"" << namaHapus << "\" berhasil dihapus.\n";
}

void tandaiSlotTerisi() {
    if (jumlahWilayah == 0) {
        cout << "Belum ada wilayah.\n";
        return;
    }
    string nama;
    cout << "Masukkan nama wilayah: ";
    cin >> nama;
    int indeks = -1;
    for (int i = 0; i < jumlahWilayah; i++) {
        if (wilayah[i].nama == nama) {
            indeks = i;
            break;
        }
    }
    if (indeks == -1) {
        cout << "Wilayah tidak ditemukan.\n";
        return;
    }

    int idSlot;
    cout << "Masukkan nomor slot yang akan ditandai terisi (1 - " << wilayah[indeks].totalSlot << "): ";
    cin >> idSlot;
    if (idSlot < 1 || idSlot > wilayah[indeks].totalSlot) {
        cout << "Nomor slot tidak valid.\n";
        return;
    }
    tandaiSlotDenganPointer(&wilayah[indeks].slot[idSlot-1], "Anonim", "Ortu", "Senin, 01-01-2026");
}

void lihatDataWilayah() {
    if (jumlahWilayah == 0) {
        cout << "Belum ada data wilayah.\n";
        return;
    }
    cout << "\n--- Daftar Wilayah ---\n";
    for (int i = 0; i < jumlahWilayah; i++) {
        Wilayah *ptrWilayah = &wilayah[i]; 
        int tersedia = 0;
        for (int j = 0; j < ptrWilayah->totalSlot; j++) {
            if (!ptrWilayah->slot[j].terisi) tersedia++;
        }
        cout << i+1 << ". Nama: " << ptrWilayah->nama
             << " | Baris: " << ptrWilayah->baris
             << " | Kolom: " << ptrWilayah->kolom
             << " | Slot total: " << ptrWilayah->totalSlot
             << " | Tersedia: " << tersedia
             << " | Harga per makam: " << ptrWilayah->hargaPerMakam << "\n";

        tampilkanDenahWilayah(i);
    }
}

void menuAdmin() {
    int pilihan = 0;
    do {
        cout << "\n=== MANAJEMEN DATA PEMAKAMAN (ADMIN) ===\n";
        cout << "1. Tambah Wilayah\n";
        cout << "2. Hapus Wilayah\n";
        cout << "3. Lihat Data Wilayah (termasuk denah)\n";
        cout << "4. Tandai Slot Terisi\n";
        cout << "5. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahWilayah(); break;
            case 2: hapusWilayah(); break;
            case 3: lihatDataWilayah(); break;
            case 4: tandaiSlotTerisi(); break;
            case 5: cout << "Kembali ke menu utama.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

void lihatDaftarMakam() {
    if (jumlahWilayah == 0) {
        cout << "Belum ada wilayah.\n";
        return;
    }
    cout << "\n--- List Makam ---\n";
    for (int i = 0; i < jumlahWilayah; i++) {
        int tersedia = 0;
        for (int j = 0; j < wilayah[i].totalSlot; j++) {
            if (!wilayah[i].slot[j].terisi) tersedia++;
        }
        cout << i+1 << ". " << wilayah[i].nama
             << " | Baris: " << wilayah[i].baris
             << " | Kolom: " << wilayah[i].kolom
             << " | Slot total: " << wilayah[i].totalSlot
             << " | Tersedia: " << tersedia
             << " | Harga: " << wilayah[i].hargaPerMakam << "\n";

        tampilkanDenahWilayah(i);
    }
}

void pesanMakam() {
    if (jumlahWilayah == 0) {
        cout << "Belum ada wilayah untuk dipesan.\n";
        return;
    }

    while (true) {
        lihatDaftarMakam();
        cout << "Pilih nomor wilayah (0 = kembali): ";
        int nomorWilayah;
        cin >> nomorWilayah;
        if (nomorWilayah == 0) return; 
        if (nomorWilayah < 1 || nomorWilayah > jumlahWilayah) {
            cout << "Pilihan wilayah tidak valid.\n";
            continue;
        }
        int indeksWilayah = nomorWilayah - 1;

        tampilkanDenahWilayah(indeksWilayah);

        cout << "Slot tersedia di wilayah " << wilayah[indeksWilayah].nama << ":\n";
        bool adaSlot = false;
        for (int i = 0; i < wilayah[indeksWilayah].totalSlot; i++) {
            if (!wilayah[indeksWilayah].slot[i].terisi) {
                cout << wilayah[indeksWilayah].slot[i].id << " ";
                adaSlot = true;
            }
        }
        cout << "\n";
        if (!adaSlot) {
            cout << "Maaf, tidak ada slot tersedia di wilayah ini.\n";
            continue;
        }

        cout << "Pilih nomor slot (0 = kembali ke pilih wilayah): ";
        int nomorSlot;
        cin >> nomorSlot;
        if (nomorSlot == 0) continue; 
        if (nomorSlot < 1 || nomorSlot > wilayah[indeksWilayah].totalSlot) {
            cout << "Nomor slot tidak valid.\n";
            continue;
        }
        if (wilayah[indeksWilayah].slot[nomorSlot-1].terisi) {
            cout << "Slot sudah terisi. Pilih slot lain.\n";
            continue;
        }

        cout << "Harga untuk slot " << nomorSlot << " = " << wilayah[indeksWilayah].hargaPerMakam << "\n";
        cout << "Ketik 'Y' untuk bayar dan lanjut, '0' untuk kembali: ";
        string konfirmasiPembayaran;
        cin >> konfirmasiPembayaran;
        if (konfirmasiPembayaran == "0") {
            continue;
        }
        if (!(konfirmasiPembayaran == "Y" || konfirmasiPembayaran == "y")) {
            cout << "Pembayaran dibatalkan. Kembali ke pilih wilayah.\n";
            continue;
        }

        string namaJenazah, namaOrtu;
        cout << "Masukkan nama jenazah (satu kata, tanpa spasi): ";
        cin >> namaJenazah;
        cout << "Masukkan nama orang tua jenazah (satu kata, tanpa spasi): ";
        cin >> namaOrtu;

        string hari;
        int tanggal, bulan, tahun;
        cout << "Masukkan hari wafat (satu kata, mis. Senin): ";
        cin >> hari;
        cout << "Masukkan tanggal (1-31): ";
        cin >> tanggal;
        cout << "Masukkan bulan (1-12). Gunakan angka, bukan nama bulan. Contoh: Januari=1, Februari=2\n";
        cin >> bulan;
        cout << "Masukkan tahun (mis. 2026): ";
        cin >> tahun;

        if (tanggal < 1 || tanggal > 31) {
            cout << "Tanggal tidak valid. Pemesanan dibatalkan.\n";
            continue;
        }
        if (bulan < 1 || bulan > 12) {
            cout << "Bulan tidak valid. Pemesanan dibatalkan.\n";
            continue;
        }
        if (tahun <= 0) {
            cout << "Tahun tidak valid. Pemesanan dibatalkan.\n";
            continue;
        }

        string tanggalWafat = hari + ", " + duaDigit(tanggal) + "-" + duaDigit(bulan) + "-" + to_string(tahun);

        // contoh penggunaan pointer (*)
        tandaiSlotDenganPointer(&wilayah[indeksWilayah].slot[nomorSlot-1], namaJenazah, namaOrtu, tanggalWafat);

        cout << "Pemesanan berhasil! Slot " << nomorSlot << " di wilayah " << wilayah[indeksWilayah].nama << " telah dipesan.\n";
        cout << "Nama jenazah: " << namaJenazah << "\n";
        cout << "Nama orang tua: " << namaOrtu << "\n";
        cout << "Tanggal wafat: " << tanggalWafat << "\n";

        return;
    }
}

void menuUser() {
    int pilihan = 0;
    do {
        cout << "\n=== MENU USER ===\n";
        cout << "1. Lihat List Makam\n";
        cout << "2. Pesan Makam\n";
        cout << "3. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: lihatDaftarMakam(); break;
            case 2: pesanMakam(); break;
            case 3: cout << "Kembali ke menu utama.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);
}

int main() {
    int pilihan;
    do {
        cout << "\n=== MENU REGISTER & LOGIN ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: daftarPengguna(); break;
            case 2: {
                string peran = masukPengguna();
                if (peran == "") return 0; 
                if (peran == "admin") {
                    menuAdmin();
                } else {
                    menuUser();
                }
                break;
            }
            case 3: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);
    return 0;
}
