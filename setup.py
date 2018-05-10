from distutils.core import setup, Extension
example_module = Extension(
    'sample',
    sources=['sample.c'],
    )

setup(
    name='sample',
    version='0.1.0',
    description='example module written in C++',
    ext_modules=[example_module], )
