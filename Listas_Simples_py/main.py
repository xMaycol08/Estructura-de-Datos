'''
Module:  main.cpp
Author:  Maycol Celi.
Date: 17/12/2024
Purpose: Metodo de Ordenamiento Externo para lista simple con el metodo (Distribution sort)
University: Universidad de las Fuerzas Armadas - ESPE
'''
import os
from lista_simple import ListaSimple
from metodo_ordenamiento_externo import MetodoOrdenamientoExterno
from validaciones import capturar_solo_numeros, capturar_cedula, validar_cedula_real, capturar_solo_letras, normalizar_nombre, validar_solo_letras, capturar_una_letra, validar_numero_1a25

def mostrar_menu():
    print("\n----------------------------------------------------")
    print("\t\t MENU DE OPCIONES\t\t")
    print("----------------------------------------------------")
    print("1. Insertar persona")
    print("2. Buscar persona")
    print("3. Eliminar persona")
    print("4. Mostrar lista")
    print("5. Eliminar caracter de nombre")
    print("6. Cifrar un caracter")
    print("7. Mostrar lista auxiliar")
    print("8. Ordenar lista por nombre (Distribution Sort)")
    print("9. Mostrar archivo de distribucion ordenado")
    print("10. Salir")

def pausar():
    input("Presione Enter para continuar...")

def limpiar_consola():
    os.system('cls' if os.name == 'nt' else 'clear')

def main():
    lista_principal = ListaSimple()
    lista_auxiliar = ListaSimple()
    metodo_ordenamiento = MetodoOrdenamientoExterno()
    cedula, nombre, apellido = None, None, None
    desplazar = 0
    caracter = ''
    opcion = 0

    lista_principal.cargar_desde_archivo("personas.txt")

    while opcion != 10:
        limpiar_consola()
        mostrar_menu()
        print("Ingrese una opción: ", end='', flush=True)
        opcion = capturar_solo_numeros()

        if opcion == 1:  # Insertar persona
            print("Ingrese la cedula: ", end='', flush=True)
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                pausar()
                continue
            if not lista_principal.validar_cedula_unica(cedula):
                print("La cedula ya esta registrada. Intente de nuevo.")
                pausar()
                continue

            print("Ingrese el nombre: ", end='', flush=True)
            nombre = capturar_solo_letras()
            nombre = normalizar_nombre(nombre)
            if not validar_solo_letras(nombre):
                print("Error: El nombre debe contener solo letras. Intente nuevamente.")
                pausar()
                continue

            print("Ingrese el apellido: ", end='', flush=True)
            apellido = capturar_solo_letras()
            apellido = normalizar_nombre(apellido)
            if not validar_solo_letras(apellido):
                print("Error: El apellido debe contener solo letras. Intente nuevamente.")
                pausar()
                continue

            lista_principal.insertar_a_cola(cedula, nombre, apellido)
            lista_principal.guardar_en_archivo(cedula, nombre, apellido, "personas.txt")
            print("Persona registrada exitosamente.")
            pausar()

        elif opcion == 2:  # Buscar persona
            if lista_principal.cabeza is None:
                print("No existen datos para buscar.")
                pausar()
                continue

            print("Ingrese la cedula: ", end='', flush=True)
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                pausar()
                continue

            persona = lista_principal.buscar(cedula)
            if persona is None:
                pausar()
            else:
                pausar()

        elif opcion == 3:  # Eliminar persona
            if lista_principal.cabeza is None:
                print("No existen datos para eliminar.")
                pausar()
                continue

            print("Ingrese la cedula: ", end='', flush=True)
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                pausar()
                continue

            if lista_principal.eliminar(cedula):
                print("Persona eliminada exitosamente.")
                # Eliminar de las cubetas
                archivos_cubetas = []
                metodo_ordenamiento.distribuir_datos("personas.txt", archivos_cubetas)
                for archivo in archivos_cubetas:
                    metodo_ordenamiento.eliminar_de_cubeta(archivo, cedula)
            else:
                print("Error: Persona no encontrada o no pudo ser eliminada.")
            pausar()

        elif opcion == 4:  # Mostrar lista principal
            lista_principal.mostrar()
            pausar()

        elif opcion == 5:  # Eliminar carácter de nombre
            print("Ingrese la cedula: ", end='', flush=True)
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                pausar()
                continue

            persona_encontrada = lista_principal.buscar(cedula)
            if persona_encontrada is None:
                pausar()
                continue

            print("Ingrese el caracter a eliminar: ", end='', flush=True)
            caracter = capturar_una_letra()
            lista_principal.eliminar_caracter(cedula, caracter, lista_auxiliar)
            lista_principal.actualizar_archivo("personas.txt")  # Actualizar el archivo personas.txt
            pausar()

        elif opcion == 6:  # Cifrar carácter
            print("Ingrese la cedula: ", end='', flush=True)
            cedula = capturar_cedula()
            if not validar_cedula_real(cedula):
                print("Cedula invalida. Intente de nuevo.")
                pausar()
                continue

            persona_encontrada = lista_principal.buscar(cedula)
            if persona_encontrada is None:
                print("Error: La cedula no existe en el archivo.")
                pausar()
                continue

            print("Ingrese el caracter a cifrar: ", end='', flush=True)
            caracter = capturar_una_letra()
            print("Ingrese el desplazamiento (1-25): ", end='', flush=True)
            desplazar = validar_numero_1a25()
            lista_principal.cifrar_caracter(cedula, caracter, desplazar, lista_auxiliar)
            lista_principal.actualizar_archivo("personas.txt")  # Actualizar el archivo personas.txt
            pausar()

        elif opcion == 7:  # Mostrar lista auxiliar
            lista_auxiliar.mostrar()
            pausar()

        elif opcion == 8:  # Ordenar lista por nombre (Distribución Sort)
            lista_principal = ListaSimple()  # Reset the list to avoid duplicates
            lista_principal.cargar_desde_archivo("personas.txt")  # Reload from file

            archivos_cubetas = []
            metodo_ordenamiento.distribuir_datos("personas.txt", archivos_cubetas)

            if not os.path.exists("personas.txt") or os.path.getsize("personas.txt") == 0:
                print("El archivo 'personas.txt' no existe o está vacío. No hay datos para procesar.")
                metodo_ordenamiento.eliminar_todas_las_cubetas()  # Eliminar todas las cubetas existentes
                pausar()
                continue

            for archivo in archivos_cubetas:
                metodo_ordenamiento.ordenar_archivo(archivo)

            metodo_ordenamiento.fusionar_archivos(archivos_cubetas, "personas_ordenadas.txt")
            print("La lista ha sido ordenada y guardada en 'personas_ordenadas.txt'.")
            pausar()

        elif opcion == 9:  # Mostrar archivo de distribución ordenado
            if not os.path.exists("personas.txt") or os.path.getsize("personas.txt") == 0:
                print("El archivo 'personas.txt' no existe o está vacío. No hay datos para mostrar.")
                if os.path.exists("personas_ordenadas.txt"):
                    os.remove("personas_ordenadas.txt")
                pausar()
                continue

            if not os.path.exists("personas_ordenadas.txt") or os.path.getsize("personas_ordenadas.txt") == 0:
                print("El archivo 'personas_ordenadas.txt' no existe o está vacío. No hay datos para mostrar.")
                pausar()
                continue

            metodo_ordenamiento.mostrar_archivo("personas_ordenadas.txt")
            pausar()

        elif opcion == 10:  # Salir
            print("Saliendo...")
            pausar()

        else:
            print("Opcion invalida. Intente de nuevo.")
            pausar()

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"Ha ocurrido un error: {e}")
        pausar()
