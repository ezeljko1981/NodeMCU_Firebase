/*
  hcsr04.h - Library for measuring distance by Ultrasonic sensor HC-SR04.
  Created by Željko Eremić, November 16, 2019.
  Released into the public domain.
*/
#ifndef HC_RS04_h
#define HC_RS04_h

typedef struct Distance
{
  int cm;
}Distance;

class HC_SR04
{
  public:
    HC_SR04();
    void SetPins(int trigPin, int echoPin);
    int ReadDistance();
  private:
    int m_trigPin;
    int m_echoPin;
    long m_duration;
    int m_distance;
};

#endif
