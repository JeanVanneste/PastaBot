# PastaBot

You can find here all the code that have been used for the Pasta Bot project.

The .ino files at the root of the repository are the final files of the source that were uploaded on the Arduino Mega.

If you want to have better comments, you can go in the differents folders were you will have the code of each task before the fusion for the demo.

## PT100

We wanted to use a PT100 (platine resistor with a restistance of 100 ohms at 0°C) for it waterproofness.
So we neehave to convert the resistance value of the probe to a tension between 0 & 5V in order to make it work with the analog pins of the Arduino.

The source of the schematics for the temperature sensor comes from : https://www.instructables.com/id/Reading-Temperature-From-PT100-Using-Arduino/ but instead of using 3 chips LM741, we choose to use the LM324 which consist of 4 operational amplifier on one chip.

You can find the Altium files in the PT100 folder.
