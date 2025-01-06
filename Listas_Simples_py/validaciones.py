import msvcrt  # For capturing single characters on Windows

def capturar_solo_numeros():
    entrada = ''
    while True:
        try:
            char = msvcrt.getch().decode('utf-8')
            if char.isdigit():
                entrada += char
                print(char, end='', flush=True)
            elif char == '\r':  # Enter key
                print()
                if entrada:
                    return int(entrada)
                else:
                    print("Entrada inválida. Por favor, ingrese solo números.")
                    print("Ingrese una opcion:")
                    entrada = ''
            elif char == '\x08':  # Backspace key
                if entrada:
                    entrada = entrada[:-1]
                    print('\b \b', end='', flush=True)
        except UnicodeDecodeError:
            print("\nEntrada inválida. Por favor, ingrese solo números.")
            entrada = ''

def capturar_cedula():
    entrada = ''
    while True:
        try:
            char = msvcrt.getch().decode('utf-8')
            if char.isdigit():
                entrada += char
                print(char, end='', flush=True)
            elif char == '\r':  # Enter key
                print()
                if not entrada:
                    print("La cédula no puede estar vacía. Intente de nuevo.")
                    print("Ingrese la cedula:")
                elif entrada.isdigit() and len(entrada) == 10:
                    return entrada
                else:
                    print("Cédula inválida. Debe contener solo números y tener 10 dígitos.")
                    print("Ingrese la cedula:")
                entrada = ''
            elif char == '\x08':  # Backspace key
                if entrada:
                    entrada = entrada[:-1]
                    print('\b \b', end='', flush=True)
        except UnicodeDecodeError:
            print("\nEntrada inválida. Por favor, ingrese solo números.")
            entrada = ''

def capturar_solo_letras():
    entrada = ''
    while True:
        try:
            char = msvcrt.getch().decode('utf-8')
            if char.isalpha():
                entrada += char
                print(char, end='', flush=True)
            elif char == '\r':  # Enter key
                print()
                if len(entrada) >= 3 and entrada.isalpha():
                    return entrada
                else:
                    print("Entrada inválida. Debe contener al menos 3 letras.")
                    entrada = ''
            elif char == '\x08':  # Backspace key
                if entrada:
                    entrada = entrada[:-1]
                    print('\b \b', end='', flush=True)
        except UnicodeDecodeError:
            print("\nEntrada inválida. Por favor, ingrese solo letras.")
            entrada = ''

def capturar_una_letra():
    while True:
        try:
            char = msvcrt.getch().decode('utf-8')
            if char.isalpha() and len(char) == 1:
                print(char)
                return char
            elif char == '\x08':  # Backspace key
                print('\b \b', end='', flush=True)
            else:
                print("\nEntrada inválida. Por favor, ingrese solo una letra.")
        except UnicodeDecodeError:
            print("\nEntrada inválida. Por favor, ingrese solo una letra.")

def validar_cedula_real(cedula):
    return len(cedula) == 10 and cedula.isdigit()

def validar_cedula_unica(cedula):
    try:
        with open("personas.txt", "r") as archivo:
            for linea in archivo:
                archivo_cedula, _, _ = linea.strip().split(',')
                if archivo_cedula == cedula:
                    return False
    except FileNotFoundError:
        pass
    return True

def normalizar_nombre(nombre):
    return nombre.strip().title()

def validar_solo_letras(nombre):
    return nombre.isalpha()

def validar_numero_1a25():
    while True:
        entrada = ''
        while True:
            try:
                char = msvcrt.getch().decode('utf-8')
                if char.isdigit():
                    entrada += char
                    print(char, end='', flush=True)
                elif char == '\r':  # Enter key
                    print()
                    if entrada:
                        numero = int(entrada)
                        break
                    else:
                        print("Entrada inválida. Por favor, ingrese solo números.")
                        print("Ingrese un número entre 1 y 25:")
                        entrada = ''
                elif char == '\x08':  # Backspace key
                    if entrada:
                        entrada = entrada[:-1]
                        print('\b \b', end='', flush=True)
            except UnicodeDecodeError:
                print("\nEntrada inválida. Por favor, ingrese solo números.")
                entrada = ''
        
        if 1 <= numero <= 25:
            return numero
        print("Número inválido. Debe estar entre 1 y 25.")

def registrar_cedula(cedula):
    try:
        with open("cedulas_registradas.txt", "a") as archivo:
            archivo.write(f"{cedula}\n")
    except FileNotFoundError:
        print("Error al abrir el archivo para registrar la cédula.")
