- Parse

• No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como \ (barra invertida) o ; (punto y coma).
• Gestionar que la ’ evite que el shell interprete los metacaracteres en la secuencia entrecomillada.
• Gestionar que la " evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando $.
• Implementar redirecciones:
	◦ < debe redirigir input.
	◦ > debe redirigir output.
	◦ “<<” debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca.
		No necesita actualizar el historial.
	◦ “>>” debe redirigir el output en modo append.
• Implementar pipes (carácter |). El output de cada comando en la pipeline se conecta a través de un pipe al input del siguiente comando.
• Gestionar las variables de entorno ($ seguidos de caracteres) que deberán expandirse a sus valores.
• Gestionar $?, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.

