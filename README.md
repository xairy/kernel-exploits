CVE-2016-2384
=============

This repo contains a proof-of-concept exploit for the vulnerability in the usb-midi Linux kernel driver ([CVE-2016-2384](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2016-2384)).
Check out [the writeup](https://xairy.github.io/blog/2016/cve-2016-2384) and [the demo video](https://www.youtube.com/watch?v=lfl1NJn1nvo)!
There's also [a discussion on reddit](https://www.reddit.com/r/linux/comments/46xpzo/cve20162384_arbitrary_code_execution_due_to_a/).

Timeline:

* 13 Feb 2016: the issue reported to security@kernel.org
* 13 Feb 2016: [the fix](https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=07d86ca93db7e5cdf4743564d98292042ec21af7) is upstream
* 14 Feb 2016: a [CVE](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2016-2384) id assigned
* 22 Feb 2016: a [writeup](https://xairy.github.io/blog/2016/cve-2016-2384) published
