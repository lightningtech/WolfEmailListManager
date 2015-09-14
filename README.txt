Tips para instalacion en Windows 8 64 bits.

1. Instalar version de Python 3.4.x
2. Descargar ultima version de la biblioteca Boost.
3. Compilar boost_thread y boost_regex con opcion para compilacion en 64 bits. (agregar a bjam address-model=64) 
4. Instalar visual studio 2015 e instalar las herramientas para la compilacion en visual c++ 14(por defecto).
5. Moverse a la raiz del proyecto y ejecutar: 
   SET VS100COMNTOOLS=%VS140COMNTOOLS%
   python setup.py build
   python setup.py install	

Tips para compilacion con Visual Studio sin opciones para distutils.( Para desarrollo )
1. Abrir pyconfig.h y comentar define Py_DEBUG
2. Modificar pragma comment(lib,"python34_d.lib") por pragma comment(lib,"python34.lib")









