
# Notas

" or ' parsing

" o ' solo cambia si se hace un split a los espacios o no
	e.j. mkdir "h     ola"" Que tal" " estas"

contenido dentro de " expande las variables mientras contenido dentro de ' no las expande

Solo hay que tomar en cuenta si estas en las comillas de mas afuera
	e.j. mkdir 'Hola "$PATH"'

# Pasos para parsing:
## 1. Variables de entorno
* Una funcion que sea consciente de cuales comillas son las que le rodean de mas afuera (no reemplazar en caso de comillas simples) y sustituya las variables
* Es el primer paso (antes de la normalizacion de espacios) debido a el ejemplo:
	```
	1. HM="          a       asd    |"
	2. echo $HM
	3. echo "$HM"
	```
* Solo son validos para expandir los caracteres alfanumericos
* Al expandir solo buscara hasta que no halla caracteres valido
* \$[caracter no valido] o \$ no sera considerado como valido para expandir y sera ignorado, se buscara el proximo \$
* Caso especial
	- echo $?a

## 2. Checkear errores y normalizacion
* Mirar comillas sin cerrar, solo mirar las de mas afuera
	* Nota: echo " ' "" ' ", echo ' " ' "" y echo ' " ' "
		* Prueba que no se puede hacer nesting de comillas
* Normalizar espacios y tabuladores en un espacio si esta fuera de comillas

## 3. Separar por operadores, tokenizar
* crear la estructura t_raw_line
* funcion tokenizadora:
	* Input:
		* char * inicio de token
		* int *err
		* e_state *state

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
* Finite State Machine (Buscando simplicidad y generalizacion en la implementacion)
	* No tiene mucho sentido por estos casos
		```
		>hol echo "hola"
		cat  <parsing_header.h test_main.c

		echo "hola" | cat <parsing_header.h test_main.c
			Translates to --> cat <parsing_header.h test_main.c
		echo "Hola" > out | <infile cat > out2
		cat | cat | cat < parsing_header.h
		```
	``` c
	enum e_states
	{
		input_parsing,
		command_parsing,
		output_parsing
	};
	```
	* Ya que un operador siempre empieza con su signo (excepto pipes).
		- Al encontrarse un caracter de operador e.g. '|'.
			* Al haber una carencia de operador al principio se asume un comando
		- Se avanza hasta encontrar el final del token y se guarda en un t_raw_cmd. Este es buen lugar para checkear archivos que faltan.
			* Encontrar otro operador o final de string
				* Pipes
			* Operador con numero de nombres definidos. Debido a su similar estructura sintactica se puede reusar la funcion.
				* Principio del string
					* Stdin redirect '<'
					* Stdin delimiter (Here doc) '<<'
				* Final del string
					* Stdout redirect '>'
					* Stdout append '>>'
		- Se guarda el final y se repite con el proximo token

#### Nueva filosofia de parseo dados los nuevos casos limitantes de la arquitectura anterior
* Casos a tener en cuenta
```
PROBAR TODO EN BASH, tiene comportamiento diferente, bash es mas sencillo ademas

	<infile cat > outi1 | <<"DOc" cato >outi2
	<infile cat > outi1 | <<"DOc" cato >outi | << "DOc" cat > outi3
		(outi3 is successfully created with heredoc content)
	cat | cat | cat | cat | <infile cat
		(Este no se si lo entiendo)
```
Gestion de errores
```
<infile <infile2 cat
	equivale a
<infile2 cat

echo "Hello World" > outi1 > outi2
	equivale a
echo "Hello World" > outi2
```

* Nueva estructura
``` c

//* Not used for pipes, pipes will be created according to the number of commands
//* Redirections have a higher priority than pipes
//	* Meaning that when both pipe and redirect (i.e. >) are present command will be dup'ed to redirect
typedef struct t_raw_redirect
{
	char				*file;
	enum e_operators	type;
}

// Input and output _redirect are nullable
typedef struct s_raw_cmd
{
	char			*file;
	char			**argv;
	t_raw_redirect	*input_redirect;
	t_raw_redirect	*output_redirect;
}		t_raw_cmd


typedef struct s_raw_line
{
	t_raw_cmd		*raw_commands;
	size_t			len;
}		t_raw_line;

```
* Dado estos nuevos casos, se puede seguir este pseudocodigo
	1. splitear por comandos (por pipes '|')
	2. construir cada t_raw_cmd
		- Buscar ultimo [infile, heredoc] y [outfile, outfile append] y parsearlo
			- Checkear en cada uno tenga su string correspondiente, si no mostrar error y liberar t_raw_line
		- en los casos sin comando pero con operador, dejar file en null
			- i.e. < infile > outfile | cat
	3. construir t_raw_line

## 4. Checkear errores en la estructura tokenizada
* Si hay un stdout redirect (>) que no es el ultimo token por ejemplo
* No hay ningun comando