#include "GenerarPDF.h"
#include <iostream>
#include <hpdf.h> // Librería de libharu
#include <sstream> // Asegúrate de incluir sstream
#include <vector>  // Usaremos vector para manejar las líneas
#include <cstdlib> // Para usar system() y abrir el PDF automáticamente
using namespace std;

void generarPDF(const ListaCircularDoble& lista) {
    // Verificar si la lista está vacía
    if (!lista.getCabeza()) {
        cout << "Error: La lista de libros esta vacia. No se puede generar el PDF." << endl;
        return; // Si la lista está vacía, salir de la función sin generar el PDF
    }

    // Crear un documento PDF
    HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        cout << "Error al crear el documento PDF." << endl;
        return;
    }

    // Crear una página en blanco
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Especificar la fuente
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Escribir los datos de los libros en el PDF
    int y_position = 800;
    NodoLibro* libro = lista.getCabeza(); // Usamos getCabeza() para obtener el primer nodo
    while (libro != nullptr) {
        stringstream ss;
        ss << "Titulo: " << libro->getTitulo() << "\n";
        ss << "Autor: " << libro->getAutor() << "\n";
        ss << "Ano de Publicacion: " << libro->getAnioPublicacion() << "\n";
        ss << "ISBN: " << libro->getISBN() << "\n";
        ss << "Genero: " << libro->getGenero() << "\n";
        ss << "Sinopsis: " << libro->getSinopsis() << "\n";
        ss << "Precio: " << libro->getPrecio() << "\n";
        ss << "Calificacion: " << libro->getCalificacion() << "\n";
        ss << "-----------------------------\n";

        // Convertir el texto a un vector de líneas
        string texto = ss.str();
        vector<string> lineas;
        string linea;
        stringstream texto_stream(texto);

        while (getline(texto_stream, linea)) {
            lineas.push_back(linea);
        }

        // Colocar el texto en el PDF, línea por línea
        for (const string& linea : lineas) {
            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, 50, y_position, linea.c_str());
            HPDF_Page_EndText(page);

            // Mover la posición para la siguiente línea
            y_position -= 15;

            // Si se ha llegado al final de la página, crear una nueva
            if (y_position < 50) {
                page = HPDF_AddPage(pdf);
                HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
                HPDF_Page_SetFontAndSize(page, font, 12);
                y_position = 800;
            }
        }

        libro = libro->getSiguiente();
        // Si hemos llegado a la cabeza nuevamente, detenemos el ciclo
        if (libro == lista.getCabeza()) break;
    }

    // Guardar el PDF en un archivo
    HPDF_SaveToFile(pdf, "libros.pdf");
    HPDF_Free(pdf);

    // Mensaje de éxito
    cout << "PDF generado exitosamente: libros.pdf" << endl;

    // Abrir el archivo PDF generado
    #if defined(_WIN32) || defined(_WIN64)
        system("start libros.pdf");  // En Windows
    #elif defined(__linux__)
        system("xdg-open libros.pdf");  // En Linux
    #elif defined(__APPLE__)
        system("open libros.pdf");  // En macOS
    #endif
}
