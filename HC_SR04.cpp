/*
  hcsr04.cpp - Library for measuring distance by Ultrasonic sensor HC-SR04.
  Created by Željko Eremić, November 16, 2019.
  Released into the public domain.
*/
#include "Arduino.h"
#include "HC_SR04.h"

HC_SR04::HC_SR04(){}

void HC_SR04::SetPins(int trigPin, int echoPin)
{
     m_trigPin = trigPin;
     m_echoPin = echoPin; 
}

int HC_SR04::ReadDistance()
{
    //Distance distance;
    // Clears the trigPin
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    m_duration = pulseIn(m_echoPin, HIGH);
    
    // Calculating the distance
    m_distance = m_duration*0.034/2;
    
    return m_distance;
}
