# Kernel
All the drivers should be packed in the kernel.
The kernel provides the communication with the hardware and represents the hardware status in the computer memory.
It also allows users to get and set parameters to the hardware.

### External dependences
These dependencies should be satisfied by the user!
1. CAENHVLibrary wrapper
2. V8100SDK


[svg](http://www.lnf.infn.it/~georgiev/padme-kernel.svg)
[png](http://www.lnf.infn.it/~georgiev/padme-kernel.png)

! [img](http://www.lnf.infn.it/~georgiev/padme-kernel.png?sanitize=true)
![img](../docs/kernel.png)


Parts of the kernel:

### Manager / Initialiser
This should initialise everything.
1. Read configuration from file. It uses yaml configuration file. Example:
   ```
- Args: {IPAddr: 192.168.0.1, User: admin, Pass: admin}
  Label: "CAENHV1"
  ParentLabel: "PADME"
  DriverType: "CAEN_HVCrate"
  Update: {"*": 3}

- Args: {"",""}
  Label: "MainFrame"
  ParentLabel: "CAENHV1"
  DriverType: "CAEN_SY4527"
  Update: {"*": 3}

- Args: {Slot: 2, NChannels: 48}
  Label: "board1"
  ParentLabel: "CAENHV1"
  DriverType: CAEN_A7030N
  Update: {"*": 3}

- Args: {TCPPortNumber: 33455}
  Label: "tcp_conf"
  ParentLabel: "PADME"
  DriverType: ServiceTCPConfigure

- Args: {TCPPortNumber: 33456}
  Label: "tcp_info"
  ParentLabel: "PADME"
  DriverType: ServiceTCPInfo
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
