

Pasos:
	Checkear errores:
		* Chekear si los comando son builtin

		* Conseguir la ruta de el nombre de los archivos
			- (Hecho en pipex)
	
		* Comprobar existencia de archivos si se requiere, permisos de archivos (Unicamente los permisos y archivos necesarios)

	* Crear la estructura t_exe
		* crear un t_cmd por comando
			* Un comando es un t_raw_cmd con tipo de operador:
				* Sin redireccion de stdout
					- no stdout redirect
				* Con redireccion de stdout
					- pipe
						* mirar el comando de adelante y atras si existen para saber si conectarlos
				- no pipe stdout redirect
		* Añadir operadores de t_cmd
			- abrir fds o pipes
			- En caso de heredoc (<<) crear archivo, leer de stdin y traducir a stdin redirect (<)
