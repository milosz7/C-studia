compile:
ifeq ($(lib),gtk)
	@gcc `pkg-config --cflags gtk4` $(file).c -o ./out/${file}.out `pkg-config --libs gtk4`
	@echo "Kompilacja pliku $(file).c ukończona."
	@./out/$(file).out
endif
ifeq ($(lib),lm)
	@gcc $(file).c -o ./out/$(file).out -lm
	@echo "Kompilacja pliku $(file).c ukończona."
	@./out/$(file).out
endif
ifeq ($(lib),)
	@gcc $(file).c -o ./out/$(file).out
	@echo "Kompilacja pliku $(file).c ukończona."
	@./out/$(file).out
endif

help:
	@echo 'Aby skompilować program użyj komendy "./compile.sh -f *nazwa_pliku* -l *wymagana_biblioteka*"'

