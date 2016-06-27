/*

  Proje Adı:          Arduino, Android Telefon ve Bluetooth ile Araba Yapımı
  Projeyi Yapımcısı:  Eren Keskin
  Yapımcı Websitesi:  http://herenkeskin.com
  Proje Detayı:       
  Versiyon:           0.1
  Son Güncelleme:     27.06.2016
  
*/

/* Motor Pinleri Kontrolü */
#define sagMotorInput1     9      // Sag Arka Tekerlek 1. Input
#define sagMotorInput2     10     // Sag Arka Tekerlek 2. Input
#define sagMotorEnable     11     // Sag Arka Tekerlek Hız Kontrol
#define solMotorInput1     6      // Sol On Tekerlek 1. Input
#define solMotorInput2     5      // Sol On Tekerlek 2. Input
#define solMotorEnable     3      // Sol On Tekerlek Hız Kontrol
#define sagaFar            12     // Sol Arka Far
#define solFar             13     // Sag Arka Far
#define buzzer             7      // Korna

/* Global Değişkenler */ 
int hiz = 0;
char karakter;

/* İleri Kontrolü */
void ileri(int donushizi){
    
    /* Yön Kontrolü */
    /* Yön Kontrolü, motorların ters veya düz yönde dönmesi ile kontrol edilir. */
    digitalWrite(sagMotorInput1, HIGH);
    digitalWrite(sagMotorInput2, LOW);  
    digitalWrite(solMotorInput1, LOW);
    digitalWrite(solMotorInput2, HIGH); 

    analogWrite(sagMotorEnable, donushizi);
    analogWrite(solMotorEnable, donushizi);

    /* Farları Sondur */
    digitalWrite(solFar, LOW);
    digitalWrite(sagFar, LOW);

    /* Kornayı Kapat */
    noTone(buzzer);
    
}

/* Geri Kontrolü */
void geri(int donushizi){

    /* Yön Kontrolü */
    /* Yön Kontrolü, motorların ters veya düz yönde dönmesi ile kontrol edilir. */
    digitalWrite(sagMotorInput1, LOW);
    digitalWrite(sagMotorInput2, HIGH);  
    digitalWrite(solMotorInput1, HIGH);
    digitalWrite(solMotorInput2, LOW); 

    analogWrite(sagMotorEnable, donushizi);
    analogWrite(solMotorEnable, donushizi);

    /* Farları Sondur */
    digitalWrite(solFar, LOW);
    digitalWrite(sagFar, LOW);

    /* Kornayı Kapat */
    noTone(buzzer);
    
}

/* Sağa Gidiş Kontrolü */
void sag(int donushizi){

    /* Yön Kontrolü */
    /* Yön Kontrolü, motorların ters veya düz yönde dönmesi ile kontrol edilir. */
    digitalWrite(sagMotorInput1, LOW);
    digitalWrite(sagMotorInput2, LOW);  
    digitalWrite(solMotorInput1, LOW);
    digitalWrite(solMotorInput2, HIGH); 

    analogWrite(sagMotorEnable, donushizi);
    analogWrite(solMotorEnable, donushizi);

    /* Farı Yak*/
    digitalWrite(solFar, LOW);
    digitalWrite(sagFar, HIGH);

    /* Kornayı Kapat */
    noTone(buzzer);
    
}

/* Sola Gidiş Kontrolü */
void sol(int donushizi){

    /* Yön Kontrolü */
    /* Yön Kontrolü, motorların ters veya düz yönde dönmesi ile kontrol edilir. */
    digitalWrite(sagMotorInput1, HIGH);
    digitalWrite(sagMotorInput2, LOW);  
    digitalWrite(solMotorInput1, LOW);
    digitalWrite(solMotorInput2, LOW); 

    analogWrite(sagMotorEnable, donushizi);
    analogWrite(solMotorEnable, donushizi);

    /* Farı Yak*/
    digitalWrite(solFar, HIGH);
    digitalWrite(sagFar, LOW);

    /* Kornayı Kapat */
    noTone(buzzer);
    
}

/* Sola Gidiş Kontrolü */
void dur(int donushizi){

    /* Yön Kontrolü */
    /* Yön Kontrolü, motorların ters veya düz yönde dönmesi ile kontrol edilir. */
    digitalWrite(sagMotorInput1, LOW);
    digitalWrite(sagMotorInput2, LOW);  
    digitalWrite(solMotorInput1, LOW);
    digitalWrite(solMotorInput2, LOW); 

    analogWrite(sagMotorEnable, donushizi);
    analogWrite(solMotorEnable, donushizi);

    /* Farları Sondur */
    digitalWrite(solFar, LOW);
    digitalWrite(sagFar, LOW);

    /* Kornayı Kapat */
    noTone(buzzer);
    
}

void setup() {

  /* Serial Monitorü Açalım */
  Serial.begin(9600);
    
  /* Motorlardan gelen Pinlerin Kontrolü */
  pinMode(sagMotorInput1, OUTPUT);
  pinMode(sagMotorInput2, OUTPUT);
  pinMode(solMotorInput1, OUTPUT);
  pinMode(solMotorInput2, OUTPUT);

  /* Enable Pinleri Kontrolü */
  pinMode(sagMotorEnable, OUTPUT);
  pinMode(solMotorEnable, OUTPUT);

  /* Far Ayarları */
  pinMode(solFar, OUTPUT);
  pinMode(sagaFar, OUTPUT);

}

void loop() {
  
  if (Serial.available() > 0){
    karakter = Serial.read();               // Telefondan gelen veriyi okuyoruz.
    if(karakter == 'i'){                    // Eğer ileriyi temsil ediyor ise;
      ileri(255);                           
      Serial.println("Ileri Gidiliyor.");    
    }else if(karakter == 's'){              // Eğer sağı temsil ediyor ise;
      sag(255);  
      Serial.println("Saga Gidiliyor.");
    }else if(karakter == 'g'){              // Eğer geriyi temsil ediyor ise;
      geri(255);  
      Serial.println("Geri Gidiliyor.");
    }else if(karakter == 'l'){              // Eğer solu temsil ediyor ise;
      sol(255); 
      Serial.println("Sola Gidiliyor."); 
    }else if(karakter == 'd'){              // Eğer durmayı temsil ediyor ise;
      dur(0); 
      Serial.println("Arac Durdu."); 
    }else if(karakter == 't'){              // Eğer sol sinyal'e basıldıysa;
      noTone(buzzer);
      digitalWrite(sagFar, LOW);
      digitalWrite(solFar, HIGH);
      Serial.println("Sola Sinyal Verildi"); 
    }else if(karakter == 'y'){              // Eğer sağ sinyal'e basıldıysa;
      noTone(buzzer);
      digitalWrite(solFar, LOW);
      digitalWrite(sagFar, HIGH);
      Serial.println("Saga Sinyal Verildi"); 
    }else if(karakter == 'u'){              // Eğer dörtlüler yakıldıysa;
      Serial.println("Dortluler Yakildi.");
      noTone(buzzer);
      digitalWrite(sagFar, HIGH); 
      digitalWrite(solFar, HIGH);
      delay(500);
      digitalWrite(sagFar, LOW); 
      digitalWrite(solFar, LOW);
      delay(500);
    }else if(karakter == 'k'){              // Eğer kornaya basıldıysa;
      digitalWrite(solFar, LOW);
      digitalWrite(sagFar, LOW);
      tone(buzzer, 1000,500);
      Serial.println("Saga Sinyal Verildi"); 
    }
   }
}

