# Dermasoft

Dermasoft es una aplicacion que actua como una interfaz para el dermatoscopio multiespectral de 7 colores, incluyendo el color blanco.

### Dependencias

Dermasoft requiere de la instalacion de las siguientes dependencias:

+ [openCV 3.0](http://opencv.org/) - Libreria open-source de computo visual.
+ [CMake](http://www.cmake.org/) - herramienta para compilar openCV 3.0

### Notas para la instalacion de openCV

1. Extraer openCV 3.0 en C:\

3. Deseleccionar opcion WITH IPP al momento de compilar openCV 3.0 con CMake

2. Generar la build en C:\opencv\build

### Notas para la generacion del instalador de Dermasoft

1. Generar el ejecutable dermatoscopio.exe de la aplicacion, ejecutando el proyecto en modo "Release", desde Qt-creator.

2. Copiar y pegar solamente dermatoscopio.exe en una carpeta aparte.

3. Estando dentro de la nueva carpeta creada, ejecutar instruccion "windeployqt dermatoscopio.exe".

4. Crear la estructura de carpetas y archivos necesarios para generar el instalador de la aplicacion,
siguiendo los pasos descritos en [Deploying Windows Applications](https://wiki.qt.io/Deploying_Windows_Applications).

5. Verificar que el instalador se haya generado correctamente.