#include "MicroBit.h"

MicroBit uBit;

void Ventilator (int VentSpeed);
void Buzzer (int BuzzerTon);


int main() {


    uBit.init();

    //P0 als Analog Output definieren.
    uBit.io.P0.isOutput();
    uBit.io.P0.isAnalog();

    //P1 als Analog Output definieren.
    uBit.io.P1.isOutput();
    uBit.io.P1.isAnalog();

    // P2 als Degital Output definieren(rot).
    uBit.io.P2.isOutput();
    uBit.io.P2.isDigital();

    //P5 als Analog Input definieren(vent).
    uBit.io.P5.isInput();
    uBit.io.P5.isAnalog();

    // P8 als Digital Output definieren(Orange).
    uBit.io.P8.isOutput();
    uBit.io.P8.isDigital();

    //P11 als Analog Input definieren().
    uBit.io.P11.isInput();
    uBit.io.P11.isAnalog();

    // P12 als Digital Output definieren(Grün).
    uBit.io.P12.isOutput();
    uBit.io.P12.isDigital();

    //Variable initialisieren, in der die Temparatur gespeichert wird.
    int temperature = 0 ;
    int Button2 = 0;
    int Button1 = 0;

    //Dauerschleife, damit das Programm endlos läuft
    while(1){

        //Wenn kein Knopf gdrückt ist wird diese Schleife ausgeführt.
        while(Button2 == 1 && Button1 == 1){

            //Funktion liest Temparatur vom Sensor aus.
            temperature = uBit.thermometer.getTemperature();

            //Entscheidung was bei welcher Temparatur passiert.
            if (temperature > 24){
                Buzzer(1000);
                uBit.io.P0.setAnalogPeriod(1);
                Ventilator(1023);
                uBit.io.P1.setAnalogPeriod(1);
                uBit.io.P2.setDigitalValue(1);
                uBit.io.P8.setDigitalValue(0);
                uBit.io.P12.setDigitalValue(0);

            } else if (temperature < 23){

                uBit.io.P0.setAnalogValue(0);
                uBit.io.P1.setAnalogValue(0);
                uBit.io.P2.setDigitalValue(0);
                uBit.io.P8.setDigitalValue(0);
                uBit.io.P12.setDigitalValue(1);

            } else {

                uBit.io.P0.setAnalogValue(0);
                Ventilator(500);
                uBit.io.P1.setAnalogPeriod(1);
                uBit.io.P2.setDigitalValue(0);
                uBit.io.P8.setDigitalValue(1);
                uBit.io.P12.setDigitalValue(0);
            }


            uBit.display.scroll(temperature);
            //Abfrage ob die Pins 5 und 11 1 oder 0 sind. Zustand wird in Variable gespeichert.
            Button1 = uBit.io.P5.getDigitalValue();
            Button2 = uBit.io.P11.getDigitalValue();
            //Von hier geht es wieder an den Anfang der Schleife. Sind die Knöpfe beide 0 dann wird sie nochmals ausgeführt.
            //Ist einer der Knöpfe 1 dann wird in die nächste Schleife gesprungen.
        }

        //Diese Schleife wird ausgeführt solange ein Knopf 1 ist.
        while(Button1 > 1 || Button2 > 1){
            //Wenn Knopf 1 1 ist dann wird der Ventilator eingeschaltet.
            if(Button1 > 0){
                Ventilator(1023);
            }
            //Wenn Knopf 2 1 ist wird Buzzer eingeschaltet.

            if(Button2 > 0){
                Buzzer(1000);
            }
            //Abfrage ob die Pins 5 und 11 1 oder 0 sind. Zustand wird in Variable gespeichert.
            Button1 = uBit.io.P5.getDigitalValue();
            Button2 = uBit.io.P11.getDigitalValue();
            //Von hier geht es wieder an den Anfang der Schleife. Ist einer der Knöpfe 1 dann wird sie nochmals ausgeführt.
            //Sind beide Knöpfe 0 dann wird in die nächste Schleife gesprungen.
        }
    }
}

void Ventilator (int VentSpeed){
    uBit.io.P1.setAnalogValue(VentSpeed);
}

void Buzzer (int BuzzerTon){
    uBit.io.P0.setAnalogValue(BuzzerTon);
}