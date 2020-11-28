# Klonoa Dimensions - Cheesai Crystal

___

## Warning
This is a **FAN GAME**, which means that the contributors of this repository are not earning money
___

## Controls

| **_Key_**       | **_Action_**         |
|:---------------:|:--------------------:|
| **Arrow Right** | Move Right           |
| **Arrow Left**  | Move Left            |
| **Z**           | Jump                 |
| **X**           | Attack               |
| **C**           | Switches Character   |
| **S**           | Swicthes Klonoa Mode |

## Download
You can clone this repository by using:
> `git clone https://github.com/Paul0TokiCrew/Klonoa-Dimensions`

You can also go to **Code** label in this repository, download a .zip file and unzip it

## Compiling
To compile the source code, you must have [Allegro 5 library](https://github.com/liballeg/allegro5) and [GCC Compiler](https://gcc.gnu.org/) installed. If you are using Visual Studio, see this [video](https://youtu.be/ETcUmU2tpvg) to install and configure Allegro 5

Now, acess the **src** folder with cmd and type this:
> `g++ hello.cpp -o ../hello.exe $(pkg-config allegro-5 allegro_image-5 allegro_primitives-5 --libs --cflags)`

If you are using Linux, go to the terminal and type this:
> `g++ hello.cpp -o ../bin/hello $(pkg-config allegro-5 allegro_image-5 allegro_primitives-5 --libs --cflags)`

## Running
Compile it and go to **Klonoa-Dimensions** folder and execute the .exe file. If you are on Linux, type this inside the **src** folder
> `./../bin/hello`
