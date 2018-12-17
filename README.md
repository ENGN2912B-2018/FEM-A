# FEM A - OptionX (v1.0)
Final Project for group FEM A
- Jack Karafotas, Daniel Wang, Rigel Galgana

### Design philosophy
OptionX (name of software) aims to create an intuitive options pricing tool utilizing finite element methods to approximate solutions to PDEs necessary in most mathematical option pricing models, such as Black Scholes. By leveraging parallelization, designing a simple but informative graphical user interface, and obtaining current information on assets through web-scraping, OptionX will be faster, easier to understand, and more convenient than other available softwares.

### Build instructions
#### Operating System and Library Requirements
- Original operating system used was Windows 10.
- The project is built and compiled in QtCreator.
- Armadillo (lapack, blas) required, OpenMP required, QtCreator 3.0+ required.
- Note: Change lines 17 and 20 in OptionX.pro to the location of the downloaded armadillo library files for lapack and blas.
#### Run Instructions
- Open OptionX through Qt Creator.
- Press Ctrl-R to run the application.

### Usage documentation
There are three main things that the user must provide: stock ticker, option type, and pricing model selected. Below are the specifics of each input:

The user will input in a stock ticker. If invalid, throw an error and prompt again. If valid, user will be given the option to input in specific values of certain metrics such as volatility, initial price, interest rate, or other parameters. If user does not provide necessary values, then OptionX will take the most recent or relevant available information on the internet and fills these values in. If no information is available, an approximation is made based off similar stocks or past behavior.

The user will then input an option type (European, American, or Asian). These will determine how prices are determined and predicted performance.

Lastly, the user must input in a pricing model. This at the moment only includes Black-Scholes and Heston pricing models.



