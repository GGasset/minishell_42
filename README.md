## TO DO

- [X]  Parsing
	- [X]  Funcion principal de parsing (Le pasas el input tal y como llega y sale parseado)
	- [X]  Gestionar Heredoc
	- [X]  LEAK
	- [X]  ELIMINAR COMILLAS DE ARGV Y ARCHIVOS
	- [ ]  Crear carpetas con outfiles
- [ ]  EJECUCION ENTERA
  - [ ] Ejecutar buil-in
	- [ ] Built-in de exit
  - [X] Ejecutar binarios
  - [X] Manejar redirecciones
  - [X] Setear exit status al ultimo comando ejecutado (El ultimo de la linea)
- [ ]  SEÑALES
	- [ ] Ctrl + \
		- [ ] Durante ejecucion
		- [ ] Durante Lectura
	- [ ] Ctrl + C
		- [ ] Durante ejecucion
		- [ ] Durante Lectura
	- [ ] Ctrl + d
		- [ ] Durante ejecucion
		- [ ] Durante Lectura
- [ ]  MAIN
	- [X] Mensaje para enunciar que se espera un comando nuevo
	- [X] Historial
	- [X] Eliminar archivos temporales despues de la ejecucion
	- [ ] Add execution function
	- [ ] Add signal setup
- [ ]  BUILTINS
	- [x] echo
		- [x] -n
	- [x] cd
		- [x] ruta relativa
		- [x] ruta absoluta
	- [x] pwd
	- [x] export ("export var=val", check "export var = val", "export var= val" y "export var=a val")
	- [X] unset
	- [X] env
	- [ ] exit
- [ ]  PARA EL FINAL, CHECKEAR MIL VECES TODO
	- [ ] Compro
	- [ ] Norminette
	- [ ] Exit status
	- [ ] Leaks
	- [ ] Señales
	- [ ] Built-ins
