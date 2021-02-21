```    
bluepill-cmsis:

StdPeriph_Lib=${HOME}/stm32lib/
mkdir  -p "${StdPeriph_Lib}"

sfm32f1 Libraries
unzip  zip-stm32f1_stdperiph_lib/stm32f1_stdperiph_lib.zip -d "${StdPeriph_Lib}"

rm stm32f1_stdperiph_lib.zip

depends: make cmake gcc g++ gcc-arm-none-eabi gdb-arm-none-eabi libusb-dev
apt install make cmake gcc g++ gcc-arm-none-eabi gdb-arm-none-eabi libusb-dev

port code from http://www.avislab.com/
```    

