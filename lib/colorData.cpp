// -*- Mode:C; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      colorData.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Definition of the colMatchPoints array@EOL
 @copyright
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

#include <cstdint>                                                       /* std:: C stdint.h        C++11    */

// Put everything in the mjr namespace
namespace mjr {

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
extern const uint32_t icp_uO_BrBu_10[13]       = {        0xd, 0x000000, 0x662f00, 0x996035, 0xcc9b7a, 0xd8af97, 0xf2dacd, 0xccfdff, 0x99f8ff, 0x65efff, 0x32e3ff, 0x00a9cc, 0xffffff };

/** Color scheme known as icp_uO_BrBu_12 (Brown to Blue, 12 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BrBu_12[15]       = {        0xf, 0x000000, 0x331900, 0x662f00, 0x996035, 0xcc9b7a, 0xd8af97, 0xf2dacd, 0xccfdff, 0x99f8ff, 0x65efff, 0x32e3ff, 0x00a9cc, 0x007a99, 0xffffff };

/** Color scheme known as icp_uO_BuDOr_12 (Blue to Dark Orange, 12 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuDOr_12[15]      = {        0xf, 0x000000, 0x1e8e99, 0x51c3cc, 0x99f9ff, 0xb2fcff, 0xccfeff, 0xe5ffff, 0xffe5cc, 0xffca99, 0xffad65, 0xff8e32, 0xcc5800, 0x993f00, 0xffffff };

/** Color scheme known as icp_uO_BuDOr_18 (Blue to Dark Orange, 18 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuDOr_18[21]      = {       0x15, 0x000000, 0x006666, 0x009999, 0x00cccc, 0x00ffff, 0x33ffff, 0x65ffff, 0x99ffff, 0xb2ffff, 0xcbffff, 0xe5ffff, 0xffe5cb, 0xffca99, 0xffad65, 0xff8e33, 0xff6e00, 0xcc5500, 0x993d00, 0x662700, 0xffffff };

/** Color scheme known as icp_uO_BuDRd_12 (Dark Red to Blue, 12 steps, based on ColorBrewer RdYlBu_11) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuDRd_12[15]      = {        0xf, 0x000000, 0x290ad8, 0x264dff, 0x3fa0ff, 0x72d9ff, 0xaaf7ff, 0xe0ffff, 0xffffbf, 0xffe099, 0xffad72, 0xf76d5e, 0xd82632, 0xa50021, 0xffffff };

/** Color scheme known as icp_uO_BuDRd_18 (Dark Red to Blue, 18 steps, based on ColorBrewer RdYlBu_11) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuDRd_18[21]      = {       0x15, 0x000000, 0x2400d8, 0x181cf7, 0x2857ff, 0x3d87ff, 0x56b0ff, 0x75d3ff, 0x99eaff, 0xbcf9ff, 0xeaffff, 0xffffea, 0xfff1bc, 0xffd699, 0xffac75, 0xff7856, 0xff3d3d, 0xf72735, 0xd8152f, 0xa50021, 0xffffff };

/** Color scheme known as icp_uO_BuGr_14 (Blue-Green) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuGr_14[17]       = {       0x11, 0x000000, 0x0000ff, 0x3333ff, 0x6565ff, 0x9999ff, 0xb2b2ff, 0xcbcbff, 0xe5e5ff, 0xe5ffe5, 0xcbffcb, 0xb2ffb2, 0x99ff99, 0x65ff65, 0x33ff33, 0x00ff00, 0xffffff };

/** Color scheme known as icp_uO_BuGy_8 (Blue to Gray, 8 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuGy_8[11]        = {        0xb, 0x000000, 0x0099cc, 0x66e5ff, 0x99ffff, 0xccffff, 0xe5e5e5, 0x999999, 0x666666, 0x333333, 0xffffff };

/** Color scheme known as icp_uO_BuOrR_14 (Blue to Orange Red, 14 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuOrR_14[17]      = {       0x11, 0x000000, 0x075aff, 0x3276ff, 0x5990ff, 0x8cb2ff, 0xbfd4ff, 0xe5eeff, 0xf7f9ff, 0xffffcc, 0xffff99, 0xffff00, 0xffcc00, 0xff9900, 0xff6600, 0xff0000, 0xffffff };

/** Color scheme known as icp_uO_BuOr_12 (Blue to Orange, 12 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuOr_12[15]       = {        0xf, 0x000000, 0x002aff, 0x1965ff, 0x3299ff, 0x65ccff, 0x99edff, 0xccffff, 0xffffcc, 0xffee99, 0xffcc65, 0xff9932, 0xff6619, 0xff2a00, 0xffffff };

/** Color scheme known as icp_uO_BuOr_8 (Blue to Orange, 8 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_BuOr_8[11]        = {        0xb, 0x000000, 0x007fff, 0x4cc3ff, 0x99edff, 0xccffff, 0xffffcc, 0xffee99, 0xffc34c, 0xff7f00, 0xffffff };

/** Color scheme known as icp_uO_Bu_10 (Light blue to dark blue, 10 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_Bu_10[13]         = {        0xd, 0x000000, 0xe5ffff, 0xccfaff, 0xb2f2ff, 0x99e5ff, 0x7fd4ff, 0x65bfff, 0x4ca5ff, 0x3288ff, 0x1965ff, 0x003fff, 0xffffff };

/** Color scheme known as icp_uO_Bu_7 (Light Blue to Dark Blue, 7 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_Bu_7[10]          = {        0xa, 0x000000, 0xffff00, 0xfdff00, 0xf8ff00, 0xf0ff00, 0xe4ff00, 0xaacc00, 0x7a9900, 0xffffff };

/** Color scheme known as icp_uO_Cat_12 (Categorical 12-step scheme, after ColorBrewer 11-step Paired Scheme) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_Cat_12[15]        = {        0xf, 0x000000, 0xffbf7f, 0xff7f00, 0xffff99, 0xffff32, 0xb2ff8c, 0x32ff00, 0xa5edff, 0x19b2ff, 0xccbfff, 0x654cff, 0xff99bf, 0xe51932, 0xffffff };

/** Color scheme known as icp_uO_GrMg_16 (Green to Magenta, 16 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_GrMg_16[19]       = {       0x13, 0x000000, 0x005000, 0x008600, 0x00bb00, 0x00f100, 0x50ff50, 0x86ff86, 0xbbffbb, 0xffffff, 0xfff1ff, 0xffbbff, 0xff86ff, 0xff50ff, 0xf100f1, 0xbb00bb, 0x860086, 0x500050, 0xffffff };

/** Color scheme known as icp_uO_RdYlBu_11b (RdYlBu_11b (Hue fixed for protans, after ColorBrewer RdYlBu)) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_RdYlBu_11b[14]    = {        0xe, 0x000000, 0xa50021, 0xd82632, 0xf76d5e, 0xffad72, 0xffe099, 0xffffbf, 0xe0ffff, 0xaaf7ff, 0x72d8ff, 0x3fa0ff, 0x264cff, 0xffffff };

/** Color scheme known as icp_uO_StepSeq_25 (Stepped sequential scheme, 5 steps) from U of Oregon (Dept of geography) */
extern const uint32_t icp_uO_StepSeq_25[28]    = {       0x1c, 0x000000, 0x990f0f, 0xb22c2c, 0xcc5151, 0xe57e7e, 0xffb2b2, 0x99540f, 0xb26f2c, 0xcc8e51, 0xe5b17e, 0xffd8b2, 0x6b990f, 0x85b22c, 0xa3cc51, 0xc3e57e, 0xe5ffb2, 0x0f6b99, 0x2c85b2, 0x51a3cc, 0x7ec3e5, 0xb2e5ff, 0x260f99, 0x422cb2, 0x6551cc, 0x8f7ee5, 0xbfb2ff, 0xffffff };

/** Color scheme known as icp_CB_Accent_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Accent_03[6]      = {        0x6, 0x000000, 0x7fc97f, 0xbeaed4, 0xfdc086, 0xffffff };

/** Color scheme known as icp_CB_Accent_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Accent_04[7]      = {        0x7, 0x000000, 0x7fc97f, 0xbeaed4, 0xfdc086, 0xffff99, 0xffffff };

/** Color scheme known as icp_CB_Accent_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Accent_05[8]      = {        0x8, 0x000000, 0x7fc97f, 0xbeaed4, 0xfdc086, 0xffff99, 0x386cb0, 0xffffff };

/** Color scheme known as icp_CB_Accent_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Accent_06[9]      = {        0x9, 0x000000, 0x7fc97f, 0xbeaed4, 0xfdc086, 0xffff99, 0x386cb0, 0xf0027f, 0xffffff };

/** Color scheme known as icp_CB_Accent_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Accent_07[10]     = {        0xa, 0x000000, 0x7fc97f, 0xbeaed4, 0xfdc086, 0xffff99, 0x386cb0, 0xf0027f, 0xbf5b17, 0xffffff };

/** Color scheme known as icp_CB_Accent_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Accent_08[11]     = {        0xb, 0x000000, 0x7fc97f, 0xbeaed4, 0xfdc086, 0xffff99, 0x386cb0, 0xf0027f, 0xbf5b17, 0x666666, 0xffffff };

/** Color scheme known as icp_CB_Blues_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_03[6]       = {        0x6, 0x000000, 0xdeebf7, 0x9ecae1, 0x3182bd, 0xffffff };

/** Color scheme known as icp_CB_Blues_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_04[7]       = {        0x7, 0x000000, 0xeff3ff, 0xbdd7e7, 0x6baed6, 0x2171b5, 0xffffff };

/** Color scheme known as icp_CB_Blues_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_05[8]       = {        0x8, 0x000000, 0xeff3ff, 0xbdd7e7, 0x6baed6, 0x3182bd, 0x08519c, 0xffffff };

/** Color scheme known as icp_CB_Blues_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_06[9]       = {        0x9, 0x000000, 0xeff3ff, 0xc6dbef, 0x9ecae1, 0x6baed6, 0x3182bd, 0x08519c, 0xffffff };

/** Color scheme known as icp_CB_Blues_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_07[10]      = {        0xa, 0x000000, 0xeff3ff, 0xc6dbef, 0x9ecae1, 0x6baed6, 0x4292c6, 0x2171b5, 0x084594, 0xffffff };

/** Color scheme known as icp_CB_Blues_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_08[11]      = {        0xb, 0x000000, 0xf7fbff, 0xdeebf7, 0xc6dbef, 0x9ecae1, 0x6baed6, 0x4292c6, 0x2171b5, 0x084594, 0xffffff };

/** Color scheme known as icp_CB_Blues_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Blues_09[12]      = {        0xc, 0x000000, 0xf7fbff, 0xdeebf7, 0xc6dbef, 0x9ecae1, 0x6baed6, 0x4292c6, 0x2171b5, 0x08519c, 0x08306b, 0xffffff };

/** Color scheme known as icp_CB_BrBG_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_03[6]        = {        0x6, 0x000000, 0xd8b365, 0xf5f5f5, 0x5ab4ac, 0xffffff };

/** Color scheme known as icp_CB_BrBG_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_04[7]        = {        0x7, 0x000000, 0xa6611a, 0xdfc27d, 0x80cdc1, 0x018571, 0xffffff };

/** Color scheme known as icp_CB_BrBG_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_05[8]        = {        0x8, 0x000000, 0xa6611a, 0xdfc27d, 0xf5f5f5, 0x80cdc1, 0x018571, 0xffffff };

/** Color scheme known as icp_CB_BrBG_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_06[9]        = {        0x9, 0x000000, 0x8c510a, 0xd8b365, 0xf6e8c3, 0xc7eae5, 0x5ab4ac, 0x01665e, 0xffffff };

/** Color scheme known as icp_CB_BrBG_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_07[10]       = {        0xa, 0x000000, 0x8c510a, 0xd8b365, 0xf6e8c3, 0xf5f5f5, 0xc7eae5, 0x5ab4ac, 0x01665e, 0xffffff };

/** Color scheme known as icp_CB_BrBG_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_08[11]       = {        0xb, 0x000000, 0x8c510a, 0xbf812d, 0xdfc27d, 0xf6e8c3, 0xc7eae5, 0x80cdc1, 0x35978f, 0x01665e, 0xffffff };

/** Color scheme known as icp_CB_BrBG_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_09[12]       = {        0xc, 0x000000, 0x8c510a, 0xbf812d, 0xdfc27d, 0xf6e8c3, 0xf5f5f5, 0xc7eae5, 0x80cdc1, 0x35978f, 0x01665e, 0xffffff };

/** Color scheme known as icp_CB_BrBG_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_10[13]       = {        0xd, 0x000000, 0x543005, 0x8c510a, 0xbf812d, 0xdfc27d, 0xf6e8c3, 0xc7eae5, 0x80cdc1, 0x35978f, 0x01665e, 0x003c30, 0xffffff };

/** Color scheme known as icp_CB_BrBG_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_BrBG_11[14]       = {        0xe, 0x000000, 0x543005, 0x8c510a, 0xbf812d, 0xdfc27d, 0xf6e8c3, 0xf5f5f5, 0xc7eae5, 0x80cdc1, 0x35978f, 0x01665e, 0x003c30, 0xffffff };

/** Color scheme known as icp_CB_BuGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_03[6]        = {        0x6, 0x000000, 0xe5f5f9, 0x99d8c9, 0x2ca25f, 0xffffff };

/** Color scheme known as icp_CB_BuGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_04[7]        = {        0x7, 0x000000, 0xedf8fb, 0xb2e2e2, 0x66c2a4, 0x238b45, 0xffffff };

/** Color scheme known as icp_CB_BuGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_05[8]        = {        0x8, 0x000000, 0xedf8fb, 0xb2e2e2, 0x66c2a4, 0x2ca25f, 0x006d2c, 0xffffff };

/** Color scheme known as icp_CB_BuGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_06[9]        = {        0x9, 0x000000, 0xedf8fb, 0xccece6, 0x99d8c9, 0x66c2a4, 0x2ca25f, 0x006d2c, 0xffffff };

/** Color scheme known as icp_CB_BuGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_07[10]       = {        0xa, 0x000000, 0xedf8fb, 0xccece6, 0x99d8c9, 0x66c2a4, 0x41ae76, 0x238b45, 0x005824, 0xffffff };

/** Color scheme known as icp_CB_BuGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_08[11]       = {        0xb, 0x000000, 0xf7fcfd, 0xe5f5f9, 0xccece6, 0x99d8c9, 0x66c2a4, 0x41ae76, 0x238b45, 0x005824, 0xffffff };

/** Color scheme known as icp_CB_BuGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuGn_09[12]       = {        0xc, 0x000000, 0xf7fcfd, 0xe5f5f9, 0xccece6, 0x99d8c9, 0x66c2a4, 0x41ae76, 0x238b45, 0x006d2c, 0x00441b, 0xffffff };

/** Color scheme known as icp_CB_BuPu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_03[6]        = {        0x6, 0x000000, 0xe0ecf4, 0x9ebcda, 0x8856a7, 0xffffff };

/** Color scheme known as icp_CB_BuPu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_04[7]        = {        0x7, 0x000000, 0xedf8fb, 0xb3cde3, 0x8c96c6, 0x88419d, 0xffffff };

/** Color scheme known as icp_CB_BuPu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_05[8]        = {        0x8, 0x000000, 0xedf8fb, 0xb3cde3, 0x8c96c6, 0x8856a7, 0x810f7c, 0xffffff };

/** Color scheme known as icp_CB_BuPu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_06[9]        = {        0x9, 0x000000, 0xedf8fb, 0xbfd3e6, 0x9ebcda, 0x8c96c6, 0x8856a7, 0x810f7c, 0xffffff };

/** Color scheme known as icp_CB_BuPu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_07[10]       = {        0xa, 0x000000, 0xedf8fb, 0xbfd3e6, 0x9ebcda, 0x8c96c6, 0x8c6bb1, 0x88419d, 0x6e016b, 0xffffff };

/** Color scheme known as icp_CB_BuPu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_08[11]       = {        0xb, 0x000000, 0xf7fcfd, 0xe0ecf4, 0xbfd3e6, 0x9ebcda, 0x8c96c6, 0x8c6bb1, 0x88419d, 0x6e016b, 0xffffff };

/** Color scheme known as icp_CB_BuPu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_BuPu_09[12]       = {        0xc, 0x000000, 0xf7fcfd, 0xe0ecf4, 0xbfd3e6, 0x9ebcda, 0x8c96c6, 0x8c6bb1, 0x88419d, 0x810f7c, 0x4d004b, 0xffffff };

/** Color scheme known as icp_CB_Dark2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Dark2_03[6]       = {        0x6, 0x000000, 0x1b9e77, 0xd95f02, 0x7570b3, 0xffffff };

/** Color scheme known as icp_CB_Dark2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Dark2_04[7]       = {        0x7, 0x000000, 0x1b9e77, 0xd95f02, 0x7570b3, 0xe7298a, 0xffffff };

/** Color scheme known as icp_CB_Dark2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Dark2_05[8]       = {        0x8, 0x000000, 0x1b9e77, 0xd95f02, 0x7570b3, 0xe7298a, 0x66a61e, 0xffffff };

/** Color scheme known as icp_CB_Dark2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Dark2_06[9]       = {        0x9, 0x000000, 0x1b9e77, 0xd95f02, 0x7570b3, 0xe7298a, 0x66a61e, 0xe6ab02, 0xffffff };

/** Color scheme known as icp_CB_Dark2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Dark2_07[10]      = {        0xa, 0x000000, 0x1b9e77, 0xd95f02, 0x7570b3, 0xe7298a, 0x66a61e, 0xe6ab02, 0xa6761d, 0xffffff };

/** Color scheme known as icp_CB_Dark2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Dark2_08[11]      = {        0xb, 0x000000, 0x1b9e77, 0xd95f02, 0x7570b3, 0xe7298a, 0x66a61e, 0xe6ab02, 0xa6761d, 0x666666, 0xffffff };

/** Color scheme known as icp_CB_GnBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_03[6]        = {        0x6, 0x000000, 0xe0f3db, 0xa8ddb5, 0x43a2ca, 0xffffff };

/** Color scheme known as icp_CB_GnBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_04[7]        = {        0x7, 0x000000, 0xf0f9e8, 0xbae4bc, 0x7bccc4, 0x2b8cbe, 0xffffff };

/** Color scheme known as icp_CB_GnBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_05[8]        = {        0x8, 0x000000, 0xf0f9e8, 0xbae4bc, 0x7bccc4, 0x43a2ca, 0x0868ac, 0xffffff };

/** Color scheme known as icp_CB_GnBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_06[9]        = {        0x9, 0x000000, 0xf0f9e8, 0xccebc5, 0xa8ddb5, 0x7bccc4, 0x43a2ca, 0x0868ac, 0xffffff };

/** Color scheme known as icp_CB_GnBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_07[10]       = {        0xa, 0x000000, 0xf0f9e8, 0xccebc5, 0xa8ddb5, 0x7bccc4, 0x4eb3d3, 0x2b8cbe, 0x08589e, 0xffffff };

/** Color scheme known as icp_CB_GnBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_08[11]       = {        0xb, 0x000000, 0xf7fcf0, 0xe0f3db, 0xccebc5, 0xa8ddb5, 0x7bccc4, 0x4eb3d3, 0x2b8cbe, 0x08589e, 0xffffff };

/** Color scheme known as icp_CB_GnBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_GnBu_09[12]       = {        0xc, 0x000000, 0xf7fcf0, 0xe0f3db, 0xccebc5, 0xa8ddb5, 0x7bccc4, 0x4eb3d3, 0x2b8cbe, 0x0868ac, 0x084081, 0xffffff };

/** Color scheme known as icp_CB_Greens_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_03[6]      = {        0x6, 0x000000, 0xe5f5e0, 0xa1d99b, 0x31a354, 0xffffff };

/** Color scheme known as icp_CB_Greens_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_04[7]      = {        0x7, 0x000000, 0xedf8e9, 0xbae4b3, 0x74c476, 0x238b45, 0xffffff };

/** Color scheme known as icp_CB_Greens_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_05[8]      = {        0x8, 0x000000, 0xedf8e9, 0xbae4b3, 0x74c476, 0x31a354, 0x006d2c, 0xffffff };

/** Color scheme known as icp_CB_Greens_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_06[9]      = {        0x9, 0x000000, 0xedf8e9, 0xc7e9c0, 0xa1d99b, 0x74c476, 0x31a354, 0x006d2c, 0xffffff };

/** Color scheme known as icp_CB_Greens_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_07[10]     = {        0xa, 0x000000, 0xedf8e9, 0xc7e9c0, 0xa1d99b, 0x74c476, 0x41ab5d, 0x238b45, 0x005a32, 0xffffff };

/** Color scheme known as icp_CB_Greens_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_08[11]     = {        0xb, 0x000000, 0xf7fcf5, 0xe5f5e0, 0xc7e9c0, 0xa1d99b, 0x74c476, 0x41ab5d, 0x238b45, 0x005a32, 0xffffff };

/** Color scheme known as icp_CB_Greens_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greens_09[12]     = {        0xc, 0x000000, 0xf7fcf5, 0xe5f5e0, 0xc7e9c0, 0xa1d99b, 0x74c476, 0x41ab5d, 0x238b45, 0x006d2c, 0x00441b, 0xffffff };

/** Color scheme known as icp_CB_Greys_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_03[6]       = {        0x6, 0x000000, 0xf0f0f0, 0xbdbdbd, 0x636363, 0xffffff };

/** Color scheme known as icp_CB_Greys_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_04[7]       = {        0x7, 0x000000, 0xf7f7f7, 0xcccccc, 0x969696, 0x525252, 0xffffff };

/** Color scheme known as icp_CB_Greys_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_05[8]       = {        0x8, 0x000000, 0xf7f7f7, 0xcccccc, 0x969696, 0x636363, 0x252525, 0xffffff };

/** Color scheme known as icp_CB_Greys_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_06[9]       = {        0x9, 0x000000, 0xf7f7f7, 0xd9d9d9, 0xbdbdbd, 0x969696, 0x636363, 0x252525, 0xffffff };

/** Color scheme known as icp_CB_Greys_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_07[10]      = {        0xa, 0x000000, 0xf7f7f7, 0xd9d9d9, 0xbdbdbd, 0x969696, 0x737373, 0x525252, 0x252525, 0xffffff };

/** Color scheme known as icp_CB_Greys_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_08[11]      = {        0xb, 0x000000, 0xffffff, 0xf0f0f0, 0xd9d9d9, 0xbdbdbd, 0x969696, 0x737373, 0x525252, 0x252525, 0xffffff };

/** Color scheme known as icp_CB_Greys_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Greys_09[12]      = {        0xc, 0x000000, 0xffffff, 0xf0f0f0, 0xd9d9d9, 0xbdbdbd, 0x969696, 0x737373, 0x525252, 0x252525, 0x000000, 0xffffff };

/** Color scheme known as icp_CB_OrRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_03[6]        = {        0x6, 0x000000, 0xfee8c8, 0xfdbb84, 0xe34a33, 0xffffff };

/** Color scheme known as icp_CB_OrRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_04[7]        = {        0x7, 0x000000, 0xfef0d9, 0xfdcc8a, 0xfc8d59, 0xd7301f, 0xffffff };

/** Color scheme known as icp_CB_OrRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_05[8]        = {        0x8, 0x000000, 0xfef0d9, 0xfdcc8a, 0xfc8d59, 0xe34a33, 0xb30000, 0xffffff };

/** Color scheme known as icp_CB_OrRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_06[9]        = {        0x9, 0x000000, 0xfef0d9, 0xfdd49e, 0xfdbb84, 0xfc8d59, 0xe34a33, 0xb30000, 0xffffff };

/** Color scheme known as icp_CB_OrRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_07[10]       = {        0xa, 0x000000, 0xfef0d9, 0xfdd49e, 0xfdbb84, 0xfc8d59, 0xef6548, 0xd7301f, 0x990000, 0xffffff };

/** Color scheme known as icp_CB_OrRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_08[11]       = {        0xb, 0x000000, 0xfff7ec, 0xfee8c8, 0xfdd49e, 0xfdbb84, 0xfc8d59, 0xef6548, 0xd7301f, 0x990000, 0xffffff };

/** Color scheme known as icp_CB_OrRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_OrRd_09[12]       = {        0xc, 0x000000, 0xfff7ec, 0xfee8c8, 0xfdd49e, 0xfdbb84, 0xfc8d59, 0xef6548, 0xd7301f, 0xb30000, 0x7f0000, 0xffffff };

/** Color scheme known as icp_CB_Oranges_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_03[6]     = {        0x6, 0x000000, 0xfee6ce, 0xfdae6b, 0xe6550d, 0xffffff };

/** Color scheme known as icp_CB_Oranges_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_04[7]     = {        0x7, 0x000000, 0xfeedde, 0xfdbe85, 0xfd8d3c, 0xd94701, 0xffffff };

/** Color scheme known as icp_CB_Oranges_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_05[8]     = {        0x8, 0x000000, 0xfeedde, 0xfdbe85, 0xfd8d3c, 0xe6550d, 0xa63603, 0xffffff };

/** Color scheme known as icp_CB_Oranges_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_06[9]     = {        0x9, 0x000000, 0xfeedde, 0xfdd0a2, 0xfdae6b, 0xfd8d3c, 0xe6550d, 0xa63603, 0xffffff };

/** Color scheme known as icp_CB_Oranges_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_07[10]    = {        0xa, 0x000000, 0xfeedde, 0xfdd0a2, 0xfdae6b, 0xfd8d3c, 0xf16913, 0xd94801, 0x8c2d04, 0xffffff };

/** Color scheme known as icp_CB_Oranges_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_08[11]    = {        0xb, 0x000000, 0xfff5eb, 0xfee6ce, 0xfdd0a2, 0xfdae6b, 0xfd8d3c, 0xf16913, 0xd94801, 0x8c2d04, 0xffffff };

/** Color scheme known as icp_CB_Oranges_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Oranges_09[12]    = {        0xc, 0x000000, 0xfff5eb, 0xfee6ce, 0xfdd0a2, 0xfdae6b, 0xfd8d3c, 0xf16913, 0xd94801, 0xa63603, 0x7f2704, 0xffffff };

/** Color scheme known as icp_CB_PRGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_03[6]        = {        0x6, 0x000000, 0xaf8dc3, 0xf7f7f7, 0x7fbf7b, 0xffffff };

/** Color scheme known as icp_CB_PRGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_04[7]        = {        0x7, 0x000000, 0x7b3294, 0xc2a5cf, 0xa6dba0, 0x008837, 0xffffff };

/** Color scheme known as icp_CB_PRGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_05[8]        = {        0x8, 0x000000, 0x7b3294, 0xc2a5cf, 0xf7f7f7, 0xa6dba0, 0x008837, 0xffffff };

/** Color scheme known as icp_CB_PRGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_06[9]        = {        0x9, 0x000000, 0x762a83, 0xaf8dc3, 0xe7d4e8, 0xd9f0d3, 0x7fbf7b, 0x1b7837, 0xffffff };

/** Color scheme known as icp_CB_PRGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_07[10]       = {        0xa, 0x000000, 0x762a83, 0xaf8dc3, 0xe7d4e8, 0xf7f7f7, 0xd9f0d3, 0x7fbf7b, 0x1b7837, 0xffffff };

/** Color scheme known as icp_CB_PRGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_08[11]       = {        0xb, 0x000000, 0x762a83, 0x9970ab, 0xc2a5cf, 0xe7d4e8, 0xd9f0d3, 0xa6dba0, 0x5aae61, 0x1b7837, 0xffffff };

/** Color scheme known as icp_CB_PRGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_09[12]       = {        0xc, 0x000000, 0x762a83, 0x9970ab, 0xc2a5cf, 0xe7d4e8, 0xf7f7f7, 0xd9f0d3, 0xa6dba0, 0x5aae61, 0x1b7837, 0xffffff };

/** Color scheme known as icp_CB_PRGn_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_10[13]       = {        0xd, 0x000000, 0x40004b, 0x762a83, 0x9970ab, 0xc2a5cf, 0xe7d4e8, 0xd9f0d3, 0xa6dba0, 0x5aae61, 0x1b7837, 0x00441b, 0xffffff };

/** Color scheme known as icp_CB_PRGn_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PRGn_11[14]       = {        0xe, 0x000000, 0x40004b, 0x762a83, 0x9970ab, 0xc2a5cf, 0xe7d4e8, 0xf7f7f7, 0xd9f0d3, 0xa6dba0, 0x5aae61, 0x1b7837, 0x00441b, 0xffffff };

/** Color scheme known as icp_CB_Paired_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_03[6]      = {        0x6, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0xffffff };

/** Color scheme known as icp_CB_Paired_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_04[7]      = {        0x7, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xffffff };

/** Color scheme known as icp_CB_Paired_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_05[8]      = {        0x8, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xffffff };

/** Color scheme known as icp_CB_Paired_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_06[9]      = {        0x9, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xffffff };

/** Color scheme known as icp_CB_Paired_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_07[10]     = {        0xa, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xfdbf6f, 0xffffff };

/** Color scheme known as icp_CB_Paired_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_08[11]     = {        0xb, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xfdbf6f, 0xff7f00, 0xffffff };

/** Color scheme known as icp_CB_Paired_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_09[12]     = {        0xc, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xfdbf6f, 0xff7f00, 0xcab2d6, 0xffffff };

/** Color scheme known as icp_CB_Paired_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_10[13]     = {        0xd, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xfdbf6f, 0xff7f00, 0xcab2d6, 0x6a3d9a, 0xffffff };

/** Color scheme known as icp_CB_Paired_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_11[14]     = {        0xe, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xfdbf6f, 0xff7f00, 0xcab2d6, 0x6a3d9a, 0xffff99, 0xffffff };

/** Color scheme known as icp_CB_Paired_12 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Paired_12[15]     = {        0xf, 0x000000, 0xa6cee3, 0x1f78b4, 0xb2df8a, 0x33a02c, 0xfb9a99, 0xe31a1c, 0xfdbf6f, 0xff7f00, 0xcab2d6, 0x6a3d9a, 0xffff99, 0xb15928, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_03[6]     = {        0x6, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_04[7]     = {        0x7, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xdecbe4, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_05[8]     = {        0x8, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xdecbe4, 0xfed9a6, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_06[9]     = {        0x9, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xdecbe4, 0xfed9a6, 0xffffcc, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_07[10]    = {        0xa, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xdecbe4, 0xfed9a6, 0xffffcc, 0xe5d8bd, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_08[11]    = {        0xb, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xdecbe4, 0xfed9a6, 0xffffcc, 0xe5d8bd, 0xfddaec, 0xffffff };

/** Color scheme known as icp_CB_Pastel1_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel1_09[12]    = {        0xc, 0x000000, 0xfbb4ae, 0xb3cde3, 0xccebc5, 0xdecbe4, 0xfed9a6, 0xffffcc, 0xe5d8bd, 0xfddaec, 0xf2f2f2, 0xffffff };

/** Color scheme known as icp_CB_Pastel2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel2_03[6]     = {        0x6, 0x000000, 0xb3e2cd, 0xfdcdac, 0xcbd5e8, 0xffffff };

/** Color scheme known as icp_CB_Pastel2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel2_04[7]     = {        0x7, 0x000000, 0xb3e2cd, 0xfdcdac, 0xcbd5e8, 0xf4cae4, 0xffffff };

/** Color scheme known as icp_CB_Pastel2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel2_05[8]     = {        0x8, 0x000000, 0xb3e2cd, 0xfdcdac, 0xcbd5e8, 0xf4cae4, 0xe6f5c9, 0xffffff };

/** Color scheme known as icp_CB_Pastel2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel2_06[9]     = {        0x9, 0x000000, 0xb3e2cd, 0xfdcdac, 0xcbd5e8, 0xf4cae4, 0xe6f5c9, 0xfff2ae, 0xffffff };

/** Color scheme known as icp_CB_Pastel2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel2_07[10]    = {        0xa, 0x000000, 0xb3e2cd, 0xfdcdac, 0xcbd5e8, 0xf4cae4, 0xe6f5c9, 0xfff2ae, 0xf1e2cc, 0xffffff };

/** Color scheme known as icp_CB_Pastel2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Pastel2_08[11]    = {        0xb, 0x000000, 0xb3e2cd, 0xfdcdac, 0xcbd5e8, 0xf4cae4, 0xe6f5c9, 0xfff2ae, 0xf1e2cc, 0xcccccc, 0xffffff };

/** Color scheme known as icp_CB_PiYG_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_03[6]        = {        0x6, 0x000000, 0xe9a3c9, 0xf7f7f7, 0xa1d76a, 0xffffff };

/** Color scheme known as icp_CB_PiYG_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_04[7]        = {        0x7, 0x000000, 0xd01c8b, 0xf1b6da, 0xb8e186, 0x4dac26, 0xffffff };

/** Color scheme known as icp_CB_PiYG_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_05[8]        = {        0x8, 0x000000, 0xd01c8b, 0xf1b6da, 0xf7f7f7, 0xb8e186, 0x4dac26, 0xffffff };

/** Color scheme known as icp_CB_PiYG_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_06[9]        = {        0x9, 0x000000, 0xc51b7d, 0xe9a3c9, 0xfde0ef, 0xe6f5d0, 0xa1d76a, 0x4d9221, 0xffffff };

/** Color scheme known as icp_CB_PiYG_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_07[10]       = {        0xa, 0x000000, 0xc51b7d, 0xe9a3c9, 0xfde0ef, 0xf7f7f7, 0xe6f5d0, 0xa1d76a, 0x4d9221, 0xffffff };

/** Color scheme known as icp_CB_PiYG_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_08[11]       = {        0xb, 0x000000, 0xc51b7d, 0xde77ae, 0xf1b6da, 0xfde0ef, 0xe6f5d0, 0xb8e186, 0x7fbc41, 0x4d9221, 0xffffff };

/** Color scheme known as icp_CB_PiYG_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_09[12]       = {        0xc, 0x000000, 0xc51b7d, 0xde77ae, 0xf1b6da, 0xfde0ef, 0xf7f7f7, 0xe6f5d0, 0xb8e186, 0x7fbc41, 0x4d9221, 0xffffff };

/** Color scheme known as icp_CB_PiYG_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_10[13]       = {        0xd, 0x000000, 0x8e0152, 0xc51b7d, 0xde77ae, 0xf1b6da, 0xfde0ef, 0xe6f5d0, 0xb8e186, 0x7fbc41, 0x4d9221, 0x276419, 0xffffff };

/** Color scheme known as icp_CB_PiYG_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PiYG_11[14]       = {        0xe, 0x000000, 0x8e0152, 0xc51b7d, 0xde77ae, 0xf1b6da, 0xfde0ef, 0xf7f7f7, 0xe6f5d0, 0xb8e186, 0x7fbc41, 0x4d9221, 0x276419, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_03[6]      = {        0x6, 0x000000, 0xece2f0, 0xa6bddb, 0x1c9099, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_04[7]      = {        0x7, 0x000000, 0xf6eff7, 0xbdc9e1, 0x67a9cf, 0x02818a, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_05[8]      = {        0x8, 0x000000, 0xf6eff7, 0xbdc9e1, 0x67a9cf, 0x1c9099, 0x016c59, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_06[9]      = {        0x9, 0x000000, 0xf6eff7, 0xd0d1e6, 0xa6bddb, 0x67a9cf, 0x1c9099, 0x016c59, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_07[10]     = {        0xa, 0x000000, 0xf6eff7, 0xd0d1e6, 0xa6bddb, 0x67a9cf, 0x3690c0, 0x02818a, 0x016450, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_08[11]     = {        0xb, 0x000000, 0xfff7fb, 0xece2f0, 0xd0d1e6, 0xa6bddb, 0x67a9cf, 0x3690c0, 0x02818a, 0x016450, 0xffffff };

/** Color scheme known as icp_CB_PuBuGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBuGn_09[12]     = {        0xc, 0x000000, 0xfff7fb, 0xece2f0, 0xd0d1e6, 0xa6bddb, 0x67a9cf, 0x3690c0, 0x02818a, 0x016c59, 0x014636, 0xffffff };

/** Color scheme known as icp_CB_PuBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_03[6]        = {        0x6, 0x000000, 0xece7f2, 0xa6bddb, 0x2b8cbe, 0xffffff };

/** Color scheme known as icp_CB_PuBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_04[7]        = {        0x7, 0x000000, 0xf1eef6, 0xbdc9e1, 0x74a9cf, 0x0570b0, 0xffffff };

/** Color scheme known as icp_CB_PuBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_05[8]        = {        0x8, 0x000000, 0xf1eef6, 0xbdc9e1, 0x74a9cf, 0x2b8cbe, 0x045a8d, 0xffffff };

/** Color scheme known as icp_CB_PuBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_06[9]        = {        0x9, 0x000000, 0xf1eef6, 0xd0d1e6, 0xa6bddb, 0x74a9cf, 0x2b8cbe, 0x045a8d, 0xffffff };

/** Color scheme known as icp_CB_PuBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_07[10]       = {        0xa, 0x000000, 0xf1eef6, 0xd0d1e6, 0xa6bddb, 0x74a9cf, 0x3690c0, 0x0570b0, 0x034e7b, 0xffffff };

/** Color scheme known as icp_CB_PuBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_08[11]       = {        0xb, 0x000000, 0xfff7fb, 0xece7f2, 0xd0d1e6, 0xa6bddb, 0x74a9cf, 0x3690c0, 0x0570b0, 0x034e7b, 0xffffff };

/** Color scheme known as icp_CB_PuBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuBu_09[12]       = {        0xc, 0x000000, 0xfff7fb, 0xece7f2, 0xd0d1e6, 0xa6bddb, 0x74a9cf, 0x3690c0, 0x0570b0, 0x045a8d, 0x023858, 0xffffff };

/** Color scheme known as icp_CB_PuOr_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_03[6]        = {        0x6, 0x000000, 0xf1a340, 0xf7f7f7, 0x998ec3, 0xffffff };

/** Color scheme known as icp_CB_PuOr_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_04[7]        = {        0x7, 0x000000, 0xe66101, 0xfdb863, 0xb2abd2, 0x5e3c99, 0xffffff };

/** Color scheme known as icp_CB_PuOr_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_05[8]        = {        0x8, 0x000000, 0xe66101, 0xfdb863, 0xf7f7f7, 0xb2abd2, 0x5e3c99, 0xffffff };

/** Color scheme known as icp_CB_PuOr_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_06[9]        = {        0x9, 0x000000, 0xb35806, 0xf1a340, 0xfee0b6, 0xd8daeb, 0x998ec3, 0x542788, 0xffffff };

/** Color scheme known as icp_CB_PuOr_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_07[10]       = {        0xa, 0x000000, 0xb35806, 0xf1a340, 0xfee0b6, 0xf7f7f7, 0xd8daeb, 0x998ec3, 0x542788, 0xffffff };

/** Color scheme known as icp_CB_PuOr_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_08[11]       = {        0xb, 0x000000, 0xb35806, 0xe08214, 0xfdb863, 0xfee0b6, 0xd8daeb, 0xb2abd2, 0x8073ac, 0x542788, 0xffffff };

/** Color scheme known as icp_CB_PuOr_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_09[12]       = {        0xc, 0x000000, 0xb35806, 0xe08214, 0xfdb863, 0xfee0b6, 0xf7f7f7, 0xd8daeb, 0xb2abd2, 0x8073ac, 0x542788, 0xffffff };

/** Color scheme known as icp_CB_PuOr_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_10[13]       = {        0xd, 0x000000, 0x7f3b08, 0xb35806, 0xe08214, 0xfdb863, 0xfee0b6, 0xd8daeb, 0xb2abd2, 0x8073ac, 0x542788, 0x2d004b, 0xffffff };

/** Color scheme known as icp_CB_PuOr_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_PuOr_11[14]       = {        0xe, 0x000000, 0x7f3b08, 0xb35806, 0xe08214, 0xfdb863, 0xfee0b6, 0xf7f7f7, 0xd8daeb, 0xb2abd2, 0x8073ac, 0x542788, 0x2d004b, 0xffffff };

/** Color scheme known as icp_CB_PuRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_03[6]        = {        0x6, 0x000000, 0xe7e1ef, 0xc994c7, 0xdd1c77, 0xffffff };

/** Color scheme known as icp_CB_PuRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_04[7]        = {        0x7, 0x000000, 0xf1eef6, 0xd7b5d8, 0xdf65b0, 0xce1256, 0xffffff };

/** Color scheme known as icp_CB_PuRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_05[8]        = {        0x8, 0x000000, 0xf1eef6, 0xd7b5d8, 0xdf65b0, 0xdd1c77, 0x980043, 0xffffff };

/** Color scheme known as icp_CB_PuRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_06[9]        = {        0x9, 0x000000, 0xf1eef6, 0xd4b9da, 0xc994c7, 0xdf65b0, 0xdd1c77, 0x980043, 0xffffff };

/** Color scheme known as icp_CB_PuRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_07[10]       = {        0xa, 0x000000, 0xf1eef6, 0xd4b9da, 0xc994c7, 0xdf65b0, 0xe7298a, 0xce1256, 0x91003f, 0xffffff };

/** Color scheme known as icp_CB_PuRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_08[11]       = {        0xb, 0x000000, 0xf7f4f9, 0xe7e1ef, 0xd4b9da, 0xc994c7, 0xdf65b0, 0xe7298a, 0xce1256, 0x91003f, 0xffffff };

/** Color scheme known as icp_CB_PuRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_PuRd_09[12]       = {        0xc, 0x000000, 0xf7f4f9, 0xe7e1ef, 0xd4b9da, 0xc994c7, 0xdf65b0, 0xe7298a, 0xce1256, 0x980043, 0x67001f, 0xffffff };

/** Color scheme known as icp_CB_Purples_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_03[6]     = {        0x6, 0x000000, 0xefedf5, 0xbcbddc, 0x756bb1, 0xffffff };

/** Color scheme known as icp_CB_Purples_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_04[7]     = {        0x7, 0x000000, 0xf2f0f7, 0xcbc9e2, 0x9e9ac8, 0x6a51a3, 0xffffff };

/** Color scheme known as icp_CB_Purples_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_05[8]     = {        0x8, 0x000000, 0xf2f0f7, 0xcbc9e2, 0x9e9ac8, 0x756bb1, 0x54278f, 0xffffff };

/** Color scheme known as icp_CB_Purples_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_06[9]     = {        0x9, 0x000000, 0xf2f0f7, 0xdadaeb, 0xbcbddc, 0x9e9ac8, 0x756bb1, 0x54278f, 0xffffff };

/** Color scheme known as icp_CB_Purples_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_07[10]    = {        0xa, 0x000000, 0xf2f0f7, 0xdadaeb, 0xbcbddc, 0x9e9ac8, 0x807dba, 0x6a51a3, 0x4a1486, 0xffffff };

/** Color scheme known as icp_CB_Purples_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_08[11]    = {        0xb, 0x000000, 0xfcfbfd, 0xefedf5, 0xdadaeb, 0xbcbddc, 0x9e9ac8, 0x807dba, 0x6a51a3, 0x4a1486, 0xffffff };

/** Color scheme known as icp_CB_Purples_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Purples_09[12]    = {        0xc, 0x000000, 0xfcfbfd, 0xefedf5, 0xdadaeb, 0xbcbddc, 0x9e9ac8, 0x807dba, 0x6a51a3, 0x54278f, 0x3f007d, 0xffffff };

/** Color scheme known as icp_CB_RdBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_03[6]        = {        0x6, 0x000000, 0xef8a62, 0xf7f7f7, 0x67a9cf, 0xffffff };

/** Color scheme known as icp_CB_RdBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_04[7]        = {        0x7, 0x000000, 0xca0020, 0xf4a582, 0x92c5de, 0x0571b0, 0xffffff };

/** Color scheme known as icp_CB_RdBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_05[8]        = {        0x8, 0x000000, 0xca0020, 0xf4a582, 0xf7f7f7, 0x92c5de, 0x0571b0, 0xffffff };

/** Color scheme known as icp_CB_RdBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_06[9]        = {        0x9, 0x000000, 0xb2182b, 0xef8a62, 0xfddbc7, 0xd1e5f0, 0x67a9cf, 0x2166ac, 0xffffff };

/** Color scheme known as icp_CB_RdBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_07[10]       = {        0xa, 0x000000, 0xb2182b, 0xef8a62, 0xfddbc7, 0xf7f7f7, 0xd1e5f0, 0x67a9cf, 0x2166ac, 0xffffff };

/** Color scheme known as icp_CB_RdBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_08[11]       = {        0xb, 0x000000, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xd1e5f0, 0x92c5de, 0x4393c3, 0x2166ac, 0xffffff };

/** Color scheme known as icp_CB_RdBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_09[12]       = {        0xc, 0x000000, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xf7f7f7, 0xd1e5f0, 0x92c5de, 0x4393c3, 0x2166ac, 0xffffff };

/** Color scheme known as icp_CB_RdBu_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_10[13]       = {        0xd, 0x000000, 0x67001f, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xd1e5f0, 0x92c5de, 0x4393c3, 0x2166ac, 0x053061, 0xffffff };

/** Color scheme known as icp_CB_RdBu_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdBu_11[14]       = {        0xe, 0x000000, 0x67001f, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xf7f7f7, 0xd1e5f0, 0x92c5de, 0x4393c3, 0x2166ac, 0x053061, 0xffffff };

/** Color scheme known as icp_CB_RdGy_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_03[6]        = {        0x6, 0x000000, 0xef8a62, 0xffffff, 0x999999, 0xffffff };

/** Color scheme known as icp_CB_RdGy_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_04[7]        = {        0x7, 0x000000, 0xca0020, 0xf4a582, 0xbababa, 0x404040, 0xffffff };

/** Color scheme known as icp_CB_RdGy_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_05[8]        = {        0x8, 0x000000, 0xca0020, 0xf4a582, 0xffffff, 0xbababa, 0x404040, 0xffffff };

/** Color scheme known as icp_CB_RdGy_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_06[9]        = {        0x9, 0x000000, 0xb2182b, 0xef8a62, 0xfddbc7, 0xe0e0e0, 0x999999, 0x4d4d4d, 0xffffff };

/** Color scheme known as icp_CB_RdGy_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_07[10]       = {        0xa, 0x000000, 0xb2182b, 0xef8a62, 0xfddbc7, 0xffffff, 0xe0e0e0, 0x999999, 0x4d4d4d, 0xffffff };

/** Color scheme known as icp_CB_RdGy_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_08[11]       = {        0xb, 0x000000, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xe0e0e0, 0xbababa, 0x878787, 0x4d4d4d, 0xffffff };

/** Color scheme known as icp_CB_RdGy_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_09[12]       = {        0xc, 0x000000, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xffffff, 0xe0e0e0, 0xbababa, 0x878787, 0x4d4d4d, 0xffffff };

/** Color scheme known as icp_CB_RdGy_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_10[13]       = {        0xd, 0x000000, 0x67001f, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xe0e0e0, 0xbababa, 0x878787, 0x4d4d4d, 0x1a1a1a, 0xffffff };

/** Color scheme known as icp_CB_RdGy_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdGy_11[14]       = {        0xe, 0x000000, 0x67001f, 0xb2182b, 0xd6604d, 0xf4a582, 0xfddbc7, 0xffffff, 0xe0e0e0, 0xbababa, 0x878787, 0x4d4d4d, 0x1a1a1a, 0xffffff };

/** Color scheme known as icp_CB_RdPu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_03[6]        = {        0x6, 0x000000, 0xfde0dd, 0xfa9fb5, 0xc51b8a, 0xffffff };

/** Color scheme known as icp_CB_RdPu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_04[7]        = {        0x7, 0x000000, 0xfeebe2, 0xfbb4b9, 0xf768a1, 0xae017e, 0xffffff };

/** Color scheme known as icp_CB_RdPu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_05[8]        = {        0x8, 0x000000, 0xfeebe2, 0xfbb4b9, 0xf768a1, 0xc51b8a, 0x7a0177, 0xffffff };

/** Color scheme known as icp_CB_RdPu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_06[9]        = {        0x9, 0x000000, 0xfeebe2, 0xfcc5c0, 0xfa9fb5, 0xf768a1, 0xc51b8a, 0x7a0177, 0xffffff };

/** Color scheme known as icp_CB_RdPu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_07[10]       = {        0xa, 0x000000, 0xfeebe2, 0xfcc5c0, 0xfa9fb5, 0xf768a1, 0xdd3497, 0xae017e, 0x7a0177, 0xffffff };

/** Color scheme known as icp_CB_RdPu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_08[11]       = {        0xb, 0x000000, 0xfff7f3, 0xfde0dd, 0xfcc5c0, 0xfa9fb5, 0xf768a1, 0xdd3497, 0xae017e, 0x7a0177, 0xffffff };

/** Color scheme known as icp_CB_RdPu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_RdPu_09[12]       = {        0xc, 0x000000, 0xfff7f3, 0xfde0dd, 0xfcc5c0, 0xfa9fb5, 0xf768a1, 0xdd3497, 0xae017e, 0x7a0177, 0x49006a, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_03[6]      = {        0x6, 0x000000, 0xfc8d59, 0xffffbf, 0x91bfdb, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_04[7]      = {        0x7, 0x000000, 0xd7191c, 0xfdae61, 0xabd9e9, 0x2c7bb6, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_05[8]      = {        0x8, 0x000000, 0xd7191c, 0xfdae61, 0xffffbf, 0xabd9e9, 0x2c7bb6, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_06[9]      = {        0x9, 0x000000, 0xd73027, 0xfc8d59, 0xfee090, 0xe0f3f8, 0x91bfdb, 0x4575b4, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_07[10]     = {        0xa, 0x000000, 0xd73027, 0xfc8d59, 0xfee090, 0xffffbf, 0xe0f3f8, 0x91bfdb, 0x4575b4, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_08[11]     = {        0xb, 0x000000, 0xd73027, 0xf46d43, 0xfdae61, 0xfee090, 0xe0f3f8, 0xabd9e9, 0x74add1, 0x4575b4, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_09[12]     = {        0xc, 0x000000, 0xd73027, 0xf46d43, 0xfdae61, 0xfee090, 0xffffbf, 0xe0f3f8, 0xabd9e9, 0x74add1, 0x4575b4, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_10[13]     = {        0xd, 0x000000, 0xa50026, 0xd73027, 0xf46d43, 0xfdae61, 0xfee090, 0xe0f3f8, 0xabd9e9, 0x74add1, 0x4575b4, 0x313695, 0xffffff };

/** Color scheme known as icp_CB_RdYlBu_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlBu_11[14]     = {        0xe, 0x000000, 0xa50026, 0xd73027, 0xf46d43, 0xfdae61, 0xfee090, 0xffffbf, 0xe0f3f8, 0xabd9e9, 0x74add1, 0x4575b4, 0x313695, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_03[6]      = {        0x6, 0x000000, 0xfc8d59, 0xffffbf, 0x91cf60, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_04[7]      = {        0x7, 0x000000, 0xd7191c, 0xfdae61, 0xa6d96a, 0x1a9641, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_05[8]      = {        0x8, 0x000000, 0xd7191c, 0xfdae61, 0xffffbf, 0xa6d96a, 0x1a9641, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_06[9]      = {        0x9, 0x000000, 0xd73027, 0xfc8d59, 0xfee08b, 0xd9ef8b, 0x91cf60, 0x1a9850, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_07[10]     = {        0xa, 0x000000, 0xd73027, 0xfc8d59, 0xfee08b, 0xffffbf, 0xd9ef8b, 0x91cf60, 0x1a9850, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_08[11]     = {        0xb, 0x000000, 0xd73027, 0xf46d43, 0xfdae61, 0xfee08b, 0xd9ef8b, 0xa6d96a, 0x66bd63, 0x1a9850, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_09[12]     = {        0xc, 0x000000, 0xd73027, 0xf46d43, 0xfdae61, 0xfee08b, 0xffffbf, 0xd9ef8b, 0xa6d96a, 0x66bd63, 0x1a9850, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_10[13]     = {        0xd, 0x000000, 0xa50026, 0xd73027, 0xf46d43, 0xfdae61, 0xfee08b, 0xd9ef8b, 0xa6d96a, 0x66bd63, 0x1a9850, 0x006837, 0xffffff };

/** Color scheme known as icp_CB_RdYlGn_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_RdYlGn_11[14]     = {        0xe, 0x000000, 0xa50026, 0xd73027, 0xf46d43, 0xfdae61, 0xfee08b, 0xffffbf, 0xd9ef8b, 0xa6d96a, 0x66bd63, 0x1a9850, 0x006837, 0xffffff };

/** Color scheme known as icp_CB_Reds_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_03[6]        = {        0x6, 0x000000, 0xfee0d2, 0xfc9272, 0xde2d26, 0xffffff };

/** Color scheme known as icp_CB_Reds_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_04[7]        = {        0x7, 0x000000, 0xfee5d9, 0xfcae91, 0xfb6a4a, 0xcb181d, 0xffffff };

/** Color scheme known as icp_CB_Reds_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_05[8]        = {        0x8, 0x000000, 0xfee5d9, 0xfcae91, 0xfb6a4a, 0xde2d26, 0xa50f15, 0xffffff };

/** Color scheme known as icp_CB_Reds_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_06[9]        = {        0x9, 0x000000, 0xfee5d9, 0xfcbba1, 0xfc9272, 0xfb6a4a, 0xde2d26, 0xa50f15, 0xffffff };

/** Color scheme known as icp_CB_Reds_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_07[10]       = {        0xa, 0x000000, 0xfee5d9, 0xfcbba1, 0xfc9272, 0xfb6a4a, 0xef3b2c, 0xcb181d, 0x99000d, 0xffffff };

/** Color scheme known as icp_CB_Reds_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_08[11]       = {        0xb, 0x000000, 0xfff5f0, 0xfee0d2, 0xfcbba1, 0xfc9272, 0xfb6a4a, 0xef3b2c, 0xcb181d, 0x99000d, 0xffffff };

/** Color scheme known as icp_CB_Reds_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_Reds_09[12]       = {        0xc, 0x000000, 0xfff5f0, 0xfee0d2, 0xfcbba1, 0xfc9272, 0xfb6a4a, 0xef3b2c, 0xcb181d, 0xa50f15, 0x67000d, 0xffffff };

/** Color scheme known as icp_CB_Set1_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_03[6]        = {        0x6, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0xffffff };

/** Color scheme known as icp_CB_Set1_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_04[7]        = {        0x7, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0x984ea3, 0xffffff };

/** Color scheme known as icp_CB_Set1_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_05[8]        = {        0x8, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0x984ea3, 0xff7f00, 0xffffff };

/** Color scheme known as icp_CB_Set1_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_06[9]        = {        0x9, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0x984ea3, 0xff7f00, 0xffff33, 0xffffff };

/** Color scheme known as icp_CB_Set1_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_07[10]       = {        0xa, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0x984ea3, 0xff7f00, 0xffff33, 0xa65628, 0xffffff };

/** Color scheme known as icp_CB_Set1_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_08[11]       = {        0xb, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0x984ea3, 0xff7f00, 0xffff33, 0xa65628, 0xf781bf, 0xffffff };

/** Color scheme known as icp_CB_Set1_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set1_09[12]       = {        0xc, 0x000000, 0xe41a1c, 0x377eb8, 0x4daf4a, 0x984ea3, 0xff7f00, 0xffff33, 0xa65628, 0xf781bf, 0x999999, 0xffffff };

/** Color scheme known as icp_CB_Set2_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set2_03[6]        = {        0x6, 0x000000, 0x66c2a5, 0xfc8d62, 0x8da0cb, 0xffffff };

/** Color scheme known as icp_CB_Set2_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set2_04[7]        = {        0x7, 0x000000, 0x66c2a5, 0xfc8d62, 0x8da0cb, 0xe78ac3, 0xffffff };

/** Color scheme known as icp_CB_Set2_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set2_05[8]        = {        0x8, 0x000000, 0x66c2a5, 0xfc8d62, 0x8da0cb, 0xe78ac3, 0xa6d854, 0xffffff };

/** Color scheme known as icp_CB_Set2_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set2_06[9]        = {        0x9, 0x000000, 0x66c2a5, 0xfc8d62, 0x8da0cb, 0xe78ac3, 0xa6d854, 0xffd92f, 0xffffff };

/** Color scheme known as icp_CB_Set2_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set2_07[10]       = {        0xa, 0x000000, 0x66c2a5, 0xfc8d62, 0x8da0cb, 0xe78ac3, 0xa6d854, 0xffd92f, 0xe5c494, 0xffffff };

/** Color scheme known as icp_CB_Set2_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set2_08[11]       = {        0xb, 0x000000, 0x66c2a5, 0xfc8d62, 0x8da0cb, 0xe78ac3, 0xa6d854, 0xffd92f, 0xe5c494, 0xb3b3b3, 0xffffff };

/** Color scheme known as icp_CB_Set3_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_03[6]        = {        0x6, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xffffff };

/** Color scheme known as icp_CB_Set3_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_04[7]        = {        0x7, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0xffffff };

/** Color scheme known as icp_CB_Set3_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_05[8]        = {        0x8, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xffffff };

/** Color scheme known as icp_CB_Set3_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_06[9]        = {        0x9, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xffffff };

/** Color scheme known as icp_CB_Set3_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_07[10]       = {        0xa, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xb3de69, 0xffffff };

/** Color scheme known as icp_CB_Set3_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_08[11]       = {        0xb, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xb3de69, 0xfccde5, 0xffffff };

/** Color scheme known as icp_CB_Set3_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_09[12]       = {        0xc, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xb3de69, 0xfccde5, 0xd9d9d9, 0xffffff };

/** Color scheme known as icp_CB_Set3_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_10[13]       = {        0xd, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xb3de69, 0xfccde5, 0xd9d9d9, 0xbc80bd, 0xffffff };

/** Color scheme known as icp_CB_Set3_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_11[14]       = {        0xe, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xb3de69, 0xfccde5, 0xd9d9d9, 0xbc80bd, 0xccebc5, 0xffffff };

/** Color scheme known as icp_CB_Set3_12 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Qualitative */
extern const uint32_t icp_CB_Set3_12[15]       = {        0xf, 0x000000, 0x8dd3c7, 0xffffb3, 0xbebada, 0xfb8072, 0x80b1d3, 0xfdb462, 0xb3de69, 0xfccde5, 0xd9d9d9, 0xbc80bd, 0xccebc5, 0xffed6f, 0xffffff };

/** Color scheme known as icp_CB_Spectral_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_03[6]    = {        0x6, 0x000000, 0xfc8d59, 0xffffbf, 0x99d594, 0xffffff };

/** Color scheme known as icp_CB_Spectral_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_04[7]    = {        0x7, 0x000000, 0xd7191c, 0xfdae61, 0xabdda4, 0x2b83ba, 0xffffff };

/** Color scheme known as icp_CB_Spectral_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_05[8]    = {        0x8, 0x000000, 0xd7191c, 0xfdae61, 0xffffbf, 0xabdda4, 0x2b83ba, 0xffffff };

/** Color scheme known as icp_CB_Spectral_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_06[9]    = {        0x9, 0x000000, 0xd53e4f, 0xfc8d59, 0xfee08b, 0xe6f598, 0x99d594, 0x3288bd, 0xffffff };

/** Color scheme known as icp_CB_Spectral_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_07[10]   = {        0xa, 0x000000, 0xd53e4f, 0xfc8d59, 0xfee08b, 0xffffbf, 0xe6f598, 0x99d594, 0x3288bd, 0xffffff };

/** Color scheme known as icp_CB_Spectral_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_08[11]   = {        0xb, 0x000000, 0xd53e4f, 0xf46d43, 0xfdae61, 0xfee08b, 0xe6f598, 0xabdda4, 0x66c2a5, 0x3288bd, 0xffffff };

/** Color scheme known as icp_CB_Spectral_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_09[12]   = {        0xc, 0x000000, 0xd53e4f, 0xf46d43, 0xfdae61, 0xfee08b, 0xffffbf, 0xe6f598, 0xabdda4, 0x66c2a5, 0x3288bd, 0xffffff };

/** Color scheme known as icp_CB_Spectral_10 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_10[13]   = {        0xd, 0x000000, 0x9e0142, 0xd53e4f, 0xf46d43, 0xfdae61, 0xfee08b, 0xe6f598, 0xabdda4, 0x66c2a5, 0x3288bd, 0x5e4fa2, 0xffffff };

/** Color scheme known as icp_CB_Spectral_11 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Divergent */
extern const uint32_t icp_CB_Spectral_11[14]   = {        0xe, 0x000000, 0x9e0142, 0xd53e4f, 0xf46d43, 0xfdae61, 0xfee08b, 0xffffbf, 0xe6f598, 0xabdda4, 0x66c2a5, 0x3288bd, 0x5e4fa2, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_03[6]      = {        0x6, 0x000000, 0xedf8b1, 0x7fcdbb, 0x2c7fb8, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_04[7]      = {        0x7, 0x000000, 0xffffcc, 0xa1dab4, 0x41b6c4, 0x225ea8, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_05[8]      = {        0x8, 0x000000, 0xffffcc, 0xa1dab4, 0x41b6c4, 0x2c7fb8, 0x253494, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_06[9]      = {        0x9, 0x000000, 0xffffcc, 0xc7e9b4, 0x7fcdbb, 0x41b6c4, 0x2c7fb8, 0x253494, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_07[10]     = {        0xa, 0x000000, 0xffffcc, 0xc7e9b4, 0x7fcdbb, 0x41b6c4, 0x1d91c0, 0x225ea8, 0x0c2c84, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_08[11]     = {        0xb, 0x000000, 0xffffd9, 0xedf8b1, 0xc7e9b4, 0x7fcdbb, 0x41b6c4, 0x1d91c0, 0x225ea8, 0x0c2c84, 0xffffff };

/** Color scheme known as icp_CB_YlGnBu_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGnBu_09[12]     = {        0xc, 0x000000, 0xffffd9, 0xedf8b1, 0xc7e9b4, 0x7fcdbb, 0x41b6c4, 0x1d91c0, 0x225ea8, 0x253494, 0x081d58, 0xffffff };

/** Color scheme known as icp_CB_YlGn_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_03[6]        = {        0x6, 0x000000, 0xf7fcb9, 0xaddd8e, 0x31a354, 0xffffff };

/** Color scheme known as icp_CB_YlGn_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_04[7]        = {        0x7, 0x000000, 0xffffcc, 0xc2e699, 0x78c679, 0x238443, 0xffffff };

/** Color scheme known as icp_CB_YlGn_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_05[8]        = {        0x8, 0x000000, 0xffffcc, 0xc2e699, 0x78c679, 0x31a354, 0x006837, 0xffffff };

/** Color scheme known as icp_CB_YlGn_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_06[9]        = {        0x9, 0x000000, 0xffffcc, 0xd9f0a3, 0xaddd8e, 0x78c679, 0x31a354, 0x006837, 0xffffff };

/** Color scheme known as icp_CB_YlGn_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_07[10]       = {        0xa, 0x000000, 0xffffcc, 0xd9f0a3, 0xaddd8e, 0x78c679, 0x41ab5d, 0x238443, 0x005a32, 0xffffff };

/** Color scheme known as icp_CB_YlGn_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_08[11]       = {        0xb, 0x000000, 0xffffe5, 0xf7fcb9, 0xd9f0a3, 0xaddd8e, 0x78c679, 0x41ab5d, 0x238443, 0x005a32, 0xffffff };

/** Color scheme known as icp_CB_YlGn_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlGn_09[12]       = {        0xc, 0x000000, 0xffffe5, 0xf7fcb9, 0xd9f0a3, 0xaddd8e, 0x78c679, 0x41ab5d, 0x238443, 0x006837, 0x004529, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_03[6]      = {        0x6, 0x000000, 0xfff7bc, 0xfec44f, 0xd95f0e, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_04[7]      = {        0x7, 0x000000, 0xffffd4, 0xfed98e, 0xfe9929, 0xcc4c02, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_05[8]      = {        0x8, 0x000000, 0xffffd4, 0xfed98e, 0xfe9929, 0xd95f0e, 0x993404, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_06[9]      = {        0x9, 0x000000, 0xffffd4, 0xfee391, 0xfec44f, 0xfe9929, 0xd95f0e, 0x993404, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_07[10]     = {        0xa, 0x000000, 0xffffd4, 0xfee391, 0xfec44f, 0xfe9929, 0xec7014, 0xcc4c02, 0x8c2d04, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_08[11]     = {        0xb, 0x000000, 0xffffe5, 0xfff7bc, 0xfee391, 0xfec44f, 0xfe9929, 0xec7014, 0xcc4c02, 0x8c2d04, 0xffffff };

/** Color scheme known as icp_CB_YlOrBr_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrBr_09[12]     = {        0xc, 0x000000, 0xffffe5, 0xfff7bc, 0xfee391, 0xfec44f, 0xfe9929, 0xec7014, 0xcc4c02, 0x993404, 0x662506, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_03 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_03[6]      = {        0x6, 0x000000, 0xffeda0, 0xfeb24c, 0xf03b20, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_04 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_04[7]      = {        0x7, 0x000000, 0xffffb2, 0xfecc5c, 0xfd8d3c, 0xe31a1c, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_05 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_05[8]      = {        0x8, 0x000000, 0xffffb2, 0xfecc5c, 0xfd8d3c, 0xf03b20, 0xbd0026, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_06 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_06[9]      = {        0x9, 0x000000, 0xffffb2, 0xfed976, 0xfeb24c, 0xfd8d3c, 0xf03b20, 0xbd0026, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_07 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_07[10]     = {        0xa, 0x000000, 0xffffb2, 0xfed976, 0xfeb24c, 0xfd8d3c, 0xfc4e2a, 0xe31a1c, 0xb10026, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_08 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_08[11]     = {        0xb, 0x000000, 0xffffcc, 0xffeda0, 0xfed976, 0xfeb24c, 0xfd8d3c, 0xfc4e2a, 0xe31a1c, 0xb10026, 0xffffff };

/** Color scheme known as icp_CB_YlOrRd_09 the ColorBrewer collection.  Origonal source: Brewer, Cynthia A., 2005. http://www.ColorBrewer.org, 2005-12-19.
    Color scheme type: Sequential */
extern const uint32_t icp_CB_YlOrRd_09[12]     = {        0xc, 0x000000, 0xffffcc, 0xffeda0, 0xfed976, 0xfeb24c, 0xfd8d3c, 0xfc4e2a, 0xe31a1c, 0xbd0026, 0x800026, 0xffffff };

/** Black and White Color */
extern const uint32_t icp_MJR_BlWt_02[3]       = { 0x3, 0x000000, 0xffffff };

/** Reg, Blue, Green */
extern const uint32_t icp_MJR_RBG_03[6]        = { 0x3, 0x000000, 0xff0000, 0x00ff00, 0x0000ff, 0xffffff };

} // end namespace mjr
