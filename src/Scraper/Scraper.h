#pragma once
#include <vector>
#include <iostream>

#ifndef Scraper_h
#define Scraper_h

#include <stdio.h>
#include "dataFrame.hpp" 

class Scraper{
public: Scraper(char *symbol, long startdate, long enddate, char outfilename[FILENAME_MAX], char cookiefilename[FILENAME_MAX], char crumbfilename[FILENAME_MAX]);
		dataFrame priceVector;
};

#endif /* Scraper_h */