/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestionar Backups                                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "BackupManager.h"
#include <iostream>
#include <windows.h> // Para las funciones de Windows
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h> // Para _stat
#include <fstream>   // Para trabajar con archivos
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <sstream>
#include "ArbolBTree.h"

namespace fs = std::experimental::filesystem;

// Implementación de los métodos de BackupManager

void BackupManager::crearCarpetaSiNoExiste(const string& ruta) {
    struct _stat st;

    // Verificar si la carpeta existe
    if (_stat(ruta.c_str(), &st) != 0) {
        // Si la carpeta no existe, la creamos
        if (_mkdir(ruta.c_str()) == 0) {
            cout << "Carpeta creada: " << ruta << endl;
        } else {
            cerr << "Error al crear la carpeta: " << ruta << endl;
        }
    } else {
        cout << "La carpeta ya existe: " << ruta << endl;
    }
}

vector<string> BackupManager::listarArchivosEnCarpeta(const string& carpeta) {
    vector<string> archivos;
    string path = carpeta + "\\*"; // Agregar comodín para buscar todos los archivos
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error al acceder a la carpeta: " << carpeta << endl;
        return archivos;
    }

    do {
        string archivo = findFileData.cFileName;
        if (archivo != "." && archivo != "..") { // Ignorar "." y ".."
            archivos.push_back(archivo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return archivos;
}

void BackupManager::crearBackup(ArbolBTree& arbol) {
    // Implementación pendiente
}

void BackupManager::restaurarBackup(ArbolBTree& arbol) {
    std::vector<std::string> archivos;
    for (const auto& entry : fs::directory_iterator("backup")) {
        archivos.push_back(entry.path().string());
    }

    if (archivos.empty()) {
        std::cout << "No hay archivos de backup disponibles.\n";
        return;
    }

    std::cout << "Archivos de backup disponibles:\n";
    for (size_t i = 0; i < archivos.size(); ++i) {
        std::cout << i + 1 << ". " << archivos[i] << "\n";
    }

    int seleccion;
    std::cout << "Seleccione un archivo para restaurar: ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > archivos.size()) {
        std::cout << "Selección inválida.\n";
        return;
    }

    std::ifstream archivo(archivos[seleccion - 1]);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo de backup.\n";
        return;
    }

    // Implementación pendiente para restaurar el árbol desde el archivo
}
