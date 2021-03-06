###package data

## 100 pin package data, PIC24FJXXXGA110
## PIC24FJ128GA110
## PIC24FJ192GA110
## PIC24FJ256GA110

## the following have no remappable pins, and fewer CN pins
## PIC24FJ64GA010
## PIC24FJ96GA010
## PIC24FJ128GA010

@digio_100pin_F_GA = (
 "RA0",
 "RA1",
 "RA2",
 "RA3",
 "RA4",
 "RA5",
 "RA6",
 "RA7",
 "RA9",
 "RA10",
 "RA14",
 "RA15",
 "RB0",
 "RB1",
 "RB2",
 "RB3",
 "RB4",
 "RB5",
 "RB6",
 "RB7",
 "RB8",
 "RB9",
 "RB10",
 "RB11",
 "RB12",
 "RB13",
 "RB14",
 "RB15",
 "RC1",
 "RC2",
 "RC3",
 "RC4",
 "RC12",
 "RC13",
 "RC14",
 "RC15",
 "RD0",
 "RD1",
 "RD2",
 "RD3",
 "RD4",
 "RD5",
 "RD6",
 "RD7",
 "RD8",
 "RD9",
 "RD10",
 "RD11",
 "RD12",
 "RD13",
 "RD14",
 "RD15",
 "RE0",
 "RE1",
 "RE2",
 "RE3",
 "RE4",
 "RE5",
 "RE6",
 "RE7",
 "RE8",
 "RE9",
 "RF0",
 "RF1",
 "RF2",
 "RF3",
 "RF4",
 "RF5",
 "RF6",
 "RF7",
 "RF8",
 "RF12",
 "RF13",
 "RG0",
 "RG1",
 "RG2",
 "RG3",
 "RG6",
 "RG7",
 "RG8",
 "RG9",
 "RG12",
 "RG13",
 "RG14",
 "RG15"
);


%pullups_100pin_F_GA = (
"RA0"=> "_CN33",
 "RA1"=> "_CN34",
 "RA2"=> "_CN35",
 "RA3"=> "_CN36",
 "RA4"=> "_CN37",
 "RA5"=> "_CN38",
 "RA6"=> "_CN39",
 "RA7"=> "_CN40",
 "RA9"=> "_CN41",
 "RA10"=> "_CN42",
 "RA14"=> "_CN43",
 "RA15"=> "_CN44",
"RB0"=> "_CN2",
 "RB1"=> "_CN3",
 "RB2"=> "_CN4",
 "RB3"=> "_CN5",
 "RB4"=> "_CN6",
 "RB5"=> "_CN7",
 "RB6"=> "_CN24",
 "RB7"=> "_CN25",
 "RB8"=> "_CN26",
 "RB9"=> "_CN27",
 "RB10"=> "_CN28",
 "RB11"=> "_CN29",
 "RB12"=> "_CN30",
 "RB13"=> "_CN31",
 "RB14"=> "_CN32",
 "RB15"=> "_CN12",
 "RC1"=> "_CN45",
 "RC2"=> "_CN46",
 "RC3"=> "_CN47",
 "RC4"=> "_CN48",
 "RC12"=> "_CN23",
 "RC13"=> "_CN1",
 "RC14"=> "_CN0",
 "RC15"=> "_CN22",
 "RD0"=> "_CN49",
 "RD1"=> "_CN50",
 "RD2"=> "_CN51",
 "RD3"=> "_CN52",
 "RD4"=> "_CN13",
 "RD5"=> "_CN14",
 "RD6"=> "_CN15",
 "RD7"=> "_CN16",
 "RD8"=> "_CN53",
 "RD9"=> "_CN54",
 "RD10"=> "_CN55",
 "RD11"=> "_CN56",
 "RD12"=> "_CN57",
 "RD13"=> "_CN19",
 "RD14"=> "_CN20",
 "RD15"=> "_CN21",
 "RE0"=> "_CN58",
 "RE1"=> "_CN59",
 "RE2"=> "_CN60",
 "RE3"=> "_CN61",
 "RE4"=> "_CN62",
 "RE5"=> "_CN63",
 "RE6"=> "_CN64",
 "RE7"=> "_CN65",
 "RE8"=> "_CN66",
 "RE9"=> "_CN67",
 "RF0"=> "_CN68",
 "RF1"=> "_CN69",
 "RF2"=> "_CN70",
 "RF3"=> "_CN71",
 "RF4"=> "_CN17",
 "RF5"=> "_CN18",
 "RF6"=> "_CN72", 
 "RF7"=> "_CN73",
 "RF8"=> "_CN74",
 "RF12"=> "_CN75",
 "RF13"=> "_CN76",
 "RG0"=> "_CN77",
 "RG1"=> "_CN78",
 "RG2"=> "_CN83",
 "RG3"=> "_CN84",
 "RG6"=> "_CN8",
 "RG7"=> "_CN9",
 "RG8"=> "_CN10",
 "RG9"=> "_CN11",
 "RG12"=> "_CN79",
 "RG13"=> "_CN80",
 "RG14"=> "_CN81",
 "RG15"=> "_CN82",
   );
  
 
 %opendrain_100pin_F_GA = (
 "RA0"=> "_ODA0",
 "RA1"=> "_ODA1",
 "RA2"=> "_ODA2",
 "RA3"=> "_ODA3",
 "RA4"=> "_ODA4",
 "RA5"=> "_ODA5",
 "RA6"=> "_ODA6",
 "RA7"=> "_ODA7",
 "RA9"=> "_ODA9",
 "RA10"=> "_ODA10",
 "RA14"=> "_ODA14",
 "RA15"=> "_ODA15",
"RB0"=> "_ODB0",
 "RB1"=> "_ODB1",
 "RB2"=> "_ODB2",
 "RB3"=> "_ODB3",
 "RB4"=> "_ODB4",
 "RB5"=> "_ODB5",
 "RB6"=> "_ODB6",
 "RB7"=> "_ODB7",
 "RB8"=> "_ODB8",
 "RB9"=> "_ODB9",
 "RB10"=> "_ODB10",
 "RB11"=> "_ODB11",
 "RB12"=> "_ODB12",
 "RB13"=> "_ODB13",
 "RB14"=> "_ODB14",
 "RB15"=> "_ODB15",
 "RC1"=>  "_ODC1",
 "RC2"=>  "_ODC2",
 "RC3"=>  "_ODC3",
 "RC4"=>  "_ODC4",
 "RC12"=>  "_ODC12",
 "RC13"=>  "_ODC13",
 "RC14"=> "_ODC14", 
 "RC15"=> "_ODC15",
 "RD0"=> "_ODD0",
 "RD1"=> "_ODD1",
 "RD2"=> "_ODD2",
 "RD3"=> "_ODD3",
 "RD4"=> "_ODD4",
 "RD5"=> "_ODD5",
 "RD6"=> "_ODD6",
 "RD7"=> "_ODD7",
 "RD8"=> "_ODD8",
 "RD9"=> "_ODD9",
 "RD10"=> "_ODD10",
 "RD11"=> "_ODD11",
 "RD12"=> "_ODD12",
 "RD13"=> "_ODD13",
 "RD14"=> "_ODD14",
 "RD15"=> "_ODD15", 
 "RE0"=> "_ODE0",
 "RE1"=> "_ODE1",
 "RE2"=> "_ODE2",
 "RE3"=> "_ODE3",
 "RE4"=> "_ODE4",
 "RE5"=> "_ODE5",
 "RE6"=> "_ODE6",
 "RE7"=> "_ODE7",
 "RE8"=> "_ODE8",
 "RE9"=> "_ODE9",
 "RF0"=> "_ODF0",
 "RF1"=> "_ODF1",
 "RF2"=> "_ODF2",
 "RF3"=> "_ODF3",
 "RF4"=> "_ODF4",
 "RF5"=> "_ODF5",
 "RF6"=> "_ODF6",
 "RF7"=> "_ODF7", 
 "RF8"=> "_ODF8",  
 "RF12"=> "_ODF12", 
 "RF13"=> "_ODF13", 
 "RG0"=> "_ODG0",
 "RG1"=> "_ODG1",
 "RG2"=> "_ODG2",
 "RG3"=> "_ODG3",
 "RG6"=> "_ODG6",
 "RG7"=> "_ODG7",
 "RG8"=> "_ODG8",
 "RG9"=> "_ODG9", 
 "RG12"=> "_ODG12",
"RG13"=> "_ODG13", 
"RG14"=> "_ODG14", 
"RG15"=> "_ODG15",  
   );

   
  %analog_100pin_F_GA = (  
 "RB0"=> "_PCFG0",
"RB1"=> "_PCFG1",
"RB2"=> "_PCFG2",
"RB3"=> "_PCFG3",
"RB4"=> "_PCFG4",
"RB5"=> "_PCFG5",
"RB6"=> "_PCFG6",
"RB7"=> "_PCFG7",
"RB8"=> "_PCFG8",
"RB9"=> "_PCFG9",
"RB10"=> "_PCFG10",
"RB11"=> "_PCFG11",
"RB12"=> "_PCFG12",
"RB13"=> "_PCFG13",
"RB14"=> "_PCFG14",
"RB15"=> "_PCFG15",
   );
   
   
  %RPanalog_100pin_F_GA = (  
  0 => "_PCFG0",
  1 => "_PCFG1",
13 => "_PCFG2",
28 => "_PCFG4",
18 => "_PCFG5",
6  => "_PCFG6",
7  => "_PCFG7",
8  => "_PCFG8",
9  => "_PCFG9",
14 => "_PCFG14",
29 => "_PCFG15",
);

%RPanalog_100pin_F_GA0 = ( );

 
   %pullups_100pin_F_GA0 = (
 "RB0"=> "_CN2",
 "RB1"=> "_CN3",
 "RB2"=> "_CN4",
 "RB3"=> "_CN5",
 "RB4"=> "_CN6",
 "RB5"=> "_CN7",
 "RB15"=> "_CN12",
 "RC13"=> "_CN1",
 "RC14"=> "_CN0",
 "RD4"=> "_CN13",
 "RD5"=> "_CN14",
 "RD6"=> "_CN15",
 "RD7"=> "_CN16",
 "RD13"=> "_CN19",
 "RD14"=> "_CN20",
 "RD15"=> "_CN21",
 "RF4"=> "_CN17",
 "RF5"=> "_CN18",
 "RG6"=> "_CN8",
 "RG7"=> "_CN9",
 "RG8"=> "_CN10",
 "RG9"=> "_CN11",
  );
 
   
  
  1;
  
  
   
