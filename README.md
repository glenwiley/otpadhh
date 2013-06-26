RCE OTPAD
=========
Rock Castle Engineering
gwiley@rockcastleengineering.com

The RCE One Time Pad (OTPAD) is a device designed to provide unbreakable
encryption for message exchange with the following primary features:

* The One Time Pad is the only truly unbreakable cipher, when used properly messages encrypted using the RCE OTPAD can not be deciphered.
* Absolutely no logical attack vector against the device, since there is an air-gap between the OTPAD and other machines there is no way to mount a logical attack against the device.
* Very portable, small enough to fit in a pocket
* Messages and pads are easily and inexpensively exchanged using SD cards
* If a device is lost or stolen there is no risk to data, keys and messages are all stored on removable SD cards

Use Cases
=========

Synchronize PADs
----------------
Send a message via telephone
Send a message via voice recorder
Send a message via SD card exchange

Firmware
========
- LCD Menu system
	- Incoming Messages
		- List of messages, pad index, first N chars of each message
		- scroll using up/dn buttons, select one
			- read
			- delete
			- copy to SD card #2
				- cipher text
				- clear text
	- Outgoing Messages
		- List of messages (incl "new"), pad index, first N chars 
		- scroll using up/dn buttons, select one
			- read, if new message, edit it
			- send via audio
			- delete
			- copy to SD card #2
				- cipher text
				- clear text
	- PAD
		- erase
		- generate new pad
		- copy to SD card #2


Electronic Design
=================
- Power
	- 2xAA
	- boost converter to deliver 5V
	- optional 3V DC in
- Display
	- graphical LCD
	- LED: power (bi-color, grn=good,red=low batt)
	- LED: busy (send/recv/SD copy)
	- LED: new unread message
- Input
	- Power on/off slider switch (in front of battery)
	- btn: menu up
	- btn: menu dn
	- btn: menu select
	- btn: send (send next unsent message)
	- btn: receive (receive new incoming message)
	- btn: copy PAD from SD #1 to SD #2
	- $6.99 PS2 style keyboard from tiger direct
- Core
	- PIC18
	- RTC would be nice
- Audio in
	- SFE mic
- Audio out
	- small speaker
- Storage
	- 2 SD slots 
- Expansion
	- headers for PIC in-circuit programming
	- headers for ADC, DIO, GND, VCC for random number board

Storage on SD
=============
Starting at byte 0 on teh SD card we store a block table, the first entry in the block table tells us how large the block table is.  By default it is 255 * 136 bytes = 34816 bytes
<8 bit entry type><64-bit start addr><64-bit end addr>
entry types
* 00: block table
* 01-99: PAD
* 100: message block


Future Changes
==============
- Improved randomicity through hardware
- serial link between devices
- firmware upgrade via SD card
- allow numeric only IO - leverage 0-9 keypad for input
- configuration/settings menu
--
end README
