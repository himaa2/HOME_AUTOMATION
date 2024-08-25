Home Automation System via Bluetooth
This project implements a basic home automation system that allows users to control a safety door and lights via a mobile phone application using Bluetooth. The system supports multiple users with different usernames and passwords, and includes an alarm feature that is triggered after multiple failed login attempts.

Features
1. Safety Door Control
Users can open the safety door by entering a username and password via the mobile application.
The system supports up to 10 users, each with a unique username and password.
If a user enters the wrong password three times in a row, the system triggers an alarm to prevent unauthorized access.
2. Light Control
Users can control the lights (on/off) through the mobile application.
The user is prompted to turn on or off the light after successfully opening the door.
3. Security Alarm
If a user fails to enter the correct password three times, a buzzer alarm is triggered for 10 seconds.
Hardware Requirements
Microcontroller: ATMEGA32
Bluetooth Module: For communication with the mobile application
EEPROM: To store predefined usernames and passwords
Solenoid: To control the safety door
LED: To represent the light control feature
Buzzer: To serve as the alarm in case of unauthorized access attempts
Software Requirements
Programming Language: C
AVR Libraries: For controlling peripherals (UART, EEPROM, GPIO, Timer)
Mobile Application: A basic mobile app or serial Bluetooth terminal app to communicate with the microcontroller via Bluetooth
Setup
Hardware Setup:

Connect the ATMEGA32 microcontroller to the Bluetooth module, LED, Solenoid, and Buzzer.
Ensure that EEPROM is properly wired and configured to store the predefined passwords.
The system uses a 5-second delay to keep the solenoid (door) open before automatically closing it.
Software Setup:

Flash the provided C code to the ATMEGA32 microcontroller using an AVR programmer.
Ensure that the mobile application is set up to send and receive data via Bluetooth.
Predefined Users and Passwords
The system supports up to 10 users with the following predefined usernames and passwords:

User ID	Password
1  -->	 1234
2  -->	 2345
3  -->	 3456
4  -->	 4567
5  -->	 5678
6  -->	 6789
7  -->	 7890
8  -->	 8901
9  -->	 9012
10 -->   0123
How It Works
User Login:

The system prompts the user to enter their User ID (1-10) via the mobile application.
The user is then asked to input their password. The system checks this against the stored password in EEPROM.
If the password is correct, the door solenoid is activated, allowing the door to open for 5 seconds.
After entering the correct password, the user is asked if they would like to control the lights (LED) as well.
Failed Attempts:

If the password is entered incorrectly three times, the system triggers a buzzer alarm for 10 seconds.
Future Enhancements
Implement dynamic user management to allow adding or modifying users via the mobile application.
Expand the system to control additional home appliances via the mobile app.
Add encryption for secure transmission of usernames and passwords over Bluetooth.
Contributing
Contributions are welcome! If you have ideas for improvements or find any issues, please open a pull request or issue on GitHub.
