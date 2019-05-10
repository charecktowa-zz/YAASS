/*Includes the Arduino functions for avr-gcc*/
#include <Arduino.h>

/*For Fingerprint*/
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

uint8_t id;
byte newFP = 10;
byte checkFP = 11;
byte LED = 13;

bool thereisnoFP = false;

uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (!Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Esperando dedo valido #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagen tomada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Error de comunicacion");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Error de imagen");
        break;
      default:
        Serial.println("Error desconocido");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen añadida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen de baja calidad");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicación");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se encontró huella valida");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("No se pudo encontrar una imagen valida");
      return p;
    default:
      Serial.println("Error desconocidos");
      return p;
  }

  Serial.println("Retire el dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Coloque otra vez el mismo dedo");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Imagen tomada");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Error de comunicasancia");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imagen erronea");
        break;
      default:
        Serial.println("Error desconocido");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen toda fea");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicacion");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se encontró una huella");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Imagen invalida");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK converted!
  Serial.print("Creando modelo #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Huellas encontrados!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("No se encontraron coincidencia");
    return p;
  } else {
    Serial.println("Error desconocido");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Guardado!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Error de comunicación");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("No se alcanzó esa posición de memoria");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error escribiendo en la memoria");
    return p;
  } else {
    Serial.println("Error desconocodo");
    return p;
  }
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen tomada");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No se ha detectado ninguna huella");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de coneccion");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Error al obtener imagen");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Imagen convertida");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Imagen fea");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Error de comunicacion");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("No se encontro huella");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Imagen invalidad");
      return p;
    default:
      Serial.println("Error desconocido");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
int val1 = 0;
int val2 = 0;
void setup() {

  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  delay(100);
  Serial.println("\nInicializando lector de huellas...\n");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("El sensor tine: ");
  Serial.print(finger.templateCount); Serial.println(" huellas");


  if (finger.templateCount == NULL) {
    Serial.println("\nNo hay huellas.");
    Serial.println("Agregando huella maestra...");
    thereisnoFP = true;
  }
}

void loop () {

  if (digitalRead(10) == HIGH || thereisnoFP == true) {
    delay(100);
    Serial.println("Listo para agregar la huella!");
    Serial.println("Por favor ingrese el ID # (DE 1 A 127");
    id = readnumber();

    if (id == 0) {
      return;
    }

    Serial.print("Agregando ID #");
    Serial.println(id);

    while (!  getFingerprintEnroll());
    delay(100);
  }

  if (digitalRead(11) == HIGH) {

    for (int i = 0; i < 50; i++) {
      getFingerprintIDez();
    }

    int confidence = finger.confidence;
    if (confidence >= 50) {
      digitalWrite(LED, HIGH);
      delay(2000);
      digitalWrite(LED, LOW);
    }
  }
}