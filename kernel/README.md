# Kernel
All the drivers should be packed in the kernel.
The kernel provides the communication with the hardware and represents the hardware status in the computer memory.
It also allows users to get and set parameters to the hardware.

Subparts of the kernel:

### Manager / Initialiser
This should initialise everything.
1. Read configuration from file
   ```
    | Device ID | Driver  | parameters  
    | CaenHV1   | drvCaen | "192.168.0.1" "admin" "admin"
   ```
1. Initialise the drivers and keeps connection with HW
1. Compare the actual configuration with what was expected from MapDB
1. Build representation of the hardware in the memory
   - all the fields should be structures of value + update timestamp + status
1. Forks services
   - Each service runs independently

### Drivers
Drivers should implement the communication methods with the hardware. They can be instantiated by the manager, opening a connection with a particular device.

### Services
##### Update
This can be one or multiple processes which listens and/or polls hardware devices and update the Memory Map. There should be parameter for the poll frequency.
```
| how often [s] | HW.Ch         | values
|            30 | crate1        | Fan speed, current draw
|            30 | crate1.b4     | Temp
|             3 | crate1.b4.ch8 | IMon VMon V0Set?
```
- Values: voltages, currents, fan RPMs temps
- Timestamps: together with the values updates the timestamps. This might be helpful to be sure that the information is up to date
##### TCP services
###### GetInfo (HI, some other proc)
###### Broadcast info (DBLogger)
###### Setparameter (HI, Inteligence module)

![img](http://www.lnf.infn.it/~georgiev/padme-kernel.svg)

-----
-----
-----

# CAEN high voltage driver

### CAEN create driver
- maintains the connection with the crate
- Creates _crate map_:
  - dynamic allocation on the board classes
  - check if it is what we expect from MapDB
  - should have button to recreate the map
- configures a TCP server for the _Subscribe_ commands
  - updates memory map with the new values

-----------------------------------------------------------------------

### CAEN HV wrapper
In [CAEN HV wrapper manual] they say that some arrays should be deallocated by the user.
- It looks like it doesn't allocate arrays if exit status is !=0 ???????


[CAEN HV wrapper manual]: http://www.caen.it/servlet/checkCaenManualFile?Id=12609


### CaenA7030.h
in the constructor it should receive the number of the channels
