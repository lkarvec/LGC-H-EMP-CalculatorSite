curl -X 'POST' \
  'https://slim1.fulgentcorp.com:14500/emp/calc' \
  --insecure \
  -H 'accept: application/json' \
  -H 'Content-Type: application/json' \
  -d '{
  "x": 0,
  "y": 0,
  "z": 0,
  "hob": 100,
  "gamyld": 0.001,
  "bfield": 2e-05,
  "bangle": 20,
  "ndelr": 50,
  "oux": 0,
  "iter": 20,
  "ap": 2.2,
  "bp": 0.25,
  "rnp": 5.62603,
  "top": 2.24
}'

This is the current CURL command to hit the program's API through a terminal.  You have to pass an insecure connection atm because the certificate is selfsigned and this is for testing purposes.

To change the input, change any of the following variables.

Variables for the Equation
X
Magnetic west (Northern Hemisphere)

Y
Magnetic South (Northern Hemisphere)

Z
Altitude (Northern Hemisphere)

HOB
Height of Burst in Kilometers (has to be greater than 50KM)

GAMYLD
Gamma Yield of Burst in Kilotons

BFIELD
Magnitude of Earth's Magnetic Field in the absorption region below the burst in Webers/Sq Meter

BANGLE
Dip angle of the Magnetic Field in degrees

NDELR
Integer number of steps between RMin and RMax (Has to be between 50 and 500)

ITER
Time of Iterations in Shakes (from 10 to 100)

Pomranning Constants
AP
BP
RNP
TOP
