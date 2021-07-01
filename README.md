# LOOPER
 16 Track Looper



 Hi! So, this looper runs on a Rasberry Pi, which is running a Linux Distro called Patchbox by Blokas.  That OS is made specifically for audio stuff and it works great with Blokas' Pi audio interface, Pisound. I decided to go that route even though it was more expensive because I had heard great things about Blokas and I wanted it to all work with the interface easily, etc.  The people at Blokas were SUPER helpful in ironing stuff out and then went above and beyond with things like writing a python script so when the thing launched it would also launch the looper via puredata etc.  The OS does some of that stuff on its own anyway, especially with the Pisound hat on, but I had some tweaks. I'm not gonna post any of the linux or python stuff though at this point.  For software, it's running Purr data, which basically has a main.pd and that opens 16 copies of track.pd (actually 21 but for obsolete reasons).  It's also talking to the foot pedal via USB comport (i think that's why i needed purr data instead of pure data, or one of the reasons, for the comport extension) and it's talking to a desktop mixer via usb ("remote"). It's also talking to a little screen via bluetooth LE. It actually does that by sending signals to the pedal's arduino, which then relays them to the screen.  That's because those little bluefruit guys were designed to talk to each other.  That battery is so huge for the bluetooth screen and uses so little energy that I think I have literally only charged it maybe three times -- and only out of like "oh I should charge this" I've never seen it run out of batteries.

 So that's it! Let me know if I can help demystify any of this.  USE ANY PART YOU WANT. It's all open source / no rights reserved, whatever you want to call it.  Point is, I'm not worried about it. This is just for fun.  Of course, if you somehow manage to make money from this, you could send me some, I guess. Or give it to the flat earth society or the guys at Bay 12 games who make Dwarf Fortress, just because I like them.  Thanks!


HARDWARE LIST:

Main stuff:

Raspberry Pi 4 Model B 2019 Quad Core 64 Bit WiFi Bluetooth (4GB) w/ CanaKit 3.5A Raspberry Pi 4 Power Supply (USB-C), like $40 on amazon
2 x Adafruit Feather nRF52840 Express $24.95
ELEGOO MEGA 2560 R3 Board ATmega2560 ATMEGA16U2 + USB Cable Compatible with Arduino IDE, RoHS Compliant
Pisound - Blokas audio interface 99 euro (you could probably use even a $20 behringer audio interface and it would work fine, I THINK)

More (all prices from adafruit invoices)

Slide Potentiometer with Knob - 75mm Long - 10KΩSlide Potentiometer with Knob - 75mm Long - 10KΩ PID: 4219$2.955$14.75
5mm Plastic Bevel LED Holder - Pack of 55mm Plastic Bevel LED Holder - Pack of 5 PID: 2174$0.951$0.95
LED Illuminated Triangle Pushbutton A.K.A 1960s Sci-Fi ButtonsLED Illuminated Triangle Pushbutton A.K.A 1960s Sci-Fi Buttons - Red PID: 4186$3.951$3.95
Potentiometer Knob - Soft Touch T18 - BluePotentiometer Knob - Soft Touch T18 - Blue PID: 2048$0.504$2.00
Diffused 5mm LED Pack - 5 LEDs each in 5 Colors - 25 PackDiffused 5mm LED Pack - 5 LEDs each in 5 Colors - 25 Pack PID: 4203$4.951$4.95
Potentiometer Knob - Soft Touch T18 - RedPotentiometer Knob - Soft Touch T18 - Red PID: 2046$0.504$2.00
Arcade Button with LED - 30mm Translucent Clear PID: 3491$2.501$2.50
Arcade Button with LED - 30mm Translucent Yellow PID: 3488$2.501$2.50
LED Illuminated Triangle Pushbutton A.K.A 1960s Sci-Fi ButtonsLED Illuminated Triangle Pushbutton A.K.A 1960s Sci-Fi Buttons - Green PID: 4188$3.951$3.95
LED Illuminated Triangle Pushbutton A.K.A 1960s Sci-Fi ButtonsLED Illuminated Triangle Pushbutton A.K.A 1960s Sci-Fi Buttons - Blue PID: 4187$3.951$3.95
USB A Jack to Micro USB B Jack Round Panel Mount Adapter PID: 4214$5.951$5.95
Assembled Adafruit FeatherWing OLEDAssembled Adafruit FeatherWing OLED - 128x32 OLED Add-on For Feather PID: 3045$15.951$15.95
Lithium Ion Polymer Battery - 3.7v 1200mAhLithium Ion Polymer Battery - 3.7v 1200mAh PID: 258$9.951$9.95
Altoids Gum sized tinAltoids Gum sized tin PID: 16$2.001$2.00
I forget where I bought the foot switches for the pedal - they were like $5 a peice. Maybe guitar pedal parts.com probably
I also forget where I got the metal enclosure for the foot pedal

SOFTWARE LIST:

Linux OS - Patchbox --> CODE / OS NOT POSTED. I used a Rasberry Pi 4B I think it's called.

Phython Script to launch purr data --> NOT POSTED

Looper itself - Main.pd -- runs in purr data

Individual tracks Track.pd -- Main.pd runs 16 copies of Track.pd.  You have to put Track.pd in a place purr data knows to look for it

Main.iso -> sorry this is also named main.  This is the arduino code that runs the foot pedal. It's actually an Adafruit Feather nRF52840 Express and it talks to the screen also

Display.iso -> this is the code for the little tiny display. This is ALSO a Adafruit Feather nRF52840 Express but it's running in receive mode. They both use Bluetooth LE.

Remote.iso - this is the arduino code that runs the wooden box mixer / "remote"  It runs on the Elegoo Mega.
