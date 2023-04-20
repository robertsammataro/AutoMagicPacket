# AutoMagicPacket
Use a Linux-based device to send a Wake-on-LAN Magic Packet to device when Static IP assignments are not available on the LAN Access Point. 

AutoMagicPacket is a program intended for Linux devices that transforms the device into a server for forwarding Wake-on-LAN (WOL) packets. Some ISPs (...ahem Xfinity) don't permit static IP addressing using their provided routers, meaning WOL can't properly work on devices connected to these networks. To circumvent this, AutoMagicPacket runs on an always-on, low-powered Linux computer (ie. Raspberry Pi) that when sent a WOL packet, in turn sends a new WOL packet to a pre-defined target machine. 

Utilizing AutoMagicPacket from outside of the LAN the server is running on will require Port Forwarding to be set up. By default, AMP listens on port 50000 and transmits WOL packets via etherwake, which will need to be installed seperately.
