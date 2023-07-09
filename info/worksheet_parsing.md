=:
Función para detectar este símbolo y guardar/cambiar la variable de entorno/local?

"ARG='123'" y 'ARG="123"'
No se registran para luego expandirse.

variable1='hola'
variable2="adios"

variable3='$variable1'
variable4="$variable1"

echo $variable3
	-'$variable1'
echo $variable4
	- 'valor'

$:
Función para que reemplace la variable por su valor.
O la busca en el historial o la coge de una variable global que es el retorno
de la ejecución del último programa.

"$ARG" sí se expande.
'$ARG' no se expande.

*:
Función para que reemplace la variable por todos los valores con los caracteres detrás de *.

?:
Función para controlar el punto de interrogación. Algo similar al *.













Ejecutar primera palabra siempre como comando y el resto pasarlo como argumento.



