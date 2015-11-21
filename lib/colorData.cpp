// -*- Mode:C; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      colorData.cpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     Definition of the colMatchPoints array@EOL 
 @copyright 
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
***************************************************************************************************************************************************************/

extern const float colMatchPoints[89][4] = {
  {390,   1.5000E-03,   -4.0000E-04,    6.2000E-03},    
  {395,   3.8000E-03,   -1.0000E-03,    1.6100E-02},    
  {400,   8.9000E-03,   -2.5000E-03,    4.0000E-02},    
  {405,   1.8800E-02,   -5.9000E-03,    9.0600E-02},    
  {410,   3.5000E-02,   -1.1900E-02,    1.8020E-01},    
  {415,   5.3100E-02,   -2.0100E-02,    3.0880E-01},    
  {420,   7.0200E-02,   -2.8900E-02,    4.6700E-01},    
  {425,   7.6300E-02,   -3.3800E-02,    6.1520E-01},    
  {430,   7.4500E-02,   -3.4900E-02,    7.6380E-01},    
  {435,   5.6100E-02,   -2.7600E-02,    8.7780E-01},    
  {440,   3.2300E-02,   -1.6900E-02,    9.7550E-01},    
  {445,  -4.4000E-03,    2.4000E-03,    1.0019E+00},    
  {450,  -4.7800E-02,    2.8300E-02,    9.9960E-01},    
  {455,  -9.7000E-02,    6.3600E-02,    9.1390E-01},    
  {460,  -1.5860E-01,    1.0820E-01,    8.2970E-01},    
  {465,  -2.2350E-01,    1.6170E-01,    7.4170E-01},    
  {470,  -2.8480E-01,    2.2010E-01,    6.1340E-01},    
  {475,  -3.3460E-01,    2.7960E-01,    4.7200E-01},    
  {480,  -3.7760E-01,    3.4280E-01,    3.4950E-01},    
  {485,  -4.1360E-01,    4.0860E-01,    2.5640E-01},    
  {490,  -4.3170E-01,    4.7160E-01,    1.8190E-01},    
  {495,  -4.4520E-01,    5.4910E-01,    1.3070E-01},    
  {500,  -4.3500E-01,    6.2600E-01,    9.1000E-02},    
  {505,  -4.1400E-01,    7.0970E-01,    5.8000E-02},    
  {510,  -3.6730E-01,    7.9350E-01,    3.5700E-02},    
  {515,  -2.8450E-01,    8.7150E-01,    2.0000E-02},    
  {520,  -1.8550E-01,    9.4770E-01,    9.5000E-03},    
  {525,  -4.3500E-02,    9.9450E-01,    7.0000E-04},    
  {530,   1.2700E-01,    1.0203E+00,   -4.3000E-03},    
  {535,   3.1290E-01,    1.0375E+00,   -6.4000E-03},    
  {540,   5.3620E-01,    1.0517E+00,   -8.2000E-03},    
  {545,   7.7220E-01,    1.0390E+00,   -9.4000E-03},    
  {550,   1.0059E+00,    1.0029E+00,   -9.7000E-03},    
  {555,   1.2710E+00,    9.6980E-01,   -9.7000E-03},    
  {560,   1.5574E+00,    9.1620E-01,   -9.3000E-03},    
  {565,   1.8465E+00,    8.5710E-01,   -8.7000E-03},    
  {570,   2.1511E+00,    7.8230E-01,   -8.0000E-03},    
  {575,   2.4250E+00,    6.9530E-01,   -7.3000E-03},    
  {580,   2.6574E+00,    5.9660E-01,   -6.3000E-03},    
  {585,   2.9151E+00,    5.0630E-01,   -5.3700E-03},    
  {590,   3.0779E+00,    4.2030E-01,   -4.4500E-03},    
  {595,   3.1613E+00,    3.3600E-01,   -3.5700E-03},    
  {600,   3.1673E+00,    2.5910E-01,   -2.7700E-03},    
  {605,   3.1048E+00,    1.9170E-01,   -2.0800E-03},    
  {610,   2.9462E+00,    1.3670E-01,   -1.5000E-03},    
  {615,   2.7194E+00,    9.3800E-02,   -1.0300E-03},    
  {620,   2.4526E+00,    6.1100E-02,   -6.8000E-04},    
  {625,   2.1700E+00,    3.7100E-02,   -4.4200E-04},    
  {630,   1.8358E+00,    2.1500E-02,   -2.7200E-04},    
  {635,   1.5179E+00,    1.1200E-02,   -1.4100E-04},    
  {640,   1.2428E+00,    4.4000E-03,   -5.4900E-05},    
  {645,   1.0070E+00,    7.8000E-05,   -2.2000E-06},    
  {650,   7.8270E-01,   -1.3680E-03,    2.3700E-05},    
  {655,   5.9340E-01,   -1.9880E-03,    2.8600E-05},    
  {660,   4.4420E-01,   -2.1680E-03,    2.6100E-05},    
  {665,   3.2830E-01,   -2.0060E-03,    2.2500E-05},    
  {670,   2.3940E-01,   -1.6420E-03,    1.8200E-05},    
  {675,   1.7220E-01,   -1.2720E-03,    1.3900E-05},    
  {680,   1.2210E-01,   -9.4700E-04,    1.0300E-05},    
  {685,   8.5300E-02,   -6.8300E-04,    7.3800E-06},    
  {690,   5.8600E-02,   -4.7800E-04,    5.2200E-06},    
  {695,   4.0800E-02,   -3.3700E-04,    3.6700E-06},    
  {700,   2.8400E-02,   -2.3500E-04,    2.5600E-06},    
  {705,   1.9700E-02,   -1.6300E-04,    1.7600E-06},    
  {710,   1.3500E-02,   -1.1100E-04,    1.2000E-06},    
  {715,   9.2400E-03,   -7.4800E-05,    8.1700E-07},    
  {720,   6.3800E-03,   -5.0800E-05,    5.5500E-07},    
  {725,   4.4100E-03,   -3.4400E-05,    3.7500E-07},    
  {730,   3.0700E-03,   -2.3400E-05,    2.5400E-07},    
  {735,   2.1400E-03,   -1.5900E-05,    1.7100E-07},    
  {740,   1.4900E-03,   -1.0700E-05,    1.1600E-07},    
  {745,   1.0500E-03,   -7.2300E-06,    7.8500E-08},    
  {750,   7.3900E-04,   -4.8700E-06,    5.3100E-08},    
  {755,   5.2300E-04,   -3.2900E-06,    3.6000E-08},    
  {760,   3.7200E-04,   -2.2200E-06,    2.4400E-08},    
  {765,   2.6500E-04,   -1.5000E-06,    1.6500E-08},    
  {770,   1.9000E-04,   -1.0200E-06,    1.1200E-08},    
  {775,   1.3600E-04,   -6.8800E-07,    7.5300E-09},    
  {780,   9.8400E-05,   -4.6500E-07,    5.0700E-09},    
  {785,   7.1300E-05,   -3.1200E-07,    3.4000E-09},    
  {790,   5.1800E-05,   -2.0800E-07,    2.2700E-09},    
  {795,   3.7700E-05,   -1.3700E-07,    1.5000E-09},    
  {800,   2.7600E-05,   -8.8000E-08,    9.8600E-10},    
  {805,   2.0300E-05,   -5.5300E-08,    6.3900E-10},    
  {810,   1.4900E-05,   -3.3600E-08,    4.0700E-10},    
  {815,   1.1000E-05,   -1.9600E-08,    2.5300E-10},    
  {820,   8.1800E-06,   -1.0900E-08,    1.5200E-10},    
  {825,   6.0900E-06,   -5.7000E-09,    8.6400E-11},    
  {830,   4.5500E-06,   -2.7700E-09,    4.4200E-11}
};

const char *webSafeColorData[218][7] = {
  // Alt1 & Al2 are different approximations for CB vision
  //            Alt1        Alt1        Alt1         Alt2        Alt2        Alt2
  //Normal      Protanopia  Deutanopia  Tritanoptia  Protanopia  Deutanopia  Tritanoptia 
  { "#000000",  "#000000",  "#000000",  "#000000",   "#000000",  "#000000",  "#000000"}, // The 0 color (white) -- not part of the color pallet
  { "#000000",  "#000000",  "#000000",  "#000000",   "#000000",  "#000000",  "#000000"},                   
  { "#000033",  "#002346",  "#002135",  "#001c1d",   "#000e33",  "#001433",  "#00191e"}, 
  { "#000066",  "#004487",  "#004168",  "#003739",   "#001d66",  "#002866",  "#00323d"}, 
  { "#000099",  "#0060c1",  "#005e97",  "#005155",   "#002b99",  "#003c99",  "#004b5b"}, 
  { "#0000cc",  "#0078f0",  "#0076be",  "#006a6e",   "#003acc",  "#0050cb",  "#00647a"}, 
  { "#0000ff",  "#719cff",  "#008bdf",  "#007f85",   "#0048ff",  "#0064fe",  "#007c98"}, // 6
  { "#003300",  "#312c00",  "#362a0c",  "#173033",   "#422f00",  "#3a2a0b",  "#202e31"}, 
  { "#003333",  "#2e2e30",  "#2f2d34",  "#0a3236",   "#303133",  "#2c2f33",  "#113237"}, 
  { "#003366",  "#0d3366",  "#003e68",  "#004347",   "#003566",  "#003866",  "#00404a"}, 
  { "#003399",  "#0053a6",  "#005e9a",  "#00595e",   "#003d99",  "#004699",  "#005463"}, 
  { "#0033cc",  "#006fde",  "#0078c2",  "#006f74",   "#0047cc",  "#0057cb",  "#006a7f"}, 
  { "#0033ff",  "#5b91ff",  "#008ce2",  "#008389",   "#0053ff",  "#0069fe",  "#00819c"}, // 12
  { "#006600",  "#635800",  "#6d5418",  "#2d5f66",   "#845d00",  "#755316",  "#415c61"}, 
  { "#006633",  "#61592e",  "#6a5538",  "#2a6068",   "#7e5e33",  "#6f5635",  "#3c5d63"}, 
  { "#006666",  "#5c5b5f",  "#5e5a69",  "#15656d",   "#606266",  "#585d67",  "#21646d"}, 
  { "#006699",  "#4e5f93",  "#3d629a",  "#00727a",   "#266699",  "#226599",  "#00707e"}, 
  { "#0066cc",  "#1a66cc",  "#0078c9",  "#00828a",   "#006bcc",  "#0070cc",  "#008093"}, 
  { "#0066ff",  "#007efe",  "#0090ec",  "#00929a",   "#0072ff",  "#007eff",  "#0093ac"}, // 18
  { "#009900",  "#948500",  "#a37e25",  "#448f9a",   "#c68c00",  "#af7d20",  "#618a92"}, 
  { "#009933",  "#93852d",  "#a27e3d",  "#42909a",   "#c38d33",  "#ac7e39",  "#5f8b93"}, 
  { "#009966",  "#90865e",  "#9b816c",  "#39929d",   "#b38f66",  "#9e8468",  "#548f99"}, 
  { "#009999",  "#8a898f",  "#8d869d",  "#1f97a3",   "#909399",  "#848c9a",  "#3296a4"}, 
  { "#0099cc",  "#7e8dc2",  "#728ecf",  "#00a1ac",   "#6896cc",  "#5f93cc",  "#00a1b4"}, 
  { "#0099ff",  "#6792f8",  "#3398ff",  "#00acb7",   "#009bff",  "#009dff",  "#00afc7"}, // 24
  { "#00cc00",  "#c5b000",  "#daa831",  "#5abfcd",   "#ffbb00",  "#eaa72b",  "#82b8c2"}, 
  { "#00cc33",  "#c5b12b",  "#d9a844",  "#59bfcd",   "#ffbb32",  "#e8a83f",  "#80b8c3"}, 
  { "#00cc66",  "#c3b25d",  "#d4aa6f",  "#54c1cf",   "#fcbd66",  "#dfab6b",  "#79bbc7"}, 
  { "#00cc99",  "#bfb38d",  "#cbaea0",  "#47c4d3",   "#e6c099",  "#cbb29b",  "#69c0cf"}, 
  { "#00cccc",  "#b8b6bf",  "#bbb3d1",  "#29cad9",   "#c0c4cc",  "#afbbcd",  "#42c8da"}, 
  { "#00ccff",  "#adbaf2",  "#a5bbff",  "#00d0df",   "#9dc7ff",  "#8fc2ff",  "#00d3ea"}, // 30
  { "#00ff00",  "#f6dc00",  "#ffcd72",  "#73edff",   "#ffe900",  "#ffd036",  "#a2e6f3"}, 
  { "#00ff33",  "#f6dd29",  "#ffcd77",  "#73edff",   "#ffea31",  "#ffd146",  "#a1e6f3"}, 
  { "#00ff66",  "#f5dd5c",  "#ffcf87",  "#73eeff",   "#ffeb65",  "#ffd46e",  "#9ce8f6"}, 
  { "#00ff99",  "#f2df8c",  "#ffd3a6",  "#72eeff",   "#ffed99",  "#ffd99d",  "#91ecfc"}, 
  { "#00ffcc",  "#ede1bd",  "#fbdad4",  "#70efff",   "#fff1cc",  "#f7e1ce",  "#7df2ff"}, 
  { "#00ffff",  "#e6e4ee",  "#e6dcff",  "#6eefff",   "#f0f5ff",  "#dbe9ff",  "#53faff"}, // 36
  { "#330000",  "#1e1b08",  "#221a00",  "#330600",   "#1a1202",  "#231800",  "#340010"}, 
  { "#330033",  "#002448",  "#131e30",  "#301517",   "#001633",  "#001f33",  "#2c1a1c"}, 
  { "#330066",  "#00468b",  "#003f67",  "#212a2d",   "#002166",  "#002d66",  "#00333a"}, 
  { "#330099",  "#0062c4",  "#005d96",  "#00474b",   "#002e99",  "#003f99",  "#004b5a"}, 
  { "#3300cc",  "#0079f2",  "#0076bf",  "#006469",   "#003bcc",  "#0052cb",  "#006479"}, 
  { "#3300ff",  "#739dff",  "#008bdf",  "#007c82",   "#0049ff",  "#0065fe",  "#007d98"}, // 42
  { "#333300",  "#373200",  "#3d2f09",  "#363033",   "#453100",  "#412e09",  "#392e2f"}, 
  { "#333333",  "#343333",  "#373133",  "#333236",   "#333333",  "#333333",  "#333333"}, 
  { "#333366",  "#19376a",  "#003b65",  "#263c41",   "#003766",  "#003c66",  "#004147"}, 
  { "#333399",  "#0054aa",  "#005d99",  "#005056",   "#003f99",  "#004999",  "#005462"}, 
  { "#3333cc",  "#0070e1",  "#0078c2",  "#006a70",   "#0048cc",  "#0059cb",  "#006a7e"}, 
  { "#3333ff",  "#6094ff",  "#008ce2",  "#008187",   "#0053ff",  "#006bfe",  "#00819c"}, // 48
  { "#336600",  "#655b00",  "#705617",  "#415f66",   "#855e00",  "#775515",  "#4d5c5f"}, 
  { "#336633",  "#645b2f",  "#6d5737",  "#3f6068",   "#7f5f33",  "#725735",  "#4a5e62"}, 
  { "#336666",  "#5e5d61",  "#615b68",  "#35656d",   "#616366",  "#5b5f66",  "#39646c"}, 
  { "#336699",  "#506195",  "#43639a",  "#146d76",   "#2a6699",  "#2c6799",  "#00707d"}, 
  { "#3366cc",  "#2067cd",  "#0078c9",  "#007f87",   "#006ccc",  "#0072cc",  "#008093"}, 
  { "#3366ff",  "#2581ff",  "#0090ec",  "#009099",   "#0072ff",  "#007ffe",  "#0093ab"}, 
  { "#339900",  "#958600",  "#a58600",  "#518f9a",   "#c78c00",  "#b17e20",  "#698a91"}, 
  { "#339933",  "#95862e",  "#a4803c",  "#4f909a",   "#c38d33",  "#ae7f39",  "#678b92"}, 
  { "#339966",  "#92875e",  "#9d826b",  "#49929d",   "#b48f66",  "#a08568",  "#5d8f98"}, 
  { "#339999",  "#8c8a90",  "#8f879d",  "#3997a3",   "#919499",  "#858d9a",  "#4296a3"}, 
  { "#3399cc",  "#7f8ec3",  "#758fce",  "#00a0ac",   "#6997cc",  "#6294cc",  "#00a1b3"}, 
  { "#3399ff",  "#6993fa",  "#3999ff",  "#00abb7",   "#009bff",  "#009eff",  "#00afc6"}, 
  { "#33cc00",  "#c6b100",  "#dba830",  "#64bfd7",   "#ffbb00",  "#eba72b",  "#87b8c1"}, 
  { "#33cc33",  "#c6b22c",  "#daa943",  "#63bfcd",   "#ffbb32",  "#e9a83f",  "#85b8c2"}, 
  { "#33cc66",  "#c4b25d",  "#d6ab6f",  "#5ec1cf",   "#fcbd66",  "#e0ac6b",  "#7fbbc6"}, 
  { "#33cc99",  "#c0b48e",  "#ccaea0",  "#54c4d3",   "#e6c099",  "#ccb39b",  "#70c0ce"}, 
  { "#33cccc",  "#b9b7bf",  "#bdb4d1",  "#3ecad9",   "#c0c5cc",  "#b0bbcd",  "#4fc8da"}, 
  { "#33ccff",  "#aebbf2",  "#a7bbff",  "#00d1e0",   "#9dc8ff",  "#91c2ff",  "#00d3e9"}, 
  { "#33ff00",  "#f7dd00",  "#ffcd74",  "#7aedff",   "#ffea00",  "#ffd136",  "#a6e6f2"}, 
  { "#33ff33",  "#f7dd29",  "#ffcd78",  "#7aedff",   "#ffea31",  "#ffd246",  "#a5e6f3"}, 
  { "#33ff66",  "#f5de5c",  "#ffcf88",  "#79eeff",   "#ffeb65",  "#ffd46e",  "#a0e8f6"}, 
  { "#33ff99",  "#f3df8c",  "#ffd4a6",  "#78eeff",   "#ffed99",  "#ffda9d",  "#95ecfc"}, 
  { "#33ffcc",  "#eee2bd",  "#fcdbd4",  "#76efff",   "#fff1cc",  "#f8e2ce",  "#82f2ff"}, 
  { "#33ffff",  "#e7e5ef",  "#e7ddff",  "#74efff",   "#f0f6ff",  "#dceaff",  "#5cfaff"}, 
  { "#660000",  "#3c360f",  "#453500",  "#660b00",   "#332405",  "#453000",  "#670021"}, 
  { "#660033",  "#323748",  "#3f352f",  "#651615",   "#1d2733",  "#393532",  "#651527"}, 
  { "#660066",  "#00478e",  "#253d60",  "#602b2d",   "#002d66",  "#003e65",  "#583338"}, 
  { "#660099",  "#0065ca",  "#005a94",  "#563f44",   "#003699",  "#004b98",  "#364e52"}, 
  { "#6600cc",  "#007cf8",  "#0076bf",  "#42545b",   "#0042cc",  "#005acb",  "#006674"}, 
  { "#6600ff",  "#7aa1ff",  "#008be1",  "#006b73",   "#004eff",  "#006cfe",  "#007e94"}, 
  { "#663300",  "#4a420b",  "#534000",  "#673033",   "#4f3804",  "#563c00",  "#692c35"}, 
  { "#663333",  "#46433a",  "#4f4031",  "#663336",   "#413a33",  "#4d4032",  "#673139"}, 
  { "#663366",  "#324676",  "#3d4763",  "#623d41",   "#003e66",  "#2c4865",  "#5b4244"}, 
  { "#663399",  "#0059b4",  "#005995",  "#584c51",   "#004499",  "#005398",  "#3c565b"}, 
  { "#6633cc",  "#0074ea",  "#0076c2",  "#445d64",   "#004dcc",  "#0061cb",  "#006c7a"}, 
  { "#6633ff",  "#6e9aff",  "#008ce4",  "#007179",   "#0057ff",  "#0071fe",  "#008298"}, 
  { "#666600",  "#6f6300",  "#7b5e11",  "#6c5f66",   "#8a6100",  "#825c11",  "#725c5e"}, 
  { "#666633",  "#6d6432",  "#795f35",  "#6b6067",   "#846233",  "#7d5e34",  "#705e60"}, 
  { "#666666",  "#686666",  "#6f6367",  "#67656c",   "#666666",  "#666666",  "#666666"}, 
  { "#666699",  "#59699c",  "#586a98",  "#5e6d75",   "#376999",  "#446d99",  "#507278"}, 
  { "#6666cc",  "#326ed5",  "#0076c9",  "#4d7982",   "#006ecc",  "#0077cc",  "#00818f"}, 
  { "#6666ff",  "#518dff",  "#0090ee",  "#228791",   "#0075ff",  "#0084fe",  "#0094a8"}, 
  { "#669900",  "#9b8b00",  "#ac8421",  "#758f9a",   "#c98e00",  "#b7821e",  "#838b8d"}, 
  { "#669933",  "#9b8b2f",  "#aa853b",  "#74909a",   "#c68f33",  "#b48338",  "#818c8e"}, 
  { "#669966",  "#988c61",  "#a4876a",  "#71929d",   "#b79166",  "#a78968",  "#7b9094"}, 
  { "#669999",  "#918f93",  "#978c9c",  "#6997a3",   "#939599",  "#8c9199",  "#6b97a0"}, 
  { "#6699cc",  "#8593c7",  "#8093cd",  "#5a9fab",   "#6e99cc",  "#6c98cc",  "#46a2b0"}, 
  { "#6699ff",  "#6e98fe",  "#519cfe",  "#3ea9b6",   "#009dff",  "#00a1ff",  "#00b0c4"}, 
  { "#66cc00",  "#cab500",  "#e0ac2e",  "#82becd",   "#ffbc00",  "#efaa2a",  "#9ab8bf"}, 
  { "#66cc33",  "#cab52d",  "#dfac42",  "#81bfcd",   "#ffbd32",  "#edab3e",  "#99b9c0"}, 
  { "#66cc66",  "#c8b65e",  "#daae6e",  "#7ec1cf",   "#febe66",  "#e4af6a",  "#94bcc4"}, 
  { "#66cc99",  "#c4b88f",  "#d2b29f",  "#77c4d3",   "#e8c199",  "#d2b69b",  "#88c1cc"}, 
  { "#66cccc",  "#bdbbc1",  "#c3b7d1",  "#6bcad9",   "#c2c6cc",  "#b5becd",  "#71c9d8"}, 
  { "#66ccff",  "#b2bef5",  "#adbeff",  "#57d1e1",   "#a0c9ff",  "#97c5ff",  "#3cd4e7"}, 
  { "#66ff00",  "#fae000",  "#ffce79",  "#92edff",   "#ffea00",  "#ffd335",  "#b5e6f0"}, 
  { "#66ff33",  "#fae02a",  "#ffcf7c",  "#92edff",   "#ffeb32",  "#ffd445",  "#b4e7f1"}, 
  { "#66ff66",  "#f8e15d",  "#ffd08b",  "#90eeff",   "#ffec65",  "#ffd66e",  "#b0e9f4"}, 
  { "#66ff99",  "#f6e28d",  "#ffd5a7",  "#8eeeff",   "#ffee99",  "#ffdc9d",  "#a7ecfa"}, 
  { "#66ffcc",  "#f1e4bf",  "#ffddd3",  "#8befff",   "#fff2cc",  "#fce4ce",  "#97f3ff"}, 
  { "#66ffff",  "#eae7f0",  "#ebdfff",  "#88efff",   "#f2f6ff",  "#e0ecff",  "#7afbff"}, 
  { "#990000",  "#5a5117",  "#674f00",  "#991100",   "#4d3607",  "#684900",  "#9b0031"}, 
  { "#990033",  "#55514a",  "#634e2c",  "#981612",   "#3e3833",  "#624b2f",  "#990035"}, 
  { "#990066",  "#39538f",  "#57535f",  "#962b2c",   "#003c66",  "#485364",  "#933041"}, 
  { "#990099",  "#0067d0",  "#385b90",  "#904044",   "#004399",  "#005c98",  "#854d54"}, 
  { "#9900cc",  "#2782ff",  "#0073c0",  "#87555b",   "#004ccc",  "#0069cb",  "#686969"}, 
  { "#9900ff",  "#83a6ff",  "#008ce5",  "#796a71",   "#0057ff",  "#0077fe",  "#1c808c"}, 
  { "#993300",  "#635913",  "#705600",  "#9a3032",   "#604407",  "#725000",  "#9c293f"}, 
  { "#993333",  "#5f5941",  "#6c552d",  "#993335",   "#564533",  "#6d5230",  "#9a2e42"}, 
  { "#993366",  "#505b80",  "#625961",  "#963d40",   "#2e4966",  "#545a64",  "#943f4c"}, 
  { "#993399",  "#005ebf",  "#496192",  "#914c51",   "#004e99",  "#106398",  "#86565b"}, 
  { "#9933cc",  "#007af6",  "#0073c2",  "#885d64",   "#0056cc",  "#006ecb",  "#6b6e6f"}, 
  { "#9933ff",  "#7da2ff",  "#008de8",  "#7a7078",   "#005fff",  "#007cfe",  "#288591"}, 
  { "#996600",  "#7f720d",  "#8e6c00",  "#9d5f66",   "#926703",  "#946800",  "#a15b63"}, 
  { "#996633",  "#7e7237",  "#8c6d31",  "#9c6067",   "#8d6833",  "#906a32",  "#a05d65"}, 
  { "#996666",  "#78746d",  "#847064",  "#9a656c",   "#726c66",  "#7e7165",  "#9a656a"}, 
  { "#996699",  "#6a77a5",  "#737696",  "#946d75",   "#496f99",  "#617898",  "#8d7275"}, 
  { "#9966cc",  "#497bdf",  "#507fc7",  "#8c7982",   "#0074cc",  "#0081cb",  "#758387"}, 
  { "#9966ff",  "#709bff",  "#0090f3",  "#7e8791",   "#007aff",  "#008dfe",  "#4496a2"}, 
  { "#999900",  "#a69500",  "#a69500",  "#a28f99",   "#ce9200",  "#c38a1a",  "#ac8b8e"}, 
  { "#999933",  "#a59532",  "#b78e37",  "#a2909a",   "#cb9233",  "#c08b37",  "#aa8c8f"}, 
  { "#999966",  "#a29665",  "#b29068",  "#9f929d",   "#bd9566",  "#b49067",  "#a59092"}, 
  { "#999999",  "#9b9899",  "#a6949a",  "#9a97a3",   "#999999",  "#999999",  "#999999"}, 
  { "#9999cc",  "#8f9cce",  "#929bcc",  "#929fab",   "#769ccc",  "#7e9fcc",  "#86a4aa"}, 
  { "#9999ff",  "#83a4ff",  "#6fa4fd",  "#86a9b6",   "#00a0ff",  "#38a8ff",  "#63b2bf"}, 
  { "#99cc00",  "#d2bc00",  "#e9b22a",  "#abbecd",   "#ffbf00",  "#f7b027",  "#bababa"}, 
  { "#99cc33",  "#d1bc2f",  "#e8b33f",  "#aabfcd",   "#ffbf32",  "#f5b13d",  "#b9babb"}, 
  { "#99cc66",  "#cfbd61",  "#e4b56c",  "#a8c1cf",   "#ffc166",  "#edb46a",  "#b5bdbf"}, 
  { "#99cc99",  "#cbbf93",  "#dbb89d",  "#a3c4d3",   "#edc499",  "#dbbb9b",  "#adc2c7"}, 
  { "#99cccc",  "#c4c1c6",  "#cebdcf",  "#9ccad9",   "#c6c8cc",  "#bec4cd",  "#9dcad3"}, 
  { "#99ccff",  "#b9c5fa",  "#b9c4ff",  "#91d1e1",   "#a5cbff",  "#a3caff",  "#83d5e3"}, 
  { "#99ff00",  "#ffe41c",  "#ffd080",  "#b6edff",   "#ffec00",  "#ffd733",  "#d0e7ec"}, 
  { "#99ff33",  "#ffe532",  "#ffd184",  "#b5edff",   "#ffed32",  "#ffd844",  "#cfe8ed"}, 
  { "#99ff66",  "#fee65e",  "#ffd291",  "#b4eeff",   "#ffee66",  "#ffda6d",  "#cbeaf0"}, 
  { "#99ff99",  "#fbe790",  "#ffd6a9",  "#b0eeff",   "#fff099",  "#ffe09d",  "#c4edf6"}, 
  { "#99ffcc",  "#f7e9c1",  "#ffddd0",  "#acefff",   "#fff4cc",  "#ffe7ce",  "#b7f3ff"}, 
  { "#99ffff",  "#efecf4",  "#f4e4ff",  "#a6efff",   "#f4f8ff",  "#e7f0ff",  "#a3fcff"}, 
  { "#cc0000",  "#786c1e",  "#886900",  "#cc1600",   "#66490a",  "#8b6100",  "#ce0042"}, 
  { "#cc0033",  "#746c4c",  "#856726",  "#cb170b",   "#5e4a33",  "#87632c",  "#cd0044"}, 
  { "#cc0066",  "#646d90",  "#7e6a5e",  "#ca2b2b",   "#3a4e66",  "#736a63",  "#c92a4e"}, 
  { "#cc0099",  "#356fd5",  "#6e7190",  "#c64043",   "#005299",  "#537297",  "#c04a5d"}, 
  { "#cc00cc",  "#5d91ff",  "#4b7ac0",  "#c0555a",   "#0059cc",  "#007bca",  "#b1676f"}, 
  { "#cc00ff",  "#8cabff",  "#008cec",  "#b76a71",   "#0062ff",  "#0087fe",  "#978284"}, 
  { "#cc3300",  "#7e711b",  "#8f6d00",  "#cc3030",   "#745209",  "#926600",  "#cf214c"}, 
  { "#cc3333",  "#7b7146",  "#8c6c27",  "#cc3334",   "#6d5333",  "#8e682c",  "#ce284e"}, 
  { "#cc3366",  "#707387",  "#856f5f",  "#ca3d3f",   "#4d5766",  "#7b6f63",  "#ca3c56"}, 
  { "#cc3399",  "#5275c8",  "#767591",  "#c64c50",   "#005b99",  "#5e7697",  "#c15463"}, 
  { "#cc33cc",  "#4387ff",  "#577ec2",  "#c15e64",   "#0061cc",  "#007fca",  "#b26d75"}, 
  { "#cc33ff",  "#8aaaff",  "#008def",  "#b87178",   "#0069ff",  "#008bfe",  "#988788"}, 
  { "#cc6600",  "#948415",  "#a67f00",  "#cf5f65",   "#9e7008",  "#ac7900",  "#d3596b"}, 
  { "#cc6633",  "#92853c",  "#a47e2b",  "#ce6067",   "#9a7133",  "#a97a2f",  "#d25b6c"}, 
  { "#cc6666",  "#8c8675",  "#9e8161",  "#cc656c",   "#837466",  "#9a8064",  "#ce6371"}, 
  { "#cc6699",  "#7f88af",  "#918694",  "#c96e75",   "#5e7899",  "#7f8897",  "#c5717b"}, 
  { "#cc66cc",  "#648ceb",  "#7b8dc5",  "#c37982",   "#007ccc",  "#5790cb",  "#b68388"}, 
  { "#cc66ff",  "#87a7ff",  "#4c97f6",  "#bb8791",   "#0081ff",  "#009afe",  "#9e9899"}, 
  { "#cc9900",  "#b5a20e",  "#ca9a00",  "#d38f99",   "#d69700",  "#d4960e",  "#da8a92"}, 
  { "#cc9933",  "#b5a336",  "#c99b32",  "#d2909a",   "#d39833",  "#d19734",  "#d98b93"}, 
  { "#cc9966",  "#b1a46a",  "#c49d65",  "#d0929d",   "#c59a66",  "#c79b66",  "#d58f97"}, 
  { "#cc9999",  "#aaa5a0",  "#baa198",  "#cd98a2",   "#a59e99",  "#b0a398",  "#cd989d"}, 
  { "#cc99cc",  "#9ea8d7",  "#aaa7c9",  "#c79fab",   "#82a1cc",  "#94abcb",  "#bfa5a7"}, 
  { "#cc99ff",  "#98b1ff",  "#8faefb",  "#bfa9b6",   "#16a5ff",  "#68b2fe",  "#aab4b6"}, 
  { "#cccc00",  "#ddc600",  "#f6c600",  "#d9becc",   "#ffc300",  "#ffb822",  "#e5b9bd"}, 
  { "#cccc33",  "#ddc631",  "#f5bc3b",  "#d8bfcd",   "#ffc333",  "#ffb93a",  "#e4babe"}, 
  { "#cccc66",  "#dbc764",  "#f1be6a",  "#d7c1cf",   "#ffc466",  "#fabc68",  "#e0bdc0"}, 
  { "#cccc99",  "#d7c997",  "#eac19b",  "#d3c4d3",   "#f3c799",  "#eac39a",  "#d9c3c5"}, 
  { "#cccccc",  "#cfcbcb",  "#dec6cd",  "#cecad9",   "#cccccc",  "#cccccc",  "#cccccc"}, 
  { "#ccccff",  "#c4ceff",  "#cbccff",  "#c6d1e1",   "#accfff",  "#b3d2ff",  "#bbd6dd"}, 
  { "#ccff00",  "#ffe655",  "#ffd389",  "#e0eeff",   "#ffef00",  "#ffde30",  "#f3e8e9"}, 
  { "#ccff33",  "#ffe75c",  "#ffd38c",  "#e0eeff",   "#ffef32",  "#ffde42",  "#f2e9e9"}, 
  { "#ccff66",  "#ffe873",  "#ffd497",  "#ddeeff",   "#fff166",  "#ffe16c",  "#efebeb"}, 
  { "#ccff99",  "#ffeb97",  "#ffd8ab",  "#d9eeff",   "#fff399",  "#ffe69c",  "#e9eff0"}, 
  { "#ccffcc",  "#fff1c5",  "#ffdecc",  "#d3efff",   "#fff6cc",  "#ffedcd",  "#dff5fa"}, 
  { "#ccffff",  "#f8f4f8",  "#ffeafd",  "#cbefff",   "#f9fbff",  "#f1f6ff",  "#d0fdff"}, 
  { "#ff0000",  "#968726",  "#a98200",  "#fe1c00",   "#805b0c",  "#ae7900",  "#ff0052"}, 
  { "#ff0033",  "#93874e",  "#a8801a",  "#fe1a00",   "#7a5c34",  "#ab7a26",  "#ff0054"}, 
  { "#ff0066",  "#888892",  "#a2835b",  "#fd2b28",   "#5c6066",  "#9d8061",  "#fe205b"}, 
  { "#ff0099",  "#6e89d7",  "#97888e",  "#fa4042",   "#006399",  "#818996",  "#f84668"}, 
  { "#ff00cc",  "#7ba0ff",  "#838fc0",  "#f6555a",   "#0069cc",  "#5b90ca",  "#ed6478"}, 
  { "#ff00ff",  "#96b1ff",  "#5e98f1",  "#f06a71",   "#0070ff",  "#009afd",  "#dd818b"}, 
  { "#ff3300",  "#9a8b23",  "#ae8600",  "#ff3331",   "#8a620c",  "#b37d00",  "#ff095a"}, 
  { "#ff3333",  "#988b4a",  "#ad841c",  "#ff3332",   "#856334",  "#b07e27",  "#ff1b5c"}, 
  { "#ff3366",  "#8f8c8b",  "#a7875c",  "#fe3d3e",   "#676766",  "#a38461",  "#ff3662"}, 
  { "#ff3399",  "#7a8ece",  "#9d8b8f",  "#fb4c4f",   "#396a99",  "#878c96",  "#f8506e"}, 
  { "#ff33cc",  "#779dff",  "#8a92c1",  "#f75e63",   "#006fcc",  "#6494ca",  "#ee6b7d"}, 
  { "#ff33ff",  "#96b1ff",  "#679bf2",  "#f07178",   "#0076ff",  "#009dfd",  "#de858f"}, 
  { "#ff6600",  "#ac9a1e",  "#c09300",  "#ff6569",   "#ae7b0b",  "#c78c00",  "#ff5674"}, 
  { "#ff6633",  "#aa9a42",  "#bf9322",  "#ff656a",   "#aa7c34",  "#c58d2a",  "#ff5875"}, 
  { "#ff6666",  "#a59b7c",  "#bb955e",  "#ff666c",   "#967e66",  "#b99162",  "#ff607a"}, 
  { "#ff6699",  "#999db9",  "#b19992",  "#fd6e74",   "#738299",  "#9f9a96",  "#fb6f83"}, 
  { "#ff66cc",  "#82a0f6",  "#a09fc3",  "#f87981",   "#2786cc",  "#83a1ca",  "#f1818f"}, 
  { "#ff66ff",  "#98b2ff",  "#85a7f5",  "#f28791",   "#008bff",  "#47aafd",  "#e1979e"}, 
  { "#ff9900",  "#c8b317",  "#dfaa00",  "#ff949c",   "#e19f08",  "#e9a400",  "#ff8898"}, 
  { "#ff9933",  "#c7b43a",  "#deab2a",  "#ff949d",   "#de9f33",  "#e7a52f",  "#ff8999"}, 
  { "#ff9966",  "#c4b470",  "#daac62",  "#ff959e",   "#d1a166",  "#dea964",  "#ff8e9c"}, 
  { "#ff9999",  "#bdb6a8",  "#d2b095",  "#ff99a2",   "#b3a599",  "#cab097",  "#ff96a3"}, 
  { "#ff99cc",  "#b1b8e0",  "#c5b5c7",  "#fc9faa",   "#90a9cc",  "#aeb9ca",  "#f7a3ac"}, 
  { "#ff99ff",  "#aabdff",  "#b0bcf9",  "#f6a9b5",   "#4facff",  "#8dc0fe",  "#e8b3b8"}, 
  { "#ffcc00",  "#ecd30f",  "#ffc750",  "#ffbeca",   "#ffc800",  "#ffc319",  "#ffb8c1"}, 
  { "#ffcc33",  "#ecd435",  "#ffc857",  "#ffbfca",   "#ffc833",  "#ffc436",  "#ffb9c2"}, 
  { "#ffcc66",  "#e9d469",  "#ffca6f",  "#ffc0cd",   "#ffca66",  "#ffc767",  "#ffbcc4"}, 
  { "#ffcc99",  "#e5d69d",  "#fccd99",  "#ffc4d1",   "#fccc99",  "#fdcd99",  "#ffc2c9"}, 
  { "#ffcccc",  "#ded8d2",  "#f1d2cb",  "#ffcad8",   "#d7d1cc",  "#e2d6cb",  "#ffcbd0"}, 
  { "#ffccff",  "#cfd7ff",  "#e1d8fd",  "#fbd1e1",   "#b7d4ff",  "#c8ddfe",  "#f2d7d9"}, 
  { "#ffff00",  "#ffe871",  "#ffd592",  "#ffe4f2",   "#fff300",  "#ffe62b",  "#ffe7ec"}, 
  { "#ffff33",  "#ffe975",  "#ffd594",  "#ffe5f3",   "#fff332",  "#ffe73f",  "#ffe8ed"}, 
  { "#ffff66",  "#ffea86",  "#ffd79d",  "#ffe6f5",   "#fff466",  "#ffe96b",  "#ffeaee"}, 
  { "#ffff99",  "#ffeda2",  "#ffdaad",  "#ffeaf9",   "#fff799",  "#ffee9b",  "#ffeff2"}, 
  { "#ffffcc",  "#fff2c8",  "#ffdfc8",  "#fdefff",   "#fffacc",  "#fff5cd",  "#fff6f7"}, 
  { "#ffffff",  "#fffafa",  "#ffe8ef",  "#f4f0ff",   "#ffffff",  "#ffffff",  "#ffffff"},
  { "#000000",  "#000000",  "#000000",  "#000000",   "#000000",  "#000000",  "#000000"}  // The final color (black) -- not part of the color pallet
};


/** Color scheme known as icp_uO_BrBu_10 (Brown to Blue, 10 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BrBu_10[13]       = {        "d", "#000000", "#662f00", "#996035", "#cc9b7a", "#d8af97", "#f2dacd", "#ccfdff", "#99f8ff", "#65efff", "#32e3ff", "#00a9cc", "#ffffff" };

/** Color scheme known as icp_uO_BrBu_12 (Brown to Blue, 12 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BrBu_12[15]       = {        "f", "#000000", "#331900", "#662f00", "#996035", "#cc9b7a", "#d8af97", "#f2dacd", "#ccfdff", "#99f8ff", "#65efff", "#32e3ff", "#00a9cc", "#007a99", "#ffffff" };

/** Color scheme known as icp_uO_BuDOr_12 (Blue to Dark Orange, 12 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BuDOr_12[15]      = {        "f", "#000000", "#1e8e99", "#51c3cc", "#99f9ff", "#b2fcff", "#ccfeff", "#e5ffff", "#ffe5cc", "#ffca99", "#ffad65", "#ff8e32", "#cc5800", "#993f00", "#ffffff" };

/** Color scheme known as icp_uO_BuDOr_18 (Blue to Dark Orange, 18 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BuDOr_18[21]      = {       "15", "#000000", "#006666", "#009999", "#00cccc", "#00ffff", "#33ffff", "#65ffff", "#99ffff", "#b2ffff", "#cbffff", "#e5ffff", "#ffe5cb", "#ffca99", "#ffad65", "#ff8e33", "#ff6e00", "#cc5500", "#993d00", "#662700", "#ffffff" };

/** Color scheme known as icp_uO_BuDRd_12 (Dark Red to Blue, 12 steps, based on ColorBrewer RdYlBu_11) from U of Oregon (Dept of geography) */
const char *icp_uO_BuDRd_12[15]      = {        "f", "#000000", "#290ad8", "#264dff", "#3fa0ff", "#72d9ff", "#aaf7ff", "#e0ffff", "#ffffbf", "#ffe099", "#ffad72", "#f76d5e", "#d82632", "#a50021", "#ffffff" };

/** Color scheme known as icp_uO_BuDRd_18 (Dark Red to Blue, 18 steps, based on ColorBrewer RdYlBu_11) from U of Oregon (Dept of geography) */
const char *icp_uO_BuDRd_18[21]      = {       "15", "#000000", "#2400d8", "#181cf7", "#2857ff", "#3d87ff", "#56b0ff", "#75d3ff", "#99eaff", "#bcf9ff", "#eaffff", "#ffffea", "#fff1bc", "#ffd699", "#ffac75", "#ff7856", "#ff3d3d", "#f72735", "#d8152f", "#a50021", "#ffffff" };

/** Color scheme known as icp_uO_BuGr_14 (Blue-Green) from U of Oregon (Dept of geography) */
const char *icp_uO_BuGr_14[17]       = {       "11", "#000000", "#0000ff", "#3333ff", "#6565ff", "#9999ff", "#b2b2ff", "#cbcbff", "#e5e5ff", "#e5ffe5", "#cbffcb", "#b2ffb2", "#99ff99", "#65ff65", "#33ff33", "#00ff00", "#ffffff" };

/** Color scheme known as icp_uO_BuGy_8 (Blue to Gray, 8 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BuGy_8[11]        = {        "b", "#000000", "#0099cc", "#66e5ff", "#99ffff", "#ccffff", "#e5e5e5", "#999999", "#666666", "#333333", "#ffffff" };

/** Color scheme known as icp_uO_BuOrR_14 (Blue to Orange Red, 14 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BuOrR_14[17]      = {       "11", "#000000", "#075aff", "#3276ff", "#5990ff", "#8cb2ff", "#bfd4ff", "#e5eeff", "#f7f9ff", "#ffffcc", "#ffff99", "#ffff00", "#ffcc00", "#ff9900", "#ff6600", "#ff0000", "#ffffff" };

/** Color scheme known as icp_uO_BuOr_12 (Blue to Orange, 12 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BuOr_12[15]       = {        "f", "#000000", "#002aff", "#1965ff", "#3299ff", "#65ccff", "#99edff", "#ccffff", "#ffffcc", "#ffee99", "#ffcc65", "#ff9932", "#ff6619", "#ff2a00", "#ffffff" };

/** Color scheme known as icp_uO_BuOr_8 (Blue to Orange, 8 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_BuOr_8[11]        = {        "b", "#000000", "#007fff", "#4cc3ff", "#99edff", "#ccffff", "#ffffcc", "#ffee99", "#ffc34c", "#ff7f00", "#ffffff" };

/** Color scheme known as icp_uO_Bu_10 (Light blue to dark blue, 10 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_Bu_10[13]         = {        "d", "#000000", "#e5ffff", "#ccfaff", "#b2f2ff", "#99e5ff", "#7fd4ff", "#65bfff", "#4ca5ff", "#3288ff", "#1965ff", "#003fff", "#ffffff" };

/** Color scheme known as icp_uO_Bu_7 (Light Blue to Dark Blue, 7 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_Bu_7[10]          = {        "a", "#000000", "#ffff00", "#fdff00", "#f8ff00", "#f0ff00", "#e4ff00", "#aacc00", "#7a9900", "#ffffff" };

/** Color scheme known as icp_uO_Cat_12 (Categorical 12-step scheme, after ColorBrewer 11-step Paired Scheme) from U of Oregon (Dept of geography) */
const char *icp_uO_Cat_12[15]        = {        "f", "#000000", "#ffbf7f", "#ff7f00", "#ffff99", "#ffff32", "#b2ff8c", "#32ff00", "#a5edff", "#19b2ff", "#ccbfff", "#654cff", "#ff99bf", "#e51932", "#ffffff" };

/** Color scheme known as icp_uO_GrMg_16 (Green to Magenta, 16 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_GrMg_16[19]       = {       "13", "#000000", "#005000", "#008600", "#00bb00", "#00f100", "#50ff50", "#86ff86", "#bbffbb", "#ffffff", "#fff1ff", "#ffbbff", "#ff86ff", "#ff50ff", "#f100f1", "#bb00bb", "#860086", "#500050", "#ffffff" };

/** Color scheme known as icp_uO_RdYlBu_11b (RdYlBu_11b (Hue fixed for protans, after ColorBrewer RdYlBu)) from U of Oregon (Dept of geography) */
const char *icp_uO_RdYlBu_11b[14]    = {        "e", "#000000", "#a50021", "#d82632", "#f76d5e", "#ffad72", "#ffe099", "#ffffbf", "#e0ffff", "#aaf7ff", "#72d8ff", "#3fa0ff", "#264cff", "#ffffff" };

/** Color scheme known as icp_uO_StepSeq_25 (Stepped sequential scheme, 5 steps) from U of Oregon (Dept of geography) */
const char *icp_uO_StepSeq_25[28]    = {       "1c", "#000000", "#990f0f", "#b22c2c", "#cc5151", "#e57e7e", "#ffb2b2", "#99540f", "#b26f2c", "#cc8e51", "#e5b17e", "#ffd8b2", "#6b990f", "#85b22c", "#a3cc51", "#c3e57e", "#e5ffb2", "#0f6b99", "#2c85b2", "#51a3cc", "#7ec3e5", "#b2e5ff", "#260f99", "#422cb2", "#6551cc", "#8f7ee5", "#bfb2ff", "#ffffff" };

/** Color scheme known as icp_CB_Accent_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Accent_03[6]      = {        "6", "#000000", "#7fc97f", "#beaed4", "#fdc086", "#ffffff" };

/** Color scheme known as icp_CB_Accent_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Accent_04[7]      = {        "7", "#000000", "#7fc97f", "#beaed4", "#fdc086", "#ffff99", "#ffffff" };

/** Color scheme known as icp_CB_Accent_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Accent_05[8]      = {        "8", "#000000", "#7fc97f", "#beaed4", "#fdc086", "#ffff99", "#386cb0", "#ffffff" };

/** Color scheme known as icp_CB_Accent_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Accent_06[9]      = {        "9", "#000000", "#7fc97f", "#beaed4", "#fdc086", "#ffff99", "#386cb0", "#f0027f", "#ffffff" };

/** Color scheme known as icp_CB_Accent_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Accent_07[10]     = {        "a", "#000000", "#7fc97f", "#beaed4", "#fdc086", "#ffff99", "#386cb0", "#f0027f", "#bf5b17", "#ffffff" };

/** Color scheme known as icp_CB_Accent_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Accent_08[11]     = {        "b", "#000000", "#7fc97f", "#beaed4", "#fdc086", "#ffff99", "#386cb0", "#f0027f", "#bf5b17", "#666666", "#ffffff" };

/** Color scheme known as icp_CB_Blues_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_03[6]       = {        "6", "#000000", "#deebf7", "#9ecae1", "#3182bd", "#ffffff" };

/** Color scheme known as icp_CB_Blues_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_04[7]       = {        "7", "#000000", "#eff3ff", "#bdd7e7", "#6baed6", "#2171b5", "#ffffff" };

/** Color scheme known as icp_CB_Blues_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_05[8]       = {        "8", "#000000", "#eff3ff", "#bdd7e7", "#6baed6", "#3182bd", "#08519c", "#ffffff" };

/** Color scheme known as icp_CB_Blues_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_06[9]       = {        "9", "#000000", "#eff3ff", "#c6dbef", "#9ecae1", "#6baed6", "#3182bd", "#08519c", "#ffffff" };

/** Color scheme known as icp_CB_Blues_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_07[10]      = {        "a", "#000000", "#eff3ff", "#c6dbef", "#9ecae1", "#6baed6", "#4292c6", "#2171b5", "#084594", "#ffffff" };

/** Color scheme known as icp_CB_Blues_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_08[11]      = {        "b", "#000000", "#f7fbff", "#deebf7", "#c6dbef", "#9ecae1", "#6baed6", "#4292c6", "#2171b5", "#084594", "#ffffff" };

/** Color scheme known as icp_CB_Blues_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Blues_09[12]      = {        "c", "#000000", "#f7fbff", "#deebf7", "#c6dbef", "#9ecae1", "#6baed6", "#4292c6", "#2171b5", "#08519c", "#08306b", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_03[6]        = {        "6", "#000000", "#d8b365", "#f5f5f5", "#5ab4ac", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_04[7]        = {        "7", "#000000", "#a6611a", "#dfc27d", "#80cdc1", "#018571", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_05[8]        = {        "8", "#000000", "#a6611a", "#dfc27d", "#f5f5f5", "#80cdc1", "#018571", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_06[9]        = {        "9", "#000000", "#8c510a", "#d8b365", "#f6e8c3", "#c7eae5", "#5ab4ac", "#01665e", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_07[10]       = {        "a", "#000000", "#8c510a", "#d8b365", "#f6e8c3", "#f5f5f5", "#c7eae5", "#5ab4ac", "#01665e", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_08[11]       = {        "b", "#000000", "#8c510a", "#bf812d", "#dfc27d", "#f6e8c3", "#c7eae5", "#80cdc1", "#35978f", "#01665e", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_09[12]       = {        "c", "#000000", "#8c510a", "#bf812d", "#dfc27d", "#f6e8c3", "#f5f5f5", "#c7eae5", "#80cdc1", "#35978f", "#01665e", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_10[13]       = {        "d", "#000000", "#543005", "#8c510a", "#bf812d", "#dfc27d", "#f6e8c3", "#c7eae5", "#80cdc1", "#35978f", "#01665e", "#003c30", "#ffffff" };

/** Color scheme known as icp_CB_BrBG_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_BrBG_11[14]       = {        "e", "#000000", "#543005", "#8c510a", "#bf812d", "#dfc27d", "#f6e8c3", "#f5f5f5", "#c7eae5", "#80cdc1", "#35978f", "#01665e", "#003c30", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_03[6]        = {        "6", "#000000", "#e5f5f9", "#99d8c9", "#2ca25f", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_04[7]        = {        "7", "#000000", "#edf8fb", "#b2e2e2", "#66c2a4", "#238b45", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_05[8]        = {        "8", "#000000", "#edf8fb", "#b2e2e2", "#66c2a4", "#2ca25f", "#006d2c", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_06[9]        = {        "9", "#000000", "#edf8fb", "#ccece6", "#99d8c9", "#66c2a4", "#2ca25f", "#006d2c", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_07[10]       = {        "a", "#000000", "#edf8fb", "#ccece6", "#99d8c9", "#66c2a4", "#41ae76", "#238b45", "#005824", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_08[11]       = {        "b", "#000000", "#f7fcfd", "#e5f5f9", "#ccece6", "#99d8c9", "#66c2a4", "#41ae76", "#238b45", "#005824", "#ffffff" };

/** Color scheme known as icp_CB_BuGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuGn_09[12]       = {        "c", "#000000", "#f7fcfd", "#e5f5f9", "#ccece6", "#99d8c9", "#66c2a4", "#41ae76", "#238b45", "#006d2c", "#00441b", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_03[6]        = {        "6", "#000000", "#e0ecf4", "#9ebcda", "#8856a7", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_04[7]        = {        "7", "#000000", "#edf8fb", "#b3cde3", "#8c96c6", "#88419d", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_05[8]        = {        "8", "#000000", "#edf8fb", "#b3cde3", "#8c96c6", "#8856a7", "#810f7c", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_06[9]        = {        "9", "#000000", "#edf8fb", "#bfd3e6", "#9ebcda", "#8c96c6", "#8856a7", "#810f7c", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_07[10]       = {        "a", "#000000", "#edf8fb", "#bfd3e6", "#9ebcda", "#8c96c6", "#8c6bb1", "#88419d", "#6e016b", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_08[11]       = {        "b", "#000000", "#f7fcfd", "#e0ecf4", "#bfd3e6", "#9ebcda", "#8c96c6", "#8c6bb1", "#88419d", "#6e016b", "#ffffff" };

/** Color scheme known as icp_CB_BuPu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_BuPu_09[12]       = {        "c", "#000000", "#f7fcfd", "#e0ecf4", "#bfd3e6", "#9ebcda", "#8c96c6", "#8c6bb1", "#88419d", "#810f7c", "#4d004b", "#ffffff" };

/** Color scheme known as icp_CB_Dark2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Dark2_03[6]       = {        "6", "#000000", "#1b9e77", "#d95f02", "#7570b3", "#ffffff" };

/** Color scheme known as icp_CB_Dark2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Dark2_04[7]       = {        "7", "#000000", "#1b9e77", "#d95f02", "#7570b3", "#e7298a", "#ffffff" };

/** Color scheme known as icp_CB_Dark2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Dark2_05[8]       = {        "8", "#000000", "#1b9e77", "#d95f02", "#7570b3", "#e7298a", "#66a61e", "#ffffff" };

/** Color scheme known as icp_CB_Dark2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Dark2_06[9]       = {        "9", "#000000", "#1b9e77", "#d95f02", "#7570b3", "#e7298a", "#66a61e", "#e6ab02", "#ffffff" };

/** Color scheme known as icp_CB_Dark2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Dark2_07[10]      = {        "a", "#000000", "#1b9e77", "#d95f02", "#7570b3", "#e7298a", "#66a61e", "#e6ab02", "#a6761d", "#ffffff" };

/** Color scheme known as icp_CB_Dark2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Dark2_08[11]      = {        "b", "#000000", "#1b9e77", "#d95f02", "#7570b3", "#e7298a", "#66a61e", "#e6ab02", "#a6761d", "#666666", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_03[6]        = {        "6", "#000000", "#e0f3db", "#a8ddb5", "#43a2ca", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_04[7]        = {        "7", "#000000", "#f0f9e8", "#bae4bc", "#7bccc4", "#2b8cbe", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_05[8]        = {        "8", "#000000", "#f0f9e8", "#bae4bc", "#7bccc4", "#43a2ca", "#0868ac", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_06[9]        = {        "9", "#000000", "#f0f9e8", "#ccebc5", "#a8ddb5", "#7bccc4", "#43a2ca", "#0868ac", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_07[10]       = {        "a", "#000000", "#f0f9e8", "#ccebc5", "#a8ddb5", "#7bccc4", "#4eb3d3", "#2b8cbe", "#08589e", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_08[11]       = {        "b", "#000000", "#f7fcf0", "#e0f3db", "#ccebc5", "#a8ddb5", "#7bccc4", "#4eb3d3", "#2b8cbe", "#08589e", "#ffffff" };

/** Color scheme known as icp_CB_GnBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_GnBu_09[12]       = {        "c", "#000000", "#f7fcf0", "#e0f3db", "#ccebc5", "#a8ddb5", "#7bccc4", "#4eb3d3", "#2b8cbe", "#0868ac", "#084081", "#ffffff" };

/** Color scheme known as icp_CB_Greens_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_03[6]      = {        "6", "#000000", "#e5f5e0", "#a1d99b", "#31a354", "#ffffff" };

/** Color scheme known as icp_CB_Greens_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_04[7]      = {        "7", "#000000", "#edf8e9", "#bae4b3", "#74c476", "#238b45", "#ffffff" };

/** Color scheme known as icp_CB_Greens_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_05[8]      = {        "8", "#000000", "#edf8e9", "#bae4b3", "#74c476", "#31a354", "#006d2c", "#ffffff" };

/** Color scheme known as icp_CB_Greens_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_06[9]      = {        "9", "#000000", "#edf8e9", "#c7e9c0", "#a1d99b", "#74c476", "#31a354", "#006d2c", "#ffffff" };

/** Color scheme known as icp_CB_Greens_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_07[10]     = {        "a", "#000000", "#edf8e9", "#c7e9c0", "#a1d99b", "#74c476", "#41ab5d", "#238b45", "#005a32", "#ffffff" };

/** Color scheme known as icp_CB_Greens_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_08[11]     = {        "b", "#000000", "#f7fcf5", "#e5f5e0", "#c7e9c0", "#a1d99b", "#74c476", "#41ab5d", "#238b45", "#005a32", "#ffffff" };

/** Color scheme known as icp_CB_Greens_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greens_09[12]     = {        "c", "#000000", "#f7fcf5", "#e5f5e0", "#c7e9c0", "#a1d99b", "#74c476", "#41ab5d", "#238b45", "#006d2c", "#00441b", "#ffffff" };

/** Color scheme known as icp_CB_Greys_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_03[6]       = {        "6", "#000000", "#f0f0f0", "#bdbdbd", "#636363", "#ffffff" };

/** Color scheme known as icp_CB_Greys_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_04[7]       = {        "7", "#000000", "#f7f7f7", "#cccccc", "#969696", "#525252", "#ffffff" };

/** Color scheme known as icp_CB_Greys_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_05[8]       = {        "8", "#000000", "#f7f7f7", "#cccccc", "#969696", "#636363", "#252525", "#ffffff" };

/** Color scheme known as icp_CB_Greys_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_06[9]       = {        "9", "#000000", "#f7f7f7", "#d9d9d9", "#bdbdbd", "#969696", "#636363", "#252525", "#ffffff" };

/** Color scheme known as icp_CB_Greys_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_07[10]      = {        "a", "#000000", "#f7f7f7", "#d9d9d9", "#bdbdbd", "#969696", "#737373", "#525252", "#252525", "#ffffff" };

/** Color scheme known as icp_CB_Greys_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_08[11]      = {        "b", "#000000", "#ffffff", "#f0f0f0", "#d9d9d9", "#bdbdbd", "#969696", "#737373", "#525252", "#252525", "#ffffff" };

/** Color scheme known as icp_CB_Greys_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Greys_09[12]      = {        "c", "#000000", "#ffffff", "#f0f0f0", "#d9d9d9", "#bdbdbd", "#969696", "#737373", "#525252", "#252525", "#000000", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_03[6]        = {        "6", "#000000", "#fee8c8", "#fdbb84", "#e34a33", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_04[7]        = {        "7", "#000000", "#fef0d9", "#fdcc8a", "#fc8d59", "#d7301f", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_05[8]        = {        "8", "#000000", "#fef0d9", "#fdcc8a", "#fc8d59", "#e34a33", "#b30000", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_06[9]        = {        "9", "#000000", "#fef0d9", "#fdd49e", "#fdbb84", "#fc8d59", "#e34a33", "#b30000", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_07[10]       = {        "a", "#000000", "#fef0d9", "#fdd49e", "#fdbb84", "#fc8d59", "#ef6548", "#d7301f", "#990000", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_08[11]       = {        "b", "#000000", "#fff7ec", "#fee8c8", "#fdd49e", "#fdbb84", "#fc8d59", "#ef6548", "#d7301f", "#990000", "#ffffff" };

/** Color scheme known as icp_CB_OrRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_OrRd_09[12]       = {        "c", "#000000", "#fff7ec", "#fee8c8", "#fdd49e", "#fdbb84", "#fc8d59", "#ef6548", "#d7301f", "#b30000", "#7f0000", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_03[6]     = {        "6", "#000000", "#fee6ce", "#fdae6b", "#e6550d", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_04[7]     = {        "7", "#000000", "#feedde", "#fdbe85", "#fd8d3c", "#d94701", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_05[8]     = {        "8", "#000000", "#feedde", "#fdbe85", "#fd8d3c", "#e6550d", "#a63603", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_06[9]     = {        "9", "#000000", "#feedde", "#fdd0a2", "#fdae6b", "#fd8d3c", "#e6550d", "#a63603", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_07[10]    = {        "a", "#000000", "#feedde", "#fdd0a2", "#fdae6b", "#fd8d3c", "#f16913", "#d94801", "#8c2d04", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_08[11]    = {        "b", "#000000", "#fff5eb", "#fee6ce", "#fdd0a2", "#fdae6b", "#fd8d3c", "#f16913", "#d94801", "#8c2d04", "#ffffff" };

/** Color scheme known as icp_CB_Oranges_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Oranges_09[12]    = {        "c", "#000000", "#fff5eb", "#fee6ce", "#fdd0a2", "#fdae6b", "#fd8d3c", "#f16913", "#d94801", "#a63603", "#7f2704", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_03[6]        = {        "6", "#000000", "#af8dc3", "#f7f7f7", "#7fbf7b", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_04[7]        = {        "7", "#000000", "#7b3294", "#c2a5cf", "#a6dba0", "#008837", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_05[8]        = {        "8", "#000000", "#7b3294", "#c2a5cf", "#f7f7f7", "#a6dba0", "#008837", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_06[9]        = {        "9", "#000000", "#762a83", "#af8dc3", "#e7d4e8", "#d9f0d3", "#7fbf7b", "#1b7837", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_07[10]       = {        "a", "#000000", "#762a83", "#af8dc3", "#e7d4e8", "#f7f7f7", "#d9f0d3", "#7fbf7b", "#1b7837", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_08[11]       = {        "b", "#000000", "#762a83", "#9970ab", "#c2a5cf", "#e7d4e8", "#d9f0d3", "#a6dba0", "#5aae61", "#1b7837", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_09[12]       = {        "c", "#000000", "#762a83", "#9970ab", "#c2a5cf", "#e7d4e8", "#f7f7f7", "#d9f0d3", "#a6dba0", "#5aae61", "#1b7837", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_10[13]       = {        "d", "#000000", "#40004b", "#762a83", "#9970ab", "#c2a5cf", "#e7d4e8", "#d9f0d3", "#a6dba0", "#5aae61", "#1b7837", "#00441b", "#ffffff" };

/** Color scheme known as icp_CB_PRGn_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PRGn_11[14]       = {        "e", "#000000", "#40004b", "#762a83", "#9970ab", "#c2a5cf", "#e7d4e8", "#f7f7f7", "#d9f0d3", "#a6dba0", "#5aae61", "#1b7837", "#00441b", "#ffffff" };

/** Color scheme known as icp_CB_Paired_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_03[6]      = {        "6", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#ffffff" };

/** Color scheme known as icp_CB_Paired_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_04[7]      = {        "7", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#ffffff" };

/** Color scheme known as icp_CB_Paired_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_05[8]      = {        "8", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#ffffff" };

/** Color scheme known as icp_CB_Paired_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_06[9]      = {        "9", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#ffffff" };

/** Color scheme known as icp_CB_Paired_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_07[10]     = {        "a", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#fdbf6f", "#ffffff" };

/** Color scheme known as icp_CB_Paired_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_08[11]     = {        "b", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#fdbf6f", "#ff7f00", "#ffffff" };

/** Color scheme known as icp_CB_Paired_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_09[12]     = {        "c", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#fdbf6f", "#ff7f00", "#cab2d6", "#ffffff" };

/** Color scheme known as icp_CB_Paired_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_10[13]     = {        "d", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#fdbf6f", "#ff7f00", "#cab2d6", "#6a3d9a", "#ffffff" };

/** Color scheme known as icp_CB_Paired_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_11[14]     = {        "e", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#fdbf6f", "#ff7f00", "#cab2d6", "#6a3d9a", "#ffff99", "#ffffff" };

/** Color scheme known as icp_CB_Paired_12 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Paired_12[15]     = {        "f", "#000000", "#a6cee3", "#1f78b4", "#b2df8a", "#33a02c", "#fb9a99", "#e31a1c", "#fdbf6f", "#ff7f00", "#cab2d6", "#6a3d9a", "#ffff99", "#b15928", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_03[6]     = {        "6", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_04[7]     = {        "7", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#decbe4", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_05[8]     = {        "8", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#decbe4", "#fed9a6", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_06[9]     = {        "9", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#decbe4", "#fed9a6", "#ffffcc", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_07[10]    = {        "a", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#decbe4", "#fed9a6", "#ffffcc", "#e5d8bd", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_08[11]    = {        "b", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#decbe4", "#fed9a6", "#ffffcc", "#e5d8bd", "#fddaec", "#ffffff" };

/** Color scheme known as icp_CB_Pastel1_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel1_09[12]    = {        "c", "#000000", "#fbb4ae", "#b3cde3", "#ccebc5", "#decbe4", "#fed9a6", "#ffffcc", "#e5d8bd", "#fddaec", "#f2f2f2", "#ffffff" };

/** Color scheme known as icp_CB_Pastel2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel2_03[6]     = {        "6", "#000000", "#b3e2cd", "#fdcdac", "#cbd5e8", "#ffffff" };

/** Color scheme known as icp_CB_Pastel2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel2_04[7]     = {        "7", "#000000", "#b3e2cd", "#fdcdac", "#cbd5e8", "#f4cae4", "#ffffff" };

/** Color scheme known as icp_CB_Pastel2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel2_05[8]     = {        "8", "#000000", "#b3e2cd", "#fdcdac", "#cbd5e8", "#f4cae4", "#e6f5c9", "#ffffff" };

/** Color scheme known as icp_CB_Pastel2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel2_06[9]     = {        "9", "#000000", "#b3e2cd", "#fdcdac", "#cbd5e8", "#f4cae4", "#e6f5c9", "#fff2ae", "#ffffff" };

/** Color scheme known as icp_CB_Pastel2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel2_07[10]    = {        "a", "#000000", "#b3e2cd", "#fdcdac", "#cbd5e8", "#f4cae4", "#e6f5c9", "#fff2ae", "#f1e2cc", "#ffffff" };

/** Color scheme known as icp_CB_Pastel2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Pastel2_08[11]    = {        "b", "#000000", "#b3e2cd", "#fdcdac", "#cbd5e8", "#f4cae4", "#e6f5c9", "#fff2ae", "#f1e2cc", "#cccccc", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_03[6]        = {        "6", "#000000", "#e9a3c9", "#f7f7f7", "#a1d76a", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_04[7]        = {        "7", "#000000", "#d01c8b", "#f1b6da", "#b8e186", "#4dac26", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_05[8]        = {        "8", "#000000", "#d01c8b", "#f1b6da", "#f7f7f7", "#b8e186", "#4dac26", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_06[9]        = {        "9", "#000000", "#c51b7d", "#e9a3c9", "#fde0ef", "#e6f5d0", "#a1d76a", "#4d9221", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_07[10]       = {        "a", "#000000", "#c51b7d", "#e9a3c9", "#fde0ef", "#f7f7f7", "#e6f5d0", "#a1d76a", "#4d9221", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_08[11]       = {        "b", "#000000", "#c51b7d", "#de77ae", "#f1b6da", "#fde0ef", "#e6f5d0", "#b8e186", "#7fbc41", "#4d9221", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_09[12]       = {        "c", "#000000", "#c51b7d", "#de77ae", "#f1b6da", "#fde0ef", "#f7f7f7", "#e6f5d0", "#b8e186", "#7fbc41", "#4d9221", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_10[13]       = {        "d", "#000000", "#8e0152", "#c51b7d", "#de77ae", "#f1b6da", "#fde0ef", "#e6f5d0", "#b8e186", "#7fbc41", "#4d9221", "#276419", "#ffffff" };

/** Color scheme known as icp_CB_PiYG_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PiYG_11[14]       = {        "e", "#000000", "#8e0152", "#c51b7d", "#de77ae", "#f1b6da", "#fde0ef", "#f7f7f7", "#e6f5d0", "#b8e186", "#7fbc41", "#4d9221", "#276419", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_03[6]      = {        "6", "#000000", "#ece2f0", "#a6bddb", "#1c9099", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_04[7]      = {        "7", "#000000", "#f6eff7", "#bdc9e1", "#67a9cf", "#02818a", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_05[8]      = {        "8", "#000000", "#f6eff7", "#bdc9e1", "#67a9cf", "#1c9099", "#016c59", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_06[9]      = {        "9", "#000000", "#f6eff7", "#d0d1e6", "#a6bddb", "#67a9cf", "#1c9099", "#016c59", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_07[10]     = {        "a", "#000000", "#f6eff7", "#d0d1e6", "#a6bddb", "#67a9cf", "#3690c0", "#02818a", "#016450", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_08[11]     = {        "b", "#000000", "#fff7fb", "#ece2f0", "#d0d1e6", "#a6bddb", "#67a9cf", "#3690c0", "#02818a", "#016450", "#ffffff" };

/** Color scheme known as icp_CB_PuBuGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBuGn_09[12]     = {        "c", "#000000", "#fff7fb", "#ece2f0", "#d0d1e6", "#a6bddb", "#67a9cf", "#3690c0", "#02818a", "#016c59", "#014636", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_03[6]        = {        "6", "#000000", "#ece7f2", "#a6bddb", "#2b8cbe", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_04[7]        = {        "7", "#000000", "#f1eef6", "#bdc9e1", "#74a9cf", "#0570b0", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_05[8]        = {        "8", "#000000", "#f1eef6", "#bdc9e1", "#74a9cf", "#2b8cbe", "#045a8d", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_06[9]        = {        "9", "#000000", "#f1eef6", "#d0d1e6", "#a6bddb", "#74a9cf", "#2b8cbe", "#045a8d", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_07[10]       = {        "a", "#000000", "#f1eef6", "#d0d1e6", "#a6bddb", "#74a9cf", "#3690c0", "#0570b0", "#034e7b", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_08[11]       = {        "b", "#000000", "#fff7fb", "#ece7f2", "#d0d1e6", "#a6bddb", "#74a9cf", "#3690c0", "#0570b0", "#034e7b", "#ffffff" };

/** Color scheme known as icp_CB_PuBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuBu_09[12]       = {        "c", "#000000", "#fff7fb", "#ece7f2", "#d0d1e6", "#a6bddb", "#74a9cf", "#3690c0", "#0570b0", "#045a8d", "#023858", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_03[6]        = {        "6", "#000000", "#f1a340", "#f7f7f7", "#998ec3", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_04[7]        = {        "7", "#000000", "#e66101", "#fdb863", "#b2abd2", "#5e3c99", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_05[8]        = {        "8", "#000000", "#e66101", "#fdb863", "#f7f7f7", "#b2abd2", "#5e3c99", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_06[9]        = {        "9", "#000000", "#b35806", "#f1a340", "#fee0b6", "#d8daeb", "#998ec3", "#542788", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_07[10]       = {        "a", "#000000", "#b35806", "#f1a340", "#fee0b6", "#f7f7f7", "#d8daeb", "#998ec3", "#542788", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_08[11]       = {        "b", "#000000", "#b35806", "#e08214", "#fdb863", "#fee0b6", "#d8daeb", "#b2abd2", "#8073ac", "#542788", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_09[12]       = {        "c", "#000000", "#b35806", "#e08214", "#fdb863", "#fee0b6", "#f7f7f7", "#d8daeb", "#b2abd2", "#8073ac", "#542788", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_10[13]       = {        "d", "#000000", "#7f3b08", "#b35806", "#e08214", "#fdb863", "#fee0b6", "#d8daeb", "#b2abd2", "#8073ac", "#542788", "#2d004b", "#ffffff" };

/** Color scheme known as icp_CB_PuOr_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_PuOr_11[14]       = {        "e", "#000000", "#7f3b08", "#b35806", "#e08214", "#fdb863", "#fee0b6", "#f7f7f7", "#d8daeb", "#b2abd2", "#8073ac", "#542788", "#2d004b", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_03[6]        = {        "6", "#000000", "#e7e1ef", "#c994c7", "#dd1c77", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_04[7]        = {        "7", "#000000", "#f1eef6", "#d7b5d8", "#df65b0", "#ce1256", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_05[8]        = {        "8", "#000000", "#f1eef6", "#d7b5d8", "#df65b0", "#dd1c77", "#980043", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_06[9]        = {        "9", "#000000", "#f1eef6", "#d4b9da", "#c994c7", "#df65b0", "#dd1c77", "#980043", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_07[10]       = {        "a", "#000000", "#f1eef6", "#d4b9da", "#c994c7", "#df65b0", "#e7298a", "#ce1256", "#91003f", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_08[11]       = {        "b", "#000000", "#f7f4f9", "#e7e1ef", "#d4b9da", "#c994c7", "#df65b0", "#e7298a", "#ce1256", "#91003f", "#ffffff" };

/** Color scheme known as icp_CB_PuRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_PuRd_09[12]       = {        "c", "#000000", "#f7f4f9", "#e7e1ef", "#d4b9da", "#c994c7", "#df65b0", "#e7298a", "#ce1256", "#980043", "#67001f", "#ffffff" };

/** Color scheme known as icp_CB_Purples_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_03[6]     = {        "6", "#000000", "#efedf5", "#bcbddc", "#756bb1", "#ffffff" };

/** Color scheme known as icp_CB_Purples_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_04[7]     = {        "7", "#000000", "#f2f0f7", "#cbc9e2", "#9e9ac8", "#6a51a3", "#ffffff" };

/** Color scheme known as icp_CB_Purples_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_05[8]     = {        "8", "#000000", "#f2f0f7", "#cbc9e2", "#9e9ac8", "#756bb1", "#54278f", "#ffffff" };

/** Color scheme known as icp_CB_Purples_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_06[9]     = {        "9", "#000000", "#f2f0f7", "#dadaeb", "#bcbddc", "#9e9ac8", "#756bb1", "#54278f", "#ffffff" };

/** Color scheme known as icp_CB_Purples_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_07[10]    = {        "a", "#000000", "#f2f0f7", "#dadaeb", "#bcbddc", "#9e9ac8", "#807dba", "#6a51a3", "#4a1486", "#ffffff" };

/** Color scheme known as icp_CB_Purples_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_08[11]    = {        "b", "#000000", "#fcfbfd", "#efedf5", "#dadaeb", "#bcbddc", "#9e9ac8", "#807dba", "#6a51a3", "#4a1486", "#ffffff" };

/** Color scheme known as icp_CB_Purples_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Purples_09[12]    = {        "c", "#000000", "#fcfbfd", "#efedf5", "#dadaeb", "#bcbddc", "#9e9ac8", "#807dba", "#6a51a3", "#54278f", "#3f007d", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_03[6]        = {        "6", "#000000", "#ef8a62", "#f7f7f7", "#67a9cf", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_04[7]        = {        "7", "#000000", "#ca0020", "#f4a582", "#92c5de", "#0571b0", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_05[8]        = {        "8", "#000000", "#ca0020", "#f4a582", "#f7f7f7", "#92c5de", "#0571b0", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_06[9]        = {        "9", "#000000", "#b2182b", "#ef8a62", "#fddbc7", "#d1e5f0", "#67a9cf", "#2166ac", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_07[10]       = {        "a", "#000000", "#b2182b", "#ef8a62", "#fddbc7", "#f7f7f7", "#d1e5f0", "#67a9cf", "#2166ac", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_08[11]       = {        "b", "#000000", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_09[12]       = {        "c", "#000000", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#f7f7f7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_10[13]       = {        "d", "#000000", "#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#053061", "#ffffff" };

/** Color scheme known as icp_CB_RdBu_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdBu_11[14]       = {        "e", "#000000", "#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#f7f7f7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#053061", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_03[6]        = {        "6", "#000000", "#ef8a62", "#ffffff", "#999999", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_04[7]        = {        "7", "#000000", "#ca0020", "#f4a582", "#bababa", "#404040", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_05[8]        = {        "8", "#000000", "#ca0020", "#f4a582", "#ffffff", "#bababa", "#404040", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_06[9]        = {        "9", "#000000", "#b2182b", "#ef8a62", "#fddbc7", "#e0e0e0", "#999999", "#4d4d4d", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_07[10]       = {        "a", "#000000", "#b2182b", "#ef8a62", "#fddbc7", "#ffffff", "#e0e0e0", "#999999", "#4d4d4d", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_08[11]       = {        "b", "#000000", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#e0e0e0", "#bababa", "#878787", "#4d4d4d", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_09[12]       = {        "c", "#000000", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#ffffff", "#e0e0e0", "#bababa", "#878787", "#4d4d4d", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_10[13]       = {        "d", "#000000", "#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#e0e0e0", "#bababa", "#878787", "#4d4d4d", "#1a1a1a", "#ffffff" };

/** Color scheme known as icp_CB_RdGy_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdGy_11[14]       = {        "e", "#000000", "#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#ffffff", "#e0e0e0", "#bababa", "#878787", "#4d4d4d", "#1a1a1a", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_03[6]        = {        "6", "#000000", "#fde0dd", "#fa9fb5", "#c51b8a", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_04[7]        = {        "7", "#000000", "#feebe2", "#fbb4b9", "#f768a1", "#ae017e", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_05[8]        = {        "8", "#000000", "#feebe2", "#fbb4b9", "#f768a1", "#c51b8a", "#7a0177", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_06[9]        = {        "9", "#000000", "#feebe2", "#fcc5c0", "#fa9fb5", "#f768a1", "#c51b8a", "#7a0177", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_07[10]       = {        "a", "#000000", "#feebe2", "#fcc5c0", "#fa9fb5", "#f768a1", "#dd3497", "#ae017e", "#7a0177", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_08[11]       = {        "b", "#000000", "#fff7f3", "#fde0dd", "#fcc5c0", "#fa9fb5", "#f768a1", "#dd3497", "#ae017e", "#7a0177", "#ffffff" };

/** Color scheme known as icp_CB_RdPu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_RdPu_09[12]       = {        "c", "#000000", "#fff7f3", "#fde0dd", "#fcc5c0", "#fa9fb5", "#f768a1", "#dd3497", "#ae017e", "#7a0177", "#49006a", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_03[6]      = {        "6", "#000000", "#fc8d59", "#ffffbf", "#91bfdb", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_04[7]      = {        "7", "#000000", "#d7191c", "#fdae61", "#abd9e9", "#2c7bb6", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_05[8]      = {        "8", "#000000", "#d7191c", "#fdae61", "#ffffbf", "#abd9e9", "#2c7bb6", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_06[9]      = {        "9", "#000000", "#d73027", "#fc8d59", "#fee090", "#e0f3f8", "#91bfdb", "#4575b4", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_07[10]     = {        "a", "#000000", "#d73027", "#fc8d59", "#fee090", "#ffffbf", "#e0f3f8", "#91bfdb", "#4575b4", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_08[11]     = {        "b", "#000000", "#d73027", "#f46d43", "#fdae61", "#fee090", "#e0f3f8", "#abd9e9", "#74add1", "#4575b4", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_09[12]     = {        "c", "#000000", "#d73027", "#f46d43", "#fdae61", "#fee090", "#ffffbf", "#e0f3f8", "#abd9e9", "#74add1", "#4575b4", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_10[13]     = {        "d", "#000000", "#a50026", "#d73027", "#f46d43", "#fdae61", "#fee090", "#e0f3f8", "#abd9e9", "#74add1", "#4575b4", "#313695", "#ffffff" };

/** Color scheme known as icp_CB_RdYlBu_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlBu_11[14]     = {        "e", "#000000", "#a50026", "#d73027", "#f46d43", "#fdae61", "#fee090", "#ffffbf", "#e0f3f8", "#abd9e9", "#74add1", "#4575b4", "#313695", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_03[6]      = {        "6", "#000000", "#fc8d59", "#ffffbf", "#91cf60", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_04[7]      = {        "7", "#000000", "#d7191c", "#fdae61", "#a6d96a", "#1a9641", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_05[8]      = {        "8", "#000000", "#d7191c", "#fdae61", "#ffffbf", "#a6d96a", "#1a9641", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_06[9]      = {        "9", "#000000", "#d73027", "#fc8d59", "#fee08b", "#d9ef8b", "#91cf60", "#1a9850", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_07[10]     = {        "a", "#000000", "#d73027", "#fc8d59", "#fee08b", "#ffffbf", "#d9ef8b", "#91cf60", "#1a9850", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_08[11]     = {        "b", "#000000", "#d73027", "#f46d43", "#fdae61", "#fee08b", "#d9ef8b", "#a6d96a", "#66bd63", "#1a9850", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_09[12]     = {        "c", "#000000", "#d73027", "#f46d43", "#fdae61", "#fee08b", "#ffffbf", "#d9ef8b", "#a6d96a", "#66bd63", "#1a9850", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_10[13]     = {        "d", "#000000", "#a50026", "#d73027", "#f46d43", "#fdae61", "#fee08b", "#d9ef8b", "#a6d96a", "#66bd63", "#1a9850", "#006837", "#ffffff" };

/** Color scheme known as icp_CB_RdYlGn_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_RdYlGn_11[14]     = {        "e", "#000000", "#a50026", "#d73027", "#f46d43", "#fdae61", "#fee08b", "#ffffbf", "#d9ef8b", "#a6d96a", "#66bd63", "#1a9850", "#006837", "#ffffff" };

/** Color scheme known as icp_CB_Reds_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_03[6]        = {        "6", "#000000", "#fee0d2", "#fc9272", "#de2d26", "#ffffff" };

/** Color scheme known as icp_CB_Reds_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_04[7]        = {        "7", "#000000", "#fee5d9", "#fcae91", "#fb6a4a", "#cb181d", "#ffffff" };

/** Color scheme known as icp_CB_Reds_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_05[8]        = {        "8", "#000000", "#fee5d9", "#fcae91", "#fb6a4a", "#de2d26", "#a50f15", "#ffffff" };

/** Color scheme known as icp_CB_Reds_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_06[9]        = {        "9", "#000000", "#fee5d9", "#fcbba1", "#fc9272", "#fb6a4a", "#de2d26", "#a50f15", "#ffffff" };

/** Color scheme known as icp_CB_Reds_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_07[10]       = {        "a", "#000000", "#fee5d9", "#fcbba1", "#fc9272", "#fb6a4a", "#ef3b2c", "#cb181d", "#99000d", "#ffffff" };

/** Color scheme known as icp_CB_Reds_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_08[11]       = {        "b", "#000000", "#fff5f0", "#fee0d2", "#fcbba1", "#fc9272", "#fb6a4a", "#ef3b2c", "#cb181d", "#99000d", "#ffffff" };

/** Color scheme known as icp_CB_Reds_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_Reds_09[12]       = {        "c", "#000000", "#fff5f0", "#fee0d2", "#fcbba1", "#fc9272", "#fb6a4a", "#ef3b2c", "#cb181d", "#a50f15", "#67000d", "#ffffff" };

/** Color scheme known as icp_CB_Set1_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_03[6]        = {        "6", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#ffffff" };

/** Color scheme known as icp_CB_Set1_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_04[7]        = {        "7", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#984ea3", "#ffffff" };

/** Color scheme known as icp_CB_Set1_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_05[8]        = {        "8", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#984ea3", "#ff7f00", "#ffffff" };

/** Color scheme known as icp_CB_Set1_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_06[9]        = {        "9", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#984ea3", "#ff7f00", "#ffff33", "#ffffff" };

/** Color scheme known as icp_CB_Set1_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_07[10]       = {        "a", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#984ea3", "#ff7f00", "#ffff33", "#a65628", "#ffffff" };

/** Color scheme known as icp_CB_Set1_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_08[11]       = {        "b", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#984ea3", "#ff7f00", "#ffff33", "#a65628", "#f781bf", "#ffffff" };

/** Color scheme known as icp_CB_Set1_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set1_09[12]       = {        "c", "#000000", "#e41a1c", "#377eb8", "#4daf4a", "#984ea3", "#ff7f00", "#ffff33", "#a65628", "#f781bf", "#999999", "#ffffff" };

/** Color scheme known as icp_CB_Set2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set2_03[6]        = {        "6", "#000000", "#66c2a5", "#fc8d62", "#8da0cb", "#ffffff" };

/** Color scheme known as icp_CB_Set2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set2_04[7]        = {        "7", "#000000", "#66c2a5", "#fc8d62", "#8da0cb", "#e78ac3", "#ffffff" };

/** Color scheme known as icp_CB_Set2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set2_05[8]        = {        "8", "#000000", "#66c2a5", "#fc8d62", "#8da0cb", "#e78ac3", "#a6d854", "#ffffff" };

/** Color scheme known as icp_CB_Set2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set2_06[9]        = {        "9", "#000000", "#66c2a5", "#fc8d62", "#8da0cb", "#e78ac3", "#a6d854", "#ffd92f", "#ffffff" };

/** Color scheme known as icp_CB_Set2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set2_07[10]       = {        "a", "#000000", "#66c2a5", "#fc8d62", "#8da0cb", "#e78ac3", "#a6d854", "#ffd92f", "#e5c494", "#ffffff" };

/** Color scheme known as icp_CB_Set2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set2_08[11]       = {        "b", "#000000", "#66c2a5", "#fc8d62", "#8da0cb", "#e78ac3", "#a6d854", "#ffd92f", "#e5c494", "#b3b3b3", "#ffffff" };

/** Color scheme known as icp_CB_Set3_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_03[6]        = {        "6", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#ffffff" };

/** Color scheme known as icp_CB_Set3_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_04[7]        = {        "7", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#ffffff" };

/** Color scheme known as icp_CB_Set3_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_05[8]        = {        "8", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#ffffff" };

/** Color scheme known as icp_CB_Set3_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_06[9]        = {        "9", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#ffffff" };

/** Color scheme known as icp_CB_Set3_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_07[10]       = {        "a", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#b3de69", "#ffffff" };

/** Color scheme known as icp_CB_Set3_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_08[11]       = {        "b", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#b3de69", "#fccde5", "#ffffff" };

/** Color scheme known as icp_CB_Set3_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_09[12]       = {        "c", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#b3de69", "#fccde5", "#d9d9d9", "#ffffff" };

/** Color scheme known as icp_CB_Set3_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_10[13]       = {        "d", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#b3de69", "#fccde5", "#d9d9d9", "#bc80bd", "#ffffff" };

/** Color scheme known as icp_CB_Set3_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_11[14]       = {        "e", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#b3de69", "#fccde5", "#d9d9d9", "#bc80bd", "#ccebc5", "#ffffff" };

/** Color scheme known as icp_CB_Set3_12 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
const char *icp_CB_Set3_12[15]       = {        "f", "#000000", "#8dd3c7", "#ffffb3", "#bebada", "#fb8072", "#80b1d3", "#fdb462", "#b3de69", "#fccde5", "#d9d9d9", "#bc80bd", "#ccebc5", "#ffed6f", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_03[6]    = {        "6", "#000000", "#fc8d59", "#ffffbf", "#99d594", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_04[7]    = {        "7", "#000000", "#d7191c", "#fdae61", "#abdda4", "#2b83ba", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_05[8]    = {        "8", "#000000", "#d7191c", "#fdae61", "#ffffbf", "#abdda4", "#2b83ba", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_06[9]    = {        "9", "#000000", "#d53e4f", "#fc8d59", "#fee08b", "#e6f598", "#99d594", "#3288bd", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_07[10]   = {        "a", "#000000", "#d53e4f", "#fc8d59", "#fee08b", "#ffffbf", "#e6f598", "#99d594", "#3288bd", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_08[11]   = {        "b", "#000000", "#d53e4f", "#f46d43", "#fdae61", "#fee08b", "#e6f598", "#abdda4", "#66c2a5", "#3288bd", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_09[12]   = {        "c", "#000000", "#d53e4f", "#f46d43", "#fdae61", "#fee08b", "#ffffbf", "#e6f598", "#abdda4", "#66c2a5", "#3288bd", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_10[13]   = {        "d", "#000000", "#9e0142", "#d53e4f", "#f46d43", "#fdae61", "#fee08b", "#e6f598", "#abdda4", "#66c2a5", "#3288bd", "#5e4fa2", "#ffffff" };

/** Color scheme known as icp_CB_Spectral_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
const char *icp_CB_Spectral_11[14]   = {        "e", "#000000", "#9e0142", "#d53e4f", "#f46d43", "#fdae61", "#fee08b", "#ffffbf", "#e6f598", "#abdda4", "#66c2a5", "#3288bd", "#5e4fa2", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_03[6]      = {        "6", "#000000", "#edf8b1", "#7fcdbb", "#2c7fb8", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_04[7]      = {        "7", "#000000", "#ffffcc", "#a1dab4", "#41b6c4", "#225ea8", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_05[8]      = {        "8", "#000000", "#ffffcc", "#a1dab4", "#41b6c4", "#2c7fb8", "#253494", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_06[9]      = {        "9", "#000000", "#ffffcc", "#c7e9b4", "#7fcdbb", "#41b6c4", "#2c7fb8", "#253494", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_07[10]     = {        "a", "#000000", "#ffffcc", "#c7e9b4", "#7fcdbb", "#41b6c4", "#1d91c0", "#225ea8", "#0c2c84", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_08[11]     = {        "b", "#000000", "#ffffd9", "#edf8b1", "#c7e9b4", "#7fcdbb", "#41b6c4", "#1d91c0", "#225ea8", "#0c2c84", "#ffffff" };

/** Color scheme known as icp_CB_YlGnBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGnBu_09[12]     = {        "c", "#000000", "#ffffd9", "#edf8b1", "#c7e9b4", "#7fcdbb", "#41b6c4", "#1d91c0", "#225ea8", "#253494", "#081d58", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_03[6]        = {        "6", "#000000", "#f7fcb9", "#addd8e", "#31a354", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_04[7]        = {        "7", "#000000", "#ffffcc", "#c2e699", "#78c679", "#238443", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_05[8]        = {        "8", "#000000", "#ffffcc", "#c2e699", "#78c679", "#31a354", "#006837", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_06[9]        = {        "9", "#000000", "#ffffcc", "#d9f0a3", "#addd8e", "#78c679", "#31a354", "#006837", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_07[10]       = {        "a", "#000000", "#ffffcc", "#d9f0a3", "#addd8e", "#78c679", "#41ab5d", "#238443", "#005a32", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_08[11]       = {        "b", "#000000", "#ffffe5", "#f7fcb9", "#d9f0a3", "#addd8e", "#78c679", "#41ab5d", "#238443", "#005a32", "#ffffff" };

/** Color scheme known as icp_CB_YlGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlGn_09[12]       = {        "c", "#000000", "#ffffe5", "#f7fcb9", "#d9f0a3", "#addd8e", "#78c679", "#41ab5d", "#238443", "#006837", "#004529", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_03[6]      = {        "6", "#000000", "#fff7bc", "#fec44f", "#d95f0e", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_04[7]      = {        "7", "#000000", "#ffffd4", "#fed98e", "#fe9929", "#cc4c02", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_05[8]      = {        "8", "#000000", "#ffffd4", "#fed98e", "#fe9929", "#d95f0e", "#993404", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_06[9]      = {        "9", "#000000", "#ffffd4", "#fee391", "#fec44f", "#fe9929", "#d95f0e", "#993404", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_07[10]     = {        "a", "#000000", "#ffffd4", "#fee391", "#fec44f", "#fe9929", "#ec7014", "#cc4c02", "#8c2d04", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_08[11]     = {        "b", "#000000", "#ffffe5", "#fff7bc", "#fee391", "#fec44f", "#fe9929", "#ec7014", "#cc4c02", "#8c2d04", "#ffffff" };

/** Color scheme known as icp_CB_YlOrBr_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrBr_09[12]     = {        "c", "#000000", "#ffffe5", "#fff7bc", "#fee391", "#fec44f", "#fe9929", "#ec7014", "#cc4c02", "#993404", "#662506", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_03[6]      = {        "6", "#000000", "#ffeda0", "#feb24c", "#f03b20", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_04[7]      = {        "7", "#000000", "#ffffb2", "#fecc5c", "#fd8d3c", "#e31a1c", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_05[8]      = {        "8", "#000000", "#ffffb2", "#fecc5c", "#fd8d3c", "#f03b20", "#bd0026", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_06[9]      = {        "9", "#000000", "#ffffb2", "#fed976", "#feb24c", "#fd8d3c", "#f03b20", "#bd0026", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_07[10]     = {        "a", "#000000", "#ffffb2", "#fed976", "#feb24c", "#fd8d3c", "#fc4e2a", "#e31a1c", "#b10026", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_08[11]     = {        "b", "#000000", "#ffffcc", "#ffeda0", "#fed976", "#feb24c", "#fd8d3c", "#fc4e2a", "#e31a1c", "#b10026", "#ffffff" };

/** Color scheme known as icp_CB_YlOrRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
const char *icp_CB_YlOrRd_09[12]     = {        "c", "#000000", "#ffffcc", "#ffeda0", "#fed976", "#feb24c", "#fd8d3c", "#fc4e2a", "#e31a1c", "#bd0026", "#800026", "#ffffff" };

/** Black and White Color */
const char *icp_MJR_BlWt_02[3]       = { "3", "#000000", "#ffffff" };

/** Reg, Blue, Green */
const char *icp_MJR_RBG_03[6]        = { "3", "#000000", "#ff0000", "#00ff00", "#0000ff", "#ffffff" };

