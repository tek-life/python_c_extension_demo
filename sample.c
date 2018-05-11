#include <Python.h>

#include <math.h>
#include <sys/prctl.h>

static char *py_get_threading_name() {
   PyObject *thrName = PyUnicode_DecodeFSDefault("threading");
   PyObject *thrMod = PyImport_Import(thrName);
   Py_DECREF(thrName);

   if (thrMod != NULL) {
      PyObject *curThreadFunc = PyObject_GetAttrString(thrMod, "current_thread");
      if (curThreadFunc && PyCallable_Check(curThreadFunc)) {
         PyObject *currentThread = PyObject_CallObject(curThreadFunc, NULL);
         if (currentThread != NULL) {
            PyObject *curThreadName = PyObject_GetAttrString(currentThread, "name");
            if (curThreadName != NULL) {
               return PyUnicode_AsUTF8(curThreadName);
            }
            Py_DECREF(currentThread);
         }
      }
      Py_DECREF(curThreadFunc);
      Py_DECREF(thrMod);
   }
   return NULL;
}

static PyObject *py_get_threading_module_name(PyObject *self, PyObject* args){
   return Py_BuildValue("s", py_get_threading_name());
}

static PyObject *py_get_thread_name(PyObject *self, PyObject* args){
   char tname[16] = {0};
   prctl(PR_GET_NAME, tname);
   return Py_BuildValue("s", tname);
}
static PyObject *py_get_string_length(PyObject *self, PyObject* args){
   char * name = NULL;
   int length = 0;
   if(!PyArg_ParseTuple(args, "s#", &name, &length)) {
   	return NULL;
   }
   return Py_BuildValue("{s:i}", name, length);
}
static PyObject *py_get_multi_length(PyObject *self, PyObject* args){
   char * name = NULL;
   int length = 0;
   int l1 = 0;
   int l2 = 0;
   if(!PyArg_ParseTuple(args, "iis#", &l1, &l2, &name, &length)) {
   	return NULL;
   }
   return Py_BuildValue("[i,i, s, i]", l1, l2, name, length);
}
static PyObject *py_set_thread_name(PyObject *self, PyObject* args){
   char * name = NULL;
   if(!PyArg_ParseTuple(args, "s", &name)) {
   	return NULL;
   }
   prctl(PR_SET_NAME, name);
   return Py_BuildValue("s", name);
}
/* int gcd(int, int) */
static PyObject *py_gcd(PyObject *self, PyObject *args) {
  int x, y, result;

  if (!PyArg_ParseTuple(args,"ii", &x, &y)) {
    return NULL;
  }
  result = x+y;
  return Py_BuildValue("i", result);
}

/* int in_mandel(double, double, int) */
static PyObject *py_in_mandel(PyObject *self, PyObject *args) {
  double x0, y0;
  int n;
  int result;

  if (!PyArg_ParseTuple(args, "ddi", &x0, &y0, &n)) {
    return NULL;
  }
 // result = in_mandel(x0,y0,n);
  result = x0 + y0;
  result += n;
  return Py_BuildValue("i", result);
}

/* int divide(int, int, int *) */
static PyObject *py_divide(PyObject *self, PyObject *args) {
  int a, b, quotient, remainder;
  if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
    return NULL;
  }
  //quotient = divide(a,b, &remainder);
  return Py_BuildValue("(ii)", a, b);
}

/* Module method table */
static PyMethodDef SampleMethods[] = {
  {"gcd",  py_gcd, METH_VARARGS, "Greatest common divisor"},
  {"in_mandel", py_in_mandel, METH_VARARGS, "Mandelbrot test"},
  {"divide", py_divide, METH_VARARGS, "Integer division"},
  {"get_thread_name", py_get_thread_name, METH_VARARGS, "Get thread name"},
  {"get_threading_module_name", py_get_threading_module_name, METH_VARARGS, "Get threading module name"},
  {"get_string_length", py_get_string_length, METH_VARARGS, "Get string length"},
  {"get_multi_length", py_get_multi_length, METH_VARARGS, "Get multi string length"},
  {"set_thread_name", py_set_thread_name, METH_VARARGS, "Set thread name"},
  { NULL, NULL, 0, NULL}
};

/* Module structure */
static struct PyModuleDef samplemodule = {
  PyModuleDef_HEAD_INIT,
  "sample",           /* name of module */
  "A sample module",  /* Doc string (may be NULL) */
  -1,                 /* Size of per-interpreter state or -1 */
  SampleMethods       /* Method table */
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit_sample(void) {
  return PyModule_Create(&samplemodule);
}

