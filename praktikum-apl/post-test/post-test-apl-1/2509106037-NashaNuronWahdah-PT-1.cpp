#include <iostream>
#include <string>
using namespace std;

int main() {
    string nama, nim;
    string nama_login = "Nuron";
    string nim_login = "037";

    int ulang = 0;

    while (ulang < 3){
        cout << "Masukkan Username Anda: ";
        getline(cin, nama);
        cout << "Masukkan Password Anda: ";
        getline(cin, nim);

        if (nama == nama_login && nim == nim_login) {
            cout << "Login Berhasil!\n";
            break;
        }
        else {
            cout << "Username atau Password Anda Salah!\n";
            ulang++;
        }
    }

    if (ulang == 3){
        cout << "Anda telah gagal login sebanyak 3 kali!\n";
        cout << "Program akan berhenti.\n";
        return 0;
    }
    
    int pilihan = 0;
    double nilai;
    
    while (pilihan != 4) {
    	cout << "\n===Menu Utama===\n";
    	cout << "1. Konversi meter => Kilometer dan Centimeter\n";
    	cout << "2. Konversi Kilometer => Meter dan Centimeter\n";
    	cout << "3. Konversi Centimeter => Meter dan Kilometer\n";
    	cout << "4. Keluar\n";
    	cout << "Pilih menu(hanya angka): ";
    	cin >> pilihan;
    	
    	if (pilihan == 1) {
    		cout << "Masukkan nilai (Meter): ";
    		cin >> nilai;
    		cout << nilai << " m = " << nilai/1000 << " km dan " << nilai*100 << " cm\n";
    	}
    	else if (pilihan == 2){
    		cout << "Masukkan nilai (Kilometer): ";
    		cin >> nilai;
    		cout << nilai << " km = " << nilai*1000 << " m dan " << nilai*100000 << " cm\n";
    	}
    	else if (pilihan == 3) {
    		cout << "Masukkan nilai (Centimeter): ";
    		cin >> nilai;
    		cout << nilai << " cm = " << nilai/100 << " m dan " << nilai/100000 << " km\n";
    	}
    	else if (pilihan == 4) {
    		cout << "Keluar dari program. \n";
    	}
    	else {
    		cout << "Pilihan tidak valid\n";
    	}
    }
    
    return 0;
}
