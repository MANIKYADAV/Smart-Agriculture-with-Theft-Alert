SMART AGRICULTURE WITH THEFT ALERT

1. Embedded System Proposal:

The Smart Agriculture with Theft Alert is an IoT project that was developed to simplify, and secure agriculture. It has a number of sensors which include DHT11 sensor to sense the temperature and humidity of the environment, a soil moisture sensor to check the amount of water in the soil, a LDR sensor and a PIR (Passive Infrared) sensor to detect any motion in the field at night times. The sensors are used to monitor the environmental factors of the farm as well as offering security against intruders.

The sensors are read by the ST Nucleo F446RE microcontroller which then displays the readings on a display. The Nucleo board communicates with a Raspberry Pi using UART and exchanges data without any problems. In case the PIR sensor detects any movement during night time, the system activates a buzzer in possibilities of any theft attempt.

The smart system gives the farmer real-time information on the temperature, humidity, and soil moisture, thus enabling the user to make decisions regarding watering and crop management. It minimizes manual labor, enhances effective utilization of resources, and enhances security of farm lands.The Smart Agriculture with Theft Alert project embraces the concept of sustainable and modern farming, particularly in remote or unattended agricultural fields.

2. Hardware Design:

The smart agricultural system consists of several components that communicate with each other and monitor the environmental conditions and send security alerts. At the center is the Raspberry Pi that serves as the processing hub. It recieves sensor data and send the approriate output according to the sensor readings, parallely it also displays the soil moisture, Temperarue and Humidity values on a display.

It interacts with the ST Nulceo F446re microcontroller which manages the real-time data collection of sensors such as the soil moisture sensor to measure the moisture in the soil, the DHT11 sensor to measure temperature and humidity, the LDR(Light Dependent Resistor) sensor to measure light intensity and the PIR sensor to detect motion. The PIR motion detection sensor only activates when it is night, which is detected by the LDR sensor. According to the readings of the soil moisture sensor the motor is turned ON/OFF.

To ensure security, it has a buzzer which gives audible signals on theft occurrence during movement. The commands to control motor and buzzer are send to ST Nucleo F446RE through Raspberrypi3. Power supply is regulated and all elements are stable with Raspberry Pi usually operating on 5V.User recieves the alert if any intruder comes near the farm in the night.

Core Components :

1. ST Nucleo F446RE

Acts as the main microcontroller which interprets information from sensors and regulates outputs.

Based on ARM Cortex-M4, with support for analog/digital I/O and UART, SPI, I2C.

Operates at 3.3 V logic and interfaces with Raspberry Pi for data transfer.

Datasheet : http://www.st.com/resource/en/datasheet/stm32f446mc.pdf

2. Raspberry Pi 3B+

Acts as the data processing and visualizations unit.

Comunicates with ST Nucleo F446RE via interface serial UART.

Datasheet : https://datasheets.raspberrypi.com/rpi3/raspberry-pi-3-b-plus-product-brief.pdf

Sensors :

1. DHT11 (Temperature & Humidity) Sensor

Reads ambient temperature and relative humidity.

Drives a single-wire digital output to ST Nucleo F446RE.

Operates on 3.3–5 V with an internal calibrated sensor.

Datasheet : https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf?srsltid=AfmBOoq_l3aHczcNWT-y25AbgbtmrTtVNSn-oBwqP_tIIQQeD4kcuTRT

2. Soil Moisture Sensor

Measures water content in soil with electrical conductivity.

Generates analog output (0–3.3 V) for ST Nucleo F446RE's ADC.

Used to automatically turn on the pump with dry soils.

Datasheet : https://handsontec.com/dataspecs/sensor/Soil%20Moisture%20Sensor.pdf

3. Passive Infrared Sensor (Motion Detection)

Senses infrared changes to detect human or animal motion.

Provides a digital HIGH/LOW output signal.

Operates at 3.3–5 V and drives the warning buzzer.

Datasheet: https://cdn-learn.adafruit.com/downloads/pdf/pir-passive-infrared-proximity-motion-sensor.pdf

4. Light Dependent Resistor (LDR) Sensor

Measures ambient light intensity by changing resistance.

In a voltage divider configuration to obtain an analog output.

Used for day/night light monitoring.

Datasheet : https://components101.com/sites/default/files/component_datasheet/LDR%20Datasheet.pdf

Output Devices:

1. Motor

Turns ON/OFF depending on the soil moisture reading

2. Buzzer

Turns On when PIR motion detection sensor is activated. (Only works during night)

Datasheet : https://www.farnell.com/datasheets/2171929.pdf

Proposal, Block Diagram, and Workflow https://docs.google.com/document/d/1C_-HEMc6-Zq8gDdPgIP90fVfSz_OH6bjkZi7KaPHSH0/edit?tab=t.0Po

3. Embedded Core Implementation and Architecture

Code's main loop (void loop()) now has three distinct, independent decision paths:

Agriculture Monitoring (Based on DHT11 & Soil Moisture) Goal: Maintain optimal growing conditions and water only when necessary. The Flow: The Manager checks the Hydration Checker (Soil Moisture). If the soil is too dry (value below threshold), the Manager commands the pump to turn ON. The Manager also checks the Weather Reporter (DHT11) to log temperature and humidity data for long-term analysis.

Theft Alert (Based on PIR and LDR) Goal: Detect unauthorized movement, but only when it's dark (usually night). The Flow: The Manager checks the Day/Night Switch (LDR). Is it dark? IF it is dark, the Manager checks the Security Watchman (PIR). Is there movement? IF both conditions are met (Dark AND Movement), the Manager triggers the Local Siren (Buzzer). IF it's daytime (LDR value is high), the PIR sensor is ignored to prevent false alarms from wildlife or authorized daytime activity.

Actuators Control (Buzzer and Pump) Goal: Physical outputs based on the two decision paths above. The Flow: Pump is activated by the Soil Moisture reading. Buzzer is activated by the combined PIR and LDR logic

4. Raspbberry pi Setup and Yocto customization

We used UBUNTU and yocto project to build a custom OS for raspberry pi 3. We created a folder named "yocto_labs" to do our project. We cloned the poky repository using the command "git clone git://git.yoctoproject.org/poky" and chosed the "kirkstone" branch. we create a directory named "build-rpi" to add all the bblayers and bake them.

We added the following layer into our "bblayers.conf" file,

meta
meta-poky
meta-yocto-bsp
meta-raspberrypi
meta-openembedded/meta-oe
meta-openembedded/meta-python
meta-openembedded/meta-networking
meta-openembedded/meta-multimedia
In addition to this layers, we created a custom layer named "meta-BKM-5". We used this layer to build interface with the st nucleo F446re board. we created the required files and folders in the layers and wrote a python code to inferface with st nucleo F446Re board and display the data recieved for that board.

Some of the commands we used to build a custom image are,

to create a directory - "mkdir"
to create or edit a file - "nano", "vi"
to check the files in a directory - "ls"
to see the files and folders present in a directory - "tree -L"
to create a custom bb layer - "bitbake-layers create-layer"
to add a bb layer - "bitbake-layers add-layer"
to see the bb layers - "bitbake-layers show-layers"
to bake an image - "bitbake"
to decompress the baked image - "bzip2 -df"
to see the name of the SD card - "lsblk"
to flash the image into the SD card - "sudo dd if= of=/dev/ bs=4M status=progress conv=fsync"
After flashing the image into the raspberry pi 3. we used the following commands to establish the connection between raspberry pi 3 and st nucleo F446Re.

"ls /dev" - the verify that the connection is build or not. If the connection is build "ttyACM0" will be displayed in the list
"minicom -D /dev/ttyACM0 -d 115200" - to establish the connection between the raspberry pi 3 and st nucleo F446Re. the number "115200" is the baud rate we used.
5. Evaluation

The Smart Agriculture with Theft Alert project demonstrates an intelligent and automated approach to the agriculture sector by incorporating three principles environmental surveillance, irrigation control, and security in a single system. The Nucleo F446RE microcontroller and Raspberry Pi 3 are both compatible with each other and the Nucleo is in charge of collecting sensor data in real-time, whereas the Raspberry Pi interprets it, makes the decision, and sends them back to the microcontroller. This arrangement provides quick, efficient and dynamic system performance.

The sensors comprising of soil moisture, temperature, LDR, and PIR collect important environmental data such as humidity of soil, temperature, light intensity, and movement. According to these readings, the system automatically manages such devices as the sensor of a water pump and the buzzer. An example is the pump is activated when the moisture content of the soil reduces below a predetermined point and the buzzer is activated when movement or trespassing is sensed. The communication of the STM32 and the Raspberry Pi is based on the UART, which enables the transfer of data between two systems easily and quickly, which makes the system more responsive.

Experiments indicated that the system is reliable in varied environmental conditions, which gives the correct sensor read and fast response rates. The theft alert system with the PIR sensor added provides an added security to the farmlands especially when they are not monitored or when these are remote. The project is a good example of how embedded systems and IoT can make farming a more efficient and less manual task as well as enhance security.

To sum this up, this prototype meets its objectives due to the provision of the integrated and affordable solution to smart agriculture. It can be extended and modified into a scalable system and sustainable and automated farming methods with additional upgrades, such as data logging, cloud integration, and improved sensor calibration.

REFERENCES:

https://github.coventry.ac.uk/7024ENG-2526SEPNOV/YOCTO-LABS/tree/main
https://www.yoctoproject.org/development/yocto-project-compatible-layers/
https://youtu.be/WWhTKrmEOjU?si=aMcyfGhiATRC3ewc
https://youtu.be/VH4y-wBOCPk?si=CL4peAKHYsVOM4V_
