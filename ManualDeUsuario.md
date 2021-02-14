# Manual de Usuario

## Instalación
Se deben instalar las siguientes librerias para que pueda funcionar el juego:  
- SDL2: sudo apt-get install libsdl2-dev  
- SDL MIXER: sudo apt-get install libsdl2-mixer-dev  
- SDL TTF: sudo apt-get install libsdl2-ttf-dev  
- YAML: sudo apt-get install libyaml-cpp-dev  

Para clonar el repositorio, ejecutar el comando: git clone https://github.com/DamianGanopolsky/TDPWolfenstein.git  

Para compilar el codigo y poder obtener los tres ejecutables, es necesario pararse en la raiz del repositorio en la terminal, y ejecutar:  
- "mkdir build"
- "cd build"
- "cmake .."
- "make"

El juego fue probado en dos computadoras con las siguientes especificaciones:

Computadora 1  
- Sistema operativo : Linux Mint 19.2
- Procesador Intel i3-6006U
- 6 GB de Ram
- Placa de video integrada, intel HD Graphics 520

Computadora 2
- Sistema operativo :  Ubuntu
- 
-
-

## Modo de uso

### Editor

Una vez compilado el programa, se puede correr esta aplicacion situandose con la terminal adentro de la carpeta Build y ejecutando el comando "./editor".  

#### Configuracion del editor
Para cambiar la resolucion con la cual se ejecuta la aplicacion se deben cambiar los parametros de "Height" y "Width" que se encuentra en el archivo "editor_config.yaml" dentro
de la carpeta "yaml_configs", dentro de la base.

#### Apertura de mapas  
Una vez iniciada la aplicacion, se debe seleccionar el mapa en formato YAML que se desea abrir, en caso de querer crear y editar un mapa inicialmente vacio, se debe
elegir la opcion "Empty".  

#### Opciones principales para editar el mapa:

- Drag & Drop: Se hace un primer click izquierdo en el objeto o personaje que se quiere crear, y se arrastra al lugar en donde se quiere que aparezca.

- Click & Drag: Sirve para crear muchos objetos en cantidad(muy util para las paredes). Se debe hacer un click derecho en el objeto deseado, y luego se debe ir
arrastrando a lo largo del mapa, manteniendo nuevamente el click derecho presionado, en todos los lugares que se desee que se cree dicho objeto.  

#### Controles para el scrolling del mapa: 

- W: Para ver el contenido del mapa en posiciones superiores  
- S: Para ver el contenido del mapa en posiciones inferiores  
- A: Para ver el contenido del mapa en posiciones que se encuentran mas a la izquierda  
- D: Para ver el contenido del mapa en posiciones que se encuentran mas a la derecha

#### Borrado de objetos:

Para eliminar un objeto personaje o estructura del mapa(o eliminar varios en simultaneo), se debe usar cualquier opcion para el editado del mapa usando el "Floor Tile" que se encuentra en la tercera
barra inferior desde la izquierda.

#### Cambio de tamaño del mapa:  

Se puede aumentar el tamaño del mapa o achicar el mismo mediante los dos botones que se encuentran en la esquina inferior derecha.

#### Guardado de mapas:

Una vez editado el mapa se puede guardar el mismo, seleccionando el boton de Guardar que se encuentra en la esquina superior derecha de la pantalla. Una vez seleccionado,
dicho boton se debe escribir el nombre del mapa(sin la extension .yaml) y seleccionar el boton "Guardar". El mapa guardado se encontrara en la carpeta Maps, junto con los 
otros.  

### Aplicacion Cliente-Servidor  

Una vez compilado el programa, se puede inicializar el servidor, situandose en la carpeta build y ejecutando el comando ./servidor [Port] . Donde Port es el puerto, que puede ser 8082 por ejemplo.  
Luego, para inicializar el cliente se debe ejecutar el comando "./Client [Host] [Port]" dentro de la carpeta build, siendo Host una 
direccion IP(e.g: 127.0.0.1), y Port el mismo puerto del servidor.

#### Configuracion del cliente
Para cambiar el volumen de la musica que se escucha mientras se ejecuta el cliente, o cambiar la resolucion del mismo, se tienen que cambiar dichos parametros
en el archivo Yaml que se encuentra en el archivo "client_settings.yaml" dentro de la carpeta "Yaml_configs".

#### Movimiento del jugador 

- W: Para avanzar hacia adelante
- S: Para avanzar hacia atras
- A: Para avanzar hacia la izquierda
- D: Para avanzar hacia la derecha
- ->(Flecha hacia la derecha): Para rotar el angulo de vision hacia la derecha
- <-(Flecha hacia la izquierda): Para rotar el angulo de vision hacia la izquierda

#### Cambio de armas
- 1: Para seleccionar el cuchillo
- 2: Para seleccionar la pistola
- 3: Para seleccionar el arma automatica
- 4: Para seleccionar el Chain Cannon  
Vale aclarar que las ultimas dos armas se tienen que lootear para que se pueda cambiar de arma a alguna de estas.

#### Salir del juego  
Se puede salir del juego en cualquier momento presionando la tecla "Esc" del lado del cliente.  
Para cerrar el servidor hay que introducir por consola la tecla "q".


