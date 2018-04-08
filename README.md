# Relay_Controller
ESP8266 Based Relay Controller

This is a UK based DIY Smart Socket / Smart Plug project.  The challenges I set myself with this project were:

- No "wall wart", all power should be supplied "in line"
- Both sockets should be independently controlable
- The controls should be simple & easy to use

As of v1 it's pretty basic as it just creates it's own HTTP server with buttons that allow for switching off the "Red", "Yellow" or All sockets.  I've used the settings on my home router to create a DNS name for us to browse to, so we can save shortcuts on our phones to control the sockets.

The colour names given to the sockets (Red & Yellow) are arbitary, and in hindsight I'd choose better names that weren't common colours used in electronics.

The MCB (miniture circuit breaker) probably isn't needed, but I added it as this is the first project I've made involving mains electricity that other people may interact with.  These specific sockets are intended for use with two simple floor standing lights.  As such, I've used a 6 AMP MCB (and the plug actually has a 5 AMP fuse, so the MCB should never trip).  The MCB added a lot of bulk in the electonic space, and without it (or with a better sized replacement) the overall unit could be made smaller.  Even though we typically turn both lights on at the same time anyway, I set myself the challenge of ensuring that both sockets could be controlled independently (otherwise a modified extension cord would do the trick).

The INO file has references to the links I've used when tweaking & developing the code.

Some of the things I may consider for upgrading this in future are:

- OTA updates, so I can update it from my sofa :)
- Add in the Wifi Manager library to make sharing completed items easier (I hardcoded my own SSID & Password because v1 is intended only for use by our household)
- Add the FauxMo project to integrate with Amazon's Alexa (should we ever get one)
- Change to using MQTT (as I develop other projects it might be nice to automate them together)
- Spending some time learning Eagle (or similar) to draw up electonic versions of the schematic & get some boards manufactured to reduce the footprint
