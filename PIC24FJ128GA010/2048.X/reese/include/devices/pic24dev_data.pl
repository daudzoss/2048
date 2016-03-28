

require "pkg18pin.pl";
require "pkg28pin.pl";
require "pkg44pin.pl";
require "pkg64pin.pl";
require "pkg64pinF_GA.pl";
require "pkg64pinF_GB.pl";
require "pkg100pin.pl";
require "pkg100pinF_GA.pl";
require "pkg100pinF_GB.pl";
require "pkg80pinF_GA.pl";
require "pkg80pinF_GB.pl";


@pic24_devices = (
 ##PIC24 Devices
 ## 18-pin devices, variant 1
 ["pic24hj12gp201",\@digio_18pin_1, \%pullups_18pin_1, \%opendrain_18pin_24H_1,\%analog_18pin_1,\%RPanalog_18pin_1],
 ##28-pin devices, variant 1
["pic24hj32gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24hj32gp302",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24hj64gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24hj64gp502",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24hj128gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24hj128gp502",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_1,\%RPanalog_28pin_1],

## 28-pin devices, variant 2
["pic24hj12gp202",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24H_1,\%analog_28pin_2,\%RPanalog_28pin_2],
##44-pin devices, variant 1
["pic24hj16gp304",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24hj32gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24hj32gp304",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24hj64gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24hj64gp504",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24hj128gp204",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24hj128gp504",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24H_1,\%analog_44pin_1,\%RPanalog_44pin_1],
##64-pin devices, variant 1
["pic24hj64gp206",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1],
["pic24hj128gp206",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1],
["pic24hj256gp206",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1],
["pic24hj128gp306",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1],
["pic24hj64gp506",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1],
["pic24hj128gp506",\@digio_64pin_1, \%pullups_64pin_1, \%opendrain_64pin_24H_1,\%analog_64pin_1,\%RPanalog_64pin_1],
##100-pin devices, variant 1
["pic24hj64gp210",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
["pic24hj128gp210",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
["pic24hj128gp310",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
["pic24hj256gp210",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
["pic24hj64gp510",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
["pic24hj128gp510",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
["pic24hj256gp610",\@digio_100pin_1, \%pullups_100pin_1, \%opendrain_100pin_24H_1,\%analog_100pin_1,\%RPanalog_100pin_1],
##PIC24F Devices
##28-pin devices, variant 1
["pic24fj16ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24fj32ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24fj48ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1],
["pic24fj64ga002",\@digio_28pin_1, \%pullups_28pin_1, \%opendrain_28pin_24F_1,\%analog_28pin_1,\%RPanalog_28pin_1],
##44-pin devices, variant 1
["pic24fj16ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24fj32ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24fj48ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1],
["pic24fj64ga004",\@digio_44pin_1, \%pullups_44pin_1, \%opendrain_44pin_24F_1,\%analog_44pin_1,\%RPanalog_44pin_1],
#64-pin devices, F_GA
["pic24fj128ga106",\@digio_64pin_F_GA, \%pullups_64pin_F_GA, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA],
["pic24fj192ga106",\@digio_64pin_F_GA, \%pullups_64pin_F_GA, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA],
["pic24fj256ga106",\@digio_64pin_F_GA, \%pullups_64pin_F_GA, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA],
#64-pin devices, F_GA0
["pic24fj64ga006",\@digio_64pin_F_GA, \%pullups_64pin_F_GA0, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA0],
["pic24fj96ga006",\@digio_64pin_F_GA, \%pullups_64pin_F_GA0, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA0],
["PIC24FJ128GA006",\@digio_64pin_F_GA, \%pullups_64pin_F_GA0, \%opendrain_64pin_F_GA,\%analog_64pin_F_GA,\%RPanalog_64pin_F_GA0],
#64-pin devices, F_GB
["pic24fj64gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB],
["pic24fj128gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB],
["pic24fj192gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB],
["pic24fj256gb106",\@digio_64pin_F_GB, \%pullups_64pin_F_GB, \%opendrain_64pin_F_GB,\%analog_64pin_F_GB,\%RPanalog_64pin_F_GB],
#100-pin devices, F_GA1
["pic24fj128ga110",\@digio_100pin_F_GA, \%pullups_100pin_F_GA, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA],
["pic24fj192ga110",\@digio_100pin_F_GA, \%pullups_100pin_F_GA, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA],
["pic24fj256ga110",\@digio_100pin_F_GA, \%pullups_100pin_F_GA, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA],
#100-pin devices, F_GA0
["pic24fj64ga010",\@digio_100pin_F_GA, \%pullups_100pin_F_GA0, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA0],
["pic24fj96ga010",\@digio_100pin_F_GA, \%pullups_100pin_F_GA0, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA0],
["pic24fj128ga010",\@digio_100pin_F_GA, \%pullups_100pin_F_GA0, \%opendrain_100pin_F_GA,\%analog_100pin_F_GA,\%RPanalog_100pin_F_GA0],
#100-pin devices, F_GB
["pic24fj64gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB],
["pic24fj128gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB],
["pic24fj192gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB],
["pic24fj256gb110",\@digio_100pin_F_GB, \%pullups_100pin_F_GB, \%opendrain_100pin_F_GB,\%analog_100pin_F_GB,\%RPanalog_100pin_F_GB],
#80-pin devices, F_GA
["pic24fj128ga108",\@digio_80pin_F_GA, \%pullups_80pin_F_GA, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA],
["pic24fj192ga108",\@digio_80pin_F_GA, \%pullups_80pin_F_GA, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA],
["pic24fj256ga108",\@digio_80pin_F_GA, \%pullups_80pin_F_GA, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA],
#80-pin devices, F_GA0
["pic24fj64ga008",\@digio_80pin_F_GA, \%pullups_80pin_F_GA0, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA0],
["pic24fj96ga008",\@digio_80pin_F_GA, \%pullups_80pin_F_GA0, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA0],
["pic24fj128ga008",\@digio_80pin_F_GA, \%pullups_80pin_F_GA0, \%opendrain_80pin_F_GA,\%analog_80pin_F_GA,\%RPanalog_80pin_F_GA0],
#80-pin devices, F_GB
["pic24fj64gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB],
["pic24fj128gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB],
["pic24fj192gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB],
["pic24fj256gb108",\@digio_80pin_F_GB, \%pullups_80pin_F_GB, \%opendrain_80pin_F_GB,\%analog_80pin_F_GB,\%RPanalog_80pin_F_GB],
);





