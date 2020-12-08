![](img/Title.png)
# Klonoa Dimensions - Cheesai Crystal
___

## Warning
This is not a official game, it's a **FAN GAME**, and the contributors of this repository are not profiting
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

## Compiling and Running
To compile the source code, you must have [Allegro 5 library](https://github.com/liballeg/allegro5) and [GCC Compiler](https://gcc.gnu.org/) installed. If you don't have Allegro 5, go to this [link](https://github.com/liballeg/allegro_wiki/wiki/Quickstart) and install it in your OS

Open your command line, acess the _src_ folder, and type one of theese commands:

### Windows
> `g++ hello.cpp -o ../hello -lallegro -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio`

### Linux
> `g++ hello.cpp -o ../hello $(pkg-config allegro-5 allegro_image-5 allegro_primitives-5 allegro_acodec-5 allegro_audio-5 --libs --cflags)`

### MacOS
> `g++ hello.cpp -o ../hello $(pkg-config allegro-5 allegro_main-5 allegro_image-5 allegro_primitives-5 allegro_acodec-5 allegro_audio-5 --libs --cflags)`

After compiling, type:
> `./../hello`
