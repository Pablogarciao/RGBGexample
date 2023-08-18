![](./resources/official_armmbed_example_badge.png)

# Blinky Mbed OS example

INTEGRANTES: NICOLÁS GUTIÉRREZ Y PABLO GARCÍA

Acá se le dará explicaión al código y sus métodos:

Por medio del UnbufferedSerial se define el puerto en el cual se va a ejecutar la tarjeta
```bash
    $ UnbufferedSerial pc(USBTX, USBRX,2400)
```
El método 'parse_hex' está diseñado para tomar un valor hexadecimal de 32 bits y extraer los componentes rojo verde y azul y almacenarlos en las variables 'r', 'g' y 'b' respectivamente.

Para el color rojo lo que se hace es que el operador >> desplaza el valor hexadecimal 16 bits hacia la derecha, lo que equivale a descartar los 16 bits más bajos los cuales corresponden a los componente azul y verde, con lo deja solo los 8 bits superiores que son se dejan para el componente rojo. Después el operador '&' se utiliza con 0xFF para asegurarse de que solo se toman los 8 bits más bajos del resultado. Esto se almacena en la variable 'r'.
Para el color verde se hace algo muy similar, solo que el operador >> desplaza 8 bits a la derecha en vez de 16, ya que en este caso solo hay que descartar los 8 bits más bajos que corresponden al color azul. Dejando así los siguientes para el componente verde.  y finalmente se almacen en la variable 'g'.
Y para el color azul que se almacena en la variable 'b', se utiliza el operador & se utiliza directamente para tomar los 8 bits más bajos del valor hexadecimal, que corresponden al componente azul. 

```bash
    $ void parse_hex(uint32_t hex, float r, float g, float b) {
    r = (hex >> 16) & 0xFF;
    g = (hex >> 8) & 0xFF;
    b = hex & 0xFF;
    }
 ```
Luego el método 'calculate_pwm_duty_cycle' ajusta cada valor rgb que se obtuvo del método anterior almacenado en las variables 'r','g' y 'b' para poder pasarselo al LED como parámetro, ya que el LED solo recibe valores entre 0 y 1. 
Este método calcula los ciclos de trabajo (duty cycles) para una modulación por ancho de pulso (PWM) inversa de los tres componentes de color.
 ```bash
    $ void calculate_pwm_duty_cycle(uint8_t r, uint8_t g, uint8_t b, uint16_t& pr, uint16_t& pg, uint16_t& pb) {
    pr = r * 1 / 255;
    pr = 1-(float)pr;
    pg = g * 1 / 255;
    pg = 1-(float)pg;
    pb = b * 1 / 255;
    pb = 1-(float)pb;
    }
```
El método recibe seis argumentos: r, g y b, que son los valores calculados en el método anterior. Luego, recibe tres argumentos por referencia (pr, pg y pb), que son utilizados para almacenar los ciclos de trabajo PWM inversos correspondientes.
Para calcular este duty _cycle, en la variable pr toma el valor de r y lo multiplica por 1 / 255. Esto normaliza el valor de 0 a 1(como ya se explico el LED solo toma valores entre 0 y 1).
Luego, resta este valor de 1, obteniendo el ciclo de trabajo inverso, almacenando el ciclo de trabajo inverso resultante en la variable pr.
Luego repite el mismo proceso para los colores verde y azul respectivamente, cálculando sus ciclos de trabajos inversos y almacenándolos en las variables 'pg' y 'pb'.

Y por último lo que se hace dentro del main es que ontrola LEDs RGB utilizando la entrada de un valor en formato HEX para definir un color. Luego, calcula los ciclos de trabajo PWM inversos correspondientes a los componentes R, G y B del color y ajusta los niveles de brillo de los LEDs.
```bash
    $ int main() {
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);
    // Parse the HEX code to extract the RGB values
    string hex; // Example HEX code for red
    cout << 'ingresar HEX';
    cin >> hex;

    uint32_t rgbValue = std::stoul(hex,nullptr,16);

    float r, g, b;
    parse_hex(rgbValue, r, g, b);

    // Calculate the PWM duty cycle values for each color
    uint16_t pr, pg, pb;
    calculate_pwm_duty_cycle(r, g, b, pr, pg, pb);

    ledR.write(pr);
    ledG.write(pg);
    ledB.write(pb);
    }
```
Primero lo que hace es que configura los pines PWM, creando tres objetos PwmOut llamados ledR, ledG y ledB, asociados a los pines LED1, LED2 y LED3 respectivamente. 
Luego extrae los valores RGB desde un Código HEX que es ingresado por consola. Para esto se declara una variable hex para almacenar el código hexadecimal, luego el programa solicita al usuario que ingrese un valor hexadecimal, que es el código de color en formato HEX. El código hexadecimal ingresado se convierte en un valor entero de 32 bits usando std::stoul. Esto proporciona un valor decimal que representa un color en formato RGB.
Después se calculan las componentes R, G y B, declarando variables r, g y b como tipo float. Para luego llamar al método parse_hex para descomponer el valor RGB en los componentes R, G y B. El método parse_hex modifica las variables r, g y b de acuerdo a los componentes extraídos del valor RGB y los almacena allí.
Por último se hace el cálculo de ciclos de trabajo PWM y el control de LEDs. Para ejecutar esto se declaran las variables pr, pg y pb como tipo uint16_t para almacenar los ciclos de trabajo PWM inversos. Se llama al método calculate_pwm_duty_cycle para calcular los ciclos de trabajo PWM inversos para los componentes R, G y B como ya se explicó y finalmente los resultados se almacenan en las variables pr, pg y pb.
Y al final del código los ciclos de trabajo inversos calculados (pr, pg y pb) se utilizan para establecer los niveles de brillo de los LEDs rojo, verde y azul respectivamente, utilizando el método write de los objetos ledR, ledG y ledB.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


The example project is part of the [Arm Mbed OS Official Examples](https://os.mbed.com/code/) and is the [getting started example for Mbed OS](https://os.mbed.com/docs/mbed-os/latest/quick-start/index.html). It contains an application that repeatedly blinks an LED on supported [Mbed boards](https://os.mbed.com/platforms/).

You can build the project with all supported [Mbed OS build tools](https://os.mbed.com/docs/mbed-os/latest/tools/index.html). However, this example project specifically refers to the command-line interface tool [Arm Mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).
(Note: To see a rendered example you can import into the Arm Online Compiler, please see our [import quick start](https://os.mbed.com/docs/mbed-os/latest/quick-start/online-with-the-online-compiler.html#importing-the-code).)

## Mbed OS build tools

### Mbed CLI 2
Starting with version 6.5, Mbed OS uses Mbed CLI 2. It uses Ninja as a build system, and CMake to generate the build environment and manage the build process in a compiler-independent manner. If you are working with Mbed OS version prior to 6.5 then check the section [Mbed CLI 1](#mbed-cli-1).
1. [Install Mbed CLI 2](https://os.mbed.com/docs/mbed-os/latest/build-tools/install-or-upgrade.html).
1. From the command-line, import the example: `mbed-tools import mbed-os-example-blinky`
1. Change the current directory to where the project was imported.

### Mbed CLI 1
1. [Install Mbed CLI 1](https://os.mbed.com/docs/mbed-os/latest/quick-start/offline-with-mbed-cli.html).
1. From the command-line, import the example: `mbed import mbed-os-example-blinky`
1. Change the current directory to where the project was imported.

## Application functionality

The `main()` function is the single thread in the application. It toggles the state of a digital output connected to an LED on the board.

**Note**: This example requires a target with RTOS support, i.e. one with `rtos` declared in `supported_application_profiles` in `targets/targets.json` in [mbed-os](https://github.com/ARMmbed/mbed-os). For non-RTOS targets (usually with small memory sizes), please use [mbed-os-example-blinky-baremetal](https://github.com/ARMmbed/mbed-os-example-blinky-baremetal) instead.

## Building and running

1. Connect a USB cable between the USB port on the board and the host computer.
1. Run the following command to build the example project and program the microcontroller flash memory:

    * Mbed CLI 2

    ```bash
    $ mbed-tools compile -m <TARGET> -t <TOOLCHAIN> --flash
    ```

    * Mbed CLI 1

    ```bash
    $ mbed compile -m <TARGET> -t <TOOLCHAIN> --flash
    ```

Your PC may take a few minutes to compile your code.

The binary is located at:
* **Mbed CLI 2** - `./cmake_build/mbed-os-example-blinky.bin`</br>
* **Mbed CLI 1** - `./BUILD/<TARGET>/<TOOLCHAIN>/mbed-os-example-blinky.bin`

Alternatively, you can manually copy the binary to the board, which you mount on the host computer over USB.

## Expected output
The LED on your target turns on and off every 500 milliseconds.


## Troubleshooting
If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.

## Related Links

* [Mbed OS Stats API](https://os.mbed.com/docs/latest/apis/mbed-statistics.html).
* [Mbed OS Configuration](https://os.mbed.com/docs/latest/reference/configuration.html).
* [Mbed OS Serial Communication](https://os.mbed.com/docs/latest/tutorials/serial-communication.html).
* [Mbed OS bare metal](https://os.mbed.com/docs/mbed-os/latest/reference/mbed-os-bare-metal.html).
* [Mbed boards](https://os.mbed.com/platforms/).

### License and contributions

The software is provided under Apache-2.0 license. Contributions to this project are accepted under the same license. Please see [CONTRIBUTING.md](./CONTRIBUTING.md) for more info.

This project contains code from other projects. The original license text is included in those source files. They must comply with our license guide.
