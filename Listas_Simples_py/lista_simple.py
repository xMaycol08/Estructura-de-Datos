import os
from nodo import Nodo

class ListaSimple:
    def __init__(self):
        self.cabeza = None

    def __del__(self):
        temp = self.cabeza
        while temp is not None:
            siguiente = temp.get_siguiente()
            del temp
            temp = siguiente

    def validar_cedula_unica(self, cedula):
        temp = self.cabeza
        while temp is not None:
            if temp.get_cedula() == cedula:
                return False
            temp = temp.get_siguiente()
        return True

    def insertar_a_cola(self, cedula, nombre, apellido):
        if not self.validar_cedula_unica(cedula):
            print("Error: La cedula ya existe en la lista.")
            return

        nuevo = Nodo(cedula, nombre, apellido)
        if self.cabeza is None:
            self.cabeza = nuevo
        else:
            temp = self.cabeza
            while temp.get_siguiente() is not None:
                temp = temp.get_siguiente()
            temp.set_siguiente(nuevo)

    def buscar(self, cedula):
        if not os.path.exists("personas.txt"):
            print("El archivo personas.txt no existe.")
            return None
        try:
            with open("personas.txt", "r") as archivo:
                for linea in archivo:
                    try:
                        archivo_cedula, nombre, apellido = linea.strip().split(',')
                        if archivo_cedula == cedula:
                            print(f"\n--Persona encontrada--\nCedula: {archivo_cedula}\nNombre: {nombre}\nApellido: {apellido}")
                            return Nodo(archivo_cedula, nombre, apellido)
                    except ValueError:
                        print("Error: Formato de línea incorrecto en el archivo.")
        except FileNotFoundError:
            print("Error al abrir el archivo personas.txt.")
        print(f"La cedula {cedula} no existe en el archivo personas.txt.")
        return None

    def eliminar(self, cedula):
        if not os.path.exists("personas.txt"):
            print("El archivo personas.txt no existe.")
            return False
        temp = self.cabeza
        anterior = None

        while temp is not None:
            if temp.get_cedula() == cedula:
                if anterior is None:
                    self.cabeza = temp.get_siguiente()
                else:
                    anterior.set_siguiente(temp.get_siguiente())
                del temp

                try:
                    with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                        encontrado = False
                        for linea in archivo_entrada:
                            try:
                                archivo_cedula, nombre, apellido = linea.strip().split(',')
                                if archivo_cedula != cedula:
                                    archivo_temporal.write(f"{archivo_cedula},{nombre},{apellido}\n")
                                else:
                                    encontrado = True
                            except ValueError:
                                print("Error: Formato de línea incorrecto en el archivo.")
                    if encontrado:
                        os.remove("personas.txt")
                        os.rename("personas_temp.txt", "personas.txt")
                        return True
                except FileNotFoundError:
                    print("Error al abrir los archivos.")
                return False
            anterior = temp
            temp = temp.get_siguiente()
        return False

    def mostrar(self):
        temp = self.cabeza
        if temp is None:
            print("\nNULL\n")
            return
        while temp is not None:
            print(f"\nCedula: {temp.get_cedula()}\nNombre: {temp.get_nombre()}\nApellido: {temp.get_apellido()} -> ", end="")
            temp = temp.get_siguiente()
        print("\nNULL\n")

    def eliminar_caracter(self, cedula, caracter, lista_auxiliar):
        if not os.path.exists("personas.txt"):
            print("El archivo personas.txt no existe.")
            return
        temp = self.cabeza
        while temp is not None:
            if temp.get_cedula() == cedula:
                nuevo_nombre = temp.get_nombre().replace(caracter, '')
                nuevo_apellido = temp.get_apellido().replace(caracter, '')
                temp.set_nombre(nuevo_nombre)
                temp.set_apellido(nuevo_apellido)
                lista_auxiliar.insertar_a_cola(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
                break
            temp = temp.get_siguiente()

        try:
            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    try:
                        archivo_cedula, nombre, apellido = linea.strip().split(',')
                        if archivo_cedula == cedula:
                            archivo_temporal.write(f"{archivo_cedula},{nuevo_nombre},{nuevo_apellido}\n")
                        else:
                            archivo_temporal.write(f"{archivo_cedula},{nombre},{apellido}\n")
                    except ValueError:
                        print("Error: Formato de línea incorrecto en el archivo.")
            os.remove("personas.txt")
            os.rename("personas_temp.txt", "personas.txt")
            print("Caracter eliminado correctamente del archivo y lista auxiliar actualizada.")
        except FileNotFoundError:
            print("Error al abrir los archivos.")

    def cifrar_caracter(self, cedula, caracter, desplazamiento, lista_auxiliar):
        if not os.path.exists("personas.txt"):
            print("El archivo personas.txt no existe.")
            return
        temp = self.cabeza
        while temp is not None:
            if temp.get_cedula() == cedula:
                def cifrar(c):
                    if c == caracter and c.isalpha():
                        base = 'a' if c.islower() else 'A'
                        return chr((ord(c) - ord(base) + desplazamiento) % 26 + ord(base))
                    return c

                nuevo_nombre = ''.join(cifrar(c) for c in temp.get_nombre())
                nuevo_apellido = ''.join(cifrar(c) for c in temp.get_apellido())
                temp.set_nombre(nuevo_nombre)
                temp.set_apellido(nuevo_apellido)
                # Actualizar la lista auxiliar
                lista_auxiliar.eliminar(cedula)
                lista_auxiliar.insertar_a_cola(temp.get_cedula(), nuevo_nombre, nuevo_apellido)
                break
            temp = temp.get_siguiente()

        # Actualizar la lista principal
        self.actualizar_archivo("personas.txt")

        try:
            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    try:
                        archivo_cedula, nombre, apellido = linea.strip().split(',')
                        if archivo_cedula == cedula:
                            archivo_temporal.write(f"{archivo_cedula},{nuevo_nombre},{nuevo_apellido}\n")
                        else:
                            archivo_temporal.write(f"{archivo_cedula},{nombre},{apellido}\n")
                    except ValueError:
                        print("Error: Formato de línea incorrecto en el archivo.")
            os.remove("personas.txt")
            os.rename("personas_temp.txt", "personas.txt")
            print(f"Caracter cifrado correctamente con desplazamiento {desplazamiento}. Archivo actualizado y lista auxiliar actualizada.")
        except FileNotFoundError:
            print("Error al abrir los archivos.")

    def guardar_en_archivo(self, cedula, nombre, apellido, nombre_archivo):
        try:
            with open(nombre_archivo, "a") as archivo:
                archivo.write(f"{cedula},{nombre},{apellido}\n")
        except FileNotFoundError:
            print("Error al abrir el archivo para escritura.")

    def cargar_desde_archivo(self, nombre_archivo):
        if not os.path.exists(nombre_archivo):
            print(f"El archivo {nombre_archivo} no existe.")
            return
        self.cabeza = None  # Clear the list before loading
        try:
            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    try:
                        cedula, nombre, apellido = linea.strip().split(',')
                        if cedula and nombre and apellido:
                            self.insertar_a_cola(cedula, nombre, apellido)
                    except ValueError:
                        print("Error: Formato de línea incorrecto en el archivo.")
        except FileNotFoundError:
            print("No se pudo abrir el archivo.")

    def actualizar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, "w") as archivo:
                actual = self.cabeza
                while actual is not None:
                    archivo.write(f"{actual.cedula},{actual.nombre},{actual.apellido}\n")
                    actual = actual.siguiente
        except FileNotFoundError:
            print(f"Error al abrir el archivo {nombre_archivo}.")
