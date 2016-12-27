# Lightswitch for Arduino

## The Scenario
My apartment has a light switch by the entrance that toggles a poorly-located outlet. I would like to transplant that outlet, but it is against my landlord's contract. The solution? Use an Arduino to wirelessly relocate the outlet!

## The Hardware
1. Five pack of Etekcity 433 MHz RF power sockets with remote control. These can be had for around $25 on US Amazon. Other brands of similar compatible hardware exist, however this one is known to work.
2. 433 MHz transmitter and receiver modules. You can get about six of each for $10 total.

## The Approach
1. Teach the Arduino to learn the light switch remote control codes and play them back on-demand.
2. Monitor a switched power socket for power-on and power-off, then automatically transmit the corresponding on/off radio frequency signal.

## The Result
It works! I have a light switch that can control multiple light sockets scattered throughout my living room.
