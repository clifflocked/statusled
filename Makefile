JETGPIO_URL = https://github.com/Rubberazer/JETGPIO
JETGPIO_DIR = JETGPIO

all: statusled

jetgpio:
	@echo "Downloading Jetgpio from source $(JETGPIO_URL)"
	git clone $(JETGPIO_URL)
	@echo "Compiling Jetgpio"
	cd $(JETGPIO_DIR) && sudo make $(nproc)
	cd $(JETGPIO_DIR) && sudo make install
	@echo "Reboot to finish installation of Jetgpio libraries"

statusled:
	@echo "Building statusled"
	cd $(JETGPIO_DIR) && \
	gcc -c -fpic status.c -o status.o
	gcc -shared -o statusled status.o -LJETGPIO-main -ljetgpio
