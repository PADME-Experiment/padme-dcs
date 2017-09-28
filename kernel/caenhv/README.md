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
