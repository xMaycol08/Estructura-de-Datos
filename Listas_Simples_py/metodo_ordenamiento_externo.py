import os

class MetodoOrdenamientoExterno:
    def distribuir_datos(self, archivo_entrada, archivos_cubetas):
        if not os.path.exists(archivo_entrada):
            print(f"El archivo {archivo_entrada} no existe.")
            return
        try:
            # Clear existing bucket files
            for i in range(26):
                nombre_archivo = f"cubeta_{chr(i + ord('A'))}.txt"
                if os.path.exists(nombre_archivo):
                    os.remove(nombre_archivo)
                archivos_cubetas.append(nombre_archivo)

            with open(archivo_entrada, "r") as archivo:
                datos_unicos = set()
                for linea in archivo:
                    try:
                        cedula, nombre, apellido = linea.strip().split(',')
                        if (cedula, nombre, apellido) not in datos_unicos:
                            datos_unicos.add((cedula, nombre, apellido))
                            indice = ord(nombre[0].upper()) - ord('A')
                            nombre_archivo = archivos_cubetas[indice]
                            with open(nombre_archivo, "a") as cubeta:
                                cubeta.write(f"{cedula},{nombre},{apellido}\n")
                    except ValueError:
                        print(f"Error al procesar la línea: {linea}")
        except FileNotFoundError:
            print("Error al abrir el archivo de entrada.")

    def ordenar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, "r") as archivo:
                lineas = archivo.readlines()
            lineas = list(set(lineas))  # Remove duplicates
            lineas.sort(key=lambda linea: (linea.split(',')[1], linea.split(',')[2]))  # Sort by name, then by surname
            with open(nombre_archivo, "w") as archivo:
                archivo.writelines(lineas)
        except FileNotFoundError:
            pass  # Do not print error message
        except ValueError:
            print(f"Error al procesar el archivo: {nombre_archivo}")

    def fusionar_archivos(self, archivos_cubetas, archivo_salida):
        try:
            with open(archivo_salida, "w") as archivo:
                for nombre_archivo in archivos_cubetas:
                    if os.path.exists(nombre_archivo):
                        with open(nombre_archivo, "r") as cubeta:
                            archivo.writelines(cubeta.readlines())
        except FileNotFoundError:
            pass  # Do not print error message

    def mostrar_archivo(self, nombre_archivo):
        if not os.path.exists(nombre_archivo):
            print(f"El archivo {nombre_archivo} no existe.")
            return
        try:
            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    print(linea.strip())
        except FileNotFoundError:
            print(f"Error al abrir el archivo {nombre_archivo}.")

    def eliminar_de_cubeta(self, nombre_archivo, cedula):
        if not os.path.exists(nombre_archivo):
            return
        try:
            with open(nombre_archivo, "r") as archivo:
                lineas = archivo.readlines()
            lineas = [linea for linea in lineas if not linea.startswith(cedula)]
            if lineas:
                with open(nombre_archivo, "w") as archivo:
                    archivo.writelines(lineas)
            else:
                os.remove(nombre_archivo)
        except FileNotFoundError:
            pass  # Do not print error message

    def eliminar_todas_las_cubetas(self):
        for i in range(26):
            archivo = f"cubeta_{chr(i + ord('A'))}.txt"
            if os.path.exists(archivo):
                os.remove(archivo)
