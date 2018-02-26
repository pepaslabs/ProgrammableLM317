EESchema Schematic File Version 2
LIBS:vref_PL
LIBS:analog_ICs_PL
LIBS:capacitors_PL
LIBS:connectors_PL
LIBS:diodes_PL
LIBS:displays_PL
LIBS:inductors_PL
LIBS:LEDs_PL
LIBS:microcontrollers_PL
LIBS:mounting_holes_PL
LIBS:noname-cache
LIBS:opamps
LIBS:opamps_PL
LIBS:opto_PL
LIBS:references_PL
LIBS:regulators_PL
LIBS:relays_PL
LIBS:resistors_PL
LIBS:switches_PL
LIBS:transistors_PL
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "26 feb 2018"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR01
U 1 1 550F905C
P 1500 1850
F 0 "#PWR01" H 1500 1850 30  0001 C CNN
F 1 "GND" H 1500 1780 30  0001 C CNN
F 2 "" H 1500 1850 60  0000 C CNN
F 3 "" H 1500 1850 60  0000 C CNN
	1    1500 1850
	1    0    0    -1  
$EndComp
$Comp
L LM317 U1
U 1 1 550F906F
P 7000 1450
F 0 "U1" H 6800 1610 40  0000 L BNN
F 1 "LM317" H 7200 1280 40  0000 R TNN
F 2 "~" H 7000 1450 60  0000 C CNN
F 3 "~" H 7000 1450 60  0000 C CNN
	1    7000 1450
	1    0    0    -1  
$EndComp
$Comp
L C_EL C1
U 1 1 550F907E
P 1700 1850
F 0 "C1" H 1720 1910 30  0000 L BNN
F 1 "10uF" H 1720 1760 30  0000 L TNN
F 2 "~" H 1738 1700 30  0000 C CNN
F 3 "~" H 1700 1850 60  0000 C CNN
	1    1700 1850
	1    0    0    -1  
$EndComp
Text GLabel 1800 1450 1    60   Input ~ 0
Vcc
Text GLabel 6300 1300 1    60   Input ~ 0
Vcc
$Comp
L LM358 U2
U 1 1 550F91B8
P 8050 4700
F 0 "U2" H 8100 4900 60  0000 C CNN
F 1 "LM358" H 8200 4500 50  0000 C CNN
F 2 "~" H 8050 4700 60  0000 C CNN
F 3 "~" H 8050 4700 60  0000 C CNN
	1    8050 4700
	1    0    0    -1  
$EndComp
$Comp
L R_0W25_1PCT R1
U 1 1 550F91CC
P 8650 5050
F 0 "R1" V 8730 5050 40  0000 C CNN
F 1 "33k" V 8657 5051 40  0000 C CNN
F 2 "~" V 8580 5050 30  0000 C CNN
F 3 "~" H 8650 5050 30  0000 C CNN
	1    8650 5050
	-1   0    0    -1  
$EndComp
$Comp
L R_0W25_1PCT R2
U 1 1 550F91DB
P 8650 5750
F 0 "R2" V 8730 5750 40  0000 C CNN
F 1 "10k" V 8657 5751 40  0000 C CNN
F 2 "~" V 8580 5750 30  0000 C CNN
F 3 "~" H 8650 5750 30  0000 C CNN
	1    8650 5750
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 550F91EA
P 7950 5200
F 0 "#PWR02" H 7950 5200 30  0001 C CNN
F 1 "GND" H 7950 5130 30  0001 C CNN
F 2 "" H 7950 5200 60  0000 C CNN
F 3 "" H 7950 5200 60  0000 C CNN
	1    7950 5200
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 550F9224
P 8650 6100
F 0 "#PWR03" H 8650 6100 30  0001 C CNN
F 1 "GND" H 8650 6030 30  0001 C CNN
F 2 "" H 8650 6100 60  0000 C CNN
F 3 "" H 8650 6100 60  0000 C CNN
	1    8650 6100
	-1   0    0    -1  
$EndComp
$Comp
L C_CER C3
U 1 1 550F9257
P 7750 4100
F 0 "C3" H 7770 4160 30  0000 L BNN
F 1 "0.1uF" H 7770 4040 30  0000 L TNN
F 2 "~" H 7788 3950 30  0000 C CNN
F 3 "~" H 7750 4100 60  0000 C CNN
	1    7750 4100
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 550F9266
P 7750 4400
F 0 "#PWR04" H 7750 4400 30  0001 C CNN
F 1 "GND" H 7750 4330 30  0001 C CNN
F 2 "" H 7750 4400 60  0000 C CNN
F 3 "" H 7750 4400 60  0000 C CNN
	1    7750 4400
	-1   0    0    -1  
$EndComp
Text GLabel 7950 3800 1    60   Input ~ 0
Vcc
$Comp
L GND #PWR05
U 1 1 550F92BB
P 10050 2000
F 0 "#PWR05" H 10050 2000 30  0001 C CNN
F 1 "GND" H 10050 1930 30  0001 C CNN
F 2 "" H 10050 2000 60  0000 C CNN
F 3 "" H 10050 2000 60  0000 C CNN
	1    10050 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 550F92CA
P 1700 2150
F 0 "#PWR06" H 1700 2150 30  0001 C CNN
F 1 "GND" H 1700 2080 30  0001 C CNN
F 2 "" H 1700 2150 60  0000 C CNN
F 3 "" H 1700 2150 60  0000 C CNN
	1    1700 2150
	1    0    0    -1  
$EndComp
$Comp
L ATTINY85-P IC1
U 1 1 550F9657
P 2550 4700
F 0 "IC1" H 1500 5100 60  0000 C CNN
F 1 "ATTINY85-P" H 3400 4300 60  0000 C CNN
F 2 "DIP8" H 1500 4300 60  0001 C CNN
F 3 "~" H 2550 4700 60  0000 C CNN
	1    2550 4700
	-1   0    0    -1  
$EndComp
$Comp
L 7805 U4
U 1 1 550F966D
P 3900 6850
F 0 "U4" H 3700 7010 40  0000 L BNN
F 1 "7805" H 4100 6680 40  0000 R TNN
F 2 "~" H 3900 6850 60  0000 C CNN
F 3 "~" H 3900 6850 60  0000 C CNN
	1    3900 6850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 550F9690
P 4300 7400
F 0 "#PWR07" H 4300 7400 30  0001 C CNN
F 1 "GND" H 4300 7330 30  0001 C CNN
F 2 "" H 4300 7400 60  0000 C CNN
F 3 "" H 4300 7400 60  0000 C CNN
	1    4300 7400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 550F969F
P 3900 7200
F 0 "#PWR08" H 3900 7200 30  0001 C CNN
F 1 "GND" H 3900 7130 30  0001 C CNN
F 2 "" H 3900 7200 60  0000 C CNN
F 3 "" H 3900 7200 60  0000 C CNN
	1    3900 7200
	1    0    0    -1  
$EndComp
Text GLabel 3500 6700 1    60   Input ~ 0
Vcc
Text GLabel 4400 6700 1    60   Input ~ 0
5V
Wire Wire Line
	6300 1400 6700 1400
Wire Wire Line
	7300 1400 9250 1400
Wire Wire Line
	6300 1400 6300 1300
Wire Wire Line
	7950 5100 7950 5200
Wire Wire Line
	8650 4800 8650 4700
Wire Wire Line
	8550 4700 8850 4700
Wire Wire Line
	8650 5300 8650 5500
Wire Wire Line
	8650 6000 8650 6100
Wire Wire Line
	7450 5350 8650 5350
Wire Wire Line
	7450 5350 7450 4800
Wire Wire Line
	7450 4800 7550 4800
Connection ~ 8650 5350
Wire Wire Line
	7750 4400 7750 4300
Wire Wire Line
	7750 3900 7950 3900
Wire Wire Line
	7950 3800 7950 4300
Connection ~ 7950 3900
Wire Wire Line
	7000 1700 7000 2550
Wire Wire Line
	8850 4700 8850 2550
Connection ~ 8650 4700
Wire Wire Line
	4300 7300 4300 7400
Wire Wire Line
	3900 7100 3900 7200
Wire Wire Line
	3500 6800 3600 6800
Wire Wire Line
	3500 6800 3500 6700
Wire Wire Line
	4200 6800 4400 6800
Wire Wire Line
	4300 6800 4300 6900
Wire Wire Line
	4400 6800 4400 6700
Connection ~ 4300 6800
Text GLabel 900  4350 1    60   Input ~ 0
5V
$Comp
L C_CER C7
U 1 1 550F97D7
P 900 4750
F 0 "C7" H 920 4810 30  0000 L BNN
F 1 "0.1uF" H 920 4690 30  0000 L TNN
F 2 "~" H 938 4600 30  0000 C CNN
F 3 "~" H 900 4750 60  0000 C CNN
	1    900  4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	900  4350 900  4550
Wire Wire Line
	1200 4450 900  4450
Connection ~ 900  4450
$Comp
L GND #PWR09
U 1 1 550F9839
P 900 5050
F 0 "#PWR09" H 900 5050 30  0001 C CNN
F 1 "GND" H 900 4980 30  0001 C CNN
F 2 "" H 900 5050 60  0000 C CNN
F 3 "" H 900 5050 60  0000 C CNN
	1    900  5050
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 550F9848
P 1100 5050
F 0 "#PWR010" H 1100 5050 30  0001 C CNN
F 1 "GND" H 1100 4980 30  0001 C CNN
F 2 "" H 1100 5050 60  0000 C CNN
F 3 "" H 1100 5050 60  0000 C CNN
	1    1100 5050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	900  4950 900  5050
Wire Wire Line
	1200 4950 1100 4950
Wire Wire Line
	1100 4950 1100 5050
$Comp
L MCP4801 U3
U 1 1 550F9940
P 5700 4600
F 0 "U3" H 5700 4950 40  0000 L BNN
F 1 "MCP4801" H 5700 4900 40  0000 L BNN
F 2 "DIP8" H 5700 4600 30  0000 C CIN
F 3 "~" H 5700 4600 60  0000 C CNN
	1    5700 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4600 6250 4600
$Comp
L C_CER C4
U 1 1 550F99AE
P 5300 4100
F 0 "C4" H 5320 4160 30  0000 L BNN
F 1 "0.1uF" H 5320 4040 30  0000 L TNN
F 2 "~" H 5338 3950 30  0000 C CNN
F 3 "~" H 5300 4100 60  0000 C CNN
	1    5300 4100
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR011
U 1 1 550F99BD
P 5000 4200
F 0 "#PWR011" H 5000 4200 30  0001 C CNN
F 1 "GND" H 5000 4130 30  0001 C CNN
F 2 "" H 5000 4200 60  0000 C CNN
F 3 "" H 5000 4200 60  0000 C CNN
	1    5000 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5100 4100 5000 4100
Wire Wire Line
	5000 4100 5000 4200
Wire Wire Line
	5500 4100 5600 4100
Wire Wire Line
	5600 4000 5600 4200
Text GLabel 5600 4000 1    60   Input ~ 0
5V
Connection ~ 5600 4100
$Comp
L GND #PWR012
U 1 1 550F9A67
P 5600 5100
F 0 "#PWR012" H 5600 5100 30  0001 C CNN
F 1 "GND" H 5600 5030 30  0001 C CNN
F 2 "" H 5600 5100 60  0000 C CNN
F 3 "" H 5600 5100 60  0000 C CNN
	1    5600 5100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5600 5100 5600 5000
Text GLabel 9250 1300 1    60   Input ~ 0
Vout
Wire Wire Line
	9250 1400 9250 1300
Text GLabel 6000 5000 1    60   Input ~ 0
5V
Wire Wire Line
	5800 5000 5800 5100
Wire Wire Line
	5800 5100 6000 5100
Wire Wire Line
	6000 5100 6000 5000
$Comp
L GND #PWR013
U 1 1 550F9BB4
P 5050 4850
F 0 "#PWR013" H 5050 4850 30  0001 C CNN
F 1 "GND" H 5050 4780 30  0001 C CNN
F 2 "" H 5050 4850 60  0000 C CNN
F 3 "" H 5050 4850 60  0000 C CNN
	1    5050 4850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 4750 5050 4750
Wire Wire Line
	5050 4750 5050 4850
Wire Wire Line
	3900 4450 5150 4450
Wire Wire Line
	3900 4550 5150 4550
Wire Wire Line
	3900 4650 5150 4650
$Comp
L GND #PWR014
U 1 1 550F9D61
P 5600 7300
F 0 "#PWR014" H 5600 7300 30  0001 C CNN
F 1 "GND" H 5600 7230 30  0001 C CNN
F 2 "" H 5600 7300 60  0000 C CNN
F 3 "" H 5600 7300 60  0000 C CNN
	1    5600 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 7300 5600 7200
Wire Wire Line
	5600 7200 5700 7200
Text GLabel 4250 5050 3    60   Input ~ 0
RX
Text GLabel 4100 5050 3    60   Input ~ 0
TX
Wire Wire Line
	3900 4750 4250 4750
Wire Wire Line
	4100 4850 3900 4850
NoConn ~ 3900 4950
Text GLabel 5450 6900 1    60   Input ~ 0
RX
Text GLabel 5250 7000 1    60   Input ~ 0
TX
Wire Wire Line
	5700 7000 5450 7000
Wire Wire Line
	5450 7000 5450 6900
Wire Wire Line
	5700 7100 5250 7100
Wire Wire Line
	5250 7100 5250 7000
$Comp
L CONN_2 P2
U 1 1 550F9EC9
P 10700 1500
F 0 "P2" V 10650 1500 40  0000 C CNN
F 1 "CONN_2" V 10750 1500 40  0000 C CNN
F 2 "" H 10700 1500 60  0000 C CNN
F 3 "" H 10700 1500 60  0000 C CNN
	1    10700 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 550F9ED8
P 10250 1700
F 0 "#PWR015" H 10250 1700 30  0001 C CNN
F 1 "GND" H 10250 1630 30  0001 C CNN
F 2 "" H 10250 1700 60  0000 C CNN
F 3 "" H 10250 1700 60  0000 C CNN
	1    10250 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 1600 10250 1600
Wire Wire Line
	10250 1600 10250 1700
Text GLabel 9950 1300 1    60   Input ~ 0
Vout
Wire Wire Line
	9950 1400 10350 1400
Wire Wire Line
	9950 1400 9950 1300
Wire Wire Line
	4100 4850 4100 5050
Wire Wire Line
	4250 4750 4250 5050
Text Notes 9250 5400 2    60   ~ 0
Gain = 4.3
Text Notes 7500 4550 2    60   ~ 0
0V to 4.096V in 16mV steps
Text Notes 6150 5300 2    60   ~ 0
8-bit DAC in 4.096V mode\n1 LSB = 16mV
Text Notes 9000 4700 1    60   ~ 0
0V to 17.613V in 69mV steps
Text Notes 7650 1350 0    60   ~ 0
1.25V to 18.863V in 69mV steps
Text Notes 4400 5400 2    60   ~ 0
RS-232 (TTL)
$Comp
L CONN_2 P1
U 1 1 55121266
P 1050 1650
F 0 "P1" V 1000 1650 40  0000 C CNN
F 1 "CONN_2" V 1100 1650 40  0000 C CNN
F 2 "" H 1050 1650 60  0000 C CNN
F 3 "" H 1050 1650 60  0000 C CNN
	1    1050 1650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 1750 1500 1750
Wire Wire Line
	1500 1750 1500 1850
Wire Wire Line
	1400 1550 1800 1550
Wire Wire Line
	1800 1550 1800 1450
Wire Wire Line
	1700 1550 1700 1650
$Comp
L HOLE H1
U 1 1 55125DF8
P 9950 6800
F 0 "H1" H 9950 6855 30  0000 C CNN
F 1 "HOLE" H 9950 6740 30  0000 C CNN
F 2 "~" H 9950 6800 60  0000 C CNN
F 3 "~" H 9950 6800 60  0000 C CNN
	1    9950 6800
	1    0    0    -1  
$EndComp
$Comp
L HOLE H3
U 1 1 55125E07
P 10200 6800
F 0 "H3" H 10200 6855 30  0000 C CNN
F 1 "HOLE" H 10200 6740 30  0000 C CNN
F 2 "~" H 10200 6800 60  0000 C CNN
F 3 "~" H 10200 6800 60  0000 C CNN
	1    10200 6800
	1    0    0    -1  
$EndComp
$Comp
L HOLE H2
U 1 1 55125E16
P 9950 7050
F 0 "H2" H 9950 7105 30  0000 C CNN
F 1 "HOLE" H 9950 6990 30  0000 C CNN
F 2 "~" H 9950 7050 60  0000 C CNN
F 3 "~" H 9950 7050 60  0000 C CNN
	1    9950 7050
	1    0    0    -1  
$EndComp
$Comp
L HOLE H4
U 1 1 55125E25
P 10200 7050
F 0 "H4" H 10200 7105 30  0000 C CNN
F 1 "HOLE" H 10200 6990 30  0000 C CNN
F 2 "~" H 10200 7050 60  0000 C CNN
F 3 "~" H 10200 7050 60  0000 C CNN
	1    10200 7050
	1    0    0    -1  
$EndComp
$Comp
L C_CER C8
U 1 1 551262B6
P 6400 1700
F 0 "C8" H 6420 1760 30  0000 L BNN
F 1 "0.1uF" H 6420 1640 30  0000 L TNN
F 2 "~" H 6438 1550 30  0000 C CNN
F 3 "~" H 6400 1700 60  0000 C CNN
	1    6400 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1500 6400 1400
Connection ~ 6400 1400
$Comp
L GND #PWR016
U 1 1 5512631C
P 6400 2000
F 0 "#PWR016" H 6400 2000 30  0001 C CNN
F 1 "GND" H 6400 1930 30  0001 C CNN
F 2 "" H 6400 2000 60  0000 C CNN
F 3 "" H 6400 2000 60  0000 C CNN
	1    6400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1900 6400 2000
$Comp
L C_CER C9
U 1 1 55126430
P 7950 1700
F 0 "C9" H 7970 1760 30  0000 L BNN
F 1 "0.1uF" H 7970 1640 30  0000 L TNN
F 2 "~" H 7988 1550 30  0000 C CNN
F 3 "~" H 7950 1700 60  0000 C CNN
	1    7950 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5512643D
P 7950 2000
F 0 "#PWR017" H 7950 2000 30  0001 C CNN
F 1 "GND" H 7950 1930 30  0001 C CNN
F 2 "" H 7950 2000 60  0000 C CNN
F 3 "" H 7950 2000 60  0000 C CNN
	1    7950 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 1900 7950 2000
Connection ~ 1700 1550
Wire Wire Line
	1700 2050 1700 2150
Wire Wire Line
	10050 1500 10050 1400
Wire Wire Line
	10050 1900 10050 2000
Connection ~ 10050 1400
Text GLabel 1050 6900 1    60   Input ~ 0
5V
$Comp
L LM358 U2
U 2 1 55127368
P 1650 7100
F 0 "U2" H 1700 7300 60  0000 C CNN
F 1 "LM358" H 1800 6900 50  0000 C CNN
F 2 "~" H 1650 7100 60  0000 C CNN
F 3 "~" H 1650 7100 60  0000 C CNN
	2    1650 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 7000 1050 7000
Wire Wire Line
	1050 7000 1050 6900
Wire Wire Line
	2150 7100 2250 7100
Wire Wire Line
	2250 7100 2250 7400
Wire Wire Line
	2250 7400 1050 7400
Wire Wire Line
	1050 7400 1050 7200
Wire Wire Line
	1050 7200 1150 7200
Wire Wire Line
	7950 1500 7950 1400
Connection ~ 7950 1400
$Comp
L R_0W25 R3
U 1 1 5512775D
P 7700 1750
F 0 "R3" V 7780 1750 40  0000 C CNN
F 1 "1.5k" V 7707 1751 40  0000 C CNN
F 2 "~" V 7630 1750 30  0000 C CNN
F 3 "~" H 7700 1750 30  0000 C CNN
	1    7700 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 1500 7700 1400
Connection ~ 7700 1400
Wire Wire Line
	7700 2100 7700 2000
Connection ~ 7000 2100
$Comp
L DIODE D2
U 1 1 55137B87
P 7400 1700
F 0 "D2" H 7400 1800 40  0000 C CNN
F 1 "1N4001" H 7400 1600 40  0000 C CNN
F 2 "~" H 7400 1700 60  0000 C CNN
F 3 "~" H 7400 1700 60  0000 C CNN
	1    7400 1700
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D1
U 1 1 55137B96
P 7000 1050
F 0 "D1" H 7000 1150 40  0000 C CNN
F 1 "1N4001" H 7000 950 40  0000 C CNN
F 2 "~" H 7000 1050 60  0000 C CNN
F 3 "~" H 7000 1050 60  0000 C CNN
	1    7000 1050
	-1   0    0    1   
$EndComp
Text Notes 900  6650 0    60   ~ 0
Terminating the unused op amp
Wire Wire Line
	7400 1500 7400 1400
Connection ~ 7400 1400
Wire Wire Line
	7400 2100 7400 1900
Wire Wire Line
	7200 1050 7450 1050
Wire Wire Line
	7450 1050 7450 1400
Connection ~ 7450 1400
Wire Wire Line
	6800 1050 6650 1050
Wire Wire Line
	6650 1050 6650 1400
Connection ~ 6650 1400
Wire Wire Line
	8850 2550 7000 2550
Wire Wire Line
	7400 2100 7000 2100
$Comp
L GND #PWR018
U 1 1 5A934F13
P 7700 2100
F 0 "#PWR018" H 7700 2100 30  0001 C CNN
F 1 "GND" H 7700 2030 30  0001 C CNN
F 2 "" H 7700 2100 60  0000 C CNN
F 3 "" H 7700 2100 60  0000 C CNN
	1    7700 2100
	1    0    0    -1  
$EndComp
$Comp
L C_CER C2
U 1 1 5A934F22
P 10050 1700
F 0 "C2" H 10070 1760 30  0000 L BNN
F 1 "0.1uF" H 10070 1640 30  0000 L TNN
F 2 "~" H 10088 1550 30  0000 C CNN
F 3 "~" H 10050 1700 60  0000 C CNN
	1    10050 1700
	1    0    0    -1  
$EndComp
$Comp
L C_CER C6
U 1 1 5A934F4E
P 4300 7100
F 0 "C6" H 4320 7160 30  0000 L BNN
F 1 "0.1uF" H 4320 7040 30  0000 L TNN
F 2 "~" H 4338 6950 30  0000 C CNN
F 3 "~" H 4300 7100 60  0000 C CNN
	1    4300 7100
	-1   0    0    -1  
$EndComp
$Comp
L C_CER C10
U 1 1 5A934FBD
P 8200 5700
F 0 "C10" H 8220 5760 30  0000 L BNN
F 1 "10nF" H 8220 5640 30  0000 L TNN
F 2 "~" H 8238 5550 30  0000 C CNN
F 3 "~" H 8200 5700 60  0000 C CNN
	1    8200 5700
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5A934FD8
P 8200 6000
F 0 "#PWR019" H 8200 6000 30  0001 C CNN
F 1 "GND" H 8200 5930 30  0001 C CNN
F 2 "" H 8200 6000 60  0000 C CNN
F 3 "" H 8200 6000 60  0000 C CNN
	1    8200 6000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8200 5900 8200 6000
Wire Wire Line
	8200 5500 8200 5350
Connection ~ 8200 5350
$Comp
L CONN_4 P3
U 1 1 5A9353AC
P 6050 7050
F 0 "P3" V 6000 7050 50  0000 C CNN
F 1 "CONN_4" V 6100 7050 50  0000 C CNN
F 2 "" H 6050 7050 60  0000 C CNN
F 3 "" H 6050 7050 60  0000 C CNN
	1    6050 7050
	1    0    0    -1  
$EndComp
Text GLabel 5650 6750 1    60   Input ~ 0
5V
Wire Wire Line
	5700 6900 5650 6900
Wire Wire Line
	5650 6900 5650 6750
$EndSCHEMATC