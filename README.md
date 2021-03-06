# OptionX: A Simple Option Pricing Software Leveraging Finite Difference Methods.


#### FEM, Group A


#### Rigel Galgana, Jack Karafotas, Daniel Wang

#### rigel_galgana@brown.edu, jack_karafotas@brown.edu, daniel_wang@brown.edu


#### ENGN 2912b Scientific Programming in C++, December 2018


## Introduction
#### Project Overview:

OptionX (the name of our software) aims to create an intuitive options pricing tool utilizing finite difference methods to approximate solutions to the partial differential equations (PDEs) used in most mathematical option pricing models, such as Black Scholes. Finite Difference Methods allows our users to easily value exotic options as well as vanilla options - something that most out of the box option valuation solvers struggle to do. This makes OptionX extremely useful for day traders that do not work for a major corporation that gives them access powerful software because it allows them to get a base valuation for more complex options which, in turn, allows them to place more complex bets on the market.

#### Goals and Objectives:

- Construct classes for European Options, Barrier Options, American Options, Power Options, and Asian Options.

- Construct the Black Scholes pricing model and the Heston pricing model as Partial Differential Equations.

- Construct the Explicit Euler and Implicit Euler Finite Difference Method schemes.

- In the FDM solvers, mesh calculation must be parallelized for speed.

- Design a simple, intuitive user interface in Qt Creator.

- Check for invalid input and throw errors in Qt instead of checking for and throwing exceptions in the solvers themselves.

- Output an informative graph of the option value versus future stock price and approximate option value given the user's input parameters.

- Build a data scraper to obtain information about particular stocks online.

## Software Architectural Design

#### Required External Libraries:

- Armadillo (lapack, blas)

#### Functional Block / Data Flow Diagram:

![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/Functional_Block_Diagram.png?token=AbGG1mR9ciHn8VVg9d6qK8aR5j2y0yj7ks5cIuTNwA%3D%3D)

#### UML Diagrams:

![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/uml.png?token=AbGG1pTqlF-YPP3wDl24JzYRi-29y1PVks5cIwQ9wA%3D%3D)

## Interface Descriptions

#### Graphical Interface:

OptionX, as promised, has a very simple graphical user interface. Upon running the program, a small window appears. On this screen are lines for the user to input the option type, days until expiration, stock initial price, volatility, strike price, interest rate, power, upper barrier, rebate, and current to average price ratio. The latter 5 values are initialized. At the bottom of the screen are the solve and help buttons. Clicking the solve button checks for valid input and then returns both the current value of the option as well as the option value given different future stock prices. Clicking the help button opens a new window specifying the input value definitions, units of measurement, and valid range.

![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/optionXgui.png?token=AbGG1iiJ68HLLA9RDem_Us7ZWsLRLz3jks5cIvjSwA%3D%3D) ![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/help.png?token=AbGG1tVMo0ERrR24R7WbwCjM70FqhMKsks5cIvlhwA%3D%3D)

#### Data Visualization:

Assuming valid input, upon hitting the solve button, two small windows appear: the first is a message bar indicating the current value of the option and the second is a 2D line plot of the option value at the current time versus stock price - this gives the user a broader view of how the value of the option might change if the stock price changes.

(Example Output)
![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/graph.png?token=AbGG1rNA0GQ83oglIYgpe_GlH4KTBydEks5cIvjmwA%3D%3D)
![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/optionValue.png?token=AbGG1gE1DV3S3buXtOEV1hoAGFlMwLn4ks5cIvkpwA%3D%3D)

#### Communications Protocols:

Fortunately passing data through the program is fairly simple. The user inputs in values for each of the parameters, which Qt interprets as QStrings - we convert these to doubles or strings as appropriate. We then pass these values into our interface solver. In this solver we build a Payoff object, that then gets fed into an Option object, which is then fed into a PDE object, which is fed into a FDM solver. Inside this FDM solver we parallelize across an STL vector of doubles stored in shared memory. We then pass an STL vector of STL vectors of doubles (the value of the option across time and stock price) stored in shared memory back to our interface so that we can return a value (double) back to our user and a plot.

#### Threading and Concurrency:

Calculating the value of the option for a particular time across stock prices (calculating the inner mesh for that time) in the Euler-Explicit solver (the primary solver we use) was parallelized using Open MP. Parallelizing across the time dimension is not possible since all FDM solvers solutions at a particular time are dependent on their solutions at past times - making this a time dependent problem and thus not parallelizable in that direction. Therefore, we only parallelized across the stock price direction.

#### Exception Handling:

Exception handling was done by checking that the user had input in a number within the specified valid range for each line. If the user does inputs in a non-numerical character or number outside of the valid range in any of the lines, OptionX will create a new window displaying an error message indicating that the specific invalid inputs must be fixed.

Example invalid input:

![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/error.png?token=AbGG1hHYVAgwYKLTg6brKN4U1SsWVUPdks5cIvfuwA%3D%3D)

Example valid input:

![alt text](https://raw.githubusercontent.com/ENGN2912B-2018/FEM-A/master/validInput.png?token=AbGG1rYXSF2oWiVTpJmI2Pe0FygclvgEks5cIvn8wA%3D%3D)

## Testing and Evaluation

#### Operating System and Software Compiler/Library Versions Tested:

The original operating system used to create the Options, PDEs, and Solvers classes and design the GUI was a 64 bit Windows 10 operating system. The software compiler was MinGW, which was distributed together with Qt Creator and Installer for Windows. The application can also run on mac OS using the g++ compiler assuming the appropriate version of Qt Creator for mac OS was installed.

#### Description of Functional Testing to Date:

The functional testing for the software consisted mostly of verifying the correctness of the behavior of the value versus stock price curve in the output plot after hitting the solve button. A few small numerical precision errors were caught such as those involving unreasonably small or large values for certain input, such as power. Aside from this, inputting certain valid values of days until expiration may crash the code due to step-size rounding errors. Error handling was also thoroughly tested.

#### Instructions for Compiling and Running the Software:

- The project is built and compiled in QtCreator.

- Armadillo version 9.200.6 (lapack, blas) required, OpenMP required, QtCreator 3.0+ required.

- Note: Change lines 17 and 20 in OptionX.pro to the location of the downloaded armadillo library files for lapack and blas.

- Open OptionX through Qt Creator.

- Press Ctrl-R to run the application.

## Conclusions

#### Major Accomplishments:

Classes for a wide variety of option types, their corresponding PDEs, and FDM solvers were successfully constructed and tested. Similarly, the simplicity of the GUI allow the user to focus on crucial parameters and inputting reasonable values for these parameters. Because of its small size, it will not get in the way of traders looking at recent stocks performance and information. It also is able to calculate the value of the option over time and space - this allows us to give traders much more information of how their option value changes over time and price allowing them to make wiser investment decisions. This is the primary purpose of the plot. Lastly, the solvers are extremely fast, fulfilling our initial promise of speed.

#### Results of the Software Development Effort:

OptionX is a fully offline basic options pricing tool with graphical user interface and data visualization done through Qt Creator. Finite difference methods were utilized and accelerated to approximate the solutions to the PDEs specified by the Black Scholes pricing model and option payoffs.

#### Results versus Objectives:

Almost all of the objectives were met. We were not able to create the Heston model PDE and the data scraper. However, the data scraper and the Heston model were ultimately deemed unnecessary because users can input the data they want with very little additional effort and we already have the Black Scholes model which is very powerful. In addition, there are a couple bugs that we did not expect (entering certain time to exprition days causes the program to crash due to round-off errors) but these aren't significant enough to impede on the user experience.

## Future Work:

- As just mentioned, creating more robust algorithms to prevent numerical precision issues.
- Create a fully functional data scraper to obtain information from the web and initialize the variables to these scraped values so the user does not have to input them.
- Create a 3D surface to allow the user to visualize option value with respect to potential stock price as well as elapsed time.

## Author Contributions:

Rigel: Created and designed the GUI along with the data visualization for the option value versus stock price plot. Implemented error checking through Qt. Parallelized Euler-Explicit using Open MP.

Jack: Created all the option payoff classes, the generic option class, all the pde classes, the black scholes class, all the FDM solver classes, and the interface connecting the user input to the solver software.

Daniel: Created a data scraper (we did not have time to integrate it).

