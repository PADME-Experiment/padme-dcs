#!/usr/bin/env python3

"""
  PADME-NIM - Firmware by INFN-LNF (C) 2012-2017


  APD - Specific commands

  ADCFG [0|1] [ch]         - Configure card P0=Dis/Enble, P1=channel 0=ALL
  ADCONVERT                - Show last LTC2489 ADC conversion
  ADSTS [1]                - Show ADC device status, 1=VERBOSE
  AUTOCALIBRATE V1 V2      - ADC autocalibrate at V1 and V2
  AUTOCONFIGURE            - Autoconfigure APD external card
  CALDACP1P2 ch new old    - Two point linear calibration on DAC ch=1..16
  CALADCP1P2 ch new old    - Two point linear calibration on ADC ch=1..16
  CALDATA 1..76 slpe ofst  - Set/get calibration data
  DACLTC2609 [ch][0|180]   - Set HV value 
  DACSTS                   - Show DAC devices status
  ENTEST [ch][0..1]        - En/Disable test flag on selected channel, 0=all
  HVONOFF [0|1]            - Enable/disable HV on sensors
  HVRANGE [50 | 100 | 500] - Set HV range
  OWDINIT                  - Initialize DS2482 1-wire driver
  OWDENUMERATE             - Enumerate devices on 1-wire bus
  OWDSTS                   - Show register of DS2482 1-wire driver
  SHOW                     - Show continuous ADC conversion
  SKIPERROR [0|1|n]        - Skip err messages, 0=skip NONE, 1=skip ALL, n=1 out of n
  SLEWRATE [1..250]        - Set APD HV bias slew rate in V/s
"""


import pexpect
import sys
import re
import json
import urllib.request
import pandas




class sipm_controller():
  host=''
  def __init__(self,ip,port,username, password):
    self.host=ip
    self.tn=''
    self.__Connect(ip,port,username, password)

  def __del__(self):
    self.__Disconnect()


  def __Connect(self,ip,port,username, password):
    self.tn = pexpect.spawnu('/usr/bin/telnet '+ip+' '+str(port))
    #self.tn.logfile = sys.stdout
    self.tn.expect('Username: ')
    self.tn.sendline(username+'\r\n')
    self.tn.expect('Password: ')
    self.tn.sendline(password+'\r\n')
    self.tn.expect('APD1768> ')



  def __Disconnect(self):
    if self.tn.isalive():
        self.tn.sendline('bye') # Try to ask ftp child to exit.
        self.tn.close()
    # Print the final state of the child. Normally isalive() should be FALSE.
    if self.tn.isalive():
      print("'"+self.host+"' did not exit gracefully.")
    else:
      print("'"+self.host+"' exited gracefully.")



  def PrintHelp(self):
    self.tn.sendline('help\r\n')
    self.tn.expect('APD1768> ')
    print(self.tn.before)

  def SwitchControllerHV(self, state):
    if(str(state)=="1"):
      self.tn.sendline("HVONOFF 1\r\n")
      self.tn.expect('APD1768> ')
    elif(str(state)=="0"):
      self.tn.sendline("HVONOFF 0\r\n")
      self.tn.expect('APD1768> ')
    else:
      print("raise syntax error")

  def SetVoltageCh(self,channel,voltage):
    """channel=0 for all channels"""
    chan_i=int(channel)
    volt_f=float(voltage)
    if chan_i<0 or chan_i>16: print("raise invalid channel")
    if volt_f<0 or volt_f>80: print("raise voltage out of range")
    self.tn.sendline("DACLTC2609 "+str(chan_i)+" "+str(volt_f)+"\r\n")
    self.tn.expect('APD1768> ')

  def SetVoltageAll(self,voltages):
    if not hasattr(voltages,"__len__") :
      self.SetVoltageAll([voltages]*16)
    elif len(voltages)==16:
      for c,v in enumerate(voltages):
        self.SetVoltageCh(c,v)
    else:
      print("raise invalid number of elements")

  def SwitchChannel(self,channel, state):
    """channel=0 for all channels"""
    chan_i=int(channel)
    state_i=int(state)
    if chan_i<0 or chan_i>16: print("raise invalid channel")
    if state_i<0 or state_i>1: print("raise unknown state")
    self.tn.sendline("ADCFG "+str(state_i)+" "+str(chan_i)+"\r\n")
    self.tn.expect('APD1768> ')

  def GetVMon(self):
    self.tn.sendline("ADCONVERT\r\n")
    self.tn.expect('APD1768> ')
    vmontable=self.tn.before
    vmontable=vmontable.split('\r\n')
    print("BEFORE",vmontable)
    vmontable=[re.sub(r'.*: ([0-9.]+) +.*',r'\1',elem) for elem in vmontable if "INFO - LTC2489  CH" in elem]
    print("AFTER",vmontable)
    #vmontable=filter(lambda elem: elem.in("INFO - LTC2489  CH", vmontable)) 
    return vmontable

  def get_brdcfg(self):
    return json.loads(
        urllib.request.urlopen("http://"+self.host+"/brdcfg.cgx").read().decode()
        )

  def get_brdusr(self):
    return json.loads(
        urllib.request.urlopen("http://"+self.host+"/brdusr.cgx").read().decode()
        )




class Manager():
  vnominal={

      "padmevetosipm19":[57.86,57.69,57.36,57.44,57.44,57.52,57.45,57.33,57.13,57.13,57.1 ,57.03,57.03,57.02,57.15,57.33], # pveto 1
      "padmevetosipm13":[57.35,57.41,57.35,57.49,57.55,57.51,57.83,57.56,57.13,57.15,57.24,57.33,57.54,57.57,57.51,57.46], # pveto 2
      "padmevetosipm15":[57.72,57.58,57.48,57.38,57.51,57.4 ,57.39,57.41,57.04,57.09,57.08,57.05,57.66,57.63,57.59,57.52], # pveto 3
      "padmevetosipm21":[57.23,57.15,57.05,57.09,57.6 ,57.57,57.36,57.3 ,57.49,57.38,57.21,57.01,57.6 ,57.35,57.39,57.56], # pveto 4
      "padmevetosipm23":[57.02,57.07,57.08,57.66,57.57,57.42,57.41,57.39,57.73,57.66,57.62,57.52,57.06,57.15,57.35,57.49], # pveto 5
      "padmevetosipm16":[57.15,57.8 ,57.71,57.69,57.61,57.5 ,57.27,57.09,57.59,57.64,57.59,57.46,57.09,57   ,57.03,57.01], # pveto 6

      "padmevetosipm07":[57.02,57.02,57.19,57.09,57.41,57.48,57.51,57.41,57.52,57.65,57.58,57.7 ,57.63,57.5 ,57.34,57.17], # eveto 1
      "padmevetosipm22":[57.01,57.06,57.28,57.42,57.75,57.55,57.82,57.4 ,57.08,57.33,57.17,57.37,57.05,57.03,57.71,57.62], # eveto 2
      "padmevetosipm24":[57.5 ,57.34,57.79,57.04,57.41,57.44,57.47,57.37,57.48,57.33,57.39,57.4 ,57.42,57.55,57.71,57.74], # eveto 3
      "padmevetosipm14":[57.77,57.53,57.67,57.76,57.01,57.56,57.53,57.83,57.44,57.34,57.43,57.62,57.26,57.12,57.05,57.04], # eveto 4
      "padmevetosipm08":[57.58,57.02,57   ,57.12,57.63,57.6 ,57.08,57.2 ,57.26,57.32,57.47,57.53,57.56,57.56,57.11,56.97], # eveto 5
      "padmevetosipm10":[57.56,57.48,57.31,57.2 ,57.03,57.12,57.26,57.4 ,57.06,57.03,57.08,57.88,57.35,57.52,57.59,57.56], # eveto 6

      #"padmevetosipm02":[57.42,57.4 ,57.46,57.42,57.4 ,57.43,57.45,57.52,57.45,57.56,57.5 ,57.47,57.62,57.55,57.03,57.05],
      #"padmevetosipm11":[57.48,57.63,57.63,57.55,57.65,57.59,57.39,57.27,57.62,57.63,57.58,57.42,57.57,57.46,57.07,57.06],
      #"padmevetosipm17":[54.61,54.65,54.64,54.91,54.81,54.7 ,54.9 ,54.83,54.89,54.83,54.67,54.85,54.77,54.76,54.76,54.78],
      #"padmevetosipm18":[57.29,57.24,57.14,57.05,57.05,57.12,57.17,57.16,57.54,57.64,57.69,57.56,57.4 ,57.24,57.01,57.01],
      }
  controllers={}
  def __init__(self):
    self.__setup()


  def __setup(self):
    port=23
    username="fcgc"
    password="fcgc"
    for host in self.vnominal :
      print("connecting to ", host)
      self.controllers[host]=sipm_controller(host,port,username,password)


  #def vmon(self):
  #  for host in self.controllers:
  #    print(self.controllers[host].GetVMon())

  def switch_on_test(self):
    for host in self.controllers:
      #self.controllers[host].SetVoltageAll(15)
      self.controllers[host].SwitchControllerHV(1)
      self.controllers[host].SwitchChannel(0,1)
      self.controllers[host].SetVoltageAll(15)

  def switch_on(self):
    for host in self.controllers:
      self.controllers[host].SetVoltageAll(self.vnominal[host])
      self.controllers[host].SwitchControllerHV(1)
      self.controllers[host].SwitchChannel(0,1)
      self.controllers[host].SetVoltageAll(self.vnominal[host])

  def switch_off(self):
    for host in self.controllers:
      self.controllers[host].SwitchControllerHV(0)
      self.controllers[host].SwitchChannel(0,1) #note all ch should be enabled
      self.controllers[host].SetVoltageAll(0)

  def get_status(self):
    for host in self.controllers:
      print(host)
      print(host)
      print(host)
      stat=self.controllers[host].get_brdcfg()
      print(stat)

      stat=self.controllers[host].get_brdusr()
      print( pandas.DataFrame(stat,
        columns=[
          "id",
          "ch",
          "cardSts",
          "hvReq",
          "hvLvl",
          "cardTemp",
          "apdCurrent",
          "apdTemp",
          "cardSsupplyV",
          "errSts",
          "errCnt",
          "lastErr",
          ]))





if __name__ == "__main__":
#import pdb
#pdb.run('Test()')
  import time

  def Test():
    ip="padmevetosipm19"
    port=23
    username="fcgc"
    password="fcgc"
    sipm=sipm_controller(ip,port,username,password)
    sipm.SwitchControllerHV(1)
    sipm.SwitchChannel(0,1)
    sipm.SetVoltageAll(10)
    sipm.SetVoltageCh(4,4.8)
    print('111111111111')
    print(sipm.GetVMon())
    time.sleep(10)
    print('222222222222')
    print(sipm.GetVMon())
    time.sleep(10)
    print('333333333333')
    print(sipm.GetVMon())
    sipm.SwitchControllerHV(0)
    time.sleep(10)
    print('444444444444')
    print(sipm.GetVMon())
    Test()
