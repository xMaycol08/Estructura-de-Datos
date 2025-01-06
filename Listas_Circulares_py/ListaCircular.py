from NodoCircular import NodoCircular
import os

class ListaCircular:
    def __init__(self):
        self.primero = None
        self.ultimo = None

    def insertar(self, cedula, nombre, apellido):
        try:
            nuevo = NodoCircular(cedula, nombre, apellido)
            if self.primero is None:
                self.primero = nuevo
                self.ultimo = nuevo
                self.ultimo.set_siguiente(self.primero)
            else:
                self.ultimo.set_siguiente(nuevo)
                self.ultimo = nuevo
                self.ultimo.set_siguiente(self.primero)
        except Exception as e:
            print(f"Error al insertar: {e}")

    def buscar(self, cedula):
        try:
            if self.primero is None:
                return None
            temp = self.primero
            while True:
                if temp.get_cedula() == cedula:
                    return temp
                temp = temp.get_siguiente()
                if temp == self.primero:
                    break
            return None
        except Exception as e:
            print(f"Error al buscar: {e}")
            return None

    def eliminar(self, cedula):
        try:
            if self.primero is None:
                return False
            temp = self.primero
            anterior = self.ultimo
            while True:
                if temp.get_cedula() == cedula:
                    if temp == self.primero:
                        if self.primero == self.ultimo:
                            self.primero = None
                            self.ultimo = None
                        else:
                            self.primero = self.primero.get_siguiente()
                            self.ultimo.set_siguiente(self.primero)
                    elif temp == self.ultimo:
                        self.ultimo = anterior
                        self.ultimo.set_siguiente(self.primero)
                    else:
                        anterior.set_siguiente(temp.get_siguiente())
                    return True
                anterior = temp
                temp = temp.get_siguiente()
                if temp == self.primero:
                    break
            return False
        except Exception as e:
            print(f"Error al eliminar: {e}")
            return False

    def eliminar_de_archivo(self, cedula, nombre_archivo):
        try:
            with open(nombre_archivo, "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    if not linea.startswith(cedula + ","):
                        archivo_temporal.write(linea)
            os.remove(nombre_archivo)
            os.rename("personas_temp.txt", nombre_archivo)
            self.eliminar(cedula)  # Remove the node from the list
        except Exception as e:
            print(f"Error al eliminar del archivo: {e}")

    def eliminar_de_cubetas(self, cedula):
        try:
            for i in range(26):
                cubeta_nombre = f"cubeta_{i}.txt"
                if os.path.isfile(cubeta_nombre):
                    with open(cubeta_nombre, "r") as archivo_entrada, open(f"temp_{cubeta_nombre}", "w") as archivo_temp:
                        for linea in archivo_entrada:
                            if not linea.startswith(cedula + ","):
                                archivo_temp.write(linea)
                    os.remove(cubeta_nombre)
                    os.rename(f"temp_{cubeta_nombre}", cubeta_nombre)
        except Exception as e:
            print(f"Error al eliminar de las cubetas: {e}")

    def mostrar(self):
        try:
            if self.primero is None:
                print("La lista está vacía.")
                return

            actual = self.primero
            while True:
                print(f"Cedula: {actual.get_cedula()}\nNombre: {actual.get_nombre()}\nApellido: {actual.get_apellido()}\n->")
                actual = actual.siguiente
                if actual == self.primero:
                    break
            print("null")
        except Exception as e:
            print(f"Error al mostrar la lista: {e}")

    def eliminar_caracter(self, cedula, caracter, lista_auxiliar):
        try:
            temp = self.buscar(cedula)
            if temp is None:
                print("Cedula no encontrada.")
                return

            nuevo_nombre = temp.get_nombre().replace(caracter, '')
            nuevo_apellido = temp.get_apellido().replace(caracter, '')

            temp.set_nombre(nuevo_nombre)
            temp.set_apellido(nuevo_apellido)
            lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)

            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    datos = linea.strip().split(',')
                    if datos[0] == cedula:
                        archivo_temporal.write(f"{datos[0]},{nuevo_nombre},{nuevo_apellido}\n")
                    else:
                        archivo_temporal.write(linea)

            os.remove("personas.txt")
            os.rename("personas_temp.txt", "personas.txt")

            print("Caracter eliminado correctamente del archivo y lista auxiliar actualizada.")
        except Exception as e:
            print(f"Error al eliminar caracter: {e}")

    def cifrar_caracter(self, cedula, caracter, desplazamiento, lista_auxiliar):
        try:
            temp = self.buscar(cedula)
            if temp is None:
                print("Cedula no encontrada.")
                return

            def cifrar(c):
                if c == caracter:
                    base = 'a' if c.islower() else 'A'
                    return chr((ord(c) - ord(base) + desplazamiento) % 26 + ord(base))
                return c

            nuevo_nombre = ''.join(cifrar(c) for c in temp.get_nombre())
            nuevo_apellido = ''.join(cifrar(c) for c in temp.get_apellido())

            temp.set_nombre(nuevo_nombre)
            temp.set_apellido(nuevo_apellido)

            lista_auxiliar.insertar(temp.get_cedula(), nuevo_nombre, nuevo_apellido)

            with open("personas.txt", "r") as archivo_entrada, open("personas_temp.txt", "w") as archivo_temporal:
                for linea in archivo_entrada:
                    datos = linea.strip().split(',')
                    if datos[0] == cedula:
                        archivo_temporal.write(f"{datos[0]},{nuevo_nombre},{nuevo_apellido}\n")
                    else:
                        archivo_temporal.write(linea)

            os.remove("personas.txt")
            os.rename("personas_temp.txt", "personas.txt")

            print(f"Caracter cifrado correctamente con desplazamiento {desplazamiento}. Archivo actualizado y lista auxiliar actualizada.")
        except Exception as e:
            print(f"Error al cifrar caracter: {e}")

    def guardar_en_archivo(self, cedula, nombre, apellido, nombre_archivo):
        try:
            with open(nombre_archivo, "a") as archivo:
                archivo.write(f"{cedula},{nombre},{apellido}\n")
        except Exception as e:
            print(f"Error al guardar en archivo: {e}")

    def cargar_desde_archivo(self, nombre_archivo):
        try:
            if not os.path.isfile(nombre_archivo):
                print("No se pudo abrir el archivo.")
                return

            with open(nombre_archivo, "r") as archivo:
                for linea in archivo:
                    datos = linea.strip().split(',')
                    if len(datos) == 3:
                        self.insertar(datos[0], datos[1], datos[2])
        except Exception as e:
            print(f"Error al cargar desde archivo: {e}")
