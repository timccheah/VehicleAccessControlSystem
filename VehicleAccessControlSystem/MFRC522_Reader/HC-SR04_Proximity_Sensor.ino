
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

float duration;

void HC_SR04Setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void HR_SR04Loop(){
   digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(8);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("  Distance: ");
  Serial.println(distance);
  delay(100);
  

}

  bool check(int distance) {
      if(distance <= 15) {
        return true;
        Serial.print(" TRUE ");
      } else {
        return false;
        Serial.print(" FALSE ");
      }
  }

/*
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(16);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(32);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

 if (distance < 20) {
    
 }

}

  */
