const int trigPin = 3;
const int echoPin = 4;
const int relayPin = 11;
// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define MAX_DIST 13.00
#define CONTACT_DIST 3.0
long duration;
float dist;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

  //Sets the relay pin for the suction pump as Output
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin,HIGH);
}

void initiateSuction(){
  Serial.println(" Initiating Suction");
  //starts the suction when relay is LOW
  digitalWrite (relayPin,LOW); 
  delay(5000);
  reverseMotor();
  //Stops the suction when relay is HIGH
  delay(8000);
  digitalWrite(relayPin,HIGH);
  delay(5000);
  motorReset();
  delay(8000);
}

void reverseMotor(){
  Serial.println("Reversing motor");
  analogWrite(enA, 64);
	// Turn on ccw direction
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
  delay(2000);
  stopMotor();
}

void motorReset(){
  analogWrite(enA, 64);
	// Turn on cw direction
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  delay(2000);
  stopMotor();
  reverseMotor();
}

void moveMotor(){
  Serial.println(" Moving motor");
  // Set motors to maximum speed (0 to 255)
	analogWrite(enA, 64);
	// Turn on cw direction
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	delay(500);
}

void stopMotor(){
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}

  float triggerSensor(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist = duration * SOUND_VELOCITY/2;
    return dist;
  }

void loop() {
  float dist = triggerSensor();
  if(dist > MAX_DIST){
    Serial.println(dist);
    stopMotor();
    //do nothing
  }
  else if(dist <= MAX_DIST && dist > CONTACT_DIST){
    Serial.println(dist);
    moveMotor();
  }
  else if(dist <= CONTACT_DIST && dist > 0.00){
    Serial.println(dist);
    stopMotor();
    initiateSuction();
  }
}
