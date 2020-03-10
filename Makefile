CXX = clang++

dynamic-wallpaper: $(obj)
	@mkdir -p bin
	clang++ -std=c++17 -o bin/dynamic-wallpaper src/*.cpp

install:
	@cp bin/dynamic-wallpaper /usr/local/bin/dynamic-wallpaper

uninstall:
	@rm /usr/local/bin/dynamic-wallpaper

