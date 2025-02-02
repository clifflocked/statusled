JETGPIO_URL = https://github.com/Rubberazer/JETGPIO/archive/refs/heads/main.zip
JETGPIO_ZIP = JETGPIO-main.zip
JETGPIO_DIR = JETGPIO-main

all: statusled

jetgpio:
	@echo "Downloading Jetgpio from source $(JETGPIO_URL)"
	wget $(JETGPIO_URL) -O $(JETGPIO_ZIP)
	@echo "Unzipping $(JETGPIO_ZIP)"
	unzip $(JETGPIO_ZIP)
	@echo "Compiling Jetgpio"
	cd $(JETGPIO_DIR) && sudo make $(nproc)
	cd $(JETGPIO_DIR) && sudo make install
	@echo "Reboot to finish installation of Jetgpio libraries"

statusled:
	@echo "Building statusled"
	gcc status.c
