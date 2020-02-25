EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5E522B8A
P 6250 2600
F 0 "A1" H 6250 1511 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 6250 1420 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6250 2600 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 6250 2600 50  0001 C CNN
	1    6250 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5E53C7E8
P 8450 3250
F 0 "J4" H 8530 3242 50  0000 L CNN
F 1 "LED_strip_WS2801" H 8530 3151 50  0000 L CNN
F 2 "" H 8450 3250 50  0001 C CNN
F 3 "~" H 8450 3250 50  0001 C CNN
	1    8450 3250
	1    0    0    -1  
$EndComp
Text Label 7650 3150 0    50   ~ 0
LED_STRIP_VCC
Text Label 7550 3250 0    50   ~ 0
LED_STRIP_SPI_SI
Text Label 7500 3350 0    50   ~ 0
LED_STRIP_SPI_CLK
Text Label 7650 3450 0    50   ~ 0
LED_STRIP_GND
Text Label 5050 3100 0    50   ~ 0
LED_STRIP_SPI_SI
Text Label 5000 3300 0    50   ~ 0
LED_STRIP_SPI_CLK
NoConn ~ 5750 3200
NoConn ~ 6750 2400
NoConn ~ 6750 2600
NoConn ~ 6750 2700
NoConn ~ 6750 2800
NoConn ~ 6750 2900
NoConn ~ 6750 3000
NoConn ~ 6750 3100
NoConn ~ 6750 3200
NoConn ~ 6750 3300
NoConn ~ 6750 2100
NoConn ~ 6750 2000
NoConn ~ 6350 1600
NoConn ~ 6450 1600
NoConn ~ 6350 3600
Text Label 4650 2200 0    50   ~ 0
FIRST_DRIVE_STEP_CONTROL
Text Label 4550 2400 0    50   ~ 0
SECOND_DRIVE_STEP_CONTROL
Text Label 4850 2300 0    50   ~ 0
FIRST_DRIVE_DIRECTION
Text Label 4750 2500 0    50   ~ 0
SECOND_DRIVE_DIRECTION
NoConn ~ 5750 2000
NoConn ~ 5750 2100
NoConn ~ 5750 2600
NoConn ~ 5750 2700
NoConn ~ 5750 2800
NoConn ~ 5750 2900
NoConn ~ 5750 3000
Wire Wire Line
	5750 2200 4650 2200
Wire Wire Line
	5750 2300 4850 2300
Wire Wire Line
	5750 2400 4550 2400
Wire Wire Line
	5750 2500 4750 2500
Wire Wire Line
	7650 3150 8250 3150
Wire Wire Line
	7550 3250 8250 3250
Wire Wire Line
	7500 3350 8250 3350
Wire Wire Line
	7650 3450 8250 3450
Wire Wire Line
	5050 3100 5750 3100
Wire Wire Line
	5000 3300 5750 3300
Text Label 3500 4150 0    50   ~ 0
FIRST_DRIVE_STEP_CONTROL
Text Label 4850 4150 0    50   ~ 0
FIRST_DRIVE_DIRECTION
Wire Wire Line
	3500 4500 3500 4150
Wire Wire Line
	3600 4500 3600 4200
Wire Wire Line
	3600 4200 4850 4200
Wire Wire Line
	4850 4200 4850 4150
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5E584F49
P 2900 2750
F 0 "J1" H 2818 2967 50  0000 C CNN
F 1 "Power_supply" H 2818 2876 50  0000 C CNN
F 2 "" H 2900 2750 50  0001 C CNN
F 3 "~" H 2900 2750 50  0001 C CNN
	1    2900 2750
	-1   0    0    -1  
$EndComp
Text Label 3350 2750 0    50   ~ 0
5V
Text Label 3350 2850 0    50   ~ 0
GND
Wire Wire Line
	3100 2750 3350 2750
Wire Wire Line
	3100 2850 3350 2850
Text Label 6150 1500 0    50   ~ 0
5V
Wire Wire Line
	6150 1500 6150 1600
Text Label 6100 3600 2    50   ~ 0
GND
Wire Wire Line
	6100 3600 6250 3600
Text Label 7450 4250 0    50   ~ 0
SECOND_DRIVE_STEP_CONTROL
Text Label 8800 4250 0    50   ~ 0
SECOND_DRIVE_DIRECTION
Wire Wire Line
	7450 4600 7450 4250
Wire Wire Line
	7550 4600 7550 4300
Wire Wire Line
	7550 4300 8800 4300
Wire Wire Line
	8800 4300 8800 4250
Text Label 3200 4150 0    50   ~ 0
GND
Text Label 7150 4250 0    50   ~ 0
GND
Wire Wire Line
	3200 4150 3200 4500
Wire Wire Line
	7150 4250 7150 4600
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5E54D784
P 2700 5350
F 0 "J5" H 2780 5342 50  0000 L CNN
F 1 "Left_floppy_drive_power" H 2780 5251 50  0000 L CNN
F 2 "" H 2700 5350 50  0001 C CNN
F 3 "~" H 2700 5350 50  0001 C CNN
	1    2700 5350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J6
U 1 1 5E54F1BD
P 6650 5350
F 0 "J6" H 6730 5342 50  0000 L CNN
F 1 "Right_floppy_drive_power" H 6730 5251 50  0000 L CNN
F 2 "" H 6650 5350 50  0001 C CNN
F 3 "~" H 6650 5350 50  0001 C CNN
	1    6650 5350
	1    0    0    -1  
$EndComp
Text Label 2250 5550 0    50   ~ 0
5V
Text Label 2250 5450 0    50   ~ 0
GND
NoConn ~ 6500 5250
NoConn ~ 6500 5350
NoConn ~ 2500 5250
NoConn ~ 2500 5350
Wire Wire Line
	2250 5450 2500 5450
Wire Wire Line
	2250 5550 2500 5550
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J2
U 1 1 5E55A838
P 3600 4800
F 0 "J2" V 3696 5780 50  0000 L CNN
F 1 "Left_floppy_drive" V 3605 5780 50  0000 L CNN
F 2 "" H 3600 4800 50  0001 C CNN
F 3 "~" H 3600 4800 50  0001 C CNN
	1    3600 4800
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J3
U 1 1 5E566A8F
P 7550 4900
F 0 "J3" V 7646 5879 50  0000 L CNN
F 1 "Right_floppy_drive" V 7555 5879 50  0000 L CNN
F 2 "" H 7550 4900 50  0001 C CNN
F 3 "~" H 7550 4900 50  0001 C CNN
	1    7550 4900
	0    -1   -1   0   
$EndComp
Text Label 6200 5550 0    50   ~ 0
5V
Text Label 6200 5450 0    50   ~ 0
GND
Wire Wire Line
	6200 5450 6450 5450
Wire Wire Line
	6200 5550 6450 5550
$EndSCHEMATC
