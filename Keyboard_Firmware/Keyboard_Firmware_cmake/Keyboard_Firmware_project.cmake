#eyJidWlsZFByZXNldHMiOnsiZGVmYXVsdF9jb25maWciOnsibmFtZSI6ImRlZmF1bHRfY29uZmlnIiwiZGVmaW5pdGlvbnMiOltdLCJyZW1vdmVkRmxhZ3MiOnsiQyI6W10sIkNYWCI6W10sIkFTTSI6W119LCJhZGRpdGlvbmFsRmxhZ3MiOnsiQyI6W10sIkNYWCI6W10sIkFTTSI6W119fX0sImRpcmVjdG9yaWVzIjpbInNyYyJdfQ==
target_sources(Keyboard_Firmware PRIVATE
	"../src/EPD_Test.c"
	"../src/ImageData.c"
	"../src/ble.c"
	"../src/ble_utility.c"
	"../src/gpio.c"
	"../src/i2c.c"
	"../src/irq.c"
	"../src/llfifo.c"
	"../src/log.c"
	"../src/oscillator.c"
	"../src/rtcc.c"
	"../src/scheduler.c"
	"../src/spi.c"
	"../src/timer.c"
	"../src/ws2812.c"
	"../src/Fonts/font12.c"
	"../src/Fonts/font12CN.c"
	"../src/Fonts/font16.c"
	"../src/Fonts/font20.c"
	"../src/Fonts/font24.c"
	"../src/Fonts/font24CN.c"
	"../src/Fonts/font8.c"
	"../src/GUI/GUI_Paint.c"
	"../src/e-ink/EPD_1in54_V2.c"
	"../src/keyboard/layout.c"
)

include_directories(
	../src
)
