# C-studia

Programy zostały napisane na systemie ubuntu 22.04.

W celu skompilowania jakiegokolwiek programu należy skorzystać z komendy:

> gcc `nazwa_pliku` -o `nazwa_pliku_wyjściowego` -`flagi`

## Flagi

W przypadku gdy program korzysta z biblioteki `<math.h>` należy użyć flagi `lm`

Jeden z programów korzysta z biblioteki `<uuid/uuid.h>`, istnieje szansa, że nie występuje ona domyślnie na komputerze.
W takim wypadku należy ją doinstalować aby program mógł zostać poprawnie skompilowany - [Jak zainstalować uuid/uuid.h](https://stackoverflow.com/questions/1089741/how-do-i-obtain-use-libuuid).

Po doinstalowaniu biblioteki należy użyć flagi `luuid` w celu kompilacji.
