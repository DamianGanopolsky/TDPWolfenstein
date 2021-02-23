#!/bin/bash

function waitingInputMessage() {
    echo "-------------------------------------------------"
    printf "> Ingrese una opción: "
}

function initialMessage () {
    clear
    echo "-------------------------------------------------"
    echo "                 WOLFENSTEIN 3D                  "
    echo "-------------------------------------------------"
    echo ""
}

function helpMessage() {
    echo "Opciones de instalación:"
    echo "  1: instalar dependencias necesarias."
    echo "  2: instalar el juego (sin las dependencias)."
    echo "  3: instalar dependencias y juego."
    echo ""
    echo "Opciones de desinstalación:"
    echo "  4: desinstalar el juego."
    echo ""
    echo "Otras opciones:"
    echo "  h: ayuda (este mensaje)."
    echo "  q: cerrar."
    echo ""
}

function unknownInput() {
    echo "Opción desconocida (ingrese 'h' para ayuda, 'q' para salir)." 
    echo ""
}

function installDependencies() {
    echo "--- INSTALACIÓN DE DEPENDENCIAS ---"
    echo ""
    echo ">> Instalando 'cmake'..."
    sudo apt-get install cmake
    echo ""
    echo ">> Instalando 'YAML'..."
    sudo apt-get install libyaml-cpp-dev
    echo ""
    echo ">> Instalando 'libsdl2-dev'..."
    sudo apt-get install libsdl2-dev
    echo ""
    echo ">> Instalando 'libsdl2-image-dev'..."
    sudo apt-get install libsdl2-image-dev
    echo ""
    echo ">> Instalando 'libsdl2-ttf-dev'..."
    sudo apt-get install libsdl2-ttf-dev
    echo ""
    echo ">> Instalando 'libsdl2-mixer-dev'..."
    sudo apt-get install libsdl2-mixer-dev
    echo ""
    echo "Instalación de dependencias finalizada."
    echo ""
}

function build() {
    sudo rm -rf build
    mkdir build
    cd build
    cmake ..
}

function installGame() {
    echo "--- INSTALACIÓN DEL JUEGO ---"
    build
    sudo make install
    echo ""
    echo "Instalación del juego finalizada."
    echo ""
    echo "Para su ejecución estar en la carpeta build:"
    echo "  * Servidor: corriendo './server <port> <map_name>' se abrirá un servidor en el puerto dado."
    echo "  * Cliente: corriendo './client <host> <port> <player_name>' se abrirá el juego."
    echo "  * Editor: corriendo './editor' se abrirá el editor."
}

function all() {
    installDependencies
    installGame
}

function uninstall() {
    echo "--- DESINSTALADOR ---"
    sudo rm -rf build
    sudo rm -rf /usr/bin/editor
    sudo rm -rf /usr/bin/client
    sudo rm -rf /usr/bin/server
    sudo rm -rf /usr/lib/libcommon-lib.so
    echo ""
    echo "Se ha desinstalado el juego con éxito."
    echo ""
}

# exit when any command fails
set -e

initialMessage
helpMessage
waitingInputMessage

while :
do
    read OPTION
    case $OPTION in
        1)  
            echo ""
            installDependencies
            waitingInputMessage
        ;;
        2)
            echo ""
            installGame
            waitingInputMessage
        ;;
        3)
            echo ""
            installDependencies
            installGame
            waitingInputMessage
        ;;
        4)
            echo ""
            uninstall
            waitingInputMessage
        ;;
        h)  
            echo ""
            helpMessage
            waitingInputMessage
        ;;
        q)  
            echo ""
            echo "-------------------------------------------------"
            exit 0
        ;;
        *)  
            echo ""
            unknownInput
            waitingInputMessage
        ;;
    esac
done

