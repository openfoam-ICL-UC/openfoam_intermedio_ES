# openfoam_intermedio_ES

Taller Intermedio de OpenFOAM para Ingeniería Química. Los ejemplos son relevantes para ingeniería de procesos, alimentos y biotecnología.

#### Requisitos

Los siguientes conocimientos previos son **necesarios** para la realización de este taller:

* Conocimientos intermedios a avanzados de Python u otro lenguaje de programación
* Conocimientos intermedios a avanzados de Mecánica de Fluidos y Fenómenos de Transferencia o Transporte de Calor.
* Conocimientos básicos a intermedios de métodos numéricos, diferencias finitas como mínimo, volúmenes finitos es ideal. Si usted quiere aprender algoritmos básicos para resolver problemas a los valores iniciales, de contorno y de valores iniciales y de contorno en el contexto de Fenómenos de Transporte, le recomendamos el MOOC gratuito [Transferencia de calor, masa y momentum computacional.](https://www.coursera.org/learn/transferencia-de-momentum-calor-y-masa-computacional)
* Habilidades de simulación en OpenFOAM (configuración de casos y creación de mallas), y post-procesamiento en Paraview.

#### Requerimientos computacionales
Los siguientes requerimientos computacionales son **absolutamente necesarios** para iniciar el taller.

* Dominio básico a intermedio de la consola `Unix`: Si usted quiere aprender lo básico, le recomendamos este curso de Software Carpentry de tres horas en español: [La Terminal de Unix.](https://swcarpentry.github.io/shell-novice-es/)
  
Previo al inicio del taller, es necesario instalar los siguientes software:
* Tener instalado OpenFOAM v2306 en su computador portátil
  * Si su OS es Windows, Windows Subsystem for Linux 2 (WSL 2): [Instrucciones de instalación](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki/Instalaci%C3%B3n-de-OpenFOAM-%E2%80%90-Windows)
  * Si su OS es macOS, versión pre-compilada de OpenFOAM en Docker container: [Instrucciones de instalación](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki/Instalaci%C3%B3n-de-OpenFOAM-%E2%80%90-macOS)
  * Si su OS es Linux, no es necesario instalar máquinas virtuales o Docker.
* ParaView > 5.0: Se debe instalar en Windows Subsystem for Linux o macOS o Linux: [Instrucciones de instalación](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki/Instalaci%C3%B3n-de-OpenFOAM)

Este taller tiene dos sesiones con dos partes cada una. Los objetivos de aprendizaje de cada parte de este taller son:

#### Sesión 1: Modificación de solver existente para incorporar medio poroso
1. Configurar y compilar un solver en OpenFOAM personalizado, esto es con configuraciones definida por el usuario.
2. Modificar dominio geométrico para separarlo en una porción de flujo libre (e.g., flujo en una tubería o canal) y otra de flujo a través de medio poroso.
3. Incluir archivos `header` adicionales a `solver` personalizado para crear las variables microestructurales representativas de un medio poroso (e.g., porosidad, tortuosidad, permeabilidad)
4. Modificar la ecuación de conservación de momentum en `solver` personalizado para permitir la resolución de la ecuacion de Brinkman en medio poroso. 
5. Configurar un caso de OpenFOAM representativo de flujo en medio libre y poroso isotérmico tridimensional no estacionario en un canal cuadrado.
6. Ejecutar un `solver` personalizado de OpenFOAM desde la línea de comando.
7. Visualizar los resultados del campo de velocidad de la simulación utilizando ParaView.

#### Sesión 2: Modificación de solver para incorporar sistema reaccionante en medio poroso
1. 
2.
3. 

La documentación asociada a cada sesión puedes encontrarla en [Wikis](https://github.com/openfoam-ICL-UC/openfoam_intermedio_ES/wiki)

## Autores:
Catalina Pino Muñoz, Research Associate, Earth Science and Engineering Department, Imperial College London

Felipe Huerta, Profesor Asistente, Departamento de Ingeniería Química y Bioprocesos, Pontificia Universidad Católica de Chile

