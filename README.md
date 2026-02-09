# Sistem Instrumentasi Cerdas (WSN & Edge AI) 📡🤖

Repositori ini berisi materi, dokumentasi, dan kode sumber untuk rangkaian praktikum mata kuliah **Sistem Instrumentasi Cerdas**. Fokus utama adalah integrasi *Wireless Sensor Network* (WSN), *Internet of Things* (IoT), dan implementasi *Edge AI*.

---

## 📋 Daftar Modul Praktikum

| Pertemuan | Nama Modul | Deskripsi |
| :--- | :--- | :--- |
| **01** | [Pendahuluan & Konfigurasi](./01_Pendahuluan_Konfigurasi) | Konfigurasi dasar komunikasi Node-to-Gateway. |
| **02** | [RSSI Analysis](./02_RSSI_Analysis) | Pengukuran kekuatan sinyal nirkabel (RSSI). |
| **03** | [Integrasi Nirkabel](./03_Integrasi_Nirkabel) | Sinkronisasi antar perangkat dalam sistem nirkabel. |
| **04** | [WSN-IoT](./04_WSN_IoT) | Menghubungkan node sensor ke platform Cloud/Supabase. |
| **05** | [ML/DL & Edge AI](./05_Edge_AI) | Implementasi model cerdas pada perangkat Edge (ESP32-S3). |
| **06** | [Proyek Sederhana I](./06_Proyek_Sederhana_1) | Implementasi terintegrasi Tahap I. |
| **07** | [Proyek Sederhana II](./07_Proyek_Sederhana_2) | Finalisasi dan pengujian sistem end-to-end. |

---

## 📚 Referensi Repositori & Library Eksternal

Untuk mendukung praktikum ini, kita menggunakan beberapa library *open-source* ternama sebagai basis komunikasi dan pemrosesan data:

* **[RadioHead](https://github.com/PaulStoffregen/RadioHead)** - Library utama untuk manajemen paket data pada berbagai modul radio (LoRa, nRF24L01, RFM69). Sangat penting untuk modul **Praktikum 1-3**.
* **[TensorFlow Lite Micro](https://github.com/tensorflow/tflite-micro)** - Framework utama untuk menjalankan model Machine Learning di mikrokontroler. Digunakan pada **Praktikum 5**.
* **[Supabase-Arduino](https://github.com/arthuro555/supabase-arduino)** - Client library untuk menghubungkan ESP32 langsung ke database Supabase.
* **[ArduinoJson](https://github.com/bblanchon/ArduinoJson)** - Library standar untuk parsing data JSON dalam komunikasi IoT.

---

## 🛠️ Tech Stack

* **Hardware:** ESP32-S3, LoRa Transceiver, Sensor Analog/Digital.
* **Edge AI:** TensorFlow Lite / EloquentTinyML.
* **Backend:** Supabase (PostgreSQL & Edge Functions).
* **Protocol:** LoRa (via RadioHead), MQTT, HTTP.

---

## 🚀 Cara Memulai

1.  **Clone Repositori:**
    ```bash
    git clone [https://github.com/username-anda/nama-repo.git](https://github.com/username-anda/nama-repo.git)
    ```
2.  **Instalasi RadioHead:**
    Unduh library [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/) dan masukkan ke folder `libraries` di Arduino IDE Anda.
3.  **Konfigurasi Device:**
    Edit file `config.h` di setiap folder praktikum untuk menyesuaikan frekuensi radio dan kredensial WiFi.

---

## 👨‍🏫 Instruktur
**(1)Devandri Suherman,(2)Fariska Aulia A.**
*(1)Bandung Institute of Technology (ITB)*
*(2)Politeknik Negeri Bandung*

****
*Politeknik Negeri Bandung*
---
Copyright © 2026 - Sistem Instrumentasi Cerdas
