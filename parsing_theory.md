
# Notas

" or ' parsing

" o ' solo cambia si se hace un split a los espacios o no
	e.j. mkdir "h     ola"" Que tal" " estas"

contenido dentro de " expande las variables mientras contenido dentro de ' no las expande

Solo hay que tomar en cuenta si estas en las comillas de mas afuera
	e.j. mkdir 'Hola "$PATH"'

# Funciones basicas para parsing
* funcion que avance un token
	* Input:
		* Pasas un char * de inicio que puede ser arbitrario
	* Output:
		* Te devuelve el puntero del inicio del siguiente comando, archivo
		* Opcionalmente, pasando un puntero a puntero diferente de cero setea al puntero del operador previo, otro para el siguiente
			* Si no hay operador siguiente o previo lo setea a 0
	
# Pasos para parsing:
1. Variables de entorno
	* Una funcion que sea consciente de cuales comillas son las que le rodean de mas afuera y sustituya las variables
	* Es el primer paso (antes de la normalizacion de espacios) debido a el ejemplo:
		1. HM="          a       asd    |"
		2. echo $HM
		3. echo 

2. Checkear errores y normalizacion
	* Mirar comillas sin cerrar, solo mirar las de mas afuera
		* Nota: echo " ' "" ' ", echo ' " ' "" y echo ' " ' "
			* Prueba que no se puede hacer nesting de comillas
	* Normalizar espacios y tabuladores en un espacio si esta fuera de comillas
	* Comprobar que cada operador tenga sus archivos correspondientes

3. Separar por operadores, tokenizar
	* crear la estructura t_raw_line
	* funcion tokenizadora:
		* Input:
			* Pasas un char puntero de inicio
		* Output:
			* Con return:
				* t_raw_cmd *
		* Notas:
			* Ya que la los espacios fuera de comillas estan normalizados 
			* Aqui se checkean los argv
				* Los argv no deben contener las comillas de mas afuera: echo "Hola"Que" Tal'"
				* Para conseguir los argv se puede usar un split que no devuelva las comillas de mas afuera y no splitee dentro de comillas
