# Project Kelompok Alpro 2026
#
Repository ini digunakan untuk pengerjaan project kelompok praktikum Algoritma dan Pemrograman.

## Cara Bergabung

### 1. Fork Repository

Klik tombol **Fork** pada repository ini untuk membuat salinan repository ke akun GitHub masing-masing.

### 2. Clone Repository Hasil Fork

```bash
git clone https://github.com/USERNAME-KALIAN/NAMA-REPOSITORY.git
cd NAMA-REPOSITORY
```

Pastikan Git sudah terinstall:

```bash
git --version
```

---

## Membuat Branch

Setiap anggota wajib bekerja pada branch masing-masing.

Format:

```text
dev-nama
```

Contoh:

```bash
git checkout -b dev-chandra
git checkout -b dev-rizki
git checkout -b dev-hirsya
```

---

## Sebelum Mulai Coding

Tambahkan repository utama sebagai upstream:

```bash
git remote add upstream https://github.com/OWNER/NAMA-REPOSITORY.git
```

Ambil perubahan terbaru:

```bash
git fetch upstream
git checkout main
git merge upstream/main
```

---

## Menyimpan Perubahan

```bash
git add .
git commit -m "Menyelesaikan bagian X"
```

Contoh:

```bash
git commit -m "Menambahkan menu inventory"
git commit -m "Memperbaiki validasi input"
git commit -m "Menyelesaikan tugas 2"
```

---

## Push ke Repository Fork

```bash
git push origin dev-nama
```

Contoh:

```bash
git push origin dev-chandra
```

---

## Membuat Pull Request

Setelah pekerjaan selesai:

1. Buka repository fork milik kalian di GitHub.
2. Klik **Compare & Pull Request**.
3. Pastikan target repository adalah repository utama kelompok.
4. Berikan judul dan deskripsi yang jelas.
5. Submit Pull Request.

Pull Request akan direview sebelum digabungkan ke branch utama.

---

## Aturan Kelompok

✅ Selalu sinkronkan repository sebelum mulai bekerja.

✅ Gunakan branch masing-masing.

✅ Commit dengan pesan yang jelas.

✅ Buat Pull Request setelah pekerjaan selesai.

❌ Jangan commit langsung ke branch `main`.

❌ Jangan menggunakan:

```bash
git push --force
```

❌ Jangan mengubah bagian anggota lain tanpa koordinasi.

❌ Jangan menghapus file project tanpa izin.

---

## Alur Kerja Singkat

```bash
git clone <repository-fork>

git checkout -b dev-nama

# coding

git add .

git commit -m "Perubahan"

git push origin dev-nama
```

Kemudian buat Pull Request ke repository utama.

---

## Jika Terjadi Error

Screenshot pesan error dan kirim ke grup agar dapat dibantu bersama.
