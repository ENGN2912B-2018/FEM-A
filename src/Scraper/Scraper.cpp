#include <string>
#include <iostream>
#include <sstream>
#include "Scraper.h"
#include <fstream>
#include <curl/curl.h>
#include <chrono>
#include <cmath>

using namespace std;

//below function searches Yahoo finance for cookies/crumbs needed for indirect access 
//need to find crumb embedded in yahoo website and spoof cookie
const char* bypassYahoo(char *ticker, char cookieFile[FILENAME_MAX], char crumbFileName[FILENAME_MAX]) {
	//initiate CURL session
	//CURL gets raw HTML
	CURL *cookiecurl = curl_easy_init();
	FILE * crumbfile;
	char netscapeCookie[256];
	const char *crumb = "";
	cookiecurl = curl_easy_init();
	string url = string("https://finance.yahoo.com/quote/") + string(ticker) + string("/history");

	if (cookiecurl) { //checks if session online
		curl_easy_setopt(cookiecurl, CURLOPT_URL, cookie_url.c_str());
		curl_easy_setopt(cookiecurl, CURLOPT_COOKIEFILE, cookiefilename);
		curl_easy_setopt(cookiecurl, CURLOPT_COOKIELIST, "ALL");

		//cookie needs to be in netscape format
		snprintf(netscapeCookie, sizeof(netscapeCookie), "%s\t%s\t%s\t%s\t%lu\t%s\t%s",
			".example.com", "TRUE", "/", "FALSE",
			(unsigned long)time(nullptr) + 31337UL,
			"PREF", "hello example, i like you very much!"); 
		//code from cookie_interface.c in curl documentation

		curl_easy_setopt(cookiecurl, CURLOPT_COOKIESESSION, true); //forces curl to ignore cookies from previous sessions (starts new session) - curl by default stores/loads all cookies
		curl_easy_setopt(cookiecurl, CURLOPT_COOKIEJAR, cookieFile); //filename to store cookies to
		curl_easy_setopt(cookiecurl, CURLOPT_COOKIELIST, netscapeCookie); //
		curl_easy_setopt(cookiecurl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(cookiecurl, CURLOPT_HEADER, 0);
	}

	crumbfile = fopen(crumbFileName, "wb");
	if (crumbfile) {
		// Write the page body to this file handle
		curl_easy_setopt(cookiecurl, CURLOPT_WRITEDATA, crumbfile);
		curl_easy_perform(cookiecurl); //block file transfer
		fclose(crumbfile); //close header file
	}

	// Sends all retrieved cookies to file
	curl_easy_cleanup(cookiecurl);
	curl_global_cleanup();

	// Search for crumb in newly created crumb file
	ifstream searchFile(crumbFileName);
	string str;
	while (getline(searchFile, str)) {
		if (str.find("CrumbStore\":{\"crumb\":\"") != str.npos) {
			size_t pos = str.find("CrumbStore\":{\"crumb\":\"") + 22;
			crumb = str.substr(pos, 11).c_str();
			break;
		}
	}

	return crumb;
}

// Constructor for CSV Reader
Scraper::Scraper(char *ticker, long startdate, long enddate, char outfilename[FILENAME_MAX], char cookiefilename[FILENAME_MAX], char crumbFileName[FILENAME_MAX]) : marketmovements() {

	// Dates formatted as YYYY-MM-DD
	auto interval = (char*)"1d";

	// Initialize variables
	CURL *curl;
	CURLcode res;
	FILE *fp;

	// Get crumb and use it to create the download url
	string down_url = string("https://query1.finance.yahoo.com/v7/finance/download/") + string(ticker) + string("?period1=") + to_string(startdate) + string("&period2=") + to_string(enddate) + string("&interval=") + string(interval) + string("&events=history&crumb=") + bypassYahoo(ticker, cookiefilename, crumbFileName);

	// Init the curl session
	curl = curl_easy_init();

	// Set cookies
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookiefilename);

	// Set URL to go to given URL
	curl_easy_setopt(curl, CURLOPT_URL, down_url.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);

	// Send all data to this function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

	// Open the file
	fp = fopen(outfilename, "wb");
	if (fp) {

		// Write the page body to this file handle
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		// Performs blocking file transfer as defined
		res = curl_easy_perform(curl);
		fclose(fp); //close header
	}

	// Get the data from the .csv file, pass into dataFrame object
	priceVector = dataFrame(outfilename, string(ticker));

	curl_easy_cleanup(curl); //prevent memory leaks
	curl_global_cleanup();
}