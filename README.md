# OptionX: A Simple Option Pricing Software Leveraging Finite Element Methods.


Final Project for group FEM-A


Rigel Galgana, Jack Karafotas, Daniel Wang
rigel_galgana@brown.edu, jack_karafotas@brown.edu, daniel_wang@brown.edu


ENGN 2912b Scientific Programming in C++, December 2018


Project Overview:
OptionX (the name of our software) aims to create an intuitive options pricing tool utilizing finite elements to approximate solutions to the partial differential equations (PDEs) used in most mathematical option pricing models, such as Black Scholes. 


Goals and Objectives:
- Construct classes for each option type, the Black Scholes pricing model, and each FEM based solver to allow for basic functionality.
- In the FEM solvers, mesh initialization must be parallelized for speed.
- Design a simple, intuitive user interface in Qt Creator.
- Check for invalid input and throw errors in Qt instead of checking for and throwing exceptions in the solvers themselves.
- Output an informative graph of the option value versus future stock price and approximate option value given the user's input parameters.
- Build a data scraper to obtain information about particular stocks online.


Required External Libraries:
- Armadillo (lapack, blas)

Functional Block Diagrams:

Data Flow Diagrams:

UML Diagrams:

Graphical Interface:
OptionX, as promised, has a very simple graphical user interface. Upon running the program, a small window appears. On this screen are lines for the user to input the option type, days until expiration, stock initial price, volatility, strike price, interest rate, power, upper barrier, rebate, and current to average price ratio. The latter 5 values are initialized. At the bottom of the screen are the solve and help buttons. Clicking the solve button checks for valid input and then returns both the current value of the option as well as the option value given different future stock prices. Clicking the help button opens a new window specifying the input value definitions, units of measurement, and valid range.

Data Visualization:
Assuming valid input, upon hitting the solve button, two small windows appear: the first is a message bar indicating the current value of the option and the second is a 2D line plot of the current option value versus future stock price.

Communications Protocols:

Threading and Concurrency:
The mesh initialization in the Euler-Explicit solver was parallelized using Open MP. Parallelizing anything outside of the mesh initialization, such as the PDE solvers, is difficult as these calculations are inherently time dependent and hence, cannot be parallelized.

Exception Handling:
Exception handling was done by checking that the user had input in a number within the specified valid range for each line. If the user does inputs in a non-numerical character or number outside of the valid range in any of the lines, OptionX will create a new window displaying an error message indicating that the specific invalid inputs must be fixed.

Operating System and Software Compiler/Library Versions Tested:
The original operating system used to create the Options, PDEs, and Solvers classes and design the GUI was a 64 bit Windows 10 operating system. The software compiler was MinGW, which was distributed together with Qt Creator and Installer for Windows. The application can also run on mac OS using the g++ compiler assuming the appropriate version of Qt Creator for mac OS was installed.

Description of Functional Testing to Date:
The functional testing for the software consisted mostly of verifying the correctness of the behavior of the value versus stock price curve in the output plot after hitting the solve button. A few small numerical precision errors were caught such as those involving unreasonably small or large values for certain input, such as power. Aside from this, inputting certain valid values of days until expiration may crash the code due to step-size rounding errors.

Instructions for Compiling and Running the Software:
-The project is built and compiled in QtCreator.
-Armadillo (lapack, blas) required, OpenMP required, QtCreator 3.0+ required.
-Note: Change lines 17 and 20 in OptionX.pro to the location of the downloaded armadillo library files for lapack and blas.
- Open OptionX through Qt Creator.
- Press Ctrl-R to run the application.

Major Accomplishments:
Classes for a wide variety of option types and their corresponding solvers were successfully constructed and tested. Similarly, the simplicity and blandness of the GUI allow the user to focus on crucial parameters and inputting reasonable values for these parameters. Because of its small size, it will not get in the way of traders looking at recent stocks performance and information. Lastly, the solvers are extremely fast, fulfilling our initial promise of speed.

Results of the Software Development Effort:
OptionX is a fully offline basic options pricing tool with graphical user interface and data visualization done through Qt Creator. Finite element methods were utilized and accelerated to approximate the solutions to the PDEs specified by the Black Scholes pricing model.

Results versus Objectives:
With the exception of data scraping, all of the objectives were met.






Usage documentation
There are three main things that the user must provide: stock ticker, option type, and pricing model selected. Below are the specifics of each input:

The user will input in a stock ticker. If invalid, throw an error and prompt again. If valid, user will be given the option to input in specific values of certain metrics such as volatility, initial price, interest rate, or other parameters. If user does not provide necessary values, then OptionX will take the most recent or relevant available information on the internet and fills these values in. If no information is available, an approximation is made based off similar stocks or past behavior.

The user will then input an option type (European, American, or Asian). These will determine how prices are determined and predicted performance.

Lastly, the user must input in a pricing model. This at the moment only includes Black-Scholes and Heston pricing models.
