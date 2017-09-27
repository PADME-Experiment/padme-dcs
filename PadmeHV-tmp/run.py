#!/usr/bin/python3

import subprocess
import time
import re
import os

def StartRun(crew, comment):
  #print(comment)
  #return
  proc = subprocess.Popen(['/home/daq/DAQ/RunControl', '--no-gui'], stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
  proc.stdin.write(b"new_run\n"    )
#  proc.stdin.write(b"dummy\n"      )
  proc.stdin.write(b"next\n"       )
  proc.stdin.write(b"TEST\n"       )
  proc.stdin.write(crew.encode()+"\n".encode()      )
  proc.stdin.write(comment.encode()+"\n".encode()   )
  out,err=proc.communicate(b"start_run\n"   )
  print(out)

  # Recover run number from RunControl output
  run_number = -1
  for line in out.decode().split('\n'):
    #print(line)
    m = re.search("new run will have number (\d+)",line)
    if (m):
      run_number = m.group(1)
      #print("Run number %s"%run_number)

  return run_number

def StopRun(comment):
  #print(comment)
  #return
  proc = subprocess.Popen(['/home/daq/DAQ/RunControl', '--no-gui'], stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
  proc.stdin.write(b"stop_run\n"    )
  out,err=proc.communicate(comment.encode()+"\n".encode())
  print(out)

def MergeRun(run_number):
  print("Merging run",run_number)
  old_dir = os.getcwd()
  os.chdir("/home/daq/DAQ")
  proc = subprocess.Popen(['./MergeRuns','-s',run_number,'-n','0'], stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
  out,err = proc.communicate(b"\n")
  print(out)
  os.chdir(old_dir)

def RecoRun(run_number):
  print("Reco run",run_number)
  old_dir = os.getcwd()
  os.chdir("/home/daq/DigiDaq/PadmeLED")
  proc = subprocess.Popen(['./ReadLED.exe','-i','/mnt/data01/daq/rawdata/run_%s.root'%run_number,'-o','/home/daq/DigiDaq/PadmeLED/output/LED_%s.root'%run_number],stdin=subprocess.PIPE, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
  out,err = proc.communicate(b"\n")
  print(out)
  os.chdir(old_dir)

def Scan():
  #VoltageSteps=[1000] # Testing run number code
  VoltageSteps=[1000,1050,1100,1150,1200]#[950,1050,1150,1200,1230,1250]
  #VoltageSteps=[20,50,80]
  ResMin=6.5
  ResMax=6.6
  VoltMarg=5
  #DAQTime=3600 
  DAQTime=50

  LOG_all = open('everything.log','a',encoding='utf-8')
  LOG_volt= open('voltage.log','a',encoding='utf-8')
  LOG_res = open('resistance.log','a',encoding='utf-8')

  LOG_all .write(time.strftime("%s %F %T") + '\n\n\n=~=~+~+~ start new scan' + '\n')
  LOG_volt.write(time.strftime("%s %F %T") + '\n\n\n=~=~+~+~ start new scan' + '\n')
  LOG_res .write(time.strftime("%s %F %T") + '\n\n\n=~=~+~+~ start new scan' + '\n')

  for voltStep in VoltageSteps:
    subprocess.check_output(['./PadmeHV','-H',str(voltStep)])
    time.sleep(2)
    subprocess.check_output(['./PadmeHV','-1'])
    while True:
        time.sleep(1)
        statusRO=subprocess.check_output(['./PadmeHV','-S']).split()
        print([s == b'On' for s in statusRO])
        if all(s == b'On' for s in statusRO): break ## finnished with rumping

    time.sleep(60)
#    time.sleep(2)
    PMTList=[
        'PMT1',
        'PMT2',
        'PMT3',
        'PMT4',
        'PMT5',
        'PMT6',
        'PMT7']
    PMTDAQChList='\n'.join( [str(i)+' '+str(j) for i,j in enumerate(PMTList)] )

    #voltstepstr=str(voltStep)
    run_number = StartRun('Autorun', 'Run with LED driver    LED setting ~3.9 on daq 2 4 6 8 26 28 30 32, rest off    HV of the PMTs %d V; setup: divider 88-100-11-48-69-29-59 tube (2103) 150-151-152-153-154-155-156 (daq from 0 to 6)' % voltStep)

    if (run_number == -1):
      print("Could not retrieve run number")
    else:
      print("Run number",run_number)

    endOfRunMessage=''
    voltRO=[]
    resRO =[]
    print("loop", DAQTime)
    for iseconds in range(DAQTime):
        print("loop", iseconds)
        time.sleep(2)
        voltRO=subprocess.check_output(['./PadmeHV','-V']).split()
        resRO =subprocess.check_output(['./PadmeHV','-Z']).split()

        LOG_volt.write((time.strftime("%s %F %T"))+str(b' '.join(voltRO))+str('\n'))
        LOG_res .write((time.strftime("%s %F %T"))+str(b' '.join(resRO ))+str('\n'))
        print(b' '.join(voltRO))

        #if all(v<=voltStep+VoltMarg and v>=voltStep-VoltMarg for v in voltRO):
        #if all(r<=ResMax and v>=ResMin for r in resRO):
        for pos,item in enumerate(voltRO):
            if float(item)>voltStep+VoltMarg or float(item)<voltStep-VoltMarg:
                print("Voltage problem", pos, item, voltStep)
                LOG_all .write(time.strftime("%s %F %T") + str(b"Voltage problem ch.")+str(pos)+str(b' V=')+ str(item) + "\n")
        for pos,item in enumerate(resRO):
            if float(item)>ResMax or float(item)<ResMin:
                print("Resistance problem", pos, item)
                LOG_all .write(time.strftime("%s %F %T") + str(b"Resistance problem ch.")+str(pos)+str(b' R=')+ str(item) + "\n")
        LOG_all.flush()
        LOG_volt.flush()
        LOG_res.flush()

    endOfRunMessage='finish' #'\n'.join( [str(i)+' '+str(j) for i,j in enumerate(PMTList)] )
    StopRun(endOfRunMessage)

    if run_number != -1: MergeRun(run_number)
    if run_number != -1: RecoRun(run_number)

  subprocess.check_output(['./PadmeHV','-0']) #switch off all tubes
  LOG_all.close()
  LOG_volt.close()
  LOG_res.close()


if __name__ == "__main__":
      Scan()
