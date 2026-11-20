// SiNilai v0.7 (hasil refactoring v0.6): satu program panjang dipecah menjadi sembilan fungsi.
// Aturan yang dipegang: data mengalir lewat parameter/return, tanpa variabel global.
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Konstanta global (aman karena tidak pernah berubah): porsi tiap komponen nilai.
const double PORSI_KEHADIRAN = 0.10;
const double PORSI_MINGGUAN = 0.45;
const double PORSI_UTS = 0.25;
const double PORSI_UAS = 0.20;

int bacaJumlah();
string bacaNama();
double bacaKomponen(string label);
void bacaData(string& nama, string& npm, double& kehadiran, double& mingguan, double& uts, double& uas);
double hitungNilaiAkhir(double kehadiran, double mingguan, double uts, double uas);
string hurufMutu(double nilai_akhir);
void cetakBaris(string nama, double nilai_akhir, string huruf, bool lulus);
void perbaruiPenghitung(char awal, int& a, int& b, int& c, int& d, int& e);
void cetakSebaran(int a, int b, int c, int d, int e);

int main() {
    cout << "=== SiNilai v0.7 ===\n";
    const int total_mhs = bacaJumlah();
    cout << fixed << setprecision(2);

    double akumulasi = 0;
    int yang_lulus = 0;
    int n_a = 0;
    int n_b = 0;
    int n_c = 0;
    int n_d = 0;
    int n_e = 0;
    double skor_max = -1;
    string juara;

    int no = 0;
    while (no < total_mhs) {
        no++;
        string nama;
        string npm;
        double hadir = 0;
        double mingguan = 0;
        double uts = 0;
        double uas = 0;

        cout << "\n--- Mahasiswa ke-" << no << " dari " << total_mhs << " ---\n";
        bacaData(nama, npm, hadir, mingguan, uts, uas);

        double skor = hitungNilaiAkhir(hadir, mingguan, uts, uas);
        string mutu = hurufMutu(skor);
        bool lulus = skor >= 60;
        cetakBaris(nama, skor, mutu, lulus);

        akumulasi += skor;
        yang_lulus += lulus ? 1 : 0;
        perbaruiPenghitung(mutu[0], n_a, n_b, n_c, n_d, n_e);
        if (skor > skor_max) {
            skor_max = skor;
            juara = nama;
        }
    }

    cout << "\n=== Laporan Kelas ===\n";
    cout << "Jumlah mahasiswa : " << total_mhs << "\n";
    cout << "Lulus            : " << yang_lulus << "\n";
    cout << "Belum lulus      : " << total_mhs - yang_lulus << "\n";
    cout << "Rata-rata kelas  : " << akumulasi / total_mhs << "\n";
    cout << "Tertinggi        : " << juara << " (" << skor_max << ")\n";
    cetakSebaran(n_a, n_b, n_c, n_d, n_e);
    return 0;
}

// Jumlah mahasiswa harus bilangan bulat >= 1; kalau tidak, ditolak dan ditanya lagi.
int bacaJumlah() {
    int hasil = 0;
    cout << "Jumlah mahasiswa (paling sedikit 1): ";
    while (!(cin >> hasil) || hasil < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Harus bilangan bulat paling sedikit 1. Coba lagi: ";
    }
    cin.ignore(1000, '\n');
    return hasil;
}

// Nama wajib berisi huruf (bukan hanya spasi) dan tanpa angka. Hasilnya dirapikan.
string bacaNama() {
    string masukan;
    while (true) {
        cout << "Nama      : ";
        getline(cin, masukan);
        if (masukan.find_first_not_of(' ') == string::npos) {
            cout << "Nama tidak boleh kosong.\n";
        } else if (masukan.find_first_of("0123456789") != string::npos) {
            cout << "Nama tidak boleh mengandung angka.\n";
        } else {
            break;
        }
    }

    for (size_t k = 0; k < masukan.size(); k++) {
        bool pembuka_kata = (k == 0 || masukan[k - 1] == ' ');
        if (pembuka_kata) {
            masukan[k] = toupper(masukan[k]);
        } else {
            masukan[k] = tolower(masukan[k]);
        }
    }
    return masukan;
}

// Satu pembacaan aman untuk semua komponen: angka 0 sampai 100, selain itu diulang.
double bacaKomponen(string label) {
    double angka = 0;
    cout << label << " : ";
    while (!(cin >> angka) || angka < 0 || angka > 100) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Harus angka 0 sampai 100. " << label << " : ";
    }
    return angka;
}

// Tidak ada return: keenam hasil "dititipkan" ke variabel pemanggil lewat referensi.
void bacaData(string& nama, string& npm, double& kehadiran, double& mingguan, double& uts, double& uas) {
    nama = bacaNama();
    cout << "NPM       : ";
    getline(cin, npm);
    kehadiran = bacaKomponen("Kehadiran ");
    mingguan = bacaKomponen("Mingguan  ");
    uts = bacaKomponen("UTS       ");
    uas = bacaKomponen("UAS       ");
    cin.ignore(1000, '\n');
}

double hitungNilaiAkhir(double kehadiran, double mingguan, double uts, double uas) {
    return kehadiran * PORSI_KEHADIRAN
         + mingguan * PORSI_MINGGUAN
         + uts * PORSI_UTS
         + uas * PORSI_UAS;
}

// Dicek dari batas bawah ke atas; return menghentikan fungsi begitu satu cabang cocok.
string hurufMutu(double nilai_akhir) {
    if (nilai_akhir < 50) {
        return "E";
    } else if (nilai_akhir < 60) {
        return "D";
    } else if (nilai_akhir < 70) {
        return "C";
    } else if (nilai_akhir < 75) {
        return "C+";
    } else if (nilai_akhir < 80) {
        return "B";
    } else if (nilai_akhir < 85) {
        return "B+";
    }
    return "A";
}

void cetakBaris(string nama, double nilai_akhir, string huruf, bool lulus) {
    string status = lulus ? "Lulus" : "Belum lulus";
    cout << "  " << left << setw(20) << nama << right << setw(7) << nilai_akhir
         << "  " << left << setw(3) << huruf << status << "\n";
}

// Parameter a sampai e merujuk ke penghitung milik pemanggil, bukan salinan.
void perbaruiPenghitung(char awal, int& a, int& b, int& c, int& d, int& e) {
    switch (awal) {
        case 'A':
            a += 1;
            break;
        case 'B':
            b += 1;
            break;
        case 'C':
            c += 1;
            break;
        case 'D':
            d += 1;
            break;
        default:
            e += 1;
            break;
    }
}

// Hanya membaca (pass by value), jadi tidak ada yang perlu dikembalikan ke pemanggil.
void cetakSebaran(int a, int b, int c, int d, int e) {
    const int hitung[5] = {a, b, c, d, e};
    cout << "Sebaran huruf mutu:\n";
    for (int k = 0; k < 5; k++) {
        cout << "  " << char('A' + k) << " : ";
        for (int s = 0; s < hitung[k]; s++) {
            cout.put('#');
        }
        cout << " (" << hitung[k] << ")\n";
    }
}
