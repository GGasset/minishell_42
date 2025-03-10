

Pasos:
	Checkear errores:
		* Comprobar existencia de archivos si se requiere, permisos de archivos (Unicamente los necesarios)
	
	Conseguir la ruta de el nombre de los archivos
		(Hecho en pipex)

	Crear la estructura t_exe
		* crear un t_cmd por comando
			* Un comando es un t_raw_cmd con tipo de operador:
				- pipe (variaciones)
				- no stdout redirect
				- no pipe stdout redirect
		* Añadir operadores de t_cmd
			- abrir fds o pipes
			- En caso de 
