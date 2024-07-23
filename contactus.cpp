#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map> 
#include <fstream>// Include the map header
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

int main() {
    cout << "Content-Type: text/html\n\n";

    // string method = getenv("REQUEST_METHOD");
    // string name;

    // if (method == "GET") {
    //     string query = getenv("QUERY_STRING");
    //     auto params = parseQueryString(query);
    //     if (params.find("name") != params.end()) {
    //         name = params["name"];
    //     }
    // } else if (method == "POST") {
    //     int contentLength = stoi(getenv("CONTENT_LENGTH"));
    //     string postData(contentLength, ' ');
    //     cin.read(&postData[0], contentLength);
    //     auto params = parseQueryString(postData);
    //     if (params.find("name") != params.end()) {
    //         name = params["name"];
    //     }
    // }

      // Read the contents of the style sheet file
      ifstream styleSheetFile("./styles.css");
      string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
      styleSheetFile.close();

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
      <title>Contact us - Elxtra</title>
      </head>
      <body>
      <header id="navbar" class="fixed-top navbar navbar-expand-md navbar-dark fade-down">
        <div class="container-fluid">
          <a class="navbar-brand d-flex gap-3 align-items-center" href="#">
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
            <a class="nav-link p-0 m-3" aria-current="page" href="./aboutus.cgi">About Us</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3 active" href="#" tabindex="-1" aria-disabled="./contactus.cgi">Contact Us</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3" href="#" tabindex="-1" aria-disabled="true">FAQs</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3" href="#" tabindex="-1" aria-disabled="true">Car Models</a>
            </li>
          </ul>
          <div class="d-flex">
            <a class="btn m-3 btn-outline-primary text-light fw-bold border-light">Login</a>
          </div>
          </nav>
        </div>
      </header>
           <main>
        <!-- Hero Section -->
          <section class="cover2">
          <section class="darkener boundary2 py-5 w-100 d-flex align-items-center justify-content-center">
            <section class="container">
              <section class="row">
                <section class="col-sm-8 fade-left">
                  <h2 class="display-3 text-light mt-5">Contact us</h2>
                </section>
              </section>
            </section>
          </section>
        </section>
      <!-- Contact Us Section -->
      <section class="container py-5 text-light">
  <div class="row">
    <div class="col-md-6">
      <div class="contact-us img-container" style="background-image: url('https://ideogram.ai/assets/image/lossless/response/OynpBNaJTjSOaho64xwgsA'); height: 300px; background-size: cover; background-position: center;"></div>
    </div>
    <div class="col-md-6 content-container">
      <div class="contact-info">
        <h2 class="text-light">Contact Us</h2>
        <p class="text-light">We are here to help you with any inquiries you may have. Feel free to reach out to us through the following contact details:</p>
        <h4 class="text-light">Office Address:</h4>
        <p class="text-light">Unit 203, 2nd Floor, Makati Corporate Center, Makati City</p>
        <h4 class="text-light">Phone:</h4>
        <p class="text-light">+63 912 345 6789</p>
        <h4 class="text-light">Email:</h4>
        <p class="text-light">info@elxtra.com</p>
        <div class="contact-details">
          <h4 class="text-light">Office Hours:</h4>
          <p class="text-light">Monday to Friday: 9:00 AM - 6:00 PM</p>
          <p class="text-light">Saturday: 9:00 AM - 12:00 PM</p>
        </div>
      </div>
    </div>
  </div>
</section>
    <!-- Message Us Section -->
<section class="py-5 bg-dark message-us"  style="background-image: url('https://ideogram.ai/assets/image/lossless/response/7D9nJ50qT5-kEtnUp_iHrA'); background-size: cover; background-position: center;">
 <div class="container">
            <h2 class="text-light">Message Us</h2>
            <form>
                <div class="mb-3">
                    <p class="text-light">Name</p>
                    <input type="text" class="form-control" id="name" placeholder="Enter your name">
                </div>
                <div class="mb-3">
                      <p class="text-light">Email</p>
                    <input type="email" class="form-control" id="email" placeholder="Enter your email">
                </div>
                <div class="mb-3">
                    <p class="text-light">Message</p>
                    <textarea class="form-control" id="message" rows="4" placeholder="Enter your message"></textarea>
                </div>
                <button type="submit" class="btn btn-light text-danger fw-bold">Submit</button>
            </form>
        </div>
</section>
    </main>
      <footer class="">
        <section class="w-100 container pt-5 pb-3">
          <section class="d-flex flex-column flex-sm-row align-items-center justify-content-center">
            <section class="">
              <img style="min-width: 75px; max-width: 100px;" src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="Elxtra" class="w-100 d-inline-block align-text-top">
            </section>
            <section class="d-md-flex align-items-center m-auto my-3">
              <nav>
                <ul class="d-md-flex p-0 m-0">
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="/">Home</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" aria-current="page" href="#">About Us</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light active" href="#" tabindex="-1" aria-disabled="true">Contact Us</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">FAQs</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Car Models</a>
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
          <hr />
          <ul class="d-flex align-items-center justify-content-center gap-3 flex-wrap">
            <p class="m-3">© 2024 Elxtra. All rights reserved.</p>
            <li class="nav-item">
              <a class="nav-link p-0 m-3 text-light" href="#">Privacy Policy</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Terms and Conditions</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Cookie Policy</a>
            </li>
          </ul>
        </section>
      </footer>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
      <script>
        const navbar = document.getElementById('navbar');

        window.addEventListener('resize', () => {
          if (window.innerWidth < 768) {
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
            navbar.classList.remove('bg-dark');
            navbar.classList.remove('border-darker');
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