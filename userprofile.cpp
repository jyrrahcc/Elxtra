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
    cout << "Content-Type: text/html\n\n";

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
                    "<a class='dropdown-item active' href='./userprofile.cgi'>User Profile</a>"
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
        <title>User Profile - Elxtra Motors</title>
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
        <main>
        <!-- Header Section -->
        <section class="cover2">
            <section class="darkener boundary2 py-5 w-100 d-flex align-items-center justify-content-center">
                <section class="container">
                    <section class="row">
                        <section class="col-sm-8 animate fade-left">
                            <h2 class="display-3 text-light mt-5">User Profile</h2>
                        </section>
                    </section>
                </section>
            </section>
        </section>
       <!-- user profile section -->
    <div class="py-5 text-light">
        <div class="container">
            <div class="row justify-content-center mb-3">
                <div class="col-md-7 text-center">
                    <h3 class="mb-3">Meet The Team</h3>
                    <p class="subtitle font-weight-normal">Our dedicated team at Elxtra Motors comprises industry experts and innovators who are passionate about driving the future of electric vehicles.</p>
                </div>
            </div>
            <div class="row">
                  <!-- First Column -->
            <div class="col-lg-12 mb-4">
                <div class="card card-shadow border-0">
                    <div class="row no-gutters">
                        <div class="col-md-5 pro-pic" style="background:url(https://scontent.fmnl25-4.fna.fbcdn.net/v/t1.6435-9/129937480_3725664117526569_1060890035174470038_n.jpg?_nc_cat=109&ccb=1-7&_nc_sid=53a332&_nc_eui2=AeHBX0sbd_0V-x7l2xDpyXU43JlavkSgW8vcmVq-RKBby09MoYRqtsGPsyKRagpFH11TQAqIAYG8rd-7V7OdBrEa&_nc_ohc=E9L-Hkv6SLMQ7kNvgFlO4DM&_nc_ht=scontent.fmnl25-4.fna&oh=00_AYAtfFdAkjzFxQs2jv_Sei_nzL2iop0RhfDCqZ_sPKXI_Q&oe=66C4512B) no-repeat center center / cover; height: 400px;">
                            <div class="card-img-overlay">
                                <ul class="list-inline position-relative text-center">
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-facebook"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-twitter"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-instagram"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-behance"></i></a></li>
                                </ul>
                            </div>
                        </div>
                        <div class="col-md-7">
                            <div class="card-body d-flex flex-column justify-content-center">
                                <h5 class="h5 text-light">John Yrrah Cabiles</h5>
                                <p class="lead">CEO</p>
                                <p class="text-light">John leads the company with a visionary approach, driving innovation and ensuring the highest standards of quality and performance.</p>
                                <p class="text-light">jyrrahcc@gmail.com</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <!-- Second Column -->
            <div class="col-lg-12 mb-4">
                <div class="card card-shadow border-0">
                    <div class="row no-gutters">
                        <div class="col-md-7">
                            <div class="card-body d-flex flex-column justify-content-center">
                                <h5 class="text-light">Hans Christian S. Purino</h5>
                                <p class="lead">Chief Technology Officer (CTO)</p>
                                <p class="text-light">Hans oversees the development and implementation of cutting-edge technologies, ensuring that Elxtra Motors stays at the forefront of innovation.</p>
                                <p class="text-light">hcpurino@gmail.com</p>
                            </div>
                        </div>
                        <div class="col-md-5 pro-pic" style="background:url(https://scontent.fmnl25-1.fna.fbcdn.net/v/t39.30808-6/400685916_652746530371106_8942522707911560417_n.jpg?_nc_cat=105&ccb=1-7&_nc_sid=6ee11a&_nc_eui2=AeHNyYuEeXahxjCM4t3BEUl6zyGiujyJHcrPIaK6PIkdyqMEU_sT3RlpVr1Hjn03tE4nbdQqsTvnrFVGlHjAn4_j&_nc_ohc=4MqaZuj9kFgQ7kNvgGhhSfU&_nc_ht=scontent.fmnl25-1.fna&oh=00_AYDUT4eaaQ23QIliMENLFzfb4QG_b59B7P8Vfy5De8QoyA&oe=66A2BBBD) no-repeat center center / cover; height: 400px;">
                            <div class="card-img-overlay">
                                <ul class="list-inline position-relative text-center">
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-facebook"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-twitter"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-instagram"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-behance"></i></a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <!-- Third Column -->
            <div class="col-lg-12 mb-4">
                <div class="card card-shadow border-0">
                    <div class="row no-gutters">
                        <div class="col-md-5 pro-pic" style="background:url(https://scontent.fmnl25-1.fna.fbcdn.net/v/t39.30808-6/371077123_279360344821347_6796263961140553935_n.jpg?_nc_cat=105&ccb=1-7&_nc_sid=6ee11a&_nc_eui2=AeHvbxdov0YL2VgT57SY_2uYUTUqRvW957NRNSpG9b3ns-1FoauiGl545QtI0YDvtoqmZthiSR8D37krhK5eufZM&_nc_ohc=Y_UNBUcjPV8Q7kNvgHvEw8-&_nc_ht=scontent.fmnl25-1.fna&oh=00_AYDIcyH9XvQfqQZ0xRKk49P91ZoLk8lu8FgcR7uEqu1tRA&oe=66A2DF6B) no-repeat center center / cover; height: 400px;">
                            <div class="card-img-overlay">
                                <ul class="list-inline position-relative text-center">
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-facebook"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-twitter"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-instagram"></i></a></li>
                                    <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-behance"></i></a></li>
                                </ul>
                            </div>
                        </div>
                        <div class="col-md-7">
                            <div class="card-body d-flex flex-column justify-content-center">
                                <h5 class="text-light">John Paul Del Pilar</h5>
                                <p class="lead">Chief Operating Officer (COO)</p>
                                <p class="text-light">John Paul ensures smooth operations across all departments, focusing on efficiency and the highest standards of operational excellence.</p>
                                <p class="text-light">jpdelpilar@gmail.com</p>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
                <!-- Fourth Column -->
                <div class="col-lg-12 mb-4">
                    <div class="card card-shadow border-0">
                        <div class="row no-gutters">
                            <div class="col-md-7">
                                <div class="card-body d-flex flex-column justify-content-center">
                                    <h5 class="text-light">Cedrick Libao</h5>
                                  <p class="lead">Chief Operating Officer (COO)</p>
                                <p class="text-light">John Paul ensures smooth operations across all departments, focusing on efficiency and the highest standards of operational excellence.</p>
                                    <p class="text-light">shurigami@gmail.com</p>
                                </div>
                            </div>
                            <div class="col-md-5 pro-pic" style="background:url(https://scontent.fmnl25-3.fna.fbcdn.net/v/t39.30808-6/221831942_1552136185132693_2448188182638511810_n.jpg?_nc_cat=101&ccb=1-7&_nc_sid=a5f93a&_nc_eui2=AeEn3e4E_ZfuuLlV-DtqHE0R_pLjpSd83W7-kuOlJ3zdbnpQLoygeWCXYLhXU60awXv1w08sw9JjfJyDq2FD7qb7&_nc_ohc=hTP5ZEBLwxcQ7kNvgFQihnB&_nc_ht=scontent.fmnl25-3.fna&oh=00_AYBn9gSe_oHVcreMlnRgTz6U5qwBAOdMiOTpp9Gch-YEuQ&oe=66A2B65B) no-repeat center center / cover; height: 400px;">
                                <div class="card-img-overlay">
                                    <ul class="list-inline position-relative text-center">
                                        <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-facebook"></i></a></li>
                                        <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-twitter"></i></a></li>
                                        <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-instagram"></i></a></li>
                                        <li class="list-inline-item"><a href="#" class="text-decoration-none d-block text-white px-1"><i class="icon-social-behance"></i></a></li>
                                    </ul>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
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