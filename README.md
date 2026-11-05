# 📚 Digital Library System (C++)

Sebuah aplikasi *Command Line Interface* (CLI) berbasis bahasa C++ untuk mengelola sistem perpustakaan sederhana. Project ini dibuat untuk melatih pemahaman tentang **Struct, Vector, Relational Data, dan File I/O**.

## ✨ Fitur Utama
- **CRUD Buku**: Tambah, Lihat, Ubah, dan Hapus data buku.
- **Sistem Peminjaman**: Peminjam bisa meminjam buku (stok otomatis berkurang).
- **Sistem Pengembalian**: Mengembalikan buku dengan validasi nama peminjam dan judul buku.
- **Riwayat Peminjam**: Melihat daftar orang yang sedang meminjam buku.
- **Penyimpanan Permanen (File I/O)**: Data buku dan peminjaman disimpan ke dalam file `.txt` sehingga tidak hilang saat program ditutup.
- **Validasi Input**: Mencegah input kosong, ISBN yang salah, atau jumlah copy negatif.

## 🛠️ Cara Menjalankan Program
1. Pastikan kamu sudah menginstal compiler C++ (seperti `g++` atau MinGW).
2. Clone repository ini:
   ```bash
   git clone https://github.com/USERNAME-KAMU/Digital-Library-System.git
3. Compile file C++:
   g++ LMS.cpp -o library
4. Jalankan Program:
   ./library