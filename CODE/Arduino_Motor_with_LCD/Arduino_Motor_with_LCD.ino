/*
Exploring Arduino - Code Listing 4-3: H-Bridge Potentiometer Speed Control
http://www.exploringarduino.com/content/ch4

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(5,6,11,13,12,10);

//Hbridge Motor Control
const int EN=9;   //Half Bridge 1 Enable
const int MC1=3;  //Motor Control 1
const int MC2=2;  //Motor Control 2
const int POT=0;  //POT on Analog Pin 0

int val = 0;      //for storing the reading from the POT
int velocity = 0; //For storing the desired velocity (from 0-255)
int count = 0;

void setup()
{
    pinMode(EN, OUTPUT);
    pinMode(MC1, OUTPUT);
    pinMode(MC2, OUTPUT);
    lcd.begin(16,2);
    lcd.print("hello world");
    brake(); //Initialize with motor stopped
    Serial.begin(9600);
    lcd.clear();
}

void loop()
{
    val = analogRead(POT);
    //lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current Vel:");
    
    
    //go forward
    if (val > 562)
    {
        velocity = map(val, 563, 1023, 0, 255);
        printScreen(velocity);
        forward(velocity);
    }
 
    //go backward
    else if (val < 462)
    {
        velocity = map(val, 461, 0, 0, 255);
        int velocity2 = -1* velocity;
        printScreen(velocity2);
        reverse(velocity);
    }
 
    //brake
    else
    {
        velocity = 0;
        printScreen(velocity);
        brake();
    }
    
}

void printScreen(int number){
  if(count%10==0){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(String(number));}
  count++;
}

//Motor goes forward at given rate (from 0-255)
void forward (int rate)
{
    digitalWrite(EN, LOW);
    digitalWrite(MC1, HIGH);
    digitalWrite(MC2, LOW);
    analogWrite(EN, rate);
}

//Motor goes backward at given rate (from 0-255)
void reverse (int rate)
{
    digitalWrite(EN, LOW);
    digitalWrite(MC1, LOW);
    digitalWrite(MC2, HIGH);
    analogWrite(EN, rate);
}

//Stops motor
void brake ()
{
    digitalWrite(EN, LOW);
    digitalWrite(MC1, LOW);
    digitalWrite(MC2, LOW);
    digitalWrite(EN, HIGH);
}

