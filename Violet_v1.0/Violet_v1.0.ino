 // Constants
const int trigPin = 3;
const int echoPin = 2;

const int leftBackward = 9; 
const int rightBackward = 10;
const int leftForward = 7; 
const int rightForward = 8; 

const int LED_R = 11;
const int LED_G = 12;
const int LED_B = 13;
const int MIN_TURN_DIST = 20; // Distanc e to an obstacle before it starts turning

float TURN_SPEED = 2.9; // The time in ms to turn a single degree. Just a guess and check estimate! 2.7

// Global variables
long duration;
int distance;


// Functions
void LED_RGB(bool red, bool green, bool blue);
void LEDoff ();

void driveForward(int vel);
void driveBackward();
void turnRight(int deg);
void turnLeft(int deg);
void stayStill(int t);
void drive(int dist);

boolean obstacleSensed();
int getDist();




void setup() {
  // put your setup code here, to run once:
  
  // Define inputs and outputs
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = getDist();

  drive(distance);
}


// Controlls driving of the car.
// Simply drives forward, until it sees an obstacle, then turns 45 deg to the left.
void drive(int dist) {

  // if there's a wall coming up, turn left!
    if (dist <= MIN_TURN_DIST) {
          
          turnLeft(90);
          stayStill(200);
    } else {
      /*
        driveForward(100);
        delay(500);
        stayStill();
        delay(500);
        driveForward(100);
        delay(500);
        stayStill();
        delay(500);
        */
        driveForward(100);
        //delay(500);
    }
}



/* FUNCTIONS */
// LED functions
void LED_RGB(bool red, bool green, bool blue) {
  if (red) { digitalWrite(LED_R, HIGH); }
  else { digitalWrite(LED_R, LOW); }

  if (green) { digitalWrite(LED_G, HIGH); }
  else { digitalWrite(LED_G, LOW); }

  if (blue) { digitalWrite(LED_B, HIGH); }
  else { digitalWrite(LED_B, LOW); }
}

void LEDoff() {
  LED_RGB(false, false, false);
}


// Motor functions
// vel is the given speed
void driveForward(int vel) {
  LED_RGB(false, true, false);

  analogWrite(leftForward, LOW);
  analogWrite(leftBackward, vel);
  analogWrite(rightForward, LOW);
  analogWrite(rightBackward, vel);

/*
 * 
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
  */
}
void driveBackward() {
  LED_RGB(true, true, false);
  
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH);
}

void turnLeft(int deg) {
  stayStill(200);
  LED_RGB(true, true, true);


  float turn_time = deg*TURN_SPEED;
  for (int i = 0; i <10; i++) {
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);

  delay(deg*TURN_SPEED/10);

  stayStill(10);
  }
}

// deg is the number of degrees we want to turn
// Lights up all 3 lights while turning right!
void turnRight(int deg) {
  LED_RGB(true, true, true); 
  stayStill(200);
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH);

  int turn_time = deg*TURN_SPEED;
  delay(deg*TURN_SPEED);
}

// t is the time in ms to wait
void stayStill(int t) {
  LED_RGB(true, false, false);
  
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , LOW);
  delay(t);
}



// Ultrasonic sensor functions
boolean obstacleSensed() {
  LED_RGB(false, false, true);
}

// Returns the distance to the nearest obstacle as sensed by the ultrasonic sensor.
int getDist() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long dur = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int dist= dur*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(dist);
  return dist;
}
