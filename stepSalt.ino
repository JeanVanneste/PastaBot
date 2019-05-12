void dispenseSalt() {
    saltDispenser.write(179);
    delay(500);
    saltDispenser.write(1);  
    delay(500);
}
