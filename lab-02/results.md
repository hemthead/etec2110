```shellsession
$ hyperfine './main' 'python ./main.py'
Benchmark 1: ./main
  Time (mean ± σ):     148.7 ms ±   2.2 ms    [User: 147.9 ms, System: 0.5 ms]
  Range (min … max):   146.3 ms … 155.9 ms    20 runs

Benchmark 2: python ./main.py
  Time (mean ± σ):     10.574 s ±  0.191 s    [User: 10.543 s, System: 0.003 s]
  Range (min … max):   10.427 s … 11.094 s    10 runs

Summary
  ./main ran
   71.10 ± 1.65 times faster than python ./main.py
```

How much faster was C? 10.4s
C speedup: 72.3x
