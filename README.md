# Health Monitoring and Alert System 
## Overview

The Health Monitoring and Alert System is our B.Tech final-year project developed to monitor a patient's vital health parameters in real time. The system continuously acquires physiological data using biomedical sensors and transmits it to the Ubidots Cloud Platform (https://ubidots.com/) through an ESP32 module.

Ubidots stores the collected health data, provides real-time visualization using dashboards and graphs, and maintains historical records for continuous health monitoring.

To ensure timely medical attention, threshold values are configured on the Ubidots platform. Whenever any monitored health parameter exceeds the predefined safe limits, the system automatically sends instant alert notifications to the doctor and the patient's family members via SMS and email, enabling a quick response during medical emergencies.

### Features
- Real-time health monitoring
- Cloud-based data storage using Ubidots
- Live graphical visualization of health parameters
- Automatic SMS and email alerts during critical conditions
- Historical data logging and analysis
- IoT-based remote patient monitoring
### Hardware Components
- ESP32 Development Board
- MAX30100 Pulse Oximeter & Heart Rate Sensor
- AD8232 ECG Sensor
- 16×2 I2C LCD Display
- I2C LCD Adapter
- Connecting Wires and Power Supply
### Software & Technologies
- Arduino IDE
- Embedded C/C++
- ESP32
- Ubidots IoT Cloud Platform
### Related Links
- [Ubidots](http://ubidots.com/)
- [Watch Demo Video](https://youtu.be/5pQjY5jsUyM?si=VHTLJgd7-fDKWE2M)