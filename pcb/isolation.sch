EESchema Schematic File Version 2
LIBS:diode-1
LIBS:rcl
LIBS:transistor
LIBS:power
LIBS:connect
LIBS:linear_pmic
LIBS:led
LIBS:isopower
LIBS:device
LIBS:monitor-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date "9 feb 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 1600 3550 0    60   ~ 0
Screw terminal
Text Label 5300 3950 0    60   ~ 0
CSBI
Text Label 5300 4250 0    60   ~ 0
SDO
Text Label 5300 4150 0    60   ~ 0
SDI
Text Label 5300 4050 0    60   ~ 0
SCKI
Wire Wire Line
	4950 3950 5700 3950
Wire Wire Line
	4950 4050 5700 4050
Wire Wire Line
	4950 4150 5700 4150
$Comp
L ADUM5401 U401
U 1 1 52F6598A
P 4200 4100
F 0 "U401" H 4200 4200 60  0000 C CNN
F 1 "ADUM5401" H 4200 4000 60  0000 C CNN
F 2 "" H 4200 4100 60  0000 C CNN
F 3 "" H 4200 4100 60  0000 C CNN
	1    4200 4100
	1    0    0    -1  
$EndComp
$Comp
L C-EUC0805 C401
U 1 1 52F659E9
P 2550 4800
F 0 "C401" H 2610 4815 50  0000 L BNN
F 1 "10u" H 2610 4615 50  0000 L BNN
F 2 "rcl-C0805" H 2550 4950 50  0001 C CNN
F 3 "" H 2550 4800 60  0000 C CNN
	1    2550 4800
	1    0    0    -1  
$EndComp
$Comp
L C-EUC0805 C402
U 1 1 52F659FD
P 3200 4800
F 0 "C402" H 3260 4815 50  0000 L BNN
F 1 "100n" H 3260 4615 50  0000 L BNN
F 2 "rcl-C0805" H 3200 4950 50  0001 C CNN
F 3 "" H 3200 4800 60  0000 C CNN
	1    3200 4800
	1    0    0    -1  
$EndComp
$Comp
L C-EUC0805 C403
U 1 1 52F65A19
P 5400 4800
F 0 "C403" H 5460 4815 50  0000 L BNN
F 1 "10u" H 5460 4615 50  0000 L BNN
F 2 "rcl-C0805" H 5400 4950 50  0001 C CNN
F 3 "" H 5400 4800 60  0000 C CNN
	1    5400 4800
	1    0    0    -1  
$EndComp
$Comp
L C-EUC0805 C404
U 1 1 52F65A1F
P 6050 4800
F 0 "C404" H 6110 4815 50  0000 L BNN
F 1 "100n" H 6110 4615 50  0000 L BNN
F 2 "rcl-C0805" H 6050 4950 50  0001 C CNN
F 3 "" H 6050 4800 60  0000 C CNN
	1    6050 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3750 3450 3750
Wire Wire Line
	2600 4300 2600 4450
Wire Wire Line
	2600 4450 3450 4450
Wire Wire Line
	2600 4200 2700 4200
Wire Wire Line
	2700 4200 2700 4250
Wire Wire Line
	2700 4250 3450 4250
Wire Wire Line
	2600 4100 2800 4100
Wire Wire Line
	2800 4100 2800 4150
Wire Wire Line
	2600 4000 3100 4000
Wire Wire Line
	3100 4000 3100 4050
Wire Wire Line
	3100 4050 3450 4050
Wire Wire Line
	2600 3900 3150 3900
Wire Wire Line
	3150 3900 3150 3950
Wire Wire Line
	3150 3950 3450 3950
Wire Wire Line
	3450 3850 3350 3850
Wire Wire Line
	3350 3850 3350 4450
Connection ~ 3350 4450
Wire Wire Line
	4950 4250 5700 4250
Wire Wire Line
	4950 3750 5700 3750
Wire Wire Line
	4950 3850 5050 3850
Wire Wire Line
	4950 4450 5700 4450
Connection ~ 5050 4450
$Comp
L 1N4004 D401
U 1 1 52F65BB0
P 1950 4850
F 0 "D401" V 2000 4650 50  0000 L BNN
F 1 "1N4004" V 1900 4450 50  0000 L BNN
F 2 "diode-1-DO41-10" H 1950 5000 50  0001 C CNN
F 3 "" H 1950 4850 60  0000 C CNN
	1    1950 4850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1850 5000 3200 5000
Wire Wire Line
	1850 5000 1850 5050
Connection ~ 2550 5000
Wire Wire Line
	1950 4950 1950 5000
Connection ~ 1950 5000
Wire Wire Line
	1850 4700 3200 4700
Wire Wire Line
	1950 4700 1950 4750
Connection ~ 2550 4700
Connection ~ 1950 4700
Wire Wire Line
	5050 4700 6050 4700
Wire Wire Line
	5050 5000 6050 5000
Text Notes 5750 5200 0    60   ~ 0
Max 2 mm from \npins 16 and 15
Text Notes 2900 5250 0    60   ~ 0
Max 2 mm from \npins 1 and 2
Wire Wire Line
	4950 4350 5150 4350
Wire Wire Line
	5150 4350 5150 3750
Connection ~ 5150 3750
Text HLabel 5700 3750 2    60   Output ~ 0
5V
Text HLabel 5700 3950 2    60   Output ~ 0
CSBI
Text HLabel 5700 4150 2    60   Output ~ 0
SDI
Text HLabel 5700 4050 2    60   Output ~ 0
SCKI
Text HLabel 5700 4250 2    60   Input ~ 0
SDO
Text Label 1850 4700 2    60   ~ 0
Vin
Text Label 3100 4450 2    60   ~ 0
GND1
Text Label 1850 5050 2    60   ~ 0
GND1
Text Label 5300 3750 2    60   ~ 0
5V
Text Label 5350 4450 2    60   ~ 0
GND2
Wire Wire Line
	5050 3850 5050 4450
Connection ~ 5400 4700
Connection ~ 5400 5000
Text Label 5050 4700 2    60   ~ 0
5V
Text Label 5050 5000 2    60   ~ 0
GND2
Text HLabel 5700 4450 2    60   Input ~ 0
GND
Wire Wire Line
	2600 3800 2600 3750
Wire Wire Line
	2800 4150 3450 4150
Text Label 2900 3750 0    60   ~ 0
Vin
Text Label 2900 3900 0    60   ~ 0
CS
Text Label 2900 4250 0    60   ~ 0
MISO
Text Label 2900 4150 0    60   ~ 0
MOSI
Text Label 2900 4000 0    60   ~ 0
SCL
$Comp
L CONNECT_6 K401
U 1 1 52FFF847
P 2300 4050
F 0 "K401" H 2300 4250 60  0000 C CNN
F 1 "CONNECT_6" H 2300 4350 60  0000 C CNN
F 2 "" H 2250 4050 60  0000 C CNN
F 3 "" H 2250 4050 60  0000 C CNN
	1    2300 4050
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
