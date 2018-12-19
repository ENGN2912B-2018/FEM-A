# OptionX: A Simple Option Pricing Software Leveraging Finite Element Methods.


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

## Interface Descriptions

#### Graphical Interface:

OptionX, as promised, has a very simple graphical user interface. Upon running the program, a small window appears. On this screen are lines for the user to input the option type, days until expiration, stock initial price, volatility, strike price, interest rate, power, upper barrier, rebate, and current to average price ratio. The latter 5 values are initialized. At the bottom of the screen are the solve and help buttons. Clicking the solve button checks for valid input and then returns both the current value of the option as well as the option value given different future stock prices. Clicking the help button opens a new window specifying the input value definitions, units of measurement, and valid range.

#### Data Visualization:

Assuming valid input, upon hitting the solve button, two small windows appear: the first is a message bar indicating the current value of the option and the second is a 2D line plot of the option value at the current time versus stock price - this gives the user a broader view of how the value of the option might change if the stock price changes.

#### Communications Protocols:

Fortunately passing data through the program is fairly simple. The user inputs a bunch of doubles and an option type - we convert these to doubles and a string respectively. We then pass that into our interface solver. In this solver we build a Payoff object, that then gets fed into an Option object, which is then fed into a PDE object, which is fed into a FDM solver. Inside this FDM solver we parallelize across an STL vector of doubles stored in shared memory. We then pass an STL vector of STL vectors of doubles (the value of the option across time and stock price) stored in shared memory back to our interface so that we can return a value (double) back to our user and a plot.

#### Threading and Concurrency:

Calculating the value of the option for a particular time across stock prices (calculating the inner mesh for that time) in the Euler-Explicit solver (the primary solver we use) was parallelized using Open MP. Parallelizing across the time dimension is not possible since all FDM solvers solutions at a particular time are dependent on their solutions at past times - making this a time dependent problem and thus not parallelizable in that direction. Therefore, we only parallelized across the stock price direction.

#### Exception Handling:

Exception handling was done by checking that the user had input in a number within the specified valid range for each line. If the user does inputs in a non-numerical character or number outside of the valid range in any of the lines, OptionX will create a new window displaying an error message indicating that the specific invalid inputs must be fixed.

## Testing and Evaluation

#### Operating System and Software Compiler/Library Versions Tested:

The original operating system used to create the Options, PDEs, and Solvers classes and design the GUI was a 64 bit Windows 10 operating system. The software compiler was MinGW, which was distributed together with Qt Creator and Installer for Windows. The application can also run on mac OS using the g++ compiler assuming the appropriate version of Qt Creator for mac OS was installed.

#### Description of Functional Testing to Date:

The functional testing for the software consisted mostly of verifying the correctness of the behavior of the value versus stock price curve in the output plot after hitting the solve button. A few small numerical precision errors were caught such as those involving unreasonably small or large values for certain input, such as power. Aside from this, inputting certain valid values of days until expiration may crash the code due to step-size rounding errors. Error handling was also thoroughly tested.

#### Instructions for Compiling and Running the Software:

-The project is built and compiled in QtCreator.
-Armadillo (lapack, blas) required, OpenMP required, QtCreator 3.0+ required.
-Note: Change lines 17 and 20 in OptionX.pro to the location of the downloaded armadillo library files for lapack and blas.
- Open OptionX through Qt Creator.
- Press Ctrl-R to run the application.

## Conclusions

#### Major Accomplishments:

Classes for a wide variety of option types, their corresponding PDEs, and FDM solvers were successfully constructed and tested. Similarly, the simplicity of the GUI allow the user to focus on crucial parameters and inputting reasonable values for these parameters. Because of its small size, it will not get in the way of traders looking at recent stocks performance and information. It also is able to calculate the value of the option over time and space - this allows us to give traders much more information of how their option value changes over time and price allowing them to make wiser investment decisions. This is the primary purpose of the plot. Lastly, the solvers are extremely fast, fulfilling our initial promise of speed.

#### Results of the Software Development Effort:

OptionX is a fully offline basic options pricing tool with graphical user interface and data visualization done through Qt Creator. Finite difference methods were utilized and accelerated to approximate the solutions to the PDEs specified by the Black Scholes pricing model and option payoffs.

#### Results versus Objectives:

Almost all of the objectives were met. We were not able to create the Heston model PDE and the data scraper. However, the data scraper and the Heston model were ultimately deemed unnecessary because users can input the data they want and we already have the Black Scholes model which is very powerful. In addition, there are a couple bugs that we did not expect (entering certain time to exprition days causes the program to crash due to round-off errors) but these aren't significant enough to impede on the user experience.

## Future Work:

- As just mentioned, creating more robust algorithms to prevent numerical precision issues.
- Create a fully functional data scraper to obtain information from the web and initialize the variables to these scraped values so the user does not have to input them.
- Create a 3D surface to allow the user to visualize option value with respect to potential stock price as well as elapsed time.

## Author Contributions:

Rigel: Created and designed the GUI along with the data visualization for the option value versus stock price plot. Implemented error checking through Qt. Parallelized Euler-Explicit using Open MP.

Jack: Created all the option payoff classes, the generic option class, all the pde classes, the black scholes class, all the FDM solver classes, and the interface connecting the user input to the solver software.

Daniel: Created a data scraper but got a concussion before being able to integrate it to the rest of the software.




