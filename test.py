#!/usr/bin/python env
import sample
import threading
import time 

if __name__ == "__main__":
   python_name = threading.current_thread().name
   native_name = sample.get_thread_name()
   print("The python thread name is:%s"%python_name)
   print("The native thread name is:%s"%native_name)
   threading_name = sample.get_threading_module_name()
   print("The threading thread name is:%s"%threading_name)
   print("----Will set python thread name---")
   threading.current_thread().name = "FOOBARBAZ"
   threading_name = sample.get_threading_module_name()
   print("The threading thread name is:%s"%threading_name)
   print("----Will set python thread name---")
   python_new_name = "I_AM_python_thread_new_name"
   native_new_name = "I_AM_Native_thread_new_name"
   sample.set_thread_name(native_new_name)
   threading.current_thread().name = python_new_name
   time.sleep(10)

   print("----After set native & python thread name.---")
   python_name = threading.current_thread().name
   native_name = sample.get_thread_name()
   print("The python thread name is:%s"%python_name)
   print("The native thread name is:%s"%native_name)
   

