#include <Time.h>
#include <TimeLib.h>

//Schedule
int startTime[] = {00, 00, 00, 1, 1, 2021}; //hour, minute, second, day, month, year
int dailyAlarm[] = {00, 00, 10};  //hour, minute, second

//Pins
const int buzzerPin = 9; //buzzer to arduino pin 9
const int temperaturePin = 0;//temperature sensor to analog arduino pin 0
const int humPin = A1; //humidity sensor to analog pin 1
const int tempLed = 3; //Temperature LED to arduino pin 3
const int humLed = 4; //Humidity LeD to arduino pin 4
const int humPower = 7;//humidity sensor power to arduino pin 7

//Alarms specifications
const int ALARM = 0; //Alarm Tone
const int alarmDuration = 1; //duration in seconds
const int frequency = 1000;

//Temperature Alarm Specifications
const int tempAlarm = 1; //Alarm Tone
const int minTemp = 65; //Minimun Temperature
const int maxTemp = 90; //Maximun Temperature

//Humidity Alarm Specifications
const int humAlarm = 2; //Alarm Tone
const int minHum = 10; //Minimun Humidity
const int maxHum = 540; //Maximun Humidity

int interval = 300;

void setup()
{
    Serial.begin(9600);
    setTime(startTime[0], startTime[1], startTime[2], startTime[3], startTime[4], startTime[5]); //hour, minute, second, day, month, year
    pinMode(buzzerPin, OUTPUT);
    pinMode(tempLed, OUTPUT);
    pinMode(humLed, OUTPUT);
    pinMode(humPower, OUTPUT);
    digitalWrite(humPower, LOW);
}

void loop()
{
    hourCheck();
    temperatureCheck();
    humidityCheck();
}

void hourCheck()
{
    if (dailyAlarm[0] == hour())
    {
        if (dailyAlarm[1] == minute())
        {
            if (second() >= dailyAlarm[2] && second() <= dailyAlarm[2] + 5)
            {
              buzzerSong(ALARM);
            }
        }
    }
}

void humidityCheck()
{
    digitalWrite(humPower, HIGH);
    delay(10);//wait 10 milliseconds
    int humidity = analogRead(humPin);//Read the SIG value form sensor
    digitalWrite(humPower, LOW);
    Serial.print("Unidad de Humedad: ");
    Serial.println(humidity);
    if (humidity < minHum)
    {
      digitalWrite(humLed, HIGH);
      buzzerSong(humAlarm);
      digitalWrite(humLed, LOW);
      delay(interval);
    }
    else if (humidity > maxHum)
    {
      digitalWrite(humLed, HIGH);
      buzzerSong(humAlarm);
    }
    else
    {
      digitalWrite(humLed, LOW);
    }
}
void temperatureCheck()
{
    int temperature = analogRead(temperaturePin); //get temperature
    float temperatureVolt = temperature * 5.0; //convert the read to volts
    temperatureVolt /= 1024.0; //convert the read to volts
    float temperatureC = (temperatureVolt - 0.5) * 100; //convert the volts to celsius
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0; //convert the volts to fahrenheit
    Serial.print("Temperatura: ");
    Serial.println(temperatureF);

    if (temperatureF < minTemp)
    {
      digitalWrite(tempLed, HIGH);
      buzzerSong(tempAlarm);
      digitalWrite(tempLed, LOW);
      delay(interval);
    }
    else if (temperatureF > maxTemp)
    {
      digitalWrite(tempLed, HIGH);
      buzzerSong(tempAlarm);
    }
    else
    {
      digitalWrite(tempLed, LOW);
    }
}

void buzzerSong(int song)
{
  switch(song)
  {
    case 0:     tone(buzzerPin, frequency); // Send 1KHz sound signal...
                delay(1000 * alarmDuration);        // ...for 1 sec
                noTone(buzzerPin);     // Stop sound...
                delay(1000);        // ...for 1 sec
                break;
                  break;
    case 1:     for (int i = 0; i < 3; i++)
                {
                  tone(buzzerPin, frequency); // Send 1KHz sound signal...
                  delay(500);        // ...for 1/2 sec
                  noTone(buzzerPin);     // Stop sound...
                  delay(500);        // ...for 1/2 sec
                }
                break;

    case 2:     for (int i = 0; i < 6; i++)
                {
                  tone(buzzerPin, frequency); // Send 1KHz sound signal...
                  delay(250);         // ...for 1/4 sec
                  noTone(buzzerPin);     // Stop sound...
                  delay(250);        // ...for 1/4 sec
                }
                break;

  }
}
