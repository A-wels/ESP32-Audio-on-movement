#define PIN_TRIGGER 12
#define PIN_ECHO    13

const int SENSOR_MAX_RANGE = 300; // in cm
unsigned long duration;
//measured distance. Not always a useful value 
 int distance;
 // keep two distances to measure movements
 int last_distance = 0;
 int new_distance = 0;

// change in distance that triggers the sound (cm)
int TRIGGER_DISTANCE = 15;
 // repeat measurements until a valid result is received
 int error = 1;

 // duration of the sound in ms
 int SOUND_DURATION = 180000;
 
void setup()
{
  Serial.begin(9600);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);

  // read initial distance
  while(error == 1){
  readDistance();
  }
  last_distance = new_distance;
  delay(500);
}

void loop()
{
  // update distance
  do{
  readDistance();
  }while(error==1);

  //if 
  if(abs(last_distance - new_distance) > TRIGGER_DISTANCE){
    digitalWrite(5, HIGH);
    // wait; prevent annoying repetitions.
    delay(SOUND_DURATION);
    digitalWrite(5, LOW);
  }
  delay(300);
}

void readDistance(){
    digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);

  duration = pulseIn(PIN_ECHO, HIGH);
  
  distance = duration/58;

  if (distance > SENSOR_MAX_RANGE || distance <= 0){
    error = 1;
  } else {
    error = 0;
    new_distance = distance;
  }

}
