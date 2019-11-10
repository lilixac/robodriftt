/*for motor*/
#define m1a 2
#define m1b 3
#define m2a 4
#define m2b 5
#define enA 10
#define enB 11

/*for sensors*/
const int trigPin1 = 6;
const int echoPin1 = 7;
const int trigPin2 = 8;
const int echoPin2 = 9;
const int trigPin3 = 12;
const int echoPin3 = 13;

long durationF, durationR, durationL;
int distF, distR, distL;


char data, z;
char temp;


void automatic()
{

    automaticontrol();
   
}

void bth()
{
  if (Serial.available() >= 0)
  {
    z = Serial.read();
    if (z == '1' || z == '2' || z == '3' || z == '4' || z == '5' || z == '6' || z == '7'|| z == 'B'|| z == 'R'|| z == 'L'|| z == 'S'|| z == 'F'|| z == 'V')
      data = z;
    Serial.println(data);
  }
}

void left()
{
  analogWrite(enA, 75); // Send PWM signal to motor A
  analogWrite(enB, 75); // Send PWM signal to motor B
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);

}
void right()
{
  analogWrite(enA, 75); // Send PWM signal to motor A
  analogWrite(enB, 75); // Send PWM signal to motor B
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}
void forward()
{
  analogWrite(enA, 60); // Send PWM signal to motor A
  analogWrite(enB, 60); // Send PWM signal to motor B
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);

}
void backward()
{
  analogWrite(enA, 60); // Send PWM signal to motor A
  analogWrite(enB, 60); // Send PWM signal to motor B
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);

}

void wait()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);


  //analogWrite(enA, 50); // Send PWM signal to motor A
  //analogWrite(enB, 50); // Send PWM signal to motor B
  
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void distance()
{
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationF = pulseIn(echoPin1, HIGH);

  // Calculating the distance
  distF = durationF * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("distF: ");
  Serial.println(distF);

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(echoPin2, HIGH);

  // Calculating the distance
  distR = durationR * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("distR: ");
  Serial.println(distR);

  // Clears the trigPin
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(echoPin3, HIGH);

  // Calculating the distance
  distL = durationL * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("distL: ");
  Serial.println(distL);

  Serial.println("AutoLoop Ended");
}


void automaticontrol()
{
  distance(); //function call to calculate distance
  // Automatic motarization
if(distL <= 25 && distF <=25 && distR > distF && distR > distL )
{
  //when close to left wall and front wall turn right
  analogWrite(enA,50); // Send PWM signal to motor A
  analogWrite(enB,50); // Send PWM signal to motor B
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}
else if(distF <= 25 && distR <= 25 && distL > distF && distL > distR)
{
  //when close to right wall and front wall turn left
  analogWrite(enA, 50); // Send PWM signal to motor A
  analogWrite(enB, 50); // Send PWM signal to motor B
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}
else if (distF >= 50 && distF> distL && distF > distR)
{
  //move forward
  analogWrite(enA, 50); // Send PWM signal to motor A
  analogWrite(enB, 50); // Send PWM signal to motor B
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}
}


void loop()
{
  Serial.println("new loop");
  bth();

  switch (data)
  {
    case '1':
      forward();
      Serial.println("forward");
      break;

    case '3':
      backward();
      Serial.println("backward");
      break;

    case '2':
      right();
      Serial.println("right");
      break;

    case '4':
      left();
      Serial.println("left");
      break;

    case '5':
      wait();
      Serial.println("stop");
      break;

    case '6':
      automatic();
      Serial.println("auto");
      break;

  }
}
