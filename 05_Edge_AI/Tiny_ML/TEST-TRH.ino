#include "model_data.h"
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

// Definisi dimensi sesuai dataset Python
#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
// Arena size disesuaikan, 20000 sudah cukup untuk model ringan
#define ARENA_SIZE 20000
#define NO_OF_OPS 10

// Pastikan nama array di model_data.h sesuai (biasanya comfort_model_tflite atau converted_model_tflite)
Eloquent::TF::Sequential<NO_OF_OPS, ARENA_SIZE> tf;

void setup() {
    Serial.begin(115200); 
    delay(1000);
    Serial.println("___ SISTEM PREDIKSI KENYAMANAN CERDAS (POLBAN) ___");
    
    tf.setNumInputs(NUMBER_OF_INPUTS);
    tf.setNumOutputs(NUMBER_OF_OUTPUTS);
    
    // Sesuaikan variabel array model dengan hasil output 'xxd' di Python
    while (!tf.begin(comfort_model_tflite).isOk()) {
        Serial.println("Gagal memuat model: " + tf.exception.toString());
        delay(5000);
    }
    
    Serial.println("Model Siap.");
    Serial.println("Format input Serial: suhu,kelembapan (Contoh: 28.5,70)");
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        
        int commaIndex = data.indexOf(',');
        if (commaIndex == -1) return; // Validasi format input

        float rawTemp = data.substring(0, commaIndex).toFloat();
        float rawHum = data.substring(commaIndex + 1).toFloat();
        
        // --- BAGIAN PENTING: NORMALISASI (Sesuai Logika Python) ---
        // Input harus dipetakan ke rentang 0-1 sebelum masuk ke model
        float input_normalized[2] = {
            rawTemp / 40.0f, 
            rawHum / 100.0f
        };
        
        unsigned long startTime = micros();
        
        // Eksekusi Prediksi
        if (!tf.predict(input_normalized).isOk()) {
            Serial.println("Inference Error: " + tf.exception.toString()); 
            return; 
        }

        unsigned long endTime = micros();
        
        // --- BAGIAN PENTING: DENORMALISASI ---
        // Hasil output model (0-1) dikalikan 10 kembali untuk skor kenyamanan
        float prediction = tf.output(0);
        float comfortScore = prediction * 10.0f;
        
        Serial.println("------------------------------------");
        Serial.print("Input Sensor  -> Suhu: "); Serial.print(rawTemp);
        Serial.print(" C, Lembap: "); Serial.print(rawHum); Serial.println("%");
        
        Serial.print("Hasil Prediksi Comfort Score (1-10): ");
        Serial.println(comfortScore, 2); // Menampilkan 2 angka di belakang koma
        
        Serial.print("Waktu Inference: ");
        Serial.print(endTime - startTime);
        Serial.println(" us");
        Serial.println("------------------------------------");
    }
}
