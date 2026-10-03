const int GREEN_LED  = PB0;
const int YELLOW_LED = PB1;
const int RED_LED    = PB2;
const int BUZZER     = PB3;

void setup()
{
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);

    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        int value = Serial.parseInt();

        // Turn everything OFF
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, LOW);
        digitalWrite(BUZZER, LOW);

        if (value < 40)
        {
            // Normal
            digitalWrite(GREEN_LED, HIGH);
        }
        else if (value < 70)
        {
            // Medium
            digitalWrite(YELLOW_LED, HIGH);
        }
        else
        {
            // High / Alarm
            digitalWrite(RED_LED, HIGH);  
            digitalWrite(BUZZER, HIGH);
        }
    }
}