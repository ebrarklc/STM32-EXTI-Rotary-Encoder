#  STM32 Harici Kesme (EXTI) ile Rotary Encoder & Menü Kontrolü

Bu proje, STM32F407 mikrodenetleyicisinin EXTI (External Interrupt) birimini kullanarak dış dünyadan gelen asenkron sinyallerin (Enkoder hareketi) işlemciyi meşgul etmeden algılanmasını sağlamak amacıyla geliştirilmiştir[cite: 5]. 

Sistem, sonsuz tur dönebilen ve dönüş yönüne göre dijital sinyal üreten mekanik bir sensör olan Rotary Encoder'ın sinyallerini (Decoding) yazılımsal olarak çözümler[cite: 5].

## 🚀 Öne Çıkan Özellikler (Highlights)

*   **Interrupt (Kesme) Tabanlı Okuma:** Sistemin belirli aralıklarla butonu kontrol ettiği verimsiz Polling (Sorgulama) yöntemi yerine, pin durumundaki değişimlerin donanım tarafından işlemciye bildirildiği Kesme (Interrupt) yöntemi kullanılmıştır[cite: 5].
*   **Faz Farkı Analizi ile Yön Tespiti:** Encoder hareket ettiğinde `EXTI` hattı üzerinden donanımsal kesme tetiklenir ve `HAL_GPIO_EXTI_Callback` fonksiyonu içerisinde CLK ile DT pinleri arasındaki faz farkı analiz edilerek dönüş yönü (CW/CCW) hatasız tespit edilir[cite: 5].
*   **Özel LCD Sürücü Entegrasyonu:** Standart HAL kütüphanesinde bulunmayan 16x2 Karakter LCD sürücüsü (`lcd.h` ve `lcd.c`), 4-bit modunda çalışacak şekilde projeye entegre edilmiştir[cite: 5].
*   **Dinamik Kullanıcı Arayüzü:** LCD ekran üzerinden anlık sayaç değeri gösterilir ve fiziksel bir Switch (`PD10`) yardımıyla yön bilgisinin ekranda görüntülenip görüntülenmeyeceği dinamik olarak kontrol edilir[cite: 5].

## 🛠️ Donanım ve Pin Yapılandırması

| Bileşen | Pin Kodu | Mod (Mode) | Açıklama |
| :--- | :--- | :--- | :--- |
| **Encoder CLK** | `PB13` | GPIO_EXTI13 | Enkoder Saat Sinyali (Kesme Kaynağı)[cite: 5]. |
| **Encoder DT** | `PB12` | GPIO_Input | Enkoder Data Sinyali (Yön Bilgisi)[cite: 5]. |
| **Switch 6 (SW6)** | `PD10` | GPIO_Input | Ekran Modu Seçimi (Görüntüleme)[cite: 5]. |
| **LCD RS & EN** | `PD2`, `PD3` | GPIO_Output | LCD Register Select ve Enable Pinleri[cite: 5]. |
| **LCD Veri** | `PC4`, `PC13-15` | GPIO_Output | LCD 4-Bit Data Hatları (`D4-D7`)[cite: 5]. |

## 📂 Yazılım Mimarisi ve Karar Mekanizması

1.  **Donanım Filtrelemesi (Pull-Up):** Encoder pinleri donanımsal kararlılık için Pull-up modunda yapılandırılmış ve NVIC üzerinden `EXTI line[15:10]` kesmeleri aktifleştirilmiştir[cite: 5].
2.  **Yön Tayini Algoritması:** Saat Yönü (CW) dönüşte CLK sinyali DT sinyalinden önce değişir; Saat Yönü Tersinde (CCW) ise tam tersi gerçekleşir[cite: 5]. Kesme anında bu iki pinin anlık durumu karşılaştırılarak `encoder_sayac` değişkeni artırılır veya azaltılır[cite: 5].
3.  **Main Loop (Ana Döngü):** İşlemci, ana döngü içerisinde polling yapmaz; yalnızca arka planda güncellenen `encoder_sayac` değişkenini ve `SW6` anahtarının durumunu okuyarak LCD ekranı 50ms aralıklarla tazeler[cite: 5].

## 💻 Nasıl Çalıştırılır?

1.  STM32CubeIDE ile projeyi açın, derleyin (`Build`) ve karta yükleyin.
2.  Sistem başladığında özel bir açılış animasyonu belirecektir[cite: 5].
3.  Rotary Encoder modülünü çevirerek ekrandaki adım sayısının donanımsal kesmeler sayesinde sıfır gecikme ile nasıl güncellendiğini test edebilirsiniz.
4.  SW6 anahtarını kullanarak dönüş yönü bilgisini ("CW" veya "CCW") ekranda gizleyip açabilirsiniz[cite: 5].

   <img width="1024" height="683" alt="image" src="https://github.com/user-attachments/assets/97ebc4d2-5786-4315-97e2-08c8fb65a19f" />
