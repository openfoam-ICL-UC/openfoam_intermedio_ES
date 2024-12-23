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

* Dominio básico de la consola `Unix`: Si usted quiere aprender lo básico, le recomendamos este curso de Software Carpentry de tres horas en español: [La Terminal de Unix.](https://swcarpentry.github.io/shell-novice-es/)
  
Previo al inicio del taller, es necesario instalar los siguientes software:
* Tener instalado OpenFOAM en su computador portátil (se podrán hacer preguntas de instalación directamente en Discord durante los días previos al taller)
  * OpenFOAM v2306: [Instrucciones de instalación]()
  * Si su OS es Windows, Windows Subsystem for Linux 2 (WSL 2): [Instrucciones de instalación](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki/Instalaci%C3%B3n-de-OpenFOAM)
  * Si su OS es macOS, versión pre-compilada de OpenFOAM en Docker container: [Instrucciones de instalación](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki/Instalaci%C3%B3n-de-OpenFOAM)
  * Si su OS es Linux, no es necesario instalar máquinas virtuales o Docker.
* ParaView > 5.0: Se debe instalar en Windows Subsystem for Linux o macOS o Linux: [Instrucciones de instalación](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki/Instalaci%C3%B3n-de-OpenFOAM)

Este taller tiene dos sesiones con dos partes cada una. Los objetivos de aprendizaje de cada parte de este taller son:

#### Sesión 1: Implementación de la solución numérica a un problema de fenómenos de transporte en OpenFOAM
1. Configurar un caso de OpenFOAM representativo de la transferencia de calor tridimensional no estacionaria en un sistema de flujo de fluidos.
2. Ejecutar un `solver` de OpenFOAM desde la línea de comando.
3. Visualizar los resultados de la simulación utilizando paraview.

#### Sesión 2: Ejemplos y solvers avanzados de OpenFOAM para fenómenos de transporte acoplados
1. Analizar la implementación de las ecuaciones de conservación de calor, masa y cantidad de movimiento para el solver `icoReactingMultiphaseInterFoam`.
2. Reproducir un tutorial de OpenFOAM de evaporación de agua en aire, donde la transferencia de calor y masa están acopladas.
3. Post-procesar un caso multifásico de OpenFOAM.

La documentación asociada a cada sesión puedes encontrarla en [Wikis](https://github.com/openfoam-ICL-UC/openfoam_intro_ES/wiki)

## Autores:
Catalina Pino Muñoz, Research Associate, Earth Science and Engineering Department, Imperial College London

Felipe Huerta, Profesor, Departamento de Ingeniería Química y Bioprocesos, Pontificia Universidad Católica de Chile
