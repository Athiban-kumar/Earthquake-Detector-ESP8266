#define SENSOR_PIN 14   // SW-420 on D6 (GPIO12)
#define SPEAKER_PIN 5   // Speaker/Buzzer on D5 (GPIO14)

int lastSensorState = LOW;
unsigned long beepStartTime = 0;
bool isBeeping = false;

// Function to force a reset
void(* resetFunc) (void) = 0;

void setup() {
    

    pinMode(SENSOR_PIN, INPUT);
    pinMode(SPEAKER_PIN, OUTPUT);
    digitalWrite(SPEAKER_PIN, LOW);
}

void loop() {
    int sensorState = digitalRead(SENSOR_PIN);  

    if (sensorState != lastSensorState) {  
        beepStartTime = millis();
        isBeeping = true;
    }

    if (isBeeping) {
        for (int freq = 500; freq <= 1500; freq += 50) {
            tone(SPEAKER_PIN, freq);
            delay(50);
        }
        for (int freq = 1500; freq >= 500; freq -= 50) {
            tone(SPEAKER_PIN, freq);
            delay(50);
        }
        if (millis() - beepStartTime >= 3000) {
            noTone(SPEAKER_PIN);
            isBeeping = false;
        }
    }

    lastSensorState = sensorState;
}
