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
1. gestionar heredocs
2. Buscar archivos
3. checkeo de errores e imprimir errores
	* En caso de error dejar error en 1
		- Permisos
		- Existencia de archivos
		- File es Null (No imprime)
4. Preparar ejecucion
	* Crear pipes
5. Setear input_fd y output_fd
	* Cuando halla un input o output _redirect ignorar pipe y setearlo en el archivo
6. Ejecucion
	* Ejecutar los t_cmd que tengan error a cero

