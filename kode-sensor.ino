/*
 * Proyek UTS: Sistem Quality Control Otomatis Berbasis Edge Intelligence
 * Board : ESP32 DevKit V1
 */

const int PIN_TRIG = 5;
const int PIN_ECHO = 18;
const int PIN_LED_NORMAL = 2;
const int PIN_LED_ANOMALY = 4;
const int PIN_SERVO = 13;

const int SERVO_CHANNEL = 0;
const int SERVO_FREQ = 50;
const int SERVO_RESOLUTION = 16;
const int SERVO_POS_0_DEG = 1638;
const int SERVO_POS_90_DEG = 4915;

const int WINDOW_SIZE = 5;
const int ANOMALY_THRESHOLD = 15;
const int SAMPLING_DELAY = 50;
const int REJECT_DELAY = 800;

int readings[WINDOW_SIZE];
int readIndex = 0;
long total = 0;
int averageDistance = 0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED_NORMAL, OUTPUT);
  pinMode(PIN_LED_ANOMALY, OUTPUT);
  ledcAttach(PIN_SERVO, SERVO_FREQ, SERVO_RESOLUTION);
  ledcWrite(PIN_SERVO, SERVO_POS_0_DEG);
  for (int i = 0; i < WINDOW_SIZE; i++) readings[i] = 0;
  Serial.println("Sistem Siap.");
}

int readDistanceCM() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  long duration = pulseIn(PIN_ECHO, HIGH, 30000);
  if (duration == 0) return 0;
  return duration * 0.034 / 2;
}

void loop() {
  int currentDistance = readDistanceCM();
  if (currentDistance > 0 && currentDistance < 400) {
    total = total - readings[readIndex];
    readings[readIndex] = currentDistance;
    total = total + readings[readIndex];
    readIndex = (readIndex + 1) % WINDOW_SIZE;
    averageDistance = total / WINDOW_SIZE;

    Serial.print("Jarak: ");
    Serial.print(currentDistance);
    Serial.print(" cm | Rata-rata: ");
    Serial.print(averageDistance);
    Serial.println(" cm");

    if (averageDistance < ANOMALY_THRESHOLD) {
      Serial.println(">> ALERT: ANOMALI! Aktivasi Reject.");
      digitalWrite(PIN_LED_NORMAL, LOW);
      digitalWrite(PIN_LED_ANOMALY, HIGH);
      ledcWrite(PIN_SERVO, SERVO_POS_90_DEG);
      delay(REJECT_DELAY);
    } else {
      digitalWrite(PIN_LED_NORMAL, HIGH);
      digitalWrite(PIN_LED_ANOMALY, LOW);
      ledcWrite(PIN_SERVO, SERVO_POS_0_DEG);
    }
  }
  delay(SAMPLING_DELAY);
}
