#include <stdint.h>
#include <SoftwareSerial.h> //Using the preset Arduino Software Serial library to read and write from the RFID module
SoftwareSerial mySerial(2, 3); //pin2 Rx, pin3 Tx 

#include "RFID_R200.h" // Using cmd struct header file
#include "Cards_EPC_List.h" // Using EPC struct header file
#include "74HC595.h" // Using 74HC595 header file

void setup() { 

    Serial.begin(115200);
    pinMode(data,OUTPUT); // Setup the data pin as output
    pinMode(clock, OUTPUT); // Setup the clock pin as output
    pinMode(latch, OUTPUT); // Setup the latch pin as output

    mySerial.listen(); // Setup receiver on RFID module
    Serial.println("Reading out put is printed here, please refers to the specific module manual to check the output reference:\n"); 
    mySerial.begin(115200); // RFID R200 is manually set to 115200 baud rate, to match with the setting, we use 115200 here
    delay(10);
    SerialSendCmd(maximum -> settingCmd, maximum -> settingCmdDec, maximum -> size); // setup the module to maximum receiving range
    delay(10);
    
} 

void loop() { 

    SerialSendCmd(cmd -> readCmd, cmd -> readCmdDec, cmd -> size); // Calls to the function to send and receive messages from the module
    delay(50); // Time break between each read
    updateLEDs(0b00000000); // close all the leds 
    leds=0b0; // led memory, refresh on every loop to clear previous lightened leds memory
}

/*
 * function SerialReadHexDigit()
 * 
 * operation: converts Hex digit to Decimal number
 * returns: return -1 if the input is not a Hex number; therefore, can not be written as a decimal digit.
 */
int SerialReadHexDigit(){

    byte c = (byte) Serial.read(); // read the Hex input from the user
    if (c >= '0' && c <= '9') {
        return c - '0'; // // calculate the corresponding decimal number by subtraction the char '0' in the ASCII table.
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10; // calculate the corresponding decimal number by subtraction the char 'A' in the ASCII table, adding 10 to match the hex digit rule
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10; // calculate the corresponding decimal number by subtraction the char 'A' in the ASCII table, adding 10 to match the hex digit rule
    } else {
        return -1;   // Returns -1 when the chracter is not able to convert from hex to decimal 
    }
}

/*
 * function SerialConvertHex2DecCmd()
 * 
 * operation: converts 8 bit Hex digit to Decimal number and store them in an int array
 */
void SerialConvertHex2DecCmd(unsigned char *cmdHex, int *cmdDec, int size){

    for (int i = 0; i < size; i++){
        *(cmdDec + i) = (int) *(cmdHex + i); // convert 8 bit command to decimal format.
    }
}

/*
 * function SerialSendCmd()
 * 
 * operation: converts 8 bit Hex digits to Decimal number and store them in an int array
 */
void SerialSendCmd(unsigned char *cmdHex, int *cmdDec, int size){

    SerialConvertHex2DecCmd(cmdHex, cmdDec, size); // Calls to the function to convert 8 bit Hex digits to Decimal number and store them in an int array

    for (int i = 0; i < size; i++){ 
        mySerial.write(*(cmdDec + i)); // Iterate through the int array to send decimal command to the module.
    }
    
    uint8_t i = 0; // tracking the index of the response byte from the module
    int sum = 0; // sum of the previous hex number for verification before the ending digit
    uint8_t checksum = -1; // checksum byte for verification of \n character
    unsigned char outputEPC[12]; // output EPC number store in array
    int printFlag = 0; //println flag

    while (mySerial.available()) {
        uint8_t c = printResponse(); // Print the response from the module
        
        if (i > 0 && i < 22){ // formatting serial println output 
            sum += (int) c;
            sum %= 256;
        }

        if (i == 22){ // formatting serial println output 
            sum %= 256;
            checksum = c;
        }

        if (i > 7 && i < 20){
            detectEPC(c, outputEPC + i - 8); // If the the current byte index is within the EPC number range, copy the epc number to the array
        }

        i++; // increase the index of response byte from the module
        
        if (c == 0x7E && sum == checksum){ // formatting serial println output 
          Serial.println();
          printFlag = 1;
          break;
        }
    }  // end printing & writing

    if (newLineFlag > 0 && printFlag == 0) {
        Serial.println(); // print a \n character when flag is true
        newLineFlag = 0; // reset the flag for the next input detection
    }

    for (uint16_t i = 0; i < epcListSize; i++){
        int ledFlag = 1; // set ledflag
        for (uint16_t j = 0; j < 12; j++){
            if((*(outputEPC + j)) != *(((epcList + i) -> epc) + j)){ 
                ledFlag = 0; // do not turn on the number i led when EPC does not match
                break;
            }
        }

        if (ledFlag){
                changeLED(i, on); // turn on the number i led when the EPC matches
        }
    }
}

/*
 * function updateLEDs(byte value)
 * parameter: byte 
 * operation: display the targeted leds by entering an 8 bits binary value 
 */
void updateLEDs(byte value){

    digitalWrite(latch, LOW); // Close the latch
    shiftOut(data, clock, LSBFIRST, value); // Shift the parameter bits and display the leds
    digitalWrite(latch, HIGH); // Open the latch
}

/*
 * function updateLEDs(int led, int state)
 * parameter: int, state
 * operation: display the targeted leds by entering the corresponding led and the state
 */

void changeLED(int led, int state)
{
  leds = leds & mask[led];
  if(state == on) {
    leds = leds | bits[led];
    updateLEDs(leds);
  }
}

/*
 * function printResponse()
 * 
 * operation: print the response from the RFID module in HEX format in the Serial monitor
 * returns: a byte number of a range (0 - 255)
 */
uint8_t printResponse() {

    byte Char = mySerial.read(); // Read the decimal response from RFID module (0 - 255)

    if (Char < 16) {
        Serial.print("0"); // Adding leading 0 to hex number < 16
    }

    Serial.print(Char, HEX); //Display the Serial Number in HEX 
    Serial.print(" "); 
    newLineFlag = 1; // If something is printed, then set the flag to true

    return Char;
}

/*
 * function detectEPC(byte c, unsigned char *epc)
 * parameter: byte, unsigned char
 * operation: append the EPC byte value to an array
 */
void detectEPC(byte c, unsigned char *epc) {

    *epc = c; // insert the EPC into the array
}



