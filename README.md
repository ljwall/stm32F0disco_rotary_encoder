# STM32F0DISCOVERY Rotary encoder example

The rotary encoder handling is a port of [this arduino code](https://github.com/buxtronix/arduino/tree/master/libraries/Rotary) to use libopencm3.

The `Makefile` is derived from the examples for stm32F0 disco board from [libopencm3-examples](https://github.com/libopencm3/libopencm3-examples).

```bash
make -C libopencm3 # onece, to build the libopencm3 library
make -C src flash
```


# License

[GPL Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html)


```
