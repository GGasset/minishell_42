
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
## 1. Variables de entorno
* Una funcion que sea consciente de cuales comillas son las que le rodean de mas afuera (no reemplazar en caso de comillas simples) y sustituya las variables
* Es el primer paso (antes de la normalizacion de espacios) debido a el ejemplo:
	1. HM="          a       asd    |"
	2. echo $HM
	3. echo "$HM"
* Solo son validos para expandir los caracteres alfanumericos
* Al expandir solo buscara hasta que no halla caracteres valido
* $[caracter no valido] o $ no sera considerado como valido para expandir y sera ignorado, se buscara el proximo $
* Caso especial
	- echo $?a

## 2. Checkear errores y normalizacion
* Mirar comillas sin cerrar, solo mirar las de mas afuera
	* Nota: echo " ' "" ' ", echo ' " ' "" y echo ' " ' "
		* Prueba que no se puede hacer nesting de comillas
* Normalizar espacios y tabuladores en un espacio si esta fuera de comillas
* Comprobar que cada operador tenga sus archivos correspondientes

## 3. Separar por operadores, tokenizar
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

* ### Posibles funciones tokenizadoras
	* #### Se presupone que la estructura tokenizada es esta
		``` c
			typedef struct s_raw_cmd
			{
				char				*file;
				char				**argv;
				enum e_operators	type;
				int					is_builtin;
			}		t_raw_cmd;

			/*
			* example "<in cat | cat>outi"
			raw_commands:
				- {in, 0, stdin_redirect}
				- {cat, {"cat", 0}, pipe}
				- {cat, {"cat", 0}, pipe}
				- {outi, 0, stdout_redirect}
			len: 4
			* example "<< "EOF" cat | cat -e | cat"
			raw_commands:
				- {EOF, 0, stdin_delimiter}
				- {cat, {"cat", 0}, pipe}
				- {cat, {"cat", "-e", 0}, pipe}
				- {cat, {"cat", 0}, pipe}
			* example "<in cat"
			raw_commands:
				- {in, 0, stdin_redirect}
				- {cat, {"cat", 0}, none}
			* example "<in cat > out"
				- {in, 0, stdin_redirect}
				- {cat, {"cat", 0}, none}
				- {out, 0, stdout_redirect}
			*/
			typedef struct s_raw_line
			{
				t_raw_cmd		*raw_commands;
				size_t			len;
			}		t_raw_line;

		```
* Finite State Machine (Un estado por token)
	* Ya que un operador siempre empieza con su signo (excepto pipes).
		- Al encontrarse un caracter de operador e.g. '|'.
			* Al haber una carencia de operador al principio se asume un comando
		- Se avanza hasta encontrar el final del token
			* Encontrar otro operador o final de string
				* Pipes
			* Operador con numero de nombres definidos
				* Principio del string
					* Stdin redirect
					* Stdin delimiter (Here doc)
				* Final del string
					* Stdout redirect
					* Stdout append
		- Se guarda el final y se repite con el proximo token



## 4. Checkear errores en la estructura tokenizada
	* Si hay un stdout redirect (>) que no es el ultimo token por ej