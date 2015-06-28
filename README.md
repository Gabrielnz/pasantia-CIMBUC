# Dermasoft

Dermasoft es una aplicacion que actua como una interfaz para el dermatoscopio multiespectral de 7 colores, incluyendo el color blanco.

### Dependencias

Dermasoft requiere de la instalacion de las siguientes dependencias:

+ [openCV 3.0](http://opencv.org/) - Libreria open-source de computo visual.

## Usuario final

### Pasos para instalar la aplicacion

1. Descargar este archivo [opencv 3.0 pre-compilado](https://mega.nz/#!XpMw1ZSS!PZA33YhmlT4_KhacCrwTeU1TE4rQYb379Tk1haiOCP8), extraer en C:\ y agregar el siguiente valor a la variable del sistema Path:
c:\opencv\build\bin como se muestra en la siguiente imagen [agregar valor a variable de entorno Path](https://mega.nz/#!q9VFWASZ!LVVSHsgSJ79tHPGYQennFeAHJk3N0qAV9w0b2hCxl4k)

2. Descargar la ultima version del instalador de la aplicacion [dermasoft](https://mega.nz/#F!7ltiHAoI!EoDU-7zDYOx2thE4ccKpVg) y ejecutarlo.

## Desarrollador

### Notas para la generacion del instalador de la aplicacion

1. Generar el ejecutable dermatoscopio.exe de la aplicacion, ejecutando el proyecto en modo "Release", desde Qt-creator.

2. Copiar y pegar solamente dermatoscopio.exe en una carpeta aparte.

3. Estando dentro de la nueva carpeta creada, ejecutar instruccion "windeployqt dermatoscopio.exe".

4. Crear la estructura de carpetas y archivos necesarios para generar el instalador de la aplicacion,
siguiendo los pasos descritos en [Deploying Windows Applications](https://wiki.qt.io/Deploying_Windows_Applications).

5. Verificar que el instalador se haya generado correctamente.