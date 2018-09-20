#!/usr/bin/env python3

import sipm_controller as sipm

import sys
def syntax():
  raise syntax (sys.argv[0]+' [on|off|status|ontest]')

if len(sys.argv)!=2:
  syntax()

mng=sipm.Manager()
cmd=str(sys.argv[1])
if cmd=='on':
  mng.switch_on()
  print('on')
elif cmd=='ontest':
  mng.switch_on_test()
  print('ontest')
elif cmd=='off':
  mng.switch_off()
elif cmd=='status':
  mng.get_status()
else:
  syntax()
