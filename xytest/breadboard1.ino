
void setup(){
    m.init(); // module MAX7219
    m.setIntensity(5); // LED Intensity 0-15
    printStringWithShift(string1, 100);  // Send scrolling Text
}
void loop(){
    byte c;
    delay(100);
    m.shiftLeft(false, true);
    printStringWithShiftRev(string1, 100);  // Send scrolling Text
}
