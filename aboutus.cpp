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

    cout << "Content-Type: text/html\n\n";

    string requestMethod = getenv("REQUEST_METHOD");
    // Read environment variables for cookie and query string
    string cookie_header = getenv("HTTP_COOKIE") ? getenv("HTTP_COOKIE") : "";
    map<string, string> cookies = parse_cookies(cookie_header);
    string name;
    // Check if the user is logged in
    if (requestMethod == "GET") {
      if (cookies.find("name") != cookies.end()) {
          name = cookies["name"];
      }
    }

    string userDisplay = "<div class=\"d-flex align-items-center text-light gap-3\">" + 
    (cookies.find("name") != cookies.end() ? 
          ("<div class='dropdown'>"
                "<button class='btn btn-outline-danger text-light fw-bold border-light dropdown-toggle' type='button' id='dropdownUser' data-bs-toggle='dropdown' aria-haspopup='true' aria-expanded='false'>" + 
                name +
                "</button>"
                "<div class='dropdown-menu dropdown-menu-end' aria-labelledby='dropdownUser'>"
                    "<a class='dropdown-item' href='./carloancalculator.cgi'>Car Loan Calculator</a>"
                    "<a class='dropdown-item' href='./userprofile.cgi'>User Profile</a>"
                    "<a class='dropdown-item' href='./logout.cgi'>Logout</a>"
                "</div>"
          "</div>") 
    : 
          "<a href='./login.cgi' class='btn btn-outline-danger text-light fw-bold border-light'>Login</a>") 
    + "</div>";

    // Generate the HTML code
    string htmlCode = R"(<!DOCTYPE html>
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
            <title>About Us - Elxtra Motors</title>
          </head>
      <body>
        <!-- Navbar -->
      <header id="navbar" class="fixed-top header navbar navbar-expand-lg navbar-dark fade-down">
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
                    <a class="nav-link p-0 m-3 active" aria-current="page" href="./aboutus.cgi">About Us</a>
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
        <main>
            <!-- Header Section -->
            <section class="cover2">
                <section class="darkener boundary2 py-5 w-100 d-flex align-items-center justify-content-center">
                    <section class="container">
                        <section class="row">
                            <section class="col-sm-8 animate fade-left">
                                <h2 class="display-3 text-light mt-5">About Us</h2>
                            </section>
                        </section>
                    </section>
                </section>
            </section>
            <!-- Who We Are Section -->
            <section class="container py-5 text-light">
              <h2 class="animate fade-left">Who We Are?</h2>
              <section class="row">
                <section class="col-md-6 mb-3 animate fade-left">
                  <p>
                    Elxtra Motors is a car manufacturing company that specializes in electric vehicles. We are committed to providing the best electric vehicles in the market. Our goal is to help reduce the carbon footprint of the automotive industry by providing electric vehicles that are affordable and reliable.
                  </p>
                  <p>
                    We believe that electric vehicles are the future of transportation. That is why we are dedicated to creating electric vehicles that are not only environmentally friendly but also stylish and affordable. Our team of engineers and designers work hard to create electric vehicles that are not only efficient but also fun to drive.
                  </p>
                  <p>
                    At Elxtra Motors, we are committed to providing the best electric vehicles in the market. We are constantly innovating and improving our electric vehicles to provide our customers with the best driving experience possible. We are dedicated to creating electric vehicles that are not only environmentally friendly but also stylish and affordable.
                  </p>
                </section>
                <section class="col-md-6 d-flex align-items-center justify-content-center">
                  <section class="d-flex align-items-center justify-content-center animate fade-right">
                    <img src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" class="drop-shadow img-fluid">
                  </section>
                </section>
              </section>
            </section>
            <!-- Our Mission and Vision Section -->
            <section class="w-100 text-light cover3 animate fade-up">
              <section class="darkener">
                <section class="container py-5 d-flex gap-5 flex-column aling-items-center justify-content-center">
                  <section class="row">
                    <section class="col-sm-7 animate fade-left">
                      <h2 class="text-shadow">Our Mission</h2>
                      <p class="lead text-shadow">To deliver exceptional electric vehicles that combine unparalleled performance, luxury, and sustainability. We strive to provide our customers with an extraordinary driving experience while fostering a community of forward-thinking, environmentally conscious individuals.</p>
                    </section>
                  </section>
                  <section class="row d-flex align-items-center justify-content-end">
                    <section class="col-sm-7 animate fade-right">
                      <h2 class="text-shadow">Our Vision</h2>
                      <p class="text-shadow lead">To lead the transition to sustainable transportation, inspiring and driving the future with cutting-edge electric vehicle technology and design.</p>
                    </section>
                  </section>
                </section>
              </section>
            </section>
            <!-- Our Commitment to Sustainability Section -->
            <section class="w-100 text-light">
              <section class="container py-5">
                <section class="mb-4 animate fade-lft">
                  <h2>Our Commitment to Sustainability</h2>
                  <p class="lead">At Elextra Motors, sustainability is at the core of everything we do. We are committed to reducing our carbon footprint and promoting environmentally friendly practices throughout our operations. </p>
                </section>
                <section class="row d-flex flex-wrap animate fade-up">
                  <section class="col-lg-3 p-3">
                    <section class="inset-card darkener d-flex flex-column align-items-center justify-content-center p-3 rounded-3">
                      <h3>Eco-Friendly Materials</h3>
                      <p>We use recycled and sustainable materials in our vehicle manufacturing process, minimizing waste and conserving resources.</p>
                    </section>
                  </section>
                  <section class="col-lg-3 p-3">
                    <section class="inset-card darkener d-flex flex-column align-items-center justify-content-center p-3 rounded-3">
                      <h3>Energy Efficiency</h3>
                      <p>Our advanced battery technology and energy-efficient designs reduce energy consumption and extend the range of our vehicles.</p>
                    </section>
                  </section>
                  <section class="col-lg-3 p-3">
                    <section class="inset-card darkener d-flex flex-column align-items-center justify-content-center p-3 rounded-3">
                      <h3>Carbon Neutrality</h3>
                      <p>We are dedicated to achieving carbon neutrality through innovative practices and offsetting our emissions with environmental projects.</p>
                    </section>
                  </section>
                  <section class="col-lg-3 p-3">
                    <section class="inset-card darkener d-flex flex-column align-items-center justify-content-center p-3 rounded-3">
                      <h3>Recycling Programs</h3>
                      <p>We offer comprehensive recycling programs for our batteries and other vehicle components, ensuring that they are disposed of responsibly.</p>
                    </section>
                  </section>
                </section>           
              </section>
            </section>
        </main>
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
        const navbar = document.getElementById('navbar');

        window.addEventListener('resize', () => {
          if (window.innerWidth < 992) {
            navbar.classList.add('bg-dark');
          } else {
            navbar.classList.remove('bg-dark');
          }
        });

        window.addEventListener('scroll', () => {
          if (window.scrollY > 0) {
            navbar.classList.add('bg-dark');
            navbar.classList.add('border-darker');
          } else {
            if (window.innerWidth < 992) {
              navbar.classList.add('border-darker');
              navbar.classList.add('bg-dark');
            } else {
              navbar.classList.remove('border-darker');
              navbar.classList.remove('bg-dark');
            }
          }
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

    // Print the HTML code
    cout << htmlCode;

    return 0;
}