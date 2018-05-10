# python_c_extension_demo
## Build
$python3 setup.py build_ext --inplace

## usage
The test.py is to identify that python thread name is different from native thread name.

$python3 test.py

The output will show as below.
```
~/python_c_extension_demo$ python3 test.py
The python thread name is:MainThread
The native thread name is:python3
----Will set python thread name---
----After set native & python thread name.---
The python thread name is:I_AM_python_thread_new_name
The native thread name is:I_AM_Native_thr
```