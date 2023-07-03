- readline: Lee una línea de entrada desde el usuario, incluyendo la funcionalidad de edición básica.

		char *readline(const char *prompt);

- rl_clear_history: Borra todo el historial de líneas ingresadas por el usuario.

		void rl_clear_history(void);

- rl_on_new_line: Realiza tareas de limpieza y reconfiguración después de que el usuario presiona Enter.

		void rl_on_new_line(void);

- rl_replace_line: Reemplaza la línea actualmente ingresada por una nueva línea.

		void rl_replace_line(const char *text, int clear_undo);

- rl_redisplay: Actualiza la línea de entrada en la pantalla.

		void rl_redisplay(void);

- add_history: Agrega una línea al historial de comandos ingresados.

		void add_history(const char *line);

- printf: Imprime datos formateados en la salida estándar.

		int printf(const char *format, ...);

- malloc: Asigna memoria dinámicamente durante el tiempo de ejecución.

		void *malloc(size_t size);

- free: Libera la memoria previamente asignada por malloc u otra función de asignación de memoria.

		void free(void *ptr);

- write: Escribe un número especificado de bytes en un descriptor de archivo.

		ssize_t write(int fd, const void *buf, size_t count);

- access: Verifica si se puede acceder a un archivo con los permisos especificados.

		int access(const char *pathname, int mode);

- open: Abre o crea un archivo para su lectura o escritura.

		int open(const char *pathname, int flags, mode_t mode);

- read: Lee un número especificado de bytes desde un descriptor de archivo.

		ssize_t read(int fd, void *buf, size_t count);

- close: Cierra un descriptor de archivo abierto previamente.

		int close(int fd);

- fork: Crea un nuevo proceso clonando el proceso existente.

		pid_t fork(void);

- wait: Suspende la ejecución del proceso actual hasta que uno de sus procesos secundarios finalice.

		pid_t wait(int *status);

- waitpid: Suspende la ejecución del proceso actual hasta que un proceso secundario específico finalice.

		pid_t waitpid(pid_t pid, int *status, int options);

- wait3: Obsoleto, se utiliza waitpid en su lugar.

- wait4: Obsoleto, se utiliza waitpid en su lugar.

- signal: Establece un manejador de señales para una señal específica.

		void (*signal(int signum, void (*handler)(int)))(int);

- sigaction: Permite un control más avanzado del manejo de señales que signal.

		int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

- kill: Envía una señal a un proceso o grupo de procesos.

		int kill(pid_t pid, int sig);

- exit: Finaliza la ejecución del programa actual.

		void exit(int status);

- getcwd: Obtiene el directorio de trabajo actual.

		char *getcwd(char *buf, size_t size);

- chdir: Cambia el directorio de trabajo actual.

		int chdir(const char *path);

- stat: Obtiene información sobre un archivo o directorio específico.

		int stat(const char *pathname, struct stat *buf);

- lstat: Obtiene información sobre un archivo o directorio, sin seguir enlaces simbólicos.

		int lstat(const char *pathname, struct stat *buf);

- fstat: Obtiene información sobre un descriptor de archivo abierto.

		int fstat(int fd, struct stat *buf);

- unlink: Elimina un archivo existente del sistema de archivos.

		int unlink(const char *pathname);

- execve: Reemplaza el proceso actual con un nuevo proceso.

		int execve(const char *pathname, char *const argv[], char *const envp[]);

- dup: Duplica un descriptor de archivo existente.

		int dup(int oldfd);

- dup2: Duplica un descriptor de archivo existente en otro descriptor especificado.

		int dup2(int oldfd, int newfd);

- pipe: Crea un par de descriptores de archivo utilizados para la comunicación entre procesos.

		int pipe(int pipefd[2]);

- opendir: Abre un directorio para su lectura.

		DIR *opendir(const char *name);

- readdir: Lee la siguiente entrada de un directorio abierto previamente.

		struct dirent *readdir(DIR *dirp);

- closedir: Cierra un directorio abierto previamente.

		int closedir(DIR *dirp);

- strerror: Devuelve una cadena descriptiva correspondiente a un número de error.

		char *strerror(int errnum);

- perror: Imprime un mensaje de error basado en el valor de la variable errno.

		void perror(const char *s);

- isatty: Verifica si un descriptor de archivo se refiere a un terminal interactivo.

		int isatty(int fd);

- ttyname: Devuelve el nombre del terminal asociado con el descriptor de archivo dado.

		char *ttyname(int fd);

- ttyslot: Obtiene el número de entrada en la tabla de términos asociada con el descriptor de archivo dado.

		int ttyslot(void);

- ioctl: Controla el comportamiento de un dispositivo de E/S a través de llamadas al sistema específicas del dispositivo.

		int ioctl(int fd, unsigned long request, ...);

- getenv: Obtiene el valor de una variable de entorno específica.

		char *getenv(const char *name);

- tcsetattr: Establece los atributos del terminal asociado con el descriptor de archivo dado.

		int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

- tcgetattr: Obtiene los atributos actuales del terminal asociado con el descriptor de archivo dado.

		int tcgetattr(int fd, struct termios *termios_p);

- tgetent: Carga las capacidades de la terminal específica en una estructura terminfo.

		int tgetent(char *bp, const char *name);

- tgetflag: Obtiene el valor de una capacidad booleana específica de la terminal.

		int tgetflag(const char *capname);

- tgetnum: Obtiene el valor de una capacidad numérica específica de la terminal.

		int tgetnum(const char *capname);

- tgetstr: Obtiene el valor de una cadena de escape específica de la terminal.

		char *tgetstr(const char *capname, char **area);

- tgoto: Construye una secuencia de escape para colocar el cursor en una ubicación específica.

		char *tgoto(const char *capname, int col, int row);

- tputs: Envía una cadena de escape a la terminal.

		int tputs(const char *str, int affcnt, int (*putc)(int));
