//test commit
//
#define BLUE 2
#define GREEN 3
#define YELLOW 4
#define RED 5
#define RDY_LIGHT 6
#define RDY_Button 7
#define SENSOR 1

int State = 0;
int State_Wainting = 0;
int TIME_TO_WARM_UP = 900;
int Timer = 0;
bool Ready = false;
void setup()
{

    Serial.begin(9600);
    pinMode(BLUE, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(RDY_LIGHT, OUTPUT);
    Serial.print("Alcohol for Arduino - Jerebern  2020");
}


void loop()
{

    switch (State) {

    case 0:
        Waiting();
        Timer++;
        delay(1000); // WAIT FOR 5 SEC             
        break;

    case 1:
        Warm_And_Ready();
        break;

    }

    if (Timer > TIME_TO_WARM_UP & !Ready) {
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
        digitalWrite(RDY_LIGHT, HIGH);
        State = 1;
        Serial.print("SENSOR is Warm_And_Ready  \n");
        Ready = false;
    }
    else
    {
        Serial.print("SENSOR is warming up and Waiting.. \n");
        Serial.print("Timer state : ");
        Serial.print(Timer, DEC);
        Serial.print("\n");
    }


}

void Waiting() {

    switch (State_Wainting) {

    case 0:
        digitalWrite(BLUE, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
        State_Wainting++;
        break;

    case 1:
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
        State_Wainting++;
        break;

    case 2:
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(RED, LOW);
        State_Wainting++;
        break;

    case 3:
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, HIGH);
        State_Wainting = 0;    //RETURN 
        break;

    }
    digitalWrite(RDY_LIGHT, LOW);

}
void Warm_And_Ready() {
    int Sensor_Value = 0;
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(RDY_LIGHT, HIGH);
    Sensor_Value = readAlcohol_FROM_Sensor();

    if (Sensor_Value > 99)
        printAlcoholLevelOnLED(Sensor_Value);

}

int readAlcohol_FROM_Sensor() {
    int i; //Declare before too keep the value after the reading
    int average =  0;

    for (int i = 0; i < 25; i++) {

        average = average + analogRead(SENSOR);

        if(digitalRead(RDY_LIGHT))
            digitalWrite(RDY_LIGHT,LOW);
          else
            digitalWrite(RDY_LIGHT,HIGH);
        delay(15);
    }

    average = average / i + 1;
    Serial.print(average, DEC);
    return average;
}

void printAlcoholLevelOnLED(int value)
{
    if (value < 100)
    {
        Serial.println("No alcohol");
        digitalWrite(BLUE, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
    }
    else if (value > 101 && value < 200) {
        Serial.println("Somme alcohol");
        digitalWrite(BLUE, HIGH);
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
    }
    else if (value > 201 && value < 300)
    {
        Serial.println("Low alcohol level.");
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
    }
    else if (value > 301 && value < 400)
    {
        Serial.println("Warning level");
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(RED, LOW);
    }
     else if (value > 401 && value < 500)
    {
        Serial.println("Warning level");
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(RED, LOW);
    }
     else if (value > 501 && value < 600)
    {
        Serial.println("HIGH level");
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, HIGH);
        digitalWrite(RED, HIGH);
    }          
    else if (value > 601 )
    {
        Serial.println("HIGH alcohol Level");
        digitalWrite(BLUE, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, HIGH);
    }

    delay(10000);
}
