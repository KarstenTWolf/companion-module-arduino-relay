## Arduino Relay Module

Based on code from the generic HTTP module. Uses GET requests. 

Uses the Analog pins, so can be adapted to non-relay use cases.

See accompanying Companion-Arduino-Relay.ino

Can also be triggered directly via http from a browser. 

* Syntax is Relay# = 0 (open) 1 (closed) delimited by '&'
* example: http://10.0.0.222/&0=0&1=0&2=1&

**Available commands**

* Relay open
* Relay closed
* Multi Open/Close


