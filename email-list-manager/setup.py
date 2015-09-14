import os, sys

__author__ = 'Amides Rodriguez'

from distutils.core import setup, Extension
from distutils.command.build_ext import build_ext
from distutils.util import get_platform

copt =  {'msvc': ['/EHsc'],
         'mingw32' : []}

class build_ext_subclass( build_ext ):
    def build_extensions(self):
        c = self.compiler.compiler_type
        if copt[c]:
           for e in self.extensions:
               e.extra_compile_args = copt[ c ]
        #if lopt.has_key(c):
        #   for e in self.extensions:
        #       e.extra_link_args = lopt[ c ]
        build_ext.build_extensions(self)

includeDirs = []
libraryDirs = []
librariesNames= []

if sys.platform == "win32":
    includeDirs = ['C:\\boost_1_59_0',
                   'C:\\Python34\\include']
    libraryDirs = ['C:\\boost_1_59_0\\stage\\lib',
				   'C:\\Python34\\libs']
    librariesNames = []
else:
    includeDirs = ['/usr/include','/usr/local/opt/python-3.4.1/include/python3.4m']
    libraryDirs = ['/usr/lib']
    librariesNames = ['boost_regex','boost_thread']


elm = Extension('elm',
	     include_dirs = includeDirs,
         library_dirs = libraryDirs,
	     libraries = librariesNames,
	     sources = ['elm.cpp','ELMModuleInterface.cpp','NetworkUtils.cpp',
	    'Python2CUtils.cpp','StringUtils.cpp','processingThreadCore/Consumer.cpp',
	    'processingThreadCore/ConsumersManager.cpp','processingThreadCore/ExtractAndCleanTask.cpp',
	    'processingThreadCore/MergeEmailListTask.cpp','processingThreadCore/EmailListElementDelete.cpp',
	    'processingThreadCore/SampleAddressListTask.cpp','processingThreadCore/keepAddressesTask.cpp',
	    'processingThreadCore/SeparateListTask.cpp','processingThreadCore/SeedAddressesTask.cpp',
	    'processingThreadCore/SplitAddressesTask.cpp','MD5Utility.cpp'])

setup (name = 'elm',
       version = '1.0',
       description = 'This is a Email List Manager package',
       ext_modules = [elm],
	   cmdclass = {'build_ext': build_ext_subclass })
