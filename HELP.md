## Arduino Relay Module

Based on code from the generic HTTP module. Uses GET requests. 

Uses the Analog pins, so can be adapted to non-relay use cases. Be sensible, don't use this for overhead or mechanical applications. The intended usecase is adding a network interface to inexpensive or legacy gear by way of using relays to open/close front panel buttons.


See accompanying Companion-Arduino-Relay.ino
The sketch can also be triggered directly via http from a browser. 
* Syntax is Relay# = 0 (open) 1 (closed) delimited by '&'
* example: http://10.0.0.222/&0=0&1=0&2=1&

**Available commands**

* Relay open
* Relay closed
* Multi Open/Close


