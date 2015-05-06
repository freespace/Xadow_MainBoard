/*
  xadow.cpp
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-6-17

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#include <Wire.h>

#include "debug_x.h"
#include "xadowDfs.h"
#include "xadow.h"
#include "Sleep_x.h"

/*********************************************************************************************************
** Function name:           init
** Descriptions:            init
*********************************************************************************************************/
void xadow::init()
{
    // io of charge state
    CHRGdir &=~ CHRGbit;
    CHRGport |= CHRGbit;
    DONEdir &=~ DONEbit;
    DONEport |= DONEbit;
    
    rLEDport |= rLEDbit;
    gLEDport |= gLEDbit;
    rLEDdir |= rLEDbit;
    gLEDdir |= gLEDbit;
}

/*********************************************************************************************************
** Function name:           getAnalog
** Descriptions:            getAnalog
*********************************************************************************************************/
int xadow::getAnalog(int pin)
{
    int sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pin);
    }

    return sum>>5;
}

/*********************************************************************************************************
** Function name:           getBatVol
** Descriptions:            get voltage of battery
*********************************************************************************************************/
float xadow::getBatVol()
{
    float vol = 0;
    vol = getAnalog(PINBAT);
    vol = vol/1023.0*3.3*2;
    return vol;
}

/*********************************************************************************************************
** Function name:           getChrgState
** Descriptions:            get state of charge:
**                          NOCHARGE        0
**                          CHARGING        1
**                          CHARGDONE       2
*********************************************************************************************************/
unsigned char xadow::getChrgState()
{
    unsigned char Temp = CHRGpin & CHRGbit;
    
    if(!Temp)
    {
        return CHARGING;
    }
    Temp = DONEpin & DONEbit;
    if(!Temp)
    {
        return CHARGDONE;
    }
    return NOCHARGE;
}

void xadow::goToSleep(uint8_t sleepmode, unsigned long tSleep)
{
    sleep.setSleepMode(sleepmode);
    sleep.sleepDelay(tSleep);   //sleep for: sleepTime
}
/*********************************************************************************************************
** Function name:           pwrDown
** Descriptions:            pwrDown
*********************************************************************************************************/
void xadow::pwrDown(unsigned long tSleep)
{
    goToSleep(SLEEP_MODE_PWR_DOWN, tSleep);
}

/*********************************************************************************************************
** Function name:           wakeUp
** Descriptions:            wakeUp
*********************************************************************************************************/
void xadow::wakeUp()
{
}

/*********************************************************************************************************
** Function name:           greenLed
** Descriptions:            green Led drive
*********************************************************************************************************/
void xadow::greenLed(unsigned char state)
{
    if(LEDOFF == state)
    {
        gLEDport |= gLEDbit;
    }
    else if(LEDON == state)
    {
        gLEDport &=~ gLEDbit;
    }
    else if(LEDCHG == state)
    {
        gLEDport ^= gLEDbit;
    }

}

/*********************************************************************************************************
** Function name:           redLed
** Descriptions:            red Led drive
*********************************************************************************************************/
void xadow::redLed(unsigned char state)
{
    if(LEDOFF == state)
    {
        rLEDport |= rLEDbit;
    }
    else if(LEDON == state)
    {
        rLEDport &=~ rLEDbit;
    }
    else if(LEDCHG == state)
    {
        rLEDport ^= rLEDbit;
    }
}

xadow Xadow;

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
