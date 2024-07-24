#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <utility>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cmath>
#include <unistd.h>
using namespace std;

// Function to format double to string currency with commas and 2 decimal places
string formatCurrency(double amount) {
    string currency = to_string(amount);
    size_t decimalPos = currency.find(".");
    if (decimalPos != string::npos && currency.length() - decimalPos > 3) {
        currency = currency.substr(0, decimalPos + 3);
    }
    for (int i = decimalPos - 3; i > 0; i -= 3) {
        currency.insert(i, ",");
    }
    return currency;
}

class CarDetails {
private:
    string model;
    double price; // in PHP
    double interestRate; // in percentage

public:
    // Constructor
    CarDetails(const string& model, double price, double interestRate) {
        this->model = model;
        this->price = price;
        this->interestRate = interestRate;
    }

    // Getters
    string getModel() const {
        return model;
    }
    double getPrice() const {
        return price;
    }
    double getInterestRate() const {
        return interestRate;
    }
};

class CarLoan {
private:
    string model;
    double price; // in PHP
    double interestRate; // in percentage
    double downPaymentRate; // in percentage
    int loanTerm; // in months
    double downPayment; // in PHP
    double loanAmount; // in PHP
    double monthlyPayment; // in PHP
    double totalPayment; // in PHP
    double totalInterest; // in PHP

public:
    // Constructor that sets all the attributes
    CarLoan(const string& model, double price, double interestRate, double downPaymentRate, int loanTerm) {
        this->model = model;
        this->price = price;
        this->interestRate = interestRate;
        this->downPaymentRate = downPaymentRate;
        this->loanTerm = loanTerm;
        this->downPayment = price * downPaymentRate / 100;
        this->loanAmount = price - downPayment;
        double monthlyInterestRate = interestRate / 100 / 12;
        this->monthlyPayment = loanAmount * monthlyInterestRate / (1 - pow(1 + monthlyInterestRate, loanTerm * -1));
        this->totalPayment = monthlyPayment * loanTerm;
        this->totalInterest = totalPayment - loanAmount;
    }

    // Function to display the full car loan details in HTML card bootstrap
    void displayDetails() const {
        cout << R"(
        <section class="col-md-6 mt-4 mt-md-0 d-flex align-items-center justify-content-center flex-column">
            <h3 class="fs-5 text-light">Loan Details</h3>
            <div class="bg-dark m-0 p-3 rounded rounded-3 d-flex align-items-center justify-content-center gap-3">
                <div class="col-sm-6">
                <p class="card-text">Downpayment Rate: )" << downPaymentRate << R"(%</p>
                <p class="card-text">Loan Term: )" << loanTerm << R"( months</p>
                <p class="card-text">Downpayment: ₱)" << formatCurrency(downPayment) << R"(</p>
                <p class="card-text">Loan Amount: ₱)" << formatCurrency(loanAmount) << R"(</p>
                </div>
                <div class="col-sm-6">
                <p class="card-text">Monthly Payment: ₱)" << formatCurrency(monthlyPayment) << R"(</p>
                <p class="card-text">Total Payment: ₱)" << formatCurrency(totalPayment) << R"(</p>
                <p class="card-text">Total Interest: ₱)" << formatCurrency(totalInterest) << R"(</p>
                </div>
            </div>
        </div>)";
    }
};

// Function to decode URL-encoded strings
string urlDecode(const string& str) {
    string result;
    char hex[3] = {0};
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%') {
            if (i + 2 < str.length()) {
                hex[0] = str[i + 1];
                hex[1] = str[i + 2];
                result += static_cast<char>(strtol(hex, nullptr, 16));
                i += 2;
            }
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

// Function to parse query string into a key-value map
map<string, string> parseQueryString(const string& query) {
    map<string, string> params;
    string key, value;
    istringstream queryStream(query);
    while (getline(queryStream, key, '=')) {
        if (getline(queryStream, value, '&')) {
            params[urlDecode(key)] = urlDecode(value);
        }
    }
    return params;
}

// Function to parse cookies
map<string, string> parse_cookies(const string &cookie_header) {
    map<string, string> cookies;
    size_t pos = 0;
    string token;
    string header = cookie_header;
    while ((pos = header.find("; ")) != string::npos) {
        token = header.substr(0, pos);
        size_t eq_pos = token.find("=");
        if (eq_pos != string::npos) {
            string key = token.substr(0, eq_pos);
            string value = token.substr(eq_pos + 1);
            cookies[key] = value;
        }
        header.erase(0, pos + 2);
    }
    if ((pos = header.find("=")) != string::npos) {
        string key = header.substr(0, pos);
        string value = header.substr(pos + 1);
        cookies[key] = value;
    }
    return cookies;
}

int main() {
    // Read the contents of the style sheet file
    ifstream styleSheetFile("./styles.css");
    string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
    styleSheetFile.close();

    string requestMethod = getenv("REQUEST_METHOD");
    // Read environment variables for cookie and query string
    string cookie_header = getenv("HTTP_COOKIE") ? getenv("HTTP_COOKIE") : "";
    map<string, string> cookies = parse_cookies(cookie_header);
    string name;
    // Check if the user is logged in
    if (cookies.find("name") != cookies.end()) {
        name = cookies["name"];
        if (name == "") {
            cout << "Location: login.cgi\r\n\r\n";
        }
    }
    else {
        cout << "Location: login.cgi\r\n\r\n";
    }

    // Print the HTTP header
    cout << "Content-Type: text/html\r\n\r\n";

    // CarLoan database
    vector<CarLoan> carLoanDatabase;

    // CarDetails database
    vector<CarDetails> carDetailsDatabase;

    // Populate the car details database with the existing car models
    carDetailsDatabase.emplace_back("ZenithEon", 1500000.0, 7.0);
    carDetailsDatabase.emplace_back("QuantumX", 2000000.0, 6.0);
    carDetailsDatabase.emplace_back("Luminova", 1200000.0, 8.5);
    carDetailsDatabase.emplace_back("Nextron", 1000000.0, 9.5);

    string defaultCarLoanForm = R"(
                <section class="container text-light w-100 py-5">
                    <h2 class="display-4 mb-5 text-center">Car Loan Calculator</h2>
                    <section class="row d-flex align-items-center justify-content-center">
                    <form method="post" class="col-md-6 row border border-light mt-0 text-dark bg-dark g-3 p-3 rounded rounded-3">
                        <div class="col-12 form-floating">
                            <select class="form-select" name="carModel" id="carModel" required>
                        <option value="" selected disabled>Select Car Model</option>)";
                        // Populate car model options
                        for (const CarDetails& car : carDetailsDatabase) {
                            defaultCarLoanForm += "<option value=\"" + car.getModel() + "\">" + car.getModel() + "</option>";
                        }
            defaultCarLoanForm += R"(</select>
                    <label for="carModel" class="form-label">Car Model</label>
                </div>
                <div class="col-lg-6 form-floating">
                    <input type="text" class="form-control" name="carPrice" id="carPrice" value="0" readonly required>
                    <label for="carPrice" class="form-label">Car Price (Php)</label>
                </div>
                <div class="col-lg-6 form-floating">
                    <input type="text" class="form-control" name="interestRate" id="interestRate" value="0" readonly required>
                    <label for="interestRate" class="form-label">Annual Interest Rate (%)</label>
                </div>
                <div class="col-lg-6 form-floating">
                    <select class="form-select" name="downpayment" id="downpayment" required>
                        <option value="" selected disabled>Select Downpayment Rate</option>
                        <option value="20">20%</option>
                        <option value="25">25%</option>
                        <option value="30">30%</option>
                        <option value="35">35%</option>
                        <option value="40">40%</option>
                        <option value="45">45%</option>
                        <option value="50">50%</option>
                    </select>
                    <label for="downpayment" class="form-label">Downpayment (%)</label>
                </div>
                <div class="col-lg-6 form-floating">
                    <select class="form-select" name="loanTerm" id="loanTerm" required>
                        <option value="" selected disabled>Select Loan Term</option>
                        <option value="12">12 Months</option>
                        <option value="24">24 Months</option>
                        <option value="36">36 Months</option>
                        <option value="48">48 Months</option>
                        <option value="60">60 Months</option>
                    </select>
                    <label for="loanTerm" class="form-label">Loan Term (Months)</label>
                </div>
                <div class="col-12 w-100">
                    <button type="submit" class="w-100 btn btn-danger border border-light">Calculate</button>
                </div>
            </form>
            </section>
            <section class="col-md-6">
            </section>
            </section>)";

    string userDisplay = "<div class=\"d-flex align-items-center text-light gap-3\">" + 
    (cookies.find("name") != cookies.end() ? 
          ("<div class='dropdown'>"
                "<button class='btn btn-outline-danger text-light fw-bold border-light dropdown-toggle' type='button' id='dropdownUser' data-bs-toggle='dropdown' aria-haspopup='true' aria-expanded='false'>" + 
                name +
                "</button>"
                "<div class='dropdown-menu dropdown-menu-end' aria-labelledby='dropdownUser'>"
                    "<a class='dropdown-item active' href='./carloancalculator.cgi'>Car Loan Calculator</a>"
                    "<a class='dropdown-item' href='./userprofile.cgi'>User Profile</a>"
                    "<a class='dropdown-item' href='./logout.cgi'>Logout</a>"
                "</div>"
          "</div>") 
    : 
          "<a href='./login.cgi' class='btn btn-outline-danger text-light fw-bold border-light'>Login</a>") 
    + "</div>";

    // Print the HTML content
    cout << R"(<!DOCTYPE html>
    <html lang="en">
        <head>
        <!-- Document Metadata -->
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
        <meta name="author" content="John Yrrah Cabiles">

        <!-- Favicon and Styles -->
        <link rel="icon" type="image/x-icon" href="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A">
        <style>)" + styleSheetContent + R"(</style>

        <!-- Bootstrap CSS -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" integrity="sha384-AYmEC3Yw5cVb3ZcuHtOA93w35dYTsvhLPVnYs9eStHfGJvOvKxVfELGroGkvsg+p" crossorigin="anonymous"/>

        <!-- Page Title -->
        <title>Car Loan Calculator - Elxtra Motors</title>
    </head>
    <body>
        <!-- Navbar -->
        <header id="navbar" class="bg-dark border-darker fixed-top navbar navbar-expand-xl navbar-dark">
            <div class="container-fluid">
            <a class="navbar-brand d-flex align-items-center" href="#">
                <img src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="" width="30" height="24" class="d-inline-block align-text-top">
                <h1 class="display-4 fs-4 m-3">Elxtra</h1>
            </a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
            </button>
            <nav class="collapse navbar-collapse" id="navbarSupportedContent">
                <ul class="navbar-nav me-auto">
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3" href="./index.cgi">Home</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3" href="./aboutus.cgi">About Us</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3" href="./contactus.cgi">Contact Us</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3" href="./carmodels.cgi">Car Models</a>
                    </li>
                    </ul>
                    <div class="d-flex justify-content-between align-items-center gap-3">
                    <form method="post" action="./carmodels.cgi" class="form-inline flex-grow-1">
                        <section class="input-group">
                            <input class="form-control " type="search" placeholder="Search Car Model..." name="model" aria-label="Search" required>
                            <button class="btn btn-outline-danger border border-light text-light" type="submit"><i class="fas fa-search"></i></button>
                        </section>
                    </form>)" + userDisplay + R"(</div></nav>
            </div>
        </header>
        <main class="main">
        <!-- Header Section -->
        <section>
            <section class="py-4 w-100 d-flex align-items-center justify-content-center">
                <section class="container">
                    <section class="row">
                        <section class="col-sm-8 animate fade-left">
                            <h2 class="fs-5">.</h2>
                        </section>
                    </section>
                </section>
            </section>
        </section>
        <!-- Car Loan Calculator Section -->
        )";
    // Car Loan Calculator Section
    if (requestMethod == "GET") {
        string queryString = getenv("QUERY_STRING");
        map<string, string> queryParams = parseQueryString(queryString);
        // Display car calculator form with selected car model
        if (queryParams.find("carModel") != queryParams.end()) {
            string carModel = queryParams["carModel"];
            for (const CarDetails& car : carDetailsDatabase) {
                if (car.getModel() == carModel) {
                    // Car Loan Calculator Form
                    cout << R"(
                        <section class="container text-light w-100 py-5">
                            <h2 class="display-4 mb-5 text-center">Car Loan Calculator</h2>
                            <section class="row d-flex align-items-center justify-content-center">
                            <form method="post" class="col-md-6 row border border-light mt-0 text-dark bg-dark g-3 p-3 rounded rounded-3">
                                <h3 class="fs-5 m-0 text-light">Calculate Loan for )" << carModel << R"(</h3>
                                <div class="col-12 form-floating">
                                    <select class="form-select" name="carModel" id="carModel" required>)";
                                        for (const CarDetails& car : carDetailsDatabase) {
                                            if (car.getModel() == carModel) {
                                                cout << "<option value=\"" << car.getModel() << "\" selected>" << car.getModel() << "</option>";
                                            } else {
                                                cout << "<option value=\"" << car.getModel() << "\">" << car.getModel() << "</option>";
                                            }
                                        }
                    cout << R"(</select>
                                    <label for="carModel" class="form-label">Car Model</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <input type="text" class="form-control" name="carPrice" id="carPrice" value=")" << fixed << setprecision(2) << car.getPrice() << R"(" readonly required>
                                    <label for="carPrice" class="form-label">Car Price (Php)</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <input type="text" class="form-control" name="interestRate" id="interestRate" value=")" << formatCurrency(car.getInterestRate()) << R"(" readonly required>
                                    <label for="interestRate" class="form-label">Annual Interest Rate (%)</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <select class="form-select" name="downpayment" id="downpayment" required>
                                        <option value="" selected disabled>Select Downpayment Rate</option>
                                        <option value="20">20%</option>
                                        <option value="25">25%</option>
                                        <option value="30">30%</option>
                                        <option value="35">35%</option>
                                        <option value="40">40%</option>
                                        <option value="45">45%</option>
                                        <option value="50">50%</option>
                                    </select>
                                    <label for="downpayment" class="form-label">Downpayment (%)</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <select class="form-select" name="loanTerm" id="loanTerm" required>
                                        <option value="" selected disabled>Select Loan Term</option>
                                        <option value="12">12 Months</option>
                                        <option value="24">24 Months</option>
                                        <option value="36">36 Months</option>
                                        <option value="48">48 Months</option>
                                        <option value="60">60 Months</option>
                                    </select>
                                    <label for="loanTerm" class="form-label">Loan Term (Months)</label>
                                </div>
                                <div class="col-12 w-100">
                                    <button type="submit" class="w-100 btn btn-danger border border-light">Calculate</button>
                                </div>
                            </form>
                            </section>
                        </section>)";
                    break;
                }
            }

        }
        // Display default car loan calculator form
        else {
            // Car Loan Calculator Form
            cout << defaultCarLoanForm;
        }
    }

    // Calculate car loan details
    else if (requestMethod == "POST") {
        string contentLengthStr = getenv("CONTENT_LENGTH");
        // Check if the content length is not empty
        if (!contentLengthStr.empty()) {
            int contentLength = stoi(contentLengthStr);
            string postBody;
            postBody.resize(contentLength);
            cin.read(&postBody[0], contentLength);
            map<string, string> queryParams = parseQueryString(postBody);
            // Calculate car loan details
            if (queryParams.find("carModel") != queryParams.end() && queryParams.find("carPrice") != queryParams.end() && queryParams.find("interestRate") != queryParams.end() && queryParams.find("downpayment") != queryParams.end() && queryParams.find("loanTerm") != queryParams.end()) {
                string carModel = queryParams["carModel"];
                double carPrice = stod(queryParams["carPrice"]);
                double interestRate = stod(queryParams["interestRate"]);
                double downPaymentRate = stod(queryParams["downpayment"]);
                double loanTerm = stod(queryParams["loanTerm"]);
                carLoanDatabase.emplace_back(carModel, carPrice, interestRate, downPaymentRate, loanTerm);
                for (const CarDetails& car : carDetailsDatabase) {
                    if (car.getModel() == carModel) {
                // Car Loan Calculator Form
                    cout << R"(
                        <section class="container text-light w-100 py-5">
                            <h2 class="display-4 mb-5 text-center">Car Loan Calculator</h2>
                            <section class="row">
                            <form method="post" class="col-md-6 row border border-light mt-0 text-dark bg-dark g-3 p-3 rounded rounded-3">
                                <h3 class="fs-5 m-0 text-light">Calculate Loan for )" << carModel << R"(</h3>
                                <div class="col-12 form-floating">
                                    <select class="form-select" name="carModel" id="carModel" required>)";
                                        for (const CarDetails& car : carDetailsDatabase) {
                                            if (car.getModel() == carModel) {
                                                cout << "<option value=\"" << car.getModel() << "\" selected>" << car.getModel() << "</option>";
                                            } else {
                                                cout << "<option value=\"" << car.getModel() << "\">" << car.getModel() << "</option>";
                                            }
                                        }
                    cout << R"(</select>
                                    <label for="carModel" class="form-label">Car Model</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <input type="text" class="form-control" name="carPrice" id="carPrice" value=")" << fixed << setprecision(2) << car.getPrice() << R"(" readonly required>
                                    <label for="carPrice" class="form-label">Car Price (Php)</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <input type="text" class="form-control" name="interestRate" id="interestRate" value=")" << formatCurrency(car.getInterestRate()) << R"(" readonly required>
                                    <label for="interestRate" class="form-label">Annual Interest Rate (%)</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <select class="form-select" name="downpayment" id="downpayment" required>
                                        <option value="" selected disabled>Select Downpayment Rate</option>
                                        <option value="20">20%</option>
                                        <option value="25">25%</option>
                                        <option value="30">30%</option>
                                        <option value="35">35%</option>
                                        <option value="40">40%</option>
                                        <option value="45">45%</option>
                                        <option value="50">50%</option>
                                    </select>
                                    <label for="downpayment" class="form-label">Downpayment (%)</label>
                                </div>
                                <div class="col-lg-6 form-floating">
                                    <select class="form-select" name="loanTerm" id="loanTerm" required>
                                        <option value="" selected disabled>Select Loan Term</option>
                                        <option value="12">12 Months</option>
                                        <option value="24">24 Months</option>
                                        <option value="36">36 Months</option>
                                        <option value="48">48 Months</option>
                                        <option value="60">60 Months</option>
                                    </select>
                                    <label for="loanTerm" class="form-label">Loan Term (Months)</label>
                                </div>
                                <div class="col-12 w-100">
                                    <button type="submit" class="w-100 btn btn-danger border border-light">Calculate</button>
                                </div>
                            </form>)";
                                for (const CarLoan& carLoan : carLoanDatabase) {
                                    carLoan.displayDetails();
                                }
                            cout << R"(
                            </section>)";
                    break;
                    }
                }
            }
            else if (queryParams.find("carModel") != queryParams.end()) {
                string carModel = queryParams["carModel"];
            }
            else {
                // Display default car loan calculator form
                cout << defaultCarLoanForm;
            }
        }
        // Display default car loan calculator form
        else {
            cout << defaultCarLoanForm;
        }
    }

    cout << R"(</main>
        <!-- Footer Section -->
        <footer>
            <section class="w-100 container pt-5 pb-3">
                <section class="animate fade d-flex flex-column flex-sm-row align-items-center justify-content-center">
                    <section class="">
                        <img style="min-width: 75px; max-width: 100px;" src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="Elxtra" class="w-100 d-inline-block align-text-top">
                    </section>
                    <section class="d-md-flex align-items-center m-auto my-3">
                        <nav>
                            <ul class="d-md-flex p-0 m-0">
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./index.cgi">Home</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./aboutus.cgi">About Us</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./contactus.cgi">Contact Us</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./carmodels.cgi">Car Models</a>
                            </li>
                            </ul>
                        </nav>
                    </section>
                    <section class="socials d-flex gap-3 align-items-center justify-content-center">
                        <a href="#" class="text-light fs-4"><i class="fab fa-facebook"></i></a>
                        <a href="#" class="text-light fs-4"><i class="fab fa-twitter"></i></a>
                        <a href="#" class="text-light fs-4"><i class="fab fa-instagram"></i></a>
                    </section>
                </section>
                <hr class="animate fade" />
                <ul class="animate fade d-flex align-items-center justify-content-center gap-3 flex-wrap">
                    <p class="m-3">© 2024 Elxtra. All rights reserved.</p>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Privacy Policy</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Terms and Conditions</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Cookie Policy</a>
                    </li>
                </ul>
            </section>
        </footer>
        <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhGWiC2Al4u+LWgxfKTRIcfu0JTxR+EQDz/bgldoEyl4H0zUF0QKbrJ0EcQF" crossorigin="anonymous"></script>
        <script>
            document.addEventListener('DOMContentLoaded', function() {
                var selectElement = document.getElementById('carModel');

                selectElement.addEventListener('change', function() {
                    var selectedValue = selectElement.value; // Get the selected value
                    window.location.href = './carloancalculator.cgi?carModel=' + encodeURIComponent(selectedValue);
                    // Redirects to the URL with the selected car model as a query parameter
                });
            });
        </script>
        <!-- Scroll Animation Script -->
        <script>
            let observer;
            function handleIntersect(entries, observer) {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                if (entry.target.dataset.animated !== 'true') {
                    triggerAnimation(entry.target);
                    entry.target.dataset.animated = 'true';
                }
                } else {
                entry.target.dataset.animated = 'false';
                }
            });
            }
    
            function triggerAnimation(element) {
            if (element.classList.contains('fade-down')) {
                element.classList.remove('fade-down');
                void element.offsetWidth;
                element.classList.add('fade-down');
            } else if (element.classList.contains('fade-right')) {
                element.classList.remove('fade-right');
                void element.offsetWidth;
                element.classList.add('fade-right');
            } else if (element.classList.contains('fade-left')) {
                element.classList.remove('fade-left');
                void element.offsetWidth;
                element.classList.add('fade-left');
            } else if (element.classList.contains('fade-up')) {
                element.classList.remove('fade-up');
                void element.offsetWidth;
                element.classList.add('fade-up');
            } else {
                element.classList.remove('fade');
                void element.offsetWidth;
                element.classList.add('fade');
            }
            }
    
            function setupIntersectionObserver() {
            const elements = document.querySelectorAll('.animate');
            const options = {
                root: null,
                rootMargin: '80px',
                threshold: 0.1
            };
    
            observer = new IntersectionObserver(handleIntersect, options);
    
            elements.forEach(element => {
                observer.observe(element);
            });
            }
            
            document.addEventListener('DOMContentLoaded', setupIntersectionObserver);
        </script>
        </body>
    </html>)";
    
    return 0;
}