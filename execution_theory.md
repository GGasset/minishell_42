# Notas

## casos extremos

<archivo (Imprimir archivo entero normal)
>archivo
<archivo1 > archivo2

## Advertencias de implemtacion
* Cualquier string copiado de la estructura de parseo a la de ejecucion debe de ser duplicado
	- Esto para poder hacer frees mas facilmente y sin casos extremos.

# Pasos:
* Crear t_exe con valores por defecto, el array tambien
1. Buscar archivos
2. checkeo de errores e imprimir errores
	* En caso de error dejar la flag error en 1
		- Permisos
		- Existencia de archivos
		- File es Null (No imprime)
3. Preparar ejecucion
	* Crear pipes
		*  Una de entrada, una de salida, una entre cada par de comandos
	* Conectar pipes de entrada y salida con stdinput y stdoutput de minishell
4. Setear input_fd y output_fd
	* Cuando halla un input o output _redirect ignorar pipe y setearlo en el archivo
5. Ejecucion
	* Ejecutar los t_cmd que tengan error a cero

