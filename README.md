# Roots finder



## A CLI program that finds integer roots and approximate decimal ones
This project consists of a multithreaded search algorithm that seeks roots of a given polynomial. In that regard, not only integer roots are found, but decimal ones are approximated as well. 



## Project motivation
The idea of this project originated from one of my calculus 1 classes where I learned the Weierstrass theorem. When hearing about such theorem, I immediately thought of implementing an algorithm to approximate roots and ended up including integer ones as well. Moreover, I took this project as a way to improve my C programming skills and learn about multithreading and parallelism.



## Screenshots
![screenshot1](https://github.com/FelipeColona/RootsFinder/blob/main/screenshot1.svg?raw=true)

![screenshot2](https://github.com/FelipeColona/RootsFinder/blob/main/screenshot2.svg?raw=true)



## Main Features
- Intuitive
- Works for decimal roots
- Has a customizable precision number for approximation 
- Is performant (runs in parallel)



## Try it out!
- Clone the project
    - `git clone https://github.com/FelipeColona/RootsFinder`

- Change to the project's directory
    - `cd RootsFinder`

- Run it
    - `make`



## Known issues
- If the polynomial has multiplicity of roots, the program will run forever


- If the polynomial has imaginary roots, the program will run forever as well


## Future Updates
- Implement Newthon's Method of approximating roots
