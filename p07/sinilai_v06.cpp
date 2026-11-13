// SiNilai v0.6: v0.5 yang tangguh terhadap masukan salah. Dibangun di atas v0.5 (laporan kelas).
// Yang baru: angka dibaca dengan aman (cin.fail, clear, ignore), nama divalidasi dan dirapikan
// huruf per huruf. Perhatikan: pola pembacaan aman ditulis berulang untuk empat komponen;
// itu sengaja, supaya di Pertemuan 9 kamu merasakan sendiri gunanya fungsi.
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    const double BOBOT_KEHADIRAN = 0.10;
    const double BOBOT_MINGGUAN = 0.45;
    const double BOBOT_UTS = 0.25;
    const double BOBOT_UAS = 0.20;
    const double BATAS_LULUS = 60;

    int banyak_mhs = 0;
    cout << "=== SiNilai v0.6 ===\n";
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> banyak_mhs;
    while (cin.fail() || banyak_mhs < 1)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Input tidak valid. Masukkan jumlah mahasiswa: ";
        cin >> banyak_mhs;
    }
    // TODO 1: do-while di atas berputar tanpa henti kalau pengguna mengetik huruf (cin gagal, isi jadi 0).
    //         Ganti dengan pola input_aman.cpp: baca sekali, lalu while (cin.fail() || jumlah_mahasiswa < 1)
    //         { cin.clear(); cin.ignore(1000, '\n'); minta lagi; }.

    cin.ignore(1000, '\n'); // buang Enter yang tersisa setelah angka, supaya getline nama tidak memungutnya

    cout << fixed << setprecision(2);

    double jumlah_semua_nilai = 0;
    int banyak_lulus = 0;
    int sebaran[5] = {0, 0, 0, 0, 0}; // indeks 0..4 mewakili A, B, C, D, E
    double skor_terbaik = -1;
    string nama_terbaik;

    for (int urutan = 1; urutan <= banyak_mhs; urutan++)
    {
        string nama_mhs;
        string npm;
        double hadir = 0;
        double tugas_mingguan = 0;
        double nilai_uts = 0;
        double nilai_uas = 0;

        cout << "\n--- Mahasiswa ke-" << urutan << " dari " << banyak_mhs << " ---\n";

        cout << "Nama      : ";
        getline(cin, nama_mhs);
        // TODO 2: bungkus pembacaan nama dengan do-while seperti validasi_nama.cpp: ulangi selama nama
        //         kosong atau hanya spasi, atau mengandung angka. Periksa huruf per huruf dengan for.
        bool nama_ok = false;

        while (!nama_ok)
        {
            bool punya_huruf = false;
            bool punya_angka = false;

            for (size_t k = 0; k < nama_mhs.size(); k++)
            {
                unsigned char karakter = nama_mhs[k];
                if (isalpha(karakter))
                    punya_huruf = true;
                else if (isdigit(karakter))
                    punya_angka = true;
            }

            nama_ok = punya_huruf && !punya_angka;

            if (!nama_ok)
            {
                cout << "Nama tidak valid. Masukkan nama lagi: ";
                getline(cin, nama_mhs);
            }
        }
        // TODO 3: rapikan nama seperti rapikan_nama.cpp: huruf pertama tiap kata besar, sisanya kecil.
        bool huruf_pertama = true;
        for (size_t k = 0; k < nama_mhs.length(); k++)
        {
            if (nama_mhs[k] == ' ')
            {
                huruf_pertama = true;
            }
            else
            {
                nama_mhs[k] = huruf_pertama ? toupper(nama_mhs[k]) : tolower(nama_mhs[k]);
                huruf_pertama = false;
            }
        }

        cout << "NPM       : ";
        getline(cin, npm);

        cout << "Kehadiran : ";
        cin >> hadir;
        // TODO 4: tambahkan while (cin.fail() || kehadiran < 0 || kehadiran > 100) { clear; ignore; minta lagi; }
        while (cin.fail() || hadir < 0 || hadir > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Kehadiran tidak valid. Masukkan lagi: ";
            cin >> hadir;
        }
        cout << "Mingguan  : ";
        cin >> tugas_mingguan;
        while (cin.fail() || tugas_mingguan < 0 || tugas_mingguan > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Mingguan tidak valid. Masukkan lagi: ";
            cin >> tugas_mingguan;
        }
        cout << "UTS       : ";
        cin >> nilai_uts;
        while (cin.fail() || nilai_uts < 0 || nilai_uts > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "UTS tidak valid. Masukkan lagi: ";
            cin >> nilai_uts;
        }
        cout << "UAS       : ";
        cin >> nilai_uas;
        while (cin.fail() || nilai_uas < 0 || nilai_uas > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "UAS tidak valid. Masukkan lagi: ";
            cin >> nilai_uas;
        }
        // TODO 5: ulangi pola TODO 4 untuk mingguan, uts, dan uas (ya, empat kali; catat rasanya).

        cin.ignore(1000, '\n'); // buang Enter setelah uas, supaya getline nama mahasiswa berikutnya bersih

        double skor = (hadir * BOBOT_KEHADIRAN) + (tugas_mingguan * BOBOT_MINGGUAN) + (nilai_uts * BOBOT_UTS) + (nilai_uas * BOBOT_UAS);

        string mutu = "E";
        if (skor >= 80)
            mutu = "A";
        else if (skor >= 75)
            mutu = "B+";
        else if (skor >= 70)
            mutu = "B";
        else if (skor >= 65)
            mutu = "C+";
        else if (skor >= 60)
            mutu = "C";
        else if (skor >= 40)
            mutu = "D";

        bool status_lulus = skor >= BATAS_LULUS;

        cout << "  " << left << setw(20) << nama_mhs << right << setw(7) << skor
             << "  " << left << setw(3) << mutu
             << (status_lulus ? "Lulus\n" : "Belum lulus\n");

        jumlah_semua_nilai += skor;
        if (status_lulus)
            banyak_lulus++;

        sebaran[mutu[0] - 'A']++;

        if (skor > skor_terbaik)
        {
            skor_terbaik = skor;
            nama_terbaik = nama_mhs;
        }
    }

    cout << "\n=== Laporan Kelas ===\n";
    cout << "Jumlah mahasiswa : " << banyak_mhs << "\n";
    cout << "Lulus            : " << banyak_lulus << "\n";
    cout << "Belum lulus      : " << banyak_mhs - banyak_lulus << "\n";
    cout << "Rata-rata kelas  : " << jumlah_semua_nilai / banyak_mhs << "\n";
    cout << "Tertinggi        : " << nama_terbaik << " (" << skor_terbaik << ")\n";

    cout << "\nSebaran huruf mutu:\n";
    for (int idx = 0; idx < 5; idx++)
    {
        cout << char('A' + idx) << " | ";
        for (int bar = 0; bar < sebaran[idx]; bar++)
        {
            cout << "#";
        }
        cout << " " << sebaran[idx] << "\n";
    }
    return 0;
}